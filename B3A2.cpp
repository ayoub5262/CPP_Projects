#include <algorithm>
#include <iostream>
  /**********************************************************/
  /****                 Kurzaufgabe 3.2:                 ****/
// Anstatt die Faktorielle Funktion in jeder Iteration neu zu berechnen
// können Wir die Faktoriellen Werte in einem Array speichern und bei Bedarf darauf zugreifen
int* factorial;// Globale Zeiger auf int Array deklarieren 
void precomputeFactorial(int n) { 
    factorial = new int[n];
    factorial[0] = 1;
    for(int i = 1; i < n; i++) {
        factorial[i] = i * factorial[i - 1];
    }
}

void kthPermutation(int* arr, int size, int k) {
    precomputeFactorial(size);
    while(size > 0) {
        int f = factorial[size - 1]; // Anzahl der Permutationen (n-1)! bsp: 3! = 6 

        int pos = k / f;   // Positon des ersten Element von der Pertation bsp: pos = 16/6 = 2

        k %= f; // k fuer naechste iteration aktualisieren bsp 16 % 6 = 4

        std::cout << arr[pos] << ( size > 1 ? ", " : ""); // Erste Element der Permutation ausgeben 

        for(int i = pos; i < size-1; i++)
            arr[i] = arr[i+1];// Ausgegebene Element aus dem Array entfernen und der Rest nach links verschieben

        size--; // Size dekrementieren da wir ein Element geloescht haben
    }
    std::cout << std::endl;
    delete[] factorial;
}
  /**********************************************************/
int main(int argc, char* argv[]) {
        int k = std::stoi(argv[1]);
        int n;
        std::cin >> n;

        int* arr = new int[n];
        for (int i = 0; i < n; i++) {
            std::cin >> arr[i];
        }

  /**********************************************************/
  /****                 Kurzaufgabe 3.2:                 ****/

    std::sort(arr, arr + n);
    std::cout << "Sorted Input: \n";

    for(int i = 0; i < n; i++)
        std::cout<< arr[i]<< (i < n - 1 ? ", " : "");

    std::cout<<std::endl;
    
    std::cout<<"The "<< k <<"-smallest permutation is: \n";

    kthPermutation(arr, n, k - 1);// k - 1 da unsere index mit 0 anfaengt (es gibt keine 0-smallest Permutation)
    delete[] arr;
    return 0;
  /**********************************************************/
}

