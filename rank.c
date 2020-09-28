/**************************************************************
Filename��rank.c   Author: ����    Version:1.0   Date:10.19
Description:���ļ����������а�������غ���
Function List:
	1.rank_main//���а�ҳ��ġ�����������������и������а������������
	2.DrawRankList//���а�ҳ��Ļ�ͼ����
	3.RankList_A//��ʾ����ģʽ���а�����
 	4.RankList_B//��ʾ�ֻ�ģʽ���а�����
 	5.RankList_C//��ʾ�ɾ����а�����	
	6.ChangeUser_A//��֮ǰ�û�����ģʽ�÷ָ���
    7.ChangeUser_B//��֮ǰ�û��ֻ�ģʽ�÷ָ���	
	8.ChangeUser_C//��֮ǰ�û��ɾ����а�÷ָ���
    9.Search_Name//����֮ǰ���а����������û�
	10.Write//�������빦�ܣ�ͬʱ��������ַ������ַ���
	11.DrawFind//������������
	12.FindRank//�����û�����������κ͵÷�
	
History�� 10.28дע��
<author>  <time> <version> <desc>
 �� ��   19/10/22  1.0     build this module
***************************************************************/


#include "common.h"
#include "rank.h"
#include"hz1.h"
#include"hz.h"
#include"user.h"


