#include <iostream>
#include <algorithm>
using namespace std;
int removeDuplicates(int data[], int n) {
    /**********************************************************/
    /**** Kurzaufgabe 3.1: ****/
    if (n <= 1)
        return n; // Wenn das Array leer oder nur ein Element hat, gibt es keine Duplikate zu entfernen

    std::sort(data, data + n); // Array sortieren, um Duplikate zu finden und zu entfernen

    int index = 0; // Index zum Speichern der Position der nicht duplizierten Elemente

    for (int i = 0; i < n; i++) {
        if (i == 0 || data[i] != data[i - 1]) 
            // Wenn das aktuelle Element nicht gleich dem vorherigen ist, kopiere es an die "index"-Position
            data[index++] = data[i]; 
        
    }
    /**********************************************************/
    return index; // Rückgabe der neuen Größe des Arrays nach dem Entfernen von Duplikaten
}

int main(int argc, char* argv[]) {
    int n;
    std::cin >> n;

    // Initialize the vector and allocate the right size
    int *array = new int[n];

    // Eingabe in vector schreiben
    for (int i = 0; i < n; i++) {
    int value;
    std::cin >> value;

    array[i] = value;
    }

    int k = std::stoi(argv[1]);
    std::cout << "Before removing duplicates: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    int distinct = removeDuplicates(array, n);
    /**********************************************************/
    /**** Kurzaufgabe 3.1: ****/
    std::cout << "After removing duplicates: ";
    for (int i = 0; i < distinct; i++) 
        std::cout << array[i] << (i < distinct - 1 ? ", " : "");
    std::cout << std::endl;

    if (k > distinct) k = distinct; // Falls distinct < k, ersetzen wir k durch distinct
    int *subset = new int[k];// Speicher für das Subset-Array reservieren
    int subset_cnt = 0;// Initialisieren Sie die Anzahl der Subsets

    // Definieren wir eine Lambda-Funktion, um alle Subsets der Größe k auszugeben
    auto printSubsets = [&](auto self, int start, int end, int idx) {
        // Wenn das Subset k Elemente hat, geben Sie es aus und erhöhen Sie die Anzahl der Subsets
        if (idx == k) {
            for (int j = 0; j < k; j++)
                std::cout << subset[j] << (j < k - 1 ? ", " : "");
            std::cout << std::endl;
            subset_cnt++;
            return;
        }
        // Für jedes Element im Array, wenn es im Subset enthalten sein kann, tun Sie dies und rufen Sie die Funktion rekursiv für das nächste Element auf
        for (int i = start; i <= end && end - i >= k - idx; i++) {
            subset[idx] = array[i];
            self(self, i + 1, end, idx + 1);
        }
    };
    // Rufen Sie die Funktion auf, um alle Subsets der Größe k auszugeben
    printSubsets(printSubsets, 0, distinct, 0);

    // Geben Sie die Gesamtzahl der Subsets aus
    std::cout << "Anzahl der Subsets: "<< subset_cnt << std::endl;

    delete[] array; //Speicher freigeben
    delete[] subset;

    return 0;
    /**********************************************************/
}
