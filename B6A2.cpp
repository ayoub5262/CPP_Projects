#include <iostream>
#include <algorithm>

int getByte(int value, int b)
{
  /**********************************************************/
  /****                Longaufgabe 6.2:                 ****/
  return (value >> (8 * b)) & 0xFF;
  /**********************************************************/
}

void sortByByte(int input[], int l, int r, int b)
{
  /**********************************************************/
  /****                Longaufgabe 6.2:                 ****/
  const int range = 256; // 256 mögliche Werte für ein Byte
  int count[range] = {0};
  int size = r - l + 1;
  int *output = new int[size];

  // Frequenzarray für das b-niederwertigste Byte aufbauen
  for (int i = l; i <= r; ++i) 
    count[getByte(input[i], b)]++;

  // Kumulierte Frequenzen berechnen (für stabile Sortierung absteigend)
  for (int i = range - 2; i >= 0; --i)
    count[i] += count[i + 1];

  // Das Array stabil sortieren basierend auf dem b-niederwertigsten Byte
  for (int i = r; i >= l; --i) {
      int byteValue = getByte(input[i], b);
      output[count[byteValue] - 1] = input[i];
      count[byteValue]--;
  }

  // Das sortierte Ergebnis zurück ins input-Array kopieren
  for (int i = 0; i < size; ++i) 
      input[l + i] = output[i];
    
  delete[] output;
  /**********************************************************/
}

void radix(int data[], int size)
{
  /**********************************************************/
  /****                Longaufgabe 6.2:                 ****/
  for (int b = 0; b < 4; ++b) 
    sortByByte(data, 0, size - 1, b);
  /**********************************************************/
}

int main()
{
  int n;
  std::cin >> n;

  int *arr = new int[n];
  for (int i = 0; i < n; i++)
    std::cin >> arr[i];

  std::cout << "Input Array: [";
  for (int i = 0; i < n; i++)
    std::cout << arr[i] << (i < n - 1 ? ", " : "]\n");

  radix(arr, n);

  std::cout << "After Sorting: [";
  for (int i = 0; i < n; i++)
    std::cout << arr[i] << (i < n - 1 ? ", " : "]\n");

  delete[] arr;
  return 0;
}
