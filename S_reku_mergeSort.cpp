#include <cassert>
#include <chrono>
#include <iostream>
using namespace std;

int compare_cnt = 0;
void merge(int arr[], int l, int m ,int r){
    int* tmp = new int[r-l+1];
    int i = l, k = 0, j = m + 1;
    while (i <= m && j <= r){
        if (arr[i] < arr[j])
            tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
        compare_cnt ++;
    }
    while (i <= m) tmp[k++] = arr[i++];
    while (j <= r) tmp[k++] = arr[j++];
    for (int n = l; n <= r; n++)
        arr[n] = tmp[n-l];
    delete [] tmp;
}
void mergeSort(int arr[], int l, int r){
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);
    merge(arr, l, m, r);
}
bool isSorted(const int array[], int n) {
    for(int i = 0; i < n - 1; ++i){
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
  mergeSort(arr, 0, size-1);             
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