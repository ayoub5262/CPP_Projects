#include <algorithm>
#include <iostream>
using namespace std;

int printPermutations(int data[], int size, int d) {
  if (d == size) { // Keine Permutation Notwendig
    for (int i = 0; i < size; ++i) { // Print the Array without modification
      cout << data[i] << " ";
    }
  cout << endl;
  return 1;
  }
  int count = 0; // Initilisierung des Permutationen Nummern
  for (int i = d; i < size; ++i) {
    swap(data[i], data[d]); // Tausche die Elemente an den Positionen d und i
    count += printPermutations(data, size, d + 1); // Rekursive Aufruf mit dem nächsten Index d erhöht um 1
    swap(data[i], data[d]); // Rücktausch zu dem ursprünglichen Zustand
  }
  return count;
}

int main() {
  int n;
  cout << "enter the size of the array :"<< std::endl; // Größe des Arrays eingeben
  cin >> n; // Größe einlesen
  int *data = new int[n]; // Speicher Allokieren
  cout << "enter the elements of the array :"<< endl;
  for (int i = 0; i < n; ++i) {
    cin >> data[i]; // Jede Elemente einlesen
  }
  int count = printPermutations(data, n, 0); 
  cout << "There are " // Mögliche Permutationen drucken
  << printPermutations(data, n, 0)
  << " permutations of the input." << endl;
  delete[] data;
  return 0;
}
