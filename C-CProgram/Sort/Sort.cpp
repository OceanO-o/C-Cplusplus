void InsertSort(int* a, size_t size)
{
	for (size_t j = 1; j < size; j++)//插入次数
	{
		size_t i = 0;//每次都从最前面去比较，看看是不是插入的比前面会小
		while (i < j && a[i] < a[j])
		{
			i++;    //如果进来就表明前面已经排好了，一旦出去表示，插入的数比i所在位置数小
		}
		int tmp = a[j];//下面移动时，就把a[j]的值覆盖了，所以要保存
		for (size_t index = j; index > i; index--) //把i后面的数据从后往前移动
		{
			a[index] = a[index - 1];
		}
		a[i] = tmp;
	}
}

void Test1()
{
	int a[10] = { 2, 5, 8, 1, 9, 4, 6, 0, 3, 7 };
	InsertSort(a, sizeof(a) / sizeof(a[0]));
	for (size_t i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void ShellSort(int* a, int size)
{
	int gap = size;
	while (gap >1)
	{
		gap = gap / 3 + 1;
		for (int i = gap; i < size; i++)
		{
			int index = i;
			int tmp = a[index];//这个值可能会在比较中吧这个位置的值换掉
			int end = index - gap;

			while (end >= 0 && tmp < a[end])//这里其实就是一个段的插入排序。
			{
				a[end + gap] = a[end];
				end -= gap;
			}

			a[end+gap] = tmp;//为什么是+因为，如果从while里面出来，end是负的，此时其实是给a[end]赋值

		}
	}
}
void Test2()
{
	int a[10] = { 2, 5, 8, 1, 9, 4, 6, 0, 3, 7 };
	ShellSort(a, sizeof(a) / sizeof(a[0]));
	for (size_t i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void BubleSort(int* a,int size)
{
	for (int i = 0; i < size; i++)//控制循环次数
	{
		for (int j = i; j < size; j++)
		{
			if (a[i] > a[j])
			{
			
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}//相比于选择排序，这个碰到不是顺序的就交换，选择先记住下标，在每趟最后交换值
	}
}

void Test3()
{
	int a[10] = { 2, 5, 8, 1, 9, 4, 6, 0, 3, 7 };
	BubleSort(a, sizeof(a) / sizeof(a[0]));
	for (size_t i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void SelectSort(int*a, int size)
{
	for (int i = 0; i < size; i++)
	{
		int index = 0;
		for (int j = 0; j < size-i; j++)
		{
			if (a[index] < a[j])
			{
				index = j;				
			}	//让index成为最大值的下标
		}
		swap(a[size - i - 1], a[index]);
	}//每趟只有一次交换，比较次数和冒泡一样
}

void Test4()
{
	int a[10] = { 2, 5, 8, 1, 9, 4, 6, 0, 3, 7 };
	SelectSort(a, sizeof(a) / sizeof(a[0]));
	for (size_t i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

//int ThreeMid(int* a, int left, int right)
//{        //虽说是取三个数的中间数，到下面的程序就是取数组里面三个值得中间值
//	int mid = left + (left - right) / 2;
//	if (a[left] > a[right])
//	{
//		if (a[right] > a[mid])
//			return right;
//		if (a[mid] > a[left])
//			return left;
//		else
//			return mid;
//	}
//
//	if (a[right] > a[left])
//	{
//		if (a[left] > a[mid])
//			return left;
//		if (a[mid] > a[right])
//			return right;
//		else
//			return mid;
//	}
//}
void QuickSort(int* a, int left,int right)

{
	//int mid = ThreeMid(a, low, high);
	//swap(a[mid], a[high]);
	if (left >= right)
		return;
	int low = left;
	int high = right;
	int key = a[high];
	
	while (low < high)
	{
		while ( (low < high) && a[high] >= key)
		{
			--high;
		}
		a[low] = a[high];

		while ((low < high) && a[low] <= key)
		{
			++low;
		}
		a[high] = a[low];
		

	}
	a[low] = key;

	QuickSort(a, left, low-1);
	QuickSort(a, low + 1, right);
}

void Test5()
{
	int a[10] = { 2, 7, 8, 1, 9, 4, 6, 0, 3, 5 };
	QuickSort(a,0,sizeof(a) / sizeof(a[0]) -1);
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void HeapAdjust(int *a, int size, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child+1< size && a[child] < a[child + 1])
		{
			child++;
		}
		if (a[child] > a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}
void HeapSort(int* a,int size)
{
	for (int i = (size - 2) / 2; i >=0; i--)
	{
		HeapAdjust(a, size, i);
	}
	for (int i = 0; i < size; i++)
	{
		swap(a[0], a[size - i - 1]);
		HeapAdjust(a, size - i - 1, 0);
	}
}
void Test6()
{
	int a[10] = { 2, 7, 8, 1, 9, 4, 6, 0, 3, 5 };
	int size = sizeof(a) / sizeof(a[0]);
	
	HeapSort(a,size);

	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}