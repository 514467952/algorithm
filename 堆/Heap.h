#pragma once
#include"HeapArray.h"
#include<string.h>
//˳�����������в��ֹ���
void AdjustUp(int array[], int size, int child);
typedef struct Heap
{
	int array[100];
	int size;

}Heap;

//��ʼ��
void HeapInit(Heap *heap, int array[], int size){
	memcpy(heap->array, array, size*sizeof(int));
	heap->size = size;
	CreateHeap(heap->array, size);
}

//�������
void HeapPush(Heap *heap, int val){
	heap->array[heap->size++] = val;
	AdjustUp(heap->array, heap->size, heap->size - 1);
}

//ɾ��
void HeapPop(Heap *heap)
{
	heap->array[0] = heap->array[heap->size - 1];
	AdjustDown(heap->array, heap->size - 1,0);
	heap->size--;
}


//���ϵ���
/*
array ����
size ����ĳ���
child Ҫ���ϵ����Ľ���±�
*/

//С�ѵ����
void AdjustUp(int array[], int size, int child)
{
	while (1)
	{
		//�Ѿ����Ѷ�λ��
		if (child == 0)
		{
			return;
		}

		int parent = (child - 1) / 2;
		//������ֵ�Ⱥ��ӵ�ֵС�ľͲ��õ���
		if (array[parent] <= array[child]){
			return;
		}

		//����
		int t = array[parent];
		array[parent] = array[child];
		array[child] = t;

		child = parent;
	}
}


//���ضѶ�Ԫ��(������ֵ)
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

//��ѵ����

void AdjustDown222(int array[], int size, int root)
{
	//�ж� root �Ƿ���Ҷ�ӽ��
	//��Ϊ ������ȫ������������û������һ��û���Һ���
	//����Ϊ����˳��洢��
	//���ԣ��ҵ����ӵ��±꣬������ӵ��±�Խ���ˣ���û������
	while (1)
	{
		int left = 2 * root + 1;
		if (left >= size){
			//Խ���ˣ�����Ҷ�ӽ��
			return;
		}

		//��������һ�������ӣ��ж��Ƿ����Һ���
		//�ҵ����Һ�����С��һ��
		int right = 2 * root + 2;
		int min = left;//�ʼ����Ϊ��С��ֵΪ����
		if (right < size && array[right] > array[left]){
			//û��Խ��,�����Һ��ӣ�����Һ��ӵ�ֵС�����ӵ�ֵ
			min = right;
		}

		//�Ƚ�array[min]  array[root]
		if (array[root] >= array[min]){
			return;
		}

		//����,����ֵ
		int t = array[root];
		array[root] = array[min];
		array[min] = t;

		//��Ҫ�������µ�������min��Ϊ���
		root = min;
	}
}
void AdjustUp222(int array[], int size, int child)
{
	while (1)
	{
		//�Ѿ����Ѷ�λ��
		if (child == 0)
		{
			return;
		}

		int parent = (child - 1) / 2;
		//������ֵ�Ⱥ��ӵ�ֵС�ľͲ��õ���
		if (array[parent] >= array[child]){
			return;
		}

		//����
		int t = array[parent];
		array[parent] = array[child];
		array[child] = t;

		child = parent;
	}
}

//������
//���򣬽����
//O(nlogn)
void HeapSort(int array[], int size)
{
	CreateHeap(array, size);
	//i ��ʾ���ҳ����������ĸ���
	for (int i = 0; i < size - 1; i++)
	{
		//ÿ��ѭ�������ҳ�����һ�����ŵ����

		int t = array[0];
		array[0] = array[size - i - 1];
		array[size - i - 1] = t;

		//�������µ��������ݹ�ģ��size-1-i;
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
����α���룬ʵ���У�size�Ǻ����ģ��ڴ��зŲ��£���Ҫ�����ļ�����
*/
void TopK(int array[], int size, int k){
	int *heap = (int *)malloc(sizeof(int)*k);
	for (int i = 0; i < k; i++){
		heap[i] = array[i];
	}

	//���heap��С��
	CreateHeap(heap, k);

	for (int j = k; j < size; j++){
		if (array[j]>heap[0]){
			heap[0] = array[j];
			AdjustDown(heap, k, 0);
		}
	}
}