/**************************************************************
Filename：user.c   Author: 田铭   Version:1.0   Date:10.19
Description:该文件包含了登录、注册文件的函数
Function List:
	1.AddUser//向用户文件中添加用户
	2.SearchUser// 检查用户名、密码是否正确
	3.SearchName//查找是否有相同用户名
	4.ChangeUser//将用户临时文件的数据写进用户文件
	5.GetScore//获取所有玩家的最高分
	6.ChangeScore//将玩家新的最高分写进临时文件
	7.Compare// 玩家获得分数与玩家的最高分进行比较
	8.CompareH//玩家获得分数与所有玩家的最高分进行比较
History： 10.22写注释
<author>  <time> <version> <desc>
田铭    19/10/22  1.0    build this module
***************************************************************/

/*******************
用户文件目录组成：
int  count  个数
char username[]
char password[]
int score[3]
********************/

#include"user.h"
#include"main.h"
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>

/**************************************************************
Function:AddUser
Description:向用户文件中添加用户
Calls:
Input:User p
Return:
Others:
***************************************************************/
void AddUser(User p)
{
	FILE* fp, * tfp;
	int count;
	fp = fopen(USERFILE, "r+");
	if (fp == NULL)
		puts("open file wrong");
	tfp = fopen(TUSERFILE, "r+");
	if (tfp == NULL)
	{
		puts("user temporary file open wrong");
	}
	fscanf(fp, "%3d", &count);
	fseek(fp, 0, 2);
	fprintf(fp, IFPRMAT, p.username, p.password, 0, 0, 0);
	count++;
	rewind(fp);
	fprintf(fp, "%3d", count);
	fclose(fp);
	rewind(tfp);
	fprintf(tfp, IFPRMAT, p.username, p.password, 0, 0, 0);
	fclose(tfp);
}

/**************************************************************
Function:SearchUser
Description: 检查用户名、密码是否正确
Calls:
Input:User p
Return:
Others:
***************************************************************/
int SearchUser(User p)
{
	FILE* fp, * tfp;
	User cmp;
	int i, n, sta = 0;
	fp = fopen(USERFILE, "r+");
	if (fp == NULL)
		puts("open file wrong");
	tfp = fopen(TUSERFILE, "r+");
	if (tfp == NULL)
		puts("t userfile open wrong");
	fscanf(fp, "%3d", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(fp, IFPRMAT, cmp.username, cmp.password, &cmp.score[0], &cmp.score[1], &cmp.score[2]);
		if (strcmp(cmp.username, p.username) == 0 && strcmp(cmp.password, p.password) == 0)
		{
			sta++;
			rewind(tfp);
			fprintf(tfp, IFPRMAT, cmp.username, cmp.password, cmp.score[0], cmp.score[1], cmp.score[2]);
			fclose(tfp);
			break;
		}
	}
	rewind(fp);
	fclose(fp);
	return sta;
}


/**************************************************************
Function:SearchName
Description: 查找是否有相同用户名
Calls:
Input:User p
Return:
Others:
***************************************************************/
int SearchName(User p)
{
	FILE* fp;
	User cmp;
	int i, count, sta = 0;
	fp = fopen(USERFILE, "r+");
	if (fp == NULL)
	{
		puts("open file wrong");
	}
	rewind(fp);
	fscanf(fp, "%3d", &count);
	for (i = 0; i < count; i++)
	{
		fscanf(fp, IFPRMAT, cmp.username, cmp.password, &cmp.score[0], &cmp.score[1], &cmp.score[2]);
		if (strcmp(p.username, cmp.username) == 0)
			sta++;
	}
	rewind(fp);
	fclose(fp);
	return sta;
}


/**************************************************************
Function:ChangeUser
Description: 将用户临时文件的数据写进用户文件
Calls:
Input:
Return:
Others:
***************************************************************/
void ChangeUser(void)
{
	FILE* fp, * fpm, * tfp;
	User user, tuser, fuser;
	int i, n, sta;
	fp = fopen(USERFILE, "r+");
	if (fp == NULL)
	{
		puts("open file wrong");
		exit(0);
	}

	fpm = fopen(FUSERFILE, "wr+");
	if (fpm == NULL)
	{
		puts("open file wrong");
		exit(0);
	}

	tfp = fopen(TUSERFILE, "r+");
	if (tfp == NULL)
	{
		puts("t userfile open wrong");
		exit(0);
	}

	fscanf(tfp, IFPRMAT, tuser.username, tuser.password, &tuser.score[0], &tuser.score[1], &tuser.score[2]);
	rewind(tfp);
	fclose(tfp);
	rewind(fp);
	rewind(fpm);
	fscanf(fp, "%3d", &n);
	fprintf(fpm, "%3d", n);
	for (i = 0; i < n; i++)
	{
		fscanf(fp, IFPRMAT, user.username, user.password, &user.score[0], &user.score[1], &user.score[2]);
		if (strcmp(user.username, tuser.username) != 0)
		{
			fprintf(fpm, IFPRMAT, user.username, user.password, user.score[0], user.score[1], user.score[2]);
		}
		else
		{
			fprintf(fpm, IFPRMAT, tuser.username, tuser.password, tuser.score[0], tuser.score[1], tuser.score[2]);
		}
	}
	rewind(fp);
	rewind(fpm);
	fclose(fp);
	fclose(fpm);
	sta = remove(USERFILE);
	if (sta != 0)
	{
		puts("remove file fail");
	}
	sta = rename(FUSERFILE, USERFILE);
	if (sta != 0)
	{
		puts("rename file fail");
	}
}


