##代码规范
###缩进
4个空格
```
for line in list_f:
    if len(line) > 0:
            lines_num += 1
```
###变量命名
下划线法命名
```
chars_num = count_chars(text)
lines_num = count_lines(text)
```
###每行最多字符数
每行尽量不超过80个字符

###函数、类命名
函数采用下划线法命名
```
ef sort_words(content):
```
类采用大驼峰法命名
```
class TestWord(TestCase):
```

###空行

函数与函数之间、类与类之间用两个空行隔开
方法中不同的逻辑相关之间用一个空行隔开

###操作符前后空格
在操作符前后各加一个空格
```words_num += 1```
在参数的逗号后面加一个空格
```
with open(inputfile, 'r', newline="\n") as f:
```
参数中，默认值的等号两边不加空格
```
with open(inputfile, 'r', newline="\n") as f:
```
