/**************************************************************
Filename：ach.c   Author: 李天依   Version:1.0   Date:10.19
Description:该文件包含了成就界面的相关函数
Function List:
	1.ach_main//成就页面的”主函数“，负责调用其他函数
	2.page3_screen//成就页面的画图函数
	3.ach_judge//成就判断函数
	4.put_ach//将成就名一一写出
History： 10.22写注释
<author>  <time> <version> <desc>
李天依    19/10/19  1.0    build this module
***************************************************************/
#include"common.h"
#include"ach.h"
/**************************************************************
Function:ach_main
Description:成就页面的”主函数“，负责调用其他函数
Calls:
	 1.page3_screen
	 2.MouseOn
	 3.MouseStatus
	 4.mouse_press
	 5.draw_exit_button
Input:User0 *user
Return:page
Others:
***************************************************************/
int ach_main(User0* user)
{
	int page = 3;
	int ach_page = 1;//成就页，共五页
	int i;//计数
	int exit_status = 0;//退出按钮的状态
	Button ach_button[20];//每一个成就


	MouseOff();
	delay(100);
	/*初始化每个按钮，并将用户信息显现出来*/

	for (i = 0; i < 20; i++)
	{
		ach_button[i].x1 = 50;
		ach_button[i].y1 = 110 + 90 * (i % 4);
		ach_button[i].x2 = 590;
		ach_button[i].y2 = 110 + 90 * (i % 4) + 70;
		ach_button[i].status = 0;
		if ((*user).ach[i] == 1)
		{
			ach_button[i].btcolor1 = GREEN;
		}
		else {
			ach_button[i].btcolor1 = LIGHTGRAY;
		}
	}
	change_achscore(user);
	page3_screen(ach_button, ach_page, user);
	MouseOn(MouseX,MouseY);

	while (page == 3)
	{
		MouseStatus();
		/******************退出按钮模块*******************************/
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
		/*********************翻页模块****************************/
		if (mouse_press(525, 454, 545, 476) == 1)
		{
			if (ach_page > 1)
			{
				ach_page--;
				page3_screen(ach_button, ach_page, user);
				MouseOn(MouseX, MouseY);
			}
			delay(150);
		}
		if (mouse_press(603, 454, 623, 476) == 1)
		{
			if (ach_page < 5)
			{
				ach_page++;
				page3_screen(ach_button, ach_page, user);
				MouseOn(MouseX, MouseY);
			}
			delay(150);
		}

	}
	ach_page = 1;
	return page;
}

/**************************************************************
Function:page3_screen
Description:成就页面的画图函数
Calls:
	 1.put_ach
Input:Button *button,int ach_page,User0 *user
Return:无
Others李天依  2019.9.19
***************************************************************/
void page3_screen(Button* button, int ach_page, User0* user)
{
	int i;
	char ach_page_num[2];//页数
	int r_trg[] = { 603,454,603,476,623,465,603,454 };
	int l_trg[] = { 545,454,545,476,525,465,545,454 };
	char ach_score[5];

	cleardevice();
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL, BROWN);
	bar(0, 0, 640, 480);
	setfillstyle(SOLID_FILL, WHITE);
	setcolor(BLACK);
	drawpoly(4, r_trg);
	drawpoly(4, l_trg);
	floodfill(610, 460, BLACK);
	floodfill(540, 460, BLACK);

	settextstyle(0, HORIZ_DIR, 2);
	setcolor(WHITE);
	itoa(ach_page, ach_page_num, 10);
	outtextxy(550, 460, ach_page_num);
	outtextxy(565, 460, "/");
	outtextxy(580, 460, "5");
	draw_exit_button(0);
	puthz(250, 20, "成就", 48, 96, WHITE);

	for (i = (ach_page - 1) * 4; i < (ach_page - 1) * 4 + 4; i++)
	{
		drawbutton(button + i);
	}

	put_ach(ach_page, user);
	setcolor(WHITE);
	settextstyle(0, 0, 3);
	itoa(user->score[2], ach_score, 10);
	outtextxy(580, 10, ach_score);
}

