/**************************************************************
Filename：fruits.c   Author: 李天依，田铭   Version:1.0   Date:10.19
Description:该文件包含了关于画图的相关函数
Function List:
		  1.fun1                                         //使水果位置坐标改变
		  2.drawtextput                              //输出框绘制
		  3.drawinbutton                              //凹陷按钮绘制
		  4.drawoutbutton                           //凸起按钮绘制
		  5.apple                                          //苹果绘制
		  6.watermelon                                  //西瓜绘制
		  7.pear                                            //梨
		  8.banana
		  9.boom
		  10.strawberry
		  11.lemon
		  12.peach
		  13.background
		  14.drawbutton
		  15.draw_exit_button
		  16.SetPixel                      //
		  17.VLine
		  18.draw_pause_button
		  19.life

History： 10.22写注释
<author>  <time> <version> <desc>
李天依 ，田铭  19/10/19  1.0    build this module
***************************************************************/
#include"common.h"
#include"fruits.h"

/**************改变水果位置****************/
void fun1(int x, int y, int* p)
{
	int i;
	for (i = 0; p[i]; i = i + 2)
	{
		p[i] = x + p[i];
	}
	for (i = 1; p[i]; i = i + 2)
	{
		p[i] = y + p[i];
	}
}
/************输出框绘制*******************/
void drawtextput(int x, int y)
{
	setfillstyle(SOLID_FILL, CYAN);
	bar(4 + x, 4 + y, 236 + x, 26 + 5 + y);
	setcolor(BLACK);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	line(3 + x, 27 + 5 + y, 3 + x, 3 + y);
	line(2 + x, 28 + 5 + y, 2 + x, 2 + y);
	line(3 + x, 3 + y, 237 + x, 3 + y);
	line(2 + x, 2 + y, 238 + x, 2 + y);
	setcolor(DARKGRAY);
	line(4 + x, 27 + 5 + y, 237 + x, 27 + 5 + y);
	line(3 + x, 28 + 5 + y, 238 + x, 28 + 5 + y);
	line(237 + x, 27 + 5 + y, 237 + x, 4 + y);
	line(238 + x, 28 + 5 + y, 238 + x, 3 + y);
	setcolor(WHITE);
	line(1 + x, 29 + 5 + y, 1 + x, 1 + y);
	line(0 + x, 29 + 5 + y, 0 + x, 1 + y);
	line(1 + x, 1 + y, 239 + x, 1 + y);
	line(0 + x, 0 + y, 239 + x, 0 + y);
	line(1 + x, 29 + 5 + y, 239 + x, 29 + 5 + y);
	line(0 + x, 30 + 5 + y, 240 + x, 30 + 5 + y);
	line(239 + x, 1 + y, 239 + x, 29 + 5 + y);
	line(240 + x, 0 + y, 240 + x, 30 + 5 + y);
}
/*************进入按钮绘制*****************/
void drawinbutton(int x, int y, int color)
{
	setfillstyle(SOLID_FILL, color);
	bar(4 + x, 4 + y, 56 + x, 31 + y);
	setcolor(BLACK);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	line(3 + x, 32 + y, 3 + x, 3 + y);
	line(2 + x, 33 + y, 2 + x, 2 + y);
	line(3 + x, 3 + y, 57 + x, 3 + y);
	line(2 + x, 2 + y, 58 + x, 2 + y);
	setcolor(DARKGRAY);
	line(4 + x, 32 + y, 57 + x, 32 + y);
	line(3 + x, 33 + y, 58 + x, 33 + y);
	line(57 + x, 32 + y, 57 + x, 4 + y);
	line(58 + x, 33 + y, 58 + x, 3 + y);
	setcolor(WHITE);
	line(1 + x, 34 + y, 1 + x, 1 + y);
	line(0 + x, 34 + y, 0 + x, 1 + y);
	line(1 + x, 1 + y, 59 + x, 1 + y);
	line(0 + x, 0 + y, 59 + x, 0 + y);
	line(1 + x, 34 + y, 59 + x, 34 + y);
	line(0 + x, 35 + y, 60 + x, 35 + y);
	line(59 + x, 1 + y, 59 + x, 34 + y);
	line(60 + x, 0 + y, 60 + x, 35 + y);
}
/**************输出按钮绘制***********************/
void drawoutbutton(int x, int y, int color)
{
	setfillstyle(SOLID_FILL, color);
	bar(4 + x, 4 + y, 56 + x, 31 + y);
	setcolor(WHITE);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	line(3 + x, 32 + y, 3 + x, 3 + y);
	line(2 + x, 33 + y, 2 + x, 2 + y);
	line(3 + x, 3 + y, 57 + x, 3 + y);
	line(2 + x, 2 + y, 58 + x, 2 + y);
	setcolor(BLACK);
	line(4 + x, 32 + y, 57 + x, 32 + y);
	line(3 + x, 33 + y, 58 + x, 33 + y);
	line(57 + x, 32 + y, 57 + x, 4 + y);
	line(58 + x, 33 + y, 58 + x, 3 + y);
	setcolor(BLACK);
	line(1 + x, 34 + y, 1 + x, 1 + y);
	line(0 + x, 34 + y, 0 + x, 1 + y);
	line(1 + x, 1 + y, 59 + x, 1 + y);
	line(0 + x, 0 + y, 59 + x, 0 + y);
	line(1 + x, 34 + y, 59 + x, 34 + y);
	line(0 + x, 35 + y, 60 + x, 35 + y);
	line(59 + x, 1 + y, 59 + x, 34 + y);
	line(60 + x, 0 + y, 60 + x, 35 + y);
}
/****************画苹果**************************/
void apple(int x, int y)
{

	int i;
	int v[] = { 46,23,39,23,33,23,25,24,17,28,
			 13,32,10,38,8,45,8,53,10,60,
			 13,67,18,75,23,80,28,84,35,86,
			 43,85,48,84,50,83,55,84,61,85,
			 64,86,70,85,75,82,80,78,84,73,
			 88,67,90,62,92,54,91,45,90,38,
			 87,32,83,28,78,25,72,23,65,23,
			 60,23,52,24,50,25,46,23,0,0 };           //轮廓
	int u[] = { 49,32,49,24,50,19,52,14,57,12,
			 59,13,60,16,59,18,56,19,53,22,
			 52,26,51,32,49,32,0,0 };                  //枝
	int l[] = { 50,16,49,13,47,10,44,8,40,7,
			 35,8,32,7,32,11,34,15,37,18,
			 41,20,46,21,50,21,51,19,50,16,0,0 };       //叶子
	fun1(x, y, u);
	fun1(x, y, v);
	fun1(x, y, l);

	setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	drawpoly(39, v);
	drawpoly(13, u);
	drawpoly(15, l);
	ellipse(x + 50, y + 21, 225, 315, 11, 11);
	setfillstyle(SOLID_FILL, RED);
	floodfill(x + 50, y + 50, DARKGRAY);
	setfillstyle(SOLID_FILL, BROWN);
	floodfill(x + 52, y + 20, DARKGRAY);
	setfillstyle(SOLID_FILL, GREEN);
	floodfill(x + 41, y + 15, DARKGRAY);
	moveto(x + 32, y + 7);
	lineto(x + 41, y + 13);
	lineto(x + 50, y + 20);
	setcolor(WHITE);
	setlinestyle(SOLID_LINE, 0, 3);
	moveto(x + 27, y + 35);
	lineto(x + 25, y + 37);
	lineto(x + 24, y + 41);
	moveto(x + 23, y + 42);
	lineto(x + 21, y + 46);
	lineto(x + 20, y + 50);
	lineto(x + 20, y + 58);
}
/**************************画西瓜***************************/
void watermelon(int x, int y)
{
	int u1[] = { 88,32,81,32,77,31,73,32,69,33,66,32,61,34,56,36,
			  50,38,46,41,41,46,36,51,30,59,29,64,26,68,24,75,
			  23,82,23,88,22,96,24,103,26,106,29,109,28,106,28,102,
			  28,98,29,92,32,87,33,83,33,78,35,73,37,69,41,65,
			  43,60,47,55,52,51,56,47,59,44,64,43,68,41,74,39,
			  79,39,84,36,89,35,91,34,88,32,0,0 };
	int u2[] = { 92,34,87,36,83,38,80,40,78,41,76,44,76,47,73,49,
			  69,52,67,55,65,60,58,66,54,69,52,74,51,77,47,80,
			  43,85,42,90,41,92,36,98,34,102,34,105,31,108,30,109,
			  29,110,34,114,35,114,39,109,41,108,44,103,46,101,51,97,
			  56,90,58,85,67,77,69,73,72,68,81,57,82,54,84,49,
			  89,43,92,40,94,37,94,35,92,34,0,0 };
	int u3[] = { 95,36,95,42,95,45,93,50,91,56,86,64,86,67,78,77,
			  78,82,69,91,68,95,64,96,61,98,58,102,54,104,51,108,
			  46,108,38,115,38,116,41,118,46,116,49,114,53,115,59,113,
			  70,107,72,102,74,102,76,101,79,98,79,96,86,90,87,86,
			  93,77,93,71,97,67,99,57,102,53,102,47,102,43,95,36,0,0 };
	int u4[] = { 103,44,103,46,104,49,104,52,105,55,104,58,105,62,103,67,
			  101,78,98,81,98,87,93,93,91,100,88,101,86,105,80,108,
			  72,114,65,115,61,116,57,116,44,117,40,118,47,121,54,122,
			  63,120,70,120,76,117,79,116,83,115,89,109,92,109,95,104,
			  98,101,102,89,106,86,106,79,110,75,109,68,111,64,110,58,
			  110,55,103,44,0,0 };
	int v1[] = { 97,37,99,34,98,30,94,27,94,32,93,34,97,37,0,0 };
	int v2[] = { 101,4,87,5,93,8,91,14,91,21,94,27,101,30,106,30,
			  109,27,110,21,107,17,99,16,96,20,95,19,95,14,97,10,
			  101,4,0,0 };
	int v3[] = { 96,20,98,25,103,26,107,23,105,20,102,20,99,22,98,25,0,0 };
	fun1(x, y, u1);
	fun1(x, y, u2);
	fun1(x, y, u3);
	fun1(x, y, u4);
	fun1(x, y, v1);
	fun1(x, y, v2);
	fun1(x, y, v3);
	setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	circle(x + 65, y + 75, 50);
	drawpoly(45, u1);
	drawpoly(45, u2);
	drawpoly(40, u3);
	drawpoly(42, u4);
	drawpoly(7, v1);
	drawpoly(17, v2);
	drawpoly(8, v3);
	setfillstyle(SOLID_FILL, GREEN);
	floodfill(x + 55, y + 55, DARKGRAY);
	floodfill(x + 45, y + 35, DARKGRAY);
	floodfill(x + 78, y + 70, DARKGRAY);
	floodfill(x + 82, y + 101, DARKGRAY);
	floodfill(x + 100, y + 104, DARKGRAY);
	floodfill(x + 102, y + 28, DARKGRAY);
	setfillstyle(SOLID_FILL, DARKGRAY);
	floodfill(x + 45, y + 50, DARKGRAY);
	floodfill(x + 64, y + 70, DARKGRAY);
	floodfill(x + 75, y + 95, DARKGRAY);
	floodfill(x + 80, y + 110, DARKGRAY);
	floodfill(x + 97, y + 33, DARKGRAY);
}
/**************************画梨************************************/
void pear(int x, int y)
{
	int u[] = { 50,9,44,11,37,19,34,23,25,31,18,40,14,49,11,58,
			 11,64,12,73,16,81,21,86,27,90,33,93,39,94,42,95,
			 55,95,62,93,71,88,81,80,86,73,89,64,89,56,87,48,
			 83,36,80,30,78,23,75,18,70,14,65,12,62,11,59,11,
			 54,9,50,9,0,0 };
	int v1[] = { 58,19,59,15,61,10,64,7,66,4,70,2,0,0 };
	int v2[] = { 52,16,55,17,59,19,62,19,65,18,0,0 };
	fun1(x, y, u);
	fun1(x, y, v1);
	fun1(x, y, v2);


	setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	drawpoly(34, u);
	setlinestyle(SOLID_LINE, 0, 3);
	drawpoly(6, v1);
	drawpoly(5, v2);
	line(x + 72, y + 31, x + 72, y + 31);
	line(x + 63, y + 41, x + 63, y + 41);
	line(x + 73, y + 42, x + 73, y + 42);
	line(x + 63, y + 49, x + 63, y + 49);
	line(x + 79, y + 58, x + 79, y + 58);
	line(x + 77, y + 66, x + 77, y + 66);
	line(x + 69, y + 67, x + 69, y + 67);
	line(x + 65, y + 75, x + 65, y + 75);
	line(x + 52, y + 89, x + 52, y + 89);
	line(x + 24, y + 75, x + 24, y + 75);
	line(x + 17, y + 63, x + 17, y + 63);
	line(x + 20, y + 54, x + 20, y + 54);
	setfillstyle(SOLID_FILL, YELLOW);
	floodfill(x + 50, y + 50, DARKGRAY);

}
/************************画香蕉****************************/
void banana(int x, int y)
{

	int u[] = { 75,3,75,6,79,8,80,9,77,17,69,24,63,33,57,40,
			 46,54,34,62,20,67,14,69,7,70,5,71,4,73,4,76,
			 6,80,11,86,19,91,28,95,35,97,49,94,66,88,75,79,
			 84,66,88,57,89,50,89,41,87,28,84,20,86,10,91,12,
			 93,10,89,6,79,3,75,3,0,0 };
	int v[] = { 84,20,81,29,79,41,75,54,66,68,57,75,48,80,35,83,
			 22,83,15,81,7,77,0,0 };
	int l[] = { 8,71,7,73,6,75,6,74,0,0 };

	fun1(x, y, u);
	fun1(x, y, v);
	fun1(x, y, l);

	setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	drawpoly(36, u);
	drawpoly(11, v);
	setlinestyle(SOLID_LINE, 0, 3);
	drawpoly(4, l);

	setfillstyle(SOLID_FILL, YELLOW);
	floodfill(x + 50, y + 60, DARKGRAY);
	floodfill(x + 75, y + 70, DARKGRAY);
}
/**********************画炸弹***************************/
void boom(int x, int y)
{
	int cmwhite[] = { 105,81,108,78,109,75,109,64,107,57,
				   103,52,98,47,93,44,88,44,86,46,
				   85,48,85,51,90,55,94,58,98,64,
				   101,70,102,76,104,81,105,81,0,0 };
	fun1(x, y, cmwhite);
	setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	setfillstyle(SOLID_FILL, BLACK);
	fillellipse(x + 80, y + 70, x + 40, y + 40);
	moveto(x + 51, y + 46);
	lineto(x + 46, y + 38);
	lineto(x + 62, y + 26);
	lineto(x + 68, y + 35);
	floodfill(x + 58, y + 30, DARKGRAY);
	moveto(x + 54, y + 32);
	lineto(x + 46, y + 20);
	setcolor(RED);
	setlinestyle(SOLID_LINE, 0, 1);
	moveto(x + 46, y + 20);
	lineto(x + 38, y + 20);
	lineto(x + 41, y + 17);
	lineto(x + 37, y + 13);
	lineto(x + 43, y + 13);
	lineto(x + 42, y + 8);
	lineto(x + 46, y + 12);
	lineto(x + 49, y + 8);
	lineto(x + 46, y + 20);
	setfillstyle(SOLID_FILL, YELLOW);
	floodfill(x + 45, y + 19, RED);
	setcolor(WHITE);
	setlinestyle(SOLID_LINE, 0, 1);
	drawpoly(19, cmwhite);
	setfillstyle(SOLID_FILL, BLACK);
	floodfill(x + 100, y + 55, DARKGRAY);
}
/***********************画草莓**************************/
void strawberry(int x, int y)
{
	int cmred[] = { 37,42,33,42,31,43,30,44,29,46,27,47,
				 26,49,24,52,23,54,23,65,25,71,26,75,
				 29,79,33,83,38,89,44,92,48,95,51,97,
				 56,99,62,100,71,100,72,99,75,96,79,92,
				 82,85,86,77,88,72,91,64,92,59,91,52,
				 89,46,85,42,79,38,76,37,67,40,69,44,
				 74,51,68,51,62,49,57,46,45,59,45,47,
				 46,44,33,50,37,42,0,0 };
	int cmgreen[] = { 76,37,81,36,75,33,72,32,66,32,62,33,
				   66,27,56,33,52,28,47,22,41,19,37,18,
				   34,22,44,25,50,30,53,35,38,34,42,38,
				   37,42,0,0 };
	fun1(x, y, cmred);
	fun1(x, y, cmgreen);
	setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	drawpoly(45, cmred);
	setfillstyle(SOLID_FILL, RED);
	floodfill(x + 40, y + 61, DARKGRAY);
	drawpoly(19, cmgreen);
	setfillstyle(SOLID_FILL, GREEN);
	floodfill(x + 49, y + 46, DARKGRAY);
	putpixel(x + 34, y + 62, BLACK);
	putpixel(x + 34, y + 61, BLACK);
	putpixel(x + 33, y + 62, BLACK);
	putpixel(x + 33, y + 61, BLACK);
	putpixel(x + 54, y + 60, BLACK);
	putpixel(x + 55, y + 60, BLACK);
	putpixel(x + 55, y + 59, BLACK);
	putpixel(x + 54, y + 59, BLACK);
	putpixel(x + 80, y + 62, BLACK);
	putpixel(x + 79, y + 61, BLACK);
	putpixel(x + 80, y + 62, BLACK);
	putpixel(x + 79, y + 62, BLACK);
	putpixel(x + 66, y + 69, BLACK);
	putpixel(x + 66, y + 70, BLACK);
	putpixel(x + 67, y + 69, BLACK);
	putpixel(x + 67, y + 70, BLACK);
	putpixel(x + 44, y + 69, BLACK);
	putpixel(x + 44, y + 70, BLACK);
	putpixel(x + 43, y + 69, BLACK);
	putpixel(x + 43, y + 70, BLACK);
	putpixel(x + 72, y + 95, BLACK);
	putpixel(x + 71, y + 94, BLACK);
	putpixel(x + 72, y + 94, BLACK);
	putpixel(x + 71, y + 95, BLACK);
	putpixel(x + 53, y + 79, BLACK);
	putpixel(x + 54, y + 80, BLACK);
	putpixel(x + 54, y + 79, BLACK);
	putpixel(x + 53, y + 80, BLACK);
	putpixel(x + 46, y + 85, BLACK);
	putpixel(x + 46, y + 86, BLACK);
	putpixel(x + 45, y + 85, BLACK);
	putpixel(x + 45, y + 86, BLACK);
	putpixel(x + 59, y + 95, BLACK);
	putpixel(x + 60, y + 94, BLACK);
	putpixel(x + 59, y + 94, BLACK);
	putpixel(x + 60, y + 95, BLACK);
	putpixel(x + 75, y + 89, BLACK);
	putpixel(x + 74, y + 89, BLACK);
	putpixel(x + 75, y + 88, BLACK);
	putpixel(x + 74, y + 89, BLACK);
	putpixel(x + 83, y + 74, BLACK);
	putpixel(x + 82, y + 74, BLACK);
	putpixel(x + 82, y + 75, BLACK);
	putpixel(x + 83, y + 75, BLACK);
	putpixel(x + 55, y + 90, BLACK);
	putpixel(x + 56, y + 91, BLACK);
	putpixel(x + 55, y + 91, BLACK);
	putpixel(x + 56, y + 90, BLACK);
	putpixel(x + 69, y + 79, BLACK);
	putpixel(x + 70, y + 79, BLACK);
	putpixel(x + 69, y + 80, BLACK);
	putpixel(x + 70, y + 80, BLACK);
	putpixel(x + 81, y + 45, BLACK);
	putpixel(x + 80, y + 45, BLACK);
	putpixel(x + 81, y + 44, BLACK);
	putpixel(x + 80, y + 44, BLACK);
}
/****************************画柠檬*********************************/
void lemon(int x, int y)
{
	int cmyellow[] = { 77,5,72,7,69,10,64,12,58,12,54,12,48,13,
					41,16,37,18,34,20,30,22,28,25,25,26,23,29,
					21,33,19,36,17,41,15,45,14,51,14,59,13,67,
					15,72,16,78,18,81,21,84,21,87,22,92,26,94,
					29,93,31,91,34,90,37,88,44,87,52,87,58,85,
					66,82,69,79,72,77,74,74,77,71,79,68,80,65,
					82,63,83,60,85,56,85,50,86,44,85,36,84,32,
					82,27,79,23,79,19,82,14,83,10,81,7,77,5,0,0 };

	fun1(x, y, cmyellow);
	setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	drawpoly(57, cmyellow);
	setfillstyle(SOLID_FILL, YELLOW);
	floodfill(x + 56, y + 68, DARKGRAY);
	putpixel(x + 78, y + 34, BLACK);
	putpixel(x + 79, y + 34, BLACK);
	putpixel(x + 78, y + 35, BLACK);
	putpixel(x + 79, y + 35, BLACK);
	putpixel(x + 76, y + 36, BLACK);
	putpixel(x + 77, y + 36, BLACK);
	putpixel(x + 76, y + 37, BLACK);
	putpixel(x + 77, y + 37, BLACK);
	putpixel(x + 57, y + 40, BLACK);
	putpixel(x + 58, y + 40, BLACK);
	putpixel(x + 57, y + 41, BLACK);
	putpixel(x + 58, y + 41, BLACK);
	putpixel(x + 56, y + 44, BLACK);
	putpixel(x + 57, y + 44, BLACK);
	putpixel(x + 56, y + 45, BLACK);
	putpixel(x + 57, y + 45, BLACK);
	putpixel(x + 62, y + 53, BLACK);
	putpixel(x + 63, y + 53, BLACK);
	putpixel(x + 62, y + 54, BLACK);
	putpixel(x + 63, y + 54, BLACK);
	putpixel(x + 57, y + 57, BLACK);
	putpixel(x + 58, y + 57, BLACK);
	putpixel(x + 57, y + 58, BLACK);
	putpixel(x + 58, y + 58, BLACK);
	putpixel(x + 64, y + 65, BLACK);
	putpixel(x + 65, y + 65, BLACK);
	putpixel(x + 64, y + 66, BLACK);
	putpixel(x + 65, y + 66, BLACK);
	putpixel(x + 52, y + 69, BLACK);
	putpixel(x + 53, y + 69, BLACK);
	putpixel(x + 52, y + 70, BLACK);
	putpixel(x + 53, y + 70, BLACK);
	putpixel(x + 61, y + 75, BLACK);
	putpixel(x + 62, y + 75, BLACK);
	putpixel(x + 61, y + 76, BLACK);
	putpixel(x + 62, y + 76, BLACK);
	putpixel(x + 70, y + 41, BLACK);
	putpixel(x + 71, y + 41, BLACK);
	putpixel(x + 70, y + 42, BLACK);
	putpixel(x + 71, y + 42, BLACK);
	putpixel(x + 79, y + 44, BLACK);
	putpixel(x + 80, y + 44, BLACK);
	putpixel(x + 79, y + 45, BLACK);
	putpixel(x + 80, y + 45, BLACK);
	putpixel(x + 81, y + 46, BLACK);
	putpixel(x + 82, y + 46, BLACK);
	putpixel(x + 81, y + 47, BLACK);
	putpixel(x + 82, y + 47, BLACK);
	putpixel(x + 74, y + 47, BLACK);
	putpixel(x + 75, y + 47, BLACK);
	putpixel(x + 74, y + 48, BLACK);
	putpixel(x + 75, y + 48, BLACK);
	putpixel(x + 72, y + 51, BLACK);
	putpixel(x + 73, y + 51, BLACK);
	putpixel(x + 72, y + 52, BLACK);
	putpixel(x + 73, y + 52, BLACK);
	putpixel(x + 69, y + 55, BLACK);
	putpixel(x + 70, y + 55, BLACK);
	putpixel(x + 69, y + 56, BLACK);
	putpixel(x + 70, y + 56, BLACK);
	putpixel(x + 79, y + 57, BLACK);
	putpixel(x + 80, y + 57, BLACK);
	putpixel(x + 79, y + 58, BLACK);
	putpixel(x + 80, y + 58, BLACK);
	putpixel(x + 74, y + 62, BLACK);
	putpixel(x + 75, y + 62, BLACK);
	putpixel(x + 74, y + 63, BLACK);
	putpixel(x + 75, y + 63, BLACK);
	putpixel(x + 67, y + 74, BLACK);
	putpixel(x + 68, y + 74, BLACK);
	putpixel(x + 67, y + 75, BLACK);
	putpixel(x + 68, y + 75, BLACK);
	putpixel(x + 75, y + 66, BLACK);
	putpixel(x + 76, y + 66, BLACK);
	putpixel(x + 75, y + 67, BLACK);
	putpixel(x + 76, y + 67, BLACK);
	putpixel(x + 54, y + 76, BLACK);
	putpixel(x + 55, y + 76, BLACK);
	putpixel(x + 54, y + 77, BLACK);
	putpixel(x + 55, y + 77, BLACK);
	putpixel(x + 57, y + 80, BLACK);
	putpixel(x + 58, y + 80, BLACK);
	putpixel(x + 57, y + 81, BLACK);
	putpixel(x + 58, y + 81, BLACK);
	putpixel(x + 47, y + 78, BLACK);
	putpixel(x + 48, y + 78, BLACK);
	putpixel(x + 47, y + 79, BLACK);
	putpixel(x + 48, y + 79, BLACK);
	putpixel(x + 49, y + 82, BLACK);
	putpixel(x + 50, y + 82, BLACK);
	putpixel(x + 49, y + 83, BLACK);
	putpixel(x + 50, y + 83, BLACK);

}
/*******************画桃子****************************/
void peach(int x, int y)
{
	int cmpink1[] = { 41,12,45,12,49,13,55,14,60,16,
				  66,20,71,23,74,26,77,29,79,34,
				  82,38,82,42,83,43,83,52,82,58,
				  80,63,77,66,75,68,70,71,66,72,
				  62,73,58,74,50,75,45,72,40,69,
				  37,67,35,65,34,62,33,58,32,53,
				  33,47,35,42,36,38,38,35,40,31,
				  41,28,42,24,40,21,38,18,37,15,
				  38,13,41,12,0,0 };
	int cmpink2[] = { 38,18,36,20,33,23,31,26,27,28,
				   24,32,21,35,19,38,17,42,16,46,
				   16,53,17,58,18,62,21,67,24,69,
				   27,72,31,73,35,74,43,74,45,72,40,69,
				  37,67,35,65,34,62,33,58,32,53,
				  33,47,35,42,36,38,38,35,40,31,
				  41,28,42,24,40,21,38,18,0,0 };

	int cmgreen1[] = { 75,68,83,71,88,73,89,74,93,72,
					92,78,89,80,86,82,83,84,80,85,
					76,86,65,87,60,85,58,84,55,82,
					52,80,50,75,58,74,62,73,66,72,70,71,75,68,0,0 };

	int cmgreen2[] = { 50,75,46,79,44,81,41,84,38,85,
					34,86,27,86,26,85,23,85,18,83,
					15,81,10,81,9,82,6,82,5,79,7,77,
					8,73,12,71,15,69,19,68,21,67,24,69,
				   27,72,31,73,35,74,43,74,45,72,50,75,0,0 };

	fun1(x, y, cmpink1);
	fun1(x, y, cmpink2);
	fun1(x, y, cmgreen1);
	fun1(x, y, cmgreen2);
	setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	drawpoly(43, cmpink1);
	setfillstyle(SOLID_FILL, LIGHTRED);
	floodfill(x + 60, y + 50, DARKGRAY);
	drawpoly(36, cmpink2);
	setfillstyle(SOLID_FILL, LIGHTRED);
	floodfill(x + 25, y + 50, DARKGRAY);
	drawpoly(23, cmgreen1);
	setfillstyle(SOLID_FILL, GREEN);
	floodfill(x + 67, y + 81, DARKGRAY);
	drawpoly(29, cmgreen2);
	setfillstyle(SOLID_FILL, GREEN);
	floodfill(x + 30, y + 80, DARKGRAY);
	moveto(x + 51, y + 75);
	lineto(x + 54, y + 75);
	lineto(x + 54, y + 76);
	lineto(x + 57, y + 76);
	lineto(x + 57, y + 77);
	lineto(x + 61, y + 77);
	lineto(x + 61, y + 78);
	lineto(x + 77, y + 78);
	lineto(x + 78, y + 77);
	lineto(x + 83, y + 77);
	moveto(x + 45, y + 74);
	lineto(x + 44, y + 75);
	lineto(x + 41, y + 75);
	lineto(x + 41, y + 76);
	lineto(x + 38, y + 76);
	lineto(x + 37, y + 77);
	lineto(x + 32, y + 77);
	lineto(x + 31, y + 77);
	lineto(x + 24, y + 76);
	lineto(x + 22, y + 75);
	lineto(x + 20, y + 76);
	lineto(x + 17, y + 76);
	lineto(x + 17, y + 77);
	lineto(x + 15, y + 77);
}
/*********************画背景******************/
void bkground()
{
	int u[] = {360,254,365,250,370,249,377,247,384,246,
			   396,246,404,248,408,250,416,254,422,257,
			   428,262,433,265,436,268,441,272,446,275,
			   452,277,456,278,460,277,461,275,458,271,
			   456,274,453,274,449,271,444,266,428,248,
			   417,240,411,234,406,231,400,229,395,228,
			   384,228,377,230,370,235,366,241,363,246,360,254};

	int v[] = {470,267,472,269,477,269,481,267,490,260,
			   506,245,519,234,530,226,540,219,549,214,
			   553,213,563,213,567,215,572,220,574,230,
			   575,246,570,241,566,238,556,236,545,236,
			   532,240,518,248,505,257,494,266,483,272,
			   476,275,472,274,470,271,470,267};

	int m[] = {457,285,454,282,447,280,437,278,427,274,
			   419,270,409,265,402,261,399,258,393,266,
			   392,273,391,281,392,296,397,301,403,304,
			   419,304,425,304,432,303,444,303,457,304,457,286};

	int n[] = {487,302,496,298,507,296,525,291,530,290,
			   539,289,545,287,550,284,555,279,555,268,
			   552,257,549,248,545,242,538,241,530,247,
			   521,254,512,262,503,267,492,272,487,276,
			   484,279,484,286,487,302};

	int a[] = {386,289-1,387,274-1,389,267-1,390,261-1,392,257-1,
			   395,255-1,399,255-1,405,257-1,412,260-1};			   

//嘴	
	int b[] = {385,331,401,334,414,337,433,339,445,341,
			   458,340,478,338,491,335,502,330,514,325,
			   523,319,530,313,537,307,543,304,547,304,
			   551,307,553,310,554,318,552,324,548,329,
			   542,333,535,337,528,340,518,343,504,345,
			   490,347,472,349,444,348,427,346,415,344,
			   404,341,397,338,385,331};
//刀			   
	int c[] = {392,336,332,336,335,343,336,351,337,357,
			   332,366,454,358,450,349};

	int d[] = {454,358,544,348,563,345,579,342,593,339,
			   618,331,626,329,584,326,554,325};	

	int e[] = {550,328,577,329,591,330,604,331,618,332,		   
			   602,339,587,344,579,347,565,349,549,352,
			   533,354,455,363};

	int f[] = {206,332,81,340,70,345,63,349,58,364,
			   56,364,55,372,55,393,56,398,61,403,
			   67,408,73,411,81,415,312,391,323,389,
			   329,389,331,384,324,378};

	int g[] = {204,330,215,335,219,339,223,344,223,350,
			   220,358,213,366,213,372};	

	int h[] = {432,222,429,218,424,214,414,208,410,207,
			   393,207,384,210,374,214,367,220,360,227,
			   357,235,350,243,345,258,341,274,341,302,
			   342,315,346,326,349,334};	

	int i[] = {373,374,382,383,388,388,430,407,444,410,
			   455,410,464,408,480,404,496,404,508,398,
			   518,393,533,379,544,364,551,352};

	int j[] = {563,323,564,317,566,307,566,307,566,281,
			   565,267,562,256,558,244,553,236,538,219,
			   531,213,523,208,512,204,502,202,479,201,
			   470,202};

	int k[] = {454,227,458,221,462,215,466,208,471,198,
			   474,168,474,168,478,151,470,147,460,146,
			   452,147,452,148,464,151,475,152};

	int l[] = {382,226,388,222,396,218,402,216,412,216,
			   420,218,426,222,427,224,439,226,448,228,
			   462,228,472,226,476,223,477,220,473,216,
			   480,214,496,213,505,215,512,219,522,227}	;	

	int q[] = {372,223,367,230,362,237,358,247,354,258,
			   351,271,350,281,350,298,352,313,359,333};

	int p[] = {482,182,486,190,494,192,514,192,524,190,
			   536,186,542,180,549,174,556,162,561,152,
			   567,139,560,146,552,148,539,148,530,151,
			   517,155,509,159,500,164,492,169,486,176,
			   482,182};	

	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL,BROWN);
	bar(0,0,640,480);
	setcolor(BLACK);
	setlinestyle(SOLID_LINE, 0, 3);
	circle(515,279,12);
	circle(429,290,11);	
	drawpoly(21,m);
	drawpoly(23,n);
	drawpoly(9,a);	
	drawpoly(33,b);	
	drawpoly(8,c);	
	drawpoly(9,d);
	drawpoly(18,f);	
	drawpoly(8,g);	
	drawpoly(18,h);	
	drawpoly(14,i);		
	drawpoly(16,j);		
	drawpoly(14,k);		
	drawpoly(20,l);		
	drawpoly(10,q);		
	drawpoly(21,p);		
	ellipse(354,348,0,360,3,2);	
	ellipse(354,348,0,360,12,6);	
	ellipse(305,338,0,360,3,2);	
	ellipse(305,338,0,360,13,8);
	moveto(468,188);
	lineto(468,190);
	lineto(468,192);	
	moveto(468,190);
	lineto(480,188);
	lineto(492,184);	
	lineto(506,180);
	lineto(519,175);
	lineto(533,167);	
	lineto(543,161);
	lineto(555,152);	
	moveto(384,373);
	lineto(388,378);	
	lineto(394,383);	
	lineto(404,388);
	lineto(420,395);	
	moveto(456,202);
	lineto(440,202);	
	lineto(430,203);	
	lineto(410,206);	
	moveto(452,148);
	lineto(458,161);	
	lineto(461,169);	
	lineto(462,182);
	lineto(457,196);
	lineto(448,226);		
	moveto(213,366);
	lineto(333,355);	
	moveto(213,372);
	lineto(333,361);	
	moveto(213,372);
	lineto(83,383);	
	lineto(76,380);	
	lineto(70,377);
	lineto(68,373);
	lineto(66,365);	
	lineto(66,357);	
	lineto(68,347);	
	moveto(456,363);
	lineto(455,359);
	moveto(206,330);
	lineto(245,328);
	lineto(248,332);	
	lineto(254,334);
	lineto(265,335);
	lineto(271,333);	
	lineto(274,331);
	lineto(279,327);
	lineto(322,327);	
	lineto(327,329);	
	lineto(332,336);	
	moveto(331,368);
	lineto(322,370);
	lineto(322,379);
	lineto(455,363);
	moveto(83,387);
	lineto(75,384);
	lineto(69,381);
	lineto(65,378);	
	lineto(69,381);
	lineto(64,378);
	lineto(63,374);	
	lineto(62,368);
	lineto(62,350);		
	moveto(321,370);
	lineto(83,389);
	lineto(82,404);
	lineto(314,384);	
	lineto(320,379);		
	moveto(416,343);
	lineto(417,340);
	moveto(444,347);
	lineto(444,342);	
	moveto(469,347);
	lineto(469,342);
	moveto(488,346);
	lineto(487,339);	
	moveto(507,344);
	lineto(504,333);
	moveto(520,341);
	lineto(517,329);	
	moveto(540,333);
	lineto(534,320);		
	moveto(381,331);
	lineto(378,319);
	lineto(393,328);
	setlinestyle(SOLID_LINE, 0, 1);
	ellipse(354,349,0,360,6,5);	
	ellipse(305,338,0,360,6,5);		
	putpixel(460-2,271+1,BLACK);
	putpixel(460-2,272+1,BLACK);
	putpixel(460-2,273+1,BLACK);
	putpixel(459-2,272+1,BLACK);
	putpixel(461-2,273+1,BLACK);	
	putpixel(461-2,272+1,BLACK);
	putpixel(459-2,273+1,BLACK);	
	putpixel(469,341,BLACK);
	putpixel(417,339,BLACK);
	putpixel(517,328,BLACK);
	putpixel(533,319,BLACK);
	moveto(108+350,434-28);
	lineto(122+350,430-28);	
	lineto(130+350,428-28);	
	lineto(148+350,428-29);
	lineto(158+350,425-30);
	lineto(166+350,420-30);	
	lineto(169+350,418-30);		
	moveto(335,340);
	lineto(396,340);	
	drawpoly(36,u);
	drawpoly(29,v);	
	drawpoly(12,e);
	circle(515,279,7);
	circle(429,290,7);	
	setfillstyle(SOLID_FILL,BLACK);
	floodfill(386,236,BLACK);
	floodfill(459,275,BLACK);
	floodfill(460,273,BLACK);
	floodfill(515,279,BLACK);		
	floodfill(562,227,BLACK);	
	floodfill(429,288,BLACK);		
	floodfill(520,243,BLACK);	
}

