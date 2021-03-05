#pragma once


const int MAX_LEN_STR = 100;	// 单词字符串的最大长度 

typedef struct word_info {		// 结构体：单词记录 
	char word[MAX_LEN_STR + 1];	// 单词 
	int  n_word_repeat;			// 单词重复的次数 
}WInfo;

typedef struct words_record {	// 结构体：单词记录 
	WInfo words[501];			// 所有单词 
	int n_word_count;			// 单词的数量 
}WRec;

bool is_digit(char ch);			// 判断ch是否是一个数字字符 
bool is_alpha(char ch);			// 判断ch是否是一个字母 
char lowercase(char ch);		// 将ch转换为小写 
void add_word_to_(WRec& records, const char* word);			// 将word加到records中 
void sort_WRec(WRec& records);								// 按照频率和字典顺序排序 
void wordcount(const char* in_file, const char* out_file);	// 对输入文件in_file进行统计，输出到out_file