/**************************************************************
Function: ach_judge
Description:成就判断函数
Calls:
	 1.put_ach
Input:User0 *user,int ap（苹果数）,int ba（香蕉数）,int wa（西瓜数 ）,int score
Return:new_ach（新完成的成就）
Others：
1.切到第一个水果
2.得到50分
3.得到100分
4.总共切掉150个水果
5.总共切掉500个水果
6.总共切掉1000个水果
7.一局游戏切到11个苹果
8.一局游戏切到22个香蕉
9.一局游戏切到33个西瓜
10.取得一个和你最高分数相同的分数
***************************************************************/
int  ach_judge(User0* user, int ap, int ba, int wa, int score)
{
	int new_ach = 0;

	if (score > 0)
	{
		if (user->ach[0] == 0)
		{
			new_ach++;
		}
		user->ach[0] = 1;
	}

	if (score >= 50)
	{
		if (user->ach[1] == 0)
		{
			new_ach++;
		}
		user->ach[1] = 1;
	}

	if (score >= 100)
	{
		if (user->ach[2] == 0)
		{
			new_ach++;
		}
		user->ach[2] = 1;
	}

	if (user->total_fruits >= 150)
	{
		if (user->ach[3] == 0)
		{
			new_ach++;
		}
		user->ach[3] = 1;
	}

	if (user->total_fruits >= 500)
	{
		if (user->ach[4] == 0)
		{
			new_ach++;
		}
		user->ach[4] = 1;
	}

	if (user->total_fruits >= 1000)
	{
		if (user->ach[5] == 0)
		{
			new_ach++;
		}
		user->ach[5] = 1;
	}

	if (ap == 11)
	{
		if (user->ach[6] == 0)
		{
			new_ach++;
		}
		user->ach[6] = 1;
	}

	if (ba == 22)
	{
		if (user->ach[7] == 0)
		{
			new_ach++;
		}
		user->ach[7] = 1;
	}

	if (wa == 33)
	{
		if (user->ach[8] == 0)
		{
			new_ach++;
		}
		user->ach[8] = 1;
	}

	if (score == user->score[0] && score != 0)
	{
		if (user->ach[9] == 0)
		{
			new_ach++;
		}
		user->ach[9] = 1;
	}

	return new_ach;
}
/**************************************************************
Function: ach_judge2
Description:成就判断函数
Calls:
	 1.put_ach
Input:User0* user, int ap, int ba, int wa, int bo, int st, int le, int peach, int pear, int score
Return:new_ach（新完成的成就）
Others：
11.街机模式切到十个炸弹
12.街机模式得到50分
13.街机模式得到100分
14.街机模式每种水果以及炸弹都切到一次
15.每把刀都体验一次
16.查看一次开发日志
***************************************************************/
int  ach_judge2(User0* user, int ap, int ba, int wa, int bo, int st, int le, int peach, int pear, int score)
{
	int new_ach;
	if (bo == 10)
	{
		if (user->ach[10] == 0)
		{
			new_ach++;
		}
		user->ach[10] = 1;
	}
	if (score >= 50)
	{
		if (user->ach[11] == 0)
		{
			new_ach++;
		}
		user->ach[11] = 1;
	}

	if (score >= 100)
	{
		if (user->ach[12] == 0)
		{
			new_ach++;
		}
		user->ach[12] = 1;
	}
	if (ap >= 1 && bo >= 1 && pear >= 1 && peach >= 1 && le >= 1 && wa >= 1 && st >= 1 && ba >= 1)
	{
		if (user->ach[13] == 0)
		{
			new_ach++;
		}
		user->ach[13] = 1;
	}
	return new_ach;
}

