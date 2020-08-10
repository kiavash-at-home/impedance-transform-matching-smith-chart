#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <alloc.h>
#include <math.h>

/*---------------*/
extern struct str
{
	float r, x, z0;
	int xo, yo;
};
extern struct str type[6];
float rpp, xp, z0p, dlp, lanp, pass_flag = 0;
extern void far * ptr;
extern unsigned size;

#define pi 3.14159265

void store_s(int x1, int y1, int x2, int y2);
void restore_s(int x, int y);
void Press_key(void);
void smit_chart(void);
void Two_stuble(int dflag);
void Three_stuble(int dflag);
float landa(int dflag);
/**************************/
void Two_stuble(int dflag)
{
	char ch[10], strlen[2];
	int px, py, temp, i, j, n1, fff = 0, k[15];
	float gl, bl, r, x, dl, rp[30], a, b, c, fi, n, gamax, gamar, b1, b2, lt1, lt2, gamar2, gamax2, tetap2;
	float teta, tetap, gamarp, gamaxp, x0, y0, xconst, lan, gamar1, gamax1;
	k[0] = '0';
	k[1] = '1';
	k[2] = '2';
	k[3] = '3';
	k[4] = '4';
	k[5] = '5';
	k[6] = '6';
	k[7] = '7';
	k[8] = '8';
	k[9] = '9';
	k[10] = '.';
	k[11] = 13;
	k[12] = '-';
	strlen[1] = NULL;
	setcolor(GREEN);
	circle((int)(320 + 210 / 2), 240, (int)(210 / 2));
	if (pass_flag == 0)
	{
		px = type[4].xo;
		py = type[4].yo;
		r = type[4].r;
		x = type[4].x;
	}

	if (pass_flag == 1)
	{
		r = rpp;
		x = xp;
		x0 = (x *x + r *r - 1) / (x *x + (1 + r) *(1 + r));
		y0 = 2 *x / (x *x + (1 + r) *(1 + r));
		px = 320 + (int)(210 *x0);
		py = 240 - (int)(210 *y0);
		/* dl=dlp; */
	}

	setcolor(YELLOW);
	line(320, 240, px, py);
	gl = r / (x *x + r *r);
	bl = -x / (x *x + r *r);
	line(320, 240, 640 - px, 480 - py);
	circle(px, py, 4);
	circle(640 - px, 480 - py, 4);
	delay(200);
	circle(320, 240, (int)(210* sqrt(((r - 1) *(r - 1) + x *x) / ((r + 1) *(r + 1) + x *x))));
	store_s(20, 400, 200, 460);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(20, 400, 200, 460);
	bar(21, 401, 199, 459);
	gcvt(gl, 3, ch);
	outtextxy(55, 420, "Gl=");
	outtextxy(100, 420, ch);
	gcvt(bl, 3, ch);
	outtextxy(55, 440, "Bl=");
	outtextxy(100, 440, ch);
	Press_key();
	restore_s(20, 400);
	if (pass_flag == 0)
	{
		/*  lanp=landa(0);  */
		store_s(120, 130, 460, 160);
		setfillstyle(SOLID_FILL, BLUE);
		setcolor(WHITE);
		rectangle(120, 130, 460, 160);
		bar(121, 131, 459, 159);
		outtextxy(130, 145, "ENTER DISTANC TWO STUBS : Ld(landa)=");
		moveto(420, 145);
		if (dflag == 1)
		{
			gcvt(.125, 3, ch);
			outtext(ch);
			dl = .125;
			Press_key();
		}

		if (dflag == 0)
		{
			for (j = 0; j < 7; j++)
			{
				for (;;)
				{
					fff = 0;
					temp = getch();
					for (n1 = 0; n1 < 12; n1++)
						if (temp == k[n1])
						{
							fff = 1;
							break;
						}

					if (fff == 1) break;
				}

				if (temp == 13) break;
				strlen[0] = temp;
				outtext(strlen);
				ch[j] = strlen[0];
			}

			if (temp == 13) ch[j] = NULL;
			ch[7] = NULL;
			dl = atof(ch);
		}

		restore_s(120, 130);
	}

	dl = dl;
	if (gl > 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl)))
	{
		setfillstyle(SOLID_FILL, BLUE);
		setcolor(WHITE);
		rectangle(120, 130, 460, 160);
		bar(121, 131, 459, 159);
		outtextxy(150, 145, "ERROR USE THREE STUB");
		getch();
		smit_chart();
		return;
	}

	setcolor(GREEN);
	circle(320 + (int)(210 *.5* cos(4 * 3.14 *dl)), 240 - (int)(210 *.5* sin(4 * 3.14 *dl)), (int)(.5 *210));
	Press_key();
	rp[0] = .1;
	rp[1] = .3;
	rp[2] = .5;
	rp[3] = .7;
	rp[4] = 1;
	rp[5] = 1.2;
	rp[6] = 1.6;
	rp[7] = 2;
	rp[8] = 2.4;
	rp[9] = 2.8;
	rp[10] = 3.2;
	rp[11] = 3.6;
	rp[12] = 3.8;
	rp[13] = 5;
	rp[14] = 7;
	rp[15] = 9;
	rp[16] = 12;
	rp[17] = 16;
	rp[18] = 20;
	rp[19] = 30;
	rp[20] = 1000;
	rp[21] = 0;
	setlinestyle(SOLID_LINE, 1, 1);
	setcolor(WHITE);
	for (i = 0; rp[i] != 0; i++)
		if (rp[i] >= 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl)))
			circle((int)(320 + 210 *rp[i] / (1 + rp[i])), 240, (int)(210 / (1 + rp[i])));
	rp[22] = 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl));
	circle((int)(320 + 210 *rp[22] / (1 + rp[22])), 240, (int)(210 / (1 + rp[22])));
	store_s(450, 220, 620, 260);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(450, 220, 620, 260);
	bar(451, 221, 619, 259);
	outtextxy(465, 240, "FOR BIDDEN REGION");
	Press_key();
	restore_s(450, 220);
	setcolor(BLUE);
	for (i = 0; rp[i] != 0; i++)
		if (rp[i] >= 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl)))
			circle((int)(320 + 210 *rp[i] / (1 + rp[i])), 240, (int)(210 / (1 + rp[i])));
	rp[22] = 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl));
	circle((int)(320 + 210 *rp[22] / (1 + rp[22])), 240, (int)(210 / (1 + rp[22])));
	rp[23] = r / (r *r + r + x *x);
	rp[24] = 1 - rp[23];
	setcolor(WHITE);
	circle(320 + (int)(210 *rp[23]), 240, (int)(210 *rp[24]));
	Press_key();
	fi = 4 * 3.14 * dl;
	n = rp[23];
	a = 1 + ((cos(fi) - 2 *n) *(cos(fi) - 2 *n)) / (sin(fi) *sin(fi));
	b = n - (-cos(fi) + 2 *n) *(1 - 2 *n) / (sin(fi) *sin(fi));
	c = (1 - 2 *n) *(1 - 2 *n) / (sin(fi) *sin(fi)) - (1 - 2 *n);
	gamar = (b + sqrt(b *b - a *c)) / a;
	gamax = (gamar *(-cos(fi) + 2 *n) + 1 - 2 *n) / sin(fi);
	gamarp = gamar;
	gamaxp = gamax;
	setfillstyle(SOLID_FILL, LIGHTRED);
	setcolor(LIGHTRED);
	circle(320 + (int)(210 *gamar), 240 - (int)(210 *gamax), 4);
	floodfill(320 + (int)(210 *gamar), 240 - (int)(210 *gamax), LIGHTRED);
	gamar = (b - sqrt(b *b - a *c)) / a;
	gamax = (gamar *(-cos(fi) + 2 *n) + 1 - 2 *n) / sin(fi);
	circle(320 + (int)(210 *gamar), 240 - (int)(210 *gamax), 4);
	floodfill(320 + (int)(210 *gamar), 240 - (int)(210 *gamax), LIGHTRED);
	Press_key();
	store_s(20, 220, 320, 340);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(20, 220, 320, 340);
	setcolor(WHITE);
	bar(21, 221, 319, 339);
	gcvt(gamar, 3, ch);
	outtextxy(45, 240, "gamar1=");
	outtextxy(125, 240, ch);
	gcvt(gamax, 3, ch);
	outtextxy(45, 260, "gamax1=");
	outtextxy(125, 260, ch);
	gcvt(gamarp, 3, ch);
	outtextxy(45, 280, "gamar2=");
	outtextxy(125, 280, ch);
	gcvt(gamaxp, 3, ch);
	outtextxy(45, 300, "gamax2=");
	outtextxy(125, 300, ch);
	outtextxy(45, 320, " point gamar1 &gamax1 is select");
	Press_key();
	restore_s(20, 220);
	/* b1=1+sqrt((1+tan(2 * 3.14*dl)*tan(2 * 3.14*dl))*gl-gl*gl*tan(2 * 3.14*dl)*tan(2 * 3.14*dl));
	  b1=-bl-b1/tan(2 * 3.14*dl); */
	b1 = 2 *gamax / ((1 - gamar) *(1 - gamar) + gamax *gamax);
	xconst = -bl + b1;
	if (xconst > 0) arc(320 + 210, (int)(240 - 210 / xconst), 180 - (int)((180 / 3.1415) *atan((xconst *xconst - 1) / (2 *xconst))), 270, (int)(210 / xconst));
	if (xconst < 0) arc(320 + 210, (int)(240 - 210 / xconst), 90, 180 - (int)((180 / 3.1415) *atan((xconst *xconst - 1) / (2 *xconst))), (int)(210 / xconst));
	store_s(20, 400, 300, 440);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(20, 400, 300, 440);
	bar(21, 401, 299, 439);
	gcvt(xconst, 3, ch);
	outtextxy(35, 420, "   SUSEBTANCE FIRST STUB =");
	outtextxy(240, 420, ch);
	Press_key();
	restore_s(20, 400);
	gamax2 = -2 *xconst / (1 + xconst *xconst);
	gamar2 = (-1 + xconst *xconst) / (1 + xconst *xconst);
	tetap2 = atan(gamax2 / gamar2);
	if (gamar2 < 0) tetap2 = tetap2 + 3.14;
	arc(320, 240, -(int)((180 / 3.14) *tetap2), 0, 210);
	Press_key();
	bar(21, 401, 299, 439);
	lt1 = (+tetap2) / (4 * 3.14);
	if (lt1 < 0) lt1 = lt1 + .5;

	setfillstyle(SOLID_FILL, BLUE);
	rectangle(20, 400, 330, 460);
	bar(21, 401, 329, 459);
	gcvt(lt1, 3, ch);
	outtextxy(40, 420, "LINE FIRST STUB(landa)=");
	outtextxy(250, 420, ch);
	Press_key();
	teta = atan(gamax / gamar);
	if (gamar < 0) teta = teta + 3.14;
	setcolor(LIGHTRED);
	arc(320, 240, (int)((180 / 3.14) *(teta - 4 * 3.14 *dl)), (int)((180 / 3.14) *teta), (int)(210* sqrt(gamax *gamax + gamar *gamar)));
	/* b2=-sqrt(gl*(1+tan(2 * 3.14*dl)*tan(2 * 3.14*dl))-gl*gl*tan(2 * 3.14*dl)*tan(2 * 3.14*dl));
	  b2=(b2-gl)/(gl*tan(2 * 3.14*dl)); */
	gamar1 = gamar* cos(4 * 3.14 *dl) + gamax* sin(4 * 3.14 *dl);
	gamax1 = gamax* cos(4 * 3.14 *dl) - gamar* sin(4 * 3.14 *dl);

	b2 = 2 *gamax1 / ((1 - gamar1) *(1 - gamar1) + gamax1 *gamax1);
	xconst = b2;
	setcolor(WHITE);
	if (xconst > 0) arc(320 + 210, (int)(240 - 210 / xconst), 180 - (int)((180 / 3.1415) *atan((xconst *xconst - 1) / (2 *xconst))), 270, (int)(210 / xconst));
	if (xconst < 0) arc(320 + 210, (int)(240 - 210 / xconst), 90, 180 - (int)((180 / 3.1415) *atan((xconst *xconst - 1) / (2 *xconst))), (int)(210 / xconst));
	store_s(20, 400, 300, 440);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(20, 400, 300, 440);
	bar(21, 401, 299, 439);
	gcvt(-xconst, 3, ch);
	outtextxy(35, 420, "SUSEBTANCE SECOND STUB =");
	outtextxy(240, 420, ch);
	Press_key();
	restore_s(20, 400);
	setcolor(WHITE);
	gamax2 = 2 *xconst / (1 + xconst *xconst);
	gamar2 = (-1 + xconst *xconst) / (1 + xconst *xconst);
	tetap2 = atan(gamax2 / gamar2);
	if (gamar2 < 0) tetap2 = tetap2 + 3.14;
	setcolor(LIGHTRED);
	arc(320, 240, -(int)((180 / 3.14) *tetap2), 0, 210);
	Press_key();
	bar(21, 401, 299, 439);
	lt2 = (+tetap2) / (4 * 3.14);
	if (lt2 < 0) lt2 = lt2 + .5;
	gcvt(lt2, 3, ch);
	outtextxy(45, 420, "LINE SECOND STUB(landa) =");
	outtextxy(250, 420, ch);
	Press_key();
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(1, 25, getmaxx() - 1, getmaxy() - 1);
	pass_flag = 0;
}