/**************************************************************
Function:ach_main
Description:���а�ҳ��ġ�����������������и������а������������
Calls:
	 1.Search_Name
	 2.ChangeUser_A
	 3.ChangeUser_B
	 4.ChangeUser_C
	 5.DrawRankList
	 6.RankList_A
	 7.RankList_B
	 8.RankList_C
Input:User0 *now_user
Return:page
Others:
***************************************************************/
int rank_main(User0 *now_user)
{	
    int i,j;
    int mode = NORMAL,pmode = NORMAL;
	int sta,ssta;
	int sta_1, sta_2, sta_3;
	int count;
	int page = 2;
	RankMan user_now;
	RankMan temp;	
    RankMan *list1 = NULL;
    RankMan *list2 = NULL;
    RankMan *list3 = NULL;	
	FILE *fp,*ffp,*fffp;
	
	
	//�ѵ�ǰ�û���Ϣ����user_now
	strcpy(user_now.username,now_user->ID);	
    user_now.score[0]=now_user->score[0];
	user_now.score[1]=now_user->score[1];
    user_now.score[2]=now_user->score[2];
	
	
	//�õ����а��ļ����û�����
	fp = fopen(USERNUM,"r+");
    if(fp == NULL)
    {
        printf("open file wrong");
    }

	fscanf(fp, "%3d", &count);	
	rewind(fp);
    fclose(fp);
	


/***********************************
�����user_now�ǵ�һ���û�,��ֱ�ӽ���Ϣд���ļ�
***********************************/
	if(count == 0)
	{
		//��1д��ͳ���û��������ļ�
		count = 1;
	    fp = fopen(FUSERNUM,"wr+");

		fprintf(fp, "%3d", count);	
		rewind(fp);
		fclose(fp);
		
	    sta = remove(USERNUM);//ɾ��ָ���ļ�,�ɹ�����0
	    if (sta != 0)		
	    {
		    printf("remove file fail");
	    }	
	
        ssta = rename(FUSERNUM,USERNUM);	//���ĺ�����,�ɹ�����0
        if (ssta != 0)
        {
		    printf("rename file fail");
	    }		
		
		
		//�ѵ�ǰ�û���Ϣд����һ�����а�
        ffp = fopen(USERFILE_1,"wb");		
        fwrite(&user_now, sizeof(RankMan), 1, ffp);
		rewind(ffp);
		fclose(ffp);
		
		//��ǰ�û���Ϣд���ڶ������а�
        fp = fopen(USERFILE_2,"wb");		
        fwrite(&user_now, sizeof(RankMan), 1, ffp);
		rewind(fp);
		fclose(fp);	

		//��ǰ�û���Ϣд�����������а�
        ffp = fopen(USERFILE_3,"wb");		
        fwrite(&user_now, sizeof(RankMan), 1, ffp);
		rewind(ffp);
		fclose(ffp);		

	}	
	
	
/*******************************************
������ǵ�һ���û�,���Ƚ��ļ���Ϣ���ṹ����
*******************************************/	
	else if(count > 0)
	{  
            list1 = (RankMan*)malloc((count+1) * sizeof(RankMan));
            list2 = (RankMan*)malloc((count+1) * sizeof(RankMan));	
            list3 = (RankMan*)malloc((count+1) * sizeof(RankMan));	
			
            //��һ���ļ���Ϣ���ṹ����			
			fffp = fopen(USERFILE_1,"rb+");
            if(fffp == NULL)
            {
                printf("open file wrong");
            }          
            fread(list1, sizeof(RankMan),count,fffp);//���ļ����ṹ����
		    rewind(fffp);
			fclose(fffp);
			
			//�ڶ����ļ���Ϣ���ṹ����
			fffp = fopen(USERFILE_2,"rb+");
            if(fffp == NULL)
            {
                printf("open file wrong");
            }           
            fread(list2, sizeof(RankMan),count,fffp);//���ļ����ṹ����
		    rewind(fffp);
			fclose(fffp);	

			//�������ļ���Ϣ���ṹ����
			fffp = fopen(USERFILE_3,"rb+");
            if(fffp == NULL)
            {
                printf("open file wrong");
            }           
            fread(list3, sizeof(RankMan),count,fffp);//���ļ����ṹ����
		    rewind(fffp);
			fclose(fffp);				
			
					
			
			
            //�����֮ǰδ�е��û�,ֱ�Ӳ����������			
            if (Search_Name(user_now, list1, list2, list3, count, &sta_1, &sta_2, &sta_3) == 0)
			{
				//����Ԫ�ظ�list
				
				strcpy(list1[count].username,user_now.username);
			    list1[count].score[0] = user_now.score[0];
				list1[count].score[1] = user_now.score[1];
				list1[count].score[2] = user_now.score[2];	
				
				strcpy(list2[count].username,user_now.username);
			    list2[count].score[0] = user_now.score[0];
				list2[count].score[1] = user_now.score[1];
				list2[count].score[2] = user_now.score[2];				

				strcpy(list3[count].username,user_now.username);
			    list3[count].score[0] = user_now.score[0];
				list3[count].score[1] = user_now.score[1];
				list3[count].score[2] = user_now.score[2];				

				
				//��һ�����а���������
				for(i = 0; i < count; i++)
				{
                    for(j = i+1; j<	(count +1); j++)
                    {
                        if(list1[i].score[0] < list1[j].score[0])
						{
							strcpy(temp.username,list1[i].username);
							temp.score[0] = list1[i].score[0];
							temp.score[1] = list1[i].score[1];
							temp.score[2] = list1[i].score[2];
							
							strcpy(list1[i].username,list1[j].username);
							list1[i].score[0] = list1[j].score[0];
							list1[i].score[1] = list1[j].score[1];
							list1[i].score[2] = list1[j].score[2];							
							

							strcpy(list1[j].username,temp.username);
							list1[j].score[0] = temp.score[0];
							list1[j].score[1] = temp.score[1];
							list1[j].score[2] = temp.score[2];	
							

						}
                    }
                }
				//�ڶ������а���������
				for(i = 0; i < count; i++)
				{
                    for(j = i+1; j<	(count +1); j++)
                    {
                        if(list2[i].score[1] < list2[j].score[1])
						{
							
							strcpy(temp.username,list2[i].username);
							temp.score[0] = list2[i].score[0];
							temp.score[1] = list2[i].score[1];
							temp.score[2] = list2[i].score[2];
							
							strcpy(list2[i].username,list2[j].username);
							list2[i].score[0] = list2[j].score[0];
							list2[i].score[1] = list2[j].score[1];
							list2[i].score[2] = list2[j].score[2];							
							

							strcpy(list2[j].username,temp.username);
							list2[j].score[0] = temp.score[0];
							list2[j].score[1] = temp.score[1];
							list2[j].score[2] = temp.score[2];	
							

						}
                    }
                }	
				//���������а���������
				for(i = 0; i < count; i++)
				{
                    for(j = i+1; j<	(count +1); j++)
                    {
                        if(list3[i].score[2] < list3[j].score[2])
						{
							
							strcpy(temp.username,list3[i].username);
							temp.score[0] = list3[i].score[0];
							temp.score[1] = list3[i].score[1];
							temp.score[2] = list3[i].score[2];
							
							strcpy(list3[i].username,list3[j].username);
							list3[i].score[0] = list3[j].score[0];
							list3[i].score[1] = list3[j].score[1];
							list3[i].score[2] = list3[j].score[2];							
							

							strcpy(list3[j].username,temp.username);
							list3[j].score[0] = temp.score[0];
							list3[j].score[1] = temp.score[1];
							list3[j].score[2] = temp.score[2];	
							

						}
                    }
                }
				
				//���û�����д��ͳ���û��������ļ�
							
				count = count + 1;
				
	            fp = fopen(USERNUM,"wr+");
		        fprintf(fp, "%3d", count);	
		        rewind(fp);
		        fclose(fp);
		
		
					
				//����һ���źõ�����д���ļ�
				fp = fopen(USERFILE_1,"wb");
				rewind(fp);				
				fwrite(list1, sizeof(RankMan),count,fp);
				rewind(fp);
				fclose(fp);
				

			
				//���ڶ����źõ�����д���ļ�
				fp = fopen(USERFILE_2,"wb");
				rewind(fp);				
				fwrite(list2, sizeof(RankMan),count,fp);
				rewind(fp);
				fclose(fp);	
				

				//���������źõ�����д���ļ�
				fp = fopen(USERFILE_3,"wb");
				rewind(fp);				
				fwrite(list3, sizeof(RankMan),count,fp);
				rewind(fp);
				fclose(fp);	
				
                 
				//�����ͷſռ�
				free(list1);
				list1 = NULL;
				free(list2);
				list2 = NULL;
				free(list3);
				list3 = NULL;
            }				


            //�����֮ǰ���е��û�,��user_now�ķ�����֮ǰ�ȶ�
			else if (Search_Name(user_now, list1, list2, list3, count, &sta_1, &sta_2, &sta_3) == 1)
            {
				//�����û�����÷ִ���ԭ������÷�,�����ڵ÷ָ�ԭ�����û���Ϣ,����������
		        if (sta_1 == 1)
		        {
			        ChangeUser_A(user_now, list1, count);
		        }	
                //�����û��ֻ��÷ִ���ԭ������÷�,�����ڵ÷ָ�ԭ�����û���Ϣ,����������			
                if (sta_2 == 1)
		        {	
                    ChangeUser_B(user_now, list2, count);
		        }	
				//�����û��ɾ͵÷ִ���ԭ������÷�,�����ڵ÷ָ�ԭ�����û���Ϣ,����������
                if (sta_3 == 1)	
                {
                    ChangeUser_C(user_now, list3, count);			
                }
				//�����ͷſռ�
				free(list1);
				list1 = NULL;
				free(list2);
				list2 = NULL;
				free(list3);
				list3 = NULL;				
			}
	}	
	
	//�������а�������
	DrawRankList();
	//��ʾ�������а�
	RankList_A();
	mode = NORMAL;
	pmode = NORMAL;
	while(page==2)
	{
		MouseDelay(2);
		if(mouse_press(90, 120, 170, 170)==1)
		{
			if(mode != NORMAL)
			{
				if (pmode == NORMAL)
				{	
	                //�������а�������
	                DrawRankList();
	                //��ʾ�������а�
	                RankList_A();
				    mode = NORMAL;
				}	
			}
		}
		if(mouse_press(90, 220, 170, 270)==1)
		{
			if(mode != ARCADE)
			{
				if (pmode == NORMAL)
				{	
	                //�������а�������
	                DrawRankList();
	                //��ʾ�ֻ����а�
	                RankList_B();
				    mode = ARCADE;
				}	
			}
		}
		if(mouse_press(90, 320, 170, 370)==1)
		{
			if(mode != ACHIEVEMENT)
			{
				if (pmode == NORMAL)
				{	
			        //�������а�������
	                DrawRankList();
	                //��ʾ�ɾ����а�
	                RankList_C();
				    mode = ACHIEVEMENT;
			    }	
			}
		}
		
		if(mouse_press(500,80,550,110) == 1)
		{
			if(pmode != FIND)
			{
				MouseOff();
                DrawFind();
				pmode = FIND;
				MouseOn(MouseX,MouseY);
				FindRank();
			}
		}

        if (mouse_press(450,100,490,140) == 1)
        {
            if (pmode != NORMAL)
            {
                if(mode == NORMAL)
			    {   
	                //�������а�������
	                DrawRankList();
	                //��ʾ�������а�
	                RankList_A();     
                    pmode = NORMAL;	
                    mode = NORMAL;					
                }
                else if(mode == ARCADE)
			    {   
	                //�������а�������
	                DrawRankList();
	                //��ʾ�������а�
	                RankList_B(); 
                    pmode = NORMAL;	
                    mode = ARCADE;					
                }	
                else if(mode == ACHIEVEMENT)
			    {   
	                //�������а�������
	                DrawRankList();
	                //��ʾ�������а�
	                RankList_C();  
					mode = ACHIEVEMENT;
                    pmode = NORMAL;					
                } 
                				
            }
            
        }

	    if(mouse_press(590, 450, 640, 480)==1)
        {
            page = 0;
        }		
    }
	return page;	
}	
	
				
            			

