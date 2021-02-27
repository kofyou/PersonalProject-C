#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <map>
#include <algorithm>
 
using namespace std;


bool isnum_str(char str)  //判断是否是字符或数字
{
  if((str >= 'A' && str <= 'z') || (str >= '0' && str <= '9') )
	  return true;
  else
	  return false;
}
bool is_lower_alpha(char str){
	if(str >= 'a' && str <= 'z')
	  return true;
  else
	  return false;
}

void count(fstream &outfile, int *cnt )  //统计函数
{ char str[256];
  while(outfile.getline(str,256))
  { 
    int tmp = 0;
    
    for(int i = 0; i < strlen(str); i++)
	{
	  if(str[i] == ' ' || str[i] == '.' || str[i] == ',' || str[i] == '?' || str[i] == '!')
		  cnt[1]++;            //统计单词数
	  
	  if(isnum_str(str[i]))
	  { cnt[0]++;   tmp++;}    //统计字符数，tmp局部变量用来区分是不是一个空行。
	}
	
	if(tmp != 0)
	cnt[2]++;                 //统计行数
	tmp = 0;
  }
    
 return ;
}

int main()
{
	
    int cnt[3] = {0};
	ifstream input;
	input.open("text.txt");
	fstream f;
	f.open("text.txt");
	count(f,cnt);
	string eachline;
	map<string, int> mapA; //第一个存单词,第二个存单词出现的次数;
	
	while (getline(input, eachline))
	{
		transform(eachline.begin(),eachline.end(),eachline.begin(),::tolower);
		string::size_type start = 0;
		string::size_type end = eachline.find_first_of(" ");
		int flag=0; 
		while (end != string::npos) //npos就是这一行到头啦；
		{
			string content = eachline.substr(start, end - start);
			map<string, int>::iterator it = mapA.find(content);
			if(content.length()>3&&is_lower_alpha(content[0])&&is_lower_alpha(content[1])
			&&is_lower_alpha(content[2])&&is_lower_alpha(content[3]))
			{				
				if (it == mapA.end())
				{
					mapA.insert(pair<string, int>(content, 1));//赋值的时候只接受pair类型；
				} else
				{
					++it->second;
				}
			}			
			start = end + 1;
			end = eachline.find_first_of(" ", start);			
		}
		string content = eachline.substr(start, end - start);
			map<string, int>::iterator it = mapA.find(content);
			if(content.length()>3&&is_lower_alpha(content[0])&&is_lower_alpha(content[1])
			&&is_lower_alpha(content[2])&&is_lower_alpha(content[3]))
			{				
				if (it == mapA.end())
				{
					mapA.insert(pair<string, int>(content, 1));//赋值的时候只接受pair类型；
				} else
				{
					++it->second;
				}
			}							
	}
	multimap<int, string, greater<int> > mapB;
 	int word_count=0;
	for (map<string, int>::iterator it1 = mapA.begin(); it1 != mapA.end();++it1)
	{
		mapB.insert(pair<int, string>(it1->second, it1->first));//方便map自动根据出现次数排序 
		word_count++;
	}
	
	cout<<"字符数为："<< cnt[0]<<endl;
	cout<<"单词总数" <<cnt[1]<<endl; 
	cout<<"单词种类数为："<<word_count<<endl;
	cout<<"行数为："<< cnt[2]<<endl;

	for (map<int, string>::iterator it2 = mapB.begin(); it2 != mapB.end();++it2)
	{
//		if ((it2->first) > 1)
			cout << it2->second << "单词出现的次数是" << it2->first << endl;
		
	}
	
 
}

