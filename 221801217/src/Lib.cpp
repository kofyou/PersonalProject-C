#include "lib.h"


int countLine(string input){
	int lines=0;
	if(input.length()!=0)
		lines=1;
	for(int i=0;i<input.length();i++){
		if((input[i]==13||input[i]==10)){
			lines++;
		}
	}
	return lines;
}



int countChar(string input){
	return input.length();
}



int countWord(string input);



void output(ofstream& out,string input){
//	out<<"aaaa";
	cout<<"Lines:"<<countLine(input)<<endl;
//	cout<<"Characters:"<<countChar(input)<<endl;
//	cout<<"Words:"<<countWord(input)<<endl;
}



