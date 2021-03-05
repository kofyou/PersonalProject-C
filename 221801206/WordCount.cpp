#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <ctype.h>
#include <map> 
#include <algorithm>
#include <functional>
#include "WordCount.h"

using namespace std;

int main(int argc, char *argv[]){
	string pathStr;
	cin>>pathStr;

	const char*path=pathStr.data();
	
	map<string,int> *wordmap;
	map<string,int> map2;
	wordmap=&map2;
	int wcot=0;			 //有效单词个数 
		
	string temp;		 //获取文件每行内容 
	bool isefct=true;    //判断是否为有效单词 
	string word="";		 //临时存放单词 
	int wordlength=0;	 //word长度判断 
	
	ifstream infs;
	infs.open(path,ifstream::in);

	if(!infs)
	{
		cout<<"Cannot open file.\n";
		return 0;
	}
	else
	{
		cout<<"open"<<'\n';
		while(getline(infs,temp))
		{
			int l=temp.length();
			for(int i=0;i<l;i++)
			{
				char ch=temp[i];
				ch=tolower(ch);
				//遇到分隔符或到达该行末尾 
				if(ch==' '||!isalnum(ch)||i==l-1)    
				{
					//行末字符的判断 
					if(i==l-1&&isalnum(ch))		
					{
						if( isdigit(ch)!=0 && wordlength<4 )
						{
							isefct=false;
						}
						else
						{
							word+=ch;
							wordlength++;
						}
					}
					 
					//若为有效单词，则存入map
					if( isefct && wordlength>=4 ) 
					{
						wcot++;
						
						map<string,int>::iterator iter=(*wordmap).find(word);
 
						if( iter!=(*wordmap).end())
						{
							(*wordmap)[word]++;
							wcot--;
						}
						else
						{
							(*wordmap).insert(pair<string, int>(word, 1));
						}

					}
					
					wordlength=0;
					word="";
					isefct=true;
				}
				else
				{
					if(isefct)
					{
						if( isdigit(ch)!=0 && wordlength<4 )		
						{
							isefct=false; 	//在单词前4位中出现数字，为无效单词
							wordlength=0;
							word="";
						}
						else
						{
							word+=ch;
							wordlength++;
						}
					}
				}
			}
			
			wordlength=0;
			word="";
			isefct=true;
		}
		infs.close();
		cout<<wcot<<'\n';	

	}

	return 0;
}
