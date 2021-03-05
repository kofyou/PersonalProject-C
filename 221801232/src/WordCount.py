# coding:utf-8
import os, re, argparse
import unittest
import codecs



def count_chars(str):
    chars_num = 0
    for line in str:
        chars_num += len(line)
    return chars_num


def count_lines(str):
    lines_num = 0
    list_f = [line.strip() for line in str]
    for line in list_f:
        if len(line) > 0:
            lines_num += 1
    return lines_num


def count_words(str):
    words_num = 0
    list_f = [line.strip() for line in str]
    for line in list_f:
        if len(line) > 0:
            for word in re.split(r'[^A-Za-z0-9]', line):
                if re.match(r"^[A-Za-z]{4}[A-Za-z0-9]{0,}", word):
                    words_num += 1
    return words_num


def sort_words(content):
    word_dic = {}
    list_f = [line.strip() for line in content]
    for line in list_f:
        if len(line) > 0:
            for word in re.split(r'[^A-Za-z0-9]', line):
                if re.match(r"^[A-Za-z]{4}[A-Za-z0-9]{0,}", word):
                    word = word.lower()
                    word_dic[word] = word_dic.get(word, 0)+1
    word_dic = sorted(word_dic.items(), key=lambda x: (-x[1], x[0]))
    return word_dic


def main(inputfile, outputfile):
    with open(inputfile, 'r', newline="\n", encoding='utf-8') as f:
        text = f.readlines()
    chars_num = count_chars(text)
    lines_num = count_lines(text)
    words_num = count_words(text)
    count_num = sort_words(text)
    with open(outputfile, 'w', newline="\n", encoding='utf-8') as wf:
        wf.write('characters:'+str(chars_num)+'\nwords:'+str(words_num)+'\nlines:'+str(lines_num)+'\n')
        if len(count_num) >= 10:
            for i in range(10):
                wf.write(count_num[i][0]+':'+str(count_num[i][1])+'\n')
        else:
            for i in range(len(count_num)):
                wf.write(count_num[i][0]+':'+str(count_num[i][1])+'\n')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('input', type=str, default='input.txt', help='input_file_path')
    parser.add_argument('output', type=str, default='output.txt', help='output_file_path')
    args = parser.parse_args()
    main(args.input, args.output)


