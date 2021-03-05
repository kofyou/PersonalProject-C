#include<iostream>
#include<fstream>
#include<algorithm> 
#include<vector>
#include<string>
using namespace std;

typedef struct 
{
	string word;
	int num;
}words;

vector<words> v;

ofstream result("out.txt");

class Wordcount 
{
	private:
		int character;
		int word;
		int line;
		string filename;
	public:
		Wordcount();
		Wordcount(string s);
		void get_line();
		void get_character();
		void get_word();
		void get_mostword();//单词计算
		void get_all();
		int get_characters() 
		{ 
			get_character(); 
			return character; 
		}
		int get_words() 
		{ 
			get_word(); 
			return word; 
		}
		int get_lines() 
		{ 
			get_line(); 
			return line; 
		}
};


bool Dic_word(const string& a, const string& b);//字典排序
bool Set_word(const words& a, const words& b);// 单词排序
bool isAscil(char temp);//判断分割符 
bool isWhite(char temp);//判断空白字符 
bool isDigit(char temp);//判断是否为数字
bool isWord(char temp);//单词检测 

