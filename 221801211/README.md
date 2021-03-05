# README

## PSP

| Personal Software Process Stages        | 预估耗时(分钟) | 实际耗时（分钟） |
| :-------------------------------------- | :------------- | :--------------- |
| 计划                                    |                |                  |
| • 估计这个任务需要多少时间              | 5              | 5                |
| • 开发                                  |                |                  |
| • 需求分析 (包括学习新技术)             | 120            | 180              |
| • 生成设计文档                          | 60             | 50               |
| • 设计复审                              | 30             | 20               |
| • 代码规范 (为目前的开发制定合适的规范) | 40             | 35               |
| • 具体设计                              | 60             | 50               |
| • 具体编码                              | 720            | 1200             |
| • 代码复审                              | 30             | 30               |
| • 测试（自我测试，修改代码，提交修改）  | 540            | 480              |
| 报告                                    | 60             | 50               |
| • 测试报告                              | 30             | 20               |
| • 计算工作量                            | 30             | 10               |
| • 事后总结, 并提出过程改进计划          | 30             | 20               |
| 合计                                    | 1725           | 2130             |

## 代码部分：

1. 数据存储：

   使用最简单的存储方式：创建一个大小为10000的字符数组存储从文件中读取的每一个字符

   ```
   char buffer[MAXWORDS] = {};	//MAXWORDS为宏定义，大小为100000
   ```

2. 读取方式：

   使用文件流按字符读取数据并存入数组中（因不区分大小写，此处读取的时候把所有小写字母转变为了大写字母，便于后面的判断）

   ``` c++
   ifstream inFile;
   inFile.open(argv[1]);
   char x;
   	while ((x=inFile.get())!=EOF)
   	{
   		if (x <= 'z' && x >= 'a')
   		{
   			x = x - 32;
   		}
   		buffer[i] = x;
   		i++;
   	}
   ```