void background()
{
	setlinestyle(SOLID_FILL, 0, 1);
	setfillstyle(SOLID_FILL, BROWN);
	bar(0, 50, 639, 479);
	
}
/***************根据参数画水果******************/
void drawfruit(int x, int y, int type)
{

	switch (type)
	{
	case 0: //炸寨
		boom(x, y);
		break;
	case 1: //苹倩
		apple(x, y);
		break;
	case 2: //幕脢
		lemon(x, y);
		break;
	case 3: //讍
		pear(x, y);
		break;
	case 4: //希荻
		banana(x, y);
		break;
	case 5: //覞莓
		strawberry(x, y);
		break;
	case 6: //虙讚
		peach(x, y);
		break;
	case 7: //畏購
		watermelon(x, y);
		break;
	}
}
/******************************************
画按钮
9.8
传入参数：Button 结构体
******************************************/
void drawbutton(Button* b)
{
	switch (b->status)
	{
	case 0:
		setcolor(BLACK);
		setlinestyle(SOLID_LINE, 0, 3);
		rectangle(b->x1, b->y1, b->x2, b->y2);
		setcolor(b->btcolor1 + 8);
		//setlinestyle(SOLID_LINE,0,1);
		line(b->x1 + 1, b->y1 + 1, b->x2 - 1, b->y1 + 1);
		line(b->x1 + 1, b->y1 + 1, b->x1 + 1, b->y2 - 1);
		setcolor(DARKGRAY);
		line(b->x2 - 1, b->y1 + 2, b->x2 - 1, b->y2 - 1);
		line(b->x1 + 2, b->y2 - 1, b->x2 - 1, b->y2 - 1);
		setfillstyle(SOLID_FILL, b->btcolor1);
		bar(b->x1 + 2, b->y1 + 2, b->x2 - 2, b->y2 - 2);
		break;
	case 1:
		setcolor(WHITE);
		setlinestyle(SOLID_LINE, 0, 3);
		rectangle(b->x1, b->y1, b->x2, b->y2);
		setcolor(DARKGRAY);
		//setlinestyle(SOLID_LINE,0,1);
		line(b->x1 + 1, b->y1 + 1, b->x2 - 1, b->y1 + 1);
		line(b->x1 + 1, b->y1 + 1, b->x1 + 1, b->y2 - 1);
		setcolor(b->btcolor2 + 8);
		line(b->x2 - 1, b->y1 + 2, b->x2 - 1, b->y2 - 1);
		line(b->x1 + 2, b->y2 - 1, b->x2 - 1, b->y2 - 1);
		setfillstyle(SOLID_FILL, b->btcolor2);
		bar(b->x1 + 2, b->y1 + 2, b->x2 - 2, b->y2 - 2);
		break;
	case 2:
		setcolor(WHITE);
		setlinestyle(SOLID_LINE, 0, 3);
		rectangle(b->x1, b->y1, b->x2, b->y2);
		setcolor(b->btcolor2 + 8);
		//setlinestyle(SOLID_LINE,0,1);
		line(b->x1 + 1, b->y1 + 1, b->x2 - 1, b->y1 + 1);
		line(b->x1 + 1, b->y1 + 1, b->x1 + 1, b->y2 - 1);
		setcolor(DARKGRAY);
		line(b->x2 - 1, b->y1 + 2, b->x2 - 1, b->y2 - 1);
		line(b->x1 + 2, b->y2 - 1, b->x2 - 1, b->y2 - 1);
		setfillstyle(SOLID_FILL, b->btcolor2);
		bar(b->x1 + 2, b->y1 + 2, b->x2 - 2, b->y2 - 2);
		break;
	}
}
/***************************画退出按钮********************/
void draw_exit_button(int i)
{
	Button button;
	button.x1 = 10;
	button.x2 = 50;
	button.y1 = 455;
	button.y2 = 475;
	button.status = i;
	button.btcolor1 = LIGHTGRAY;
	button.btcolor2 = GREEN;
	drawbutton(&button);
	if (i == 0)
	{
		puthz(14, 458, "退出", 16, 16, BLACK);
	}
	else {
		puthz(14, 458, "退出", 16, 16, WHITE);
	}
}

