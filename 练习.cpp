#include<iostream>
#include<string.h>
#include<io.h>
#include<windows.h>
using namespace std;
int is_begin(char* buf)
{
	if(strlen(buf)==0) return 0;
	for(int i=0;i<strlen(buf);i++)
		if(buf[i]=='.'&&i!=0&&isdigit(buf[i-1])) return 1;
	return 0;
}
int main()
{
	system("color f0");
	printf("欢迎使用史纲复习软件！\n使用方法：输入答案后按回车。\n如果停止答题，按q退出或直接关闭程序。\n");
	printf("所有错题将被收集在文件目录下的incorrect.txt文件中。\n");
	system("pause");
	system("cls");
	int is_num=0,is_dot=0;
	FILE* problems=fopen("question.txt","r");
	FILE* answers=fopen("answer.txt","r");
	FILE *notebook,*progress;
	if(_access("incorrect.txt",0)==-1) notebook=fopen("incorrect.txt","w");
	else notebook=fopen("incorrect.txt","a");
	fclose(notebook); 
	int index,i;
	char question[10000];
	char buf[10000],answer[10000];
	if(_access("progress.dat",0)==-1) index=1;
	else
	{
		progress=fopen("progress.dat","r");
		fscanf(progress,"%d",&index);
		if(index<1||index>573) index=1;
		fclose(progress);
	}
	while(1)
	{
		notebook=fopen("incorrect.txt","a");
		progress=fopen("progress.dat","w");
		fprintf(progress,"%d\n",index);
		fclose(progress); 
		i=0;
		while(i!=index)
		{
			fscanf(problems,"%s",buf);
			if(strlen(buf)!=0&&isdigit(buf[0])) i++;
		}
		strcpy(question,buf);
		strcat(question,"\n");
		while(1)
		{
			int ret=fscanf(problems,"%s",buf);
			if (ret == -1) break;
			if(strlen(buf)!=0&&isdigit(buf[0])) break;
			strcat(question,buf);
			strcat(question,"\n");
		}
		printf("%s",question);
		i=0;
		while(i!=index)
		{
			fscanf(answers,"%s",buf);
			if(strlen(buf)!=0&&is_begin(buf)) i++;
		}
		strcpy(answer,buf);
		while(1)
		{
			int ret=fscanf(answers,"%s",buf);
			if(ret==-1) break;
			if(strlen(buf)!=0&&is_begin(buf)) break;
			strcat(answer,buf); 
		}
		char* tmp=answer;
		while(isdigit(*tmp)) tmp++;
		if(*tmp=='.')
		{
			tmp++;
			strcpy(answer,tmp);
		}
		char mine[500];
		scanf("%s",mine);
		for(char* j=mine;j!=mine+strlen(mine);j++)
			if(*j>='a'&&*j<='z') *j=*j-'a'+'A';
		if(strcmp(mine,"q")==0||strcmp(mine,"Q")==0)
		{
			fclose(problems);
			fclose(answers);
			fclose(notebook);
			return 0;
		}
		if(strcmp(mine,answer)==0)
		{
			printf("Correct!\n");
			collect:;
			printf("收入错题集？(y/n)");
			cin>>buf[0];
			if(buf[0]=='y'||buf[0]=='Y') fprintf(notebook,"%s%s\n",question,answer);
			else if(buf[0]=='n'||buf[0]=='N') ;
			else goto collect;
		}
		else
		{
			printf("The right answer is %s.\n",answer);
			fprintf(notebook,"%s答案：%s\n",question,answer);
			system("pause");
		}
		fclose(notebook);
		index++;
		if(index==574)
		{
			printf("恭喜你完成所有题目！\n");
			Sleep(5000);
			system("pause"); 
			return 0;
		}
		rewind(problems);
		rewind(answers);
		system("cls"); 
	}
	return 0;
} 
