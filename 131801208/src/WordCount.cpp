#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <map>
#include <algorithm>
 
using namespace std;
int word_count=0;
multimap<int, string, greater<int> > mapB;
map<string, int> mapA; //第一个存单词,第二个存单词出现的次数;


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

void count(ifstream &outfile, int *cnt )  //统计函数
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
int fcharCount(fstream &infile){
	int a=0;
	infile >> skipws;
	while(!infile.eof())
	{
		char ch;
		infile.get( ch ); 
		a++;
	}
	a-=1;
	return a;
}
void countWord(ifstream &input){
	string eachline;
		
	while (getline(input, eachline))
	{
		transform(eachline.begin(),eachline.end(),eachline.begin(),::tolower);
		string::size_type start = 0;
		string::size_type end = eachline.find_first_of(".,?! ");
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
			end = eachline.find_first_of(".,?! ", start);			
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
 	word_count=0;
	for (map<string, int>::iterator it1 = mapA.begin(); it1 != mapA.end();++it1)
	{
		mapB.insert(pair<int, string>(it1->second, it1->first));//方便map自动根据出现次数排序 
		word_count+=it1->second;//顺手统计 
	}
}
void output(ofstream &foutput,int a,int *cnt){
	foutput<<"字符数为："<< a<<endl; 
	foutput<<"单词数为："<<word_count<<endl;
	foutput<<"行数为："<< cnt[2]<<endl;
	int temp=0;
	for (map<int, string>::iterator it2 = mapB.begin(); it2 != mapB.end()&&temp<10;++it2)
	{
//		if ((it2->first) > 1)
			temp++;
			foutput << it2->second << "单词出现的次数是" << it2->first << endl;
		
	}
}
int main()
//int main(int argc,char* argv[])
{
	
    int cnt[3] = {0};
	ifstream fword,fchar;//两种功能两个变量 
	ofstream foutput;
	foutput.open("output.txt");
	fchar.open("input.txt");
	fword.open("input.txt");
	
	//foutput.open(argv[2]);
	//fchar.open(argv[1]);
	//fword.open(argv[1]);
	countWord(fword);
	count(fchar,cnt);
	
	//fstream infile(argv[1],ios::in);
	fstream infile("input.txt",ios::in)	;
	int a=fcharCount(infile);
	
	output(foutput,a,cnt);		
	cout<<"字符数为："<< a<<endl; 
	cout<<"单词数为："<<word_count<<endl;
	cout<<"行数为："<< cnt[2]<<endl;

	for (map<int, string>::iterator it2 = mapB.begin(); it2 != mapB.end();++it2)
	{
//		if ((it2->first) > 1)
			cout << it2->second << "单词出现的次数是" << it2->first << endl;
		
	}
	
 	foutput.close();
 	fword.close();
 	fchar.close();
}

