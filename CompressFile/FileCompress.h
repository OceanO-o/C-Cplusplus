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
	unsigned char _ch;   //�ַ�  256
	LongType _count;     //�ַ����ֵĴ���
	string _code;	      //Huffman����

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
		//1.���ļ���ͳ���ַ����ֵĴ���
		//2.���ɶ�Ӧ��HUffman����
		//3.ѹ���ļ�
		//4.д�����ļ�����������Ľ�ѹ��

		assert(filename);
		FILE* fOut = fopen(filename, "rb");
		assert(fOut);

		//ͳ���ַ����ֵĴ���
		char ch = fgetc(fOut);
		while (ch != EOF)
		{
			_infors[(unsigned char)ch]._count++;
			ch = fgetc(fOut);
		}

		//���ɶ�Ӧ��HuffmanCode
		HuffmanTree<FileInfo> HT;                                           /////////
		HuffmanTreeNode<FileInfo>* root = HT.CreateTree(_infors, 256, 0);   /////////
		_GenerateHuffmanCode(root);                                         /////////

		//3.ѹ���ļ�
		CompressFile(filename);

		//4.д�����ļ�����������Ľ�ѹ��
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

		//�����ǰ�ڵ���Ҷ�ӽڵ㣬�����ɶ�Ӧ�Ĺ���������
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

		FILE* fOut = fopen(filename, "rb");   //���ļ������
		assert(fOut);                                                   /////////////
		                                                                /////////////
		string CompressFile = filename;                                 ///////////////
		CompressFile = "Compress." + CompressFile;   //�½��ļ�������
		FILE* fInCompress = fopen(CompressFile.c_str(), "wb");//��д�ķ�ʽ�򿪣�ѹ���ļ�д��
		assert(fInCompress);

		int flag = 0;  //һ��code������������λ��
		unsigned char CHAR = 0;    //Ҫ������ַ�

		char ch = fgetc(fOut);//���ļ�
		while (ch != EOF)
		{
			int index = 0;      //�˸�һ����±�
			
			string code = _infors[(unsigned char)ch]._code;
			while (index < code.size())
			{
				unsigned char tmp = code[index] - '0';//��ȡλ
				tmp <<= flag;
				CHAR = CHAR | tmp;
				if (flag == 7)
				{
					//��chд���ļ�
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

		//���ļ������󣬻��в���8λ�ļ�0
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

		FILE* fOut = fopen(filename, "rb");//������ȡ
		assert(fOut);

		string NoCompressFile = filename;
		NoCompressFile ="config." + NoCompressFile;
		FILE* fInNoCompress = fopen(NoCompressFile.c_str(), "wb");//������ȡ
		assert(fInNoCompress);

		int Height = 0;       //��32λ
		int Low = 0;          //��32λ
		long long size = GetSize(fOut);   
		Low |= (size & 0xffffffff);    //������ȡ��λ
		Height |= size >> 32;          //������ȡ��λ

		char str1[128];                                         ////////////////
		_itoa_s(Low, str1, 10); // ��ʮ���Ʒ�ʽ���ȥ           ////////////////
		fputs(str1, fInNoCompress);                              ////////////////
		fputc('\n', fInNoCompress);   
		//

		char str2[128];
		_itoa_s(Height, str2, 10);   //9876
		fputs(str2, fInNoCompress);  //76 
		                             //98
		fputc('\n', fInNoCompress);
		//delete[] str2;

		//����infors
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
	//��ѹ��
	bool  NoCompress(const char* filename)
	{
		//�������ļ������մ�������
		assert(filename);                                  ////////////////////
		/////////////
		//�������ļ�
		string ConfigFile = filename;
		ConfigFile = "config." + ConfigFile;
		FILE* fOutConfig = fopen(ConfigFile.c_str(), "rb");
		assert(fOutConfig);

		//��ѹ���ļ�   CompressFile = "Compress." + CompressFile; 
		string CompressFile = filename;
		CompressFile = "Compress." + CompressFile;
		FILE* fOutCompress = fopen(CompressFile.c_str(), "rb");
		assert(fOutCompress);

		//��ѹ���ļ�
		string NoCompressFile = filename;
		NoCompressFile = "NoCompress." + NoCompressFile;
		FILE* fInNoCompress = fopen(NoCompressFile.c_str(), "wb");
		assert(fInNoCompress);

		//�������ļ������մ�������
		//ÿ�ζ�һ��

		//ͳ���ļ�������Ϊ��ֹ����
		long long size = 0;
		string str1 = GetLine(fOutConfig);//str1 ��ȡ�����ļ���������
		int tmp = atoi(str1.c_str());
		size >>= 32;
		size |= tmp;
		size <<= 32;
		string str2 = GetLine(fOutConfig);
		tmp = atoi(str2.c_str());
		size |= tmp;//����size�����������ļ�����//

		str1.clear();//?
		str2.clear();    //?

		string str = GetLine(fOutConfig);
		while (!str.empty())
		{
			string str2;
			str2 = str.substr(2);//ȥ�����ţ��Ժ���ֵ
			_infors[str[0]]._count = atoi(str2.c_str());
			str.clear();
			str = GetLine(fOutConfig);
		}

		//������������
		HuffmanTree<FileInfo> HT;
		HuffmanTreeNode<FileInfo>* root = HT.CreateTree(_infors, 256, 0);
		HuffmanTreeNode<FileInfo>* cur = root;

		//��ѹ���ļ�
		int flag = 0;
		char ch = fgetc(fOutCompress);
		while (cur && !feof(fOutCompress))//�ж��ļ��Ƿ����
		{
			//�ó�һ���ַ�Ȼ����в���
			int index = 0;
			while (cur && index < 8)
			{
				char CHAR = 1;
				CHAR = (CHAR << index) & ch;

				if (CHAR)      //��Ϊ��-��right
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


//ѹ���ļ�    -----ͳ�ƴ������������������---��Ҷ�ӽڵ㣬����Ҷ�ӽڵ�ȡ�ñ��룬�������
//
//�����ļ�   =======�����������ҵ� size,���棬ͳ��_ch����ͳ��_count
//
//��ѹ��     =========�������ļ������������ļ���ͳ��_count��������������
//                    ��ѹ���ļ���11011��������ֱ������һ��Ҷ�ӽڵ㣬�����Ҷ�ӽڵ�
//  ===============   �ġ���ch,