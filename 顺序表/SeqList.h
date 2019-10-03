#pragma once
#include<stdbool.h>

typedef int SDataType;
/*
//��̬˳���
typedef struct SeqList{
	SDataType array[100]; //�ܴ�100�����ľ�̬˳���
	int size;      //���ǵ�ǰ˳������ж��ٸ�����˳��Ҳ��ʾ�˼���������±�
						
} SeqList;
*/

//��̬˳���
typedef struct SeqList{
	SDataType *array;		//ָ�϶��ϵĿռ�
	int size;      //���ǵ�ǰ˳������ж��ٸ�����˳��Ҳ��ʾ�˼���������±�

	int capacity;	//����
} SeqList;

//��ʼ��/����
//seqlist ��һ�������ĵ�ַ
//capacity ��ʾ˳��������
void SeqListInit(SeqList * seqlist,int capacity);
void SeqListDestroy(SeqList * seqlist);

//��ɾ�Ĳ�

//���� (ǰ���У���)
//β��
void SeqListPushBack(SeqList *seqlist, SDataType value);
//ͷ��
void SeqListPushFront(SeqList * seqlist, SDataType value);
//�м����
void SeqListInsert(SeqList *seqlsit, int pos, SDataType value);

//ɾ��
//βɾ
void SeqListPopBack(SeqList *seqlist);
//ͷɾ
void SeqListPopFront(SeqList *seqlist);
//ɾ��pos���ڵ��±������
void SeqListErase(SeqList *seqlist, int pos);

//��ӡ
void SeqListPrint(const SeqList *seqlist);
//�޸�pos�����±������Ϊvalue
void SeqListModify(SeqList *seqlist, int pos, SDataType value);
//����
int SeqListFind(const SeqList *seqlist, SDataType value);
//�ҵ���ɾ�������ĵ�һ��value
void SeqListRemove(SeqList *seqlist, SDataType value);
//�ж�˳����Ƿ�Ϊ��
bool SeqListEmpty(const SeqList *seqlist);
//�������ݸ���
int SeqListSize(const SeqList *seqlist);

//ð������
void SeqListBubbleSort(SeqList *seqlist);
//���ֲ���
int SeqListSort(const SeqList *seqlist, SDataType value);
//ɾ������������value
void SeqListRemoveAll(SeqList *seqlist, SDataType value);
