#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <alloc.h>
#include <ctype.h>
#include <math.h>

extern void far * ptr;
extern unsigned size;
/*----------------------*/
int menu(void);
void make_bar(void);
int getkey(void);
void highlight(int num);
void lowlight(int num);
void gotolr(int *i, int key);
void make_down(int i);
void clean_down(int i);
void pull_up(int *i, int *j, int key);
int gotodu(int *i, int *j, int key);
void highdown(int i, int j, int flag);
int select_func(int i, int j);
void store_s(int x1, int y1, int x2, int y2);
void restore_s(int x, int y);
/*-----------------------------*/

int menu(void)
{
	register int i, j, ch;
	i = j = ch = 1;
	int temp;
	make_bar();
	for (;;)
	{
		ch = getkey();
		for (; ch != 13;)
		{
			gotolr(&i, ch);
			ch = getkey();
		}

		make_down(i);
		ch = getkey();
		for (;
			(ch == 77) || (ch == 75);)
		{
			pull_up(&i, &j, ch);
			ch = getkey();
		}

		if (ch == 27) gotodu(&i, &j, ch);
		else
		{
			temp = gotodu(&i, &j, ch);

			if (temp != 0) return temp;
			do {
				ch = getkey();
				temp = gotodu(&i, &j, ch);
				if (temp != 0) return temp;
				pull_up(&i, &j, ch);
			} while (ch != 27);
		}
	}
}

/********************/
void make_bar(void)
{
	char *m_bar[] = { " PUBLIC     ",
		" L PARAM.   ",
		" Lmin,max   ",
		" Z INPUT    ",
		" 1  STUB    ",
		" 2  STUB    ",
		" 3  STUB    " };
	char *m_ba[] = { "P",
		"L",
		"L",
		"Z",
		"1",
		"2",
		"3" };

	register int i;
	void *buf;
	setcolor(MAGENTA);
	setfillstyle(SOLID_FILL, getmaxcolor());
	bar(2, 2, getmaxx() - 2, 24);
	bar(2, 458, getmaxx() - 2, 478);
	setcolor(BLACK);
	rectangle(1, 459, getmaxx() - 3, 477);
	line(100, 458, 100, 478);
	setcolor(RED);
	outtextxy(20, 464, "COMMENT");
	setcolor(BLACK);
	outtextxy(120, 464, "IMPEDANCE TRANSFORM AND MATCHING BY SMIT CHART");
	setcolor(DARKGRAY);
	for (i = 0; i < 7; i++) outtextxy(10 + i *79, 10, m_bar[i]);
	setcolor(RED);
	for (i = 0; i < 7; i++) outtextxy(19 + i *79, 10, m_ba[i]);
	setcolor(DARKGRAY);
	for (i = 0; i < 7; i++)
	{
		rectangle(4 + i *79, 4, 4 + (i + 1) *79, 23);
		rectangle(3 + i *79, 3, 3 + (i + 1) *79, 24);
	}
}

/***********************/
int getkey(void)
{
	register int x;
	union REGS r;
	union scan
	{
		int c;
		char ch[2];
	}

	sc;
	r.h.ah = 0;
	sc.c = int86(0x16, &r, &r);
	if (sc.ch[0] == 0)
		return sc.ch[1];
	x = sc.ch[0];
	x >> 8;
	return x;
}

/**********************/
void highlight(int num)
{
	register int temp = num;
	setcolor(BLUE);
	rectangle(5 + (temp - 1) *79, 5, 4 + temp *79, 21);
	rectangle(3 + (temp - 1) *79, 3, 2 + temp *79, 23);
	setcolor(GREEN);
	rectangle(6 + (temp - 1) *79, 6, 5 + temp *79, 20);
	rectangle(4 + (temp - 1) *79, 4, 3 + temp *79, 22);

}

/****************************/
void lowlight(int num)
{
	register int temp = num;
	setcolor(DARKGRAY);
	rectangle(5 + (temp - 1) *79, 5, 4 + temp *79, 21);
	rectangle(3 + (temp - 1) *79, 3, 2 + temp *79, 23);
	setcolor(WHITE);
	rectangle(6 + (temp - 1) *79, 6, 5 + temp *79, 20);
	rectangle(4 + (temp - 1) *79, 4, 3 + temp *79, 22);

}

