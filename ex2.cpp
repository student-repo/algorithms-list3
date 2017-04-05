#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include <time.h>
#include<algorithm>

using namespace std;

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

typedef struct Counter{
  int comparisonNumber;
  int swapNumber;
}Counter;

int *insertionSort(int *a, int n); //a - array, n - length
int partition(int *a, int p, int r);
void swap(int *A, int i, int j);
int *getRandomArray(int n, int range);
int *getSortedArray(int n, int range);
void reverseArray(int *a, int n);
void displayArray(int *a, int n);
int *copyArray(int *a, int n);
void quicksort(int *a, int p, int r);
void compareArrays(int *a, int *aa, int n);
void resetCounrers();
double getInsertionSortTime(int *a, int n);
double getMergesortTime(int *a, int n);
double getQuicksortTime(int *a, int n);
int randomPartition(int *a, int p, int r);
int random_selection(int* arr, int p, int r, int k);
int partition(int arr[], int l, int r, int x);
int select(int arr[], int l, int r, int k);
int findMedian(int arr[], int n);
int *generateRandomPermutation(int n);
double getRandSelectTime(int *a, int n, int k);
double getSelectTime(int *a, int n, int k);
int random_selectionDemonstration(int* arr, int p, int r, int k);
void printArray(int * array, int size);
int randomPartitionDemonstration(int *a, int p, int r);
int findMedianDemonstration(int arr[], int n);
int selectDemonstration(int arr[], int l, int r, int k);
int findMaxArrayElement(Counter *a, int n);
int getArrayAvg(Counter *a, int n);
int findMinArrayElement(Counter *a, int n);




int randomSelectionIndex;
int selectionIndex;


Counter randomSelectionInfo = {0, 0}, selectionInfo = {0, 0};

