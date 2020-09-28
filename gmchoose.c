/**************************************************************
Filename：gamechoose.c  Author: 李天依   Version:1.0   Date:10.19
Description:该文件包含了选择页面的相关函数
Function List:
       1.int game_choose()
History： 10.22写注释
<author>  <time> <version> <desc>
李天依    19/10/19  1.0    build this module
***************************************************************/
#include"common.h"
#include"gmchoose.h"
/**************************************************************
Function: ach_judge
Description:游戏选择函数
Calls:drawbutton
Input:
Return:page
Others：
***************************************************************/
int  game_choose()
{
	int page = 1;
	Button game1_button, game2_button;
	int exit_status = 0;//退出按钮的状态

	game1_button.x1 = 100;
	game1_button.x2 = 300;
	game1_button.y1 = 100;
	game1_button.y2 = 400;
	game1_button.status = 0;
	game1_button.btcolor1 = LIGHTGRAY;
	game1_button.btcolor2 = GREEN;

	game2_button.x1 = 340;
	game2_button.x2 = 540;
	game2_button.y1 = 100;
	game2_button.y2 = 400;
	game2_button.status = 0;
	game2_button.btcolor1 = LIGHTGRAY;
	game2_button.btcolor2 = GREEN;

	cleardevice();

	setbkcolor(BLACK);

	setfillstyle(SOLID_FILL, BROWN);
	bar(0, 0, 640, 480);
	drawbutton(&game1_button);
	puthz(140, 180, "经典", 48, 80, WHITE);
	puthz(140, 270, "模式", 48, 80, WHITE);
	drawbutton(&game2_button);
	puthz(380, 180, "街机", 48, 80, WHITE);
	puthz(380, 270, "模式", 48, 80, WHITE);
	draw_exit_button(0);
	while (page == 1)
	{
		MouseStatus();
		if (mouse_press(100, 100, 300, 400) == 2)
		{
			if (game1_button.status != 2)
			{
				MouseOff();
				game1_button.status = 2;
				drawbutton(&game1_button);
				puthz(140, 180, "经典", 48, 80, WHITE);
				puthz(140, 270, "模式", 48, 80, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(100, 100, 300, 400) == 1)
		{
			MouseOff();
			game1_button.status = 1;
			drawbutton(&game1_button);
			puthz(140, 180, "经典", 48, 80, WHITE);
			puthz(140, 270, "模式", 48, 80, WHITE);
			MouseOn(MouseX, MouseY);
			delay(100);
			page = 5;

		}
		if (mouse_press(100, 100, 300, 400) == 0)
		{
			if (game1_button.status != 0)
			{
				MouseOff();
				game1_button.status = 0;
				drawbutton(&game1_button);
				puthz(140, 180, "经典", 48, 80, BLACK);
				puthz(140, 270, "模式", 48, 80, BLACK);
				MouseOn(MouseX, MouseY);
			}
		}

		if (mouse_press(340, 100, 540, 400) == 2)
		{
			if (game2_button.status != 2)
			{
				MouseOff();
				game2_button.status = 2;
				drawbutton(&game2_button);
				puthz(380, 180, "街机", 48, 80, WHITE);
				puthz(380, 270, "模式", 48, 80, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(340, 100, 540, 400) == 1)
		{
			MouseOff();
			game2_button.status = 1;
			drawbutton(&game2_button);
			puthz(380, 180, "街机", 48, 80, WHITE);
			puthz(380, 270, "模式", 48, 80, WHITE);
			MouseOn(MouseX, MouseY);
			delay(100);
			page = 6;
		}
		if (mouse_press(340, 100, 540, 400) == 0)
		{
			if (game2_button.status != 0)
			{
				MouseOff();
				game2_button.status = 0;
				drawbutton(&game2_button);
				puthz(380, 180, "街机", 48, 80, BLACK);
				puthz(380, 270, "模式", 48, 80, BLACK);
				MouseOn(MouseX, MouseY);
			}
		}

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
	}
	return page;
}