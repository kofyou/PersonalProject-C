#include "WordCount.h"
#include <cmath>
#include <fstream>
#include <map>
#include <string>
#include <iostream>

void WordCount::charAndEntercount(string pathstr){
	const char*path=pathstr.data();
	
	int cc=0;
	int ec=0;	
	char temp;
	int isnewEnter=1;
	
	ifstream infs;
	infs.open(path,ifstream::in);
	
	if(!infs)
	{
		cout<<"Cannot open file";
	}
	else
	{
		//逐个获取字符 
		while(!infs.eof())
		{
			infs.get(temp);
			cc++;
			if(temp=='\n')
			{
				isnewEnter=1;
			}
			else
			{
				if((temp=='\f'||temp=='\r'||temp=='\t'||temp=='\v'||temp=='\b'||temp==' ')&&isnewEnter==1);
				else
				{
					ec+=isnewEnter;
					isnewEnter=0;
				}
			}
		}
		cc--;
		infs.close();
	}
	
	ccount=cc;
	ecount=ec;
}

void WordCount::wCount(string pathstr){
	int wcot=0;			 //有效单词个数 
		
	map<string,int> *wdmap;
	wdmap=&wordmap;		  //将wordmap的地址赋值给wdmap，这样修改wdmap时也会修改wordmap 
	
	string temp;		 //获取文件每行内容 
	bool isefct=true;    //判断是否为有效单词 
	string word="";		 //临时存放单词 
	int wordlength=0;	 //word长度判断 
	
	ifstream infs;
	infs.open(pathstr,ifstream::in);

	if(!infs);
	else
	{
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
					 
					//若为有效单词，则存入wdmap
					if( isefct && wordlength>=4 ) 
					{
						cout<<word<<'\n';
						wcot++;
						
						map<string,int>::iterator iter=(*wdmap).find(word);
 
						if( iter!=(*wdmap).end())
						{
							(*wdmap)[word]++;
							wcot--;
						}
						else
						{
							(*wdmap).insert(pair<string, int>(word, 1));
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
							word+=tolower(ch);
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
	}
		wcount=wcot;	
}

void wordMapSort(){
	
} 
