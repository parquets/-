#pragma once

#include "sorts.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

/* Experience6.9 输入SrcData，返回Scr的一个随机排列，保存在DstArr中， ScrSize表示输入的数组大小 */
template <typename DataType>
void random_permutation(DataType* SrcData, DataType* DstArr, int SrcSize);

/* 数组的逆序 */
template <typename DataType>
void reverse(DataType* ArrData, int Left, int Right);

/* Experience6.11 子数组换位 */
template <typename DataType>
void right_rotate(DataType* ArrData, int Left, int Right, int k);

/* Experience6.17 最坏情况下ceil(3*n/2-2)次比较找出ArrData[0:ArrSize-1]中的最大最小元素 
	ArrSize 表示数组的大小，max,min用于保存最大最小值 */
template <typename DataType>
void max_min_v1(DataType* ArrData, int ArrSize, int& max, int& min);

/* Experience6.18 最坏情况下 n+ceil(logn)-2次比较找出ArrData[0:ArrSize-1]中的最大最小元素 
	地推式 T(n) = 2*T(n/2)+2 */
template <typename DataType>
void max_min_v2(DataType* ArrData, int ArrSize, int& max, int& min);

/* Experience6.11 */
template <typename DataType>
void subarray_sort(DataType* ArrData, int ArrSize, int k);

/* Experience6.21 找到距离中位数最近的k个元素,时间复杂度O(n) */
template <typename DataType>
int findKNearest(DataType* ArrData, int Left, int Right, int k);

/* Experience6.22 两个等大小，已排序的数组，求两数组的中位数，O(logn)效率 */
template <typename DataType>
int TwoArrMid(DataType* FirstArr, DataType* SecondArr, int FirstLeft, int FirstRight, int SecondLeft, int SecondRight);

/* Experience6.24 logn时间找到 arr[i] = i对应的i */
template <typename DataType>
int ithEquali(DataType* ArrData, int Left, int Right);

/* Experience6.25 线性时间找到数组的主元素 */
template <typename DataType>
int findMainElem(DataType* ArrData, int Left, int Right);



template <typename DataType>
void random_permutation(DataType* SrcData, DataType* DstArr, int SrcSize)
{
	/* 检查DstArr，当DstArr为空时，分配空间  */
	if (DstArr == NULL) DstArr = new DataType[SrcSize];

	DataType tmp;
	for (int i = 0; i < SrcSize; ++i)
		DstArr[i] = SrcData[i];

	srand((int)time(0));

	for (int i = 0; i < 2 * SrcSize; ++i)
	{
		int r_a, r_b;

		//生成两个随机数，范围在0-SrcSize之间
		r_a = rand() % SrcSize;
		r_b = rand() % SrcSize;

		//将两随机数对应位置的元素交换
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
	/* 思路：两个两个比较 */
	/* 当数组元素个数为1时，直接比较并返回 */
	if (ArrSize == 1)
	{
		max = ArrData[0];
		min = ArrData[0];
		return;
	}

	/* 先对前两个元素进行比较，小的元赋值给min，大的赋值给max*/
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
	/* 总共ArrSize/2次循环 */
	for (i = 2; i < ArrSize - 1; i += 2)
	{
		/* 对每一组，进行一次ArrData的比较，每个循环最多进行三次比较 */
		if (ArrData[i] > ArrData[i + 1])
		{
			/* 大者与max比较，小者与min比较 */
			if (ArrData[i] > max) max = ArrData[i];
			if (ArrData[i + 1] < min) min = ArrData[i + 1];
		}
		else
		{
			/* ArrDara[i] <= ArrData[i+1]的情况 */
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
	/* 当数组元素个数为1时，直接比较返回 */
	if (ArrSize == 1)
	{
		max = ArrData[0];
		min = ArrData[0];
		return;
	}

	/* 大小为2时，也直接比较得出结论 */
	if (ArrSize == 2)
	{
		if (ArrData[0] < ArrData[1]) min = ArrData[0], max = ArrData[1];
		else min = ArrData[1], max = ArrData[0];
		return;
	}
	
	/* 当数组元素大于3的时候讨论 */
	int mid = ArrSize / 2;
	int min1, max1, min2, max2;
	/* 分治，将数组分为ArrData[0:mid],ArrData[mid:ArrSize]两部分 */
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
			/* 当ArrData[i]>ArrData[end], 则将这两段以分界线k为中心逆序，该算法保证ArrData[0:end]之间是有序的 */
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
	/* 思路：先找到中位数，，然后找中位数左边的第Left-k/2个元素，找到中位数右边的第k/2个元素 */
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
	/* 找到主元素（元素个数大于等于一半）*/
	int Mid = (Left + Right) / 2; 

	/* 线性时间找到中位数，如果主元素存在，那么该中位数一定是主元素的值 */
	int MidIndex = selectKMin(ArrData, Left, Right, Mid);

	int MidVal = ArrData[MidIndex];

	/* 计算机中位数的元素个数 */
	int cnt = 0;
	for (int i = Left; i < Right; ++i)
	{
		if (ArrData[i] == MidVal) ++cnt;
	}
	/* 如果中位数在数组中出现的次数大于一半，则认为该元素为主元素 */
	if (cnt > (Right - Left) / 2) return MidIndex;
	else return -1;
}