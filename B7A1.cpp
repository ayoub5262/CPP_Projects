
#include <iostream>
#include <list>
#include <utility>
#include <cassert>
#include <cmath>

class B7A1 {
private:
    int m;
    std::list<std::pair<int, int>>* table;

    const double A = (std::sqrt(5) - 1) / 2;
    // Hilfsfunktion zur Berechnung der Listenadresse
    int addressOfList(int key) {
  /**********************************************************/
  /****                Kurzaufgabe 7.1:                 ****/
        //h(k) = floor[m ·(k · A − florr[k · A])]
        double frac = key * A - std::floor(key * A);
        int index = std::floor(m * frac);
        std::cout << "Frac: "<< frac << ", Key: " << key  << ", Index: " << index << std::endl; 
        return index;
  /**********************************************************/
    }

public:
    B7A1(int m): m(m){
  /**********************************************************/
  /****                Kurzaufgabe 7.1:                 ****/
       table = new std::list<std::pair<int, int>>[m];
  /**********************************************************/
    }
    ~B7A1() {
        delete[] table;
    }

    void insert(int key, int value) {
  /**********************************************************/
  /****                Kurzaufgabe 7.1:                 ****/
        int index = addressOfList(key); // Berechnet den Index für den gegebenen Schlüssel
        for (auto& pair : table[index]) { // Durchläuft die Liste am berechneten Index
            if (pair.first == key) { // Wenn der Schlüssel in der Liste gefunden wird
                pair.second = value; // Aktualisiert den Wert
                return; // Beendet die Methode
            }
        }
        // Fügt das Schlüssel-Wert-Paar am Ende der Liste ein, wenn der Schlüssel nicht gefunden wurde
        table[index].emplace_back(key, value); 
  /**********************************************************/
    }

    std::pair<int, int>* get(int key) {
  /**********************************************************/
  /****                Kurzaufgabe 7.1:                 ****/
        int index = addressOfList(key); // Berechnet den Index für den gegebenen Schlüssel
        for (auto& pair : table[index]) { // Durchläuft die Liste am berechneten Index
            if (pair.first == key) { // Wenn der Schlüssel in der Liste gefunden wird
                return &pair; // Gibt einen Zeiger auf das Schlüssel-Wert-Paar zurück
            }
        }
  /**********************************************************/
        return nullptr;
    }


    bool remove(int key) {
  /**********************************************************/
  /****                Kurzaufgabe 7.1:                 ****/
        int index = addressOfList(key); // Berechnet den Index für den gegebenen Schlüssel
        for (auto it = table[index].begin(); it != table[index].end(); ++it) { 
            if (it->first == key) { // Wenn der Schlüssel in der Liste gefunden wird
                table[index].erase(it); // Entfernt das Schlüssel-Wert-Paar aus der Liste
                return true; // Gibt true zurück, um anzuzeigen, dass das Entfernen erfolgreich war
            }
        }
  /**********************************************************/
        return false;
    }
};

int main() {
    int n;
    std::cin >> n;
    assert(n > 0);
    
    B7A1 table(n);

    std::string command;
    while (true) {
            std::cout << "Enter command (i to insert, g to get, r to remove, q to quit): ";
            std::cin >> command;

            if (command == "i") {
                int key, value;
                std::cin >> key >> value;
                table.insert(key, value);
                std::cout << "Inserted (" << key << ", " << value << ")" << std::endl;
            } else if (command == "g") {
                int key;
                std::cin >> key;
                auto result = table.get(key);
                if (result) {
                    std::cout << "Key: " << result->first << ", Value: " << result->second << std::endl;
                } else {
                    std::cout << "Key not found." << std::endl;
                }
            } else if (command == "r") {
                int key;
                std::cin >> key;
                bool removed = table.remove(key);
                std::cout << "Key " << key << " removed: " << std::boolalpha << removed << std::endl;
            } else if (command == "q") {
                break;
            } else {
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }

        return 0;
}

