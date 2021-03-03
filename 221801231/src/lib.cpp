#include "lib.h"
/*************************************************
 Description:ͨ����������ļ����������ַ��Ķ�ȡ�Լ����ַ�����
 Input: ��������ֱ�Ϊfstream�������in���������ļ��Ķ�ȡ����out����д������ļ��������.
 Output: ���ֵΪ�����output�ļ����ַ����ִ���// �����������˵����
 Return:�����ַ�������intֵ.
 Others:
*************************************************/
int myfile::Countchar(fstream &in, fstream &out)
{

	int totalCount = 0;
	char temp;
	in.unsetf(ios_base::skipws);//���ò��������з��Ϳհ׷�
	in >> temp;
	while (!in.eof())
	{
		totalCount++;
		in >> temp;
	}
	out << "characters:" << totalCount << '\n';
	return totalCount;
}
/*************************************************
 Description:ͨ����������ļ����������ַ��Ķ�ȡ������ȡ�����ַ�ƴ��Ϊ�ַ������������ָ������ǰƴ�ӳɵ��ַ������м�飬�ж��Ƿ�Ϊ��Ч�ĵ��ʣ�����Ч�����map�����С���Ч��������
 Input: ��������ֱ�Ϊfstream�������in���������ļ��Ķ�ȡ����out����д������ļ��������// �������˵��������ÿ����������
 // �á�ȡֵ˵�����������ϵ��
 Output: ���ֵΪ�����output�ļ��ĵ����ܼƳ��ִ���// �����������˵����
 Return:���ص���������intֵ. // ��������ֵ��˵��
 Others: // ����˵��
*************************************************/
int myfile::Countword(fstream &in, fstream &out)
{
	bool isWord = true;//�ж��ַ��������Ƿ���ϵ������
	in.unsetf(ios_base::skipws);//���ò��������з��Ϳհ׷�
	if (!in.is_open())
	{
		cout << "�޷����ļ�" << endl;
		exit(0);
	}
	int totalCount = 0;
	string wordString = "";
	char temp;
	in >> noskipws;
	if (in.eof())
	{
		cout << "�ļ�����ĩβ" << endl;
	}
	while (!in.eof())
	{

		in >> temp;
		if (temp <= 'Z'&&temp >= 'A')//����ַ�Ϊ��д��ĸ����ת��ΪСд��ĸ
		{
			temp += 32;
		}
		if (!(isalpha(temp)||isdigit(temp)))//�ж��Ƿ������ָ��������ִ����������
		{
			if (wordString.length() < 4)//������ʳ���С��4����ֱ������������ַ�������
			{
				wordString = "";
				continue;
			}
			for (int i = 0;i < 4;i++)
			{
				if (!isalpha(wordString[i]))//�ж��ַ���ǰ��λ�Ƿ�Ϊ��ĸ����Ϊ��ĸ��ֱ�ӽ���ѭ��
				{
					wordString = "";
					isWord = false;
					break;
				}

			}
			if (!isWord)//�����Ϊ���������ִ����һ��whileѭ������ִ�����´���
			{
				isWord = true;
				continue;
			}
			totalCount++;

			//ͨ��find�����жϵ����Ƿ���map�����г��ֹ��������ֹ������ӵ��������ص�ָ���ֵ�ȵ��ʴ������ɣ�δ���ֹ�������µ�Ԫ�ء�
			map<string, int>::iterator it = this->wMap.find(wordString);
			if (it != this->wMap.end())
			{
				it->second++;
			}
			else
			{
				this->wMap.insert(pair<string, int>(wordString, 1));
			}
			wordString = "";
		}
		else	wordString = wordString + temp;
	}
	if (!wordString.empty())//���ļ���ȡ������û�������ָ���ȴ�ַ�����ȴ�������ݣ�Ҫ�������һ�μ�顣
	{
		if (wordString.length() < 4)//������ʳ���С��4����ֱ������������ַ�������
		{
			wordString = "";

		}
		for (int i = 0;i <= 4;i++)
		{
			if (!isalpha(wordString[i]))//�ж��ַ���ǰ��λ�Ƿ�Ϊ��ĸ����Ϊ��ĸ��ֱ�ӽ���ѭ��
			{
				wordString = "";
				isWord = false;
				break;
			}

		}
		if (isWord)
		{
			for (int j = 0;j < wordString.length();j++)
			{

				if (wordString[j] <= 'Z'&&wordString[j] >= 'A')
				{
					wordString[j] += 32;
				}
			}
			totalCount++;
			map<string, int>::iterator it = this->wMap.find(wordString);
			if (it != this->wMap.end())
			{
				it->second++;
			}
			else
			{
				this->wMap.insert(pair<string, int>(wordString, 1));
			}
			wordString = "";
		}
		else
		{
			isWord = true;//����isWord��ʶ��
		}
	}

	out << "word:" << totalCount << endl;//������ʵ�����
	return totalCount;
}
/*************************************************
 Description:ͨ����������ļ����������еĶ�ȡ��ͳ���ļ�������
 Input: ��������ֱ�Ϊfstream�������in���������ļ��Ķ�ȡ����out����д������ļ��������// �������˵��������ÿ����������
 // �á�ȡֵ˵�����������ϵ��
 Output: ���ֵΪ�����output�ļ���input�ļ����ܹ���������// �����������˵����
 Return:��������������intֵ // ��������ֵ��˵��
 Others: // ����˵��
*************************************************/
int myfile::Countline(fstream &in, fstream &out)
{
	if (!in.is_open())
	{
		cout << "�޷����ļ�" << endl;
		exit(0);
	}
	int totalCount = 0;
	string line;
	while (!in.eof())
	{
		getline(in, line);
		for (int i = 0;i < line.length();i++)
		{
			if (!isspace(line[i]))//���ļ��������еĶ�ȡ���ж��Ƿ���ڷǿհ��ַ���
			{
				totalCount++;
				break;
			}
		}
	}
	out << "line:" << totalCount << endl;
	return totalCount;
}
/*************************************************
 Description:��Ϊvector�������Զ���ıȽϺ����Ƚ�vector�����е�pair<string,int>Ԫ�أ����ȸ��ݵ��ʳ��ִ������бȽϣ������map�ٸ��ݼ�ֵ�ֵ�������
 Input: �������Ϊ�������ԱȽϵ�pair<string,int>�ೣ������ϵΪ��Ϊ�����е�Ԫ���Խ��бȽϡ�
 Output: �����ֵ
 Return:�ж�����pair<string,int>��Ԫ��֮���С��boolֵ
 Others: // ����˵��
*************************************************/
bool Sortwordtimes(const pair<string, int> &wordA, const pair<string, int> &wordB)
{

	return wordA.second > wordB.second;

}
/*************************************************
 Description:��map���������ݿ�����vector,�ھ������Ե�vector����ͨ��vector�����ĵ�������������������õ��ʳ��ֵĴ���ǰʮ�ߵĵ���������ִ���д������ļ���
 Input: ��������ֱ�Ϊfstream�������out������Ҫ����ļ�����.
 Output: ���ֵΪ�����output�ļ��ĵ������뵥�ʳ��ִ���.
 Return:��returnֵ
 Others:
*************************************************/
void myfile::Sortmap(fstream &out)
{
	vector< pair<string, int> > vec(this->wMap.begin(), this->wMap.end());
	sort(vec.begin(), vec.end(), Sortwordtimes);
	if (vec.size() < 10)
	{
		for (int i = 0;i < vec.size();i++)
		{
			out << vec[i].first << ":" << vec[i].second << endl;
		}
	}
	else
	{
		for (int i = 0;i < 10;i++)
		{
			out << vec[i].first << ":" << vec[i].second << endl;
		}
	}
}