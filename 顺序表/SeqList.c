#include"SeqList.h"
#include<assert.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>

//����Ƿ���Ҫ���ݣ������Ҫ���ݾͽ�������
//��֤��������������һ������
static void CheckCapacity(SeqList *seqlist)
{
	assert(seqlist != NULL);
	assert(seqlist->array != NULL);
	assert(seqlist->size <= seqlist->capacity);

	if (seqlist->size < seqlist->capacity){
		return;
	}

	//�ռ���������
	int capacity = 2 * seqlist->capacity;
	//�����¿ռ�
	SDataType *array = (SDataType *)malloc(sizeof(SDataType)*capacity);
	assert(array);

	//����
	for (int i = 0; i < seqlist->size; i++){
		array[i] = seqlist->array[i];
	}
	//�ͷ�ԭ�ռ�
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
//β��
void SeqListPushBack(SeqList *seqlist, SDataType value)
{
	assert(seqlist != NULL);
	assert(seqlist->array !=NULL);

	CheckCapacity(seqlist);

	seqlist->array[seqlist->size] = value;
	seqlist->size++;
}
//βɾ
void SeqListPopBack(SeqList *seqlist)
{
	assert(seqlist != NULL);
	assert(seqlist->array != NULL);
	assert(seqlist->size > 0); //����Ԫ�ظ�������0

	seqlist->size--;
}
//ͷ��
/*1. �Ӻ���ǰ�ᣬ���⸲��
  2. дѭ��
	 ��ȷ��ѭ���ı߽�
	 i �ռ��±� [size,0)
	 i �����±� [size -1,0]
  3. ����
	�ռ��±꣺array[i] = array[i-1];
	�����±꣺array[i+1] = array[i];
*/
void SeqListPushFront(SeqList * seqlist, SDataType value)
{
	assert(seqlist != NULL);
	assert(seqlist->array != NULL);

	CheckCapacity(seqlist);

	//�����ݵİ��ƣ�i����ռ��±�
	for (int i = seqlist->size; i > 0; i--){
		seqlist->array[i] = seqlist->array[i - 1];
	}
	seqlist->array[0] = value;
	seqlist->size++;
}
//ǰɾ
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

//�м��
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

//�м�ɾ
void SeqListErase(SeqList *seqlist, int pos){
	assert(seqlist!= NULL);
	assert(seqlist->array != NULL);
	assert(seqlist->size > 0);
	assert(pos >= 0 && pos < seqlist->size);
#if 0
	//i��������
	for (int i = pos; i < seqlist->size - 1; i++){
		seqlist->array[i] = seqlist->array[i + 1];
	}
#endif
	//i��������
	for (int i = pos + 1; i < seqlist->size ; i++){
		seqlist->array[i - 1] = seqlist->array[i];
	}

	seqlist->size--;
}

//��ӡ
void SeqListPrint(const SeqList *seqlist){
	for (int i = 0; i < seqlist->size; i++)
		printf("%d", seqlist->array[i]);

	printf("\n");
}
//�޸�pos�����±������Ϊvalue
void SeqListModify(SeqList *seqlist, int pos, SDataType value){
	assert(pos >= 0 && pos < seqlist->size);
	seqlist->array[pos] = value;
}
//����
//�ҵ������±�
//û�ҵ�����-1
int SeqListFind(const SeqList *seqlist, SDataType value){
	for (int i = 0; i < seqlist->size; i++){
		if (seqlist->array[i] == value){
			return i;
		}
	}
	return -1;
}
//�ҵ���ɾ�������ĵ�һ��value
void SeqListRemove(SeqList *seqlist, SDataType value){
	int pos = SeqListFind(seqlist, value);
	if (pos != -1){
		SeqListErase(seqlist, pos);
	}
}
//�ж�˳����Ƿ�Ϊ��
bool SeqListEmpty(const SeqList *seqlist){
	return seqlist->size == 0;
}
//�������ݸ���
int SeqListSize(const SeqList *seqlist){
	return seqlist->size;
}


void Swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

//ð������
void BubbleSort(int array[], int size)
{
	int isSorted; //������鱾�����򣬾Ϳ����Ż�
	for (int i = 0; i < size - 1; i++){
		isSorted = 1; //1��������

		//һ��ð�ݹ���
		//һ��ð�ݹ����У����û�н�����˵����������
		for (int j = 0; j < size - 1 - i; j++){
			if (array[j]>array[j + 1]){
				Swap(array + j, array + j + 1);
				//Swap(&array[i])
				isSorted = 0;
			}
		}

		//һ��ð�ݽ���
		if (isSorted == 1){
			break;
		}
	}
}



//ð������
void SeqListBubbleSort(SeqList *seqlist){

	BubbleSort(seqlist->array, seqlist->size);
}


//���ֲ���
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
	//����������
	SDataType *array = (SDataType *)malloc(sizeof(SDataType)* seqlist->size);
	assert(array);
	//���ȥ
	int index = 0;
	for (int i = 0; i < seqlist->size; i++){
		if (seqlist->array[i] != value){
			array[index] = seqlist->array[i];
			index++;
		}
	}
	//���ȥ
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