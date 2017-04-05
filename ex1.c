#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include <time.h>

int *insertionSort(int *a, int n); //a - array, n - length
void merge(int *a, int p, int q, int r); //a - array p -first index, q - array length middle r - last array index
void mergeSort(int *a, int p, int r); //a - array p -first index, r - last array index
int partition(int *a, int p, int r);
void quicksort2(int *a, int p, int r);//a - array p -first index, r - last array index
void swap(int *A, int i, int j);
int *getRandomArray(int n, int range);
int *getSortedArray(int n, int range);
void reverseArray(int *a, int n);
void displayArray(int *a, int n);
int *copyArray(int *a, int n);
void quicksort(int *a, int p, int r);
void compareArrays(int *a, int *aa, int n);
void merge2(int *A,int *L,int leftCount,int *R,int rightCount);
void mergeSort2(int *A,int n);
void resetCounrers();
double getInsertionSortTime(int *a, int n);
double getMergesortTime(int *a, int n);
double getQuicksortTime(int *a, int n);
int findLargestNum(int * array, int size);
void radixSort(int * array, int size);
double getRadixSortTime(int *a, int n);
void radixSortDemonstration(int * array, int size);
void printArray(int * array, int size);

typedef struct Counter{
  int comparisonNumber;
  int swapNumber;
}Counter;

Counter insertionSortInfo = {0, 0}, mergeSortInfo = {0, 0}, quicksortInfo = {0, 0}, radixSortInfo = {0, 0};

int main(){
  int *a, *insertionSortArray, *mergeSortArray, *quicksortArray, *radixSortArray, range, arraySize, foo, i, *aa;
  char arrayType;
  double seconds;
  FILE *fp;
  clock_t start = clock();
  clock_t end = clock();
  printf("1. Generate random array\n");
  printf("2. Generate sorted array\n");
  printf("3. Demonstrate how radixsort works for small data\n");
  printf("chose: ");
  scanf("%c", &arrayType);
  while(arrayType != '1' && arrayType != '2' && arrayType != '3'){
    printf("Incorrect intput! \n");
    printf("choose: ");
    scanf("%c", &arrayType);
  }
  printf("Value range: ");
  scanf("%d", &range);
  range++;

  printf("Data size: ");
  scanf("%d",&arraySize);

if(arrayType == '3'){
  int *a;
  a = getRandomArray(arraySize, range);
  radixSortDemonstration(a, arraySize);
  exit(1);

}
if(arrayType == '1'){
  a = getRandomArray(arraySize, range);
}
else{
  a = getSortedArray(arraySize, range);
}

foo = arraySize / 100;
Counter *insertionSortCounter, *mergeSortCounter, *quicksortCounter, *radixSortCounter;
insertionSortCounter = malloc((foo) * sizeof(Counter));
mergeSortCounter = malloc((foo) * sizeof(Counter));
quicksortCounter = malloc((foo) * sizeof(Counter));
radixSortCounter = malloc((foo) * sizeof(Counter));

fp = fopen("test.csv", "w+");
fprintf(fp, "Data size,RadixSort time,Insertionsort time time,Mergesort time,Quicksort time,     ,\n");

for(i = 1; i <= foo; i++){
  if(arrayType == '1'){
    a = getRandomArray(i * 100, range);
  }
  else{
    a = getSortedArray(i * 100, range);
  }

  fprintf(fp, "%d,",i * 100);
  fprintf(fp, "%.10e,",getRadixSortTime(a, i * 100));
  // fprintf(fp, "%.10e,",getInsertionSortTime(a, i * 100));
  fprintf(fp, "%.10e,",0);
  // fprintf(fp, "%.10e,", getMergesortTime(a, i * 100));
  fprintf(fp, "%.10e,",0);
  fprintf(fp, "%.10e\n",getQuicksortTime(a, i * 100));
  free(a);
  insertionSortCounter[i - 1].comparisonNumber = insertionSortInfo.comparisonNumber;
  insertionSortCounter[i - 1].swapNumber = insertionSortInfo.swapNumber;
  mergeSortCounter[i - 1].comparisonNumber = mergeSortInfo.comparisonNumber;
  mergeSortCounter[i - 1].swapNumber = mergeSortInfo.swapNumber;
  quicksortCounter[i - 1].comparisonNumber = quicksortInfo.comparisonNumber;
  quicksortCounter[i - 1].swapNumber = quicksortInfo.swapNumber;
  radixSortCounter[i - 1].swapNumber = radixSortInfo.swapNumber;
  radixSortCounter[i - 1].comparisonNumber = radixSortInfo.comparisonNumber;
  resetCounrers();
}


printf("\n\n" );

// fp = fopen("test.csv", "w+");
fprintf(fp, "Data size,radixSort comparison,Insertionsort comparison,Mergesort comparison,Quicksort comparison,     ,Data size,RadixSort swap,Insertionsort swap,Mergesort swap,Quicksort swap\n");
for(i = 0; i < foo; i++){
  fprintf(fp, "%d,%d,%d,%d,%d,    ,%d,%d,%d,%d,%d\n", (i + 1) * 100, radixSortCounter[i].comparisonNumber,insertionSortCounter[i].comparisonNumber, mergeSortCounter[i].comparisonNumber, quicksortCounter[i].comparisonNumber, (i + 1) * 100, radixSortCounter[i].swapNumber, insertionSortCounter[i].swapNumber, mergeSortCounter[i].swapNumber, quicksortCounter[i].swapNumber);
}
 fclose(fp);

 system("libreoffice --calc test.csv &");
 free(insertionSortCounter);
 free(mergeSortCounter);
 free(quicksortCounter);
 free(radixSortCounter);

  return 0;
}


