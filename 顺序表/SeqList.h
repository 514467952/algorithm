#pragma once
#include<stdbool.h>

typedef int SDataType;
/*
//静态顺序表
typedef struct SeqList{
	SDataType array[100]; //能存100个数的静态顺序表
	int size;      //表是当前顺序表中有多少个数，顺便也表示了即将插入的下标
						
} SeqList;
*/

//动态顺序表
typedef struct SeqList{
	SDataType *array;		//指上堆上的空间
	int size;      //表是当前顺序表中有多少个数，顺便也表示了即将插入的下标

	int capacity;	//容量
} SeqList;

//初始化/销毁
//seqlist 是一个变量的地址
//capacity 表示顺序表的容量
void SeqListInit(SeqList * seqlist,int capacity);
void SeqListDestroy(SeqList * seqlist);

//增删改查

//插入 (前，中，后)
//尾插
void SeqListPushBack(SeqList *seqlist, SDataType value);
//头插
void SeqListPushFront(SeqList * seqlist, SDataType value);
//中间插入
void SeqListInsert(SeqList *seqlsit, int pos, SDataType value);

//删除
//尾删
void SeqListPopBack(SeqList *seqlist);
//头删
void SeqListPopFront(SeqList *seqlist);
//删除pos所在的下标的数据
void SeqListErase(SeqList *seqlist, int pos);

//打印
void SeqListPrint(const SeqList *seqlist);
//修改pos所在下标的数据为value
void SeqListModify(SeqList *seqlist, int pos, SDataType value);
//查找
int SeqListFind(const SeqList *seqlist, SDataType value);
//找到并删除遇到的第一个value
void SeqListRemove(SeqList *seqlist, SDataType value);
//判断顺序表是否为空
bool SeqListEmpty(const SeqList *seqlist);
//返回数据个数
int SeqListSize(const SeqList *seqlist);

//冒泡排序
void SeqListBubbleSort(SeqList *seqlist);
//二分查找
int SeqListSort(const SeqList *seqlist, SDataType value);
//删除遇到的所有value
void SeqListRemoveAll(SeqList *seqlist, SDataType value);
