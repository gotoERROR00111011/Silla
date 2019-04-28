#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define BOARD 8
#define BLANK ' '
#define INPUT '.'
#define WHITE 'O'
#define BLACK 'X'
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13

void set();
void marking();
int chkReverse();
void draw();
void input_key();
void input_u();
void input_c();
void reverse();
void chturn();
int chk_end();
void victory();
void save();
void load();

typedef struct keyboard
{
	int row;
	int col;
}key;

char othello[BOARD][BOARD];
int score[BOARD][BOARD];
char turn;
key k;

void main()
{
	set();
	while (1)
	{
		if (!chkReverse()) break;
		marking();
		draw();
		if (turn == WHITE) //input_u();
			input_key();
		else input_c();
		if (chk_end()) break;
		chturn();
	}
	victory();
}

void set()
{
	int i, j;
	turn = WHITE;
	for (i = 0; i < BOARD; i++)
	{
		for (j = 0; j < BOARD; j++)
		{
			othello[i][j] = BLANK;
		}
	}
	othello[3][3] = WHITE;
	othello[3][4] = BLACK;
	othello[4][3] = BLACK;
	othello[4][4] = WHITE;
	k.row = BOARD / 2;
	k.col = BOARD / 2;
}

void marking()
{
	int i, j;
	int h, w;
	int cnt;
	char player2;

	if (turn == WHITE) player2 = BLACK;
	else player2 = WHITE;

	for (i = 0; i < BOARD; i++)
	{
		for (j = 0; j < BOARD; j++)
		{
			score[i][j] = 0;
		}
	}

	for (i = 0; i < BOARD; i++)
	{
		for (j = 0; j < BOARD; j++)
		{
			if (othello[i][j] == '.')
			{
				//상
				h = i - 1; w = j; cnt = 0;
				while (othello[h][w] == player2)
				{
					h--;
					cnt++;
				}
				if (othello[h][w] == turn) score[i][j] += cnt;
				//하
				h = i + 1; w = j; cnt = 0;
				while (othello[h][w] == player2)
				{
					h++;
					cnt++;
				}
				if (othello[h][w] == turn) score[i][j] += cnt;
				//좌
				h = i; w = j - 1; cnt = 0;
				while (othello[h][w] == player2)
				{
					w--;
					cnt++;
				}
				if (othello[h][w] == turn) score[i][j] += cnt;
				//우
				h = i; w = j + 1; cnt = 0;
				while (othello[h][w] == player2)
				{
					w++;
					cnt++;
				}
				if (othello[h][w] == turn) score[i][j] += cnt;
				//좌상
				h = i - 1; w = j - 1; cnt = 0;
				while (othello[h][w] == player2)
				{
					h--; w--;
					cnt++;
				}
				if (othello[h][w] == turn) score[i][j] += cnt;
				//우하
				h = i + 1; w = j + 1; cnt = 0;
				while (othello[h][w] == player2)
				{
					h++; w++;
					cnt++;
				}
				if (othello[h][w] == turn) score[i][j] += cnt;
				//좌하
				h = i + 1; w = j - 1; cnt = 0;
				while (othello[h][w] == player2)
				{
					h++; w--;
					cnt++;
				}
				if (othello[h][w] == turn) score[i][j] += cnt;
				//우상
				h = i - 1; w = j + 1; cnt = 0;
				while (othello[h][w] == player2)
				{
					h--; w++;
					cnt++;
				}
				if (othello[h][w] == turn) score[i][j] += cnt;
			}
		}
	}
}

