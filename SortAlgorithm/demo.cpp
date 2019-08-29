#include "sorts.h"
#include "SortExperience.h"
#include <iostream>
#include <stdlib.h>

int len1 = 8;
int len2 = 16;
int len3 = 11;

int test_arr1[] = { -4,-4,-4,-4,-4,-4,-4,-4 }; /* len = 8*/
int test_arr2[] = { -5,2,-6,89,3,100,28,-22,48,-84,922,34,575,-184,15,15 };/*len = 16*/
int test_arr3[] = { -3,-2,-1,1,2,3,4,5,6,7,8 }; /* len = 11*/

template <typename ArrType>
void output(ArrType* Arr, int len)
{
	for (int i = 0; i < len; ++i)
		std::cout << Arr[i] << " ";
	std::cout << std::endl;
}

int main()
{
	//right_rotate(test_arr3, 3, 8, 4);
	//reverse(test_arr3, 4, len3);
	int k = 5;
	int index = selectKMin(test_arr2, 0, len2, k-1);
	printf("index = %d value = %d\n", index, test_arr2[index]);
	quick_sort(test_arr2, 0, len2);
	output(test_arr2, len2);
	system("pause");
	return 0;
}
