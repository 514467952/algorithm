#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
void PrintArray(int array[], int size)
{
	for (int i = 0; i < size; ++i)
		printf("% d", array[i]);
	printf("\n");
}

void InsertSort(int *array, int size)
{
	for (int i = 1; i < size; ++i)
	{
		int key = array[i];
		int end = i - 1; //iǰ����Ѿ��ź�����
		while (key < array[end] && end >= 0)
		{
			array[end + 1] = array[end];
			end--;
		}
		array[end + 1] = key;
	}
}

void ShellSort(int* array, int size)
{
	int gap = size;
	while (gap > 1) {
		gap = gap / 3 + 1;

		for (int i = gap; i < size; ++i)//iÿ�ؼ�1���÷���ͬʱ�������򣬲���Ҫ+gap
		{
			int key = array[i];
			int end = i - gap; //i��ǰһ��Ԫ��
			while (key < array[end] && end >= 0)
			{
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = key;
		}	
	}
}

void Swap(int *pLeft, int *pRight)
{
	int temp = *pLeft;
	*pLeft = *pRight;
	*pRight = temp;
}
//ֱ��ѡ������
void SelectSort(int*array, int size)
{
	
	for (int i = 0; i < size - 1; ++i)	//�ܹ��Ҷ��ٴ�,-1����Ϊ���һ�Σ�������ֻ��һ��Ԫ����
	{
		//�����������Ԫ�ص�λ��
		//�����Ԫ�صķ�ʽ
		int maxPos = 0;					//������Ԫ��
		for (int j = 1; j < size - i; ++j)	//-i����û�����������������Ԫ��
		{
			if (array[j]>array[maxPos])		//������±���
				maxPos = j;
		}
		if (maxPos != size - i - 1)		//������Ԫ���±겻���ڴ�ʱ��ǰû������������һ��Ԫ��
			Swap(&array[maxPos], &array[size - i - 1]);//���λ�õ�Ԫ�غ����λ�õ�Ԫ�ؽ���
	}
}

//ѡ�������Ż�
//һ������ʱ���ҳ���ǰ���䣬��ǰ���䣬��ǰ����������С��Ԫ�أ����Ԫ�غ͵�ǰ��������һ��Ԫ�ؽ���
//��СԪ�غ͵�ǰ�����һ��Ԫ�ؽ��н����������꣬������С���ظ�������ֱ������
void SelectSort_OP(int*array, int size)
{
	int begin = 0;
	int end = size - 1;
	while (begin < end){
		int maxPos = begin;//��Ϊ��ǰ�����һ��Ԫ�����
		int minPos = begin;//��Ϊ��ǰ�����һ��Ԫ����С
		int i = begin;//i�ӵ�ǰ�����һ��Ԫ�ؿ�ʼ

		//���������ҵ�������СԪ�ص�λ��
		while (i <= end)
		{
			if (array[i]>array[maxPos])
				maxPos = i;
			if (array[i] < array[minPos])
				minPos = i;
			i++;
		}
		//������СԪ�غ͵�ǰ�����һλ�ú����һλ�ý��н���
		if (maxPos != end)
			Swap(&array[maxPos], &array[end]);//���������±����ֵ���±겢û�иı�
		//�����ǰ��������Ԫ�طŵ����������ҵ���СԪ��,������СԪ�ص�λ��
		if (minPos == end)
			minPos = maxPos;
		if (minPos != 0)
			Swap(&array[minPos], &array[begin]);
		//��С����
		begin++;
		end--;
	}	
}
//O(logN)
void HeapAdjust(int*array, int size, int parent)
{
	int child = parent * 2 + 1; //����
	//int right = parent * 2 + 2;//�Һ���
	while (child<size)
	{
		//�����Һ���������
		if (child+1<size && array[child + 1] > array[child])
			child += 1;
		//���˫���Ƿ�����ѵ�����
		if (array[child] > array[parent]) //������
		{
			Swap(&array[child], &array[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}

//O(NlogN)
void HeapSort(int *array, int size)
{
	//����----����(���) ����(С��)
	//�ӵ�����һ����Ҷ�ӽ��----���µ���
	//size-1���������һ������parent=(child-1)/2��
	int last = ((size - 1 - 1) / 2);
	for (; last >= 0; last)
		HeapAdjust(array, size, last--);

	//����---�ѵ�ɾ��
	int end = size - 1; //ʣ�������Ԫ�ظ���
	while (end)
	{
		Swap(&array[0], &array[end]);
		HeapAdjust(array, end, 0);
		--end;
	}
}


void BublleSort(int*array, int size)
{	
	for (int i = 0; i < size - 1; ++i)       //�ܹ�ð�ݵ�����
	{
		int IsChange = 0;			//�鿴��һ����û�н���
		//ð�ݵķ�ʽ----->������Ԫ�ؽ��бȽ�
		for (int j = 0; j < size - i - 1; ++j)		//һ��ð��
		{
			if (array[j]>array[j + 1])
			{
				Swap(&array[j], &array[j + 1]);
				IsChange = 1;
			}	
		}
		if (!IsChange)  //���û�н���
			return;
	}
}
//����ȡ�з�
int GetMiddleIdx(int*array, int left, int right)
{
	int mid = left + ((right - left) >> 1);
	//left mid right-1
	if (array[left] < array[right - 1])
	{
		if (array[mid] < array[left])
			return left;
		else if (array[mid]>array[right - 1])
			return right - 1;
		else
			return mid;
	}
	else
	{
		if (array[mid] > array[left])
			return left;
		else if (array[mid] < array[right - 1])
			return right - 1;
		else
			return mid;
	}
}
int Partion(int*array, int left, int right)
{
	int middle = GetMiddleIdx(array, left, right);
	if (middle != right - 1)
		Swap(&array[middle], &array[right - 1]);

	int key = array[right - 1];
	int begin = left;
	int end = right - 1;
	while (begin<end)
	{
		//��ǰ�����ұȻ�׼ֵ���Ԫ�أ��ҵ���ͣ����,����Ҳ��ǰ�ߣ���Ϊ�ҵ��Ǵ��
		while (begin < end&&array[begin] <= key)
			begin++;
		//end�Ӻ���ǰ�ұȻ�׼ֵС��Ԫ�أ��ҵ���ͣ����������Ҳ��ǰ�ߣ��ҵ���С�ģ����ǵ���
		while (begin < end&&array[end] >= key)
			end--;
		if (begin < end)
			Swap(&array[begin], &array[end]);
	}
	if (begin != right - 1)
		Swap(&array[begin], &array[right - 1]);
	return begin;
}
//hoare����
int Partion1(int*array, int left, int right)
{
	int key = array[right - 1];
	int begin = left;
	int end = right - 1;
	while (begin<end)
	{
		//��ǰ�����ұȻ�׼ֵ���Ԫ�أ��ҵ���ͣ����,����Ҳ��ǰ�ߣ���Ϊ�ҵ��Ǵ��
		while (begin < end&&array[begin] <= key)
			begin++;
		//end�Ӻ���ǰ�ұȻ�׼ֵС��Ԫ�أ��ҵ���ͣ����������Ҳ��ǰ�ߣ��ҵ���С�ģ����ǵ���
		while (begin < end&&array[end] >= key)
			end--;
		if (begin < end)
			Swap(&array[begin], &array[end]);
	}
	if (begin != right - 1)
		Swap(&array[begin], &array[right-1]);
	return begin;
}

//�ڿӷ�
int Partion2(int*array, int left, int right)
{
	int key = array[right - 1];
	int begin = left;
	int end = right - 1;
	
	while (begin<end)
	{
		while (begin<end&&array[begin] <= key)
			begin++;
		if (begin<end)
		{
			//��һ������end��begin�ǱȻ�׼ֵ�����
			array[end] = array[begin];
			end--;
		}
		while (begin<end&&array[end] >= key)
			end--;
		if (begin<end)
		{
			//�ϴο���end����ӵ���begin������Ӻ�begin�ɿӣ�����end�Ȼ�׼ֵС��������
			array[begin] = array[end];
			begin++;
		}
	}
	array[begin] = key;
	return begin;
}

int Partion3(int*array, int left, int right)
{
	int key = array[right - 1];
	int cur = left;
	int pre = cur - 1;
	while (cur<right)
	{
		if (array[cur] < key && ++pre != cur)
			Swap(&array[cur], &array[pre]);
		cur++;
	}
	if (++pre != right - 1)
		Swap(&array[pre], &array[right - 1]);
	return pre;
}
void QuickSort(int *array, int left, int right)
{
	if (right - left < 16)
		//������ŵ�Ԫ�ظ���û�дﵽ16�������ϣ����ò�������
		InsertSort(array, right - left);
	else
	{
		int div = Partion(array, left, right);
		QuickSort(array, left, div);
		QuickSort(array, div + 1, right);
	}
}
#include"stack.h"

//���ŷǵݹ�
void QuickSortNor(int*array, int size)
{
	int left = 0;
	int right = size;
	
	Stack s;
	StackInit(&s);
	StackPush(&s,right);
	StackPush(&s,left); //���ȥ���ȳ������ȳ���������

	while (!StackEmpty(&s))
	{
		left = StackTop(&s);
		StackPop(&s);
		right = StackTop(&s);
		StackPop(&s);

		if (left < right)
		{
			int div = Partion3(array, left, right);
			//�ȱ����Ұ벿��,�Ƚ������
			StackPush(&s,right);//�Ұ벿���ұ߽�
			StackPush(&s, div + 1);//�Ұ벿����߽�
			//�ٱ�����߲��֣�����ȳ���
			StackPush(&s, div);//��벿���ұ߽�
			StackPush(&s, left);//��벿����߽�
		}
	}
	StackDestroy(&s);
}
//�鲢��temp��ʱ�ռ���
//�����������кϲ���һ��
void MergeData(int*array, int left, int mid, int right, int *temp)
{
	int begin1 = left, end1 = mid;
	int begin2 = mid, end2 = right;
	int index = left;
	while (begin1 < end1 && begin2 < end2)//��һ���͵ڶ����������Ԫ��û�д�����
	{
		if (array[begin1] < array[begin2])
			temp[index++] = array[begin1++];
		else
			temp[index++] = array[begin2++];
	}
	//�����һ���ռ������û�а�����
	while (begin1 < end1)
		temp[index++] = array[begin1++];
	//��һ���ռ�������ˣ��ڶ����ռ����Ԫ��û�а�����
	while (begin2 < end2)
		temp[index++] = array[begin2++];
}
#include<string>
void _MergeSort(int*array, int left, int right,int*temp)
{
	//int*temp=(int*)malloc(sizeof(array[left])*(right-left));
	if (right - left>1) //�������Ԫ�س���һ����������
	{
		//���м�λ��
		
		int mid = left + ((right - left) >> 1);
		_MergeSort(array, left, mid,temp);
		_MergeSort(array, mid, right,temp);
		MergeData(array, left, mid, right, temp);
		memcpy(array + left, temp + left, sizeof(array[left])*(right - left));
	}
}
void MergeSort(int *array, int size)
{
	int *temp = (int*)malloc(size*sizeof(array[0]));
	if (NULL == temp)
	{
		assert(0);
		return;
	}
	_MergeSort(array, 0, size, temp);
	free(temp);
}
void MergeSortNor(int *array, int size)
{
	int *temp = (int*)malloc(size*sizeof(array[0]));
	if (NULL == temp)
	{
		assert(0);
		return;
	}
	int gap = 1;
	while (gap < size)
	{
		for (int i = 0; i < size; i += 2 * gap)
		{
			int left = i;//��
			int mid = left + gap;//��
			int right = mid + gap;//��
			if (mid >= size)
				mid = size;
			if (right >= size)
				right = size;
			MergeData(array, left, mid, right, temp);
		}
		memcpy(array, temp, (sizeof(array[0])*size));
		gap *= 2;
	}
	free(temp);
}
void Test()
{
	//int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	int array[] = { 2, 0, 4, 9, 3, 6, 8, 7, 1, 5 };
	PrintArray(array, sizeof(array) / sizeof(array[0]));
	//InsertSort(array, sizeof(array) / sizeof(array[0]));
	//ShellSort(array, sizeof(array) / sizeof(array[0]));
	//SelectSort(array, sizeof(array) / sizeof(array[0]));
	//HeapSort(array, sizeof(array) / sizeof(array[0]));
	//BublleSort(array, sizeof(array) / sizeof(array[0]));
	//QuickSort(array, 0, sizeof(array) / sizeof(array[0]));
	//QuickSortNor(array,  sizeof(array) / sizeof(array[0]));
	//MergeSort(array, sizeof(array) / sizeof(array[0]));
	MergeSortNor(array, sizeof(array) / sizeof(array[0]));
	PrintArray(array, sizeof(array) / sizeof(array[0]));
}