/**************************************************************
Filename��log.c  Author: ������   Version:1.0   Date:10.19
Description:���ļ������˿�����־ҳ�����غ���
Function List:
	   1.int userlog(void)
History�� 10.22дע��
<author>  <time> <version> <desc>
������    19/10/19  1.0    build this module
***************************************************************/
#include"common.h"
#include"log.h"
int userlog (void)
{
	int i = 0, j = 0, i0;
	int page = 7;
	FILE* fp;
	char ch, a[10][100] = { 0 };
	delay(100);
	cleardevice();

	setbkcolor(BLACK);

	setfillstyle(SOLID_FILL, BROWN);
	bar(0, 0, 640, 480);
	puthz(10, 460, "����", 16, 16, WHITE);
	MouseOn(MouseX, MouseY);

	if ((fp = fopen("log.txt", "rt")) == NULL)
	{
		printf("error!");
	}
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')//�жϻس���
		{
			a[i][j] = '\0';//�ַ���ĩβҪ�ӡ�\0��
			i++;
			j = 0;
		}
		else
		{
			a[i][j] = ch;
			j++;
		}
	}
	a[i][j] = '\0';
	i0 = i;
	for (i = 0; i <= i0; i++)
	{
		puthz(0, i * 24, a[i], 24, 24, WHITE);
	}
	fclose(fp);
	while (page == 7)
	{
		MouseStatus();
		if (mouse_press(0, 460, 50, 480) == 1)
		{
			delay(150);
			return 4;
		}
	}
	return 4;
}
