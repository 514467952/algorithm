#include"SeqList.h"
#include<assert.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>

//检查是否需要扩容，如果需要扩容就进行扩容
//保证函数结束后，容量一定够用
static void CheckCapacity(SeqList *seqlist)
{
	assert(seqlist != NULL);
	assert(seqlist->array != NULL);
	assert(seqlist->size <= seqlist->capacity);

	if (seqlist->size < seqlist->capacity){
		return;
	}

	//空间扩大两倍
	int capacity = 2 * seqlist->capacity;
	//申请新空间
	SDataType *array = (SDataType *)malloc(sizeof(SDataType)*capacity);
	assert(array);

	//搬移
	for (int i = 0; i < seqlist->size; i++){
		array[i] = seqlist->array[i];
	}
	//释放原空间
	free(seqlist->array);
	seqlist->array = array;
}

void SeqListInit(SeqList * seqlist, int capacity)
{
	assert(seqlist != NULL);

	seqlist->array = (SDataType*)malloc(sizeof(SDataType)* capacity);
	assert(seqlist->array);
	
	seqlist->size = 0;
	seqlist->capacity = capacity;
}

void SeqListDestroy(SeqList * seqlist)
{
	assert(seqlist != NULL);
	assert(seqlist->array != NULL);

	free(seqlist->array);

	seqlist->array = NULL;
	seqlist->size = 0;
	seqlist->capacity = 0;
}
//尾插
void SeqListPushBack(SeqList *seqlist, SDataType value)
{
	assert(seqlist != NULL);
	assert(seqlist->array !=NULL);

	CheckCapacity(seqlist);

	seqlist->array[seqlist->size] = value;
	seqlist->size++;
}
//尾删
void SeqListPopBack(SeqList *seqlist)
{
	assert(seqlist != NULL);
	assert(seqlist->array != NULL);
	assert(seqlist->size > 0); //数据元素个数大于0

	seqlist->size--;
}
//头插
/*1. 从后往前搬，避免覆盖
  2. 写循环
	 先确定循环的边界
	 i 空间下表 [size,0)
	 i 数据下标 [size -1,0]
  3. 搬移
	空间下标：array[i] = array[i-1];
	数据下标：array[i+1] = array[i];
*/
void SeqListPushFront(SeqList * seqlist, SDataType value)
{
	assert(seqlist != NULL);
	assert(seqlist->array != NULL);

	CheckCapacity(seqlist);

	//做数据的搬移，i代表空间下标
	for (int i = seqlist->size; i > 0; i--){
		seqlist->array[i] = seqlist->array[i - 1];
	}
	seqlist->array[0] = value;
	seqlist->size++;
}
//前删
void SeqListPopFront(SeqList *seqlist){
	assert(seqlist != NULL);
	assert(seqlist->array != NULL);
	assert(seqlist->size > 0);

#if 0
	for (int i = 0; i < seqlist->size; i++)
	{
		seqlist->array[i] = seqlist->array[i + 1];
	}
#endif
	for (int i = 1; i < seqlist->size; i++)
	{
		seqlist->array[i - 1] = seqlist->array[i];
	}
	seqlist->size--;
}

//中间插
void SeqListInsert(SeqList *seqlist, int pos, SDataType value){
	assert(seqlist != NULL);
	assert(seqlist->array != NULL);
	assert(pos >= 0 && pos <= seqlist->size);

	CheckCapacity(seqlist);

	for (int i = seqlist->size - 1; i >= pos; i--){
		seqlist->array[i + 1] = seqlist->array[i];
	}

	seqlist->array[pos] = value;
}

//中间删
void SeqListErase(SeqList *seqlist, int pos){
	assert(seqlist!= NULL);
	assert(seqlist->array != NULL);
	assert(seqlist->size > 0);
	assert(pos >= 0 && pos < seqlist->size);
#if 0
	//i代表数据
	for (int i = pos; i < seqlist->size - 1; i++){
		seqlist->array[i] = seqlist->array[i + 1];
	}
#endif
	//i代表数据
	for (int i = pos + 1; i < seqlist->size ; i++){
		seqlist->array[i - 1] = seqlist->array[i];
	}

	seqlist->size--;
}

//打印
void SeqListPrint(const SeqList *seqlist){
	for (int i = 0; i < seqlist->size; i++)
		printf("%d", seqlist->array[i]);

	printf("\n");
}
//修改pos所在下标的数据为value
void SeqListModify(SeqList *seqlist, int pos, SDataType value){
	assert(pos >= 0 && pos < seqlist->size);
	seqlist->array[pos] = value;
}
//查找
//找到返回下标
//没找到返回-1
int SeqListFind(const SeqList *seqlist, SDataType value){
	for (int i = 0; i < seqlist->size; i++){
		if (seqlist->array[i] == value){
			return i;
		}
	}
	return -1;
}
//找到并删除遇到的第一个value
void SeqListRemove(SeqList *seqlist, SDataType value){
	int pos = SeqListFind(seqlist, value);
	if (pos != -1){
		SeqListErase(seqlist, pos);
	}
}
//判断顺序表是否为空
bool SeqListEmpty(const SeqList *seqlist){
	return seqlist->size == 0;
}
//返回数据个数
int SeqListSize(const SeqList *seqlist){
	return seqlist->size;
}


void Swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

//冒泡排序
void BubbleSort(int array[], int size)
{
	int isSorted; //如果数组本身有序，就可以优化
	for (int i = 0; i < size - 1; i++){
		isSorted = 1; //1代表有序

		//一次冒泡过程
		//一次冒泡过程中，如果没有交换就说明本身有序
		for (int j = 0; j < size - 1 - i; j++){
			if (array[j]>array[j + 1]){
				Swap(array + j, array + j + 1);
				//Swap(&array[i])
				isSorted = 0;
			}
		}

		//一次冒泡结束
		if (isSorted == 1){
			break;
		}
	}
}



//冒泡排序
void SeqListBubbleSort(SeqList *seqlist){

	BubbleSort(seqlist->array, seqlist->size);
}


//二分查找
int SeqListSort(const SeqList *seqlist, SDataType value)
{
	int left = 0;
	int right = seqlist->size;
	while (left < right){
		int mid = (right - left) / 2 + left;
		if (value == seqlist->array[mid]){
			return mid;
		}
		else if (value < seqlist->array[mid]){
			right = mid;
		}
		else{
			left = mid + 1;
		}
	}
	return -1;
}

void SeqListRemoveAll(SeqList *seqlist, SDataType value){
#if 0 //O(N*2) O(1)
	int pos;
	while ((pos = SeqListFind(seqlist, value)) != -1){
		SeqListErase(seqlist, pos);
	}
#endif

#if 0 //O(N) O(N)
	//开辟新数组
	SDataType *array = (SDataType *)malloc(sizeof(SDataType)* seqlist->size);
	assert(array);
	//搬出去
	int index = 0;
	for (int i = 0; i < seqlist->size; i++){
		if (seqlist->array[i] != value){
			array[index] = seqlist->array[i];
			index++;
		}
	}
	//搬回去
	for (int j = 0; j < index; j++){
		seqlist->array[j] = array[j];
	}
	seqlist->size = index;
#endif

	int index = 0;
	for (int i = 0; i < seqlist->size; i++){
		if (seqlist->array[i] != value){
			seqlist->array[index] = seqlist->array[i];
			index++;
		}
	}
	seqlist->size = index;
}