int chkReverse()
{
	int board_h, board_w;
	int h, w;
	int chk = 0;
	int rev = 0;
	char player2;

	if (turn == WHITE) player2 = BLACK;
	else player2 = WHITE;
	
	for (h = 0; h < BOARD; h++)
	{
		for (w = 0; w < BOARD; w++)
		{
			if (othello[h][w] == INPUT) othello[h][w] = BLANK;
		}
	}

	for (board_h = 0; board_h < BOARD; board_h++)
	{
		for (board_w = 0; board_w < BOARD; board_w++)
		{
			if (othello[board_h][board_w] == BLANK)
			{
				h = board_h + 1;
				while (h < BOARD && othello[h][board_w] == player2)//하단
				{
					h++;
					if (othello[h][board_w] == turn && h != board_h + 1) chk = 1;
				}
				w = board_w + 1;
				while (w < BOARD && othello[board_h][w] == player2)//우측
				{
					w++;
					if (othello[board_h][w] == turn && w != board_w + 1) chk = 1;
				}
				h = board_h - 1;
				while (h >= 0 && othello[h][board_w] == player2)//상단
				{
					h--;
					if (othello[h][board_w] == turn && h != board_h - 1) chk = 1;
				}
				w = board_w - 1;
				while (w >= 0 && othello[board_h][w] == player2)//좌측
				{
					w--;
					if (othello[board_h][w] == turn && w != board_w - 1) chk = 1;
				}
				h = board_h + 1; w = board_w + 1;
				while (h < BOARD && w < BOARD && othello[h][w] == player2)//우측하단
				{
					h++; w++;
					if (othello[h][w] == turn && h != h + 1 && w != w + 1) chk = 1;
				}
				h = board_h - 1; w = board_w + 1;
				while (h >= 0 && w < BOARD && othello[h][w] == player2)//우측상단
				{
					h--; w++;
					if (othello[h][w] == turn && h != h - 1 && w != w + 1) chk = 1;
				}
				h = board_h + 1; w = board_w - 1;
				while (h < BOARD && w >= 0 && othello[h][w] == player2)//좌측하단
				{
					h++; w--;
					if (othello[h][w] == turn && h != h + 1 && w != w - 1) chk = 1;
				}
				h = board_h - 1; w = board_w - 1;
				while (h >= 0 && w >= 0 && othello[h][w] == player2)//좌측상단
				{
					h--; w--;
					if (othello[h][w] == turn && h != h - 1 && w != w - 1) chk = 1;
				}
			}
			if (chk == 1)
			{
				othello[board_h][board_w] = INPUT;
				chk = 0;
				rev = 1;
			}
		}
	}
	return rev;
}

