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

//统计文件中各单词出现的次数
void top10(FILE *fp,FILE *fp1,char *argv); 

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
	rewind(fp);
	
	//统计文件中各单词出现的次数
	top10(fp,fp1,argv[2]); 
	
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

//统计文件中各单词出现的次数
void top10(FILE *fp,FILE *fp1,char *argv){	
	//按频次排序 
	map<int,string>mapSorted;
	//按字典序排序 
	map<string,int>mapCmp;
	
	char ch; 
	//单词总数、字母总数、数字总数、单词内字符数 
	int cntWord,cntAlpha,cntNum,cntChar; 
	cntWord=cntAlpha=cntNum=cntChar=0;
	
	int increase=0;
	
	while((ch=fgetc(fp))!=EOF){ 
		//是字母或数字 
		if(isalnum(ch)){
			if(isdigit(ch)){
				cntNum++;
				//出现数字，则将cntAlpha清零 
				cntAlpha=0;
			}
			else if(isalpha(ch)){
				cntAlpha++;
				if(isWord(cntAlpha,cntNum,increase)){
					cntWord++;
					increase=1; 
					cntChar=3;
				}
			}
			if(increase){
				cntChar++;
			} 
		}
		
		else if(ch!=10){
			//单词结尾第一个分隔符 
			if(increase){
				FILE *fp1=fp;
				for(int i=0;i<cntChar;i++){
					fseek(fp1,-1L,SEEK_CUR);
				}
				fseek(fp1,-1L,SEEK_CUR);
				char wordStr[cntChar+1],chWord;
				wordStr[cntChar]='\0';
				for(int i=0;i<cntChar;i++){
					chWord=fgetc(fp1);
					chWord=tolower(chWord);
					wordStr[i]=chWord;
				}
				string str=wordStr;
				map<string,int>::iterator l_it;
				l_it=mapCmp.find(str);
				if(l_it==mapCmp.end()){
					mapCmp[str]=1;
				}
				else{
					mapCmp[str]++;
				}
			}
			cntNum=cntAlpha=increase=cntChar=0;
		}

		else if(ch==10){

			if(increase){
				FILE *fp1=fp;
				for(int i=0;i<cntChar;i++){
					fseek(fp1,-1L,SEEK_CUR);
				}
				fseek(fp1,-2L,SEEK_CUR);
				char wordStr[cntChar+1],chWord;
				wordStr[cntChar]='\0';
				for(int i=0;i<cntChar;i++){
					chWord=fgetc(fp1);
					chWord=tolower(chWord);
					wordStr[i]=chWord;
				}
				string str=wordStr;
				map<string,int>::iterator l_it;
				l_it=mapCmp.find(str);
				if(l_it==mapCmp.end()){
					mapCmp[str]=1;
				}
				else{
					mapCmp[str]++;
				}
			}
			cntNum=cntAlpha=increase=cntChar=0;
		}
	}
	
	{
		if(increase){
			FILE *fp1=fp;
			for(int i=0;i<cntChar;i++){
				fseek(fp1,-1L,SEEK_CUR);
			}
			char wordStr[cntChar+1],chWord;
			wordStr[cntChar]='\0';
			for(int i=0;i<cntChar;i++){
				chWord=fgetc(fp1);
				chWord=tolower(chWord);
				wordStr[i]=chWord;
			}
			string str=wordStr;
			map<string,int>::iterator l_it;
			l_it=mapCmp.find(str);
			if(l_it==mapCmp.end()){
				mapCmp[str]=1;
			}
			else{
				mapCmp[str]++;
			}
		}
		cntNum=cntAlpha=increase=cntChar=0;
	} 
	 
	//将mapCmp中的数据存入mapSorted 
	map<string,int>::iterator l_it;
	l_it=mapCmp.begin();
	map<int,string>::iterator m_it;
	for(int i=0;i<mapCmp.size();i++){
		m_it=mapSorted.find(l_it->second);
		if(m_it==mapSorted.end()){
			mapSorted[l_it->second]=l_it->first;
		}
		else{
			if(l_it->first.compare(mapSorted[l_it->second])<0){
				mapSorted[l_it->second]=l_it->first;
			}
		}
		l_it++;
	}
	m_it=mapSorted.begin();
	for(int i=0;i<10;i++){
		//统计文件中各单词出现的次数 
		ofstream output(argv, ios::app);
		output<<m_it->second.c_str()<<':'<<m_it->first<<std::endl;
		std::cout<<m_it->second.c_str()<<':'<<m_it->first<<std::endl;
		if(m_it!=mapSorted.end())
		m_it++;
	}
}
