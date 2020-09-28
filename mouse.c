/**************************************************************
Filename��mouse.c  Author: ������   Version:1.0   Date:10.19
Description:���ļ������˹���������غ���
Function List:
     //����Ϊѧ����д
	1.void MouseOn(int x,int y);                   //��ʾ���
	2.void MouseOff(void);					   //�������
	3.void MouseInit(void);					   //��ʼ�����
	4.void Mouse_Init(void);					   //��ʼ�������� ���ñ߽��
	5.void MouseRangeX(int lx, int rx);	        //����x�߽�
	6.void MouseRangeY(int uy, int dy);	        //����y�߽�
	7.void MouseSetXY(int x, int y);			   //�������λ��
	8.void MouseSpeed(int vx, int vy);		   //��������ٶ�
	9.int LeftPress(void);					   //����������Ƿ���
	10.int MiddlePress(void);					   //�������м��Ƿ���
	11.int RightPress(void);					   //�������Ҽ��Ƿ���
	12.void MouseGetMXY(void);                 	//����굱ǰλ��д��ȫ�ֱ���
	13.void MouseGetXY(int *x, int *y);           	//�õ���ǰλ��
	14.int MouseStatus(void);					  //��ȡ���״̬������ƶ�������»����	
	15.void MouseShow(void);					  //ÿ��һ��ʱ�仭���
	16.void MouseDelay(int n);					  //���ӳٵ�����»����
	17.void MouseOnfx(int mx, int my);			  //�����ʾΪ��
    //����Ϊ�Լ���ѧ�������ϲ����д�ĺ���
	18.int mouse_judge(int x,int y,int r);       //����ж�
	19.int mouse_press(int x1, int y1, int x2, int y2);     //�ж������ָ������ ��״̬
	20.int  if_mouse_move(int *mx,int *my);    //�ж�����Ƿ��ƶ�
	21. void Sword_On(int x, int y);                //��sword
	22.void DrawSword(int x, int y,int n);        //�������໭����
	23.void Mouse_On(int x,int y);                   //
	24.void Sword1_On(int x, int y);                   //
	25.void MouseDelay_type(int n,int type);     //
	26.void MouseOff_type(int type);                 //
	27.void MouseOn_type(int x, int y,int type);    //
	28.void  draw_scratch(int *p,int *status);       //����껮��
History�� 10.22дע��
<author>  <time> <version> <desc>
������    19/10/19  1.0    build this module
***************************************************************/

#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <math.h>
#include"mouse.h"
#include"time.h"
//#include"svgasub.h"



int MouseX;
int MouseY;
int pixel_save[16][16];
int pixel_save1[25][25];
int mouse_draw[16][16] =
{
	1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 1, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 2, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3,
	1, 2, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 1, 3, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 1, 3, 3, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 1, 2, 2, 1, 3, 3, 3, 3, 3, 3
};

int sword[16][16] =
{
	1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 1, 1, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	1, 1, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 1, 1, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 1, 1, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 1, 1, 2, 2, 1, 1, 3, 3, 1, 1, 3, 3, 3,
	3, 3, 3, 3, 1, 1, 2, 2, 1, 1, 1, 1, 1, 3, 3, 3,
	3, 3, 3, 3, 3, 1, 1, 2, 2, 1, 1, 1, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 2, 1, 1, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 2, 2, 1, 1, 3, 3,
	3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 1, 2, 2, 1, 1, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 2, 1, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3
};

