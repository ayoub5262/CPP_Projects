#include <chrono>
#include <iostream>
#include <utility>
#include <cassert>
// test if the data[l,r] is partitioned with pivotelement p1 at position m1, p2
// at m2.
// m1 <= m2 and p1 >= p2
// data[i] >=p1 for l<=i < m1
// p2<=data[i] <= p1 for m1 < p < m2
// data[i] <= p2 for m2 < p <=r
bool isPartitioned(int data[], int l, int r, int m1, int p1, int m2, int p2) {
  /**********************************************************/
  /****                Kurzaufgabe 5.2:                 ****/
     // Überprüft den ersten Bereich: Alle Elemente links von m1 müssen größer oder gleich p1 sein.
    for (int i = l; i < m1; i++) {
        if (data[i] < p1) return false;// Wenn ein Element kleiner als p1 ist, ist die Partitionierung falsch.
    }
     // Überprüft den zweiten Bereich: Alle Elemente zwischen m1 und m2 müssen zwischen p2 und p1 liegen.
    for (int i = m1; i < m2; i++) {
        if (data[i] < p2 || data[i] > p1) return false; // Wenn ein Element kleiner als p2 oder größer als p1 ist, ist die Partitionierung falsch
    }
     // Überprüft den dritten Bereich: Alle Elemente rechts von m2 müssen kleiner oder gleich p2 sein
    for (int i = m2; i <= r; i++) {
        if (data[i] > p2) return false;// Wenn ein Element größer als p2 ist, ist die Partitionierung falsch
    }
  /**********************************************************/
  return true;
}

std::pair<int, int> partition(int data[], int l, int r) {
  /**********************************************************/
  /****                Kurzaufgabe 5.2:                 ****/
    if (data[l] < data[r]) std::swap(data[l], data[r]); // Stellt sicher, dass p1 <= p2
    int p1 = data[l];  // Wählt das erste Element des Teilarrays als das erste Pivot-Element 
    int p2 = data[r];  // Wählt das letzte Element des Teilarrays als das zweite Pivot-Element 
    int m1 = l + 1;    // Index für das Ende des ersten Teils
    int m2 = r - 1;    // Index für den Anfang des dritten Teils
    int i = l + 1;     // Index für das aktuelle Element
    while (i <= m2) {
        if (data[i] > p1) {
            std::swap(data[i], data[m1]);
            m1++;
            i++;
        } else if (data[i] < p2) {
            std::swap(data[i], data[m2]);
            m2--;
        } else {
            i++;
        }
    }
    std::swap(data[l], data[m1 - 1]);  // Setzt p1 an die richtige Stelle
    std::swap(data[r], data[m2 + 1]);  // Setzt p2 an die richtige Stelle
    return std::make_pair(m1 - 1, m2 + 1);  // Gibt ein Paar von Indizes zurück, die die Positionen der beiden Pivot-Elemente im sortierten Array darstellen
  /**********************************************************/
}

void qsort(int data[], int l, int r) {
  /**********************************************************/
  /****                Kurzaufgabe 5.2:                 ****/
   if (l < r) {
        // Partitioniert das Array
        auto pivotPositions = partition(data, l, r);
        int m1 = pivotPositions.first;
        int m2 = pivotPositions.second;

        // Überprüft die Invarianten nach der Partitionierung
        assert(isPartitioned(data, l, r, m1, data[m1], m2, data[m2]));

        // Rekursiv sortiert die Teile links und rechts von den Pivot-Elementen
        qsort(data, l, m1-1);
        qsort(data, m1 + 1, m2-1);
        qsort(data, m2 + 1, r);
    }
  /**********************************************************/
}
bool isSorted(int data[], int size) {
    // Überprüft, ob das Array absteigend sortiert ist
    for (int i = 1; i < size; i++) {
        if (data[i-1] < data[i]) return false ;
    }
    return true  ;
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
    std::cout << "\n";
  }

  /**********************************************************/
  /****                Kurzaufgabe 5.2:                 ****/
  // Starte die Zeitmessung
  auto start = std::chrono::high_resolution_clock::now();
  // Sortiert das Array
  qsort(arr, 0, n - 1);
  // Beende die Zeitmessung
  auto end = std::chrono::high_resolution_clock::now();

  // Berechne die Laufzeit
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

  // Überprüft, ob das Array korrekt sortiert ist
  assert(isSorted(arr, n)); 
  
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
