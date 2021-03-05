# Word Count

## 使用方法

WordCount.exe input.txt output.txt

## 功能

统计input.txt中字符个数、单词总数、有效行数和单词的出现次数（10个）

- 只统计Ascii码，汉字不考虑

- 空格，水平制表符，换行符，均算字符

- 英文字母： A-Z，a-z

- 字母数字符号：A-Z， a-z，0-9

- 分割符：空格，非字母数字符号

- **例**：file123是一个单词， 123file不是一个单词。file，File和FILE是同一个单词

- 频率相同的单词，优先输出字典序靠前的单词。

  > 例如，windows95，windows98和windows2000同时出现时，则先输出windows2000

- 输出的单词统一为小写格式

## 注意

输入文件的格式必须为UTF-8或者UTF-8 with BOM