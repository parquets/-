#pragma once

#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/*
	Data:2018/8/20
	Auther: 白洁
	Description:数据结构排序章节复习，各类sort函数的声明与实现，排序规则都是从小到大
	函数参数说明：void SortFuncName(DataType* ArrData, int Left, int Right)
				ArrData:输入数组数据
				Left：排序起始的位置
				Right：排序终止位置+1
	Reference：数据结构-王晓东，数据结构与算法分析-Mark Allen Weiss
*/

/* 冒泡排序， 时间复杂度为O(n^2), 是一种交换排序 */
template <typename DataType>
void bubble_sort(DataType* ArrData, int Left, int Right);

/* 插入排序， 时间复杂度为O(n^2) */
template <typename DataType>
void insert_sort(DataType* ArrData, int Left, int Right);

/* 选择排序，时间复杂度为O(n^2) */
template <typename DataType>
void select_sort(DataType* ArrData, int Left, int Right);

/* 快速排序, 时间复杂度为O(nlogn)
	步骤：1、分解：以ArrData[p]为基准元素，将数组ArrData[Left:Right-1]分为三个部分：ArrData[p:q-1],ArrData[q],ArrData[q+1:Right-1]
				使得ArrData[p:q-1]里的任一元素小于ArrData[q],ArrData[q+1:Right-1]的任一元素大于ArrData[q];
		 2、递归求解：分别对ArrData[p:q-1]和ArrData[q+1,Right-1]的元素进行快速排序
		 3、合并
	是不稳定的排序 */
template <typename DataType>
void quick_sort(DataType* ArrData, int Left, int Right);

/* 并归排序 时间复杂度：O(nlogn)
	思想：当n为1时停止排序，否则将待排序元素分成大小大致相同的两个子集，分别对这两个子集进行排序 */
template <typename DataType>
void merge_sort(DataType* ArrData, int Left, int Right);

template <typename DataType>
void merge_sort_loop(DataType* ArrData, int Left, int Right);

/* 寻找从小到大排列的第K个的元素 ，线性时间 */
template <typename DataType>
int selectKMin(DataType* ArrData, int Left, int Right, int k);

template <typename DataType>
int partition(DataType* ArrData, int Left, int Right, int privotIndex);

template <typename DataType>
int partition(DataType* ArrData, int Left, int Right, int privotIndex)
{
	/* 划分，数组中小于ArrData[privotInedx]的值保存在其左边，大于在其右边 */
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
	bool is_sorted = true;		// 冒泡的优化，判断是否已排序，如果是，则结束
	for (int i = Left; i < Right; ++i)
	{
		for (int j = i + 1; j < Right; ++j)
		{
			if (ArrData[i] > ArrData[j])
			{
				true = false;	//如果进行了交换操作，则认为非有序
				tmp = ArrData[i];
				ArrData[i] = ArrData[j];
				ArrData[j] = tmp;
			}
		}
		if (is_sorted == true) break;	//有序，跳出循环
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
	bool is_sorted = true;	//判断是否有序
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
			if (ArrData[j] < ArrData[j - 1]) is_sorted = false;	//如果存在ArrData[j]<ArrData[j-1],则表示数组仍无须
		}
		if (is_sorted == true) break; // 如数组已经有序，则跳出循环体
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
		key_pos = Left;	/* 这里设置哨兵元素的位置，哨兵节点的左侧元素小于哨兵元素，右侧大于，更换key_pos时要和第一个元素交换*/
		key_val = ArrData[key_pos];
		while (true)
		{
			while (ArrData[++i] < key_val && i < Right - 1);	//寻找第一个元素值大于key_val的位置
			while (ArrData[--j] > key_val);	//寻找第一个元素值小于key_val的位置
			if (i >= j) break;
			/* 交换ArrData[i]与ArrData[j] */
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
	/* 并归函数，用于排序好的两部分的合并
       参数说明： LeftPos  表示左半部开始的位置
				RightPos 表示右半部开始的位置
				RightEnd 左半部分结束的位置
	*/
	int i, //循环变量
		LeftEnd = RightPos - 1,	//LeftEnd表示左边数组结束的位置
		TmpPos = LeftPos,		//在TmpArr中插入元素所需要的下标
		ElemNum = RightEnd - LeftPos + 1;

	/* 循环体内合并两组数据 */
	while (LeftPos <= LeftEnd && RightPos <= RightEnd)
	{
		/* 如果是左边的数据小，则左边的数据加入到TmpArr中，并且位置自增1，右边类似 */
		if (ArrData[LeftPos] <= ArrData[RightPos]) 
			TmpArr[TmpPos++] = ArrData[LeftPos++];
		else 
			TmpArr[TmpPos++] = ArrData[RightPos++];
	}
	/* 将剩余的数据也加入到TmpArr中去*/
	while (LeftPos <= LeftEnd)
		TmpArr[TmpPos++] = ArrData[LeftPos++];
	while (RightPos <= RightEnd)
		TmpArr[TmpPos++] = ArrData[RightPos++];

	/* 将TmpArr中的结果复制会ArrData中*/
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
		/*center将数组分为左右两个部分， 对左右两个部分分别做排序 */
		msort(ArrData, TmpArr, Left, center);
		msort(ArrData, TmpArr, center + 1, Right);
		//合并数组
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

	/* 设置枢纽元为ArrData[Left+1] */
	int privotIndex = Left + 1;

	/* 针对该枢纽元进行一次划分，小于枢纽元的元素在枢纽元左边，大于在右边 */
	nret = partition(ArrData, Left, Right, privotIndex);

	/* 如果枢纽元对应的Index大于k，则待查找的第k个元素在Index的左边 */
	if (nret > k) return selectKMin(ArrData, Left, nret, k);
	
	/* 反之，如果枢纽元对应的Index小于k，则在右边 */
	if (nret < k) return selectKMin(ArrData, nret + 1, Right, k);

	return nret;
}
