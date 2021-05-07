#pragma once

//#define _CRT_SECURE_NO_WARNINGS 1

#include <string>
#include <assert.h>
#include <algorithm>
#include <iostream>

using namespace std;
#pragma warning(disable:4996)

typedef long LongType;
struct FileInfo
{
	unsigned char _ch;   //字符  256
	LongType _count;     //字符出现的次数
	string _code;	      //Huffman编码

	FileInfo(unsigned char ch = 0)
		:_ch(ch)
		, _count(0)
		, _code("")
	{}

	bool operator < (const FileInfo& info)
	{
		return this->_count < info._count;
	}

	bool operator != (const int& illegal)const
	{
		if (this->_count != illegal)
			return true;
		return false;
	}

	FileInfo operator + (const FileInfo& info)
	{
		FileInfo FI;
		FI._count = this->_count + info._count;
		return FI;
	}
};

class FileCompress
{
public:
	FileCompress()
	{
		for (int i = 0; i < 256; ++i)
		{
			_infors[i]._ch = (unsigned char)i;                           //////
		}//   _infors[1]._ch = 1    FileInfo _infors[256];               //////
	}                                                                     //////
public:
	bool Compress(const char* filename)
	{
		//1.打开文件，统计字符出现的次数
		//2.生成对应的HUffman编码
		//3.压缩文件
		//4.写配置文件，方便后续的解压缩

		assert(filename);
		FILE* fOut = fopen(filename, "rb");
		assert(fOut);

		//统计字符出现的次数
		char ch = fgetc(fOut);
		while (ch != EOF)
		{
			_infors[(unsigned char)ch]._count++;
			ch = fgetc(fOut);
		}

		//生成对应的HuffmanCode
		HuffmanTree<FileInfo> HT;                                           /////////
		HuffmanTreeNode<FileInfo>* root = HT.CreateTree(_infors, 256, 0);   /////////
		_GenerateHuffmanCode(root);                                         /////////

		//3.压缩文件
		CompressFile(filename);

		//4.写配置文件，方便后续的解压缩
		ConfigFile(filename);
		
		return true;
	}

	
public:
	void _GenerateHuffmanCode(HuffmanTreeNode<FileInfo>* root)
	{
		if (NULL == root)
			return;

		_GenerateHuffmanCode(root->_left);
		_GenerateHuffmanCode(root->_right);

		//如果当前节点是叶子节点，则生成对应的哈夫曼编码
		if (root->_left == NULL && root->_right == NULL)
		{
			HuffmanTreeNode<FileInfo>* cur = root;
			HuffmanTreeNode<FileInfo>* parent = cur->_parent;
			//                          T    _weight
			string& code = _infors[cur->_weight._ch]._code;//a-> 10  ???????

			while (parent)
			{
				if (parent->_left == cur)                     ///////////////
				{                                             //////////////
					code += '0';                              ///////////////
				}
				else
				{
					code += '1';
				}
				cur = cur->_parent;
				parent = cur->_parent;
			}

			reverse(code.begin() , code.end());			
		}
	}

	void CompressFile(const char* filename)
	{
		assert(filename);

		FILE* fOut = fopen(filename, "rb");   //从文件里面读
		assert(fOut);                                                   /////////////
		                                                                /////////////
		string CompressFile = filename;                                 ///////////////
		CompressFile = "Compress." + CompressFile;   //新建文件并命名
		FILE* fInCompress = fopen(CompressFile.c_str(), "wb");//以写的方式打开，压缩文件写入
		assert(fInCompress);

		int flag = 0;  //一个code操作完后的所在位置
		unsigned char CHAR = 0;    //要存入的字符

		char ch = fgetc(fOut);//读文件
		while (ch != EOF)
		{
			int index = 0;      //八个一组的下标
			
			string code = _infors[(unsigned char)ch]._code;
			while (index < code.size())
			{
				unsigned char tmp = code[index] - '0';//获取位
				tmp <<= flag;
				CHAR = CHAR | tmp;
				if (flag == 7)
				{
					//将ch写入文件
					fputc(CHAR, fInCompress);
					CHAR = 0;
				}
				++index;
				++flag;
				if (flag == 8)
				{
					flag -= 8;
				}
			}

			ch = fgetc(fOut);
		}

		//读文件结束后，还有不够8位的加0
		if (flag != 0)
		{
			fputc(CHAR, fInCompress);
		}

		fclose(fOut);
		fclose(fInCompress);
	}

