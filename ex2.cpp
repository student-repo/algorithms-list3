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
int randomPartition(int *a, int p, int r);
int random_selection(int* arr, int p, int r, int k);
int partition(int arr[], int l, int r, int x);
int kthSmallest(int arr[], int l, int r, int k);
int findMedian(int arr[], int n);
int *generateRandomPermutation(int n);

typedef struct Counter{
  int comparisonNumber;
  int swapNumber;
}Counter;

Counter insertionSortInfo = {0, 0}, mergeSortInfo = {0, 0}, quicksortInfo = {0, 0};

int main(){
  int *a, *insertionSortArray, *mergeSortArray, *quicksortArray, range, arraySize, foo, i, *aa, selectionNumber;
  char arrayType;
  double seconds;
  FILE *fp;
  clock_t start = clock();
  clock_t end = clock();
  printf("1. Generate random array\n");
  printf("2. Generate permutation array\n");
  printf("chose: ");
  scanf("%c", &arrayType);
  while(arrayType != '1' && arrayType != '2'){
    printf("Incorrect intput! \n");
    printf("choose: ");
    scanf("%c", &arrayType);
  }
  if(arrayType == '1'){
    printf("Value range: ");
    scanf("%d", &range);
    range++;
  }

  printf("Data size: ");
  scanf("%d",&arraySize);

  printf("selection number: ");
  scanf("%d",&selectionNumber);

if(arrayType == '1'){
  a = getRandomArray(arraySize, range);
}
else{
  a = generateRandomPermutation(arraySize);
}

foo = arraySize / 100;
Counter *insertionSortCounter, *mergeSortCounter, *quicksortCounter;
insertionSortCounter = new Counter[foo];
mergeSortCounter = new Counter[foo];
quicksortCounter = new Counter[foo];

fp = fopen("test.csv", "w+");
fprintf(fp, "Data size,Insertionsort time time,Mergesort time,Quicksort time,     ,\n");

for(i = 1; i <= foo; i++){
  if(arrayType == '1'){
    a = getRandomArray(i * 100, range);
  }
  else{
    a = getSortedArray(i * 100, range);
  }

  fprintf(fp, "%d,",i * 100);
  fprintf(fp, "%.10e,",getInsertionSortTime(a, i * 100));
  fprintf(fp, "%.10e,", getMergesortTime(a, i * 100));
  fprintf(fp, "%.10e\n",getQuicksortTime(a, i * 100));
  free(a);
  insertionSortCounter[i - 1].comparisonNumber = insertionSortInfo.comparisonNumber;
  insertionSortCounter[i - 1].swapNumber = insertionSortInfo.swapNumber;
  mergeSortCounter[i - 1].comparisonNumber = mergeSortInfo.comparisonNumber;
  mergeSortCounter[i - 1].swapNumber = mergeSortInfo.swapNumber;
  quicksortCounter[i - 1].comparisonNumber = quicksortInfo.comparisonNumber;
  quicksortCounter[i - 1].swapNumber = quicksortInfo.swapNumber;
  resetCounrers();
}


printf("\n\n" );

// fp = fopen("test.csv", "w+");
fprintf(fp, "Data size,Insertionsort comparison,Mergesort comparison,Quicksort comparison,     ,Data size,Insertionsort swap,Mergesort swap,Quicksort swap\n");
for(i = 0; i < foo; i++){
  fprintf(fp, "%d,%d,%d,%d,    ,%d,%d,%d,%d\n", (i + 1) * 100, insertionSortCounter[i].comparisonNumber, mergeSortCounter[i].comparisonNumber, quicksortCounter[i].comparisonNumber, (i + 1) * 100, insertionSortCounter[i].swapNumber, mergeSortCounter[i].swapNumber, quicksortCounter[i].swapNumber);
}
 fclose(fp);

 system("libreoffice --calc test.csv &");
 free(insertionSortCounter);
 free(mergeSortCounter);
 free(quicksortCounter);



// int *a;
// a = generateRandomPermutation(100);
// for(int i = 0; i < 100; i++){
//   printf("%d\n",a[i] );
// }


// int arr[] = {12, 3, 5, 7, 4, 19, 26};
// int n = sizeof(arr)/sizeof(arr[0]), k = 3;
// printf("K'th smallest element is %d\n",kthSmallest(arr, 0, n-1, k));

// int A[] = {9,5,7,1,10,2,3};
// int loc = random_selection(A, 0,6,5);
// printf("%d\n",loc );


  return 0;
}

