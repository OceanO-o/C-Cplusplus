void InsertSort(int* a, size_t size)
{
	assert(a);
	for (size_t j = 1; j < size; j++)
	{
		size_t i = 0;
		while (i < j && a[j] > a[i])
		{
			i++;    //��Ҫ��a[j]����a[i]����ط�
		}           //�����Ժ��ֱ��Ҫ��i����ط���a[j]���ȥ
		int tmp = a[j];//������a[j]Ҫ��֮ǰ�ź����������ƶ������a[j]�����ôj = i�����ý�����for
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