/**************************************************************
Function:DrawRankList
Description:���а�ҳ��Ļ�ͼ����
Calls:
	 1.MouseOff
	 2.MouseOn
	 3.puthz
Input:
Return:
Others:
***************************************************************/
void DrawRankList(void)
{
    cleardevice();
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL,BROWN);
	MouseOff();
    bar(0, 0, 640, 480);	
	setfillstyle(SOLID_FILL,14);
    bar(50, 50, 590, 430);
	setfillstyle(SOLID_FILL,3);
	bar(90, 120, 170, 170);
	bar(90, 220, 170, 270);
	bar(90, 320, 170, 370);
	bar(200, 120, 550, 370);	
	bar(590,450,640,480);
	bar(500,80,550,110);
  	puthz(117,139,"����",16,16,BLACK);
  	puthz(600,460,"����",16,16,BLACK);	
  	puthz(117,239,"�ֻ�",16,16,BLACK);
  	puthz(117,339,"�ɾ�",16,16,BLACK);
  	puthz(230,125,"����",16,16,BLACK);
  	puthz(270,70,"���а�",32,32,BLACK);
  	puthz(350,125,"�û���",16,16,BLACK);
  	puthz(470,125,"�÷�",16,16,BLACK);
	puthz(510,85,"��ѯ",16,16,BLACK);
	MouseOn(MouseX, MouseY);
}


