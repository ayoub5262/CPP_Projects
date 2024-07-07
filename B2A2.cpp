#include <cassert>
#include <chrono>
#include <iostream>
using namespace std;

class B2A2 {
 public:
  int compare_cnt = 0;  // Zähler für die Vergleiche während des sortierens.

  /**
   * Führt den Merge-Sort-Algorithmus aus.
   *
   * @param numbers das zu sortierende Array
   */
  void mergeSort(int arr[], int n) {
    int* tmpArray = new int[n];
    std::copy(arr, arr + n, tmpArray);
    mergeSort(arr, tmpArray, 0, n);
    delete[] tmpArray;
  }
  /**
   * Hilfsfunktion, welche die rekursiven Aufrufe ausführt.
   *
   * @param target Zielarray für die sortierte Folge
   * @param source ein zu sortierendes Array mit Integer Zahlen
   * @param left   die linke Grenze des zu sortierenden Teilarrays, inklusiv
   * @param right  die rechte Grenze des zu sortierenden Teilarrays, exklusiv
   */
  void mergeSort(int target[], int source[], int left, int right) {
    // Basisfall: Wenn die Größe des zu sortierenden Bereichs 1 oder weniger ist, ist er bereits sortiert.
    if (right - left <= 1) return; 
    // Berechne die Mitte des Arrays.
    int mid = left + (right - left) / 2;
    // Sortiere die linke Hälfte des Arrays rekursiv.
    mergeSort(source, target, left, mid);
    // Sortiere die rechte Hälfte des Arrays rekursiv.
    mergeSort(source, target, mid, right);
    
    // Führe die Merge-Operation durch, um die beiden sortierten Hälften zu vereinen.
    int i = left;
    int j = mid;
    int k = left;
    
    // Vergleiche die Elemente der beiden Hälften und füge das kleinere in das Zielarray ein.
    while (i < mid && j < right) {
      if (source[i] <= source[j]) {
        target[k++] = source[i++];
      } else {
        target[k++] = source[j++];
      }
      // Zähle die Anzahl der Vergleiche
      compare_cnt++;
    }
    // Füge die restlichen Elemente der linken Hälfte in das Zielarray ein.
    while (i < mid) {
      target[k++] = source[i++];
    }
    // Füge die restlichen Elemente der rechten Hälfte in das Zielarray ein.
    while (j < right) {
      target[k++] = source[j++];
    }
    // Kopiere die sortierten Elemente zurück in das ursprüngliche Array.
    for (int l = left; l < right; ++l) {
      source[l] = target[l];
    }
  }
  
  bool isSorted(const int array[], int n) {
    for(int i=0;i<n-1;++i){
     if(array[i] > array[i+1]) return false; // Falls ein Zahl ist goesser als naechster Zahl => Array nicht sortiert
     }
     return true;  
  }
};

int main(int argc, char* argv[]) {
  B2A2 sorter;//Objekt von class B2A2 erstellen
  int size;
  // Überprüfen, ob Befehlszeilenargumente vorhanden sind, um die Größe des Arrays zu erhalten oder von der Standardeingabe
  if (argc > 1) size = argc - 2;
  else cin >> size;
  // Dynamische Speicherreservierung für das Array
  int* arr = new int[size];
  // Eingabe der Arrayelemente entweder aus Befehlszeilenargumenten oder von der Standardeingabe
  if(argc > 1){
    for (int i = 0; i < size; ++i){
      arr[i] = atoi(argv[i+2]);
    }
  }else{
    for (int i = 0; i < size; ++i) {
    cin >> arr[i];
    }
  }
  // Dynamische Speicherreservierung für ein temporäres Array und Kopieren des ursprünglichen Arrays
  int* tmpArray = new int[size];
  copy(arr, arr + size, tmpArray);
  
  auto start = chrono::steady_clock::now();// Beginn der Messung der Laufzeit
  sorter.mergeSort(arr, size);             // Das Array sortieren
  auto finish = chrono::steady_clock::now();// Ende der Messung der Laufzeit
  auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();// Laufzeit rechnen
  
  // Falls das Array nicht sortiert ist Fehler melden
  if (!sorter.isSorted(arr, size)){
    cerr << "FEHLER: Feld ist NICHT sortiert!" << endl;
  delete[] arr;      // Speicher freigeben
  delete[] tmpArray; // Speicher freigeben
  assert(false);  // Programm beenden
  }
  if (size <= 100){              // Das unsortierte Array ausgeben
    for (int i = 0; i < size; i++)  
      cout << tmpArray[i] << " ";
    cout << endl << endl;
  }
  delete[] tmpArray; // Speicher freigeben 

  if (size <= 100){            // Das sortierte Array ausgeben
  for (int i = 0; i < size; ++i) {
    cout << arr[i] << " ";
  }
  cout << endl;
  }
  cout << "Feld ist sortiert! in " << duration << " microsekunden"<< endl;
  cout << "Das Sortieren des Arrays hat " << sorter.compare_cnt << " Vergleiche benoetigt." << endl;
  
  delete[] arr; // Speicher freigeben 
  return 0;
}

