#include<iostream>
using namespace std;



//int main()
//{
//	union
//	{
//		int x;
//		char ch[2];
//	}a;
//	a.ch[0] = 0x39;
//	a.ch[1] = 0x38;
//	printf("%d\n", a.x);
//	system("pause");
//	return 0;           //�������У��𰸳���
//}
union
{
	int i;
	char a[2];
}u; 
int main()
{
	
	u.a[0] = 0x39;     //С��ģʽ   3     8     3     9    
	u.a[1] = 0x38;     //           0011  1000  0011  1001
	printf("i = %d\n", u.i);      //14393
	system("pause");
	return 0;
}



//bool check()
//{
//	union
//	{                   //�����壬�����洢��ַ������ͬ����ʼλ�ã�����i�Ĵ洢״̬����
//		int i;          //     0x 00 00 00 01             0x 00 00 00 00 01
//		char a;        //         ---->�ߵ�ַ                   �ߵ�ַ<----
//	}u;                //   a��i������ͬ�洢��ַ��������ʼ��ַ��ȥ������a����ȡ�� 0 Ҳ����ȡ�� 1
//	                   //  a���ȡ��0����˵��1�ڸߵ�ַ����ˣ���a���ȡ��1����˵��a�ڵ͵�ַ��С�ˣ�
//	u.i = 1;           //
//	printf("%d", u.a);
//	return 0;
//}
//int main()
//{
//	check();
//	system("pause");
//	return 0;
//}
