#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#define MAXWORD 500
#define MAXWORDS 100000

int GetCharacters(char* str);
int GetWords(char* str);
int GetLines(char* str);
void GetNumbers(char* str,string outfile);