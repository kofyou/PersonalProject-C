#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

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

bool is_digit(char ch);         // 判断ch是否是一个数字字符 
bool is_alpha(char ch);			// 判断ch是否是一个字母 
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

bool is_word(const char* str) {
	
	int alpha_count = 0;	// 开头连续字母的个数
	
	if(is_digit(*str))		// 如果第一个是数字字符，不是单词 
		return false;

	// 遍历字符串 
	for(const char *p = str; *p != '\0'; p ++) {
		
		if(is_alpha(*p))			// 如果是字符，字母数+1 
			alpha_count++;
		else if(alpha_count < 4)	// 碰到第一个非字母字符时，如果不满4个，不是单词 
			return false;
			
		if(alpha_count >= 4)
			return true;
	}
	return false;
}

void add_word_to_(WRec &records, const char* word) {
	
	for(int i = 0; i < records.n_word_count; i ++) {
		
		// 如果是重复单词，重复次数+1 
		if(strcmp(word, records.words[i].word) == 0) {
			
			records.words[i].n_word_repeat ++;
			return;
		}
	}
	
	// 否则作为新的单词添加 
	strcpy(records.words[records.n_word_count].word, word);
	records.words[records.n_word_count].n_word_repeat = 1;
	records.n_word_count ++;
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
	
	input.open(in_file);
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
			if(is_digit(*p) || is_alpha(*p)){	// 读到字母或数字字符，开始尝试按单词读入 
				
				
				if( !is_digit(*(p+1)) && !is_alpha(*(p+1)) ) {	// 下一个字符不为字母或数字字符时，完成读取 
					
					word_buf[word_len] = '\0';
					word_len = 0;
					if(is_word(word_buf)){
						
						add_word_to_(records, word_buf);
						n_word++;
					}
				}
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
