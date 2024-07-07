#include <iostream>
#include <random>

// Hilfsfunktion zum Vertauschen zweier Werte
void swap(int data[], int i, int j)
{
    int h = data[i];
    data[i] = data[j];
    data[j] = h;
}

// Hilfsfunktion zum Berechnen von n!
int fact(int n)
{
    int fact = 1;
    for (int i = 2; i <= n; i++)
    {
        fact = fact * i;
    }
    return fact;
}

void updatePermutation(int numbers[], int counters[], int n)
{
    /**********************************************************/
    /****                Langaufgabe 4.2:                  ****/
    int i = 0; // Initialisieren Wir i mit 0
    while (i < n) { // Solange i kleiner als n ist
        if (counters[i] < i) { // Wenn der Zähler an der Position i kleiner als i ist
            if (i % 2 == 0)  // Wenn i gerade ist
                // Tauschen Wir das Element an der Position 0 mit dem Element an der Position i
                swap(numbers, 0, i); 
            else // Wenn i ungerade ist
                // Tauschen Wir das Element an der Position des Zählers[i] mit dem Element an der Position i
                swap(numbers, counters[i], i); 
            
            counters[i]++; // Inkrementieren Wir den Zähler an der Position i
            return; // Beenden Wir die Funktion
        } else { // Wenn der Zähler an der Position i größer oder gleich i ist
            counters[i] = 0; // Setzen Wir den Zähler an der Position i auf 0
            i++; // Inkrementieren Wir i
        }
    }
    /**********************************************************/
}

void shufflePermutation(int numbers[], int n)
{
    /**********************************************************/
    /****                Langaufgabe 4.2:                  ****/
    for (int i = 0; i < n; i++) { // Für jedes Element im Array
        // Generieren Wir eine zufällige Zahl j im Bereich von i bis n-1
        int j = i + std::rand() % (n - i);
        // Tauschen Wir das Element an der Position i mit dem Element an der Position j 
        swap(numbers, i, j); 
    }
    /**********************************************************/
}

int insertionSort(int numbers[], int n)
{
    /**********************************************************/
    /****                Langaufgabe 4.2:                  ****/

    int shifts = 0; // InitialiWirren Wir die Anzahl der Verschiebungen mit 0
    for (int i = 1; i < n; i++) { // Für jedes Element im Array (außer dem ersten)
        int key = numbers[i]; // Speichern Wir den Wert des aktuellen Elements in einer Variablen "key"
        int j = i - 1; // InitialiWirren Wir j mit dem Index des vorherigen Elements
        while (j >= 0 && numbers[j] > key) { // Solange j größer oder gleich 0 ist und das Element an der Position j größer als "key" ist
            numbers[j + 1] = numbers[j]; // Verschieben Wir das Element an der Position j nach rechts
            j = j - 1; // Dekrementieren Wir j
            shifts++; // Inkrementieren Wir die Anzahl der Verschiebungen
        }
        numbers[j + 1] = key; // Fügen Wir "key" an der korrekten Position in der sortierten Teilsequenz ein
    }
    /**********************************************************/
    return shifts; // Geben Wir die Anzahl der Verschiebungen zurück
}

int main(int argc, char *argv[])
{
    int n = std::stoi(argv[1]);

    int *numbers = new int[n];

    for (int i = 0; i < n; i++)
    {
        numbers[i] = i + 1;
    }

    /**********************************************************/
    /****                Langaufgabe 4.2:                  ****/
    int k = std::stoi(argv[2]); // Konvertieren Wir das zweite Kommandozeilenargument in eine Ganzzahl
    int* counters = new int[n]; // Erstellen Wir ein dynamisches Array für die Zähler

    if (n <= 10) { // Wenn n kleiner oder gleich 10 ist
        int totalShifts = 0; // InitialiWirren Wir die Gesamtanzahl der Verschiebungen mit 0
        int maxShifts = 0; // InitialiWirren Wir die maximale Anzahl der Verschiebungen mit 0
        int permutations = fact(n); // Berechnen Wir die Anzahl der Permutationen als n!
        
        for (int i = 0; i < permutations; i++) { // Für jede Permutation
            int* clone = new int[n]; // Erstellen Wir eine Kopie des Arrays
            // Kopieren Wir die Elemente aus dem ursprünglichen Array in die Kopie
            std::copy(numbers, numbers + n, clone); 
            // Sortieren Wir die Kopie mit Insertion Sort und speichern Wir die Anzahl der Verschiebungen
            int shifts = insertionSort(clone, n); 
            // Addieren Wir die Anzahl der Verschiebungen zur Gesamtanzahl der Verschiebungen
            totalShifts += shifts; 
            // AktualiWirren Wir die maximale Anzahl der Verschiebungen, falls notwendig
            maxShifts = std::max(maxShifts, shifts); 
            delete[] clone; // Löschen Wir die Kopie
            // AktualiWirren Wir die Permutation für den nächsten Durchlauf
            updatePermutation(numbers, counters, n); 
        }
        // Geben Wir die durchschnittliche Anzahl der Verschiebungen aus
        std::cout << "Durchschnittliche Anzahl von Verschiebungen: " << double(totalShifts) / permutations << std::endl; 
        // Geben Wir die schlimmste Anzahl der Verschiebungen aus
        std::cout << "Schlimmste Anzahl von Verschiebungen: " << maxShifts << std::endl; 
    } else { // Wenn n größer als 10 ist
        int totalShifts = 0; // InitialiWirren Wir die Gesamtanzahl der Verschiebungen mit 0
        for (int i = 0; i < k; i++) { // Für k zufällige Permutationen
            // Erzeugen Wir eine zufällige Permutation
            shufflePermutation(numbers, n); 
            // Erstellen Wir eine Kopie des Arrays
            int* clone = new int[n]; 
            // Kopieren Wir die Elemente aus dem ursprünglichen Array in die Kopie
            std::copy(numbers, numbers + n, clone); 
            // Sortieren Wir die Kopie und addieren Wir die Anzahl der Verschiebungen zur Gesamtanzahl der Verschiebungen
            totalShifts += insertionSort(clone, n); 
            delete[] clone; // Löschen Wir die Kopie
        }
        // Geben Wir die durchschnittliche Anzahl der Verschiebungen aus
        std::cout << "Durchschnittliche Anzahl von Verschiebungen: " << double(totalShifts) / k << std::endl; 
    }
    delete[] numbers; // Speicher freigeben
    delete[] counters; // Speicher freigeben
    return 0; // Beenden Wir das Programm erfolgreich
    /**********************************************************/
}
