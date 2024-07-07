#include <iostream>

// Hilfsfunktion zum Vertauschen zweier Werte
void swap(int data[], int i, int j)
{
    int h = data[i];
    data[i] = data[j];
    data[j] = h;
}

void maxHeapifyUp(int data[], int i)
{
    /**********************************************************/
    /****                Langaufgabe 4.1:                  ****/
    while (i != 0 && data[(i - 1) / 2] < data[i]) { // Solange i nicht 0 ist und das Elternelement kleiner als das aktuelle Element ist
        swap(data, i,(i - 1) / 2); // Tauschen Sie das aktuelle Element mit seinem Elternelement
        i = (i - 1) / 2; // Aktualisieren Sie i auf den Index des Elternelements
    }
    /**********************************************************/
}

void maxHeapifyDown(int data[], int n)
{
    /**********************************************************/
    /****                Langaufgabe 4.1:                  ****/
    int i = 0; // Starten Sie am Wurzelelement
    while (2 * i + 1 < n) { // Solange das linke Kind existiert
        int kind = 2 * i + 1; // Setzen Sie das linke Kind als das größte Kind
        if (kind + 1 < n && data[kind] < data[kind + 1]) // Wenn das rechte Kind existiert und größer als das linke Kind ist
            kind++; // Setzen Sie das rechte Kind als das größte Kind
        
        if (data[i] >= data[kind]) // Wenn das aktuelle Element größer oder gleich dem größten Kind ist
            break; // Beenden Sie die Schleife
        
        swap(data, i, kind); // Tauschen Sie das aktuelle Element mit seinem größten Kind
        i = kind; // Aktualisieren Sie i auf den Index des größten Kindes
    }
    /**********************************************************/
}

void buildMaxHeap(int data[], int n)
{
    /**********************************************************/
    /****                Langaufgabe 4.1:                  ****/
    for (int i = 1; i < n; i++) // Für jedes Element im Array (außer dem ersten)
        maxHeapifyUp(data, i); // Stellen Sie die Heap-Eigenschaft für dieses Element her
    /**********************************************************/
}

int extractMax(int data[], int n)
{
    /**********************************************************/
    /****                Langaufgabe 4.1:                  ****/
    int max = data[0]; // Speichern Sie das maximale Element (Wurzelelement)
    data[0] = data[n - 1]; // Ersetzen Sie das Wurzelelement durch das letzte Element im Heap
    maxHeapifyDown(data, n - 1); // Stellen Sie die Heap-Eigenschaft für das Wurzelelement wieder her
    /**********************************************************/
    return max;// Geben Sie das maximale Element zurück
}

int heapSelect(int data[], int k, int n)
{
    /**********************************************************/
    /****                Langaufgabe 4.1:                  ****/
    buildMaxHeap(data, n); // Bauen Sie einen Max-Heap aus dem Array auf
    for (int i = 0; i < k - 1; i++) // Entfernen Sie die k-1 größten Elemente aus dem Heap
        extractMax(data, n - i);
    /**********************************************************/
    return extractMax(data, n - k + 1); // Entfernen Sie und geben Sie das k-te kleinste Element zurück
}

int main(int argc, char *argv[])
{
    int k = std::stoi(argv[1]);

    int n;
    std::cin >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    std::cout << "Input Array: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << (i < n - 1 ? ", " : "");
    }
    std::cout << std::endl;

    int v = heapSelect(arr, k, n);
    std::cout << "The " << k << "-th element: " << v << std::endl;

    delete[] arr; // Speicher freigeben
    return 0; //
}
