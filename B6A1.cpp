#include <iostream>
#include <algorithm>
#include <cassert>

int getMin(const int data[], int size)
{
  /**********************************************************/
  /****                Langaufgabe 6.1:                 ****/
  int min = data[0];
  for (int i = 1; i < size; ++i) {
    if (data[i] < min)
      min = data[i];
  }
  /**********************************************************/
  return min;
}

int getMax(const int data[], int size)
{
  /**********************************************************/
  /****                Langaufgabe 6.1:                 ****/
  int max = data[0];
  for (int i = 1; i < size; ++i) {
    if (data[i] > max)
      max = data[i];
  }
  /**********************************************************/
  return max;
}

int *count(const int data[], int size, int min, int max)
{
  /**********************************************************/
  /****                Langaufgabe 6.1:                 ****/
  int *Frequency = new int[max - min + 1]();
  for (int i = 0; i < size; ++i) 
    // Für jede Zahl in den Daten, erhöhe das entsprechende Element in Frequency
    Frequency[data[i] - min]++;

  return Frequency;
  /**********************************************************/
}

int *countingSort(const int data[], int size)
{
  /**********************************************************/
  /****                Langaufgabe 6.1:                 ****/
  int min = getMin(data, size);
  int max = getMax(data, size);
  int range = max - min + 1;
  int *Frequency = count(data, size, min, max);

  int *Sorted = new int[size];
  int index = 0;

  for (int i = range - 1; i >= 0; --i) {
    // Für jede Zahl i + min, fügen Sie sie so oft in B ein, wie sie in den Daten vorkommt
    while (Frequency[i] > 0) {
      Sorted[index++] = i + min;
      Frequency[i]--;
      }
    }
  delete[] Frequency;
  return Sorted;
  /**********************************************************/
}

int main()
{
  int n;
  std::cin >> n;
  assert(n > 0);
  int *arr = new int[n];
  for (int i = 0; i < n; i++)
    std::cin >> arr[i];

  std::cout << "Input Array: [";
  for (int i = 0; i < n; i++)
    std::cout << arr[i] << (i < n - 1 ? ", " : "]\n");
  
  int min = getMin(arr, n);
  std::cout << "The minimum value: " << min << std::endl;

  int max = getMax(arr, n);
  std::cout << "The maximum value: " << max << std::endl;

  int *count_arr = count(arr, n, min, max);
  if (max - min < 20){
    std::cout << "Frequencies: [";
    for (int i = 0; i < max - min + 1; i++)
      std::cout << count_arr[i] << (i < max-min ? ", " : "]\n");
  }
  
  int *output = countingSort(arr, n);
  std::cout << "After sorting: [";
  for (int i = 0; i < n; i++)
    std::cout << output[i] << (i < n - 1 ? ", " : "]\n");
  
  delete[] arr;
  delete[] count_arr;
  delete[] output;
  return 0;
}
