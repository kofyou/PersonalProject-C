#include "WordCount.h"

int main(int argc, char *argv[]){
	string pathstr,outstr;
	cin>>pathstr>>outstr;
  	
  	WordCount wordcot;
  	wordcot.charAndEntercount(pathstr);
  	wordcot.wCount(pathstr);
  	
  	wordcot.writeTxt(outstr);

	return 0;
}