/**************************************************************
Function:RankList_A
Description:��ʾ����ģʽ���а�����
Calls:
	 1.MouseOn
	 2.MouseOff
Input:
Return:
Others:
***************************************************************/
void RankList_A(void)
{
    RankMan *llist1 = NULL;	
	FILE *fp;
	int i,y=0;
	int count;
	char sco[5];
	char rank[5];
	int ranknum = 1;
	settextstyle(3,0,3);
	

	fp = fopen(USERNUM,"r+");
    if(fp == NULL)
    {
        printf("open file wrong");
    }

	fscanf(fp, "%3d", &count);	
	rewind(fp);
    fclose(fp);
	
	llist1 = (RankMan *)malloc(sizeof(RankMan)*count);
	
    fp = fopen(USERFILE_1,"rb+");
    if(fp == NULL)
    {
        printf("open file wrong");
    }          
    fread(llist1, sizeof(RankMan),count,fp);//���ļ����ṹ����
    rewind(fp);
	fclose(fp);	


	MouseOff();	
	setfillstyle(SOLID_FILL,LIGHTGREEN);
	bar(90, 120, 170, 170);	
  	puthz(117,139,"����",16,16,BLACK);	
    setcolor(WHITE);	
	if(count < 10)
	{
        for(i = 0; i < count; i++)
		{
            			
			outtextxy(350,140+y,llist1[i].username);
			itoa(llist1[i].score[0],sco,10);
			outtextxy(470,140+y,sco);
			itoa(ranknum,rank,10);
			outtextxy(230,140+y,rank);			
			y = y + 21;
			ranknum = ranknum + 1;
        }
    }
	
	
    else if(count >= 10)
    {
        for(i = 0; i < 10; i++)
		{

			outtextxy(350,140+y,llist1[i].username);
			itoa(llist1[i].score[0],sco,10);
			outtextxy(470,140+y,sco);	
			itoa(ranknum,rank,10);
			outtextxy(230,140+y,rank);			
			y = y + 21;	
			ranknum = ranknum + 1;			
        }		
    }
	free(llist1);	
	llist1 = NULL;
	MouseOn(MouseX, MouseY);	

}


/**************************************************************
Function:RankList_B
Description:��ʾ�ֻ�ģʽ���а�����
Calls:
	 1.MouseOn
	 2.MouseOff
Input:
Return:
Others:
***************************************************************/
void RankList_B(void)
{
    RankMan *llist2 = NULL;
	FILE *fp;
	int i,y=0;
	int count;
	char sco[5];
	char rank[5];
	int ranknum = 1;
	settextstyle(3,0,3);
	
	
	fp = fopen(USERNUM,"r+");
    if(fp == NULL)
    {
        printf("open file wrong");
    }

	fscanf(fp, "%3d", &count);	
	rewind(fp);
    fclose(fp);
	
	llist2 = (RankMan *)malloc(sizeof(RankMan)*count);	
	
    fp = fopen(USERFILE_2,"rb+");
    if(fp == NULL)
    {
        printf("open file wrong");
    }          
    fread(llist2, sizeof(RankMan),count,fp);//���ļ����ṹ����
    rewind(fp);
	fclose(fp);	

	MouseOff();	
	setfillstyle(SOLID_FILL,LIGHTGREEN);	
	bar(90, 220, 170, 270);	
  	puthz(117,239,"�ֻ�",16,16,BLACK);	
	setcolor(WHITE);
	if(count < 10)
	{
        for(i = 0; i < count; i++)
		{
            			
			outtextxy(350,140+y,llist2[i].username);
			itoa(llist2[i].score[1],sco,10);
			outtextxy(470,140+y,sco);
			itoa(ranknum,rank,10);
			outtextxy(230,140+y,rank);			
			y = y + 21;
			ranknum = ranknum + 1;
        }
    }
	
    else if(count >= 10)
    {
        for(i = 0; i < 10; i++)
		{

			outtextxy(350,140+y,llist2[i].username);
			itoa(llist2[i].score[1],sco,10);
			outtextxy(470,140+y,sco);	
			itoa(ranknum,rank,10);
			outtextxy(230,140+y,rank);			
			y = y + 21;	
			ranknum = ranknum + 1;			
        }		
    }
	free(llist2);	
	llist2 = NULL;
	MouseOn(MouseX, MouseY);	

}