/**************************************************************
Function: put_ach
Description:将成就名一一写出
Calls:
Input:int ach_page,User0 *user
Return:new_ach（新完成的成就）
Others：
***************************************************************/
void put_ach(int ach_page, User0* user)
{
	switch (ach_page)
	{
	case 1://第一页
		//成就1
		if (user->ach[0] == 1)
		{
			puthz(252, 120, "初出茅庐", 32, 32, WHITE);
			puthz(260, 160, "切到第一个水果", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 130, "5");
		}
		else
		{
			puthz(252, 120, "初出茅庐", 32, 32, BLACK);
			puthz(260, 160, "切到第一个水果", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 130, "5");
		}
		//成就2
		if (user->ach[1] == 1)
		{
			puthz(252, 210, "小试牛刀", 32, 32, WHITE);
			puthz(280, 250, "得到五十分", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}
		else {
			puthz(252, 210, "小试牛刀", 32, 32, BLACK);
			puthz(280, 250, "得到五十分", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}

		if (user->ach[2] == 1)
		{
			puthz(252, 300, "游刃有余", 32, 32, WHITE);
			puthz(280, 340, "得到一百分", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 310, "10");
		}
		else {
			puthz(252, 300, "游刃有余", 32, 32, BLACK);
			puthz(280, 340, "得到一百分", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 310, "10");
		}

		if (user->ach[3] == 1)
		{
			puthz(252, 390, "水果沙拉", 32, 32, WHITE);
			puthz(240, 430, "总共切掉一百五十个水果", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		else {
			puthz(252, 390, "水果沙拉", 32, 32, BLACK);
			puthz(240, 430, "总共切掉一百五十个水果", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		break;

	case 2:
		if (user->ach[4] == 1)
		{
			puthz(252, 120, "水果大师", 32, 32, WHITE);
			puthz(250, 160, "总共切掉五百个水果", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}
		else
		{
			puthz(252, 120, "水果大师", 32, 32, BLACK);
			puthz(250, 160, "总共切掉五百个水果", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}

		if (user->ach[5] == 1)
		{
			puthz(252, 210, "水果杀手", 32, 32, WHITE);
			puthz(250, 250, "总共切掉一千个水果", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 220, "20");
		}
		else {
			puthz(252, 210, "水果杀手", 32, 32, BLACK);
			puthz(250, 250, "总共切掉一千个水果", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 220, "20");
		}

		if (user->ach[6] == 1)
		{
			puthz(265, 300, "红果果", 32, 32, WHITE);
			puthz(235, 340, "一局游戏切到十一个苹果", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}
		else {
			puthz(265, 300, "红果果", 32, 32, BLACK);
			puthz(235, 340, "一局游戏切到十一个苹果", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}
		if (user->ach[7] == 1)
		{
			puthz(265, 390, "香蕉君", 32, 32, WHITE);
			puthz(230, 430, "一局游戏切到二十二个香蕉", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		else {
			puthz(265, 390, "香蕉君", 32, 32, BLACK);
			puthz(230, 430, "一局游戏切到二十二个香蕉", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		break;

	case 3:
		if (user->ach[8] == 1)
		{
			puthz(252, 120, "吃瓜群众", 32, 32, WHITE);
			puthz(230, 160, "一局游戏切到三十三个西瓜", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}
		else {
			puthz(252, 120, "吃瓜群众", 32, 32, BLACK);
			puthz(230, 160, "一局游戏切到三十三个西瓜", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}

		if (user->ach[9] == 1)
		{
			puthz(252, 210, "似曾相识", 32, 32, WHITE);
			puthz(220, 250, "取得一个和你最高分数相同的分数", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 220, "20");
		}
		else {
			puthz(252, 210, "似曾相识", 32, 32, BLACK);
			puthz(220, 250, "取得一个和你最高分数相同的分数", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 220, "20");
		}

		if (user->ach[10] == 1)
		{
			puthz(252, 300, "拆弹专家", 32, 32, WHITE);
			puthz(230, 340, "街机模式切到十个炸弹", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}
		else {
			puthz(252, 300, "拆弹专家", 32, 32, BLACK);
			puthz(230, 340, "街机模式切到十个炸弹", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}

		if (user->ach[11] == 1)
		{
			puthz(252, 390, "初试街机", 32, 32, WHITE);
			puthz(240, 430, "街机模式得到五十分", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		else {
			puthz(252, 390, "初试街机", 32, 32, BLACK);
			puthz(240, 430, "街机模式得到五十分", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		break;

	case 4:

		if (user->ach[12] == 1)
		{
			puthz(252, 120, "街机达人", 32, 32, WHITE);
			puthz(240, 160, "街机模式得到一百分", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}
		else {
			puthz(252, 120, "街机达人", 32, 32, BLACK);
			puthz(240, 160, "街机模式得到一百分", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}

		if (user->ach[13] == 1)
		{
			puthz(252, 210, "大杂烩", 32, 32, WHITE);
			puthz(200, 250, "街机模式每种水果以及炸弹都切到一次", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}
		else {
			puthz(252, 210, "大杂烩", 32, 32, BLACK);
			puthz(200, 250, "街机模式每种水果以及炸弹都切到一次", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}

		if (user->ach[14] == 1)
		{
			puthz(260, 300, "刀客", 32, 32, WHITE);
			puthz(230, 340, "体验一次其他刀具", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}
		else {
			puthz(260, 300, "刀客", 32, 32, BLACK);
			puthz(230, 340, "体验一次其他刀具", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}

		if (user->ach[15] == 1)
		{
			puthz(252, 390, "好奇心", 32, 32, WHITE);
			puthz(230, 430, "查看一次开发日志", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		else {
			puthz(252, 390, "好奇心", 32, 32, BLACK);
			puthz(230, 430, "查看一次开发日志", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		break;
		
	case 5:
		if (user->ach[16] == 1)
		{
			puthz(252, 120, "小小忍者", 32, 32, WHITE);
			//puthz(240, 160, "街机模式得到一百分", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}
		else {
			puthz(252, 120, "小小忍者", 32, 32, BLACK);
			//puthz(240, 160, "街机模式得到一百分", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}

		if (user->ach[17] == 1)
		{
			puthz(252, 210, "大大大", 32, 32, WHITE);
			//puthz(200, 250, "街机模式每种水果以及炸弹都切到一次", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}
		else {
			puthz(252, 210, "大大大", 32, 32, BLACK);
			//puthz(200, 250, "街机模式每种水果以及炸弹都切到一次", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}

		if (user->ach[18] == 1)
		{
			puthz(260, 300, "剑客", 32, 32, WHITE);
			//puthz(230, 340, "体验一次其他刀具", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}
		else {
			puthz(260, 300, "剑客", 32, 32, BLACK);
			//puthz(230, 340, "体验一次其他刀具", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}

		if (user->ach[19] == 1)
		{
			puthz(252, 390, "好胜心", 32, 32, WHITE);
			//puthz(230, 430, "查看一次开发日志", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		else {
			puthz(252, 390, "好胜心", 32, 32, BLACK);
			//puthz(230, 430, "查看一次开发日志", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		break;
	}
}
/**************************************************************
Function: change_achscore
Description:改变结构体里的分数
Calls:
Input:User0 *user
Return:
Others：
***************************************************************/
void change_achscore(User0 *user)
{
		int i;
		user->score[2] = 0;
		for (i = 0; i < 20; i++)
		{
			user->score[2] = user->score[2] + user->ach[i] * 5;
		}
		if (user->ach[2] == 1)
		{
			user->score[2] = user->score[2] + 5;
		}
		if (user->ach[4] == 1)
		{
			user->score[2] = user->score[2] + 5;
		}
		if (user->ach[8] == 1)
		{
			user->score[2] = user->score[2] + 5;
		}
		if (user->ach[12] == 1)
		{
			user->score[2] = user->score[2] + 5;
		}
		if (user->ach[5] == 1)
		{
			user->score[2] = user->score[2] + 15;
		}
		if (user->ach[9] == 1)
		{
			user->score[2] = user->score[2] + 15;
		}
}







