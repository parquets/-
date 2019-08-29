#pragma once

#include "sorts.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

/* Experience6.9 ����SrcData������Scr��һ��������У�������DstArr�У� ScrSize��ʾ����������С */
template <typename DataType>
void random_permutation(DataType* SrcData, DataType* DstArr, int SrcSize);

/* ��������� */
template <typename DataType>
void reverse(DataType* ArrData, int Left, int Right);

/* Experience6.11 �����黻λ */
template <typename DataType>
void right_rotate(DataType* ArrData, int Left, int Right, int k);

/* Experience6.17 ������ceil(3*n/2-2)�αȽ��ҳ�ArrData[0:ArrSize-1]�е������СԪ�� 
	ArrSize ��ʾ����Ĵ�С��max,min���ڱ��������Сֵ */
template <typename DataType>
void max_min_v1(DataType* ArrData, int ArrSize, int& max, int& min);

/* Experience6.18 ������ n+ceil(logn)-2�αȽ��ҳ�ArrData[0:ArrSize-1]�е������СԪ�� 
	����ʽ T(n) = 2*T(n/2)+2 */
template <typename DataType>
void max_min_v2(DataType* ArrData, int ArrSize, int& max, int& min);

/* Experience6.11 */
template <typename DataType>
void subarray_sort(DataType* ArrData, int ArrSize, int k);

/* Experience6.21 �ҵ�������λ�������k��Ԫ��,ʱ�临�Ӷ�O(n) */
template <typename DataType>
int findKNearest(DataType* ArrData, int Left, int Right, int k);

/* Experience6.22 �����ȴ�С������������飬�����������λ����O(logn)Ч�� */
template <typename DataType>
int TwoArrMid(DataType* FirstArr, DataType* SecondArr, int FirstLeft, int FirstRight, int SecondLeft, int SecondRight);

/* Experience6.24 lognʱ���ҵ� arr[i] = i��Ӧ��i */
template <typename DataType>
int ithEquali(DataType* ArrData, int Left, int Right);

/* Experience6.25 ����ʱ���ҵ��������Ԫ�� */
template <typename DataType>
int findMainElem(DataType* ArrData, int Left, int Right);



template <typename DataType>
void random_permutation(DataType* SrcData, DataType* DstArr, int SrcSize)
{
	/* ���DstArr����DstArrΪ��ʱ������ռ�  */
	if (DstArr == NULL) DstArr = new DataType[SrcSize];

	DataType tmp;
	for (int i = 0; i < SrcSize; ++i)
		DstArr[i] = SrcData[i];

	srand((int)time(0));

	for (int i = 0; i < 2 * SrcSize; ++i)
	{
		int r_a, r_b;

		//�����������������Χ��0-SrcSize֮��
		r_a = rand() % SrcSize;
		r_b = rand() % SrcSize;

		//�����������Ӧλ�õ�Ԫ�ؽ���
		tmp = DstArr[r_a];
		DstArr[r_a] = DstArr[r_b];
		DstArr[r_b] = tmp;
	}
}

template <typename DataType>
void reverse(DataType* ArrData, int Left, int Right)
{
	DataType tmp;
	Right--;
	for (int i = Left, j = Right; i < j; ++i, --j)
	{
		tmp = ArrData[i];
		ArrData[i] = ArrData[j];
		ArrData[j] = tmp;
	}
}

template <typename DataType>
void right_rotate(DataType* ArrData, int Left, int Right, int k)
{
	reverse(ArrData, Left, k + 1);
	reverse(ArrData, k + 1, Right);
	reverse(ArrData, Left, Right);
}

template <typename DataType>
void max_min_v1(DataType* ArrData, int ArrSize, int& max, int& min)
{
	/* ˼·�����������Ƚ� */
	/* ������Ԫ�ظ���Ϊ1ʱ��ֱ�ӱȽϲ����� */
	if (ArrSize == 1)
	{
		max = ArrData[0];
		min = ArrData[0];
		return;
	}

	/* �ȶ�ǰ����Ԫ�ؽ��бȽϣ�С��Ԫ��ֵ��min����ĸ�ֵ��max*/
	if (ArrData[0] > ArrData[1])
	{
		max = ArrData[0];
		min = ArrData[1];
	}
	else
	{
		max = ArrData[1];
		min = ArrData[0];
	}

	int i;
	/* �ܹ�ArrSize/2��ѭ�� */
	for (i = 2; i < ArrSize - 1; i += 2)
	{
		/* ��ÿһ�飬����һ��ArrData�ıȽϣ�ÿ��ѭ�����������αȽ� */
		if (ArrData[i] > ArrData[i + 1])
		{
			/* ������max�Ƚϣ�С����min�Ƚ� */
			if (ArrData[i] > max) max = ArrData[i];
			if (ArrData[i + 1] < min) min = ArrData[i + 1];
		}
		else
		{
			/* ArrDara[i] <= ArrData[i+1]����� */
			if (ArrData[i] < min) min = ArrData[i];
			if (ArrData[i + 1] > max) max = ArrData[i + 1];
		}
	}

	if(i != ArrSize)
	{
		if (ArrData[i] < min) min = ArrData[i];
		else
		{
			if (ArrData[i] > max) max = ArrData[i];
		}
	}
}