int findLargestNum(int * array, int size){

  int i;
  int largestNum = -1;

  for(i = 0; i < size; i++){
    radixSortInfo.comparisonNumber++;
    if(array[i] > largestNum)
      largestNum = array[i];
  }

  return largestNum;
}

void radixSort(int * array, int size){
  int i;
  int *semiSorted;
  semiSorted = malloc((size) * sizeof(int));
  int significantDigit = 1;
  int largestNum = findLargestNum(array, size);

  while (largestNum / significantDigit > 0){
    int bucket[10] = { 0 };

    for (i = 0; i < size; i++)
      bucket[(array[i] / significantDigit) % 10]++;

    for (i = 1; i < 10; i++)
      bucket[i] += bucket[i - 1];

    for (i = size - 1; i >= 0; i--)
      semiSorted[--bucket[(array[i] / significantDigit) % 10]] = array[i];

    for (i = 0; i < size; i++){
      array[i] = semiSorted[i];
      radixSortInfo.swapNumber++;
    }


    significantDigit *= 10;
  }
}


int *insertionSort(int *a, int n){
  // printf("Start insertionSort algorithm\n" );
  int j, i, key;
  for(j = 1; j < n; j++){
    // printf("Store key = %d\n",a[j] );
    key = a[j];
    i = j - 1;
    insertionSortInfo.comparisonNumber++;
    // printf("Move key to the left until it will be on the right place\n" );
    while((i >= 0) && (a[i] > key)){
      a[i + 1] = a[i];
      i--;
      insertionSortInfo.comparisonNumber++;
      insertionSortInfo.swapNumber++;
    }
    // printf("Store key value a[%d] = %d\n",i + 1, key );
    a[i + 1] = key;
    insertionSortInfo.swapNumber++;
  }
  // printf("End insertionSort algorithm\n" );
    return a;
}

void swap(int *A, int i, int j) {
   int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
}



