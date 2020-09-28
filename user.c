/**************************************************************
Filename��user.c   Author: ����   Version:1.0   Date:10.19
Description:���ļ������˵�¼��ע���ļ��ĺ���
Function List:
	1.AddUser//���û��ļ�������û�
	2.SearchUser// ����û����������Ƿ���ȷ
	3.SearchName//�����Ƿ�����ͬ�û���
	4.ChangeUser//���û���ʱ�ļ�������д���û��ļ�
	5.GetScore//��ȡ������ҵ���߷�
	6.ChangeScore//������µ���߷�д����ʱ�ļ�
	7.Compare// ��һ�÷�������ҵ���߷ֽ��бȽ�
	8.CompareH//��һ�÷�����������ҵ���߷ֽ��бȽ�
History�� 10.22дע��
<author>  <time> <version> <desc>
����    19/10/22  1.0    build this module
***************************************************************/

/*******************
�û��ļ�Ŀ¼��ɣ�
int  count  ����
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
Description:���û��ļ�������û�
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
Description: ����û����������Ƿ���ȷ
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
Description: �����Ƿ�����ͬ�û���
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
Description: ���û���ʱ�ļ�������д���û��ļ�
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
Description: ��ȡ������ҵ���߷֣�
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
Description: ������µ���߷�д����ʱ�ļ�
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
Description: ��һ�÷�������ҵ���߷ֽ��бȽ�
Calls:
Input:int n, int sco
Return:����߷ָ߷���1������߷��ٷ���0��
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
Description: ��һ�÷�����������ҵ���߷ֽ��бȽ�
Calls:
Input:int n, int sco
Return:����߷ָ߷���1������߷��ٷ���0��
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
����ҵķ���д����߷��ļ���
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
��ʼ�������߷�
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