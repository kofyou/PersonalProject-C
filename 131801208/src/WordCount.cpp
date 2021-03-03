#include <string>
#include <fstream>
#include <string.h>
#include <map>
#include <algorithm>
#include <iostream>
#include<ctime> 
 
using namespace std;
int word_count=0;//用于统计单词书 
multimap<int, string, greater<int> > mapB;//基于map特性再用一个map使其根据频率排序 
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
{ 
	char str[256];
	//int wrong=0;
	while(outfile.getline(str,256))
	{ 
		/*wrong++;
		if(wrong>256){
			cout<<"wrong line num";
			break;
		}*/
    	int tmp = 0;
    	for(int i = 0; i < strlen(str); i++)
		{
	  		if(str[i] == ' ' || str[i] == '.' || str[i] == ',' || str[i] == '?' || str[i] == '!'){
	  				cnt[1]++;	 //统计单词数	
			  }
	  
	  		if(isnum_str(str[i]))
	  		{ 
				cnt[0]++;
			    tmp++;     //统计字符数，tmp局部变量用来区分是不是一个空行。
			}    
		}
	
		if(tmp != 0){
			cnt[2]++;	//统计行数
		}                
		tmp = 0;
  }    
	return ;
}

int fcharCount(fstream &infile){	//统计字符数 
	int a=0;//用于统计 字符数 
	infile >> skipws;
	while(!infile.eof())
	{
		char ch;
		infile.get( ch ); 
		a++;
	}
	a-=1;//因为会多读入一个 \0结尾 不在本次要求当中 
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
			&&is_lower_alpha(content[2])&&is_lower_alpha(content[3]))//判断是否前四个都是字符 
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
	if((word_count>0||a>0)&&cnt[2]==0){
		foutput<<"单行内弱太多，抛出异常";
		return; 
	}
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

void test(ofstream &t){//测试函数 
	for(int a=0;a<10000000;a++){
    	t<<"ddaa ";
    	if(a%50==0&&a!=0){//每行字符数 
    		t<<"\n";
		}
	}
}

int main()
//int main(int argc,char* argv[])
{
	
    int cnt[3] = {0};
    
    ofstream t;
    t.open("input.txt");
    test(t);	
	t.close();
    clock_t start1,end1,start2,end2,start3,end3,start,end;
    
    start=clock();
	ifstream fword,fchar;//两种功能两个变量 
	ofstream foutput;
	
	foutput.open("output.txt");
	
	start1=clock();
	fchar.open("input.txt");
	count(fchar,cnt);
	fchar.close();
	end1=clock();
	
	start2=clock();
	fword.open("input.txt");
	countWord(fword);
	fword.close();
	end2=clock();
	//foutput.open(argv[2]);
	//fchar.open(argv[1]);
	//fword.open(argv[1]);
	
	//fstream infile(argv[1],ios::in);
	start3=clock();
	fstream infile("input.txt",ios::in)	;	
	int fchar_count=fcharCount(infile);
	end3=clock();
	
	output(foutput,fchar_count,cnt);
	end=clock();
	cout<<"总耗时"<<(double)((end-start)/1000)<<"s"<<endl;
	cout<<"统计字符耗时"<<(double)((end1-start1)/1000)<<"s"<<endl;
	cout<<"统计单词时"<<(double)((end2-start2)/1000)<<"s"<<endl;
	cout<<"统计行数耗时"<<(double)((end3-start3)/1000)<<"s"<<endl;
	
			
	cout<<"字符数为："<< fchar_count<<endl; 
	cout<<"单词数为："<<word_count<<endl;
	cout<<"行数为："<< cnt[2]<<endl;
	

	for (map<int, string>::iterator it2 = mapB.begin(); it2 != mapB.end();++it2)
	{
//		if ((it2->first) > 1)
			cout << it2->second << "单词出现的次数是" << it2->first << endl;
		
	}
	
 	foutput.close();
 	fword.close();
 	
 	
 	
	int a;
	cin >> a;
 	 
}