int main(){
  int *a, *insertionSortArray, *mergeSortArray, *quicksortArray, range, arraySize, foo, i, *aa, *aaa, selectionNumber, interval = 1, k, testNumber;
  char arrayType, programMode;
  double seconds;
  FILE *fp;
  // srand(time(NULL));
  clock_t start = clock();
  clock_t end = clock();
  printf("1. Single selection test\n");
  printf("2. Statistics growing data\n" );
  printf("3. Work demonstration\n" );
  printf("4. Statistics same size data data\n" );
  printf("chose: ");
  scanf("%c", &programMode);
  while(programMode != '1' && programMode != '2'&& programMode != '3' && programMode != '4'){
    printf("Incorrect intput! \n");
    printf("choose: ");
    scanf("%c", &programMode);
  }
  printf("---------------------------------------------\n" );
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

if(arrayType == '1'){
  a = getRandomArray(arraySize, range);
}
else{
  a = generateRandomPermutation(arraySize);
}


if(programMode == '1'){
  printf("selection number: ");
  scanf("%d",&selectionNumber);
  aaa =copyArray(a, arraySize);


  printf("\n\ntest\n" );
  printf("-----------------------------------------------------------\n" );
  printf("[");
    for(int ii = 0; ii < arraySize; ii++){
      printf("%d, ",a[ii] );
    }
    printf("]\n");



  int x = random_selection(a, 0, arraySize -1, selectionNumber);

printf("\n\nRandom Selection\n" );
printf("-----------------------------------------------------------\n" );
printf("[");
  for(int ii = 0; ii < arraySize; ii++){
    if(ii == randomSelectionIndex){
      printf(RED "%d," RESET, a[ii]);
    }
    else{
      printf("%d, ",a[ii] );
    }
  }
  printf("]\n");

  quicksort(a, 0, arraySize -1);

  printf("[" );
    for(int ii = 0; ii < arraySize; ii++){
      if(ii == selectionNumber - 1){
        printf(RED "%d," RESET, a[ii]);
      }
      else{
        printf("%d, ",a[ii] );
      }
    }
    printf("]\n");


x = select(aaa, 0, arraySize -1, selectionNumber);
    printf("\n\n Selection\n" );
    printf("-----------------------------------------------------------\n" );
    printf("[");
      for(int ii = 0; ii < arraySize; ii++){
        if(ii == selectionIndex){
          printf(RED "%d," RESET, aaa[ii]);
        }
        else{
          printf("%d, ",aaa[ii] );
        }
      }
      printf("]\n");

      quicksort(aaa, 0, arraySize -1);

      printf("[" );
        for(int ii = 0; ii < arraySize; ii++){
          if(ii == selectionNumber - 1){
            printf(RED "%d," RESET, aaa[ii]);
          }
          else{
            printf("%d, ",aaa[ii] );
          }
        }
        printf("]\n");


  exit(1);
}

if(programMode == '3'){
  printf("selection number: ");
  scanf("%d",&selectionNumber);
  aaa =copyArray(a, arraySize);

  printf("\n\nRandom Selection\n" );
  printf("-----------------------------------------------------------\n" );
  random_selectionDemonstration(a, 0, arraySize -1, selectionNumber);



  printf("\n\n Selection\n" );
  printf("-----------------------------------------------------------\n" );

selectDemonstration(aaa, 0, arraySize -1, selectionNumber);
  exit(1);
}
  if(programMode == '4'){
    printf("test number: ");
    scanf("%d",&testNumber);

    Counter *randomSelectionCounter, *selectionCounter;
    randomSelectionCounter = new Counter[testNumber];
    selectionCounter = new Counter[testNumber];

    fp = fopen("test.csv", "w+");
    fprintf(fp, "Data size,random selection time,selection time,     ,\n");

    for(i = 0; i < testNumber; i++){
      if(arrayType == '1'){
        a = getRandomArray(arraySize, range);
      }
      else{
        a = generateRandomPermutation(arraySize);
      }
      // printArray(a, arraySize);

      fprintf(fp, "%d,",arraySize);
      k = rand() % arraySize;
      fprintf(fp, "%.10e,",getRandSelectTime(a, arraySize, k));
      fprintf(fp, "%.10e\n",getSelectTime(a, arraySize, k));
      // free(a);
      delete[] a;
      randomSelectionCounter[i].comparisonNumber = randomSelectionInfo.comparisonNumber;
      selectionCounter[i].comparisonNumber = selectionInfo.comparisonNumber;
      resetCounrers();
    }


    printf("\n\n" );

    // fp = fopen("test.csv", "w+");
    int randMax, randMin, randAvg, selectMax, selectMin, selectAvg;
    fprintf(fp, "Data size,Random selection comparison,Selection comparison\n");
    for(i = 0; i < testNumber; i++){
      fprintf(fp, "%d,%d,%d\n", arraySize, randomSelectionCounter[i].comparisonNumber, selectionCounter[i].comparisonNumber);
    }
     fclose(fp);

     printf("Random select minComparison = %d avgComparison = %d maxComparison = %d \n",findMinArrayElement(randomSelectionCounter, testNumber),getArrayAvg(randomSelectionCounter, testNumber),findMaxArrayElement(randomSelectionCounter, testNumber) );

    printf("select minComparison = %d avgComparison = %d maxComparison = %d \n",findMinArrayElement(selectionCounter, testNumber),getArrayAvg(selectionCounter, testNumber),findMaxArrayElement(selectionCounter, testNumber) );
     system("libreoffice --calc test.csv &");
    free(randomSelectionCounter);
    free(selectionCounter);
    exit(1);
  }

foo = arraySize / interval;
Counter *randomSelectionCounter, *selectionCounter;
randomSelectionCounter = new Counter[foo];
selectionCounter = new Counter[foo];

fp = fopen("test.csv", "w+");
fprintf(fp, "Data size,random selection time,selection time,     ,\n");

for(i = 1; i <= foo; i++){
  if(arrayType == '1'){
    a = getRandomArray(i * 100, range);
  }
  else{
    a = generateRandomPermutation(i * 100);
  }

  fprintf(fp, "%d,",i * interval);
  k = rand() % (i * interval);
  fprintf(fp, "%.10e,",getRandSelectTime(a, i * interval, k));
  fprintf(fp, "%.10e\n",getSelectTime(a, i * interval, k));
  free(a);
  randomSelectionCounter[i - 1].comparisonNumber = randomSelectionInfo.comparisonNumber;
  selectionCounter[i - 1].comparisonNumber = selectionInfo.comparisonNumber;
  resetCounrers();
}


printf("\n\n" );

// fp = fopen("test.csv", "w+");
fprintf(fp, "Data size,Random selection comparison,Selection comparison\n");
for(i = 0; i < foo; i++){
  fprintf(fp, "%d,%d,%d\n", (i + 1) * interval, randomSelectionCounter[i].comparisonNumber, selectionCounter[i].comparisonNumber);
}
 fclose(fp);

 system("libreoffice --calc test.csv &");
free(randomSelectionCounter);
free(selectionCounter);


  return 0;
}

int randomPartition(int *a, int p, int r){
  int pivotIndex = p + rand()% (r-p);
  swap(a, pivotIndex, p);
  int x = a[p], i = p, j, buffor;
  for(j = p + 1; j <= r; j++){
    randomSelectionInfo.comparisonNumber++;
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
    if(p == r){
      randomSelectionIndex = p;
        return arr[p];
    }


    if(k ==0){
      randomSelectionIndex = -1;
      return -1;
    }

    if(p < r)
    {

    int mid = randomPartition(arr, p, r);
    int i = mid - p + 1;
    if(i == k){
    randomSelectionIndex = mid;
    return arr[mid];
    }
    else if(k < i)
        return random_selection(arr, p, mid-1, k);
    else
        return random_selection(arr, mid+1, r, k-i);
    }

}

int select(int arr[], int l, int r, int k)
{
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1;

        int i, median[(n+4)/5];
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n)
        {
            median[i] = findMedian(arr+l+i*5, n%5);
            i++;
        }
        int medOfMed = (i == 1)? median[i-1]:
                                 select(median, 0, i-1, i/2);

        int pos = partition(arr, l, r, medOfMed);

        if (pos-l == k-1){
          selectionIndex = pos;
          return arr[pos];
        }
        if (pos-l > k-1)
            return select(arr, l, pos-1, k);

        return select(arr, pos+1, r, k-pos+l-1);
    }
    selectionIndex = INT_MAX;
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
      selectionInfo.comparisonNumber++;
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
    selectionInfo.comparisonNumber++;
    while((i >= 0) && (a[i] > key)){
      a[i + 1] = a[i];
      i--;
      selectionInfo.comparisonNumber++;
    }
    a[i + 1] = key;
  }
    return a;
}

