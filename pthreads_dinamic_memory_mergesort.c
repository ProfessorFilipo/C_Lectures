//This code was adapted from the code available at
// https://www.geeksforgeeks.org/merge-sort-using-multi-threading/

// C Program to implement merge sort using 
// multi-threading and dinamic memory allocation
#include <pthread.h> 
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>

// number of elements in array 
#define MAX 2000 

// number of threads 
#define THREAD_MAX 4 

//using namespace std; 

// array of size MAX 
int* a; 
int part = 0; 

// merge function for merging two parts 
void merge(int low, int mid, int high) 
{ 
	//int* left = new int[mid - low + 1]; 
	int *left = (int*)malloc(sizeof(int) * (mid - low + 1));
	
	//int* right = new int[high - mid]; 
	int *right = (int*)malloc(sizeof(int) * (high - mid));

	// n1 is size of left part and n2 is size 
	// of right part 
	int n1 = mid - low + 1, n2 = high - mid, i, j; 

	// storing values in left part 
	for (i = 0; i < n1; i++) 
		left[i] = a[i + low]; 

	// storing values in right part 
	for (i = 0; i < n2; i++) 
		right[i] = a[i + mid + 1]; 

	int k = low; 
	i = j = 0; 

	// merge left and right in ascending order 
	while (i < n1 && j < n2) { 
		if (left[i] <= right[j]) 
			a[k++] = left[i++]; 
		else
			a[k++] = right[j++]; 
	} 

	// insert remaining values from left 
	while (i < n1) { 
		a[k++] = left[i++]; 
	} 

	// insert remaining values from right 
	while (j < n2) { 
		a[k++] = right[j++]; 
	} 
} 

// merge sort function 
void merge_sort(int low, int high) 
{ 
	// calculating mid point of array 
	int mid = low + (high - low) / 2; 
	if (low < high) { 

		// calling first half 
		merge_sort(low, mid); 

		// calling second half 
		merge_sort(mid + 1, high); 

		// merging the two halves 
		merge(low, mid, high); 
	} 
} 

// thread function for multi-threading 
void* th_merge_sort(void* arg) 
{ 
	// which part out of 4 parts 
	int thread_part = part++; 

	// calculating low and high 
	int low = thread_part * (MAX / 4); 
	int high = (thread_part + 1) * (MAX / 4) - 1; 

	// evaluating mid point 
	int mid = low + (high - low) / 2; 
	if (low < high) { 
		merge_sort(low, mid); 
		merge_sort(mid + 1, high); 
		merge(low, mid, high); 
	} 
} 

// Driver Code 
int main() 
{ 
	printf("\n\n::: PThreads Merge Sort ::: \n\n");
	printf("::: Array size: %d \n::: Thread Number: %d\n", MAX, THREAD_MAX );
    // memory allocation for the array
    a = (int*)malloc(sizeof(int) * MAX);
    if(a == NULL)
    {
    	printf("\nError allocating memory...\n");
    	exit(EXIT_FAILURE);
	}

	// generating random values in array 
	printf(":::: generating random values in array...\n");
	for (int i = 0; i < MAX; i++) 
		a[i] = rand() % MAX; 

	// show the array before sorting it
	//printf("\n Array before sorting it: \n");
	//for(int i = 0; i < MAX; i++)
	//{
	//	printf(" %d ", a[i]);
	//}
	
	// save the assorted array at disk
	printf(":::: Saving assorted array on disk...\n");
	FILE* assortedFile = fopen("assorted.txt", "w");
	if(assortedFile == NULL)
    {
    	printf("\nError creating assorted file on disk...\n");
    	exit(EXIT_FAILURE);
	}

	for(int i = 0; i < MAX; i++)
	{
		fprintf(assortedFile, " %6d \n", a[i]);
	}
	fclose(assortedFile);
	

	// t1 and t2 for calculating time for 
	// merge sort 
	clock_t t1, t2; 

	t1 = clock(); 
	pthread_t threads[THREAD_MAX]; 

	// creating 4 threads 
	printf(":::: creating %d threads...\n", THREAD_MAX);
	for (int i = 0; i < THREAD_MAX; i++) 
		pthread_create(&threads[i], NULL, th_merge_sort, (void*)NULL); 

	// joining all 4 threads 
	printf(":::: joining all %d threads...\n", THREAD_MAX);
	for (int i = 0; i < 4; i++) 
		pthread_join(threads[i], NULL); 

	// merging the final 4 parts 
	printf(":::: merging the final %d parts...\n", THREAD_MAX);
	merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1); 
	merge(MAX / 2, MAX/2 + (MAX-1-MAX/2)/2, MAX - 1); 
	merge(0, (MAX - 1)/2, MAX - 1); 

	t2 = clock(); 

	// displaying sorted array 
	//printf("\nSorted array: \n"); 
	//for (int i = 0; i < MAX; i++) 
	//	printf(" %d ", a[i]);

	// save the sorted array at disk
	printf(":::: Saving the final sorted array on disk...\n");
	FILE* sortedFile = fopen("sorted.txt", "w");
	if(sortedFile == NULL)
    {
    	printf("\nError creating sorted file on disk...\n");
    	exit(EXIT_FAILURE);
	}

	for(int i = 0; i < MAX; i++)
	{
		fprintf(sortedFile, " %6d \n", a[i]);
	}
	fclose(sortedFile);


	// time taken by merge sort in seconds 
	printf("\n\n::::Time taken: %2.2fs \n",  (t2 - t1) / (double)CLOCKS_PER_SEC ); 

	return 0; 
}
