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
		int end = i - 1; //i前面的已经排好序了
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

		for (int i = gap; i < size; ++i)//i每回加1，让分组同时进行排序，不需要+gap
		{
			int key = array[i];
			int end = i - gap; //i的前一个元素
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
//直接选择排序
void SelectSort(int*array, int size)
{
	
	for (int i = 0; i < size - 1; ++i)	//总共找多少次,-1是因为最后一次，区间中只有一个元素了
	{
		//找区间中最大元素的位置
		//找最大元素的方式
		int maxPos = 0;					//找最大的元素
		for (int j = 1; j < size - i; ++j)	//-i，从没排序的序列中找最大的元素
		{
			if (array[j]>array[maxPos])		//如果大，下标变更
				maxPos = j;
		}
		if (maxPos != size - i - 1)		//如果最大元素下标不等于此时当前没排序区间的最后一个元素
			Swap(&array[maxPos], &array[size - i - 1]);//最大位置的元素和最后位置的元素交换
	}
}

//选择排序优化
//一次排序时，找出当前区间，当前区间，当前区间最大和最小的元素，最大元素和当前区间的最后一个元素交换
//最小元素和当前区间第一个元素进行交换，交换完，区间缩小，重复操作，直到有序
void SelectSort_OP(int*array, int size)
{
	int begin = 0;
	int end = size - 1;
	while (begin < end){
		int maxPos = begin;//认为当前区间第一个元素最大
		int minPos = begin;//认为当前区间第一个元素最小
		int i = begin;//i从当前区间第一个元素开始

		//在区间中找到最大和最小元素的位置
		while (i <= end)
		{
			if (array[i]>array[maxPos])
				maxPos = i;
			if (array[i] < array[minPos])
				minPos = i;
			i++;
		}
		//最大和最小元素和当前区间第一位置和最后一位置进行交换
		if (maxPos != end)
			Swap(&array[maxPos], &array[end]);//交换的是下标里的值，下标并没有改变
		//如果当前区间最后的元素放的正好是你找到最小元素,更新最小元素的位置
		if (minPos == end)
			minPos = maxPos;
		if (minPos != 0)
			Swap(&array[minPos], &array[begin]);
		//缩小区间
		begin++;
		end--;
	}	
}
//O(logN)
void HeapAdjust(int*array, int size, int parent)
{
	int child = parent * 2 + 1; //左孩子
	//int right = parent * 2 + 2;//右孩子
	while (child<size)
	{
		//找左右孩子中最大的
		if (child+1<size && array[child + 1] > array[child])
			child += 1;
		//检测双亲是否满足堆的性质
		if (array[child] > array[parent]) //不满足
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
	//建堆----升序(大堆) 降序(小堆)
	//从倒数第一个非叶子结点----向下调整
	//size-1数组中最后一个数，parent=(child-1)/2；
	int last = ((size - 1 - 1) / 2);
	for (; last >= 0; last)
		HeapAdjust(array, size, last--);

	//排序---堆的删除
	int end = size - 1; //剩余排序的元素个数
	while (end)
	{
		Swap(&array[0], &array[end]);
		HeapAdjust(array, end, 0);
		--end;
	}
}


void BublleSort(int*array, int size)
{	
	for (int i = 0; i < size - 1; ++i)       //总共冒泡的趟数
	{
		int IsChange = 0;			//查看这一趟有没有交换
		//冒泡的方式----->用相邻元素进行比较
		for (int j = 0; j < size - i - 1; ++j)		//一次冒泡
		{
			if (array[j]>array[j + 1])
			{
				Swap(&array[j], &array[j + 1]);
				IsChange = 1;
			}	
		}
		if (!IsChange)  //如果没有交换
			return;
	}
}
//三数取中法
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
		//从前往后找比基准值大的元素，找到就停下来,等于也往前走，因为找的是大的
		while (begin < end&&array[begin] <= key)
			begin++;
		//end从后往前找比基准值小的元素，找到就停下来，等于也往前走，找的是小的，不是等于
		while (begin < end&&array[end] >= key)
			end--;
		if (begin < end)
			Swap(&array[begin], &array[end]);
	}
	if (begin != right - 1)
		Swap(&array[begin], &array[right - 1]);
	return begin;
}
//hoare方法
int Partion1(int*array, int left, int right)
{
	int key = array[right - 1];
	int begin = left;
	int end = right - 1;
	while (begin<end)
	{
		//从前往后找比基准值大的元素，找到就停下来,等于也往前走，因为找的是大的
		while (begin < end&&array[begin] <= key)
			begin++;
		//end从后往前找比基准值小的元素，找到就停下来，等于也往前走，找的是小的，不是等于
		while (begin < end&&array[end] >= key)
			end--;
		if (begin < end)
			Swap(&array[begin], &array[end]);
	}
	if (begin != right - 1)
		Swap(&array[begin], &array[right-1]);
	return begin;
}

//挖坑法
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
			//上一个坑是end，begin是比基准值大的数
			array[end] = array[begin];
			end--;
		}
		while (begin<end&&array[end] >= key)
			end--;
		if (begin<end)
		{
			//上次坑是end，填坑的是begin，填完坑后，begin成坑，由新end比基准值小的数来填
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
		//如果快排的元素个数没有达到16及其以上，就用插入排序
		InsertSort(array, right - left);
	else
	{
		int div = Partion(array, left, right);
		QuickSort(array, left, div);
		QuickSort(array, div + 1, right);
	}
}
#include"stack.h"

//快排非递归
void QuickSortNor(int*array, int size)
{
	int left = 0;
	int right = size;
	
	Stack s;
	StackInit(&s);
	StackPush(&s,right);
	StackPush(&s,left); //后进去的先出来，先出来的是左

	while (!StackEmpty(&s))
	{
		left = StackTop(&s);
		StackPop(&s);
		right = StackTop(&s);
		StackPop(&s);

		if (left < right)
		{
			int div = Partion3(array, left, right);
			//先保存右半部分,先进后出来
			StackPush(&s,right);//右半部分右边界
			StackPush(&s, div + 1);//右半部分左边界
			//再保存左边部分，后进先出来
			StackPush(&s, div);//左半部分右边界
			StackPush(&s, left);//左半部分左边界
		}
	}
	StackDestroy(&s);
}
//归并到temp临时空间里
//两个有序序列合并成一个
void MergeData(int*array, int left, int mid, int right, int *temp)
{
	int begin1 = left, end1 = mid;
	int begin2 = mid, end2 = right;
	int index = left;
	while (begin1 < end1 && begin2 < end2)//第一个和第二个区间里的元素没有处理完
	{
		if (array[begin1] < array[begin2])
			temp[index++] = array[begin1++];
		else
			temp[index++] = array[begin2++];
	}
	//如果第一个空间里的数没有搬移完
	while (begin1 < end1)
		temp[index++] = array[begin1++];
	//第一个空间搬移完了，第二个空间里的元素没有搬移完
	while (begin2 < end2)
		temp[index++] = array[begin2++];
}
#include<string>
void _MergeSort(int*array, int left, int right,int*temp)
{
	//int*temp=(int*)malloc(sizeof(array[left])*(right-left));
	if (right - left>1) //区间里的元素超过一个，再排序
	{
		//找中间位置
		
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
			int left = i;//左
			int mid = left + gap;//中
			int right = mid + gap;//右
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