#ifndef  __WORDCOUNT_H
#define  __WORDCOUNT_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class WordCount;


class WordCount
{
	private:
		int ccount;    //字符数
		int wcount;    //单词数
		int ecount;    //行数
		map<string,int> wordmap;
		
	public:
		WordCount();
		
		//成员函数 
		void charAndEntercount(string pathstr);    //统计字符数的同时统计行数 
		void wCount(string pathstr);				//统计单词数，并放入wordmap 
		void wordMapSort();							//对wordmap进行排序，只保留词频最高的10项，若不满10项就全部保留 
};

#endif
