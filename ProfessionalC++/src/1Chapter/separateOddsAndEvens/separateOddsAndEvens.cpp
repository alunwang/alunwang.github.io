/*
 * Splits an array of ints into two arrays: one of even numbers and one of odd numbers. 
 */
#include <vector>
#include <iostream>

// Canonical C way to write such a function:
// Use pointers
void separateOddsAndEvens(const int arr[], std::size_t size, int** odds, std::size_t* numOdds, int** evens, std::size_t* numEvens)
{
    *numOdds = *numEvens = 0;
    for (std::size_t i=0; i<size; i++) {
        if (arr[i] % 2 == 1) {
            ++(*numOdds);
        } else {
            ++(*numEvens);
        }
    }

    *odds = new int[*numOdds];
    *evens = new int[*numEvens];
    std::size_t oddCount = 0, evenCount = 0;
    for (std::size_t i {0}; i<size; i++) {
        if (arr[i] % 2 == 1) {
            (*odds)[oddCount++] = arr[i];
        } else {
            (*evens)[evenCount++] = arr[i];
        }
    }
}


// 传统分拆方法：
// Use reference
void separateOddsAndEvens(const int arr[], std::size_t size, int*& odds, std::size_t& numOdds, int*& evens, std::size_t& numEvens)
{
    numOdds = numEvens = 0;
    for (std::size_t i {0}; i<size; i++) {
        if (arr[i] % 2 == 1) {
            ++numOdds;
        } else {
            ++numEvens;
        }
    }

    odds = new int[numOdds];
    evens = new int[numEvens];
    std::size_t oddsCount {0}, evensCount {0};
    for (std::size_t i {0}; i<size; i++) {
        if (arr[i] %2 == 1) {
            odds[oddsCount++] = arr[i];
        } else {
            evens[evensCount++] = arr[i];
        }
    }
}


/*
 * Even though using reference parameters is already much cleaner than using pointers,
 * it is recommended that you avoid dynamically allocated arrays as much as possible. 
 * For example, by using the Standard Library vector container, the separateOddsAndEvens()
 * function can be rewritten to be much safer, shorter, more elegant, and much more readable,
 * because all memory allocations and deallocations happen automatically.
 */
void separateOddsAndEvens(const std::vector<int>& arr, std::vector<int>& odds, std::vector<int>& evens)
{
    for (auto& v : arr) {
        if (v % 2 == 1) {
            odds.push_back(v);
        } else {
            evens.push_back(v);
        }
    }
}


struct OddsAndEvens {
    std::vector<int> odds, evens;
};
// 使用Return by value
// 而不要使用参数output
OddsAndEvens separateOddsAndEvens(const std::vector<int>& arr)
{
    std::vector<int> odds, evens;
    for (int v : arr) {
        if (v%2 == 1) {
            odds.push_back(v);
        } else {
            evens.push_back(v);
        }
    }

    return OddsAndEvens {.odds = odds, .evens = evens}; // Designated initializer introduced in C++20
}


int main(int argc, char* argv[])
{
    int unSplit[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* odds {nullptr};
    int* evens {nullptr};
    std::size_t numOdds {0}, numEvens {0};

    {
    std::cout << "testing separaeOddsAndEvens() with canonical C way...\n";
    separateOddsAndEvens(unSplit, std::size(unSplit), &odds, &numOdds, &evens, &numEvens);
    std::cout << "odds = ";
    for (int i=0; i<numOdds; ++i) {
        std::cout << odds[i] << " ";
    } 
    std::cout << std::endl;
    std::cout << "evens = ";
    for (int i=0; i<numEvens; ++i) {
        std::cout << evens[i] << " ";
    } 
    std::cout << std::endl;
    if (odds) {
        delete [] odds;
        odds = nullptr;
    }
    if (evens) {
        delete [] evens;
        evens = nullptr;
    }
    }

    {
    std::cout << "testing separateOddsAndEvens() with canonical C way and reference...\n";
    separateOddsAndEvens(unSplit, std::size(unSplit), odds, numOdds, evens, numEvens);
    std::cout << "odds = ";
    for (int i=0; i<numOdds; ++i) {
        std::cout << odds[i] << " ";
    } 
    std::cout << std::endl;
    std::cout << "evens = ";
    for (int i=0; i<numEvens; ++i) {
        std::cout << evens[i] << " ";
    } 
    std::cout << std::endl;
    if (odds) {
        delete [] odds;
        odds = nullptr;
    }
    if (evens) {
        delete [] evens;
        evens = nullptr;
    }
    }
    {
    std::cout << "testing separateOddsAndEvens() with container...\n";
    // Use vector, memory allocation/free managed by the vector itself
    std::vector<int> vecUnSplit { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> odds, evens;
    separateOddsAndEvens(vecUnSplit, odds, evens);
    // No need to deallocate the odds and evens containers; the vector class takes care of this.
    std::cout << "odds: ";
    for (auto& v : odds) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    std::cout << "evens: ";
    for (auto& v : evens) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    }

    {
    std::cout << "testing separateOddsAndEvens() with return by value...\n";
    // Changed to return by value
    std::vector<int> vecUnSplit { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto oddsAndEvens { separateOddsAndEvens(vecUnSplit) };
    std::cout << "odds: ";
    for (auto& v : oddsAndEvens.odds) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    std::cout << "evens: ";
    for (auto& v : oddsAndEvens.evens) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    }
    return 0;
}