3. 函数实现：

   1. 统计字符：

      ``` c++
      int GetCharacters(char *str)
      {
      	return strlen(str);
      }
      ```

   2. 统计单词数量：

      ``` c++
      int GetWords(char* str)
      {
      	char temp[MAXWORD][MAXWORD];
      	int j = 0;
      	int num = 0;
      	for (int i = 0; i < strlen(str); i++)
      	{
      		if (str[i] != ' '&&str[i]!='\n')
      		{
      			temp[num][j] = str[i];
      			j++;
      		}
      		if (j == strlen(str))
      		{
      			if (j >= 4)
      			{
      				if ((('a' <= temp[num][0] && temp[num][0] <= 'z') || ('A' <= temp[num][0] && temp[num][0] <= 'Z')) &&
      					(('a' <= temp[num][1] && temp[num][1] <= 'z') || ('A' <= temp[num][1] && temp[num][1] <= 'Z')) &&
      					(('a' <= temp[num][2] && temp[num][2] <= 'z') || ('A' <= temp[num][2] && temp[num][2] <= 'Z')) &&
      					(('a' <= temp[num][3] && temp[num][3] <= 'z') || ('A' <= temp[num][3] && temp[num][3] <= 'Z')))
      				{
      					return 1;
      				}
      				
      			}
      		}
      		else if (str[i] == ' '||i == strlen(str)-1||str[i]=='\n')
      		{
      			if (j >= 4)
      			{
      				if ((('a' <= temp[num][0] && temp[num][0] <= 'z') || ('A' <= temp[num][0] && temp[num][0] <= 'Z')) &&
      					(('a' <= temp[num][1] && temp[num][1] <= 'z') || ('A' <= temp[num][1] && temp[num][1] <= 'Z')) &&
      					(('a' <= temp[num][2] && temp[num][2] <= 'z') || ('A' <= temp[num][2] && temp[num][2] <= 'Z')) &&
      					(('a' <= temp[num][3] && temp[num][3] <= 'z') || ('A' <= temp[num][3] && temp[num][3] <= 'Z')))
      				{
      					num++;
      				}
      			}
      			j = 0;
      		}
      	}
      	return num;
      }
      ```
      
   3. 统计行数：
   
      ``` c++
   int GetLines(char* str)
      {
   	int n = strlen(str);
      	int num = 0;
      	if (str[n - 1] == '\n')
      	{
      		num--;
      	}
      	for (int i = 0; i < n; i++)
      	{
      		if (str[i] == '\n')
      		{
      			if (str[i + 1] != '\n')
      			{
      				num++;
      			}
      		}
      	}
      	return num+1;
      }
      ```
   
   4. 按照出现次数从多到少排列：
   
      ``` c++
   void GetNumbers(char* str,string filename)
      {
   	char temp[MAXWORD][MAXWORD] = {0};
      	int j = 0;
      	int num = 0;
      	string strx[MAXWORD] = {};
      
      	for (int i = 0; i < strlen(str); i++)
      	{
      		if (str[i] != ' ' && str[i] != '\n')
      		{
      			temp[num][j] = str[i];
      			j++;
      		}
      		else if (str[i] == ' ' || i == strlen(str) - 1 || str[i] == '\n')
      		{
      			if (j >= 4)
      			{
      				if ((('a' <= temp[num][0] && temp[num][0] <= 'z') || ('A' <= temp[num][0] && temp[num][0] <= 'Z')) &&
      					(('a' <= temp[num][1] && temp[num][1] <= 'z') || ('A' <= temp[num][1] && temp[num][1] <= 'Z')) &&
      					(('a' <= temp[num][2] && temp[num][2] <= 'z') || ('A' <= temp[num][2] && temp[num][2] <= 'Z')) &&
      					(('a' <= temp[num][3] && temp[num][3] <= 'z') || ('A' <= temp[num][3] && temp[num][3] <= 'Z')))
      				{
      					num++;
      				}
      			}
      			j = 0;
      		}
      	}
      	for (int i = 0; i < num; i++)
      	{
      		for (int j = 0; j < MAXWORD; j++)
      		{
      			if (temp[i][j] != 0)
      			{
      				strx[i]+=temp[i][j];
      			}
      		}
      	}
      }
      ```
   
4. 单元测试：

   1. 测试统计字符函数：

      ``` c++
      TEST_METHOD(TestMethod1)
      		{
      			ifstream inFile;
      			inFile.open("F:\\test.txt");
      			char buffer[MAXWORDS] = {};
      			long i = 0;
      			char x;
      			while ((x = inFile.get()) != EOF)
      			{
      				buffer[i] = x;
      				i++;
      			}
      			Assert::AreEqual(GetCharacters(buffer), 44);
      		}
      ```

   2. 测试统计单词量函数：

   	``` c++
   TEST_METHOD(TestMethod2)
   		{
   			ifstream inFile;
   			inFile.open("F:\\test.txt");
   			char buffer[MAXWORDS] = {};
   			long i = 0;
   			char x;
   			while ((x = inFile.get()) != EOF)
   			{
   				buffer[i] = x;
   				i++;
   			}
   			Assert::AreEqual(GetWords(buffer), 5);
   		}
   	```

   3. 测试统计行数函数：

      ``` c++
      TEST_METHOD(TestMethod3)
      		{
      			ifstream inFile;
      			inFile.open("F:\\test.txt");
      			char buffer[MAXWORDS] = {};
      			long i = 0;
      			char x;
      			while ((x = inFile.get()) != EOF)
      			{
      				buffer[i] = x;
      				i++;
      			}
      			Assert::AreEqual(GetLines(buffer), 6);
      		}
      ```

5. 代码覆盖率检测：

   ![img](file:///C:\Users\99647\Documents\Tencent Files\996478603\Image\Group2\H$\WN\H$WN8A2_3D8[_5]3C_GTYPO.png)