	void ConfigFile(const char* filename)
	{
		assert(filename);

		FILE* fOut = fopen(filename, "rb");//用来读取
		assert(fOut);

		string NoCompressFile = filename;
		NoCompressFile ="config." + NoCompressFile;
		FILE* fInNoCompress = fopen(NoCompressFile.c_str(), "wb");//用来存取
		assert(fInNoCompress);

		int Height = 0;       //高32位
		int Low = 0;          //低32位
		long long size = GetSize(fOut);   
		Low |= (size & 0xffffffff);    //用来获取低位
		Height |= size >> 32;          //用来获取高位

		char str1[128];                                         ////////////////
		_itoa_s(Low, str1, 10); // 以十进制方式存进去           ////////////////
		fputs(str1, fInNoCompress);                              ////////////////
		fputc('\n', fInNoCompress);   
		//

		char str2[128];
		_itoa_s(Height, str2, 10);   //9876
		fputs(str2, fInNoCompress);  //76 
		                             //98
		fputc('\n', fInNoCompress);
		//delete[] str2;

		//利用infors
		for (int i = 0; i < 256; ++i)
		{
			if (_infors[i]._count)
			{
				char buffer[128];
				fputc(_infors[i]._ch, fInNoCompress);
				fputc(',', fInNoCompress);
				                                          // a,10
				                                         // b,20
				_itoa_s(_infors[i]._count, buffer, 10);
				fputs(buffer, fInNoCompress);

				//delete[] buffer;
				fputc('\n', fInNoCompress);
			}
		}

		fclose(fOut);
		fclose(fInNoCompress);
		//delete[] str1;
		//delete[] str2;
		//delete[] buffer;
	}

	string GetLine(FILE* fOut)
	{
		assert(fOut);

		string str = "";

		char ch = fgetc(fOut);
		while (ch != EOF && ch != '\n')
		{
			str += ch;
			ch = fgetc(fOut);
		}
		return str;
	}

	long long GetSize(FILE* fOut)
	{
		assert(fOut);
		long long size = 0;
		for (int i = 0; i < 256; ++i)
		{
			if (_infors[i]._count)
			{
				size = size + _infors[i]._count;
			}
		}
		return size;
	}
	//解压缩
	bool  NoCompress(const char* filename)
	{
		//读配置文件，依照次数建树
		assert(filename);                                  ////////////////////
		/////////////
		//读配置文件
		string ConfigFile = filename;
		ConfigFile = "config." + ConfigFile;
		FILE* fOutConfig = fopen(ConfigFile.c_str(), "rb");
		assert(fOutConfig);

		//读压缩文件   CompressFile = "Compress." + CompressFile; 
		string CompressFile = filename;
		CompressFile = "Compress." + CompressFile;
		FILE* fOutCompress = fopen(CompressFile.c_str(), "rb");
		assert(fOutCompress);

		//解压缩文件
		string NoCompressFile = filename;
		NoCompressFile = "NoCompress." + NoCompressFile;
		FILE* fInNoCompress = fopen(NoCompressFile.c_str(), "wb");
		assert(fInNoCompress);

		//读配置文件，依照次数建树
		//每次读一行

		//统计文件个数作为终止条件
		long long size = 0;
		string str1 = GetLine(fOutConfig);//str1 读取配置文件所有数据
		int tmp = atoi(str1.c_str());
		size >>= 32;
		size |= tmp;
		size <<= 32;
		string str2 = GetLine(fOutConfig);
		tmp = atoi(str2.c_str());
		size |= tmp;//现在size保存着所有文件个数//

		str1.clear();//?
		str2.clear();    //?

		string str = GetLine(fOutConfig);
		while (!str.empty())
		{
			string str2;
			str2 = str.substr(2);//去掉逗号，以后是值
			_infors[str[0]]._count = atoi(str2.c_str());
			str.clear();
			str = GetLine(fOutConfig);
		}

		//创建哈弗曼树
		HuffmanTree<FileInfo> HT;
		HuffmanTreeNode<FileInfo>* root = HT.CreateTree(_infors, 256, 0);
		HuffmanTreeNode<FileInfo>* cur = root;

		//解压缩文件
		int flag = 0;
		char ch = fgetc(fOutCompress);
		while (cur && !feof(fOutCompress))//判断文件是否结束
		{
			//拿出一个字符然后进行操作
			int index = 0;
			while (cur && index < 8)
			{
				char CHAR = 1;
				CHAR = (CHAR << index) & ch;

				if (CHAR)      //不为零-》right
					cur = cur->_right;
				else
					cur = cur->_left;

				if (cur && cur->_left == NULL && cur->_right == NULL)
				{
					fputc((unsigned char)cur->_weight._ch, fInNoCompress);
					++flag;
					if (flag == size)
					{
						break;
					}
					cur = root;
				}
				++index;
			}

			ch = fgetc(fOutCompress);
		}

		fclose(fOutConfig);
		fclose(fOutCompress);
		fclose(fInNoCompress);
		return true;
	}
private:
	FileInfo _infors[256];
};


//压缩文件    -----统计次数，创建哈尼夫曼树---找叶子节点，根据叶子节点取得编码，保存编码
//
//配置文件   =======挨个遍历先找到 size,保存，统计_ch并且统计_count
//
//解压缩     =========读配置文件，根据配置文件，统计_count来建立哈夫曼树
//                    读压缩文件，11011，读树，直到读到一个叶子节点，就输出叶子节点
//  ===============   的——ch,