int sword1[25][25] =
{
	1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	1,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	1,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,1,2,2,1,2,2,1,3,3,3,3,3,3,3,1,1,3,3,3,
	3,3,3,3,3,3,3,1,2,2,1,2,2,1,3,3,3,3,3,1,1,3,3,3,3,
	3,3,3,3,3,3,3,3,1,2,2,1,2,2,1,3,3,3,1,1,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,1,2,2,1,2,2,1,3,1,1,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,1,2,2,1,2,2,1,1,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,1,2,2,1,1,2,1,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,1,2,1,2,2,1,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,1,2,2,2,2,1,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,2,2,2,1,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,1,2,2,2,1,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,1,2,2,1,1,3,3,3,
	3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,1,1,1,1,1,3,3,
	3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,3,3,3,1,1,1,1,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

void Mouse_Init(void)            //��ʼ�������� ���ñ߽��
{
	MouseInit();    //��ʼ�����
	MouseRangeX(0, 640);   //����x�߽�
	MouseRangeY(0, 480);   //����y�߽�
	MouseGetMXY();         //����굱ǰλ��д��ȫ�ֱ���
	MouseSpeed(15, 15);      //��������ٶ�
	/*_AX = 0x01;
	geninterrupt(0x33);
	delay(200);
	_AX = 0x02;
	geninterrupt(0x33);*/
}

void MouseSpeed(int vx, int vy)		//��������ٶ�(ȱʡֵ) ֵԽ���ٶ�Խ��
{
	_CX = vx;
	_DX = vy;
	_AX = 0x0f;
	geninterrupt(0x33);
}


/*�������ʾ*/
void MouseOn(int x, int y)
{
	int i, j;
	int color;

	for (i = 0; i < 16; i++)/*�����*/
	{
		for (j = 0; j < 16; j++)
		{
			pixel_save[i][j] = getpixel(x + j, y + i);/*����ԭ������ɫ*/
			if (mouse_draw[i][j] == 1)
				putpixel(x + j, y + i, BLACK);
			else if (mouse_draw[i][j] == 2)
				putpixel(x + j, y + i, WHITE);
		}
	}
}
/*�������*/
void MouseOff()
{
	int i, j, x, y, color;
	x = MouseX;//ȫ�ֱ���
	y = MouseY;//ȫ�ֱ���
	for (i = 0; i < 16; i++)/*ԭλ�������ȥ*/
	{
		for (j = 0; j < 16; j++)
		{
			if (mouse_draw[i][j] == 3 || mouse_draw[i][j] == 4)
				continue;
			color = getpixel(x + j, y + i);
			putpixel(x + j, y + i, color ^ color);  //color^color=0
			putpixel(x + j, y + i, pixel_save[i][j]);
		}
	}
}


int MouseStatus()        //��ȡ���״̬������ƶ�������»���� status=0����û�� =1������
						 //return press 3�����Ҷ��� 2���Ҽ� 1����� 0��û����
{
	int x, y;
	int status;
	int press = 0;
	int xx, yy;
	int i, j, color;
	status = 0;            	//Ĭ�����û���ƶ�

	x = MouseX;//ȫ�ֱ���
	y = MouseY;//ȫ�ֱ���
	/*x == MouseX&&y == MouseY&&*/
	while (status == 0 && press == 0)
	{
		if (LeftPress() && RightPress())//LeftPress����������Ƿ��� RightPress�������Ҽ��Ƿ���
			press = 3;
		else if (LeftPress())
			press = 1;
		else if (RightPress())
			press = 2;
		MouseGetMXY();  //����굱ǰλ��д��ȫ�ֱ���
		if (MouseX != x || MouseY != y)
			status = 1;
	}
	if (status)           	//�ƶ������������ʾ���
	{
		for (i = 0; i < 16; i++)           	//ԭλ�������ȥ
			for (j = 0; j < 16; j++)
			{
				if (mouse_draw[i][j] == 3 || mouse_draw[i][j] == 4)
					continue;
				color = getpixel(x + j, y + i);
				putpixel(x + j, y + i, color ^ color);
				putpixel(x + j, y + i, pixel_save[i][j]);
			}


		MouseOn(MouseX, MouseY);/*��λ����ʾ*/
	}
	if (press != 0)/*�а��������*/
		return press;
	return 0;/*ֻ�ƶ������*/
}

void MouseDelay(int n)//���ӳٵ�����»����
{
	int x, y;
	int status;
	int xx, yy;
	int i, j, color, k;
	for (k = 0; k < n; k++)
	{
		x = MouseX;
		y = MouseY;
		delay(10);                                   //�ӳ�10����
		MouseGetMXY();                               //����굱ǰλ��д��ȫ�ֱ���
		if (MouseX != x || MouseY != y)           	//�ƶ������������ʾ���
		{
			for (i = 0; i < 16; i++)           	//ԭλ�������ȥ
				for (j = 0; j < 16; j++)
				{
					if (mouse_draw[i][j] == 3 || mouse_draw[i][j] == 4)
						continue;
					color = getpixel(x + j, y + i);
					putpixel(x + j, y + i, color ^ color);
					putpixel(x + j, y + i, pixel_save[i][j]);
				}
			MouseOn(MouseX, MouseY);//��λ����ʾ
		}
	}
}


void MouseShow(void)                   //ÿ��һ��ʱ�仭���
{
	int x, y;
	int status;
	int xx, yy;
	int i, j, color, k;
	x = MouseX;
	y = MouseY;
	//delay(10);
	MouseGetMXY();
	for (i = 0; i < 16; i++)           	//ԭλ�������ȥ
		for (j = 0; j < 16; j++)
		{
			if (mouse_draw[i][j] == 3 || mouse_draw[i][j] == 4)
				continue;
			color = getpixel(x + j, y + i);
			putpixel(x + j, y + i, color ^ color);
			putpixel(x + j, y + i, pixel_save[i][j]);
		}
	MouseOn(MouseX, MouseY);//��λ����ʾ
}

/*���״ֵ̬��ʼ��*/

void MouseInit(void)
{
	_AX = 0x00;
	geninterrupt(0x33);           	//0x33��DOS�ж�,����DOS��ͨ�������ж����������в���.
}

void MouseSetXY(int x, int y)		//���õ�ǰλ��
{
	_CX = x;
	_DX = y;
	_AX = 0x04;
	geninterrupt(0x33);
}

void MouseRangeX(int lx, int rx)		//����x�߽�
{
	_CX = lx;
	_DX = rx;
	_AX = 0x07;
	geninterrupt(0x33);
}

void MouseRangeY(int uy, int dy)		//����y�߽�
{
	_CX = uy;
	_DX = dy;
	_AX = 0X08;
	geninterrupt(0x33);
}


int LeftPress(void)					//����������
{
	_AX = 0x03;
	geninterrupt(0x33);
	return(_BX & 1);
}

int MiddlePress(void)					//����м�����
{
	_AX = 0x03;
	geninterrupt(0x33);
	return(_BX & 4);
}

int RightPress(void)					//����Ҽ�����
{
	_AX = 0x03;
	geninterrupt(0x33);
	return(_BX & 2);
}

/*��ȡ��굱ǰλ��*/
void MouseGetMXY(void)
{
	_AX = 0x03;
	geninterrupt(0x33);
	MouseX = _CX;
	MouseY = _DX;
}

void MouseGetXY(int* x, int* y)
{
	_AX = 0x03;
	geninterrupt(0x33);
	*x = _CX;
	*y = _DX;
}

//����ڿ��е�����򷵻�1���ڿ���δ������򷵻�2�����ڿ����򷵻�0

int mouse_press(int x1, int y1, int x2, int y2)
{
	//�ڿ��е�����򷵻�1
	if (MouseX > x1
		&& MouseX < x2
		&& MouseY > y1
		&& MouseY < y2
		&& LeftPress())
	{
		return 1;
	}

	//�ڿ���δ������򷵻�2
	else if (MouseX > x1
		&& MouseX < x2
		&& MouseY > y1
		&& MouseY < y2
		&& LeftPress() != 1)
	{
		return 2;
	}

	//�ڿ��е���Ҽ����򷵻�3
	else if (MouseX > x1
		&& MouseX < x2
		&& MouseY > y1
		&& MouseY < y2
		&& RightPress())
	{
		return 3;
	}

	else
	{
		return 0;
	}
}

 //�ж�����Ƿ��ƶ�
int  if_mouse_move(int* mx, int* my)
{
	int r = 1;
	if (*mx != -1 && *my != -1)
	{
		if (fabs(pow(fabs(MouseX - *mx), 2)) + fabs(pow(fabs(MouseY - *my), 2)) >= pow(r, 2))
		{
			return 1;
		}
	}
	return 0;
}

void Sword_On(int x, int y)
{
	int i, j;
	int color;

	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			if (sword[i][j] == 1)
				putpixel(x + j, y + i, BLACK);
			else if (sword[i][j] == 2)
				putpixel(x + j, y + i, WHITE);
		}
	}
}
void Sword1_On(int x, int y)
{
	int i, j;
	int color;

	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < 25; j++)
		{
			if (sword1[i][j] == 1)
				putpixel(x + j, y + i, BLACK);
			else if (sword1[i][j] == 2)
				putpixel(x + j, y + i, WHITE);
		}
	}
}
void Mouse_On(int x, int y)
{
	int i, j;
	int color;

	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			if (mouse_draw[i][j] == 1)
				putpixel(x + j, y + i, BLACK);
			else if (mouse_draw[i][j] == 2)
				putpixel(x + j, y + i, WHITE);
		}
	}
}
void DrawSword(int x, int y, int n)
{
	switch (n)
	{
	case 1:
		Mouse_On(x, y);
		break;
	case 2:
		Sword_On(x, y);
		break;
	case 3:
		Sword1_On(x, y);
		break;
	}
}
//��mouseon���ƣ�ֻ�������˲��������Ի���꣬������Ϸ��
void MouseOn_type(int x, int y, int type)
{
	int i, j;
	int color;

	switch (type)
	{
	case 1:
		for (i = 0; i < 16; i++)/*�����*/
		{
			for (j = 0; j < 16; j++)
			{
				pixel_save[i][j] = getpixel(x + j, y + i);/*����ԭ������ɫ*/
				if (mouse_draw[i][j] == 1)
					putpixel(x + j, y + i, BLACK);
				else if (mouse_draw[i][j] == 2)
					putpixel(x + j, y + i, WHITE);
			}
		}
		break;
	case 2:
		for (i = 0; i < 16; i++)/*��С��*/
		{
			for (j = 0; j < 16; j++)
			{
				pixel_save[i][j] = getpixel(x + j, y + i);/*����ԭ������ɫ*/
				if (sword[i][j] == 1)
					putpixel(x + j, y + i, BLACK);
				else if (sword[i][j] == 2)
					putpixel(x + j, y + i, WHITE);
			}
		}
		break;
	case 3:
		for (i = 0; i < 25; i++)/*������*/
		{
			for (j = 0; j < 25; j++)
			{
				pixel_save1[i][j] = getpixel(x + j, y + i);/*����ԭ������ɫ*/
				if (sword1[i][j] == 1)
					putpixel(x + j, y + i, BLACK);
				else if (sword1[i][j] == 2)
					putpixel(x + j, y + i, WHITE);
			}
		}
		break;
	}

}
/*�������*/
void MouseOff_type(int type)
{
	int i, j, x, y, color;
	x = MouseX;//ȫ�ֱ���
	y = MouseY;//ȫ�ֱ���

	switch (type)
	{
	case 1:
		for (i = 0; i < 16; i++)/*ԭλ�������ȥ*/
		{
			for (j = 0; j < 16; j++)
			{
				if (mouse_draw[i][j] == 3 || mouse_draw[i][j] == 4)
					continue;
				color = getpixel(x + j, y + i);
				putpixel(x + j, y + i, color ^ color);  //color^color=0
				putpixel(x + j, y + i, pixel_save[i][j]);
			}
		}
		break;
	case 2:
		for (i = 0; i < 16; i++)/*ԭλ�������ȥ*/
		{
			for (j = 0; j < 16; j++)
			{
				if (sword[i][j] == 3 || sword[i][j] == 4)
					continue;
				color = getpixel(x + j, y + i);
				putpixel(x + j, y + i, color ^ color);  //color^color=0
				putpixel(x + j, y + i, pixel_save[i][j]);
			}
		}
		break;
	case 3:
		for (i = 0; i < 25; i++)/*ԭλ�������ȥ*/
		{
			for (j = 0; j < 25; j++)
			{
				if (sword1[i][j] == 3 || sword1[i][j] == 4)
					continue;
				color = getpixel(x + j, y + i);
				putpixel(x + j, y + i, color ^ color);  //color^color=0
				putpixel(x + j, y + i, pixel_save1[i][j]);
			}
		}
		break;
	}
}
void MouseDelay_type(int n, int type)//���ӳٵ�����»����
{
	int x, y;
	int status;
	int xx, yy;
	int i, j, color, k;
	for (k = 0; k < n; k++)
	{
		x = MouseX;
		y = MouseY;
		delay(10);                                   //�ӳ�10����
		MouseGetMXY();                               //����굱ǰλ��д��ȫ�ֱ���
		if (MouseX != x || MouseY != y)           	//�ƶ������������ʾ���
		{
			switch (type)
			{
			case 1:
				for (i = 0; i < 16; i++)/*ԭλ�������ȥ*/
				{
					for (j = 0; j < 16; j++)
					{
						if (mouse_draw[i][j] == 3 || mouse_draw[i][j] == 4)
							continue;
						color = getpixel(x + j, y + i);
						putpixel(x + j, y + i, color ^ color);  //color^color=0
						putpixel(x + j, y + i, pixel_save[i][j]);
					}
				}
				break;
			case 2:
				for (i = 0; i < 16; i++)/*ԭλ�������ȥ*/
				{
					for (j = 0; j < 16; j++)
					{
						if (sword[i][j] == 3 || sword[i][j] == 4)
							continue;
						color = getpixel(x + j, y + i);
						putpixel(x + j, y + i, color ^ color);  //color^color=0
						putpixel(x + j, y + i, pixel_save[i][j]);
					}
				}
				break;
			case 3:
				for (i = 0; i < 25; i++)/*ԭλ�������ȥ*/
				{
					for (j = 0; j < 25; j++)
					{
						if (sword1[i][j] == 3 || sword1[i][j] == 4)
							continue;
						color = getpixel(x + j, y + i);
						putpixel(x + j, y + i, color ^ color);  //color^color=0
						putpixel(x + j, y + i, pixel_save1[i][j]);
					}
				}
				break;
			}

			MouseOn_type(MouseX, MouseY, type);//��λ����ʾ
		}
	}
}

