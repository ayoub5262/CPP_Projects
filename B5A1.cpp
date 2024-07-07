#include <cassert>
#include <chrono>
#include <iostream>
// test if the data[l,r] is partitioned with pivotelement p at position m.
// data[i] >=p for i < m
// data[i] <= p for j > m
bool isPartitioned(int data[], int l, int r, int m, int p) {
  /**********************************************************/
  /****                Kurzaufgabe 5.1:                 ****/
  for (int i = l; i <= m; i++) {  
    // Überprüft, ob die Elemente links vom Pivot kleiner oder gleich p sind
    if (data[i] < p)
     // Wenn ein Element links vom Pivot kleiner als p ist, ist der Bereich nicht partitioniert
      return false;                
  }
  for (int i = m + 1; i <= r; i++) { 
    // Überprüft, ob die Elemente rechts vom Pivot größer oder gleich p sind
    if (data[i] > p)
     // Wenn ein Element rechts vom Pivot größer als p ist, ist der Bereich nicht partitioniert
      return false;  
  }
  /**********************************************************/
  return true;
}
// l,r inclusive -> partition data[l,r]
int partition(int data[], int l, int r) {
  /**********************************************************/
  /****                Kurzaufgabe 5.1:                 ****/
  int pivot = data[l];  // Wählt das erste Element als Pivot
  int i = l + 1;
  // Durchläuft das Array und verschiebt Elemente größer als der Pivot nach rechts
  for (int j = l + 1; j <= r; j++) { 
    if (data[j] > pivot) {
      std::swap(data[j],data[i]);  // Tauscht Elemente, wenn sie größer als der Pivot sind
      i++;
    }
  }
  std::swap(data[l],data[i - 1]);  // Platziert den Pivot an die richtige Position
  
  return i - 1;            // Gibt die Position des Pivot-Elements zurück
  /**********************************************************/
}
// l,r inclusive -> sort data[l,r]
void qsort(int data[], int l, int r) {
  /**********************************************************/
  /****                Kurzaufgabe 5.1:                 ****/
  if (l < r) {  // Führt Quicksort nur aus, wenn der linke Index kleiner als der rechte ist
    int m = partition(data, l, r);  // Führt die Partitionierung durch
    assert(isPartitioned(data, l, r, m, data[m]));
    // Sortiert die Teile links und rechts vom Pivot rekursiv
    qsort(data, l, m - 1);
    qsort(data, m + 1, r);
  }
    /**********************************************************/
}

// check if the array sorted discreading.
bool isSorted(const int data[], int size) {
  /**********************************************************/
  /****                Kurzaufgabe 5.3:                 ****/
  // Überprüft, ob jedes Element kleiner oder gleich dem nächsten ist
  for (int i = 1; i < size; i++) {
    // Wenn ein Element größer als das nächste ist, ist das Array nicht sortiert
    if (data[i - 1] < data[i])
      return false;
  }
  return true;  // Das Array ist sortiert

  /**********************************************************/
}

int main() {
  int n;
  std::cin >> n;

  int *arr = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  if (n < 20) {
    std::cout << "Input Array:\n";
    for (int i = 0; i < n; i++) {
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
  }

  /**********************************************************/
  /****            Kurzaufgabe 5.1 & 5.3 & 5.4:          ****/
  auto start = std::chrono::high_resolution_clock::now();
  qsort(arr, 0, n - 1);  // Sortiert das Array mit Quicksort
  auto end = std::chrono::high_resolution_clock::now();
  // Berechne die Dauer der Sortierung
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

  assert(isSorted(arr, n)); // Überprüfe, ob das Array korrekt sortiert ist

  if (n < 20){
  std::cout << "After Sorting (descending):\n"; 
  for (int i = 0; i < n; i++) 
    std::cout << arr[i] << (i < n - 1 ? ", " : "");
  std::cout << std::endl;
  }

  std::cout << "Time taken by qsort: " << duration << " microseconds\n";
  delete[] arr;
  /**********************************************************/
  return 0;
}
