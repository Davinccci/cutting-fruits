/**************************************************************
Filename：mouse.c  Author: 李天依   Version:1.0   Date:10.19
Description:该文件包含了关于鼠标的相关函数
Function List:
     //以下为学长编写
	1.void MouseOn(int x,int y);                   //显示鼠标
	2.void MouseOff(void);					   //隐藏鼠标
	3.void MouseInit(void);					   //初始化鼠标
	4.void Mouse_Init(void);					   //初始化鼠标包括 设置边界等
	5.void MouseRangeX(int lx, int rx);	        //设置x边界
	6.void MouseRangeY(int uy, int dy);	        //设置y边界
	7.void MouseSetXY(int x, int y);			   //设置鼠标位置
	8.void MouseSpeed(int vx, int vy);		   //设置鼠标速度
	9.int LeftPress(void);					   //检测鼠标左键是否按下
	10.int MiddlePress(void);					   //检测鼠标中键是否按下
	11.int RightPress(void);					   //检测鼠标右键是否按下
	12.void MouseGetMXY(void);                 	//将鼠标当前位置写进全局变量
	13.void MouseGetXY(int *x, int *y);           	//得到当前位置
	14.int MouseStatus(void);					  //获取鼠标状态在鼠标移动的情况下画鼠标	
	15.void MouseShow(void);					  //每隔一段时间画鼠标
	16.void MouseDelay(int n);					  //在延迟的情况下画鼠标
	17.void MouseOnfx(int mx, int my);			  //鼠标显示为刀
    //以下为自己在学长基础上补充编写的函数
	18.int mouse_judge(int x,int y,int r);       //鼠标判断
	19.int mouse_press(int x1, int y1, int x2, int y2);     //判断鼠标在指定区域 的状态
	20.int  if_mouse_move(int *mx,int *my);    //判断鼠标是否移动
	21. void Sword_On(int x, int y);                //画sword
	22.void DrawSword(int x, int y,int n);        //根据种类画刀具
	23.void Mouse_On(int x,int y);                   //
	24.void Sword1_On(int x, int y);                   //
	25.void MouseDelay_type(int n,int type);     //
	26.void MouseOff_type(int type);                 //
	27.void MouseOn_type(int x, int y,int type);    //
	28.void  draw_scratch(int *p,int *status);       //画鼠标划痕
History： 10.22写注释
<author>  <time> <version> <desc>
李天依    19/10/19  1.0    build this module
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

void Mouse_Init(void)            //初始化鼠标包括 设置边界等
{
	MouseInit();    //初始化鼠标
	MouseRangeX(0, 640);   //设置x边界
	MouseRangeY(0, 480);   //设置y边界
	MouseGetMXY();         //将鼠标当前位置写进全局变量
	MouseSpeed(15, 15);      //设置鼠标速度
	/*_AX = 0x01;
	geninterrupt(0x33);
	delay(200);
	_AX = 0x02;
	geninterrupt(0x33);*/
}

void MouseSpeed(int vx, int vy)		//设置鼠标速度(缺省值) 值越大速度越慢
{
	_CX = vx;
	_DX = vy;
	_AX = 0x0f;
	geninterrupt(0x33);
}


