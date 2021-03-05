# 代码风格
+ 缩进
     每级都比上一级缩进4格。
```
void WordCount::charAndEntercount(string pathstr)
{
    ifstream infs;
    infs.open(path,ifstream::in);
	
    if(!infs)
    {
        cout<<"Cannot open file";
    }
    
    infs.close();
}
```
+ 变量命名
    用x_xxx的格式命名成员变量，用g_xxx的格式命名全局变量。
```
class WordCount
{
    private:
        int w_char;
        int w_word;
        int w_line;
}
```
+ 每行最多字符数
     100。
+ 函数最大行数
     100。
+ 函数、类命名
     函数命名多以小写字母开头，使用小驼峰法
`void charAndEntercount(string pathstr);`
+ 常量
   全大写+下划线。
`#define MAX_LENGTH 80`
+ 空行规则
    一个短句一行，相对独立的程序块之间，变量说明之后空行。
```
    int cc=0;
    int ec=0;	
    char temp;
    int isnewEnter=1;

    ifstream infs;
    infs.open(path,ifstream::in);
```
+ 注释规则
    - 一般使用单行双斜杠进行注释。
    - 会在重要函数上方做一个简单介绍函数功能的注释。
    - 会在变量旁做解释变量作用的注释。
```
//output wordcount
void WordCount::writeTxt(string outstr)
{
    output();
}
```
```
int wcot=0;        //the count of effective words
```
+ 操作符前后空格
     基本不加。
+ 其他规则