/**************************************************************
Function:RankList_C
Description:��ʾ�ɾ����а�����
Calls:
	 1.MouseOn
	 2.MouseOff
Input:
Return:
Others:
***************************************************************/
void RankList_C(void)
{
    RankMan *llist3 = NULL;
	FILE *fp;
	int i,y=0;
	int count;
	char sco[5];
	char rank[5];
	int ranknum = 1;
	settextstyle(3,0,3);
	

	fp = fopen(USERNUM,"r+");
    if(fp == NULL)
    {
        printf("open file wrong");
    }

	fscanf(fp, "%3d", &count);	
	rewind(fp);
    fclose(fp);
	
	llist3 = (RankMan *)malloc(sizeof(RankMan)*count);
	
    fp = fopen(USERFILE_3,"rb+");
    if(fp == NULL)
    {
        printf("open file wrong");
    }          
    fread(llist3, sizeof(RankMan),count,fp);//���ļ����ṹ����
    rewind(fp);
	fclose(fp);	

	MouseOff();	
	setfillstyle(SOLID_FILL,LIGHTGREEN);		
	bar(90, 320, 170, 370);	
  	puthz(117,339,"�ɾ�",16,16,BLACK);	
	setcolor(WHITE);
	if(count < 10)
	{
        for(i = 0; i < count; i++)
		{
            			
			outtextxy(350,140+y,llist3[i].username);
			itoa(llist3[i].score[2],sco,10);
			outtextxy(470,140+y,sco);
			itoa(ranknum,rank,10);
			outtextxy(230,140+y,rank);			
			y = y + 21;
			ranknum = ranknum + 1;
        }
    }
	
    else if(count >= 10)
    {
        for(i = 0; i < 10; i++)
		{

			outtextxy(350,140+y,llist3[i].username);
			itoa(llist3[i].score[2],sco,10);
			outtextxy(470,140+y,sco);	
			itoa(ranknum,rank,10);
			outtextxy(230,140+y,rank);			
			y = y + 21;	
			ranknum = ranknum + 1;			
        }		
    }
	free(llist3);
	llist3 = NULL;
	MouseOn(MouseX, MouseY);	

}


/**************************************************************
Function:ChangeUser_A
Description:��֮ǰ�û�����ģʽ�÷ָ���
Calls:
Input:RankMan p,RankMan *list1, int count
Return:
Others:
***************************************************************/			
void ChangeUser_A(RankMan p,RankMan *list1, int count)
{
	RankMan temp;
	FILE *fp;
    int i,j;

	//��������û��ĵ÷ֱ���ԭ���÷ָ�,����½ṹ����
    for (i = 0;i < count; i++)
	{	
        if (strcmp(p.username,list1[i].username) == 0)
		{				
			if (p.score[0]>list1[i].score[0])
			{
                list1[i].score[0] = p.score[0];
				
            }
			
			if (p.score[1]>list1[i].score[1])
			{
                list1[i].score[1] = p.score[1];
				
            }	
			
			if (p.score[2]>list1[i].score[2])
			{
                list1[i].score[2] = p.score[2];
				
            }
			
		}
    }
	//���ṹ������������
	for (i = 0; i < (count-1); i++)
	{
        for (j = i+1; j<	count; j++)
        {
            if (list1[i].score[0] < list1[j].score[0])
			{
				
			strcpy(temp.username,list1[i].username);
			temp.score[0] = list1[i].score[0];
			temp.score[1] = list1[i].score[1];
			temp.score[2] = list1[i].score[2];
							
			strcpy(list1[i].username,list1[j].username);
			list1[i].score[0] = list1[j].score[0];
			list1[i].score[1] = list1[j].score[1];
			list1[i].score[2] = list1[j].score[2];							
							

			strcpy(list1[j].username,temp.username);
			list1[j].score[0] = temp.score[0];
			list1[j].score[1] = temp.score[1];
			list1[j].score[2] = temp.score[2];	
							

		    }
        }
    }

    //д���ļ�
	fp = fopen(USERFILE_1,"wb");			
	fwrite(list1, sizeof(RankMan),count,fp);
	rewind(fp);
	fclose(fp);
	
	// sta = remove(USERFILE_1);//ɾ��ָ���ļ�,�ɹ�����0
	// if (sta != 0)		
	// {
		// printf("remove file fail");
	// }	
	
    // ssta = rename(FUSERFILE_1,USERFILE_1);	//���ĺ�����,�ɹ�����0
    // if (ssta != 0)
    // {
		// printf("rename file fail");
	// }	
 
 
}   


