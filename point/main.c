#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (*cmp_t)(const void *data1, const void *data2);

int sort_arr(void *arr, int nmemb, int size, cmp_t cmp);

static int cmp_num(const void *data1, const void *data2)
{
	const int *d1 = data1;
	const int *d2 = data2;

	return *d2 - *d1;
}
int main(void)
{
	int arr[] = {8, 1, 2, 7, 9, 10, 15, 3, 2, 1};

	sort_arr(arr, sizeof(arr) / sizeof(*arr), sizeof(int), cmp_num);

	for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

/*
定义一个函数:能为任意类型的数组排序 
int *start nmemb
*start *(start+1)---->start[1]
*/
int sort_arr(void *arr, int nmemb, int size, cmp_t cmp)
{
	int i, j;
	char *tmp;

	tmp = calloc(1, size);
	// if error

	for (i = 0; i < nmemb-1; i++) {
		for (j = 0; j < nmemb-i-1; j++) {
			if (cmp((char *)arr+j*size, (char *)arr+(j+1)*size) < 0) {
				memcpy(tmp, (char *)arr+j*size, size);	
				memcpy((char *)arr+j*size,(char *)arr+(j+1)*size, size);
				memcpy((char *)arr+(j+1)*size, tmp, size);
			}
		}	
	}
}







