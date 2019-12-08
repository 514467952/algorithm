#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
#include<string>
void PrintArray(int array[], int size)
{
	for (int i = 0; i < size; ++i)
		printf("% d", array[i]);
	printf("\n");
}
//场景:数据密集集中在某个范围中
void CountSort(int*array, int size)
{
	int minVal = array[0];
	int maxVal = array[0];
	//1--找数据的范围
	for (int i = 1; i < size; ++i)
	{
		if (array[i] < minVal)
			minVal = array[i];
		if (array[i]>maxVal)
			maxVal = array[i];
	}
	//2--计算保存计数的空间
	int range = maxVal - minVal + 1;
	int *temp = (int*)malloc(sizeof(int)*range);
	if (NULL == temp)
	{
		assert(0);
		return;
	}
	//3---空间位置里全部置为0
	memset(temp, 0, sizeof(int)*range);
	//memeset 按一个一个字节赋值，赋值0可以，赋值其他值不行，例如100，给一个字节赋值100
	//4--统计每个数据出现的次数
	for (int i = 0; i < size; ++i)
	{
		temp[array[i] - minVal]++;
	}
	//5--回收数据
	int index = 0;
	for (int i = 0; i < range; ++i)
	{
		while (temp[i]--)  //当前元素值不为0，说明该下标还有个数	
		{
			array[index++] = i + minVal;
		}
	}
	free(temp);
}

void Test()
{
	int array[] = { 2, 0, 4, 9, 3, 6, 8, 7, 1, 5 };
	PrintArray(array, sizeof(array) / sizeof(array[0]));
	CountSort(array, sizeof(array) / sizeof(array[0]));
	PrintArray(array, sizeof(array) / sizeof(array[0]));
}