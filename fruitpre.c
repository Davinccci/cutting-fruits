/**************************************************************
Filename：fruitpre.c  Author: 田铭   Version:1.0   Date:10.19
Description:该文件包含了水果运动前初始化的相关函数
Function List:
	1.void fruit1_init(FRUIT* f1, int n)                     //总水果初始化，为每个水果附上type值，方便之后分类调用
	2.void fruit2_init(FRUIT* f1, FRUIT* f2, int n)     //每一波水果初始化，随机从fruit1里选n个水果给fruit2
	3.void path_init(FRUIT* f2, int n)                      //水果路径初始化，为每个水果随机赋值（x,y,vx,vy）
	4.void path(FRUIT* f2, int n, User0* user, int* p, int* status, int* kp_status)  //使水果按规律出现在下一帧
	5.void Putimage(FRUIT* f, int i)                        //综合画水果，根据水果类型读取相应文件，通过白与黑或的形式绘制到屏幕上
History： 10.22写注释
<author>  <time> <version> <desc>
田铭    19/10/19  1.0    build this module
***************************************************************/

#include"common.h"
#include"fruitpre.h"

/**************************************************************
Function:fruit1_init
Description:总水果初始化，为每个水果附上type值，方便之后分类调用
Calls:
Input:FRUIT* f1, int n
Return:
Others:
***************************************************************/
void fruit1_init(FRUIT* f1, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		f1[i].type = i;
	}
}

/**************************************************************
Function:fruit2_init
Description:每一波水果初始化，随机从fruit1里选n个水果给fruit2
Calls:
Input:FRUIT* f1, FRUIT* f2, int n
Return:
Others:
***************************************************************/
void fruit2_init(FRUIT* f1, FRUIT* f2, int n)
{
	int i, k;
	randomize();
	for (i = 0; i < n; i++)
	{
		k = random(8);
		f2[i] = f1[k];
	}

}

/**************************************************************
Function:path_init
Description:水果路径初始化，为每个水果随机赋值（x,y,vx,vy）
Calls:
Input:FRUIT* f2, int n
Return:
Others:
***************************************************************/
void path_init(FRUIT* f2, int n)
{
	int i, j;
	int initial_vx, initial_vy;
	randomize();
	for (i = 0; i < n; i++)
	{
		j = random(640);
		f2[i].x = j;
		f2[i].y = 480;
		f2[i].status = 0;
		initial_vx = random(12) + 5;
		initial_vy = random(5) + 20;
		if (f2[i].x > 320)
		{
			f2[i].vx = -initial_vx;
		}
		else
		{
			f2[i].vx = initial_vx;
		}
		f2[i].vy = initial_vy;
	}
}

/**************************************************************
Function:path
Description:使水果按规律出现在下一帧
Calls:background
      combo_judge
	  draw_scratch
Input:FRUIT* f2, int n, User0* user, int* p, int* status, int* kp_status
Return:
Others:
***************************************************************/
void path(FRUIT* f2, int n, User0* user, int* p, int* status, int* kp_status)
{
	int i;
	float g = 1;                                 //垂直向下加速度
	for (i = 0; i < n; i++)
	{
		if (f2[i].status != 1)       //1是被切状态
		{
			//更新轨迹（物理引擎）
			f2[i].x = f2[i].x + f2[i].vx;
			f2[i].y = 480 - ((480 - f2[i].y) + f2[i].vy);
			f2[i].vy = f2[i].vy - g;
		}
		else
		{                                          //若已被切，则轨迹变为掉落
			f2[i].y = 480 - ((480 - f2[i].y) + f2[i].vy);
			f2[i].vy = f2[i].vy - 9 * g;
		}
	}
	
	background();	                      //清空上一帧水果
	combo_judge(kp_status);       //画出连击
	draw_scratch(p, status);         //画出鼠标划痕
	
	if (MouseY > 50)                    //若鼠标在可显示区，则画鼠标，可使鼠标显示更流畅
	{
		MouseOn_type(MouseX, MouseY, user->mouse_type);
	}
	for (i = 0; i < n; i++)
	{
		//若未被切，则画出		
		if (f2[i].status != 1)
		{
			if (f2[i].x > 0 && f2[i].y > 0)
			{
				Putimage(f2, i);
			}
		}
		else
		{                    //若被切，则画被切开后的水果碎片
			switch (f2[i].type)
			{
			case 0:
				setfillstyle(SOLID_FILL, BLACK);
				setcolor(BLACK);
				fillellipse(f2[i].x, f2[i].y, 15, 15);
				break;
			case 1:
				setfillstyle(SOLID_FILL, RED);
				setcolor(RED);
				pieslice(f2[i].x, f2[i].y, 120, 300, 15);
				pieslice(f2[i].x + 30, f2[i].y, 240, 420, 15);
				break;
			case 2:
				setfillstyle(SOLID_FILL, YELLOW);
				setcolor(YELLOW);
				fillellipse(f2[i].x, f2[i].y, 15, 15);
				break;
			case 3:
				setfillstyle(SOLID_FILL, YELLOW);
				setcolor(YELLOW);
				pieslice(f2[i].x, f2[i].y, 120, 300, 15);
				pieslice(f2[i].x + 30, f2[i].y, 240, 420, 15);
				break;
			case 4:
				setfillstyle(SOLID_FILL, YELLOW);
				setcolor(YELLOW);
				fillellipse(f2[i].x, f2[i].y, 15, 15);
				break;
			case 5:
				setfillstyle(SOLID_FILL, RED);
				setcolor(RED);
				pieslice(f2[i].x, f2[i].y, 120, 300, 15);
				pieslice(f2[i].x + 30, f2[i].y, 240, 420, 15);
				break;
			case 6:
				setfillstyle(SOLID_FILL, LIGHTRED);
				setcolor(LIGHTRED);
				pieslice(f2[i].x, f2[i].y, 120, 300, 15);
				pieslice(f2[i].x + 30, f2[i].y, 240, 420, 15);
				break;
			case 7:
				setfillstyle(SOLID_FILL, RED);
				setcolor(GREEN);
				pieslice(f2[i].x, f2[i].y, 120, 300, 30);
				pieslice(f2[i].x + 60, f2[i].y, 240, 420, 30);
			}
		}
	}
}