/*******************/
void gotolr(int *i, int key)
{
	register int t;
	t = *i;
	switch (key)

	{
		case 25:
			t = 1;
			highlight(t);
			break;
		case 38:
			t = 2;
			highlight(t);
			break;
		case 44:
			t = 4;
			highlight(t);
			break;
		case 120:
			t = 5;
			highlight(t);
			break;
		case 121:
			t = 6;
			highlight(t);
			break;
		case 122:
			t = 7;
			highlight(t);
			break;
		case 27:
			lowlight(t);
			break;
		case 77:
			if (t < 7)
			{
				t = t + 1;
				lowlight(t - 1);
				highlight(t);
			}

			break;
		case 75:
			if (t > 1)
			{
				t = t - 1;
				lowlight(t + 1);
				highlight(t);
			}

			break;
		case 13:
			break;
	}

	*i = t;
}

/***************************/
void make_down(int i)
{
	char *abar[] = { " SMIT CHART ",
		"   DEMO     ",
		"   EXIT     " };
	char *bbar[] = { "  LOAD IMP. ",
		"   VSWR     ",
		"   GAMA     " };
	char *cbar[] = { "  LOAD IMP. ",
		" Z max,min  ",
		" V max,min  " };
	char *dbar[] = { "  LOAD IMP. ",
		"  LOAD LINE ",
		"  Z INPUT   " };
	char *ebar[] = { "  LOAD IMP. ",
		"   Ls &Lt  ",
		" SCH. GRAPH " };
	char *fbar[] = { "  LOAD IMP. ",
		" Ld,Lt, Lt1 ",
		" SCH. GRAPH " };
	char *gbar[] = { "  LOAD IMP. ",
		" Ld,t,t1,t2 ",
		" SCH. GRAPH " };
	register int j;
	setfillstyle(SOLID_FILL, getmaxcolor());
	setcolor(DARKGRAY);
	switch (i)
	{
		case 1:
			store_s(4, 25, 120, 104);
			bar(4, 25, 120, 104);
			for (j = 1; j <= 3; j++)
			{
				outtextxy(17, 10 + j *25, abar[j - 1]);
				rectangle(6, 2 + j *25, 118, 27 + j *25);
				rectangle(7, 3 + j *25, 117, 26 + j *25);
			}

			break;
		case 2:
			store_s(74, 25, 190, 104);
			bar(74, 25, 190, 104);
			for (j = 1; j <= 3; j++)
			{
				outtextxy(90, 10 + j *25, bbar[j - 1]);
				rectangle(76, 2 + j *25, 188, 27 + j *25);
				rectangle(77, 3 + j *25, 187, 26 + j *25);
			}

			break;
		case 3:
			store_s(156, 25, 269, 104);
			bar(156, 25, 269, 104);
			for (j = 1; j <= 3; j++)
			{
				outtextxy(169, 10 + j *25, cbar[j - 1]);
				rectangle(155, 2 + j *25, 267, 27 + j *25);
				rectangle(156, 3 + j *25, 266, 26 + j *25);
			}

			break;
		case 4:
			store_s(235, 25, 348, 104);
			bar(235, 25, 348, 104);
			for (j = 1; j <= 3; j++)
			{
				outtextxy(248, 10 + j *25, dbar[j - 1]);
				rectangle(234, 2 + j *25, 346, 27 + j *25);
				rectangle(235, 3 + j *25, 345, 26 + j *25);
			}

			break;
		case 5:
			store_s(314, 25, 427, 104);
			bar(314, 25, 427, 104);
			for (j = 1; j <= 3; j++)
			{
				outtextxy(327, 10 + j *25, ebar[j - 1]);
				rectangle(313, 2 + j *25, 425, 27 + j *25);
				rectangle(314, 3 + j *25, 424, 26 + j *25);
			}

			break;
		case 6:
			store_s(393, 25, 506, 104);
			bar(393, 25, 506, 104);
			for (j = 1; j <= 3; j++)
			{
				outtextxy(406, 10 + j *25, fbar[j - 1]);
				rectangle(392, 2 + j *25, 504, 27 + j *25);
				rectangle(393, 3 + j *25, 503, 26 + j *25);
			}

			break;
		case 7:
			store_s(472, 25, 585, 104);
			bar(472, 25, 585, 104);
			for (j = 1; j <= 3; j++)
			{
				outtextxy(485, 10 + j *25, gbar[j - 1]);
				rectangle(471, 2 + j *25, 583, 27 + j *25);
				rectangle(472, 3 + j *25, 582, 26 + j *25);
			}

			break;
	}

	highlight(i);
	highdown(i, 1, 1);
}

