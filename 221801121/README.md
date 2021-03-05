### wordcount-C语言提交

#### 内包含：

1. README.md  说明文档
2. codestyle.md  代码规范
3. Lib.h 头文件内含类、结构体、函数声明
4. WordCount.cpp  main函数在其中，可以接收命令行参数

- 题目要求：https://edu.cnblogs.com/campus/fzu/FZUSESPR21/homework/11672 
- 博客链接：https://www.cnblogs.com/221801121hw/p/14484513.html

功能简介：

实现统计文件的字符数，单词总数，有效行数，各单词的出现次数。

运行说明：

输入文件和输出文件以命令行参数传入。在输入文件和输出文件都可以打开的情况下，main函数实例化analysisFlie类后调用其中的函数，通过getXXX返回字符计算，行数计算，词频统计排序所需要的数据，并存储在指定文本中。