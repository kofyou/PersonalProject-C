#ifndef  __WORDCOUNT_H
#define  __WORDCOUNT_H

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <ctype.h>
#include <map> 
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

bool cmp(const pair<string, int>& a, const pair<string, int>& b);
class WordCount;

class WordCount
{
	private:
		int w_char;    //characters' count
		int w_word;    //words' count
		int w_line;    //enter count
		map<string,int> wordmap;
		
	public:
		WordCount(){
			w_char=0;
			w_word=0;
			w_line=0;
		}
		
		//function
		void charAndEntercount(string pathstr);    //count characters
		void wCount(string pathstr);				//count words and enter						
		void writeTxt(string outstr);

};

bool cmp(const pair<string, int>& a, const pair<string, int>& b)
{
        return a.second > b.second;
}

void WordCount::charAndEntercount(string pathstr)
{
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
		//get char one by one
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
	
	w_char=cc;
	w_line=ec;	
	if(cc==0) w_line=0;
}

void WordCount::wCount(string pathstr)
{
	int wcot=0;			 //the count of effective words
		
	map<string,int> *wdmap;
	wdmap=&wordmap;		  //give wordmap's address to wdmap,so wordmap would change while change wdmap 
	
	string temp;		 //get everyline in the file 
	bool isefct=true;    //check if the word is effective
	string word="";		 //store the word for a short time
	int wordlength=0;	 //word'd length
	
	const char *path=pathstr.data();
	ifstream infs;
	infs.open(path,ifstream::in);

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
				
				//when meet separation character or be the last of the line
				if(ch==' '||!isalnum(ch)||i==l-1)    
				{
					//discussion for the last char
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
					 
					//if the word is effective,store it into wdmap
					if( isefct && wordlength>=4 ) 
					{
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
							isefct=false; 	//if digit show in the first 4 char,the word is not effective
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
		w_word=wcot;	
}

//output wordcount
void WordCount::writeTxt(string outstr)
{
	const char *outpath=outstr.data();
	ofstream out(outpath); 
	
	vector<pair<string, int> > vec(wordmap.begin(),wordmap.end());
    sort(vec.begin(),vec.end(),cmp);
    
	vector<pair<string,int> >::iterator it=vec.begin();

	if(!out)
    {
		cout<<"Cannot open file.\n";
		return;
	} 
	out<<"characters: "<<w_char<<'\n';
	out<<"words: "<<w_word<<'\n';
	out<<"lines: "<<w_line<<'\n';
	if(w_word<10)
	{
		for(it;it!= vec.end();it++)
		{
        	out<<it->first << ": " << it->second <<endl;
    	}
	}
	else
	{
		for(int i=0;i<10;i++){
			out<< it->first << ": " << it->second <<endl;
        	it++;
		}
	}
  	out.close(); 
}


#endif