/*****************************
 实现输入框线的显示，消逝效果
*****************************/
void SetPixel(int x, int y, int color)
{

	color ^= getpixel(x, y);
	putpixel(x, y, color);
}
/*************绘制输入框线*************/
void VLine(int x, int y1, int y2)
{
	int i;
	for (i = y1; i <= y2; i++)
	{
		SetPixel(x, i, CYAN);
	}
}
/************************暂停按钮*****************************/
void draw_pause_button(int i)
{
	Button button1, button2;
	button1.x1 = 10;
	button1.x2 = 20;
	button1.y1 = 10;
	button1.y2 = 40;
	button1.status = i;
	button1.btcolor1 = LIGHTGRAY;
	button1.btcolor2 = GREEN;
	button2.x1 = 25;
	button2.x2 = 35;
	button2.y1 = 10;
	button2.y2 = 40;
	button2.status = i;
	button2.btcolor1 = LIGHTGRAY;
	button2.btcolor2 = GREEN;
	drawbutton(&button1);
	drawbutton(&button2);
}

/***********************画生命****************************/
void life(int i)
{
	int life1[] = { 620,44,637,33,629,24,638,17,628,4,
			 615,11,606,2,593,9,600,18,591,24,
			 602,38,612,31,620,44,0,0 };
	int life2[] = { 561,1,554,7,561,13,552,20,563,29,
			 571,24,578,33,590,23,583,17,591,11,
			 581,1,571,7,561,1,0,0 };
	int life3[] = { 541,1,534,6,526,1,521,7,526,12,
			 522,16,531,24,536,19,543,24,550,16,
			 545,12,549,6,541,1,0,0 };
	setcolor(8);
	setlinestyle(SOLID_LINE, 0, 3);
	drawpoly(13, life1);
	drawpoly(13, life2);
	drawpoly(13, life3);
	switch (i)
	{
	case 0:
		setfillstyle(SOLID_FILL, BROWN);
		floodfill(614, 22, 8);
		floodfill(574, 17, 8);
		floodfill(536, 14, 8);
		break;
	case 1:
		setfillstyle(SOLID_FILL, BROWN);
		floodfill(614, 22, 8);
		floodfill(574, 17, 8);
		setfillstyle(SOLID_FILL, RED);
		floodfill(536, 14, 8);
		break;
	case 2:
		setfillstyle(SOLID_FILL, BROWN);
		floodfill(614, 22, 8);
		setfillstyle(SOLID_FILL, RED);
		floodfill(574, 17, 8);
		floodfill(536, 14, 8);
		break;
	case 3:
		setfillstyle(SOLID_FILL, RED);
		floodfill(614, 22, 8);
		floodfill(574, 17, 8);
		floodfill(536, 14, 8);
		break;
	}
}