/*******************************************/
void Three_stuble(int dflag)
{
	int px, py, j, temp, i, u, v, n1, fff, k[15];
	float tt, r, x, bl, gl, dl, rp[30], a, b, c, n, fi, z, gamar1, gamax1, gamar2, gamax2, rr;
	float b1, b2, b3, r1, r2, x1, x2, bs1, teta, t, z0, tetap, xconst, lt1, lan, tetap3, gamar3, gamax3;
	float gamar4, gamax4, gl4, bl4;
	char ch[10], strlen[2];
	k[0] = '0';
	k[1] = '1';
	k[2] = '2';
	k[3] = '3';
	k[4] = '4';
	k[5] = '5';
	k[6] = '6';
	k[7] = '7';
	k[8] = '8';
	k[9] = '9';
	k[10] = '.';
	k[11] = 13;
	k[12] = '-';
	strlen[1] = NULL;
	px = type[5].xo;
	py = type[5].yo;
	r = type[5].r;
	x = type[5].x;
	z0 = type[5].z0;
	setcolor(YELLOW);
	line(320, 240, px, py);
	gl = r / (x *x + r *r);
	bl = -x / (x *x + r *r);
	line(320, 240, 640 - px, 480 - py);
	circle(px, py, 4);
	circle(640 - px, 480 - py, 4);
	delay(200);
	circle(320, 240, (int)(210* sqrt(((r - 1) *(r - 1) + x *x) / ((r + 1) *(r + 1) + x *x))));
	store_s(20, 400, 200, 460);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(20, 400, 200, 460);
	bar(21, 401, 199, 459);
	gcvt(gl, 3, ch);
	outtextxy(55, 420, "Gl=");
	outtextxy(100, 420, ch);
	gcvt(bl, 3, ch);
	outtextxy(55, 440, "Bl=");
	outtextxy(100, 440, ch);
	Press_key();
	restore_s(20, 400);
	setcolor(GREEN);
	circle(320 + 105, 240, 105);
	/* lan=landa(0); */
	store_s(120, 130, 480, 160);
	setfillstyle(SOLID_FILL, BLUE);
	setcolor(WHITE);
	rectangle(120, 130, 480, 160);
	bar(121, 131, 479, 159);
	outtextxy(130, 145, "ENTER DISTANC THREE STUBS : Ld(landa)=");
	moveto(430, 145);
	if (dflag == 1)
	{
		gcvt(.125, 3, ch);
		outtext(ch);
		dl = .125;
		Press_key();
	}

	if (dflag == 0)
	{
		for (j = 0; j < 7; j++)
		{
			for (;;)
			{
				fff = 0;
				temp = getch();
				for (n1 = 0; n1 < 12; n1++)
					if (temp == k[n1])
					{
						fff = 1;
						break;
					}

				if (fff == 1) break;
			}

			if (temp == 13) break;
			strlen[0] = temp;
			outtext(strlen);
			ch[j] = strlen[0];
		}

		if (temp == 13) ch[j] = NULL;
		ch[7] = NULL;
		dl = atof(ch);
	}

	restore_s(120, 130);
	Press_key();
	rp[0] = .1;
	rp[1] = .3;
	rp[2] = .5;
	rp[3] = .7;
	rp[4] = 1;
	rp[5] = 1.2;
	rp[6] = 1.6;
	rp[7] = 2;
	rp[8] = 2.4;
	rp[9] = 2.8;
	rp[10] = 3.2;
	rp[11] = 3.6;
	rp[12] = 3.8;
	rp[13] = 5;
	rp[14] = 7;
	rp[15] = 9;
	rp[16] = 12;
	rp[17] = 16;
	rp[18] = 20;
	rp[19] = 30;
	rp[20] = 1000;
	rp[21] = 0;
	setlinestyle(SOLID_LINE, 1, 1);
	setcolor(WHITE);
	for (i = 0; rp[i] != 0; i++)
		if (rp[i] >= 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl)))
			circle((int)(320 + 210 *rp[i] / (1 + rp[i])), 240, (int)(210 / (1 + rp[i])));
	rp[22] = 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl));
	circle((int)(320 + 210 *rp[22] / (1 + rp[22])), 240, (int)(210 / (1 + rp[22])));
	Press_key();
	store_s(450, 220, 620, 260);
	setfillstyle(SOLID_FILL, BLUE);

	rectangle(450, 220, 620, 260);
	bar(451, 221, 619, 259);
	outtextxy(465, 240, "FOR BIDDEN REGION");
	Press_key();
	restore_s(450, 220);
	setcolor(BLUE);
	for (i = 0; rp[i] != 0; i++)

		if (rp[i] >= 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl)))
			circle((int)(320 + 210 *rp[i] / (1 + rp[i])), 240, (int)(210 / (1 + rp[i])));
	rp[22] = 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl));
	circle((int)(320 + 210 *rp[22] / (1 + rp[22])), 240, (int)(210 / (1 + rp[22])));
	Press_key();
	setcolor(WHITE);
	for (i = 0; rp[i] != 0; i++)
		if (rp[i] >= 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl)))
		{
			u = 320 + (int)(210 *(rp[i] / (1 + rp[i])) *cos(4 * 3.14 *dl));
			v = 240 - (int)(210 *(rp[i] / (1 + rp[i])) *sin(4 * 3.14 *dl));
			circle(u, v, (int)(210 / (rp[i] + 1)));
		}

	rp[22] = 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl));
	u = 320 + (int)(210 *(rp[22] / (1 + rp[22])) *cos(4 * 3.14 *dl));
	v = 240 - (int)(210 *(rp[22] / (1 + rp[22])) *sin(4 * 3.14 *dl));
	circle(u, v, (int)(210 / (rp[22] + 1)));
	Press_key();
	if (r >= 1 / (sin(2 * 3.14 *dl) *sin(2 * 3.14 *dl)))
	{
		setfillstyle(SOLID_FILL, BLUE);
		setcolor(WHITE);
		rectangle(120, 130, 460, 160);
		bar(121, 131, 459, 159);
		outtextxy(150, 145, "  USE TWO STUB");
		Press_key();
		smit_chart();
		return;
	}

	setcolor(YELLOW);
	u = 320 + (int)(210 *(r / (r *r + x *x + r)));
	circle(u, 240, (int)(210 *(1 - r / (r *r + x *x + r))));
	Press_key();
	rr = 1 / (sin(2 *pi *dl) *sin(2 *pi *dl));
	fi = 4 *pi * dl;
	n = r / (r *r + r + x *x);
	z = rr / (rr + 1);
	a = (2 *z* cos(fi) - 2 *n) *(2 *z* cos(fi) - 2 *n);
	a = a / (4 *z *z* sin(fi) *sin(fi));
	a = a + 1;
	b = (2 *n - 2 *z* cos(fi)) *(z *z *(1 / (rr *rr) - 1) - 1 + 2 *n);
	b = b / (4 *z *z* sin(fi) *sin(fi));
	b = b + n;
	c = z *z *(1 / (rr *rr) - 1) - 1 + 2 * n;
	c = c *c / (4 *z *z* sin(fi) *sin(fi));
	c = c - 1 + 2 * n;
	if ((b *b - a *c) > 0)
	{
		gamar1 = (b + sqrt(b *b - a *c)) / a;
		gamax1 = gamar1 *(2 *z* cos(fi) - 2 *n) + z *z *(1 / (rr *rr) - 1) - 1 + 2 * n;
		gamax1 = gamax1 / (-2 *z* sin(fi));
		gamar2 = (b - sqrt(b *b - a *c)) / a;
		gamax2 = gamar2 *(2 *z* cos(fi) - 2 *n) + z *z *(1 / (rr *rr) - 1) - 1 + 2 * n;
		gamax2 = gamax2 / (-2 *z* sin(fi));
		setfillstyle(SOLID_FILL, LIGHTRED);
		setcolor(LIGHTRED);
		circle(320 + (int)(210 *gamar1), 240 - (int)(210 *gamax1), 3);
		floodfill(320 + (int)(210 *gamar1), 240 - (int)(210 *gamax1), LIGHTRED);
		circle(320 + (int)(210 *gamar2), 240 - (int)(210 *gamax2), 3);
		floodfill(320 + (int)(210 *gamar2), 240 - (int)(210 *gamax2), LIGHTRED);
		x1 = 2 *gamax1 / ((1 - gamar1) *(1 - gamar1) + gamax1 *gamax1);
		b1 = x1;
		x2 = 2 *gamax2 / ((1 - gamar2) *(1 - gamar2) + gamax2 *gamax2);
		b2 = x2;
		if (b1 < b2)
		{
			b3 = b2;
			b2 = b1;
			b1 = b3;
		}

		store_s(120, 130, 480, 190);
		setfillstyle(SOLID_FILL, BLUE);
		setcolor(WHITE);
		rectangle(120, 130, 480, 190);
		bar(121, 131, 479, 189);
		outtextxy(130, 145, "SUSCEBTANCE FIRST STUB >       or<");
		gcvt(b1 - bl, 3, ch);
		outtextxy(330, 145, ch);
		gcvt(b2 - bl, 3, ch);
		outtextxy(410, 145, ch);
		Press_key();
		outtextxy(150, 175, "ENTER BS1 INSID AREA UP");
	}
	else
	{
		store_s(120, 130, 480, 190);
		setfillstyle(SOLID_FILL, BLUE);
		setcolor(WHITE);
		rectangle(120, 130, 480, 190);
		bar(121, 131, 479, 189);
		outtextxy(130, 155, "ENTER BS1 ANY NUMBER");
		outtextxy(150, 175, "  OR USE TWO STUB");
	}

	moveto(370, 175);
	if (dflag == 1)
	{
		gcvt(1.0, 3, ch);
		outtext(ch);
		bs1 = 1.0;
		Press_key();
	}

	if (dflag == 0)
	{
		for (j = 0; j < 7; j++)
		{
			for (;;)
			{
				fff = 0;
				temp = getch();
				for (n1 = 0; n1 < 13; n1++)
					if (temp == k[n1])
					{
						fff = 1;
						break;
					}

				if (fff == 1) break;
			}

			if (temp == 13) break;
			strlen[0] = temp;
			outtext(strlen);
			ch[j] = strlen[0];
		}

		if (temp == 13) ch[j] = NULL;
		ch[7] = NULL;
		bs1 = atof(ch);
	}

	restore_s(120, 130);
	bl = bl + bs1;
	gamar1 = (gl *gl + bl *bl - 1) / ((gl + 1) *(gl + 1) + bl *bl);
	gamax1 = 2 *bl / ((gl + 1) *(gl + 1) + bl *bl);
	setcolor(LIGHTRED);
	setfillstyle(SOLID_FILL, LIGHTRED);
	circle(320 + (int)(210 *gamar1), 240 - (int)(210 *gamax1), 3);
	floodfill(320 + (int)(210 *gamar1), 240 - (int)(210 *gamax1), LIGHTRED);
	store_s(120, 130, 480, 160);
	xconst = bs1;
	if (xconst > 0) arc(320 + 210, (int)(240 - 210 / xconst), 180 - (int)((180 / 3.1415) *atan((xconst *xconst - 1) / (2 *xconst))), 270, (int)(210 / xconst));
	if (xconst < 0) arc(320 + 210, (int)(240 - 210 / xconst), 90, 180 - (int)((180 / 3.1415) *atan((xconst *xconst - 1) / (2 *xconst))), (int)(210 / xconst));
	store_s(20, 400, 300, 440);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(20, 400, 300, 440);
	bar(21, 401, 299, 439);
	gcvt(xconst, 3, ch);
	outtextxy(45, 420, "SUSEBTANCE FIRST STUB =");
	outtextxy(240, 420, ch);
	Press_key();
	restore_s(20, 400);

	gamax3 = -2 *xconst / (1 + xconst *xconst);
	gamar3 = (-1 + xconst *xconst) / (1 + xconst *xconst);
	tetap3 = atan(gamax3 / gamar3);
	if (gamar3 < 0) tetap3 = tetap3 + 3.14;
	arc(320, 240, -(int)((180 / 3.14) *tetap3), 0, 210);
	Press_key();
	bar(21, 401, 299, 439);
	lt1 = (+tetap3) / (4 * 3.14);
	if (lt1 < 0) lt1 = .5 + lt1;
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(20, 400, 330, 460);
	bar(21, 401, 329, 459);
	gcvt(lt1, 3, ch);
	outtextxy(40, 420, "LINE FIRST STUB(landa)=");
	outtextxy(250, 420, ch);
	Press_key();
	/*  restore_s(120,130); */
	teta = atan(gamax1 / gamar1);
	if (gamar1 < 0) teta = teta + pi;
	setcolor(LIGHTRED);
	arc(320, 240, (int)((teta - 4 *pi *dl) *180 / pi), (int)(teta *180 / pi), (int)(210 *(sqrt(gamax1 *gamax1 + gamar1 *gamar1))));
	Press_key();
	tt = tan(2 * 3.14 *dl);
	gl4 = gl *(1 - bl *tt) + (bl + tt) *gl * tt;
	gl4 = gl4 / ((1 - bl *tt) *(1 - bl *tt) + (gl *tt *gl *tt));
	bl4 = (bl + tt) *(1 - bl *tt) - gl *gl * tt;
	bl4 = bl4 / ((1 - bl *tt) *(1 - bl *tt) + (gl *tt *gl *tt));

	/* gamar4=gamar1*cos(4 * 3.14*dl)+gamax1*sin(4 * 3.14*dl);
	  gamax4=gamax1*cos(4 * 3.14*dl)-gamar1*sin(4 * 3.14*dl);
	  gl4=(1-gamar4*gamar4-gamax4*gamax4)/((1-gamar4)*(1-gamar4)+gamax4*gamax4);
	  bl4=2*gamax4/((1-gamar4)*(1-gamar4)+gamax4*gamax4); */

	r1 = gl4 / (gl4 *gl4 + bl4 *bl4);
	x1 = -bl4 / (gl4 *gl4 + bl4 *bl4);
	setfillstyle(SOLID_FILL, BLUE);
	setcolor(WHITE);
	rectangle(120, 130, 480, 190);
	bar(121, 131, 479, 189);
	outtextxy(160, 145, "CONTINUE AS TWO STUB TUNER ");
	outtextxy(160, 175, " r=       x=        z0=");
	gcvt(r1 *z0, 3, ch);
	outtextxy(185, 175, ch);
	gcvt(x1 *z0, 3, ch);
	outtextxy(260, 175, ch);
	gcvt(z0, 3, ch);
	outtextxy(345, 175, ch);
	Press_key();
	dlp = dl;
	rpp = r1;
	lanp = lan;
	xp = x1;
	z0p = z0;
	pass_flag = 1;
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(1, 25, getmaxx() - 1, getmaxy() - 1);
	smit_chart();
	Two_stuble(0);
}

/***************************************/