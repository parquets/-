#pragma once

#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/*
	Data:2018/8/20
	Auther: �׽�
	Description:���ݽṹ�����½ڸ�ϰ������sort������������ʵ�֣���������Ǵ�С����
	��������˵����void SortFuncName(DataType* ArrData, int Left, int Right)
				ArrData:������������
				Left��������ʼ��λ��
				Right��������ֹλ��+1
	Reference�����ݽṹ-�����������ݽṹ���㷨����-Mark Allen Weiss
*/

/* ð������ ʱ�临�Ӷ�ΪO(n^2), ��һ�ֽ������� */
template <typename DataType>
void bubble_sort(DataType* ArrData, int Left, int Right);

/* �������� ʱ�临�Ӷ�ΪO(n^2) */
template <typename DataType>
void insert_sort(DataType* ArrData, int Left, int Right);

/* ѡ������ʱ�临�Ӷ�ΪO(n^2) */
template <typename DataType>
void select_sort(DataType* ArrData, int Left, int Right);

/* ��������, ʱ�临�Ӷ�ΪO(nlogn)
	���裺1���ֽ⣺��ArrData[p]Ϊ��׼Ԫ�أ�������ArrData[Left:Right-1]��Ϊ�������֣�ArrData[p:q-1],ArrData[q],ArrData[q+1:Right-1]
				ʹ��ArrData[p:q-1]�����һԪ��С��ArrData[q],ArrData[q+1:Right-1]����һԪ�ش���ArrData[q];
		 2���ݹ���⣺�ֱ��ArrData[p:q-1]��ArrData[q+1,Right-1]��Ԫ�ؽ��п�������
		 3���ϲ�
	�ǲ��ȶ������� */
template <typename DataType>
void quick_sort(DataType* ArrData, int Left, int Right);

/* �������� ʱ�临�Ӷȣ�O(nlogn)
	˼�룺��nΪ1ʱֹͣ���򣬷��򽫴�����Ԫ�طֳɴ�С������ͬ�������Ӽ����ֱ���������Ӽ��������� */
template <typename DataType>
void merge_sort(DataType* ArrData, int Left, int Right);

template <typename DataType>
void merge_sort_loop(DataType* ArrData, int Left, int Right);

/* Ѱ�Ҵ�С�������еĵ�K����Ԫ�� ������ʱ�� */
template <typename DataType>
int selectKMin(DataType* ArrData, int Left, int Right, int k);

template <typename DataType>
int partition(DataType* ArrData, int Left, int Right, int privotIndex);

template <typename DataType>
int partition(DataType* ArrData, int Left, int Right, int privotIndex)
{
	/* ���֣�������С��ArrData[privotInedx]��ֵ����������ߣ����������ұ� */
	Right -= 1;
	int privotVal = ArrData[privotIndex];
	int storeIndex = Left;
	DataType Tmp;

	Tmp = ArrData[privotIndex];
	ArrData[privotIndex] = ArrData[Left];
	ArrData[Left] = Tmp;

	int i = Left + 1, j = Right;
	while (i < j)
	{
		while (ArrData[i] < privotVal && i<j) ++i;
		while (ArrData[j] > privotVal) --j;

		if (i >= j) break;

		Tmp = ArrData[i];
		ArrData[i] = ArrData[j];
		ArrData[j] = Tmp;
	}
	
	Tmp = ArrData[j];
	ArrData[j] = ArrData[storeIndex];
	ArrData[storeIndex] = Tmp;

	storeIndex = j;

	printf("Left = %d  Right = %d  privotVal = %d  storeIndex = %d\n", Left, Right, privotVal, storeIndex);
	for (int i = Left; i <= Right; i++) printf("%d ", ArrData[i]);
	printf("\n");

	return storeIndex;
}




template <typename DataType>
void bubble_sort(DataType* ArrData, int Left, int Right)
{
	DataType tmp;
	bool is_sorted = true;		// ð�ݵ��Ż����ж��Ƿ�����������ǣ������
	for (int i = Left; i < Right; ++i)
	{
		for (int j = i + 1; j < Right; ++j)
		{
			if (ArrData[i] > ArrData[j])
			{
				true = false;	//��������˽�������������Ϊ������
				tmp = ArrData[i];
				ArrData[i] = ArrData[j];
				ArrData[j] = tmp;
			}
		}
		if (is_sorted == true) break;	//��������ѭ��
	}
}

template <typename DataType>
void insert_sort(DataType* ArrData, int Left, int Right)
{
	DataType tmp;
	int i, j;
	for (i = Left; i < Right; ++i)
	{
		int tmp = ArrData[i];
		for (j = i - 1; j >= Left && ArrData[j] > tmp; --j)
			ArrData[j + 1] = ArrData[j];
		ArrData[j + 1] = tmp;
	}
}

