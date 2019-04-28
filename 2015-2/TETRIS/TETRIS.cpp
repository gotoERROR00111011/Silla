// TETRIS.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

/*
	작품	:	테트리스
	제작	:	임현택
	기간	:	2015/11/07 ~ 2015/11/09 Ver1
				2015/11/09 ~ 2015/11/09 Ver2
				2015/11/13 ~ 2015/11/14	Ver3
				2015/11/13 ~ 2015/11/14 Ver4
				2015/11/15 ~ 2015/11/15	Ver5
				2015/11/28 ~ 2015/11/28 Ver6
				2015/11/28 ~ 2015/11/28 Ver7
				2015/11/28 ~ 2015/11/28 Ver8
				2015/12/04 ~ 2015/12/04 Ver9
	
	Ver1	:	1초 간격 낙하, 쌓기, 생성, 키보드 입력
	Ver2	:	줄이 완성되면 지우고 위의 줄을 내리기, 회전
	Ver3	:	회전 문제점 개선, 색 설정, 한번에 내리기, 게임 종료, 종료 출력, 외형 조정
	Ver4	:	time_h 의 C언어 미지원으로 인해 C++로 변경
	Ver5	:	종료 후 블록 회색으로 바꾸기
	Ver6	:	쌓이기 직전에 스페이스바, 회전 잔상 수정
	Ver7	:	다음블록 보여주기, 점수
	Ver8	:	종료시 저장 & 순위
	Ver9	:	속도
*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

//----사이즈 설정----
#define HEIGHT_FULL 25	//총 세로길이
#define HEIGHT_DRAW 20	//출력 길이
#define HEIGHT_IN 4		//새블록 생성구간길이(4)
#define TOP_DESIGN 1	//상측 인터페이스 길이
#define HEIGHT_LOW 1	//처음 쌓이는 바닥
#define WIDTH_FULL 10	//총 가로길이
#define LEFT_DESIGN 1	//좌측 인터페이스
#define BLOCK_SIZE 4	//블록의 최대 사이즈
//----디자인 설정----
#define BOX "■"		//네모 아스키코드
#define BOX_NULL "  "	//빈칸
#define BLACK	0		//색 (색+BRIGHT 를 하면 밝기UP)
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
//----키보드 입력----
#define ASCII	224		//확장 아스키 코드
#define UP		72		//아스키코드 ↑
#define DOWN	80		//아스키코드 ↓
#define LEFT	75		//아스키코드 ←
#define RIGHT	77		//아스키코드 →
#define TURN_LEFT_Z		122	//좌회전
#define TURN_RIGHT_X	120	//우회전
#define SPACE_BAR		32	//아래로
//----이벤트 설정----
#define BLANK 0			//빈칸 값
#define BLOCK 1			//  칸 값
#define OVERLAP 2		//BLOCK * 2 (블록 겹침)
#define TOP 3			//가장 높은 위치의 블록
#define BUILD 4			//BLOCK + TOP (쌓기상태)

typedef struct block	//내려오는 블록
{
	COORD point;	//블록의 좌표
	int state;		//블록의 이벤트 상태값
	char design[3];	//아스키코드 모양
	int color;		//색상
}block;

typedef struct tetris	//쌓여있는 블록
{
	int state;
	char design[3];
	int color;
}tetris;

typedef struct savedata	//저장 데이터
{
	int rank;
	char name[20];
	int score;
}savedata;

int lock;
int score;

block next[BLOCK_SIZE][BLOCK_SIZE];				//다음 블록 보여주기용
block block_input[BLOCK_SIZE][BLOCK_SIZE];		//블록을 쌓을 때 사용하는 배열
tetris blocked[HEIGHT_FULL][WIDTH_FULL];		//쌓여있는 블록 배열

void setBase(void);		//초기설정
void draw(void);		//디스플레이 기능
void nextBlock(void);	//다음 블록 보여주기
void newBlock(void);	//블록생성
void keypress(void);	//키보드 입력 처리
void down(void);		//바닥으로 순간이동
int moveChk(int, int);	//이동가능한지 체크
void moveBlock(int key);//블록이동
void reBlock(void);		//회전후 블록 출력
void rotateLeft(void);	//왼쪽 회전
void rotateRight(void);	//오른쪽 회전
void topBlock(void);	//꼭대기 체크
int buildChk(int);		//쌓기가능체크
void build(void);		//쌓기
void scoring(int);		//점수 추가, 출력
void clearLine(int line);	//줄 삭제
void clear(void);		//줄 지우고 줄 내리기
void fail(void);		//게임 종료 확인
void endGame(void);		//FAIL 출력
void endBlock(void);	//패배표시 (블록 흑백전환)
void save(void);		//저장

int _tmain(int argc, _TCHAR* argv[])				//메인
{
	clock_t t1, t2;		//시간
	int level = 1000;	//레벨업 조건점수
	int levelup = 1;	//초기 레벨
	t1 = clock();		//시간조절
	setBase();			//초기설정
	while (1)			//메인루프
	{
		t2 = clock();	//시간 갱신
		if (t2 - t1 > level)		//1초가 지나면
		{
			moveBlock(DOWN);//블록을 한칸 내림
			t1 = t2;		//차이를 0으로 돌림
			if (score >= (levelup * 1000))	//레벨 * 1000점이 되면
			{
				levelup++;					//레벨 업
				level = (level * 2) / 3;	//속도 증가
			}
		}
		if (_kbhit()) keypress();	//키보드 입력이 발생하면
		if (lock == 1)				//게임(메인루프) 종료상태
			break;
	}
	endBlock();	//꾸미기 출력
	endGame();	//꾸미기 출력
	save();		//저장
}

void setBase()	//초기설정
{
	int height, width;	//for문 변수
	lock = 0;
	score = 0;

	for (height = 0; height < HEIGHT_FULL; height++)
	{
		for (width = 0; width < WIDTH_FULL; width++)
		{
			blocked[height][width].state = BLANK;		//상태 - 빈칸
			strcpy(blocked[height][width].design, BOX_NULL);	//모양
			if (height == HEIGHT_FULL - HEIGHT_LOW) blocked[height][width].state = BLOCK;	//가상의 밑바닥 설정
		}
	}
	draw();		//그리기
	scoring(0);
	nextBlock();//첫 블록
	newBlock();	//블록 생성
}

void draw()	//화면 자체를 재출력
{
	int height, width;	//for문 변수

	system("cls");	//화면을 지우기
	//디자인--------------------------------------------------------
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	printf("┌");
	for (width = 0; width < WIDTH_FULL; width++)
	{
		printf("─");
	}
	printf("┐");
	printf("\n");
	for (height = HEIGHT_IN; height < HEIGHT_FULL - 1; height++) //보이는 구간 출력
	{
		printf("│");
		for (width = 0; width < WIDTH_FULL; width++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blocked[height][width].color);
			printf("%s", blocked[height][width].design);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("│\n");
	}
	printf("└");
	for (width = 0; width < WIDTH_FULL; width++)
	{
		printf("─");
	}
	printf("┘");
	printf("\n");
	//디자인--------------------------------------------------------
}

void nextBlock()
{
	int height, width;	//for문 변수
	int design;			//모양을 선택할 정수 7가지
	COORD pos;
	srand((unsigned)time(NULL));	//랜덤을 위한 함수
	design = (rand() % 7);			//랜덤으로 생성한 수를 대입

	for (height = 0; height < BLOCK_SIZE; height++)	//세로4 블록
	{
		for (width = 0; width < BLOCK_SIZE; width++)//++)	//가로4 블록
		{
			next[height][width].point.Y = height + TOP_DESIGN;	//전체 좌표 - 세로
			next[height][width].point.X = (width + (WIDTH_FULL / 2) - 1) - 1;		//전체 좌표 - 가로(중심)
			next[height][width].state = BLANK;				//상태 - 블록
			strcpy(next[height][width].design, BOX_NULL);	//모양
		}
	}
	if (design == 0)	//직선
	{
		next[0][1].state = BLOCK; next[0][1].color = RED + BRIGHT;
		next[1][1].state = BLOCK; next[1][1].color = RED + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = RED + BRIGHT;
		next[3][1].state = BLOCK; next[3][1].color = RED + BRIGHT;
	}
	else if (design == 1)	//네모
	{
		next[1][1].state = BLOCK; next[1][1].color = YELLOW + BRIGHT;
		next[1][2].state = BLOCK; next[1][2].color = YELLOW + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = YELLOW + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = YELLOW + BRIGHT;
	}
	else if (design == 2)	//지그재그 1
	{
		next[1][1].state = BLOCK; next[1][1].color = BLUE + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = BLUE + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = BLUE + BRIGHT;
		next[3][2].state = BLOCK; next[3][2].color = BLUE + BRIGHT;
	}
	else if (design == 3)	//지그재그 2
	{
		next[1][2].state = BLOCK; next[1][2].color = PUPLE + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = PUPLE + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = PUPLE + BRIGHT;
		next[3][1].state = BLOCK; next[3][1].color = PUPLE + BRIGHT;
	}
	else if (design == 4)	//니은 1
	{
		next[1][1].state = BLOCK; next[1][1].color = GREEN + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = GREEN + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = GREEN + BRIGHT;
		next[2][3].state = BLOCK; next[2][3].color = GREEN + BRIGHT;
	}
	else if (design == 5)	//니은 2
	{
		next[1][3].state = BLOCK; next[1][3].color = BG + BRIGHT;
		next[2][3].state = BLOCK; next[2][3].color = BG + BRIGHT;
		next[2][2].state = BLOCK; next[2][2].color = BG + BRIGHT;
		next[2][1].state = BLOCK; next[2][1].color = BG + BRIGHT;
	}
	else if (design == 6)	//나머지
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
			if (next[height][width].state == BLOCK)		//4X4 배열중 블록이 있는칸
				strcpy(next[height][width].design, BOX);	//■문자를 설정
		}
	}
	//우측 공백에 다음 블록 출력
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

void newBlock()	//블록 생성
{
	int height, width;	//for문 변수

	for (height = 0; height < BLOCK_SIZE; height++)	//세로4 블록
	{
		for (width = 0; width < BLOCK_SIZE; width++)//++)	//가로4 블록
		{
			block_input[height][width].point.Y = next[height][width].point.Y;	//전체 좌표 - 세로
			block_input[height][width].point.X = next[height][width].point.X;	//전체 좌표 - 가로(중심)
			block_input[height][width].state = next[height][width].state;		//상태 - 블록
			block_input[height][width].color = next[height][width].color;		//색
			strcpy(block_input[height][width].design, next[height][width].design);	//모양
		}
	}
	topBlock();	//가장 최상층에 있는 블록 검사
	reBlock();	//첫 출력
	nextBlock();
}

void keypress()
{
	int ascii1 = _getch();	//키보드 입력값 꺼내기
	int ascii2;				//확장아스키코드 값
	int height, width;		//
	if (ascii1 == ASCII)		//확장아스키코드
	{
		ascii2 = _getch();	//키보드 입력값 꺼내기
		switch (ascii2)		//확장키값으로 스위치
		{
		case DOWN:
			if (block_input[BLOCK_SIZE - 1][0].point.Y < (HEIGHT_FULL))	//범위를 안벗어났으면
				moveBlock(ascii2);										//이동
			break;
		case LEFT:
			for (width = 0; width < BLOCK_SIZE; width++)
				for (height = 0; height < BLOCK_SIZE; height++)
					if (block_input[height][width].state == BLOCK)//블록상태 (가장 좌측블록)
						goto left;//이중 for문 종료
		left:
			if (block_input[height][width].point.X > 0)	//범위를 안벗어났으면
				moveBlock(ascii2);						//이동
			break;
		case RIGHT:
			for (width = BLOCK_SIZE - 1; width >= 0; width--)
				for (height = BLOCK_SIZE - 1; height >= 0; height--)
					if (block_input[height][width].state == BLOCK)//블록상태 (가장 우측블록)
						goto right;//이중 for문 종료
		right:
			if (block_input[height][width].point.X < (WIDTH_FULL - 1))	//범위를 안벗어났으면
				moveBlock(ascii2);										//이동
			break;
		default:
			break;
		}
	}
	else if (ascii1 == TURN_LEFT_Z)		//아스키코드 z가 입력되면
		rotateLeft();//좌회전
	else if (ascii1 == TURN_RIGHT_X)	//아스키코드 x가 입력되면
		rotateRight();//우회전
	else if (ascii1 == SPACE_BAR)		//스페이스바
		down();	//아래로
}

void down()
{
	int height, width;
	COORD pos;

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			if (block_input[height][width].state == BLOCK)	//블록상태의 좌표 - 이동 전
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//임시좌표 - 세로
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2;	//임시좌표 - 가로
				if (pos.Y < TOP_DESIGN) continue;	//미출력구간 처리
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//이전 블록 좌표
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);	//지우기
				printf("%s", block_input[height][width].design);	//출력
			}
		}
	}

	while (1)
	{
		if (buildChk(1))
		{
			build();	//쌓기
			newBlock(); //새 블록 생성
			break;
		}
		for (height = 0; height < BLOCK_SIZE; height++)
		{
			for (width = 0; width < BLOCK_SIZE; width++)
			{
				block_input[height][width].point.Y++;	//한칸씩 내리기
			}
		}
	}
}

int moveChk(int y, int x)	//블록이 움직일 수 있는지 체크
{
	int height, width;		//for변수
	int yy, xx;				//

	if (x == 0) return 0;	//좌우 이동이 아닌경우

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			yy = block_input[height][width].point.Y + y;//매개변수 임시좌표
			xx = block_input[height][width].point.X + x;//매개변수 임시좌표
			//이동할 곳에 블록이 있으면
			if (block_input[height][width].state == BLOCK && blocked[yy][xx].state != BLANK)
				return 1;	//1 반환 (종료)
		}
	}
	return 0;	//0 반환 속행
}

void moveBlock(int key)	//블록 이동
{
	int height, width;	//for문 변수
	int wayX = 0;		//가로축 값
	int wayY = 0;		//세로축 값
	COORD pos;			//인터페이스 여백

	if (key == DOWN) wayY = 1;			//하
	else if (key == LEFT) wayX = -1;		//좌
	else if (key == RIGHT) wayX = 1;	//우
	else if (key == UP)	wayY = -1;		//상 삭제

	if (moveChk(wayY, wayX)) return;	//좌우로 움직일수 있는지 체크

	if (buildChk(wayY))	//쌓일상태인지 확인
	{
		build();	//쌓기
		newBlock();	//새블록 생성
		return;		//종료
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			if (block_input[height][width].point.Y < HEIGHT_IN) continue;
			if (block_input[height][width].state == BLOCK)	//블록상태의 좌표 - 이동 전
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//임시좌표 - 세로
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2;	//임시좌표 - 가로
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//이전 블록 좌표
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);	//지우기
				printf("%s", block_input[height][width].design);	//출력
			}
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			block_input[height][width].point.Y += wayY;	//상하 좌표 변경
			block_input[height][width].point.X += wayX;	//좌우 좌표 변경
			if (block_input[height][width].point.Y < HEIGHT_IN) continue;
			if (block_input[height][width].state == BLOCK)	//블록상태의 좌표 - 이동할 좌표
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//임시좌표 - 세로
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2;	//임시좌표 - 가로
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//이동할 블록 좌표
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block_input[height][width].color);//출력할 색상
				printf("%s", block_input[height][width].design);	//출력
			}
		}
	}
}

void reBlock()
{
	int height, width;	//for문 변수
	COORD pos;

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			if (block_input[height][width].state == BLOCK)	//블록 자리
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//좌표 설정
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2; //좌표 설정
				if (pos.Y < TOP_DESIGN) continue;	//미출력 구간이면 블록 한칸 건너뛰기
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//출력 좌표
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block_input[height][width].color);//색상 설정
				printf("%s", block_input[height][width].design);				//출력
			}
		}
	}
}

void rotateLeft()	//좌회전
{
	int height, width;	//세로 가로
	int turn_height, turn_width;	//회전 설정용
	COORD pos;						//회전 설정용
	block temp[BLOCK_SIZE][BLOCK_SIZE];	//임시 저장

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			turn_height = BLOCK_SIZE - width - 1;	//회전 후 배열좌표 - 세로
			turn_width = height;					//회전 후 배열좌표 - 가로
			temp[height][width].point = block_input[height][width].point;			//좌표값은 유지
			temp[turn_height][turn_width].state = block_input[height][width].state;	//회전 후 임시배열에 대입
			temp[turn_height][turn_width].color = block_input[height][width].color;	//회전 후 임시배열에 대입
			strcpy(temp[turn_height][turn_width].design, block_input[height][width].design);	//문자열은 따로 옮기기
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			pos.Y = temp[height][width].point.Y;	//임시 좌표
			pos.X = temp[height][width].point.X;	//임시 좌표
			if (temp[height][width].state == BLOCK && blocked[pos.Y][pos.X].state != BLANK)	//회전할 곳이 빈칸이 아니면 종료
				return;
			else if (!(pos.X >= 0 && pos.X < WIDTH_FULL))	//범위를 벗어나면 종료
				return;
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			block_input[height][width].point = temp[height][width].point;			//실제 블록에 적용
			block_input[height][width].state = temp[height][width].state;			//실제 블록에 적용
			block_input[height][width].color = temp[height][width].color;			//실제 블록에 적용
			strcpy(block_input[height][width].design, temp[height][width].design);	//실제 블록에 적용
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			pos.Y = block_input[height][width].point.Y;	//배열값에 들어갈 자리 줄이기
			pos.X = block_input[height][width].point.X;	//배열값에 들어갈 자리 줄이기
			//빈칸이면 지우기
			if (blocked[pos.Y][pos.X].state == BLANK)
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//임시 좌표 - 세로
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2;	//임시 좌표 - 가로
				if (pos.Y < TOP_DESIGN) continue;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//출력할 좌표로 이동
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);//지우기
				printf("%s", block_input[height][width].design);				//지우기
			}
		}
	}
	reBlock();	//회전한 블록 출력
}

void rotateRight()	//우회전
{
	int height, width;	//세로 가로
	int turn_height, turn_width;	//회전 설정용
	COORD pos;						//회전 설정용
	block temp[BLOCK_SIZE][BLOCK_SIZE];	//임시 저장

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			turn_height = width;					//회전 후 배열좌표 - 세로
			turn_width = BLOCK_SIZE - height - 1;	//회전 후 배열좌표 - 가로
			temp[height][width].point = block_input[height][width].point;			//좌표값은 유지
			temp[turn_height][turn_width].state = block_input[height][width].state;	//회전 후 임시배열에 대입
			temp[turn_height][turn_width].color = block_input[height][width].color;	//회전 후 임시배열에 대입
			strcpy(temp[turn_height][turn_width].design, block_input[height][width].design);	//문자열은 따로 옮기기
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			pos.Y = temp[height][width].point.Y;	//임시 좌표
			pos.X = temp[height][width].point.X;	//임시 좌표
			if (temp[height][width].state == BLOCK && blocked[pos.Y][pos.X].state != BLANK)	//회전할 곳이 빈칸이 아니면 종료
				return;
			else if (!(pos.X >= 0 && pos.X < WIDTH_FULL))	//범위를 벗어나면 종료
				return;
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			pos.Y = block_input[height][width].point.Y;	//배열값에 들어갈 자리 줄이기
			pos.X = block_input[height][width].point.X;	//배열값에 들어갈 자리 줄이기
			//빈칸이면 지우기
			if (blocked[pos.Y][pos.X].state == BLANK)
			{
				pos.Y = block_input[height][width].point.Y - HEIGHT_IN + TOP_DESIGN;	//임시 좌표 - 세로
				pos.X = (block_input[height][width].point.X + LEFT_DESIGN) * 2;	//임시 좌표 - 가로
				if (pos.Y < TOP_DESIGN) continue;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//출력할 좌표로 이동
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);//지우기
				printf("%s", block_input[height][width].design);				//지우기
			}
		}
	}

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			block_input[height][width].point = temp[height][width].point;			//실제 블록에 적용
			block_input[height][width].state = temp[height][width].state;			//실제 블록에 적용
			block_input[height][width].color = temp[height][width].color;			//실제 블록에 적용
			strcpy(block_input[height][width].design, temp[height][width].design);	//실제 블록에 적용
		}
	}
	reBlock();	//회전한 블록 출력
}

void topBlock()	//최상층의 블록 검사
{
	int height, width;	//가로 세로
	int flag;			//연속된 블록 확인

	for (width = 0; width < WIDTH_FULL; width++)
	{
		flag = 0;	//초기화
		for (height = 0; height < HEIGHT_FULL; height++)
		{
			if (blocked[height][width].state == TOP)	//이전 TOP을 초기화
				blocked[height][width].state = BLOCK;	//일반 블록상태
			if (flag == 1 && blocked[height][width].state == BLANK)	//flag=0 일때, 빈칸이 검사되면
				flag = 0;	//초기화
			if (blocked[height][width].state == BLOCK && flag == 0)	//flag=0 일때, 블록이 검사되면
			{
				blocked[height][width].state = TOP;	//TOP상태로 세팅
				flag = 1;	//flag 바꾸기
			}
			else if (blocked[height][width].state != BLANK && flag == 1)	//flag=1 이고 빈칸이 아니면
				blocked[height][width].state = BLOCK;	//블록상태
		}
	}
}

int buildChk(int y)	//쌓을수 있는지 검사
{
	int height, width;	//가로 세로
	int yy, xx;			//임시 좌표

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			yy = block_input[height][width].point.Y + y;	//한칸 아래 좌표
			xx = block_input[height][width].point.X;		//수평 좌표
			//쌓을 블록과 쌓인 블록 좌표의 상태값의 합이 BUILD 이면 (BLOCK + TOP)
			if (block_input[height][width].state + blocked[yy][xx].state == BUILD)
				return 1;	//1반환 (쌓기)
		}
	}
	return 0;
}

void build()
{
	int height, width;	//for문 변수
	int yy, xx;			//임시변수 (한문장의 길이 줄이기)
	COORD pos;

	for (height = 0; height < BLOCK_SIZE; height++)
	{
		for (width = 0; width < BLOCK_SIZE; width++)
		{
			if (block_input[height][width].state == BLOCK)	//블록이 있는 칸이면
			{
				yy = block_input[height][width].point.Y;	//매개변수 임시좌표
				xx = block_input[height][width].point.X;	//매개변수 임시좌표

				if (block_input[height][width].state == BLANK) continue;
				if (blocked[yy][xx].state != BLANK) continue;
				pos.Y = yy - HEIGHT_IN + TOP_DESIGN;	//임시좌표 - 세로
				pos.X = (xx + LEFT_DESIGN) * 2;	//임시좌표 - 가로
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//이동할 블록 좌표
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block_input[height][width].color);//출력할 색상
				blocked[yy][xx].state = BLOCK;				//쌓여있는 블록배열에 채우기
				blocked[yy][xx].color = block_input[height][width].color;	//색상
				strcpy(blocked[yy][xx].design, BOX);		//모양 복사
				printf("%s", blocked[yy][xx].design);
			}
		}
	}
	fail();		//패배 확인
	clear();	//완성된 줄 지우기
}

void scoring(int num)	//점수 매기기 & 출력
{
	COORD pos;
	score = score + num;	//점수 추가

	//score 표시 출력
	pos.Y = 7;
	pos.X = (LEFT_DESIGN + WIDTH_FULL + 5) * 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE + BRIGHT);
	printf("SCORE");
	//실제 점수 출력
	pos.Y = 8;
	pos.X = (LEFT_DESIGN + WIDTH_FULL + 5) * 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE + BRIGHT);
	printf(" %d", score);
}

void clearLine(int line)	//지우고 내리기
{
	int height, width;	//가로 세로
	for (height = line; height > HEIGHT_IN; height--)
	{
		for (width = 0; width < WIDTH_FULL; width++)
		{
			blocked[height][width] = blocked[height - 1][width];	//지울 줄 위를 한칸씩 내리기
			strcpy(blocked[height][width].design, blocked[height - 1][width].design);
		}
	}
	system("cls");	//화면 지우기
	draw();			//전체 재출력
	scoring(100);
}

void clear()
{
	int height, width;	//가로 세로
	int delcnt;			//지우기 카운터 (= 가로 길이)

	for (height = HEIGHT_FULL - HEIGHT_LOW - 1; height > HEIGHT_IN; height--)	//아래에서 부터
	{
		delcnt = 0;	//초기화
		for (width = 0; width < WIDTH_FULL; width++)	//가로 한줄
		{
			if (blocked[height][width].state != BLANK)	//빈칸이 아니면
				delcnt++;	//카운트 증가
		}
		if (delcnt == WIDTH_FULL)	//카운트가 가로길이와 같아지면
		{
			clearLine(height);	//지우기 실행
			height++;			//내린 줄로 이동
		}
	}
}

void fail()	//패배상태
{
	int width;	//가로

	for (width = HEIGHT_IN; width < WIDTH_FULL; width++)	//데드라인 한줄
	{
		if (blocked[HEIGHT_IN][width].state != BLANK)		//빈칸이 아닌게 하나라도 있으면
			lock = 1;	//종료 상태
	}
}

void endGame()	//FAIL 출력
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
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);				printf("■■■■■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■■■■■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■");

		Sleep(sleep);
		pos.Y = 4;
		pos.X = 8;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (GREEN + color) % 8 + BRIGHT);
		if (color == 7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK + BRIGHT);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);				printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■ ■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■■■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■   ■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■    ■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■     ■");

		Sleep(sleep);
		pos.Y = 8;
		pos.X = 16;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (BG + color) % 8 + BRIGHT);
		if (color == 7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK + BRIGHT);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);				printf("■■■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("  ■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("  ■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("  ■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("  ■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("  ■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■■■");

		Sleep(sleep);
		pos.Y = 12;
		pos.X = 24;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (RED + color) % 8 + BRIGHT);
		if (color == 7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK + BRIGHT);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);				printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■");
		pos.Y++;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	printf("■■■■■");
	}
}

void endBlock()	//패배효과(꾸밈) 출력
{
	int height, width;	//가로 세로
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
	savedata ranking[11];	//저장할 데이터 배열 10명 + 이번에 저장 비교할 여분 1명
	savedata temp;			//자리 교환용
	int i, j;				//반복문
	int length;				//길이(처음 저장시 1명, 2명... 이기때문에)
	system("cls");			//화면정리

	fp = fopen("F:\\TETRIS.txt", "r");	//읽기	//F:\TETRIS.txt 파일 읽기형식
	if (fp == NULL)	// 열기실패
	{
		printf("파일 열기 실패\n");
		return;
	}
	else   //열기 성공
	{
		for (i = 1; i < 11; i++)
		{
			fscanf(fp, "%d", &ranking[i].rank);	//순위
			fscanf(fp, "%s", &ranking[i].name);	//이름
			fscanf(fp, "%d", &ranking[i].score);//점수
			fscanf(fp, "");
			if (feof(fp) != 0) break;			//읽을것이 없으면 반복종료
		}
		fclose(fp);	//읽기형식 닫기
	}
	length = i;	//읽어온 플레이어 자료 수

	printf("이름 입력 : ");
	scanf("%s", &ranking[0].name);
	ranking[0].rank = 0;
	ranking[0].score = score;

	for (i = 0; i < length; i++)	//정렬
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
		ranking[i].rank = i + 1;	//정렬된 자료에 순위 매기기
	}
	//1~10위 출력
	system("cls");
	printf("rank\t name\t score\n");
	for (i = 0; i < length; i++)
	{
		printf("%d\t ", ranking[i].rank);
		printf("%s\t ", ranking[i].name);
		printf("%d\n", ranking[i].score);
	}

	fp = fopen("F:\\TETRIS.txt", "w");	//쓰기형식
	if (fp == NULL)
	{
		printf("파일 열기 실패\n");
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