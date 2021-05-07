#include <iostream>
#include <Windows.h>

#include "Heap.h"
#include "HuffmanTree.h"
#include "FileCompress.h"

using namespace std;

void TestHuffmanCompress1()
{
	FileCompress FC;

	int begin1 = GetTickCount();
	FC.Compress("File.txt");
	int end1 = GetTickCount();
	int begin2 = GetTickCount();
	FC.NoCompress("File.txt");
	int end2 = GetTickCount();

	cout << "Compress:" << end1 - begin1 << endl;
	cout << "NoCompare:" << end2 - begin2 << endl;
}
void TestHuffmanCompress2()
{
	FileCompress FC;

	int begin1 = GetTickCount();
	FC.Compress("Hometown.txt");
	int end1 = GetTickCount();
	int begin2 = GetTickCount();
	FC.NoCompress("Hometown.txt");
	int end2 = GetTickCount();

	cout << "Compress:" << end1 - begin1 << endl;
	cout << "NoCompare:" << end2 - begin2 << endl;
}