void quicksort(int *a, int p, int r){
    int i = p, j = r, x, q = a[(p + r) / 2];
    do{
      quicksortInfo.comparisonNumber++;
    while (a[i] < q){
      // printf("Move left array index one position to the right\n");
      i++;
      quicksortInfo.comparisonNumber++;
    }
    quicksortInfo.comparisonNumber++;
    while (a[j] > q){
      // printf("Move right array index one position to the left\n");
      quicksortInfo.comparisonNumber++;
      j--;
    }
    if (i <= j){
      // printf("Swap a[%d] = %d and a[%d] = %d\n",i, a[i], j, a[j] );
      quicksortInfo.swapNumber += 2;
      swap(a, i, j);
      i++; j--;
    }
    }while (i<=j);
    if (j > p){
      // printf("Call quicksort(array, %d, %d)\n", p, j);
      quicksort(a, p, j);
    }
    if (i < r){
      // printf("Call quicksort(array, %d, %d)\n", i, r);
      quicksort(a, i, r);
    }
  }

  void merge(int *a, int p, int q, int r){
    int n1 = q - p + 1, n2 = r - q, *ll, *rr, i, j, k;
    ll = malloc((n1) * sizeof(int));
    rr = malloc((n2) * sizeof(int));

    // printf("Create first sub-array\n" );
    for(i = 0; i < n1; i++){
      ll[i] = a[p + i];
    }
    // printf("Create second sub-array\n" );
    for(i = 0; i < n2; i++){
        rr[i] = a[q + i + 1];
    }
    i = 0; j = 0;k = p;
    // printf("Merge 2 sorted arrays\n" );
    while(i < n1 && j < n2) {
      if(ll[i]  < rr[j]) a[k++] = ll[i++];
      else a[k++] = rr[j++];
      mergeSortInfo.comparisonNumber++;
      mergeSortInfo.swapNumber += 2;
    }
    while(i < n1){
      a[k++] = ll[i++];
      mergeSortInfo.swapNumber += 2;
    }
    while(j < n2){
      a[k++] = rr[j++];
      mergeSortInfo.swapNumber += 2;
    }
    free(ll);
    free(rr);
  }

    void mergeSort(int *a, int p, int r){
      int q;
      if(p < r){
      q = (int)((p + r) / 2);
      // printf("Call mergeSort(array, %d, %d)\n",p, q );
      mergeSort(a, p, q);
      // printf("Call mergeSort(array, %d, %d)\n",q + 1, r );
      mergeSort(a, q + 1, r);
      // printf("Call merge(array, %d, %d, %d)\n",p, q, r );
      merge(a, p, q, r);
    }
  }












  void quicksort2(int *a, int p, int r){
    int q;
    if(p < r){
      q = partition(a, p, r);
      quicksort2(a, p, q - 1);
      quicksort2(a, q + 1, r);
    }
  }

  int partition(int *a, int p, int r){
    int x = a[r], i = p - 1, j, buffor;
    for(j = p; j <= r - 1; j++){
      quicksortInfo.comparisonNumber++;
      if(a[j] <= x){
        i = i + 1;
        swap(a, i, j);
        quicksortInfo.swapNumber += 2;
      }
    }
    swap(a, i + 1, r);
    quicksortInfo.swapNumber += 2;
    return i + 1;
  }

  void merge2(int *a,int *p,int np,int *r,int rc) {
  	int i,j,k;
  	i = 0; j = 0; k =0;

  	while(i < np && j< rc) {
  		if(p[i]  < r[j]) a[k++] = p[i++];
  		else a[k++] = r[j++];
      mergeSortInfo.comparisonNumber++;
      mergeSortInfo.swapNumber += 2;
  	}
  	while(i < np){
      a[k++] = p[i++];
      mergeSortInfo.swapNumber += 2;
    }
  	while(j < rc){}
    a[k++] = r[j++];
    mergeSortInfo.swapNumber += 2;
  }

  void mergeSort2(int *a,int n) {
  	int q,i, *p, *r;
  	if(n < 2) return;
  	q = n/2;
  	p = (int*)malloc(q * sizeof(int));
  	r = (int*)malloc((n - q) * sizeof(int));

  	for(i = 0;i < q; i++) p[i] = a[i];
  	for(i = q;i < n; i++) r[i - q] = a[i];

  	mergeSort2(p, q);
  	mergeSort2(r,n - q);
  	merge2(a, p, q, r, n - q);
          free(p);
          free(r);
  }


















  void compareArrays(int *a, int *aa, int n){
    int i;
    for(i = 0; i < n; i++){
      if(a[i] != aa[i]){
        printf("NOT THE SAME !!!\n");
        printf("NOT THE SAME !!!\n");
        printf("NOT THE SAME !!!\n");
        break;
      }
    }
    printf("TABLES ARE THE SAME !!!\n" );
    printf("TABLES ARE THE SAME !!!\n" );
    printf("TABLES ARE THE SAME !!!\n" );
  }

  int *getRandomArray(int n, int range){
    int *a, r, k, i;
    a = malloc(n * sizeof(int));
    srand(time(NULL));
    for(i = 0; i < n; i++){
      r = rand() % range;
      // k = rand() % 2;
      // if(k == 1){
      //   r*=( -1);
      // }
      a[i] = r;
  }
  return a;
  }

  int *getSortedArray(int n, int range){
    int *a, i, j;
    a = getRandomArray(n, range);
    quicksort(a, 0, n - 1);
    reverseArray(a, n);
    quicksortInfo.comparisonNumber = 0;
    quicksortInfo.swapNumber = 0;
    return a;
  }

  void reverseArray(int *a, int n){
    int i, j;
    i = n - 1;
    j = 0;
    while(i > j){
      swap(a, i, j);
      i--;
      j++;
    }
  }

  void displayArray(int *a, int n){
    int i;
    printf("[");
    for(i = 0; i < n; i++){
      printf("%d", a[i]);
      printf(",");
    }
    printf("]\n" );
  }

  int *copyArray(int *a, int n){
    int *aa, i;
    aa = malloc((n + 1) * sizeof(int));
    for(i = 0; i < n; i++){
      aa[i] = a[i];
    }
    return aa;
  }

