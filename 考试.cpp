#include<iostream>
#include<string.h>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<set>
#include<windows.h>
#include<sstream>
using namespace std;
template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}
int is_begin(char* buf)
{
	if(strlen(buf)==0) return 0;
	for(int i=0;i<strlen(buf);i++)
		if(buf[i]=='.'&&i!=0&&isdigit(buf[i-1])) return 1;
	return 0;
}
bool valid(char* answer,int progress)
{
	if(progress<=25)
	{
		if(strlen(answer)==1) return true;
		else return false;
	}
	else if(progress<=45)
	{
		if(answer[0]>='A'&&answer[0]<='D'&&strlen(answer)>1&&strlen(answer)<=4) return true;
		else return false;
	}
	else
	{
		if(strcmp(answer,"正确")==0||strcmp(answer,"错误")==0) return true;
		else return false;
	}
}
int main()
{
	system("color f0");
	printf("欢迎使用史纲机考模拟软件！\n使用方法：输入答案后按回车。\n");
	printf("所有错题将被收集在文件目录下的feedback.txt文件中。\n");
	system("pause");
	system("cls");
	int is_num=0,is_dot=0,score=0;
	set<int> chosen;
	FILE* problems=fopen("question.txt","r");
	FILE* answers=fopen("answer.txt","r");
	FILE *notebook;
	notebook=fopen("feedback.txt","w");
	fclose(notebook); 
	int index,i,progress=1;
	char question[10000];
	char buf[10000],answer[10000];
	srand((unsigned)time(NULL));
	while(1)
	{
		index=rand()%573+1;
		if(chosen.count(index)!=0) continue;
		chosen.insert(index);
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
		char* tmp=question,tmp2[1000];
		while(isdigit(*tmp)) tmp++;
		if(*tmp=='.')
		{
			tmp++;
			string pre=to_string(progress)+".";
			strcpy(tmp2,tmp);
			strcpy(question,pre.c_str());
			strcat(question,tmp2);
		}
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
		tmp=answer;
		while(isdigit(*tmp)) tmp++;
		if(*tmp=='.')
		{
			tmp++;
			strcpy(answer,tmp);
		}
		if(!valid(answer,progress))
		{
			rewind(problems);
			rewind(answers);
			continue;
		}
		printf("%s",question);
		char mine[500];
		scanf("%s",mine);
		for(char* j=mine;j!=mine+strlen(mine);j++)
			if(*j>='a'&&*j<='z') *j=*j-'a'+'A';
		if(strcmp(mine,answer)!=0)
		{
			notebook=fopen("feedback.txt","a");
			fprintf(notebook,"%s我的答案：%s\n标准答案：%s\n",question,mine,answer);
			fclose(notebook);
		}
		else
		{
			if(progress<=45) score+=2;
			else score+=1;
		}
		progress++;
		if(progress==56)
		{
			system("cls");
			printf("题目完成！\n总分：%d\n",score);
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
