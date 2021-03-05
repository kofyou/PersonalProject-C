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
		void get_mostword();
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

bool isAscil(char temp);//ÅÐ¶Ï·Ö¸î·û 
bool isWhite(char temp);//ÅÐ¶Ï¿Õ°××Ö·û 
bool isDigit(char temp);//ÅÐ¶ÏÊÇ·ñÎªÊý×Ö
bool isWord(char temp);//µ¥´Ê¼ì²â 
