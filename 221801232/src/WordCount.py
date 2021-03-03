import os,re,argparse
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
            for word in re.split(r'[^A-Za-z0-9]',line):
                if re.match(r"^[A-Za-z]{4}[A-Za-z0-9]{0,}",word):
                    words_num += 1
    return words_num
def main(inputfile, outputfile):
    # inputfile='input.txt'
    # outputfile='output.txt'
    with open(inputfile, 'r', newline="\n") as f:
        text = f.readlines()
    chars_num = count_chars(text)
    lines_num = count_lines(text)
    words_num = count_words(text)
    with open(outputfile, 'w', newline="\n") as wf:
        wf.write('characters:'+str(chars_num)+'\nwords:'+str(words_num)+'\nlines:'+str(lines_num))
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('input', type=str,default='input.txt',help='input_file_path')
    parser.add_argument('output', type=str,default='output.txt', help='output_file_path')
    args = parser.parse_args()
    main(args.input,args.output)
    

