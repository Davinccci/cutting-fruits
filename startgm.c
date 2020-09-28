/**************************************************************
Filename��startgame.c    Author: ������   Version:1.0   Date:10.19
Description:���ļ���������ͨģʽ����غ���
Function List:
	   1int normal_game(User0* user)    //��ͨģʽ����Ҫʵ�ֺ���
	   2.void Mouse_judge(FRUIT* f, int n, int* s, int* pend, int* ap, int* ba, int* wa, int* mx, int* my, int* comboshow_times)  //�ж��Ƿ���������У��ӷֲ�����ˮ����������ը������Ϸ����
	   3.int fruit_judge(FRUIT* f, int n, int* pdrop)//�ж�һ���Ƿ���������ж��Ƿ����
	   4.int  pause(int score)  //��ͣ
	   5.int  gameover(int score) //��Ϸ����
	   6.int if_crossing(int incenterX, int incenterY, int r, int x1, int y1, int x2, int y2)  //�ж����켣���Ƿ���ˮ���ཻ
	   7.  void combo_judge(int* comboshow_times)     //�ж�����
	   History�� 10.22дע��
<author>  <time> <version> <desc>
������    19/10/19  1.0    build this module
***************************************************************/
#include"common.h"
#include"startgm.h"
int normal_game(User0* user)
{
	FILE* fp;  //�ļ�ָ��
	int i;
	int page = 5;

	int scratch_status = 1;   //��껮��״̬
	int comboshow_times[4] = { 0,0,0,0 };  //�����ı��������
	int p[SCRATCH];            //���ץ�۵ĳ���
	int N = user->fn;            //ˮ������
       
	unsigned s;                 //��ͣʱ�汳���Ĵ�С            
	char filename[30] = "users0\\";   
	void* pauseimage = NULL;      //��ͣʱ������ָ��
	int score = 0;               //�÷�
	int drop = 0;                //����ˮ����
	int pause_status = 0;    //��ͣ��ť��״̬
	char now_score[5];                      //��ǰ����
	char topscore[5];               //��߷�
	int end = 0;                      // ����״̬

	int ap = 0;                       //ƻ�� 
	int ba = 0 ;                      //�㽶
	int wa = 0;                     //����

	int mx = -1;                     //�����һλ�õ�x����
	int my = -1;                     //�����һλ�õ�y����

	FRUIT fruit1[8];                  //��ˮ��
	FRUIT* fruit2 = (FRUIT*)malloc(N * sizeof(FRUIT)); //Ҫ����ˮ��

	fruit1_init(fruit1, 8);           
	for (i = 0; i < SCRATCH - 1; i++)
	{
		p[i] = -1;
	}

	background();
	setfillstyle(SOLID_FILL, BROWN);
	bar(300, 10, 370, 30);
	setcolor(WHITE);
	settextstyle(0, 0, 3);
	itoa(score, now_score, 10);
	outtextxy(300, 10, now_score);
	itoa(user->score[0], topscore, 10);
	puthz(250, 33, "������߷�", 16, 16, WHITE);
	settextstyle(2, 0, 6);
	outtextxy(335, 32, topscore);
	draw_pause_button(0);
	life(0);

	while (1)
	{
		fruit2_init(fruit1, fruit2, N);    //ÿһ��ˮ����ʼ��
		path_init(fruit2, N);               //ˮ��·����ʼ��
		while (1)
		{
			MouseOff_type(user->mouse_type);
			path(fruit2, N, user, p, &scratch_status, comboshow_times);//·��
			MouseOn_type(MouseX, MouseY, user->mouse_type);
			MouseDelay_type(3, user->mouse_type);
			draw_scratch(p, &scratch_status);
			Mouse_judge(fruit2, N, &score, &end, &ap, &ba, &wa, &mx, &my, comboshow_times);//�ж��Ƿ���������У��ӷֲ�����ˮ��							
			/*****�ж��Ƿ�һ������******/
			if (fruit_judge(fruit2, N, &drop))
			{
				background();
				break;
			}
			/*******�˳�����***************/
			if (end == 1 || drop == 3)
			{
				MouseOff_type(user->mouse_type);
				page = gameover(score);//����������
				if (ach_judge(user, ap, ba, wa, score))
				{
					printf("%d", 1);//����ж��ٸ��³ɾ����
				}//�жϳɾ�
				if ((*user).score[0] <= score)
				{
					(*user).score[0] = score;
				}//������߷�
				change_achscore(user);
				user->total_fruits += score;
				//д���ļ���ȥ
				strcat(filename, (*user).ID);
				strcat(filename, ".dat");
				fp = fopen(filename, "wb");
				fwrite(user, sizeof(User0), 1, fp);
				fclose(fp);
				break;
			}
			/*************************************/
			/***************��ͣ��ť************/
			if (mouse_press(10, 10, 35, 40) == 2)
			{
				if (pause_status != 2)
				{
					MouseOff_type(user->mouse_type);
					draw_pause_button(2);
					MouseOn_type(MouseX, MouseY, user->mouse_type);
					pause_status = 2;
				}
			}
			if (mouse_press(10, 10, 35, 40) == 1)
			{
				MouseOff_type(user->mouse_type);
				draw_pause_button(1);
				MouseOn_type(MouseX, MouseY, user->mouse_type);
				/*�汳��*/
				s = imagesize(168, 128, 472, 352);
				pauseimage = malloc(s);
				getimage(168, 128, 472, 352, pauseimage);
				page = pause(score);
				MouseOff_type(user->mouse_type);
				putimage(168, 128, pauseimage, COPY_PUT);
				MouseOn_type(MouseX, MouseY, user->mouse_type);
				free(pauseimage);
				pauseimage = NULL;
				pause_status = 1;
				/*��ת*/
				if (page != 5)
				{
					ach_judge(user, ap, ba, wa, score);
					if ((*user).score[0] <= score)
					{
						(*user).score[0] = score;
					}//������߷�
					change_achscore(user);
					user->total_fruits += score;
					//д���ļ���ȥ
					strcat(filename, (*user).ID);
					strcat(filename, ".dat");
					fp = fopen(filename, "wb");
					fwrite(user, sizeof(User0), 1, fp);
					fclose(fp);
					break;
				}
			}
			if (mouse_press(10, 10, 35, 40) == 0)
			{
				if (pause_status != 0)
				{
					draw_pause_button(0);
					pause_status = 0;
				}
			}
			/************************************/
		}
		/*��ת*/
		if (page != 5)
		{
			break;
		}
	}
	if (page == 55)
	{
		page = 5;
	}
	return page;
}
/*******�ж��Ƿ���������У��ӷֲ�����ˮ����������ը������Ϸ����**************/
void Mouse_judge(FRUIT* f, int n, int* s, int* pend, int* ap, int* ba, int* wa, int* mx, int* my, int* comboshow_times)
{
	int i;
	int combo = 0;
	char now_score[5];                   
	int r = 40;                   //����жϰ뾶
	int x;
	int y;
	int r2, r3;                    //�㽶��Ҫ����жϰ뾶
	int x2, y2, x3, y3;         //�㽶�Ķ���ж�Բ��
	int score0 = *s;

	for (i = 0; i < n; i++)
	{
		if (f[i].status != 1)
		{
			switch (f[i].type)
			{
			case 0:
				x = f[i].x + 55;
				y = f[i].y + 55;
				r = 45;
				if (fabs(pow((MouseX - x), 2)) + fabs(pow((MouseY - y), 2)) <= pow(r, 2) && LeftPress())
				{
					if (f[i].status == 0)
					{
						f[i].status = 2;//׼����״̬
					}
					else if (f[i].status == 2)
					{
						if (if_mouse_move(mx, my))
						{
							f[i].status = 1;
							*pend = 1;
						}
					}
				}
				else {
					f[i].status = 0;
				}
				r = 40;
				break;

			case 1:
				x = f[i].x + 50;
				y = f[i].y + 50;
				if (fabs(pow((MouseX - x), 2)) + fabs(pow((MouseY - y), 2)) <= pow(r, 2) && LeftPress())
				{
					if (f[i].status == 0)
					{
						f[i].status = 2;//׼����״̬
					}
					else if (f[i].status == 2)
					{
						if (if_mouse_move(mx, my))
						{
							f[i].status = 1;//�ѱ���״̬
							(*s)++;
							(*ap)++;
							combo++;
						}
					}
				}
				else if (if_crossing(x, y, r, MouseX, MouseY, *mx, *my) && LeftPress())
				{
					f[i].status = 1;//�ѱ���״̬
					(*s)++;
					(*ap)++;
					combo++;
				}
				else {
					f[i].status = 0;
				}
				break;

			case 2:

			case 3:
				x = f[i].x + 50;
				y = f[i].y + 50;
				if (fabs(pow((MouseX - x), 2)) + fabs(pow((MouseY - y), 2)) <= pow(r, 2) && LeftPress())
				{
					if (f[i].status == 0)
					{
						f[i].status = 2;//׼����״̬
					}
					else if (f[i].status == 2)
					{
						if (if_mouse_move(mx, my))
						{
							f[i].status = 1;//�ѱ���״̬
							(*s)++;
							combo++;
						}
					}
				}
				else if (if_crossing(x, y, r, MouseX, MouseY, *mx, *my) && LeftPress())
				{
					f[i].status = 1;//�ѱ���״̬
					(*s)++;
					combo++;
				}
				else {
					f[i].status = 0;
				}
				break;

			case 4://banana
				x = f[i].x + 75;
				y = f[i].y + 40;
				r = 15;
				x2 = f[i].x + 62;
				y2 = f[i].y + 64;
				r2 = 21;
				x3 = f[i].x + 35;
				y3 = f[i].y + 78;
				r3 = 18;
				if (((fabs(pow((MouseX - x), 2)) + fabs(pow((MouseY - y), 2)) <= pow(r, 2)) ||
					(fabs(pow((MouseX - x2), 2)) + fabs(pow((MouseY - y2), 2)) <= pow(r2, 2)) ||
					(fabs(pow((MouseX - x3), 2)) + fabs(pow((MouseY - y3), 2)) <= pow(r3, 2)))
					&& LeftPress())
				{
					if (f[i].status == 0)
					{
						f[i].status = 2;
					}//׼����״̬
					else if (f[i].status == 2)
					{
						if (if_mouse_move(mx, my))
						{
							f[i].status = 1;//�ѱ���״̬
							(*s)++;
							(*ba)++;
							combo++;
						}
					}
				}
				else if ((if_crossing(x, y, r, MouseX, MouseY, *mx, *my) || if_crossing(x2, y2, r2, MouseX, MouseY, *mx, *my) || if_crossing(x3, y3, r3, MouseX, MouseY, *mx, *my)) && LeftPress())
				{
					f[i].status = 1;//�ѱ���״̬
					(*s)++;
					combo++;
					(*ba)++;
				}
				else {
					f[i].status = 0;
				}
				r = 40;
				break;

			case 5:
			case 6:
				x = f[i].x + 55;
				y = f[i].y + 55;
				if (fabs(pow((MouseX - x), 2)) + fabs(pow((MouseY - y), 2)) <= pow(r, 2) && LeftPress())
				{
					if (f[i].status == 0)
					{
						f[i].status = 2;//׼����״̬
					}
					else if (f[i].status == 2)
					{
						if (if_mouse_move(mx, my))
						{
							f[i].status = 1;//�ѱ���״̬
							(*s)++;
							combo++;
						}
					}
				}
				else if (if_crossing(x, y, r, MouseX, MouseY, *mx, *my) && LeftPress())
				{
					f[i].status = 1;//�ѱ���״̬
					(*s)++;
					combo++;
				}
				else {
					f[i].status = 0;
				}
				break;

			case 7:
				x = f[i].x + 65;
				y = f[i].y + 75;
				r = 45;
				if (fabs(pow((MouseX - x), 2)) + fabs(pow((MouseY - y), 2)) <= pow(r, 2) && LeftPress())
				{
					if (f[i].status == 0)
					{
						f[i].status = 2;//׼����״̬
					}
					else if (f[i].status == 2)
					{
						if (if_mouse_move(mx, my))
						{
							f[i].status = 1;//�ѱ���״̬
							(*s)++;
							(*wa)++;
							combo++;
						}
					}
				}
				else if (if_crossing(x, y, r, MouseX, MouseY, *mx, *my) && LeftPress())
				{
					f[i].status = 1;//�ѱ���״̬
					(*s)++;
					(*wa)++;
					combo++;
				}
				else {
					f[i].status = 0;
				}
				r = 40;
				break;
			}
		}
	}
	if (combo >= 2)
	{
		*s = *s + combo;
		switch (combo)
		{
		case 2:
			puthz(400, 100, "������", 48, 48, WHITE);
			comboshow_times[0] = 1;
			break;
		case 3:
			puthz(400, 100, "������", 48, 48, WHITE);
			comboshow_times[1] = 1;
			break;
		case 4:
			puthz(400, 100, "������", 48, 48, WHITE);
			comboshow_times[2] = 1;
			break;
		case 5:
			puthz(400, 100, "������", 48, 48, WHITE);
			comboshow_times[3] = 1;
			break;
		}
	}
	combo_judge(comboshow_times);
	if (*s != score0)
	{
		itoa(*s, now_score, 10);
		setfillstyle(SOLID_FILL, BROWN);
		bar(300, 10, 370, 30);
		setcolor(WHITE);
		settextstyle(0, 0, 3);
		outtextxy(300, 10, now_score);

	}
	*mx = MouseX;
	*my = MouseY;
}
/********************************************************************/
//�ж�һ���Ƿ���������ж��Ƿ����
/********************************************************************/
int fruit_judge(FRUIT* f, int n, int* pdrop)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < n; i++)
	{
		if (f[i].x >= 640 || f[i].y >= 480 || f[i].x <= 0)
		{
			if (f[i].status != 1)
			{
				if (f[i].type != 0)
				{
					f[i].status = 1;
					if (*pdrop < 3)
					{
						(*pdrop)++;
						life(*pdrop);
					}
				}
			}
			j++;
		}
	}
	if (j == n)
	{
		return 1;
	}
	else {
		return 0;
	}
}
/********��ͣ����*********/
int  pause(int score)
{
	char now_score[10];
	Button  ach, rank, main, conti;  //�ĸ���ť

	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	bar(168, 128, 472, 352);
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	bar(170, 130, 470, 350);
	conti.x1 = 190;
	conti.y1 = 195;
	conti.x2 = 310;
	conti.y2 = 250;
	conti.btcolor1 = LIGHTGRAY;
	conti.btcolor2 = GREEN;
	conti.status = 0;
	ach.x1 = 330;
	ach.y1 = 195;
	ach.x2 = 450;
	ach.y2 = 250;
	ach.btcolor1 = LIGHTGRAY;
	ach.btcolor2 = GREEN;
	ach.status = 0;
	rank.x1 = 190;
	rank.y1 = 270;
	rank.x2 = 310;
	rank.y2 = 325;
	rank.btcolor1 = LIGHTGRAY;
	rank.btcolor2 = GREEN;
	rank.status = 0;
	main.x1 = 330;
	main.y1 = 270;
	main.x2 = 450;
	main.y2 = 325;
	main.btcolor1 = LIGHTGRAY;
	main.btcolor2 = GREEN;
	main.status = 0;
	drawbutton(&conti);
	puthz(204, 210, "������Ϸ", 24, 24, BLACK);
	drawbutton(&ach);
	puthz(356, 210, "�ɾ�", 24, 48, BLACK);
	drawbutton(&rank);
	puthz(206, 285, "���а�", 24, 32, BLACK);
	drawbutton(&main);
	puthz(346, 285, "���˵�", 24, 32, BLACK);
	puthz(220, 140, "�÷�", 48, 48, WHITE);
	setcolor(WHITE);
	settextstyle(0, 0, 4);
	itoa(score, now_score, 10);
	outtextxy(320, 150, ":");
	outtextxy(345, 150, now_score);

	while (1)
	{
		MouseStatus();
		/*conti��ť*/
		if (mouse_press(conti.x1 - 10, conti.y1 - 10, conti.x2, conti.y2) == 2)
		{
			if (conti.status != 2)
			{
				MouseOff();
				conti.status = 2;
				drawbutton(&conti);
				puthz(204, 210, "������Ϸ", 24, 24, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(conti.x1, conti.y1, conti.x2, conti.y2) == 1)
		{
			conti.status = 1;
			MouseOff();
			drawbutton(&conti);
			puthz(204, 210, "������Ϸ", 24, 24, WHITE);
			MouseOn(MouseX, MouseY);
			delay(200);
			return 5;
		}
		if (mouse_press(conti.x1, conti.y1, conti.x2, conti.y2) == 0)
		{
			if (conti.status != 0)
			{
				MouseOff();
				conti.status = 0;
				drawbutton(&conti);
				puthz(204, 210, "������Ϸ", 24, 24, BLACK);
				MouseOn(MouseX, MouseY);
			}
		}
		/*ach��ť*/
		if (mouse_press(ach.x1 - 10, ach.y1 - 10, ach.x2, ach.y2) == 2)
		{
			if (ach.status != 2)
			{
				MouseOff();
				ach.status = 2;
				drawbutton(&ach);
				puthz(356, 210, "�ɾ�", 24, 48, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(ach.x1, ach.y1, ach.x2, ach.y2) == 1)
		{
			ach.status = 1;
			MouseOff();
			drawbutton(&ach);
			puthz(356, 210, "�ɾ�", 24, 48, WHITE);
			MouseOn(MouseX, MouseY);
			return 3;
		}
		if (mouse_press(ach.x1, ach.y1, ach.x2, ach.y2) == 0)
		{
			if (ach.status != 0)
			{
				MouseOff();
				ach.status = 0;
				drawbutton(&ach);
				puthz(356, 210, "�ɾ�", 24, 48, BLACK);
				MouseOn(MouseX, MouseY);
			}
		}

		/*rank��ť*/
		if (mouse_press(rank.x1 - 10, rank.y1 - 10, rank.x2, rank.y2) == 2)
		{
			if (rank.status != 2)
			{
				MouseOff();
				rank.status = 2;
				drawbutton(&rank);
				puthz(206, 285, "���а�", 24, 32, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(rank.x1, rank.y1, rank.x2, rank.y2) == 1)
		{
			rank.status = 1;
			MouseOff();
			drawbutton(&rank);
			puthz(206, 285, "���а�", 24, 32, WHITE);
			MouseOn(MouseX, MouseY);
			delay(200);
			return 2;
		}
		if (mouse_press(rank.x1, rank.y1, rank.x2, rank.y2) == 0)
		{
			if (rank.status != 0)
			{
				MouseOff();
				rank.status = 0;
				drawbutton(&rank);
				puthz(206, 285, "���а�", 24, 32, BLACK);
				MouseOn(MouseX, MouseY);
			}
		}

		/*main��ť*/
		if (mouse_press(main.x1 - 10, main.y1 - 10, main.x2, main.y2) == 2)
		{
			if (main.status != 2)
			{
				MouseOff();
				main.status = 2;
				drawbutton(&main);
				puthz(346, 285, "���˵�", 24, 32, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(main.x1, main.y1, main.x2, main.y2) == 1)
		{
			main.status = 1;
			MouseOff();
			drawbutton(&main);
			puthz(346, 285, "���˵�", 24, 32, WHITE);
			MouseOn(MouseX, MouseY);
			return 0;
		}
		if (mouse_press(main.x1, main.y1, main.x2, main.y2) == 0)
		{
			if (main.status != 0)
			{
				MouseOff();
				main.status = 0;
				drawbutton(&main);
				puthz(346, 285, "���˵�", 24, 32, BLACK);
				MouseOn(MouseX, MouseY);
			}
		}
	}
}
int  gameover(int score)
{
	char final_score[10];
	Button  ach, rank, main, restart;

	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	bar(168, 128, 472, 352);
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	bar(170, 130, 470, 350);
	restart.x1 = 190;
	restart.y1 = 195;
	restart.x2 = 310;
	restart.y2 = 250;
	restart.btcolor1 = LIGHTGRAY;
	restart.btcolor2 = GREEN;
	restart.status = 0;
	ach.x1 = 330;
	ach.y1 = 195;
	ach.x2 = 450;
	ach.y2 = 250;
	ach.btcolor1 = LIGHTGRAY;
	ach.btcolor2 = GREEN;
	ach.status = 0;
	rank.x1 = 190;
	rank.y1 = 270;
	rank.x2 = 310;
	rank.y2 = 325;
	rank.btcolor1 = LIGHTGRAY;
	rank.btcolor2 = GREEN;
	rank.status = 0;
	main.x1 = 330;
	main.y1 = 270;
	main.x2 = 450;
	main.y2 = 325;
	main.btcolor1 = LIGHTGRAY;
	main.btcolor2 = GREEN;
	main.status = 0;
	drawbutton(&restart);
	puthz(204, 210, "������Ϸ", 24, 24, BLACK);
	drawbutton(&ach);
	puthz(356, 210, "�ɾ�", 24, 48, BLACK);
	drawbutton(&rank);
	puthz(206, 285, "���а�", 24, 32, BLACK);
	drawbutton(&main);
	puthz(346, 285, "���˵�", 24, 32, BLACK);
	puthz(220, 140, "�÷�", 48, 48, WHITE);
	setcolor(WHITE);
	settextstyle(0, 0, 4);
	itoa(score, final_score, 10);
	outtextxy(320, 150, ":");
	outtextxy(345, 150, final_score);
	MouseOn(MouseX, MouseY);
	while (1)
	{
		MouseStatus();
		/*restart��ť*/
		if (mouse_press(restart.x1 - 10, restart.y1 - 10, restart.x2, restart.y2) == 2)
		{
			if (restart.status != 2)
			{
				MouseOff();
				restart.status = 2;
				drawbutton(&restart);
				puthz(204, 210, "������Ϸ", 24, 24, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(restart.x1, restart.y1, restart.x2, restart.y2) == 1)
		{
			restart.status = 1;
			MouseOff();
			drawbutton(&restart);
			puthz(204, 210, "������Ϸ", 24, 24, WHITE);
			MouseOn(MouseX, MouseY);
			delay(200);
			return 55;
		}
		if (mouse_press(restart.x1, restart.y1, restart.x2, restart.y2) == 0)
		{
			if (restart.status != 0)
			{
				restart.status = 0;
				drawbutton(&restart);
				puthz(204, 210, "������Ϸ", 24, 24, BLACK);
			}
		}


		/*ach��ť*/
		if (mouse_press(ach.x1 - 10, ach.y1 - 10, ach.x2, ach.y2) == 2)
		{
			if (ach.status != 2)
			{
				MouseOff();
				ach.status = 2;
				drawbutton(&ach);
				puthz(356, 210, "�ɾ�", 24, 48, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(ach.x1, ach.y1, ach.x2, ach.y2) == 1)
		{
			ach.status = 1;
			MouseOff();
			drawbutton(&ach);
			puthz(356, 210, "�ɾ�", 24, 48, WHITE);
			MouseOn(MouseX, MouseY);
			return 3;
		}
		if (mouse_press(ach.x1, ach.y1, ach.x2, ach.y2) == 0)
		{
			if (ach.status != 0)
			{
				MouseOff();
				ach.status = 0;
				drawbutton(&ach);
				puthz(356, 210, "�ɾ�", 24, 48, BLACK);
				MouseOn(MouseX, MouseY);
			}
		}


		/*rank��ť*/
		if (mouse_press(rank.x1 - 10, rank.y1 - 10, rank.x2, rank.y2) == 2)
		{
			if (rank.status != 2)
			{
				MouseOff();
				rank.status = 2;
				drawbutton(&rank);
				puthz(206, 285, "���а�", 24, 32, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(rank.x1, rank.y1, rank.x2, rank.y2) == 1)
		{
			rank.status = 1;
			MouseOff();
			drawbutton(&rank);
			puthz(206, 285, "���а�", 24, 32, WHITE);
			MouseOn(MouseX, MouseY);
			delay(200);
			return 2;
		}
		if (mouse_press(rank.x1, rank.y1, rank.x2, rank.y2) == 0)
		{
			if (rank.status != 0)
			{
				MouseOff();
				rank.status = 0;
				drawbutton(&rank);
				puthz(206, 285, "���а�", 24, 32, BLACK);
				MouseOn(MouseX, MouseY);
			}
		}


		/*main��ť*/
		if (mouse_press(main.x1 - 10, main.y1 - 10, main.x2, main.y2) == 2)
		{
			if (main.status != 2)
			{
				MouseOff();
				main.status = 2;
				drawbutton(&main);
				puthz(346, 285, "���˵�", 24, 32, WHITE);
				MouseOn(MouseX, MouseY);
			}
		}
		if (mouse_press(main.x1, main.y1, main.x2, main.y2) == 1)
		{
			main.status = 1;
			MouseOff();
			drawbutton(&main);
			puthz(346, 285, "���˵�", 24, 32, WHITE);
			MouseOn(MouseX, MouseY);
			return 0;
		}
		if (mouse_press(main.x1, main.y1, main.x2, main.y2) == 0)
		{
			if (main.status != 0)
			{
				MouseOff();
				main.status = 0;
				drawbutton(&main);
				puthz(346, 285, "���˵�", 24, 32, BLACK);
				MouseOn(MouseX, MouseY);
			}
		}
	}
}



int if_crossing(int incenterX, int incenterY, int r, int x1, int y1, int x2, int y2)
{
	double a =  fabs((y2 - y1) * incenterX + (x1 - x2) * incenterY + (x2 * y1) - (x1 * y2));

	long int b =  (long int)pow(y2 - y1, 2) +(long int) pow(x1 - x2, 2);
	double d;
	//printf("%d",b);
	if(b>0)
	{
	  d =a/sqrt(b);
	}
	else{
	  d=1000;
	}
	//double d = (fabs((y2 - y1) * incenterX + (x1 - x2) * incenterY + ((x2 * y1) - (x1 * y2)))) / (sqrt(pow(y2 - y1, 2) + pow(x1 - x2, 2)));

	if (x2 != -1 && y2 != -1)
	{
		if (d < r)
		{
			if ((pow(incenterX - x1, 2) + (pow(incenterY - y1, 2) + pow(x1 - x2, 2) + pow(y1 - y2, 2)
				- pow(incenterX - x2, 2) - pow(incenterY - y2, 2))
				/ 2 * sqrt(pow(y2 - y1, 2) + pow(x1 - x2, 2)) * sqrt(pow(incenterX - x1, 2) + pow(incenterY - y1, 2))) > 0 &&
				(pow(incenterX - x2, 2) + (pow(incenterY - y2, 2) + pow(x1 - x2, 2) + pow(y1 - y2, 2)
					- pow(incenterX - x1, 2) - pow(incenterY - y1, 2))
					/ 2 * sqrt(pow(y2 - y1, 2) + pow(x1 - x2, 2)) * sqrt(pow(incenterX - x2, 2) + pow(incenterY - y2, 2))) > 0)
			{
				return 1;
			}
		}
	}
	return 0;

	//�ж�Բ�����߶ξ����Ƿ�С��r
	//��С��r�ж��������Ƿ�����ǣ�cos��
	//��������ǣ��򷵻�1
}
void combo_judge(int* comboshow_times)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			if (comboshow_times[0] <= 10 & comboshow_times[0] >= 1)
			{
				puthz(400, 100, "������", 48, 48, WHITE);
				comboshow_times[0]++;
			}
			else {
				comboshow_times[0] = 0;
			}
			break;
		case 1:
			if (comboshow_times[1] <= 10 & comboshow_times[1] >= 1)
			{
				puthz(400, 100, "������", 48, 48, WHITE);
				comboshow_times[1]++;
			}
			else {
				comboshow_times[1] = 0;
			}
			break;
		case 2:
			if (comboshow_times[2] <= 10 & comboshow_times[2] >= 1)
			{
				puthz(400, 100, "������", 48, 48, WHITE);
				comboshow_times[2]++;
			}
			else {
				comboshow_times[2] = 0;
			}
			break;
		case 3:
			if (comboshow_times[3] <= 10 & comboshow_times[3] >= 1)
			{
				puthz(400, 100, "������", 48, 48, WHITE);
				comboshow_times[3]++;
			}
			else {
				comboshow_times[3] = 0;
			}
		}
	}
}