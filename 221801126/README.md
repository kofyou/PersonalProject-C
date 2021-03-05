# WordCount

## 文件包含：

`CountWord.cpp (主程序，可以从命令行接收参数)`
    `Lib.h(包含其它自定义函数)`
    `Lib.cpp(包含其它自定义函数)`

## 项目思考与实践：

1. **文件需要通过命令行输入输出** 使用C++的文件处理流来处理I/O操作
2. **统计字符** 使用`string`类自带的长度统计函数解决
3. **统计单词总数** 此处需要

   - 判断是否为单词 通过逻辑判断函数处理
   - 不同单词的区分 使用`map`
   - 统计单词个数 同步计数即可
4. **有效行数**

   -  判断换行符
   -  判断是否为空行
   -  判断是否有`\t \n \r null`字符出现
5. **容错性**  使用抛出捕获异常处理



首先进行I/O读取使用：`string InputFile(const char* filename);`

接下来将得到的字符串送入个函数接口进行处理：

`int CountChar(string inputString);`统计字符接口
`int CountWord(string inputString); `统计单词接口
`int CountRow(string inputString);`统计有效行接口

最后进行文件输出：`void OutputFlie(char* filename,string inputString) ;`

## 作业链接

[作业链接](https://edu.cnblogs.com/campus/fzu/FZUSESPR21/homework/11672)

## 博客链接 

[博客链接](https://www.cnblogs.com/yangzishen/)


