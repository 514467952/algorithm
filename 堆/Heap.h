#pragma once
#include"HeapArray.h"
#include<string.h>
//顺序表基础上又有部分规则
void AdjustUp(int array[], int size, int child);
typedef struct Heap
{
	int array[100];
	int size;

}Heap;

//初始化
void HeapInit(Heap *heap, int array[], int size){
	memcpy(heap->array, array, size*sizeof(int));
	heap->size = size;
	CreateHeap(heap->array, size);
}

//插入操作
void HeapPush(Heap *heap, int val){
	heap->array[heap->size++] = val;
	AdjustUp(heap->array, heap->size, heap->size - 1);
}

//删除
void HeapPop(Heap *heap)
{
	heap->array[0] = heap->array[heap->size - 1];
	AdjustDown(heap->array, heap->size - 1,0);
	heap->size--;
}


//向上调整
/*
array 数组
size 数组的长度
child 要向上调整的结点下标
*/

//小堆的情况
void AdjustUp(int array[], int size, int child)
{
	while (1)
	{
		//已经到堆顶位置
		if (child == 0)
		{
			return;
		}

		int parent = (child - 1) / 2;
		//父结点的值比孩子的值小的就不用调整
		if (array[parent] <= array[child]){
			return;
		}

		//交换
		int t = array[parent];
		array[parent] = array[child];
		array[child] = t;

		child = parent;
	}
}


//返回堆顶元素(返回最值)
int HeapTop(Heap *heap)
{
	return heap->array[0];
}

void Test()
{
	Heap heap;
	int array[] = { 15, 37, 2, 45, 63, 9, 18, 7, 16, 13 };
	int size = sizeof(array) / sizeof(int);
	HeapInit(&heap, array,size);
	PrintArray(heap.array, heap.size);

	HeapPush(&heap, 1);
	PrintArray(heap.array, heap.size);

}

//大堆的情况

void AdjustDown222(int array[], int size, int root)
{
	//判断 root 是否是叶子结点
	//因为 堆是完全二叉树，所以没有左孩子一定没有右孩子
	//又因为堆是顺序存储的
	//所以，找到左孩子的下标，如果左孩子的下标越界了，则没有左孩子
	while (1)
	{
		int left = 2 * root + 1;
		if (left >= size){
			//越界了，就是叶子结点
			return;
		}

		//走完上面一定有左孩子，判读是否有右孩子
		//找到左右孩子最小的一个
		int right = 2 * root + 2;
		int min = left;//最开始就认为最小的值为左孩子
		if (right < size && array[right] > array[left]){
			//没有越界,就有右孩子，如果右孩子的值小于左孩子的值
			min = right;
		}

		//比较array[min]  array[root]
		if (array[root] >= array[min]){
			return;
		}

		//调整,交换值
		int t = array[root];
		array[root] = array[min];
		array[min] = t;

		//需要继续向下调整，以min作为结点
		root = min;
	}
}
void AdjustUp222(int array[], int size, int child)
{
	while (1)
	{
		//已经到堆顶位置
		if (child == 0)
		{
			return;
		}

		int parent = (child - 1) / 2;
		//父结点的值比孩子的值小的就不用调整
		if (array[parent] >= array[child]){
			return;
		}

		//交换
		int t = array[parent];
		array[parent] = array[child];
		array[child] = t;

		child = parent;
	}
}

//堆排序
//升序，建大堆
//O(nlogn)
void HeapSort(int array[], int size)
{
	CreateHeap(array, size);
	//i 表示被找出的最大的数的个数
	for (int i = 0; i < size - 1; i++)
	{
		//每次循环，会找出最大的一个数放到最后

		int t = array[0];
		array[0] = array[size - i - 1];
		array[size - i - 1] = t;

		//进行向下调整，数据规模是size-1-i;
		AdjustDown222(array, size - 1 - i, 0);
	}
}

void TestHeapSort()
{
	int array[] = { 39, 129, 12, 38, 27, 9, 33, 2, 14 };
	int size = sizeof(array) / sizeof(int);

	HeapSort(array, size);

	PrintArray(array, size);
}


void BubbleSort(int array[], int size)
{
	for (int i = 0; i < size - 1; i++){
		int sorted = 1;
		for (int j = 0; j < size - 1 - i; j++){
			if (array[j]>array[j + 1]){
				int t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;

				sorted = 0;
			}
		}
		if (sorted == 1){
			break;
		}
	}
}

#define SIZE 50000

void TestSortSpeed(){
	srand(20190104);
	int array[SIZE] ;
	for (int i = 0; i < SIZE; i++){
		array[i] = rand() % 10 * 10000;
	}
	/*int s = time();
	HeapSort(array, SIZE);
	int e = time();
	printf("%d\n", e - s);*/

	int s = time();
	BubbleSort(array, SIZE);
	int e = time();
	printf("%d\n", e - s);

	
}

/*
类似伪代码，实际中，size是海量的，内存中放不下，需要借助文件操作
*/
void TopK(int array[], int size, int k){
	int *heap = (int *)malloc(sizeof(int)*k);
	for (int i = 0; i < k; i++){
		heap[i] = array[i];
	}

	//针对heap建小堆
	CreateHeap(heap, k);

	for (int j = k; j < size; j++){
		if (array[j]>heap[0]){
			heap[0] = array[j];
			AdjustDown(heap, k, 0);
		}
	}
}