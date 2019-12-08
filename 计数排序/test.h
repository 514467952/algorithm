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
//����:�����ܼ�������ĳ����Χ��
void CountSort(int*array, int size)
{
	int minVal = array[0];
	int maxVal = array[0];
	//1--�����ݵķ�Χ
	for (int i = 1; i < size; ++i)
	{
		if (array[i] < minVal)
			minVal = array[i];
		if (array[i]>maxVal)
			maxVal = array[i];
	}
	//2--���㱣������Ŀռ�
	int range = maxVal - minVal + 1;
	int *temp = (int*)malloc(sizeof(int)*range);
	if (NULL == temp)
	{
		assert(0);
		return;
	}
	//3---�ռ�λ����ȫ����Ϊ0
	memset(temp, 0, sizeof(int)*range);
	//memeset ��һ��һ���ֽڸ�ֵ����ֵ0���ԣ���ֵ����ֵ���У�����100����һ���ֽڸ�ֵ100
	//4--ͳ��ÿ�����ݳ��ֵĴ���
	for (int i = 0; i < size; ++i)
	{
		temp[array[i] - minVal]++;
	}
	//5--��������
	int index = 0;
	for (int i = 0; i < range; ++i)
	{
		while (temp[i]--)  //��ǰԪ��ֵ��Ϊ0��˵�����±껹�и���	
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