/**************************************************************
Function:ChangeUser_B
Description:��֮ǰ�û��ֻ�ģʽ�÷ָ���
Calls:
Input:RankMan p,RankMan *list2, int count
Return:
Others:
***************************************************************/
void ChangeUser_B(RankMan p,RankMan *list2, int count)
{
	RankMan temp;	
	FILE *fp;	
	
    int i,j;

	
	//��������û��ĵ÷ֱ���ԭ���÷ָ�,����½ṹ����
    for (i = 0;i < count; i++)
	{	
        if (strcmp(p.username,list2[i].username) == 0)
		{				
			if (p.score[0]>list2[i].score[0])
			{
                list2[i].score[0] = p.score[0];
				
            }
			
			if (p.score[1]>list2[i].score[1])
			{
                list2[i].score[1] = p.score[1];
				
            }	
			
			if (p.score[2]>list2[i].score[2])
			{
                list2[i].score[2] = p.score[2];
				
            }
			
		}
    }
	//���ṹ������������
	for (i = 0; i < (count-1); i++)
	{
        for (j = i+1; j<	count; j++)
        {
            if (list2[i].score[1] < list2[j].score[1])
			{
				
			strcpy(temp.username,list2[i].username);
			temp.score[0] = list2[i].score[0];
			temp.score[1] = list2[i].score[1];
			temp.score[2] = list2[i].score[2];
							
			strcpy(list2[i].username,list2[j].username);
			list2[i].score[0] = list2[j].score[0];
			list2[i].score[1] = list2[j].score[1];
			list2[i].score[2] = list2[j].score[2];							
							

			strcpy(list2[j].username,temp.username);
			list2[j].score[0] = temp.score[0];
			list2[j].score[1] = temp.score[1];
			list2[j].score[2] = temp.score[2];	
							

		    }
        }
    }

    //д���ļ�
	fp = fopen(USERFILE_2,"wb");			
	fwrite(list2, sizeof(RankMan),count,fp);
	rewind(fp);
	fclose(fp);
	
	// sta = remove(USERFILE_2);//ɾ��ָ���ļ�,�ɹ�����0
	// if (sta != 0)		
	// {
		// printf("remove file fail");
	// }	
	
    // ssta = rename(FUSERFILE_2,USERFILE_2);	//���ĺ�����,�ɹ�����0
    // if (ssta != 0)
    // {
		// printf("rename file fail");
	// }	
 
 
}  


/**************************************************************
Function:ChangeUser_C
Description:��֮ǰ�û��ɾ����а�÷ָ���
Calls:
Input:RankMan p,RankMan *list3, int count
Return:
Others:
***************************************************************/
void ChangeUser_C(RankMan p,RankMan *list3, int count)
{
	RankMan temp;	
	FILE *fp;	
    int i,j;

	
	//��������û��ĵ÷ֱ���ԭ���÷ָ�,����½ṹ����
    for(i = 0;i < count; i++)
	{	
        if(strcmp(p.username,list3[i].username) == 0)
		{				
			if(p.score[0]>list3[i].score[0])
			{
                list3[i].score[0] = p.score[0];
				
            }
			
			if(p.score[1]>list3[i].score[1])
			{
                list3[i].score[1] = p.score[1];
				
            }	
			
			if(p.score[2]>list3[i].score[2])
			{
                list3[i].score[2] = p.score[2];
				
            }
			
		}
    }
	//���ṹ������������
	for(i = 0; i < (count-1); i++)
	{
        for(j = i+1; j<	count; j++)
        {
            if(list3[i].score[2] < list3[j].score[2])
			{
				
			strcpy(temp.username,list3[i].username);
			temp.score[0] = list3[i].score[0];
			temp.score[1] = list3[i].score[1];
			temp.score[2] = list3[i].score[2];
							
			strcpy(list3[i].username,list3[j].username);
			list3[i].score[0] = list3[j].score[0];
			list3[i].score[1] = list3[j].score[1];
			list3[i].score[2] = list3[j].score[2];							
							

			strcpy(list3[j].username,temp.username);
			list3[j].score[0] = temp.score[0];
			list3[j].score[1] = temp.score[1];
			list3[j].score[2] = temp.score[2];	
							

		    }
        }
    }

    //д���ļ�
	fp = fopen(USERFILE_3,"wb");			
	fwrite(list3, sizeof(RankMan),count,fp);
	rewind(fp);
	fclose(fp);
	  
} 	
        	
