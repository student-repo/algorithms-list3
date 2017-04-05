#include<stdio.h>

void swap(int *A, int i, int j);
// int random_partition(int* arr, int start, int end);
// int random_partition(int* arr, int start, int end);
int random_selection(int* arr, int p, int r, int k);
void quicksort(int *a, int p, int r);
int randomPartition(int *a, int p, int r);

int main(){

  int A[] = {9,5,7,1,10,2,3};
  int loc = random_selection(A, 0,6,5);
  printf("%d\n",loc );
  // quicksort(A, 0, 6);
  // int i;
  // for(i = 0; i < 7; i++){
  //   printf("%d, ",A[i] );
  // }
  // printf("\n" );

  return 0;
}

void swap(int *A, int i, int j) {
   int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
}

int randomPartition(int *a, int p, int r){
  srand(time(NULL));
  int pivotIndex = p + rand()% (r-p);
  swap(a, pivotIndex, p);
  int x = a[p], i = p, j, buffor;
  printf("pivotid = %d   p = %d   r = %d\n", pivotIndex, p ,r );
  for(j = p + 1; j <= r; j++){
    if(a[j] <= x){
      i = i + 1;
      swap(a, i, j);
    }
  }
  swap(a, i, p);
  return i;
}

void quicksort(int *a, int p, int r){
  int q;
  if(p < r){
    q = randomPartition(a, p, r);
    quicksort(a, p, q - 1);
    quicksort(a, q + 1, r);
  }
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
