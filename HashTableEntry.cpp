#include <iostream>
#include <list>
#include <vector>
#include <utility> // For std::pair

// Define the HashTable class with two template parameters: K for keys and V for values.
template<typename K, typename V>
class HashTable {
private:
    static const int HASH_GROUPS = 10; // Define the number of hash groups (buckets) for simplicity.
    // The table is a vector of lists, where each list holds pairs of keys and values.
    std::vector<std::list<std::pair<K, V>>> table;

public:
    // Constructor initializes the table with the predefined number of hash groups.
    HashTable() : table(HASH_GROUPS) {}

    // Checks if the hash table is empty by checking each group for contents.
    bool isEmpty() const {
        for (int i = 0; i < HASH_GROUPS; ++i) {
            if (!table[i].empty()) {
                return false;
            }
        }
        return true;
    }

    // Hash function: calculates the bucket index for a given key.
    int hashFunction(K key) {
        return key % HASH_GROUPS; // Simple modulo-based hash function.
    }

    // Insert a key-value pair into the hash table.
    void insertItem(K key, V value) {
        int hashValue = hashFunction(key); // Determine the bucket for this key.
        auto& cell = table[hashValue]; // Reference to the cell (bucket).
        auto bItr = begin(cell); // Iterator to traverse the cell.
        bool keyExists = false; // Flag to check if the key exists.

        // Search for the key in the bucket. If found, update the value.
        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                bItr->second = value;
                std::cout << "[WARNING] Key exists. Value replaced." << std::endl;
                break;
            }
        }

        // If the key was not found, insert the new key-value pair at the end of the bucket.
        if (!keyExists) {
            cell.emplace_back(key, value);
        }
    }

    // Remove a key-value pair from the hash table.
    void removeItem(K key) {
        int hashValue = hashFunction(key); // Determine the bucket for this key.
        auto& cell = table[hashValue]; // Reference to the cell (bucket).
        auto bItr = begin(cell); // Iterator to traverse the cell.
        bool keyExists = false; // Flag to check if the key exists.

        // Search for the key in the bucket. If found, remove the key-value pair.
        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                bItr = cell.erase(bItr); // Erase the element and update the iterator.
                std::cout << "[INFO] Pair removed." << std::endl;
                break;
            }
        }

        // If the key was not found, print a warning message.
        if (!keyExists) {
            std::cout << "[WARNING] Key not found. Pair not removed." << std::endl;
        }
    }

    // Print the entire hash table.
    void printTable() {
        for (int i = 0; i < HASH_GROUPS; ++i) {
            if (!table[i].empty()) {
                auto bItr = table[i].begin(); // Iterator to traverse each bucket.
                for (; bItr != table[i].end(); bItr++) {
                    // Print each key-value pair in the bucket.
                    std::cout << "[INFO] Key: " << bItr->first << " Value: " << bItr->second << std::endl;
                }
            }
        }
    }
};

int main() {
    HashTable<int, std::string> hTable; // Instantiate the hash table with int keys and string values.
    int choice, key; // Variables for user's choice and the key input.
    std::string value; // Variable for the value input.

    // Infinite loop for the user interface.
    while (true) {
        std::cout << "\nHash Table Operations:\n";
        std::cout << "1. Insert Item\n";
        std::cout << "2. Remove Item\n";
        std::cout << "3. Display Table\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Switch case based on user input.
        switch (choice) {
            case 1: // Insert item case.
                std::cout << "Enter key (integer) and value (string): ";
                std::cin >> key >> value;
                hTable.insertItem(key, value);
                break;
            case 2: // Remove item case.
                std::cout << "Enter key (integer) to remove: ";
                std::cin >> key;
                hTable.removeItem(key);
                break;
            case 3: // Display hash table case.
                hTable.printTable();
                break;
            case 4: // Exit case.
                return 0; // Exit the program.
            default: // Default case for invalid inputs.
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