/**************************************************************
Function:Search_Name
Description:����֮ǰ���а����������û�
Calls:
Input:RankMan p, RankMan *list1,RankMan *list2, RankMan *list3, int count, int *sta_1, int *sta_2,int *sta_3
Return:sta
Others:
***************************************************************/			
int Search_Name(RankMan p, RankMan *list1,RankMan *list2, RankMan *list3, int count, int *sta_1, int *sta_2,int *sta_3)//�����,��������1
{
    int i;
	int sta = 0;
	for (i = 0; i < count; i++)
	{
        if (strcmp(p.username,list1[i].username) == 0)
		{
        	sta = 1;
            if (p.score[0]>list1[i].score[0])
            {
                *sta_1 = 1;
            }
        }
    }

    for (i = 0; i < count; i++)	
	{
        if (strcmp(p.username,list2[i].username) == 0)
		{
		    sta = 1;
            if (p.score[1]>list2[i].score[1])
            {

                *sta_2 = 1;
            }
        }
    } 


    for (i = 0; i < count; i++)	
	{
        if (strcmp(p.username,list3[i].username) == 0)
		{
        	sta = 1;
            if (p.score[2]>list3[i].score[2])
            {
				
                *sta_3 = 1;
            }
        }
    }	
	
	return sta;
}	

/**************************************************************
Function:FindRank
Description:�����û�����������κ͵÷�
Calls:MouseDelay
      puthz
Input:
Return:
Others:
***************************************************************/	
void FindRank(void)
{
    char *name = NULL;
	int sta;
	int i;
	int count;
	int wsta = 0;
	char sco[5];
	char rank[3];
    RankMan *list1 = NULL;
    RankMan *list2 = NULL;
    RankMan *list3 = NULL;	
    FILE *fp,*fffp;
	
	sta = 2;
	
	while (1)
	{
        MouseDelay(3);
        switch (sta)
        {
        case 1: {
 	        
	        fp = fopen(USERNUM,"r+");//�õ����а��ļ����û�����
            if(fp == NULL)
            {
                printf("open file wrong");
            }

	        fscanf(fp, "%3d", &count);	
	        rewind(fp);
            fclose(fp);
			
            list1 = (RankMan*)malloc((count) * sizeof(RankMan));
            list2 = (RankMan*)malloc((count) * sizeof(RankMan));	
            list3 = (RankMan*)malloc((count) * sizeof(RankMan));	

            //��һ���ļ���Ϣ���ṹ����			
			fffp = fopen(USERFILE_1,"rb+");
            if(fffp == NULL)
            {
                printf("open file wrong");
            }          
            fread(list1, sizeof(RankMan),count,fffp);//���ļ����ṹ����
		    rewind(fffp);
			fclose(fffp);
			
			//�ڶ����ļ���Ϣ���ṹ����
			fffp = fopen(USERFILE_2,"rb+");
            if(fffp == NULL)
            {
                printf("open file wrong");
            }           
            fread(list2, sizeof(RankMan),count,fffp);//���ļ����ṹ����
		    rewind(fffp);
			fclose(fffp);	

			//�������ļ���Ϣ���ṹ����
			fffp = fopen(USERFILE_3,"rb+");
            if(fffp == NULL)
            {
                printf("open file wrong");
            }           
            fread(list3, sizeof(RankMan),count,fffp);//���ļ����ṹ����
		    rewind(fffp);
			fclose(fffp);	

            MouseOff();
            for(i = 0; i < count; i++)
            {
                if (strcmp(name,list1[i].username) == 0)
				{
					
					puthz(170,290,"����",16,16,BLACK);
					setcolor(WHITE);
					puthz(420,250,"�÷�",16,16,BLACK);
                    itoa(list1[i].score[0],sco,10);
                    outtextxy(420,285,sco);	
					puthz(250,250,"����",16,16,BLACK);
					itoa((i+1),rank,10);
			        outtextxy(250,285,rank);
					break;
                }
				
									
            }
				

            for(i = 0; i < count; i++)
            {
                if (strcmp(name,list2[i].username) == 0)
				{
					
					puthz(170,320,"�ֻ�",16,16,BLACK);
					setcolor(WHITE);
					puthz(420,250,"�÷�",16,16,BLACK);
                    itoa(list2[i].score[1],sco,10);
                    outtextxy(420,315,sco);	
					puthz(250,250,"����",16,16,BLACK);
					itoa((i+1),rank,10);
			        outtextxy(250,315,rank);
					break;
                }
            }

            for(i = 0; i < count; i++)
            {
                if (strcmp(name,list3[i].username) == 0)
				{
					
					puthz(170,350,"�ɾ�",16,16,BLACK);
					setcolor(WHITE);
					puthz(420,250,"�÷�",16,16,BLACK);
                    itoa(list3[i].score[2],sco,10);
                    outtextxy(420,345,sco);	
					puthz(250,250,"����",16,16,BLACK);
					itoa((i+1),rank,10);
			        outtextxy(250,345,rank);
					break;
                }
            } 
			if(i == count)
			{
                puthz(250,300,"���޴��û�",32,32,BLACK);
			}
			
			MouseOn(MouseX,MouseY);
			
			free(list1);
			list1 = NULL;
			free(list2);
			list2 = NULL;
			free(list3);
			list3 = NULL;
			
            wsta = 1;
            break;
        }
		case 2: {
			name [0] = '\0';
			Write(name, &sta, 150,200);
			
			break;
			
		}
		default:break;
		}
	    if (wsta!=0)
		{
            break;
        }
    }		
	return;
}	
	
