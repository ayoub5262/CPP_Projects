#include <iostream>
#include <list>
#include <utility>
#include <cassert>
#include <cmath>

template <typename K, typename V>
class B7A2 {
private:
    int m;
    std::list<std::pair<K, V>>* table;

    // Hilfsfunktion zur Berechnung der Listenadresse
    const double A = (std::sqrt(5) - 1) / 2;

    int addressOfList(const K& key) {
  /**********************************************************/
  /****                 Kurzaufgabe 7.2:                 ****/
        //h(k) = floor[m ·(k · A − florr[k · A])]
        int hashValue = std::hash<K>{}(key);
        double frac = (hashValue * A) - std::floor(hashValue * A);
        int index = std::floor(m * frac);
        std::cout << "Frac: "<< frac <<", Key: " << key << ", Hash: " << hashValue << ", Index: " << index << std::endl;
        return index;
  /**********************************************************/
    }

public:
    B7A2(int m) : m(m) {
  /**********************************************************/
  /****                 Kurzaufgabe 7.2:                 ****/
        table = new std::list<std::pair<K, V>>[m];
  /**********************************************************/
    }

    ~B7A2() {
        delete[] table;
    }

    void insert(const K& key, const V& value) {
  /**********************************************************/
  /****                 Kurzaufgabe 7.2:                 ****/
        int index = addressOfList(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
  /**********************************************************/
    }

    std::pair<K, V>* get(const K& key) {
  /**********************************************************/
  /****                 Kurzaufgabe 7.2:                 ****/
        int index = addressOfList(key);
        for (auto& pair : table[index]) {
            if (pair.first == key)
                return &pair;
        }
  /**********************************************************/
        return nullptr;
    }

    bool remove(const K& key) {
  /**********************************************************/
  /****                 Kurzaufgabe 7.2:                 ****/
        int index = addressOfList(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return true;
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
    
    B7A2<std::string, std::string> table(n);
    
    std::string command;
    while (true) {
            std::cout << "Enter command (i to insert, g to get, r to remove, q to quit): ";
            std::cin >> command;

            if (command == "i") {
                std::string key;
                std::string value;
                std::cin >> key >> value;
                table.insert(key, value);
                std::cout << "Inserted (" << key << ", " << value << ")" << std::endl;
            } else if (command == "g") {
                std::string key;
                std::cin >> key;
                auto result = table.get(key);
                if (result) {
                    std::cout << "Key: " << result->first << ", Value: " << result->second << std::endl;
                } else {
                    std::cout << "Key not found." << std::endl;
                }
            } else if (command == "r") {
                std::string key;
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