/**************************************************************
Function:GetScore
Description: 获取所有玩家的最高分；
Calls:
Input:char* name[3], int* score
Return:
Others:
***************************************************************/
void GetScore(char* name[3], int* score)
{
	int i;

	FILE* hfp;
	hfp = fopen(FHIGH, "r");
	if (hfp == NULL)
		puts("open highestscore file wrong");
	rewind(hfp);
	for (i = 0; i < 3; i++)
	{
		fscanf(hfp, "%20s%8d", name[i], &score[i]);
	}

	rewind(hfp);
	fclose(hfp);
}


/**************************************************************
Function:ChangeScore
Description: 将玩家新的最高分写进临时文件
Calls:
Input:int n, int sco
Return:
Others:
***************************************************************/
void ChangeScore(int n, int sco)
{
	FILE* fp;
	User user;
	fp = fopen(TUSERFILE, "r+");
	if (fp == NULL)
		puts("open t userfile wrong");
	fscanf(fp, IFPRMAT, user.username, user.password, &user.score[0], &user.score[1], &user.score[2]);
	rewind(fp);
	user.score[n - 1] = sco;
	fprintf(fp, IFPRMAT, user.username, user.password, user.score[0], user.score[1], user.score[2]);
	rewind(fp);
	fclose(fp);
}


/**************************************************************
Function:ChangeScore
Description: 玩家获得分数与玩家的最高分进行比较
Calls:
Input:int n, int sco
Return:比最高分高返回1；比最高分少返回0；
Others:
***************************************************************/
int Compare(int n, int sco)
{
	FILE* fp;
	User user;
	fp = fopen(TUSERFILE, "r+");
	if (fp == NULL)
		puts("open tuserfile wrong");
	fscanf(fp, IFPRMAT, user.username, user.password, &user.score[0], &user.score[1], &user.score[2]);
	rewind(fp);
	fclose(fp);
	if (user.score[n - 1] < sco)
	{
		return 1;
	}
	else
		return 0;
}


/**************************************************************
Function:ChangeScore
Description: 玩家获得分数与所有玩家的最高分进行比较
Calls:
Input:int n, int sco
Return:比最高分高返回1；比最高分少返回0；
Others:
***************************************************************/
int CompareH(int  n, int score)
{
	int i, sco;
	char* name = NULL;
	FILE* hfp;
	hfp = fopen(FHIGH, "r");
	if (hfp == NULL)
		puts("open highestscore file wrong");
	rewind(hfp);
	for (i = 0; i < n; i++)
	{
		fscanf(hfp, "%20s%8d", name, &sco);
	}
	rewind(hfp);
	fclose(hfp);
	if (score > sco)
	{
		return 1;
	}
	else
		return 0;
}

/***************************************************
将玩家的分数写进最高分文件；
*****************************************************/

void ChangeHSco(int n, int sco)
{
	FILE* fp, * hfp, * fpm;
	char name[3][20];
	int i, s[3], sta;
	User user;
	fp = fopen(TUSERFILE, "r");
	if (fp == NULL)
		puts("open t userfile wrong");
	fscanf(fp, IFPRMAT, user.username, user.password, &user.score[0], &user.score[1], &user.score[2]);
	rewind(fp);
	fclose(fp);
	hfp = fopen(FHIGH, "r+");
	if (hfp == NULL)
		puts("open highest userfile wrong");
	fpm = fopen(FHIGHM, "wr+");
	if (fpm == NULL)
		puts("build highest userfile wrong");
	switch (n)
	{
	case 1:
	{
		rewind(fpm);
		rewind(hfp);
		fscanf(hfp, "%20s%8d%20s%8d%20s%8d", name[0], &s[0], name[1], &s[1], name[2], &s[2]);
		fprintf(fpm, "%20s%8d%20s%8d%20s%8d", user.username, sco, name[1], s[1], name[2], s[2]);
		break;
	}
	case 2:
	{
		rewind(fpm);
		rewind(hfp);
		fscanf(hfp, "%20s%8d%20s%8d%20s%8d", name[0], &s[0], name[1], &s[1], name[2], &s[2]);
		fprintf(fpm, "%20s%8d%20s%8d%20s%8d", name[0], s[0], user.username, sco, name[2], s[2]);
		break;
	}
	case 3:
	{
		rewind(fpm);
		rewind(hfp);
		fscanf(hfp, "%20s%8d%20s%8d%20s%8d", name[0], &s[0], name[1], &s[1], name[2], &s[2]);
		fprintf(fpm, "%20s%8d%20s%8d%20s%8d", name[0], s[0], name[1], s[1], user.username, sco);
		break;
	}
	default:break;
	}

	rewind(hfp);
	fclose(hfp);
	rewind(fpm);
	fclose(fpm);
	sta = remove(FHIGH);
	if (sta != 0)
	{
		puts("remove file fail");
	}
	sta = rename(FHIGHM, FHIGH);
	if (sta != 0)
	{
		puts("rename file fail");
	}
}

/*********************************************
初始化玩家最高分
**********************************************/

void InitHigh(void)
{
	FILE* hfp;
	char* name = "wang";
	int i, s;
	s = 0;
	hfp = fopen(FHIGH, "r+");
	if (hfp == NULL)
		puts("open highest userfile wrong");
	rewind(hfp);
	fprintf(hfp, "%20s%8d%20s%8d%20s%8d", name, s, name, s, name, s);
	rewind(hfp);
	fclose(hfp);
}