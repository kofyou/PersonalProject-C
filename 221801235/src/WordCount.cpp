#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <map>
#include <string>
#include <vector> 
#include <iostream>
#include <fstream>

using std::map;
using std::string;
using std::ofstream;
using std::ios;

//统计文件的字符数 
int countChar(FILE *fp,char *argv);

//判断是否为ASCII字符
int isascii(char ch);

//统计文件的单词总数 
int countWord(FILE *fp,char *argv);

//判断是否为单词
int isWord(int cntAlpha,int cntNum,int increase);

//统计文件的有效行数
int countRow(FILE *fp,char *argv);

int main(int argc,char *argv[]) {
	FILE *fp,*fp1;
	if((fp=fopen(argv[1],"rt"))==NULL){
		printf("Cannot open file[%s]!\n",argv[1]);
		exit(1);
	}
	fp1=fopen(argv[2],"wt");
	
	//统计文件的字符数
	countChar(fp,argv[2]);
	rewind(fp);
	
	//统计文件的单词总数 
	countWord(fp,argv[2]);
	rewind(fp);
	
	//统计文件的有效行数 
	countRow(fp,argv[2]); 
	
	fclose(fp);
	fclose(fp1);
	return 0;
}

//统计文件的字符数
int countChar(FILE *fp,char *argv){
	int others=0;
	char ch; 
	int cntChar=0; 
	while((ch=fgetc(fp))!=EOF){ 
		if(isascii(ch))
		cntChar++;
		else {
			others++;
		}
	}
	if(others>0){
		printf("非ASCII字符已忽略\n");
	}
	//统计文件的字符数
	ofstream output(argv, ios::app);
	output<<"字符个数为"<<cntChar<<std::endl;
//	printf("字符个数为%d\n",cntChar);
	return cntChar;
}

//判断是否为ASCII字符
int isascii(char ch){
	return(ch>=0 && ch<=127);
} 

//统计文件的单词总数
int countWord(FILE *fp,char *argv){
	char ch; 
	//单词总数、字母总数、数字总数 
	int cntWord,cntAlpha,cntNum; 
	cntWord=cntAlpha=cntNum=0;
	
	//标志cntWord是否已经加一 
	int increase=0;
	
	while((ch=fgetc(fp))!=EOF){ 
		if(isalnum(ch)){
			if(isdigit(ch)){
				cntNum++;
				//出现数字，则将cntAlpha清零 
				cntAlpha=0;
			}
			else if(isalpha(ch)){
				cntAlpha++;
				if(isWord(cntAlpha,cntNum,increase)) {
					cntWord++;
					increase=1; 
				}
			}
		}
		//遇到非字母数字的字符，将cntNum,cntAlpha清零 
		else{
			cntNum=cntAlpha=increase=0;
		}
	}
	//统计文件的单词总数 
	ofstream output(argv, ios::app);
	output<<"单词总数为"<<cntWord<<std::endl;
//	printf("单词总数为%d\n",cntWord);
	return cntWord;
}

//判断是否为单词
int isWord(int cntAlpha,int cntNum,int increase){
	//字母连续出现4次,前面没有数字且此单词尚未计入总数 
	return(cntAlpha>=4 && cntNum==0 && increase==0);
}

//统计文件的有效行数
//任何包含非空白字符的行，都需要统计
int countRow(FILE *fp,char *argv){
	int row=0;
	char ch; 
	int cntChar=0; 
	while((ch=fgetc(fp))!=EOF){ 
		if(!isspace(ch)) {
			cntChar++;
		}
		if(ch=='\n' && cntChar!=0){
			row++;
			cntChar=0;
		}
	}
	if(cntChar!=0){
		row++;
		cntChar=0;
	}
	//统计文件的有效行数
	ofstream output(argv, ios::app);
	output<<"有效行数为"<<row<<std::endl;
//	printf("有效行数为%d\n",row);
	return row;
}
