#include <iostream>
#include <fstream>

using namespace std;

const int MAX_LEN_STR = 100;	// 单词字符串的最大长度 

typedef struct word_info{		// 结构体：单词记录 
	char word[MAX_LEN_STR+1];	// 单词 
	int  n_word_repeat;			// 单词重复的次数 
}WInfo;

typedef struct words_record{	// 结构体：单词记录 
	WInfo words[501];			// 所有单词 
	int n_word_count;			// 单词的数量 
}WRec;

void summarize(const char* in_file, const char* out_file);	  // 对输入文件in_file进行统计，输出到out_file

int main(int argc, const char* argv[]) {
	
	if(argc != 3){		// 参数个数必须为3 
		
		printf("Usage: %s [input_file] [output_file]\n", argv[0]);
		return 1;
	}
	
	summarize(argv[1], argv[2]);
	
	return 0;
}

bool is_digit(char ch) {
	
	return (ch >= '0' && ch <= '9');
}

bool is_alpha(char ch) {
	
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ;
}

void summarize(const char* in_file, const char* out_file) {
	
	ifstream input;			// 输入文件 
	ofstream output;		// 输出文件 
	int      n_line = 0;	// 非空行数 
	int   	 n_word = 0;	// 单词数 
	int   	 n_char = 0;	// 字符数 
	WRec 	 records;		// 所有单词记录 
	char 	 buf[1024];		// 缓冲区 
	char 	 word_buf[MAX_LEN_STR+1];	// 单词缓冲区 
	int  	 word_len = 0;	// 单词长度 
	bool 	 line_empty;	// 行是否为空 
	
	int cur_line = 0; 
	
	input.open(in_file,ios::binary);
	if(!input.is_open() || input.bad()){
		
		printf("文件%s打开失败\n", in_file);
		return;
	}
	
	records.n_word_count = 0;	// 初始单词数为0 
						
	while(!input.eof()) {		// 读取到文件尾 
		
		input.getline(buf, 1024);	// 读取整行 
		if(!input.eof())
			n_char ++;
		line_empty = true;
		
		for(char* p = buf; *p != '\0'; p ++) {	// 遍历整行中的每个字符 
			
			n_char ++;
			if(*p != ' ' && *p != '\t') {		// 有其他字符时，该行非空 
				
				line_empty = false;
			}
		}
	}
		
	input.close();

	// 输出到指定输出文件 
	output.open(out_file);
	if(!output.is_open() || output.bad()){
		
		printf("文件%s打开失败\n", out_file);
		return;
	}
	sprintf(buf, "characters: %d\nwords: %d\nlines: %d\n", n_char, n_word, n_line);
	output << buf;
	for(int i = 0; i < 10; i ++) {
		
		sprintf(buf, "%s: %d\n", records.words[i].word, records.words[i].n_word_repeat);
		output << buf;
	}
	output.close();
}