void resetCounrers(){
  insertionSortInfo.comparisonNumber = 0;
  insertionSortInfo.swapNumber = 0;
  mergeSortInfo.comparisonNumber = 0;
  mergeSortInfo.swapNumber = 0;
  quicksortInfo.comparisonNumber = 0;
  quicksortInfo.swapNumber = 0;
  radixSortInfo.swapNumber = 0;
  radixSortInfo.comparisonNumber = 0;
}

double getInsertionSortTime(int *a, int n){
  clock_t start = clock();
  clock_t end = clock();
  int *aa;
  double seconds;
  aa = copyArray(a, n);
  start = clock();
  insertionSort(aa, n);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  free(aa);
  return seconds;
}

double getMergesortTime(int *a, int n){
  clock_t start = clock();
  clock_t end = clock();
  int *aa;
  double seconds;
  aa = copyArray(a, n);
  start = clock();
  // mergeSort(aa, n);
   mergeSort(aa, 0, n - 1);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  free(aa);
  return seconds;
}

double getQuicksortTime(int *a, int n){
  clock_t start = clock();
  clock_t end = clock();
  int *aa;
  double seconds;
  aa = copyArray(a, n);
  start = clock();
  quicksort(aa, 0, n - 1);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  free(aa);
  return seconds;
}

double getRadixSortTime(int *a, int n){
  clock_t start = clock();
  clock_t end = clock();
  int *aa;
  double seconds;
  aa = copyArray(a, n);
  start = clock();
  radixSort(aa, n);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  free(aa);
  return seconds;
}

void radixSortDemonstration(int * array, int size){

  printf("\n\nRunning Radix Sort on Random List!\n\n");

  // Base 10 is used
  int i;
  int semiSorted[size];
  int significantDigit = 1;
  int largestNum = findLargestNum(array, size);

  // Loop until we reach the largest significant digit
  while (largestNum / significantDigit > 0){

    printf("\tSorting: %d's place ", significantDigit);
    printArray(array, size);

    int bucket[10] = { 0 };

    // Counts the number of "keys" or digits that will go into each bucket
    for (i = 0; i < size; i++)
      bucket[(array[i] / significantDigit) % 10]++;

    /**
     * Add the count of the previous buckets,
     * Acquires the indexes after the end of each bucket location in the array
		 * Works similar to the count sort algorithm
     **/
    for (i = 1; i < 10; i++)
      bucket[i] += bucket[i - 1];

    // Use the bucket to fill a "semiSorted" array
    for (i = size - 1; i >= 0; i--)
      semiSorted[--bucket[(array[i] / significantDigit) % 10]] = array[i];


    for (i = 0; i < size; i++)
      array[i] = semiSorted[i];

    // Move to next significant digit
    significantDigit *= 10;

    printf("\n\tBucket: ");
    printArray(bucket, 10);
  }
}


void printArray(int * array, int size){

  int i;
  printf("[ ");
  for (i = 0; i < size; i++)
    printf("%d ", array[i]);
  printf("]\n");
}