template <typename DataType>
void select_sort(DataType* ArrData, int Left, int Right)
{
	int i, j;
	int min_in;
	DataType min_val;
	bool is_sorted = true;	//�ж��Ƿ�����
	for (i = Left; i < Right; ++i)
	{
		min_val = ArrData[i];
		min_in = i;
		for (j = i + 1; j < Right; ++j)
		{
			if (ArrData[j] < min_val)
			{
				min_in = j;
				min_val = ArrData[j];
			}
			if (ArrData[j] < ArrData[j - 1]) is_sorted = false;	//�������ArrData[j]<ArrData[j-1],���ʾ����������
		}
		if (is_sorted == true) break; // �������Ѿ�����������ѭ����
		ArrData[min_in] = ArrData[i];
		ArrData[i] = min_val;
	}
}

template <typename DataType>
void quick_sort(DataType* ArrData, int Left, int Right)
{
	int key_pos;
	int key_val;
	int i = Left, j = Right;
	DataType tmp;
	if (Left < Right)
	{
		key_pos = Left;	/* ���������ڱ�Ԫ�ص�λ�ã��ڱ��ڵ�����Ԫ��С���ڱ�Ԫ�أ��Ҳ���ڣ�����key_posʱҪ�͵�һ��Ԫ�ؽ���*/
		key_val = ArrData[key_pos];
		while (true)
		{
			while (ArrData[++i] < key_val && i < Right - 1);	//Ѱ�ҵ�һ��Ԫ��ֵ����key_val��λ��
			while (ArrData[--j] > key_val);	//Ѱ�ҵ�һ��Ԫ��ֵС��key_val��λ��
			if (i >= j) break;
			/* ����ArrData[i]��ArrData[j] */
			tmp = ArrData[i];			
			ArrData[i] = ArrData[j];
			ArrData[j] = tmp;
		}
		tmp = ArrData[Left];
		ArrData[Left] = ArrData[j];
		ArrData[j] = tmp;

		quick_sort(ArrData, Left, j);
		quick_sort(ArrData, j + 1, Right);
	}
}

template <typename DataType>
void merge(DataType* ArrData, DataType* TmpArr, int LeftPos, int RightPos, int RightEnd)
{
	/* ���麯������������õ������ֵĺϲ�
       ����˵���� LeftPos  ��ʾ��벿��ʼ��λ��
				RightPos ��ʾ�Ұ벿��ʼ��λ��
				RightEnd ��벿�ֽ�����λ��
	*/
	int i, //ѭ������
		LeftEnd = RightPos - 1,	//LeftEnd��ʾ������������λ��
		TmpPos = LeftPos,		//��TmpArr�в���Ԫ������Ҫ���±�
		ElemNum = RightEnd - LeftPos + 1;

	/* ѭ�����ںϲ��������� */
	while (LeftPos <= LeftEnd && RightPos <= RightEnd)
	{
		/* �������ߵ�����С������ߵ����ݼ��뵽TmpArr�У�����λ������1���ұ����� */
		if (ArrData[LeftPos] <= ArrData[RightPos]) 
			TmpArr[TmpPos++] = ArrData[LeftPos++];
		else 
			TmpArr[TmpPos++] = ArrData[RightPos++];
	}
	/* ��ʣ�������Ҳ���뵽TmpArr��ȥ*/
	while (LeftPos <= LeftEnd)
		TmpArr[TmpPos++] = ArrData[LeftPos++];
	while (RightPos <= RightEnd)
		TmpArr[TmpPos++] = ArrData[RightPos++];

	/* ��TmpArr�еĽ�����ƻ�ArrData��*/
	for (i = 0; i < ElemNum; i++, RightEnd--)
		ArrData[RightEnd] = TmpArr[RightEnd];
}

template <typename DataType>
void msort(DataType* ArrData, DataType* TmpArr, int Left, int Right)
{
	int center;
	if (Left < Right)
	{
		center = (Left + Right) / 2;		
		/*center�������Ϊ�����������֣� �������������ֱַ������� */
		msort(ArrData, TmpArr, Left, center);
		msort(ArrData, TmpArr, center + 1, Right);
		//�ϲ�����
		merge(ArrData, TmpArr, Left, center + 1, Right);
	}
}

template <typename DataType>
void merge_sort(DataType* ArrData, int Left, int Right)
{
	int arr_size = Right - Left;
	DataType* TmpArr = new DataType[arr_size];
	if (Left < Right)
		msort(ArrData, TmpArr, Left, Right - 1);
}


template <typename DataType>
int selectKMin(DataType* ArrData, int Left, int Right, int k)
{
	int nret;

	/* ������ŦԪΪArrData[Left+1] */
	int privotIndex = Left + 1;

	/* ��Ը���ŦԪ����һ�λ��֣�С����ŦԪ��Ԫ������ŦԪ��ߣ��������ұ� */
	nret = partition(ArrData, Left, Right, privotIndex);

	/* �����ŦԪ��Ӧ��Index����k��������ҵĵ�k��Ԫ����Index����� */
	if (nret > k) return selectKMin(ArrData, Left, nret, k);
	
	/* ��֮�������ŦԪ��Ӧ��IndexС��k�������ұ� */
	if (nret < k) return selectKMin(ArrData, nret + 1, Right, k);

	return nret;
}