int randomPartition(int *a, int p, int r){
  srand(time(NULL));
  int pivotIndex = p + rand()% (r-p);
  swap(a, pivotIndex, p);
  int x = a[p], i = p, j, buffor;
  for(j = p + 1; j <= r; j++){
    if(a[j] <= x){
      i = i + 1;
      swap(a, i, j);
    }
  }
  swap(a, i, p);
  return i;
}

int random_selection(int* arr, int p, int r, int k)
{
    if(p == r)
        return arr[p];

    if(k ==0) return -1;

    if(p < r)
    {

    int mid = randomPartition(arr, p, r);
    int i = mid - p + 1;
    if(i == k)
        return arr[mid];
    else if(k < i)
        return random_selection(arr, p, mid-1, k);
    else
        return random_selection(arr, mid+1, r, k-i);
    }

}

int kthSmallest(int arr[], int l, int r, int k)
{
    // If k is smaller than number of elements in array
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1; // Number of elements in arr[l..r]

        // Divide arr[] in groups of size 5, calculate median
        // of every group and store it in median[] array.
        int i, median[(n+4)/5]; // There will be floor((n+4)/5) groups;
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n) //For last group with less than 5 elements
        {
            median[i] = findMedian(arr+l+i*5, n%5);
            i++;
        }

        // Find median of all medians using recursive call.
        // If median[] has only one element, then no need
        // of recursive call
        int medOfMed = (i == 1)? median[i-1]:
                                 kthSmallest(median, 0, i-1, i/2);

        // Partition the array around a random element and
        // get position of pivot element in sorted array
        int pos = partition(arr, l, r, medOfMed);

        // If position is same as k
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  // If position is more, recur for left
            return kthSmallest(arr, l, pos-1, k);

        // Else recur for right subarray
        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }

    // If k is more than number of elements in array
    return INT_MAX;
}

int findMedian(int arr[], int n)
{
    // sort(arr, arr+n);  // Sort the array
    insertionSort(arr, n);
    return arr[n/2];   // Return middle element
}

int partition(int arr[], int l, int r, int x)
{
    // Search for x in arr[l..r] and move it to start
    int i;
    for (i=l; i<r; i++){
      if (arr[i] == x)
      break;
    }
    swap(arr, i, l);
    i = l;
    int  j, buffor;
    for(j = l + 1; j <= r; j++){
      if(arr[j] <= x){
        i = i + 1;
        swap(arr, i, j);
      }
    }
    swap(arr, i, l);
    return i;
}






int *insertionSort(int *a, int n){
  int j, i, key;
  for(j = 1; j < n; j++){
    key = a[j];
    i = j - 1;
    insertionSortInfo.comparisonNumber++;
    while((i >= 0) && (a[i] > key)){
      a[i + 1] = a[i];
      i--;
      insertionSortInfo.comparisonNumber++;
      insertionSortInfo.swapNumber++;
    }
    a[i + 1] = key;
    insertionSortInfo.swapNumber++;
  }
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
    ll = new int[n1];
    rr = new int[n2];

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
  	p = new int[q];
  	r = new int[n - q];

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
    a = new int[n];
    srand(time(NULL));
    for(i = 0; i < n; i++){
      r = rand() % range;
      k = rand() % 2;
      if(k == 1){
        r*=( -1);
      }
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
    aa = new int[n + 1];
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

int *generateRandomPermutation(int n){
  int *a;
  a = new int[n];
  for(int i = 0; i < n; i++){
    a[i] = i;
  }
  int index;
  srand(time(NULL));
  for(int j = 0; j < n; j++){
    index = rand() % n;
    printf("index = %d   i = %d\n",index, j );
    swap(a, index, j);
  }
    return a;
}
