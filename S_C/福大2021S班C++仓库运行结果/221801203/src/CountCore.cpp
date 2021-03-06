#define _CRT_SECURE_NO_WARNINGS
#include "CountCore.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

bool is_digit(char ch) {

	return (ch >= '0' && ch <= '9');
}

bool is_alpha(char ch) {

	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

char lowercase(char ch) {

	if (ch >= 'A' && ch <= 'Z')	// 大写字母的ascall加32等于对应的小写字母 
		return ch + 32;
	// 如果不是大写字母，返回原本的值 
	return ch;
}

bool is_word(const char* str) {

	int alpha_count = 0;	// 开头连续字母的个数

	if (is_digit(*str))		// 如果第一个是数字字符，不是单词 
		return false;

	// 遍历字符串 
	for (const char* p = str; *p != '\0'; p++) {

		if (is_alpha(*p))			// 如果是字符，字母数+1 
			alpha_count++;
		else if (alpha_count < 4)	// 碰到第一个非字母字符时，如果不满4个，不是单词 
			return false;

		if (alpha_count >= 4)
			return true;
	}
	return false;
}

void add_word_to_(WRec& records, const char* word) {

	for (int i = 0; i < records.n_word_count; i++) {

		// 如果是重复单词，重复次数+1 
		if (strcmp(word, records.words[i].word) == 0) {

			records.words[i].n_word_repeat++;
			return;
		}
	}

	// 否则作为新的单词添加 
	strcpy(records.words[records.n_word_count].word, word);
	records.words[records.n_word_count].n_word_repeat = 1;
	records.n_word_count++;
}

void sort_WRec(WRec& records) {

	WInfo temp;

	for (int i = 0; i < records.n_word_count - 1; i++) {

		for (int j = 0; j < records.n_word_count - 1 - i; j++) {

			// 单词的频率更大，或评率相同、字典序高的放前 
			if (records.words[j].n_word_repeat < records.words[j + 1].n_word_repeat
				|| records.words[j].n_word_repeat == records.words[j + 1].n_word_repeat && strcmp(records.words[j].word, records.words[j + 1].word) > 0) {

				temp = records.words[j];
				records.words[j] = records.words[j + 1];
				records.words[j + 1] = temp;
			}
		}
	}
}

void wordcount(const char* in_file, const char* out_file) {

	ifstream input;			// 输入文件 
	ofstream output;		// 输出文件 
	int      n_line = 0;	// 非空行数 
	int   	 n_word = 0;	// 单词数 
	int   	 n_char = 0;	// 字符数 
	WRec 	 records;		// 所有单词记录 
	char 	 last_ch = '\0';// 上一个读取的字符 
	char 	 ch;			// 读取的字符 
	char 	 buf[501];		// 缓冲区 
	char 	 word_buf[MAX_LEN_STR + 1];	// 单词缓冲区 
	int  	 word_len = 0;	// 单词长度 
	bool 	 line_empty;	// 行是否为空 

	int cur_line = 0;

	input.open(in_file, ios::binary);
	if (!input.is_open() || input.bad()) {

		printf("文件%s打卡失败\n", in_file);
        return;
	}

	records.n_word_count = 0;	// 初始单词数为0 

	n_line = 1;
	line_empty = true;
	while (!input.eof()) {		// 读取到文件尾 

		ch = input.get();
		if (ch == EOF || ch == '\0') {

			if (n_char == 0) {

				n_line = 0;
			}
			break;
		}

		n_char++;
		if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r') {		// 有其他字符时，该行非空 

			line_empty = false;
		}
		if (is_digit(ch) || is_alpha(ch)) {	// 读到字母或数字字符，开始尝试按单词读入 

			word_buf[word_len++] = lowercase(ch);
		}
		else if (word_len > 0 && (is_digit(last_ch) || is_alpha(last_ch))) {	// 当前字符不为字母或数字字符，且上一个字符是时 

			word_buf[word_len] = '\0';
			word_len = 0;
			if (is_word(word_buf)) {

				add_word_to_(records, word_buf);
				n_word++;
			}
		}

		if (ch == '\n') {

			if (!line_empty)
				n_line++;
			line_empty = true;
		}
		last_ch = ch;
	}
	input.close();
	if (line_empty)
		n_line--;
	if (word_len > 0 && (is_digit(last_ch) || is_alpha(last_ch))) {	// 当前字符不为字母或数字字符，且上一个字符是时 

		word_buf[word_len] = '\0';
		word_len = 0;
		if (is_word(word_buf)) {

			add_word_to_(records, word_buf);
			n_word++;
		}
	}
	sort_WRec(records);

	// 输出到指定输出文件 
	output.open(out_file);
	if (!output.is_open() || output.bad()) {

		printf("文件%s打开失败\n", out_file);
		return;
	}
	sprintf(buf, "characters: %d\nwords: %d\nlines: %d\n", n_char, n_word, n_line);
	output << buf;
	for (int i = 0; i < 10; i++) {

		sprintf(buf, "%s: %d\n", records.words[i].word, records.words[i].n_word_repeat);
		output << buf;
	}
	output.close();
}

