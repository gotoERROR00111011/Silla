// TETRIS.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

/*
	��ǰ	:	��Ʈ����
	����	:	������
	�Ⱓ	:	2015/11/07 ~ 2015/11/09 Ver1
				2015/11/09 ~ 2015/11/09 Ver2
				2015/11/13 ~ 2015/11/14	Ver3
				2015/11/13 ~ 2015/11/14 Ver4
				2015/11/15 ~ 2015/11/15	Ver5
				2015/11/28 ~ 2015/11/28 Ver6
				2015/11/28 ~ 2015/11/28 Ver7
				2015/11/28 ~ 2015/11/28 Ver8
				2015/12/04 ~ 2015/12/04 Ver9
	
	Ver1	:	1�� ���� ����, �ױ�, ����, Ű���� �Է�
	Ver2	:	���� �ϼ��Ǹ� ����� ���� ���� ������, ȸ��
	Ver3	:	ȸ�� ������ ����, �� ����, �ѹ��� ������, ���� ����, ���� ���, ���� ����
	Ver4	:	time_h �� C��� ���������� ���� C++�� ����
	Ver5	:	���� �� ��� ȸ������ �ٲٱ�
	Ver6	:	���̱� ������ �����̽���, ȸ�� �ܻ� ����
	Ver7	:	������� �����ֱ�, ����
	Ver8	:	����� ���� & ����
	Ver9	:	�ӵ�
*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

//----������ ����----
#define HEIGHT_FULL 25	//�� ���α���
#define HEIGHT_DRAW 20	//��� ����
#define HEIGHT_IN 4		//����� ������������(4)
#define TOP_DESIGN 1	//���� �������̽� ����
#define HEIGHT_LOW 1	//ó�� ���̴� �ٴ�
#define WIDTH_FULL 10	//�� ���α���
#define LEFT_DESIGN 1	//���� �������̽�
#define BLOCK_SIZE 4	//����� �ִ� ������
//----������ ����----
#define BOX "��"		//�׸� �ƽ�Ű�ڵ�
#define BOX_NULL "  "	//��ĭ
#define BLACK	0		//�� (��+BRIGHT �� �ϸ� ���UP)
#define BLUE	1
#define GREEN	2
#define BG		3
#define RED		4
#define PUPLE	5
#define YELLOW	6
#define WHITE	7
#define BRIGHT	8
#define BACK_COLOR	16
#define MAX_COLOR	255
//BACKGROUND_INTENSITY
//----Ű���� �Է�----
#define ASCII	224		//Ȯ�� �ƽ�Ű �ڵ�
#define UP		72		//�ƽ�Ű�ڵ� ��
#define DOWN	80		//�ƽ�Ű�ڵ� ��
#define LEFT	75		//�ƽ�Ű�ڵ� ��
#define RIGHT	77		//�ƽ�Ű�ڵ� ��
#define TURN_LEFT_Z		122	//��ȸ��
#define TURN_RIGHT_X	120	//��ȸ��
#define SPACE_BAR		32	//�Ʒ���
//----�̺�Ʈ ����----
#define BLANK 0			//��ĭ ��
#define BLOCK 1			//  ĭ ��
#define OVERLAP 2		//BLOCK * 2 (��� ��ħ)
#define TOP 3			//���� ���� ��ġ�� ���
#define BUILD 4			//BLOCK + TOP (�ױ����)

typedef struct block	//�������� ���
{
	COORD point;	//����� ��ǥ
	int state;		//����� �̺�Ʈ ���°�
	char design[3];	//�ƽ�Ű�ڵ� ���
	int color;		//����
}block;

typedef struct tetris	//�׿��ִ� ���
{
	int state;
	char design[3];
	int color;
}tetris;

typedef struct savedata	//���� ������
{
	int rank;
	char name[20];
	int score;
}savedata;

int lock;
int score;

block next[BLOCK_SIZE][BLOCK_SIZE];				//���� ��� �����ֱ��
block block_input[BLOCK_SIZE][BLOCK_SIZE];		//����� ���� �� ����ϴ� �迭
tetris blocked[HEIGHT_FULL][WIDTH_FULL];		//�׿��ִ� ��� �迭

void setBase(void);		//�ʱ⼳��
void draw(void);		//���÷��� ���
void nextBlock(void);	//���� ��� �����ֱ�
void newBlock(void);	//��ϻ���
void keypress(void);	//Ű���� �Է� ó��
void down(void);		//�ٴ����� �����̵�
int moveChk(int, int);	//�̵��������� üũ
void moveBlock(int key);//����̵�
void reBlock(void);		//ȸ���� ��� ���
void rotateLeft(void);	//���� ȸ��
void rotateRight(void);	//������ ȸ��
void topBlock(void);	//����� üũ
int buildChk(int);		//�ױⰡ��üũ
void build(void);		//�ױ�
void scoring(int);		//���� �߰�, ���
void clearLine(int line);	//�� ����
void clear(void);		//�� ����� �� ������
void fail(void);		//���� ���� Ȯ��
void endGame(void);		//FAIL ���
void endBlock(void);	//�й�ǥ�� (��� �����ȯ)
void save(void);		//����

int _tmain(int argc, _TCHAR* argv[])				//����
{
	clock_t t1, t2;		//�ð�
	int level = 1000;	//������ ��������
	int levelup = 1;	//�ʱ� ����
	t1 = clock();		//�ð�����
	setBase();			//�ʱ⼳��
	while (1)			//���η���
	{
		t2 = clock();	//�ð� ����
		if (t2 - t1 > level)		//1�ʰ� ������
		{
			moveBlock(DOWN);//����� ��ĭ ����
			t1 = t2;		//���̸� 0���� ����
			if (score >= (levelup * 1000))	//���� * 1000���� �Ǹ�
			{
				levelup++;					//���� ��
				level = (level * 2) / 3;	//�ӵ� ����
			}
		}
		if (_kbhit()) keypress();	//Ű���� �Է��� �߻��ϸ�
		if (lock == 1)				//����(���η���) �������
			break;
	}
	endBlock();	//�ٹ̱� ���
	endGame();	//�ٹ̱� ���
	save();		//����
}

void setBase()	//�ʱ⼳��
{
	int height, width;	//for�� ����
	lock = 0;
	score = 0;

	for (height = 0; height < HEIGHT_FULL; height++)
	{
		for (width = 0; width < WIDTH_FULL; width++)
		{
			blocked[height][width].state = BLANK;		//���� - ��ĭ
			strcpy(blocked[height][width].design, BOX_NULL);	//���
			if (height == HEIGHT_FULL - HEIGHT_LOW) blocked[height][width].state = BLOCK;	//������ �عٴ� ����
		}
	}
	draw();		//�׸���
	scoring(0);
	nextBlock();//ù ���
	newBlock();	//��� ����
}

void draw()	//ȭ�� ��ü�� �����
{
	int height, width;	//for�� ����

	system("cls");	//ȭ���� �����
	//������--------------------------------------------------------
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	printf("��");
	for (width = 0; width < WIDTH_FULL; width++)
	{
		printf("��");
	}
	printf("��");
	printf("\n");
	for (height = HEIGHT_IN; height < HEIGHT_FULL - 1; height++) //���̴� ���� ���
	{
		printf("��");
		for (width = 0; width < WIDTH_FULL; width++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blocked[height][width].color);
			printf("%s", blocked[height][width].design);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("��\n");
	}
	printf("��");
	for (width = 0; width < WIDTH_FULL; width++)
	{
		printf("��");
	}
	printf("��");
	printf("\n");
	//������--------------------------------------------------------
}

void nextBlock()
{
	int height, width;	//for�� ����
	int design;			//����� ������ ���� 7����
	COORD pos;
	srand((unsigned)time(NULL));	//������ ���� �Լ�
	design = (rand() % 7);			//�������� ������ ���� ����

	for (height = 0; height < BLOCK_SIZE; height++)	//����4 ���
	{
		for (width = 0; width < BLOCK_SIZE; width++)//++)	//����4 ���
		{
			next[height][width].point.Y = height + TOP_DESIGN;	//��ü ��ǥ - ����
			next[height][width].point.X = (width + (WIDTH_FULL / 2) - 1) - 1;		//��ü ��ǥ - ����(�߽�)
			next[height][width].state = BLANK;				//���� - ���
			strcpy(next[height][width].design, BOX_NULL);	//���
		}
	}
	if (design == 0)	//����
	{
		next[0][1].state = BLOCK; next[0][1].color = RED + BRIGHT;
		next[1][1].state = BLOCK; next[1][1].color = RED + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = RED + BRIGHT;
		next[3][1].state = BLOCK; next[3][1].color = RED + BRIGHT;
	}
	else if (design == 1)	//�׸�
	{
		next[1][1].state = BLOCK; next[1][1].color = YELLOW + BRIGHT;
		next[1][2].state = BLOCK; next[1][2].color = YELLOW + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = YELLOW + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = YELLOW + BRIGHT;
	}
	else if (design == 2)	//������� 1
	{
		next[1][1].state = BLOCK; next[1][1].color = BLUE + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = BLUE + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = BLUE + BRIGHT;
		next[3][2].state = BLOCK; next[3][2].color = BLUE + BRIGHT;
	}
	else if (design == 3)	//������� 2
	{
		next[1][2].state = BLOCK; next[1][2].color = PUPLE + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = PUPLE + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = PUPLE + BRIGHT;
		next[3][1].state = BLOCK; next[3][1].color = PUPLE + BRIGHT;
	}
	else if (design == 4)	//���� 1
	{
		next[1][1].state = BLOCK; next[1][1].color = GREEN + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = GREEN + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = GREEN + BRIGHT;
		next[2][3].state = BLOCK; next[2][3].color = GREEN + BRIGHT;
	}
	else if (design == 5)	//���� 2
	{
		next[1][3].state = BLOCK; next[1][3].color = BG + BRIGHT;
		next[2][3].state = BLOCK; next[2][3].color = BG + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = BG + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = BG + BRIGHT;
	}
	else if (design == 6)	//������
	{
		next[1][2].state = BLOCK; next[1][2].color = WHITE + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = WHITE + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = WHITE + BRIGHT;
		next[2][3].state = BLOCK; next[2][3].color = WHITE + BRIGHT;
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			if (next[height][width].state == BLOCK)		//4X4 �迭�� ����� �ִ�ĭ
				strcpy(next[height][width].design, BOX);	//�Ṯ�ڸ� ����
		}
	}
	//���� ���鿡 ���� ��� ���
	pos.Y = 1;
	pos.X = (LEFT_DESIGN + WIDTH_FULL + 4) * 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE + BRIGHT);
	printf("NEXT BLOCK");
	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			pos.Y = height + 2;
			pos.X = (width + LEFT_DESIGN + WIDTH_FULL + 4) * 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), next[height][width].color);
			printf("%s", next[height][width].design);
		}
	}
}

void newBlock()	//��� ����
{
	int height, width;	//for�� ����

	for (height = 0; height < BLOCK_SIZE; height++)	//����4 ���
	{
		for (width = 0; width < BLOCK_SIZE; width++)//++)	//����4 ���
		{
			block_input[height][width].point.Y = next[height][width].point.Y;	//��ü ��ǥ - ����
			block_input[height][width].point.X = next[height][width].point.X;	//��ü ��ǥ - ����(�߽�)
			block_input[height][width].state = next[height][width].state;		//���� - ���
			block_input[height][width].color = next[height][width].color;		//��
			strcpy(block_input[height][width].design, next[height][width].design);	//���
		}
	}
	topBlock();	//���� �ֻ����� �ִ� ��� �˻�
	reBlock();	//ù ���
	nextBlock();
}

void keypress()
{
	int ascii1 = _getch();	//Ű���� �Է°� ������
	int ascii2;				//Ȯ��ƽ�Ű�ڵ� ��
	int height, width;		//
	if (ascii1 == ASCII)		//Ȯ��ƽ�Ű�ڵ�
	{
		ascii2 = _getch();	//Ű���� �Է°� ������
		switch (ascii2)		//Ȯ��Ű������ ����ġ
		{
		case DOWN:
			if (block_input[BLOCK_SIZE - 1][0].point.Y < (HEIGHT_FULL))	//������ �ȹ������
				moveBlock(ascii2);										//�̵�
			break;
		case LEFT:
			for (width = 0; width < BLOCK_SIZE; width++)
				for (height = 0; height < BLOCK_SIZE; height++)
					if (block_input[height][width].state == BLOCK)//��ϻ��� (���� �������)
						goto left;//���� for�� ����
		left:
			if (block_input[height][width].point.X > 0)	//������ �ȹ������
				moveBlock(ascii2);						//�̵�
			break;
		case RIGHT:
			for (width = BLOCK_SIZE - 1; width >= 0; width--)
				for (height = BLOCK_SIZE - 1; height >= 0; height--)
					if (block_input[height][width].state == BLOCK)//��ϻ��� (���� �������)
						goto right;//���� for�� ����
		right:
			if (block_input[height][width].point.X < (WIDTH_FULL - 1))	//������ �ȹ������
				moveBlock(ascii2);										//�̵�
			break;
		default:
			break;
		}
	}
	else if (ascii1 == TURN_LEFT_Z)		//�ƽ�Ű�ڵ� z�� �ԷµǸ�
		rotateLeft();//��ȸ��
	else if (ascii1 == TURN_RIGHT_X)	//�ƽ�Ű�ڵ� x�� �ԷµǸ�
		rotateRight();//��ȸ��
	else if (ascii1 == SPACE_BAR)		//�����̽���
		down();	//�Ʒ���
}

void down()
{
	int height, width;
	COORD pos;

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			if (block_input[height][width].state == BLOCK)	//��ϻ����� ��ǥ - �̵� ��
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//�ӽ���ǥ - ����
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2;	//�ӽ���ǥ - ����
				if (pos.Y < TOP_DESIGN) continue;	//����±��� ó��
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//���� ��� ��ǥ
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);	//�����
				printf("%s", block_input[height][width].design);	//���
			}
		}
	}

	while (1)
	{
		if (buildChk(1))
		{
			build();	//�ױ�
			newBlock(); //�� ��� ����
			break;
		}
		for (height = 0; height < BLOCK_SIZE; height++)
		{
			for (width = 0; width < BLOCK_SIZE; width++)
			{
				block_input[height][width].point.Y++;	//��ĭ�� ������
			}
		}
	}
}

int moveChk(int y, int x)	//����� ������ �� �ִ��� üũ
{
	int height, width;		//for����
	int yy, xx;				//

	if (x == 0) return 0;	//�¿� �̵��� �ƴѰ��

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			yy = block_input[height][width].point.Y + y;//�Ű����� �ӽ���ǥ
			xx = block_input[height][width].point.X + x;//�Ű����� �ӽ���ǥ
			//�̵��� ���� ����� ������
			if (block_input[height][width].state == BLOCK && blocked[yy][xx].state != BLANK)
				return 1;	//1 ��ȯ (����)
		}
	}
	return 0;	//0 ��ȯ ����
}

void moveBlock(int key)	//��� �̵�
{
	int height, width;	//for�� ����
	int wayX = 0;		//������ ��
	int wayY = 0;		//������ ��
	COORD pos;			//�������̽� ����

	if (key == DOWN) wayY = 1;			//��
	else if (key == LEFT) wayX = -1;		//��
	else if (key == RIGHT) wayX = 1;	//��
	else if (key == UP)	wayY = -1;		//�� ����

	if (moveChk(wayY, wayX)) return;	//�¿�� �����ϼ� �ִ��� üũ

	if (buildChk(wayY))	//���ϻ������� Ȯ��
	{
		build();	//�ױ�
		newBlock();	//����� ����
		return;		//����
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			if (block_input[height][width].point.Y < HEIGHT_IN) continue;
			if (block_input[height][width].state == BLOCK)	//��ϻ����� ��ǥ - �̵� ��
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//�ӽ���ǥ - ����
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2;	//�ӽ���ǥ - ����
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//���� ��� ��ǥ
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);	//�����
				printf("%s", block_input[height][width].design);	//���
			}
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			block_input[height][width].point.Y += wayY;	//���� ��ǥ ����
			block_input[height][width].point.X += wayX;	//�¿� ��ǥ ����
			if (block_input[height][width].point.Y < HEIGHT_IN) continue;
			if (block_input[height][width].state == BLOCK)	//��ϻ����� ��ǥ - �̵��� ��ǥ
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//�ӽ���ǥ - ����
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2;	//�ӽ���ǥ - ����
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//�̵��� ��� ��ǥ
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block_input[height][width].color);//����� ����
				printf("%s", block_input[height][width].design);	//���
			}
		}
	}
}

void reBlock()
{
	int height, width;	//for�� ����
	COORD pos;

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			if (block_input[height][width].state == BLOCK)	//��� �ڸ�
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//��ǥ ����
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2; //��ǥ ����
				if (pos.Y < TOP_DESIGN) continue;	//����� �����̸� ��� ��ĭ �ǳʶٱ�
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//��� ��ǥ
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block_input[height][width].color);//���� ����
				printf("%s", block_input[height][width].design);				//���
			}
		}
	}
}

void rotateLeft()	//��ȸ��
{
	int height, width;	//���� ����
	int turn_height, turn_width;	//ȸ�� ������
	COORD pos;						//ȸ�� ������
	block temp[BLOCK_SIZE][BLOCK_SIZE];	//�ӽ� ����

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			turn_height = BLOCK_SIZE - width - 1;	//ȸ�� �� �迭��ǥ - ����
			turn_width = height;					//ȸ�� �� �迭��ǥ - ����
			temp[height][width].point = block_input[height][width].point;			//��ǥ���� ����
			temp[turn_height][turn_width].state = block_input[height][width].state;	//ȸ�� �� �ӽù迭�� ����
			temp[turn_height][turn_width].color = block_input[height][width].color;	//ȸ�� �� �ӽù迭�� ����
			strcpy(temp[turn_height][turn_width].design, block_input[height][width].design);	//���ڿ��� ���� �ű��
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			pos.Y = temp[height][width].point.Y;	//�ӽ� ��ǥ
			pos.X = temp[height][width].point.X;	//�ӽ� ��ǥ
			if (temp[height][width].state == BLOCK && blocked[pos.Y][pos.X].state != BLANK)	//ȸ���� ���� ��ĭ�� �ƴϸ� ����
				return;
			else if (!(pos.X >= 0 && pos.X < WIDTH_FULL))	//������ ����� ����
				return;
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			block_input[height][width].point = temp[height][width].point;			//���� ��Ͽ� ����
			block_input[height][width].state = temp[height][width].state;			//���� ��Ͽ� ����
			block_input[height][width].color = temp[height][width].color;			//���� ��Ͽ� ����
			strcpy(block_input[height][width].design, temp[height][width].design);	//���� ��Ͽ� ����
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			pos.Y = block_input[height][width].point.Y;	//�迭���� �� �ڸ� ���̱�
			pos.X = block_input[height][width].point.X;	//�迭���� �� �ڸ� ���̱�
			//��ĭ�̸� �����
			if (blocked[pos.Y][pos.X].state == BLANK)
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//�ӽ� ��ǥ - ����
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2;	//�ӽ� ��ǥ - ����
				if (pos.Y < TOP_DESIGN) continue;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//����� ��ǥ�� �̵�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);//�����
				printf("%s", block_input[height][width].design);				//�����
			}
		}
	}
	reBlock();	//ȸ���� ��� ���
}

void rotateRight()	//��ȸ��
{
	int height, width;	//���� ����
	int turn_height, turn_width;	//ȸ�� ������
	COORD pos;						//ȸ�� ������
	block temp[BLOCK_SIZE][BLOCK_SIZE];	//�ӽ� ����

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			turn_height = width;					//ȸ�� �� �迭��ǥ - ����
			turn_width = BLOCK_SIZE - height - 1;	//ȸ�� �� �迭��ǥ - ����
			temp[height][width].point = block_input[height][width].point;			//��ǥ���� ����
			temp[turn_height][turn_width].state = block_input[height][width].state;	//ȸ�� �� �ӽù迭�� ����
			temp[turn_height][turn_width].color = block_input[height][width].color;	//ȸ�� �� �ӽù迭�� ����
			strcpy(temp[turn_height][turn_width].design, block_input[height][width].design);	//���ڿ��� ���� �ű��
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			pos.Y = temp[height][width].point.Y;	//�ӽ� ��ǥ
			pos.X = temp[height][width].point.X;	//�ӽ� ��ǥ
			if (temp[height][width].state == BLOCK && blocked[pos.Y][pos.X].state != BLANK)	//ȸ���� ���� ��ĭ�� �ƴϸ� ����
				return;
			else if (!(pos.X >= 0 && pos.X < WIDTH_FULL))	//������ ����� ����
				return;
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			pos.Y = block_input[height][width].point.Y;	//�迭���� �� �ڸ� ���̱�
			pos.X = block_input[height][width].point.X;	//�迭���� �� �ڸ� ���̱�
			//��ĭ�̸� �����
			if (blocked[pos.Y][pos.X].state == BLANK)
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//�ӽ� ��ǥ - ����
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2;	//�ӽ� ��ǥ - ����
				if (pos.Y < TOP_DESIGN) continue;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//����� ��ǥ�� �̵�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);//�����
				printf("%s", block_input[height][width].design);				//�����
			}
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			block_input[height][width].point = temp[height][width].point;			//���� ��Ͽ� ����
			block_input[height][width].state = temp[height][width].state;			//���� ��Ͽ� ����
			block_input[height][width].color = temp[height][width].color;			//���� ��Ͽ� ����
			strcpy(block_input[height][width].design, temp[height][width].design);	//���� ��Ͽ� ����
		}
	}
	reBlock();	//ȸ���� ��� ���
}

void topBlock()	//�ֻ����� ��� �˻�
{
	int height, width;	//���� ����
	int flag;			//���ӵ� ��� Ȯ��

	for (width = 0; width < WIDTH_FULL; width++)
	{
		flag = 0;	//�ʱ�ȭ
		for (height = 0; height < HEIGHT_FULL; height++)
		{
			if (blocked[height][width].state == TOP)	//���� TOP�� �ʱ�ȭ
				blocked[height][width].state = BLOCK;	//�Ϲ� ��ϻ���
			if (flag == 1 && blocked[height][width].state == BLANK)	//flag=0 �϶�, ��ĭ�� �˻�Ǹ�
				flag = 0;	//�ʱ�ȭ
			if (blocked[height][width].state == BLOCK && flag == 0)	//flag=0 �϶�, ����� �˻�Ǹ�
			{
				blocked[height][width].state = TOP;	//TOP���·� ����
				flag = 1;	//flag �ٲٱ�
			}
			else if (blocked[height][width].state != BLANK && flag == 1)	//flag=1 �̰� ��ĭ�� �ƴϸ�
				blocked[height][width].state = BLOCK;	//��ϻ���
		}
	}
}

int buildChk(int y)	//������ �ִ��� �˻�
{
	int height, width;	//���� ����
	int yy, xx;			//�ӽ� ��ǥ

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			yy = block_input[height][width].point.Y + y;	//��ĭ �Ʒ� ��ǥ
			xx = block_input[height][width].point.X;		//���� ��ǥ
			//���� ��ϰ� ���� ��� ��ǥ�� ���°��� ���� BUILD �̸� (BLOCK + TOP)
			if (block_input[height][width].state + blocked[yy][xx].state == BUILD)
				return 1;	//1��ȯ (�ױ�)
		}
	}
	return 0;
}

void build()
{
	int height, width;	//for�� ����
	int yy, xx;			//�ӽú��� (�ѹ����� ���� ���̱�)
	COORD pos;

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			if (block_input[height][width].state == BLOCK)	//����� �ִ� ĭ�̸�
			{
				yy = block_input[height][width].point.Y;	//�Ű����� �ӽ���ǥ
				xx = block_input[height][width].point.X;	//�Ű����� �ӽ���ǥ

				if (block_input[height][width].state == BLANK) continue;
				if (blocked[yy][xx].state != BLANK) continue;
				pos.Y = yy - HEIGHT_IN + TOP_DESIGN;	//�ӽ���ǥ - ����
				pos.X = (xx + LEFT_DESIGN) * 2;	//�ӽ���ǥ - ����
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//�̵��� ��� ��ǥ
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block_input[height][width].color);//����� ����
				blocked[yy][xx].state = BLOCK;				//�׿��ִ� ��Ϲ迭�� ä���
				blocked[yy][xx].color = block_input[height][width].color;	//����
				strcpy(blocked[yy][xx].design, BOX);		//��� ����
				printf("%s", blocked[yy][xx].design);
			}
		}
	}
	fail();		//�й� Ȯ��
	clear();	//�ϼ��� �� �����
}

void scoring(int num)	//���� �ű�� & ���
{
	COORD pos;
	score = score + num;	//���� �߰�

	//score ǥ�� ���
	pos.Y = 7;
	pos.X = (LEFT_DESIGN + WIDTH_FULL + 5) * 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE + BRIGHT);
	printf("SCORE");
	//���� ���� ���
	pos.Y = 8;
	pos.X = (LEFT_DESIGN + WIDTH_FULL + 5) * 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE + BRIGHT);
	printf(" %d", score);
}

void clearLine(int line)	//����� ������
{
	int height, width;	//���� ����
	for (height = line; height > HEIGHT_IN; height--)
	{
		for (width = 0; width < WIDTH_FULL; width++)
		{
			blocked[height][width] = blocked[height - 1][width];	//���� �� ���� ��ĭ�� ������
			strcpy(blocked[height][width].design, blocked[height - 1][width].design);
		}
	}
	system("cls");	//ȭ�� �����
	draw();			//��ü �����
	scoring(100);
}

void clear()
{
	int height, width;	//���� ����
	int delcnt;			//����� ī���� (= ���� ����)

	for (height = HEIGHT_FULL - HEIGHT_LOW - 1; height > HEIGHT_IN; height--)	//�Ʒ����� ����
	{
		delcnt = 0;	//�ʱ�ȭ
		for (width = 0; width < WIDTH_FULL; width++)	//���� ����
		{
			if (blocked[height][width].state != BLANK)	//��ĭ�� �ƴϸ�
				delcnt++;	//ī��Ʈ ����
		}
		if (delcnt == WIDTH_FULL)	//ī��Ʈ�� ���α��̿� ��������
		{
			clearLine(height);	//����� ����
			height++;			//���� �ٷ� �̵�
		}
	}
}

void fail()	//�й����
{
	int width;	//����

	for (width = HEIGHT_IN; width < WIDTH_FULL; width++)	//������� ����
	{
		if (blocked[HEIGHT_IN][width].state != BLANK)		//��ĭ�� �ƴѰ� �ϳ��� ������
			lock = 1;	//���� ����
	}
}

void endGame()	//FAIL ���
{
	COORD pos;
	int color;
	int sleep = 20;

	for (color = 0; color < 8; color++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (color % 8 + BRIGHT)* BACK_COLOR);
		system("cls");
		Sleep(100);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (BLACK)* BACK_COLOR);
	system("cls");

	for (color = 0; color < 8; color++)
	{
		Sleep(sleep);
		pos.Y = 0;
		pos.X = 0;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (BLUE + color) % 8 + BRIGHT);
		if (color == 7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK + BRIGHT);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);				printf("������");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("������");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��");

		Sleep(sleep);
		pos.Y = 4;
		pos.X = 8;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (GREEN + color) % 8 + BRIGHT);
		if (color == 7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK + BRIGHT);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);				printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("���");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("�� ��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("����");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��   ��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��    ��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��     ��");

		Sleep(sleep);
		pos.Y = 8;
		pos.X = 16;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (BG + color) % 8 + BRIGHT);
		if (color == 7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK + BRIGHT);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);				printf("����");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("  ��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("  ��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("  ��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("  ��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("  ��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("����");

		Sleep(sleep);
		pos.Y = 12;
		pos.X = 24;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (RED + color) % 8 + BRIGHT);
		if (color == 7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK + BRIGHT);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);				printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("��");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("������");
	}
}

void endBlock()	//�й�ȿ��(�ٹ�) ���
{
	int height, width;	//���� ����
	COORD pos;

	for (width = 0; width < WIDTH_FULL; width++)
	{
		if (blocked[HEIGHT_IN - 1][width].state != BLANK)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (BLACK)* BACK_COLOR);
			pos.Y = 0;
			pos.X = (width + LEFT_DESIGN) * 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("%s", blocked[HEIGHT_IN - 1][width].design);
		}
		Sleep(10);
	}

	for (height = HEIGHT_IN; height < HEIGHT_FULL - 1; height++)
	{
		for (width = 0; width < WIDTH_FULL; width++)
		{
			if (blocked[height][width].state != BLANK)
			{
				blocked[height][width].color = (BLACK)* BACK_COLOR;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (BLACK)* BACK_COLOR);
			}
			else
			{
				blocked[height][width].color = (WHITE + BRIGHT) * BACK_COLOR;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WHITE + BRIGHT) * BACK_COLOR);
			}
			pos.Y = height - HEIGHT_IN + TOP_DESIGN;
			pos.X = (width + LEFT_DESIGN) * 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("%s", blocked[height][width].design);
			Sleep(10);
		}
	}
	Sleep(1500);
}

void save()
{
	FILE *fp;
	savedata ranking[11];	//������ ������ �迭 10�� + �̹��� ���� ���� ���� 1��
	savedata temp;			//�ڸ� ��ȯ��
	int i, j;				//�ݺ���
	int length;				//����(ó�� ����� 1��, 2��... �̱⶧����)
	system("cls");			//ȭ������

	fp = fopen("F:\\TETRIS.txt", "r");	//�б�	//F:\TETRIS.txt ���� �б�����
	if (fp == NULL)	// �������
	{
		printf("���� ���� ����\n");
		return;
	}
	else   //���� ����
	{
		for (i = 1; i < 11; i++)
		{
			fscanf(fp, "%d", &ranking[i].rank);	//����
			fscanf(fp, "%s", &ranking[i].name);	//�̸�
			fscanf(fp, "%d", &ranking[i].score);//����
			fscanf(fp, "");
			if (feof(fp) != 0) break;			//�������� ������ �ݺ�����
		}
		fclose(fp);	//�б����� �ݱ�
	}
	length = i;	//�о�� �÷��̾� �ڷ� ��

	printf("�̸� �Է� : ");
	scanf("%s", &ranking[0].name);
	ranking[0].rank = 0;
	ranking[0].score = score;

	for (i = 0; i < length; i++)	//����
	{
		for (j = 0; j < length; j++)
		{
			if (ranking[i].score > ranking[j].score)
			{
				temp = ranking[i];
				ranking[i] = ranking[j];
				ranking[j] = temp;
			}
		}
	}

	for (i = 0; i < length; i++)
	{
		ranking[i].rank = i + 1;	//���ĵ� �ڷῡ ���� �ű��
	}
	//1~10�� ���
	system("cls");
	printf("rank\t name\t score\n");
	for (i = 0; i < length; i++)
	{
		printf("%d\t ", ranking[i].rank);
		printf("%s\t ", ranking[i].name);
		printf("%d\n", ranking[i].score);
	}

	fp = fopen("F:\\TETRIS.txt", "w");	//��������
	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return;
	}
	else
	{
		for (i = 0; i < length; i++)
		{
			fprintf(fp, "%d ", ranking[i].rank);
			fprintf(fp, "%s ", ranking[i].name);
			fprintf(fp, "%d ", ranking[i].score);
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
}