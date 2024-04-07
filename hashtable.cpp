#include <iostream>
#include <list>
#include <vector>
#include <utility> // For std::pair

template<typename K, typename V>
class HashTable {
private:
    static const int HASH_GROUPS = 10; // Example size, can be resized according to needs
    std::vector<std::list<std::pair<K, V>>> table;

public:
    HashTable() : table(HASH_GROUPS) {}

    bool isEmpty() const {
        for (int i = 0; i < HASH_GROUPS; ++i) {
            if (!table[i].empty()) {
                return false;
            }
        }
        return true;
    }

    int hashFunction(K key) {
        return key % HASH_GROUPS; // Simple hash function, works with integer keys
    }

    void insertItem(K key, V value) {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        auto bItr = begin(cell);
        bool keyExists = false;

        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                bItr->second = value;
                std::cout << "[WARNING] Key exists. Value replaced." << std::endl;
                break;
            }
        }

        if (!keyExists) {
            cell.emplace_back(key, value);
        }

        return;
    }

    void removeItem(K key) {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        auto bItr = begin(cell);
        bool keyExists = false;

        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                bItr = cell.erase(bItr);
                std::cout << "[INFO] Pair removed." << std::endl;
                break;
            }
        }

        if (!keyExists) {
            std::cout << "[WARNING] Key not found. Pair not removed." << std::endl;
        }

        return;
    }

    void printTable() {
        for (int i = 0; i < HASH_GROUPS; ++i) {
            if (!table[i].empty()) {
                auto bItr = table[i].begin();
                for (; bItr != table[i].end(); bItr++) {
                    std::cout << "[INFO] Key: " << bItr->first << " Value: " << bItr->second << std::endl;
                }
            }
        }
        return;
    }
};

int main() {
    HashTable<int, std::string> hTable;
    hTable.insertItem(905, "John");
    hTable.insertItem(201, "Mary");
    hTable.insertItem(332, "Peter");
    hTable.insertItem(124, "Raj");
    hTable.insertItem(107, "Mona");
    hTable.insertItem(333, "Wanda");

    hTable.printTable();

    hTable.removeItem(332);
    hTable.removeItem(100);

    hTable.printTable();

    if (hTable.isEmpty()) {
        std::cout << "The hash table is empty." << std::endl;
    } else {
        std::cout << "The hash table is not empty." << std::endl;
    }

    return 0;
}
