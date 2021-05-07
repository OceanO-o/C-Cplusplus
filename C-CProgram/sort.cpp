void InsertSort(int* a, size_t size)
{
	assert(a);
	for (size_t j = 1; j < size; j++)
	{
		size_t i = 0;
		while (i < j && a[j] > a[i])
		{
			i++;    //就要把a[j]放入a[i]这个地方
		}           //出来以后就直接要在i这个地方把a[j]插进去
		int tmp = a[j];//保存着a[j]要把之前排好序的数向后移动，如果a[j]最大那么j = i，不用进下面for
		for (size_t index = j; index > i; index--)
		{
			a[index] = a[index - 1];
		}
		a[i] = tmp;

	}
}

void ShellSort(int* a, size_t size)
{
	assert(a);
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (size_t i = gap; i < size; ++i)
		{
			int index = i;
			int tmp = a[index];
			int end = index - gap;
			while (end >= 0 && tmp < a[end])
			{
				a[end + gap] = a[end];
				end -= gap;
			}
			a[end + gap] = tmp;
		}
	}
}