void swap(int *A, int i, int j) {
   int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
}



void quicksort(int *a, int p, int r){
    int i = p, j = r, x, q = a[(p + r) / 2];
    do{
    while (a[i] < q){
      i++;
    }
    while (a[j] > q){
      j--;
    }
    if (i <= j){
      swap(a, i, j);
      i++; j--;
    }
    }while (i<=j);
    if (j > p){
      quicksort(a, p, j);
    }
    if (i < r){
      quicksort(a, i, r);
    }
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
  selectionInfo.comparisonNumber = 0;
  randomSelectionInfo.comparisonNumber = 0;
}

double getSelectTime(int *a, int n, int k){
  clock_t start = clock();
  clock_t end = clock();
  int *aa;
  double seconds;
  aa = copyArray(a, n);
  start = clock();
  select(aa, 0, n - 1, k);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  free(aa);
  return seconds;
}

double getRandSelectTime(int *a, int n, int k){
  clock_t start = clock();
  clock_t end = clock();
  int *aa;
  double seconds;
  aa = copyArray(a, n);
  start = clock();
  random_selection(aa, 0, n - 1, k);
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
  // srand(time(NULL));
  for(int j = 0; j < n; j++){
    index = rand() % n;
    swap(a, index, j);
  }
    return a;
}










int random_selectionDemonstration(int* arr, int p, int r, int k)
{
  printArray(arr + p, r - p + 1);
    if(p == r){
      printf("p == r    return value: %d\n", arr[p]);
        return arr[p];
    }


    if(k ==0){
      return -1;
    }

    if(p < r)
    {

    int mid = randomPartitionDemonstration(arr, p, r);
    int i = mid - p + 1;
    if(i == k){
      printf("%d smaller elements before pivot    return value: %d\n",k - 1,  arr[mid]);
    return arr[mid];
    }
    else if(k < i)
        return random_selectionDemonstration(arr, p, mid-1, k);
    else
        return random_selectionDemonstration(arr, mid+1, r, k-i);
    }

}

int randomPartitionDemonstration(int *a, int p, int r){
  // srand(time(NULL));
  int pivotIndex = p + rand()% (r-p);
  printf("pivot = %d\n",a[pivotIndex] );
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

void printArray(int * array, int size){

  int i;
  printf("[ ");
  for (i = 0; i < size; i++)
    printf("%d ", array[i]);
  printf("]\n");
}


int selectDemonstration(int arr[], int l, int r, int k)
{
    // If k is smaller than number of elements in array
    if (k > 0 && k <= r - l + 1)
    {
      printArray(arr + l, r - l + 1);
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
        printf("determine medians:\n");
        printArray(median, (n+4)/5);

        // Find median of all medians using recursive call.
        // If median[] has only one element, then no need
        // of recursive call
        int medOfMed = (i == 1)? median[i-1]:
                                 selectDemonstration(median, 0, i-1, i/2);

        printf("determine median of medians = %d\n", medOfMed );

        // Partition the array around a random element and
        // get position of pivot element in sorted array
        printf("pivot = %d\n",arr[medOfMed] );
        int pos = partition(arr, l, r, medOfMed);


        // If position is same as k
        if (pos-l == k-1){
          printf("return value = %d \n", arr[pos]);
          selectionIndex = pos;
          return arr[pos];
        }
        if (pos-l > k-1)  // If position is more, recur for left
            return selectDemonstration(arr, l, pos-1, k);

        // Else recur for right subarray
        return selectDemonstration(arr, pos+1, r, k-pos+l-1);
    }

    // If k is more than number of elements in array
    selectionIndex = INT_MAX;
    return INT_MAX;
}

int findMedianDemonstration(int arr[], int n)
{
    // sort(arr, arr+n);  // Sort the array
    insertionSort(arr, n);
    return arr[n/2];   // Return middle element
}

int findMinArrayElement(Counter *a, int n){
  int i, min;
  min = a[0].comparisonNumber;
  for(i = 0; i < n; i++){
  if(a[i].comparisonNumber < min){
    min = a[i].comparisonNumber;
  }
  }
  return min;
}

int findMaxArrayElement(Counter *a, int n){
  int i, max;
  max = a[0].comparisonNumber;
  for(i = 0; i < n; i++){
  if(a[i].comparisonNumber > max){
    max = a[i].comparisonNumber;
  }
  }
  return max;
}

int getArrayAvg(Counter *a, int n){
  int sum = 0, i;
  for(i = 0; i < n; i++){
    sum += a[i].comparisonNumber;
  }
  return sum / n;
}