/**************************************************************
Function:DrawFind
Description:������������
Calls:puthz
Input:
Return:
Others:
***************************************************************/	
void DrawFind(void)
{ 
    
    int a[] = {455,105,465,120,455,135,460,135,
	           470,125,480,135,485,135,475,120,
	           485,105,480,105,470,115,460,105,455,105};
    setlinestyle(0,0,1);			   
    setfillstyle(SOLID_FILL,BROWN);
    bar(150,100,490,380);
	setfillstyle(SOLID_FILL,WHITE);
	bar(450,100,490,140);
	bar(450,205,485,225);
    setcolor(BLACK);
    rectangle(149,99,491,381);
	rectangle(449,204,486,226);
	setcolor(RED);
	drawpoly(13,a);
	setfillstyle(SOLID_FILL,RED);
	floodfill(470,120,RED);
	setfillstyle(SOLID_FILL,CYAN);
	floodfill(460,217,WHITE);
    puthz(280, 150, "��ѯ", 32, 32, BLACK);	
	puthz(452, 207, "ȷ��", 16, 16, BLACK);
    drawtextput(200, 200);	
	
}	


/**************************************************************
Function:Write
Description:�������빦�ܣ�ͬʱ��������ַ������ַ���
Calls:
	 1.VLine
	 2.MouseOff
	 3.MouseOn
	 4.Put_Asc16_Size
Input:char* str, int* sta, int xx, int yy
Return:
Others:xx yy ��ʾ�ַ��������ʼ����
       sta ����״̬
***************************************************************/	


void Write(char *str, int *sta, int xx, int yy)
{
    int i, mx, my, judgeN, nn = 0, nnn = 0;
	int m = 15;
    char zm;
    fflush(stdin);
    i = 0;
    while (kbhit())	
	{
        bioskey(0);
	}
    while (1)
    {
        MouseDelay(2);
        nn += 1;
        if (nn == 25)
        {
            nnn++;
            nnn = nnn % 2;

			MouseOff();
			VLine((xx + 17 * i + 82), yy + 5, yy + 28);
			MouseOn(MouseX, MouseY);
			
			nn = 0;
		}
        judgeN = 0;
		if (kbhit() != 0)
		{
			zm = getch();
			if ((zm >= 'a' && zm <= 'z') || (zm >= 'A' && zm <= 'Z') || (zm >= '0' && zm <= '9'))
            {
				if (i <= m)
				{
                    str[i] = zm;
					str[i + 1] = '\0';
					if (nnn == 1)
					{
						MouseOff();
						VLine((xx + 17 * i + 82), yy + 5, yy + 28);
						MouseOn(MouseX, MouseY);
						nnn = 0;					
					}
                    MouseOff();
					Put_Asc16_Size(xx + 80 + 17 * i, yy, 2, 2, zm, BLACK);
					MouseOn(MouseX, MouseY);  					
			        
			        i++;
				}
            }
			if (zm == Back)
			{
				if (i > 0)
				{
					i--; 

					MouseOff();//��ȥ���
					Put_Asc16_Size(xx + 80 + 17 * i, yy, 2, 2, str[i], CYAN);  
					setcolor(CYAN);
					line((xx + 17 * i + 99), yy + 5, (xx + 17 * i + 99), yy + 28);
					MouseOn(MouseX, MouseY);//�����		
					
					str[i] = '\0';
				}
            }
			
			if (zm == Enter)
			{
			    setcolor(CYAN);	
				line((150 + 17 * i + 82), 200 + 5, (150 + 17 * i + 82), 205 + 26);
				judgeN = 1;
				*sta = 1;
			}
		}	
		
        if (LeftPress())
		{
            MouseGetXY(&mx, &my);
			if (mx > 450 && my > 205 && mx < 485 && my < 225)	
            {
				setcolor(CYAN);	
				line((150 + 17 * i + 82), 200 + 5, (150 + 17 * i + 82), 205 + 26);
				*sta = 1;
                break;
				
			}
        }
		
        if (judgeN != 0)
        {
            break;
        }				
	}
}	

            			
            
	

	
	
	
	
	
	
	
	

	
	