/***************************/
void clean_down(int i)
{
	switch (i)
	{
		case 1:
			restore_s(4, 25);
			break;
		case 2:
			restore_s(74, 25);
			break;
		case 3:
			restore_s(156, 25);
			break;
		case 4:
			restore_s(235, 25);
			break;
		case 5:
			restore_s(314, 25);
			break;
		case 6:
			restore_s(393, 25);
			break;
		case 7:
			restore_s(472, 25);
			break;
	}
}

/***************************/
void pull_up(int *i, int *j, int key)
{
	switch (key)
	{
		case 77:
			if (*i < 7)
			{
				*i = *i + 1;
				clean_down(*i - 1);
				lowlight(*i - 1);
				highlight(*i);
				make_down(*i);
				*j = 1;
			}

			break;
		case 75:
			if (*i > 1)
			{
				*i = *i - 1;
				clean_down(*i + 1);
				lowlight(*i + 1);
				highlight(*i);
				make_down(*i);
				*j = 1;
			}

			break;
	}
}

/****************************/
int gotodu(int *i, int *j, int key)
{
	switch (key)
	{
		case 27:
			clean_down(*i);
			break;
		case 13:
			return select_func(*i, *j);
		case 80:
			if (*j < 3)
			{
				*j = *j + 1;
				highdown(*i, *j - 1, 0);
				highdown(*i, *j, 1);
			}

			break;
		case 72:
			if (*j > 1)
			{
				*j = *j - 1;
				highdown(*i, *j + 1, 0);
				highdown(*i, *j, 1);
			}

			break;
	}

	return 0;
}

/*********************************/
void highdown(int i, int j, int flag)
{
	register int ip, jp;
	ip = i;
	jp = j;
	if (flag == 0) setcolor(WHITE);
	else setcolor(GREEN);
	switch (ip)
	{
		case 1:
			rectangle(10, 6 + jp *25, 114, 23 + jp *25);
			rectangle(11, 7 + jp *25, 113, 22 + jp *25);
			rectangle(8, 4 + jp *25, 116, 25 + jp *25);
			rectangle(9, 5 + jp *25, 115, 24 + jp *25);
			break;
		case 2:
			rectangle(80, 6 + jp *25, 184, 23 + jp *25);
			rectangle(81, 7 + jp *25, 183, 22 + jp *25);
			rectangle(78, 4 + jp *25, 186, 25 + jp *25);
			rectangle(79, 5 + jp *25, 185, 24 + jp *25);
			break;
		case 3:
			rectangle(159, 6 + jp *25, 267, 23 + jp *25);
			rectangle(160, 7 + jp *25, 266, 22 + jp *25);
			rectangle(157, 4 + jp *25, 265, 25 + jp *25);
			rectangle(158, 5 + jp *25, 264, 24 + jp *25);
			break;
		case 4:
			rectangle(238, 6 + jp *25, 342, 23 + jp *25);
			rectangle(239, 7 + jp *25, 341, 22 + jp *25);
			rectangle(236, 4 + jp *25, 344, 25 + jp *25);
			rectangle(237, 5 + jp *25, 343, 24 + jp *25);
			break;
		case 5:
			rectangle(317, 6 + jp *25, 421, 23 + jp *25);
			rectangle(318, 7 + jp *25, 420, 22 + jp *25);
			rectangle(315, 4 + jp *25, 423, 25 + jp *25);
			rectangle(316, 5 + jp *25, 422, 24 + jp *25);
			break;
		case 6:
			rectangle(396, 6 + jp *25, 500, 23 + jp *25);
			rectangle(397, 7 + jp *25, 499, 22 + jp *25);
			rectangle(394, 4 + jp *25, 502, 25 + jp *25);
			rectangle(395, 5 + jp *25, 501, 24 + jp *25);
			break;
		case 7:
			rectangle(475, 6 + jp *25, 579, 23 + jp *25);
			rectangle(476, 7 + jp *25, 578, 22 + jp *25);
			rectangle(473, 4 + jp *25, 581, 25 + jp *25);
			rectangle(474, 5 + jp *25, 580, 24 + jp *25);
			break;
	}
}

/*********************************/
int select_func(int i, int j)
{
	int temp;
	switch (i)
	{
		case 1:
			temp = j;
			break;
		case 2:
			temp = j + 3;
			break;
		case 3:
			temp = j + 6;
			break;
		case 4:
			temp = j + 9;
			break;
		case 5:
			temp = j + 12;
			break;
		case 6:
			temp = j + 15;
			break;
		case 7:
			temp = j + 18;
			break;
	}

	clean_down(i);
	return temp;
}

/***************************/