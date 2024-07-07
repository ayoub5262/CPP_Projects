#include <cassert>
#include <chrono>
#include <iostream>
using namespace std;

int compare_cnt = 0;
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
        compare_cnt++;
    }
     while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void iterativeMergeSort(int arr[], int n) {
   int curr_size; 
   int left_start;
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
   {
       for (left_start=0; left_start<n-1; left_start += 2*curr_size)
       {
           int mid = min(left_start + curr_size - 1, n-1);
 
           int right_end = min(left_start + 2*curr_size - 1, n-1);
 
           merge(arr, left_start, mid, right_end);
       }
   }
}
bool isSorted(const int array[], int n) {
    for(int i=0;i<n-1;++i){
     if(array[i] > array[i+1]) return false;
     }
     return true;  
}

int main(int argc, char* argv[]) {
  int size;
  if (argc > 1) size = argc - 2;
  else cin >> size;
  int* arr = new int[size];
  if(argc > 1){
    for (int i = 0; i < size; ++i)
      arr[i] = atoi(argv[i+2]);
  }else{
    for (int i = 0; i < size; ++i) 
        cin >> arr[i];
  }
  int* tmpArray = new int[size];
  copy(arr, arr + size, tmpArray);
  
  auto start = chrono::steady_clock::now();
  iterativeMergeSort(arr, size);             
  auto finish = chrono::steady_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
  
  if (!isSorted(arr, size)){
    cerr << "FEHLER: Feld ist NICHT sortiert!" << endl;
    delete[] arr;     
    delete[] tmpArray; 
    assert(false); 
  }
  if (size <= 100){             
    for (int i = 0; i < size; i++)  
      cout << tmpArray[i] << " ";
    cout << endl << endl;
  }
  delete[] tmpArray;

  if (size <= 100){            
    for (int i = 0; i < size; ++i) 
        cout << arr[i] << " ";
  cout << endl;
  }
  cout << "Feld ist sortiert! in " << duration << " microsekunden"<< endl;
  cout << "Das Sortieren des Arrays hat " << compare_cnt << " Vergleiche benoetigt." << endl;
  
  delete[] arr;  
  return 0;
}