/**************************************************************
Function:Putimage
Description:综合画水果，根据水果类型读取相应文件，通过白与黑或的形式绘制到屏幕上
Calls:background
      combo_judge
	  draw_scratch
Input:(FRUIT* f, int i
Return:
Others:
***************************************************************/
void Putimage(FRUIT* f, int i)
{

	FILE* fp;
	unsigned s;
	//将文件中存储的图像点读出
	switch (f[i].type) 
	{
	case 0://炸弹
		s = imagesize(0, 0, 130, 130);
		fp = fopen("fruits\\boom1.dat", "rb");
		f[i].image1 = malloc(s);
		fread(f[i].image1, s, 1, fp);
		fclose(fp);
		fp = fopen("fruits\\boom2.dat", "rb");
		s = imagesize(0, 0, 130, 130);
		f[i].image2 = malloc(s);
		fread(f[i].image2, s, 1, fp);
		fclose(fp);
		break;
	case 1:
		s = imagesize(0, 0, 100, 100);
		fp = fopen("fruits\\apple1.dat", "rb");
		f[i].image1 = malloc(s);
		fread(f[i].image1, s, 1, fp);
		fclose(fp);
		fp = fopen("fruits\\apple2.dat", "rb");
		s = imagesize(0, 0, 100, 100);
		f[i].image2 = malloc(s);
		fread(f[i].image2, s, 1, fp);
		fclose(fp);
		break;
	case 2:
		s = imagesize(0, 0, 100, 100);
		fp = fopen("fruits\\lemon1.dat", "rb");
		f[i].image1 = malloc(s);
		fread(f[i].image1, s, 1, fp);
		fclose(fp);
		fp = fopen("fruits\\lemon2.dat", "rb");
		s = imagesize(0, 0, 100, 100);
		f[i].image2 = malloc(s);
		fread(f[i].image2, s, 1, fp);
		fclose(fp);
		break;
	case 3:
		s = imagesize(0, 0, 100, 100);
		fp = fopen("fruits\\pear1.dat", "rb");
		f[i].image1 = malloc(s);
		fread(f[i].image1, s, 1, fp);
		fclose(fp);
		fp = fopen("fruits\\pear2.dat", "rb");
		s = imagesize(0, 0, 100, 100);
		f[i].image2 = malloc(s);
		fread(f[i].image2, s, 1, fp);
		fclose(fp);
		break;
	case 4:
		s = imagesize(0, 0, 100, 100);
		fp = fopen("fruits\\banana1.dat", "rb");
		f[i].image1 = malloc(s);
		fread(f[i].image1, s, 1, fp);
		fclose(fp);
		fp = fopen("fruits\\banana2.dat", "rb");
		s = imagesize(0, 0, 100, 100);
		f[i].image2 = malloc(s);
		fread(f[i].image2, s, 1, fp);
		fclose(fp);
		break;
	case 5:
		s = imagesize(0, 0, 100, 100);
		fp = fopen("fruits\\straw1.dat", "rb");
		f[i].image1 = malloc(s);
		fread(f[i].image1, s, 1, fp);
		fclose(fp);
		fp = fopen("fruits\\straw2.dat", "rb");
		s = imagesize(0, 0, 100, 100);
		f[i].image2 = malloc(s);
		fread(f[i].image2, s, 1, fp);
		fclose(fp);
		break;
	case 6:
		s = imagesize(0, 0, 100, 100);
		fp = fopen("fruits\\peach1.dat", "rb");
		f[i].image1 = malloc(s);
		fread(f[i].image1, s, 1, fp);
		fclose(fp);
		fp = fopen("fruits\\peach2.dat", "rb");
		s = imagesize(0, 0, 100, 100);
		f[i].image2 = malloc(s);
		fread(f[i].image2, s, 1, fp);
		fclose(fp);
		break;
	case 7:
		s = imagesize(0, 0, 130, 130);
		fp = fopen("fruits\\water1.dat", "rb");
		f[i].image1 = malloc(s);
		fread(f[i].image1, s, 1, fp);
		fclose(fp);
		fp = fopen("fruits\\water2.dat", "rb");
		s = imagesize(0, 0, 130, 130);
		f[i].image2 = malloc(s);
		fread(f[i].image2, s, 1, fp);
		fclose(fp);
		break;
	}
    //将水果画到当前位置
	putimage(f[i].x, f[i].y, f[i].image2, AND_PUT); //白色"与"写入    防止自己边界遮盖下面的水果
	putimage(f[i].x, f[i].y, f[i].image1, OR_PUT);//黑色"或"写入   把本体水果部分补出
	free(f[i].image2);
	free(f[i].image1);
}






