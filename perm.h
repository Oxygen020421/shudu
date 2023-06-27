#ifndef _PERM_H
#define _PERM_H

#include<cstdio>
#include<cstdlib>

void swap(int *a, int *b)//交换 
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void Reversal(int *a, int *b)//反转区间 
{
	while (a < b)
	{
		swap(a++, b--);
	}
}

int Perm(int *s_start, int *s_end)		//对从s_start到s_end进行全排列 
{
	int *p, *q, *s_find;
	p = s_end;

	while (p != s_start)  //排列未结束 
	{
		q = p;
		p--;

		if (*p < *q)             //找到相邻的，左邻小于右邻的地址 
		{
			s_find = s_end;

			while (*s_find <= *p) //从最右端开始找大于左邻小于右邻的值 的地址 
			{
				--s_find;
			}

			swap(p, s_find);       //替换 
			Reversal(q, s_end);   //反转 

			return 1;
		}
	}

	Reversal(p, s_end);  //如果没有下一个排列,全部反转后返回0
	return 0;
}

#endif