/**************************************************************
Function: draw_scratch
Description:��껮��
Calls
Input:int* p����������ʷ������飩, int* status�����״̬��
Return:
Others��
�����˶��е�˼�룬���ƶ�ʮ�������ɵ���껮��
***************************************************************/
void  draw_scratch(int* p, int* status)
{
	int j;
	int k;
	int i;
	if (LeftPress() && MouseY > 50)
	{
		if (*status == 1)
		{
			//����һ���ɿ���꣬��ն���
			for (i = 0; i < SCRATCH; i++)
			{
				p[i] = -1;
			}
			*status = 0;
		}
		if (p[SCRATCH - 1] != -1)
		{
			//���������
			for (i = 0; i < SCRATCH - 2; i++)
			{
				p[i] = p[i + 2];
			}
			p[SCRATCH - 2] = -1;
			p[SCRATCH - 1] = -1;
		}
		//���
		for (i = 0; i < SCRATCH; i++)
		{
			if (p[i] == -1)
			{
				break;
			}
		}
		p[i] = MouseX;
		p[i + 1] = MouseY;
	}
	else {
		*status = 1;
		//����
		for (k = 0; k < 3; k++)
		{
			for (i = 0; i < SCRATCH; i++)
			{
				if (p[i] == -1)
				{
					j = i;
					break;
				}
				j = SCRATCH;
			}
			if (j >= 3)
			{
				for (i = 0; i < j - 2; i++)
				{
					p[i] = p[i + 2];
				}
				p[j - 1] = -1;
				p[j - 2] = -1;
			}
		}
	}
	randomize();
	setcolor(7 + random(8));
	setlinestyle(0, 0, 3);

	for (i = 2; i < SCRATCH - 1; i++)
	{
		if (p[i] == -1)
		{
			j = i;
			break;
		}
		j = SCRATCH;
	}
	for (i = 2; i < j / 2; i++)
	{
		if (p[i] != -1 && i % 2 == 0)
		{
			line(p[i - 2], p[i - 1], p[i], p[i + 1]);
		}
	}
	setcolor(7 + random(8));
	setlinestyle(0, 0, 3);

	for (i = j / 2 - 1; i < j - 2; i++)
	{
		if (p[i] != -1 && i % 2 == 0)
		{
			line(p[i - 2], p[i - 1], p[i], p[i + 1]);
		}
	}
}