template <typename DataType>
void max_min_v2(DataType* ArrData, int ArrSize, int& max, int& min)
{
	/* ������Ԫ�ظ���Ϊ1ʱ��ֱ�ӱȽϷ��� */
	if (ArrSize == 1)
	{
		max = ArrData[0];
		min = ArrData[0];
		return;
	}

	/* ��СΪ2ʱ��Ҳֱ�ӱȽϵó����� */
	if (ArrSize == 2)
	{
		if (ArrData[0] < ArrData[1]) min = ArrData[0], max = ArrData[1];
		else min = ArrData[1], max = ArrData[0];
		return;
	}
	
	/* ������Ԫ�ش���3��ʱ������ */
	int mid = ArrSize / 2;
	int min1, max1, min2, max2;
	/* ���Σ��������ΪArrData[0:mid],ArrData[mid:ArrSize]������ */
	max_min_v2(ArrData, mid, max1, min1);
	max_min_v2(ArrData + mid, ArrSize - mid, max2, min2);

	max = max1 > max2 ? max1 : max2;
	min = min1 < min2 ? min1 : min2;
}

template <typename DataType>
void subarray_sort(DataType* ArrData, int ArrSize, int k)
{
	int i = 0;
	int end = k + 1;
	while (end < ArrSize)
	{
		if (ArrData[i] > ArrData[end])
		{
			/* ��ArrData[i]>ArrData[end], ���������Էֽ���kΪ�������򣬸��㷨��֤ArrData[0:end]֮��������� */
			right_rotate(ArrData, i, end + 1, k);
			++end;
		}
		++i;
	}
}

template <typename DataType>
int ithEquali(DataType* ArrData, int Left, int Right)
{
	int Mid = (Left + Right) / 2;
	if (ArrData[Mid] == Mid) return Mid;
	else
	{
		if (Left >= Right) return -1;
		else
		{
			int t = ithEquali(ArrData, Left, Mid);
			if (t != -1) return t;
			else return ithEquali(ithEquali(ArrData, Mid + 1, Right));
		}
	}
}

template <typename DataType>
int findKNearest(DataType* ArrData, int Left, int Right, int k)
{
	/* ˼·�����ҵ���λ������Ȼ������λ����ߵĵ�Left-k/2��Ԫ�أ��ҵ���λ���ұߵĵ�k/2��Ԫ�� */
	int Mid = (Left + Right) / 2;

	int midIndex = selectKMin(ArrData, Left, Right, Mid);
	int start = selectKMin(ArrData, Left, midIndex - 1, Left - k / 2);
	int end = selectKMin(ArrData, midIndex, Right, k / 2);
	return start;
}

template <typename DataType>
int TwoArrMid(DataType* FirstArr, DataType* SecondArr, int FirstLeft, int FirstRight, int SecondLeft, int SecondRight)
{
	if (FirstLeft == FirstRight) return FirstArr[FirstLeft];
	else
	{
		if (SecondLeft == SecondRight) return SecondArr[SecondLeft];
	}

	int FirstMid = (FirstLeft + FirstRight) / 2;
	int SecondMid = (SecondLeft + SecondRight) / 2;

	if (FirstArr[Mid] > SecondArr[Mid])
	{
		FirstRight = FirstMid;
		SecondLeft = SecondMid;
	}
	else
	{
		if (FirstArr[Mid] < SecondArr[Mid])
		{
			FirstLeft = FirstMid;
			SecondRight = SecondMid;
		}
		else return FirstArr[FirstMid];
	}
	TwoArrMid(FirstArr, SecondArr, FirstLeft, FirstRight, SecondLeft, SecondRight);

}

template <typename DataType>
int findMainElem(DataType* ArrData, int Left, int Right)
{
	/* �ҵ���Ԫ�أ�Ԫ�ظ������ڵ���һ�룩*/
	int Mid = (Left + Right) / 2; 

	/* ����ʱ���ҵ���λ���������Ԫ�ش��ڣ���ô����λ��һ������Ԫ�ص�ֵ */
	int MidIndex = selectKMin(ArrData, Left, Right, Mid);

	int MidVal = ArrData[MidIndex];

	/* �������λ����Ԫ�ظ��� */
	int cnt = 0;
	for (int i = Left; i < Right; ++i)
	{
		if (ArrData[i] == MidVal) ++cnt;
	}
	/* �����λ���������г��ֵĴ�������һ�룬����Ϊ��Ԫ��Ϊ��Ԫ�� */
	if (cnt > (Right - Left) / 2) return MidIndex;
	else return -1;
}