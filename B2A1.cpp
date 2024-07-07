#include <cassert>
#include <chrono>
#include <iostream>
using namespace std;

class B2A1 {
 public:
  int compare_cnt;  // Zähler für die Vergleiche während des sortierens.
  /**
   * Prüft, ob ein Array von Große n aufsteigend sortiert ist.
   *
   * @param array Array die sortierd wird
   * @param n  Linke Grenze des zu prüfenden Bereichs
   * @return true genau dann, wenn das Array sortiert ist
   */
  bool isSorted(const int array[], int n) {
    /**********************************************************/
    /****                 Kurzaufgabe 2.1:                 ****/
    for(int i=0;i<n-1;++i){
     if(array[i] > array[i+1]) return false; // Falls ein Zahl ist goesser als naechster Zahl => Array nicht sortiert  
     }
     return true;  
    }
    /**********************************************************/
  /**
   * Insertion-Sort-Algorithmus.
   *
   * @param numbers das zu sortierende Array
   * @param size: Groesse des Array numbers
   */
  void insertionSort(int numbers[], int size) {
    /**********************************************************/
    /****                 Kurzaufgabe 2.1:                 ****/
    compare_cnt = 0; // Setze den Zähler für Vergleiche auf 0
    for (int i = 1; i < size; ++i){ // Beginne mit dem zweiten Element (Index 1)
        int key = numbers[i]; // Speichere das aktuelle Element, das sortiert werden soll
        int j = i - 1;        // Initialisiere den Index j auf den Vorgänger des aktuellen Index i
        // Durchlaufe die Elemente von rechts nach links und vergleiche sie mit dem Schlüssel
        while(( j >= 0) && (numbers[j] > key)){ 
            // Verschiebe jedes Element, das größer als der Schlüssel ist, um eine Position nach rechts
            numbers[j + 1] = numbers[j];
            --j; // Reduziere den Index j, um die nächste Position zu überprüfen
            ++compare_cnt; // Inkrementiere den Zähler für Vergleiche
        }
        // Setze das aktuelle Element an die richtige Position im sortierten Bereich
        numbers[j + 1] = key;
    }
    /**********************************************************/
  }
};

int main(int argc, char* argv[]) {
  /**********************************************************/
  /****                 Kurzaufgabe 2.1:                 ****/
  B2A1 sorter;//Objekt von class B2A1 erstellen
  int size;
  // Überprüfen, ob Befehlszeilenargumente vorhanden sind, um die Größe des Arrays zu erhalten oder von der Standardeingabe
  if (argc > 1) size = argc - 1;
  else cin >> size;
  // Dynamische Speicherreservierung für das Array
  int* arr = new int[size];
  // Eingabe der Arrayelemente entweder aus Befehlszeilenargumenten oder von der Standardeingabe
  if(argc > 1){
    for (int i = 0; i < size; ++i){
      arr[i] = atoi(argv[i+1]);
    }
  }else{
    for (int i = 0; i < size; ++i) {
    cin >> arr[i];
    }
  }
  // Dynamische Speicherreservierung für ein temporäres Array und Kopieren des unsortierten Arrays für später ausgeben
  int* tmpArray = new int[size];    
  copy(arr, arr + size, tmpArray);

  auto start = chrono::steady_clock::now(); // Beginn der Messung der Laufzeit
  sorter.insertionSort(arr, size);          // Das Array sortieren
  auto finish = chrono::steady_clock::now();   // Ende der Messung der Laufzeit
  auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count(); // Laufzeit rechnen

  // Falls das Array nicht sorted ist Fehler melden
  if (!sorter.isSorted(arr, size)){
    cerr << "FEHLER: Feld ist NICHT sortiert!" << endl;
  delete[] arr;      // Speicher freigeben 
  delete[] tmpArray; // Speicher freigeben 
  assert(false); // Programm beenden
  }
// Das sortierte Array ausgeben mit 100 als Grenze fuer n
  if (size <= 100){
  for (int i = 0; i < size; i++)  // Das unsortierte Array ausgeben
     cout << tmpArray[i] << " ";
  cout << endl << endl;
  }
  delete[] tmpArray;// Speicher freigeben 

  if (size <= 100) {                  // Das sortierte Array ausgeben
    for (int i = 0; i < size; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }
  cout << "Feld ist sortiert! in " << duration << " microsekunden"<< endl;
  cout << "Das Sortieren des Arrays hat " << sorter.compare_cnt << " Vergleiche benoetigt." << endl;

  delete[] arr; // Speicher freigeben 
  /**********************************************************/
  return 0;
}