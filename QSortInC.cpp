/*
 * QSort.cpp
 *
 *  Created on: 2016年6月8日
 *      Author: Qingwei
 */

//void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
//*base is pointer to the first element.
//nitems is the number of items to sort.
//size is the size of each element.
//compar is a compare function which can return -1 for less, 0 for equal and +1 for greater.

#include <stdio.h>
#include <stdlib.h>

int values[] = { 88, 56, 100, 2, 25 };

int cmpfunc(const void * a, const void * b) {
	return (*(int*) a - *(int*) b);
}

int QSortT() {
	int n;

	printf("Before sorting the list is: \n");
	for (n = 0; n < 5; n++) {
		printf("%d ", values[n]);
	}

	qsort(values, 5, sizeof(int), cmpfunc);

	printf("\nAfter sorting the list is: \n");
	for (n = 0; n < 5; n++) {
		printf("%d ", values[n]);
	}

	return (0);
}