void draw()
{
	int i, j;

	printf("  ");
	for (i = 0; i < BOARD; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 0; i < BOARD; i++)
	{
		printf("%d", i);
		for (j = 0; j < BOARD; j++)
		{
			if (i == k.row && j == k.col)
			{
				printf("◇");
				continue;
			}
			printf(" %c", othello[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void input_key()
{
	char c;
	while (1)
	{
		if (_kbhit()) //key press
		{
			system("cls");
			c = _getch();
			switch (c)
			{
			case UP:
				k.row--;
				break;
			case DOWN:
				k.row++;
				break;
			case LEFT:
				k.col--;
				break;
			case RIGHT:
				k.col++;
				break;
			case ENTER:
				if (othello[k.row][k.col] == '.')
				{
					othello[k.row][k.col] = turn;
					reverse(k.row, k.col);
					return;
				}
				break;
			default:
				break;
			}
			if (k.row < 0) k.row = 0;
			else if (k.row >= BOARD) k.row = BOARD - 1;
			if (k.col < 0) k.col = 0;
			else if (k.col >= BOARD) k.col = BOARD - 1;
			draw();
		}
	}
}

void input_u()
{
	int input;
	int h, w;
	while (1)
	{
		printf("%c의 차례", turn);
		scanf("%d", &input);
		if (input == -1)
		{
			load();
			draw();
			continue;
		}
		h = input / 10;
		w = input % 10;
		if (othello[h][w] == INPUT)
		{
			save();
			break;
		}
		else printf("둘 수 없는 곳 입니다.(재입력)\n");
	}
	othello[h][w] = turn;
	reverse(h, w);
}

void input_c()
{
	int h, w;
	int max = 0;

	for (h = 0; h < BOARD; h++)
	{
		for (w = 0; w < BOARD; w++)
		{
			if (othello[h][w] == '.')
			{
				if (score[h][w] > max) 
					max = score[h][w];
			}
		}
	}

	for (h = 0; h < BOARD; h++)
	{
		for (w = 0; w < BOARD; w++)
		{
			if (othello[h][w] == '.')
			{
				if (score[h][w] == max)
				{
					othello[h][w] = turn;
					reverse(h, w);
					return;
				}
			}
		}
	}
}

void reverse(int input_h, int input_w)
{
	int h, w;
	int chk = 0;
	char player2;

	if (turn == WHITE) player2 = BLACK;
	else player2 = WHITE;

	//---------------------------하단-------------------------------
	h = input_h + 1;
	while (h < BOARD && othello[h][input_w] == player2)
	{
		h++;
		if (othello[h][input_w] == turn && h != input_h + 1) chk = 1;
	}
	while (h != input_h && chk == 1)//뒤집기
	{
		h--;
		othello[h][input_w] = turn;
	}
	chk = 0;
	//---------------------------우측-------------------------------
	w = input_w + 1;
	while (w < BOARD && othello[input_h][w] == player2)
	{
		w++;
		if (othello[input_h][w] == turn && w != input_w + 1) chk = 1;
	}
	while (w != input_w && chk == 1)//뒤집기
	{
		w--;
		othello[input_h][w] = turn;
	}
	chk = 0;
	//---------------------------상단-------------------------------
	h = input_h - 1;
	while (h >= 0 && othello[h][input_w] == player2)
	{
		h--;
		if (othello[h][input_w] == turn && h != input_h - 1) chk = 1;
	}
	while (h != input_h && chk == 1)//뒤집기
	{
		h++;
		othello[h][input_w] = turn;
	}
	chk = 0;
	//---------------------------좌측-------------------------------
	w = input_w - 1;
	while (w >= 0 && othello[input_h][w] == player2)
	{
		w--;
		if (othello[input_h][w] == turn && w != input_w - 1) chk = 1;
	}
	while (w != input_w && chk == 1)//뒤집기
	{
		w++;
		othello[input_h][w] = turn;
	}
	chk = 0;
	//---------------------------우측하단-------------------------------
	h = input_h + 1; w = input_w + 1;
	while (h < BOARD && w < BOARD && othello[h][w] == player2)
	{
		h++; w++;
		if (othello[h][w] == turn && h != input_h + 1 && w != input_w + 1) chk = 1;
	}
	while (h != input_h && w != input_w && chk == 1)//뒤집기
	{
		h--; w--;
		othello[h][w] = turn;
	}
	chk = 0;
	//---------------------------우측상단-------------------------------
	h = input_h - 1; w = input_w + 1;
	while (h >= 0 && w < BOARD && othello[h][w] == player2)
	{
		h--; w++;
		if (othello[h][w] == turn && h != input_h - 1 && w != input_w + 1) chk = 1;
	}
	while (h != input_h && w != input_w && chk == 1)//뒤집기
	{
		h++; w--;
		othello[h][w] = turn;
	}
	chk = 0;
	//---------------------------좌측하단-------------------------------
	h = input_h + 1; w = input_w - 1;
	while (h < BOARD && w >= 0 && othello[h][w] == player2)
	{
		h++; w--;
		if (othello[h][w] == turn && h != input_h + 1 && w != input_w - 1) chk = 1;
	}
	while (h != input_h && w != input_w && chk == 1)//뒤집기
	{
		h--; w++;
		othello[h][w] = turn;
	}
	chk = 0;
	//---------------------------좌측상단-------------------------------
	h = input_h - 1; w = input_w - 1;
	while (h >= 0 && w >= 0 && othello[h][w] == player2)
	{
		h--; w--;
		if (othello[h][w] == turn && h != input_h - 1 && w != input_w - 1) chk = 1;
	}
	while (h != input_h && w != input_w && chk == 1)//뒤집기
	{
		h++; w++;
		othello[h][w] = turn;
	}
	printf("\n");
}

int chk_end()
{
	int i, j;
	int flag = 0;
	int count = 0;
	for (i = 0; i < BOARD; i++)
	{
		for (j = 0; j < BOARD; j++)
		{
			if (othello[i][j] == BLANK)		
				count++;
			else if (othello[i][j] == turn)
				count++;
			if (othello[i][j] == BLANK)		
				flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("빈칸 없음\n");
		return 1;
	}
	else if (count == BOARD*BOARD)
	{
		printf("%c가 모두 뒤집음\n", turn);
		return 1;
	}
	else
		return 0;
}

void chturn()
{
	if (turn == WHITE)
		turn = BLACK;
	else
		turn = WHITE;
}

void victory()
{
	int i, j;
	int osum = 0;
	int xsum = 0;

	for (i = 0; i < BOARD; i++)
	{
		for (j = 0; j < BOARD; j++)
		{
			if (othello[i][j] == WHITE)
				osum++;
			else if (othello[i][j] == BLACK)
				xsum++;
		}
	}
	if (osum > xsum) printf("O의 승리\n");
	else if (xsum > osum) printf("X의 승리");
	else printf("무승부\n");
}

void save()
{
	FILE *fp;
	int i, j;

	fp = fopen("C:\\Othello.txt", "w");

	if (fp == NULL)
	{
		printf("파일 열기 실패\n");
		return;
	}
	else
	{
		fprintf(fp, "%c", turn);
		for (i = 0; i < BOARD; i++)
		{
			for (j = 0; j < BOARD; j++)
			{
				fprintf(fp, "%c", othello[i][j]);
			}
		}
		fclose(fp);
	}
}

void load()
{
	FILE *fp;
	int i, j;

	fp = fopen("C:\\Othello.txt", "r");

	if (fp == NULL)
	{
		printf("파일 열기 실패\n");
		return;
	}
	else
	{
		fscanf(fp, "%c", &turn);
		for (i = 0; i < BOARD; i++)
		{
			for (j = 0; j < BOARD; j++)
			{
				fscanf(fp, "%c", &othello[i][j]);
			}
		}
		fclose(fp);
	}
}