
/**************************************************************
Filename：option.c  Author: 李天依   Version:1.0   Date:10.19
Description:该文件包含了关于鼠标的相关函数
Function List:
       1.int opions_page(User0* u)  //选项界面主函数
	   2. void options_screen(void)  //画选项界面
History： 10.22写注释
<author>  <time> <version> <desc>
李天依    19/10/19  1.0    build this module
***************************************************************/
#include"common.h"
#include"options.h"
int opions_page(User0* u)
{
	// int mouse_draw[16][16] =
	// {
	// 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 1, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 2, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3,
	// 1, 2, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 1, 3, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 1, 3, 3, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3,
	// 3, 3, 3, 3, 3, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3,
	// 3, 3, 3, 3, 3, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3,
	// 3, 3, 3, 3, 3, 3, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3
	// };

	// int sword[16][16] =
	// {
	// 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 1, 1, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 1, 1, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 3, 1, 1, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	// 3, 3, 1, 1, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3,
	// 3, 3, 3, 1, 1, 2, 2, 1, 1, 3, 3, 1, 1, 3, 3, 3,
	// 3, 3, 3, 3, 1, 1, 2, 2, 1, 1, 1, 1, 1, 3, 3, 3,
	// 3, 3, 3, 3, 3, 1, 1, 2, 2, 1, 1, 1, 3, 3, 3, 3,
	// 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
	// 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 2, 1, 1, 3, 3, 3,
	// 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 2, 2, 1, 1, 3, 3,
	// 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 1, 2, 2, 1, 1, 3,
	// 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 2, 1, 3,
	// 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1,
	// 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3
	// };
	// int sword1[25][25] =
	// {
	// 1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	// 1,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	// 1,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	// 1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	// 3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	// 3,3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	// 3,3,3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	// 3,3,3,3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	// 3,3,3,3,3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
	// 3,3,3,3,3,3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,1,1,3,3,3,
	// 3,3,3,3,3,3,3,1,2,2,1,2,2,1,3,3,3,3,3,1,1,3,3,3,3,
	// 3,3,3,3,3,3,3,3,1,2,2,1,2,2,1,3,3,3,1,1,3,3,3,3,3,
	// 3,3,3,3,3,3,3,3,3,1,2,2,1,2,2,1,3,1,1,3,3,3,3,3,3,
	// 3,3,3,3,3,3,3,3,3,3,1,2,2,1,2,2,1,1,3,3,3,3,3,3,3,
	// 3,3,3,3,3,3,3,3,3,3,3,1,2,2,1,1,2,1,3,3,3,3,3,3,3,
	// 3,3,3,3,3,3,3,3,3,3,3,3,1,2,1,2,2,1,3,3,3,3,3,3,3,
	// 3,3,3,3,3,3,3,3,3,3,3,3,3,1,2,2,2,2,1,3,3,3,3,3,3,
	// 3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,2,2,2,1,3,3,3,3,3,
	// 3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,1,2,2,2,1,3,3,3,3,
	// 3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,1,2,2,1,1,3,3,3,
	// 3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,1,1,1,1,1,3,3,
	// 3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,3,3,3,1,1,1,1,3,3,
	// 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,3,3,
	// 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	// 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	// };
	int exit_status = 0;//退出按钮的状态
	int page = 4;
	int n = u->fn;
	int m = u->mouse_type;
	char fn[3];

	Button log_button;
	log_button.x1 = 430;
	log_button.x2 = 520;
	log_button.y1 = 365;
	log_button.y2 = 395;
	log_button.status = 0;
	log_button.btcolor1 = LIGHTGRAY;
	log_button.btcolor2 = GREEN;


	MouseOff();
	delay(100);
	options_screen();
	MouseOn(MouseX, MouseY);
	itoa(n, fn, 10);
	settextstyle(0, HORIZ_DIR, 2);
	setcolor(WHITE);
	outtextxy(470, 130, fn);
	DrawSword(470, 210, m);
	drawbutton(&log_button);
	puthz(450, 368, "查看", 24, 24, BLACK);
	while (page == 4)
	{
		MouseStatus();
		/*退出按钮模块*/
		if (mouse_press(10, 455, 50, 475) == 2)
		{
			if (exit_status != 2)
			{
				MouseOff();
				draw_exit_button(2);
				MouseOn(MouseX, MouseY);
				exit_status = 2;
			}
		}
		if (mouse_press(10, 455, 50, 475) == 1)
		{
			draw_exit_button(1);
			delay(200);
			page = 0;
			exit_status = 1;
		}
		if (mouse_press(0, 435, 50, 475) == 0)
		{
			if (exit_status != 0)
			{
				draw_exit_button(0);
				exit_status = 0;
			}
		}
		/*日志*/
		if (mouse_press(425, 355, 515, 395) == 2)
		{
			if (log_button.status != 2)
			{
				MouseOff();
				log_button.status = 2;
				drawbutton(&log_button);
				puthz(450, 368, "查看", 24, 24, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(425, 355, 515, 395) == 1)
		{
			MouseOff();
			log_button.status = 1;
			drawbutton(&log_button);
			puthz(450, 368, "查看", 24, 24, WHITE);
			MouseOn(MouseX, MouseY);
			delay(100);
			u->ach[15] = 1;
			page = 7;
		}
		if (mouse_press(425, 355, 515, 395) == 0)
		{
			if (log_button.status != 0)
			{
				MouseOff();
				log_button.status = 0;
				drawbutton(&log_button);
				puthz(450, 368, "查看", 24, 24, BLACK);
				MouseOn(MouseX, MouseY);
			}
		}

		if (mouse_press(430, 125, 450, 145) == 1)
		{
			if (n > 3)
			{
				n--;
				u->fn = n;
				setfillstyle(SOLID_FILL, LIGHTBLUE);
				bar(450, 125, 500, 145);
				setcolor(WHITE);
				itoa(n, fn, 10);
				outtextxy(470, 130, fn);
			}
			delay(150);
		}
		if (mouse_press(500, 125, 520, 145) == 1)
		{

			if (n < 5)
			{
				n++;
				u->fn = n;
				setfillstyle(SOLID_FILL, LIGHTBLUE);
				bar(450, 125, 500, 145);
				setcolor(WHITE);
				itoa(n, fn, 10);
				outtextxy(470, 130, fn);
			}
			delay(150);
		}

		if (mouse_press(430, 207, 450, 227) == 1)
		{

			if (m > 1)
			{
				u->ach[14] = 1;
				m--;
				u->mouse_type = m;
				setfillstyle(SOLID_FILL, YELLOW);
				bar(451, 207, 499, 237);
				DrawSword(470, 210, m);
			}
			delay(150);
		}
		if (mouse_press(500, 207, 520, 227) == 1)
		{

			if (m < 3)
			{
				u->ach[14] = 1;
				m++;
				u->mouse_type = m;
				setfillstyle(SOLID_FILL, YELLOW);
				bar(451, 207, 499, 237);
				DrawSword(470, 210, m);
			}
			delay(150);
		}

		//开发日记模块
	}
	return page;
}
void options_screen(void)
{
	int v1[] = { 450,125,450,145,430,135,450,125 };
	int u1[] = { 500,125,500,145,520,135,500,125 };

	int v2[] = { 450,207,450,227,430,217,450,207 };
	int u2[] = { 500,207,500,227,520,217,500,207 };


	cleardevice();

	setbkcolor(BLACK);

	setfillstyle(SOLID_FILL, BROWN);
	bar(0, 0, 640, 480);
	puthz(250, 20, "选项", 48, 96, WHITE);
	setfillstyle(SOLID_FILL, BLACK);
	bar(98, 88, 542, 420);
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	bar(100, 90, 540, 418);
	setlinestyle(0, 0, 1);
	setcolor(BLACK);
	line(100, 171, 540, 171);
	line(100, 172, 540, 172);
	line(100, 253, 540, 253);
	line(100, 254, 540, 254);
	line(100, 335, 540, 335);
	line(100, 336, 540, 336);
	setfillstyle(SOLID_FILL, YELLOW);
	floodfill(120, 200, BLACK);
	floodfill(120, 350, BLACK);


	puthz(120, 120, "最大水果数", 32, 32, WHITE);
	puthz(120, 200, "刀具选择", 32, 32, BLACK);
	puthz(120, 280, "游戏提示", 32, 32, WHITE);
	puthz(120, 365, "开发日志", 32, 32, BLACK);
	puthz(320, 285, "按下鼠标滑动切水果", 24, 24, WHITE);

	drawpoly(4, v1);
	drawpoly(4, u1);
	drawpoly(4, v2);
	drawpoly(4, u2);

	setfillstyle(SOLID_FILL, WHITE);
	floodfill(440, 135, BLACK);
	floodfill(510, 135, BLACK);
	floodfill(440, 217, BLACK);
	floodfill(510, 217, BLACK);

	draw_exit_button(0);

}