/*鼠标光标显示*/
void MouseOn(int x, int y)
{
	int i, j;
	int color;

	for (i = 0; i < 16; i++)/*画鼠标*/
	{
		for (j = 0; j < 16; j++)
		{
			pixel_save[i][j] = getpixel(x + j, y + i);/*保存原来的颜色*/
			if (mouse_draw[i][j] == 1)
				putpixel(x + j, y + i, BLACK);
			else if (mouse_draw[i][j] == 2)
				putpixel(x + j, y + i, WHITE);
		}
	}
}
/*隐藏鼠标*/
void MouseOff()
{
	int i, j, x, y, color;
	x = MouseX;//全局变量
	y = MouseY;//全局变量
	for (i = 0; i < 16; i++)/*原位置异或消去*/
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


int MouseStatus()        //获取鼠标状态在鼠标移动的情况下画鼠标 status=0代表没动 =1代表动了
						 //return press 3是左右都按 2是右键 1是左键 0是没按键
{
	int x, y;
	int status;
	int press = 0;
	int xx, yy;
	int i, j, color;
	status = 0;            	//默认鼠标没有移动

	x = MouseX;//全局变量
	y = MouseY;//全局变量
	/*x == MouseX&&y == MouseY&&*/
	while (status == 0 && press == 0)
	{
		if (LeftPress() && RightPress())//LeftPress检测鼠标左键是否按下 RightPress检测鼠标右键是否按下
			press = 3;
		else if (LeftPress())
			press = 1;
		else if (RightPress())
			press = 2;
		MouseGetMXY();  //将鼠标当前位置写进全局变量
		if (MouseX != x || MouseY != y)
			status = 1;
	}
	if (status)           	//移动情况才重新显示鼠标
	{
		for (i = 0; i < 16; i++)           	//原位置异或消去
			for (j = 0; j < 16; j++)
			{
				if (mouse_draw[i][j] == 3 || mouse_draw[i][j] == 4)
					continue;
				color = getpixel(x + j, y + i);
				putpixel(x + j, y + i, color ^ color);
				putpixel(x + j, y + i, pixel_save[i][j]);
			}


		MouseOn(MouseX, MouseY);/*新位置显示*/
	}
	if (press != 0)/*有按键的情况*/
		return press;
	return 0;/*只移动的情况*/
}

void MouseDelay(int n)//在延迟的情况下画鼠标
{
	int x, y;
	int status;
	int xx, yy;
	int i, j, color, k;
	for (k = 0; k < n; k++)
	{
		x = MouseX;
		y = MouseY;
		delay(10);                                   //延迟10毫秒
		MouseGetMXY();                               //将鼠标当前位置写进全局变量
		if (MouseX != x || MouseY != y)           	//移动情况才重新显示鼠标
		{
			for (i = 0; i < 16; i++)           	//原位置异或消去
				for (j = 0; j < 16; j++)
				{
					if (mouse_draw[i][j] == 3 || mouse_draw[i][j] == 4)
						continue;
					color = getpixel(x + j, y + i);
					putpixel(x + j, y + i, color ^ color);
					putpixel(x + j, y + i, pixel_save[i][j]);
				}
			MouseOn(MouseX, MouseY);//新位置显示
		}
	}
}


void MouseShow(void)                   //每隔一段时间画鼠标
{
	int x, y;
	int status;
	int xx, yy;
	int i, j, color, k;
	x = MouseX;
	y = MouseY;
	//delay(10);
	MouseGetMXY();
	for (i = 0; i < 16; i++)           	//原位置异或消去
		for (j = 0; j < 16; j++)
		{
			if (mouse_draw[i][j] == 3 || mouse_draw[i][j] == 4)
				continue;
			color = getpixel(x + j, y + i);
			putpixel(x + j, y + i, color ^ color);
			putpixel(x + j, y + i, pixel_save[i][j]);
		}
	MouseOn(MouseX, MouseY);//新位置显示
}

/*鼠标状态值初始化*/

void MouseInit(void)
{
	_AX = 0x00;
	geninterrupt(0x33);           	//0x33是DOS中断,是在DOS下通过调用中断来对鼠标进行操作.
}

void MouseSetXY(int x, int y)		//设置当前位置
{
	_CX = x;
	_DX = y;
	_AX = 0x04;
	geninterrupt(0x33);
}

void MouseRangeX(int lx, int rx)		//设置x边界
{
	_CX = lx;
	_DX = rx;
	_AX = 0x07;
	geninterrupt(0x33);
}

void MouseRangeY(int uy, int dy)		//设置y边界
{
	_CX = uy;
	_DX = dy;
	_AX = 0X08;
	geninterrupt(0x33);
}


int LeftPress(void)					//鼠标左键按下
{
	_AX = 0x03;
	geninterrupt(0x33);
	return(_BX & 1);
}

int MiddlePress(void)					//鼠标中键按下
{
	_AX = 0x03;
	geninterrupt(0x33);
	return(_BX & 4);
}

int RightPress(void)					//鼠标右键按下
{
	_AX = 0x03;
	geninterrupt(0x33);
	return(_BX & 2);
}

/*获取鼠标当前位置*/
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

//如果在框中点击，则返回1；在框中未点击，则返回2；不在框中则返回0

int mouse_press(int x1, int y1, int x2, int y2)
{
	//在框中点击，则返回1
	if (MouseX > x1
		&& MouseX < x2
		&& MouseY > y1
		&& MouseY < y2
		&& LeftPress())
	{
		return 1;
	}

	//在框中未点击，则返回2
	else if (MouseX > x1
		&& MouseX < x2
		&& MouseY > y1
		&& MouseY < y2
		&& LeftPress() != 1)
	{
		return 2;
	}

	//在框中点击右键，则返回3
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

 //判断鼠标是否移动
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
//与mouseon类似，只不过加了参数，可以换鼠标，用于游戏中
void MouseOn_type(int x, int y, int type)
{
	int i, j;
	int color;

	switch (type)
	{
	case 1:
		for (i = 0; i < 16; i++)/*画鼠标*/
		{
			for (j = 0; j < 16; j++)
			{
				pixel_save[i][j] = getpixel(x + j, y + i);/*保存原来的颜色*/
				if (mouse_draw[i][j] == 1)
					putpixel(x + j, y + i, BLACK);
				else if (mouse_draw[i][j] == 2)
					putpixel(x + j, y + i, WHITE);
			}
		}
		break;
	case 2:
		for (i = 0; i < 16; i++)/*画小刀*/
		{
			for (j = 0; j < 16; j++)
			{
				pixel_save[i][j] = getpixel(x + j, y + i);/*保存原来的颜色*/
				if (sword[i][j] == 1)
					putpixel(x + j, y + i, BLACK);
				else if (sword[i][j] == 2)
					putpixel(x + j, y + i, WHITE);
			}
		}
		break;
	case 3:
		for (i = 0; i < 25; i++)/*画长剑*/
		{
			for (j = 0; j < 25; j++)
			{
				pixel_save1[i][j] = getpixel(x + j, y + i);/*保存原来的颜色*/
				if (sword1[i][j] == 1)
					putpixel(x + j, y + i, BLACK);
				else if (sword1[i][j] == 2)
					putpixel(x + j, y + i, WHITE);
			}
		}
		break;
	}

}
/*隐藏鼠标*/
void MouseOff_type(int type)
{
	int i, j, x, y, color;
	x = MouseX;//全局变量
	y = MouseY;//全局变量

	switch (type)
	{
	case 1:
		for (i = 0; i < 16; i++)/*原位置异或消去*/
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
		for (i = 0; i < 16; i++)/*原位置异或消去*/
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
		for (i = 0; i < 25; i++)/*原位置异或消去*/
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
void MouseDelay_type(int n, int type)//在延迟的情况下画鼠标
{
	int x, y;
	int status;
	int xx, yy;
	int i, j, color, k;
	for (k = 0; k < n; k++)
	{
		x = MouseX;
		y = MouseY;
		delay(10);                                   //延迟10毫秒
		MouseGetMXY();                               //将鼠标当前位置写进全局变量
		if (MouseX != x || MouseY != y)           	//移动情况才重新显示鼠标
		{
			switch (type)
			{
			case 1:
				for (i = 0; i < 16; i++)/*原位置异或消去*/
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
				for (i = 0; i < 16; i++)/*原位置异或消去*/
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
				for (i = 0; i < 25; i++)/*原位置异或消去*/
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

			MouseOn_type(MouseX, MouseY, type);//新位置显示
		}
	}
}

/**************************************************************
Function: draw_scratch
Description:鼠标划痕
Calls
Input:int* p（存放鼠标历史点的数组）, int* status（鼠标状态）
Return:
Others：
采用了队列的思想，绘制二十个点连成的鼠标划痕
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
			//若上一次松开鼠标，清空队列
			for (i = 0; i < SCRATCH; i++)
			{
				p[i] = -1;
			}
			*status = 0;
		}
		if (p[SCRATCH - 1] != -1)
		{
			//若满则出队
			for (i = 0; i < SCRATCH - 2; i++)
			{
				p[i] = p[i + 2];
			}
			p[SCRATCH - 2] = -1;
			p[SCRATCH - 1] = -1;
		}
		//入队
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
		//出队
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


