#include "map.h"
#include "timer.h"
#include <map>

#define INSERT_ELEMENTS
#define SEARCH_ELEMENTS
#define ERASE_ELEMENTS
#define RANDOM_OPERATIONS

int main() {
    map<int> myMap;
    std::map<int, int> map;

	Timer timer;
    int range = 10000;

	int numInsert = 1000;
    int numSearch = 1000;
    int numDelete = 1000;
    int numOps = 1000;

#if defined INSERT_ELEMENTS
    timer.restart();
    for (int i = 0; i < numInsert; i++)
        map.insert(std::pair<int, int>(rand() % range, rand() % range));
    printf("Insert %u elements in a std::map = %.3f milliseconds\n", numInsert, timer.elapsed<float>() * 1000);

    timer.restart();
    for (int i = 0; i < numInsert; i++)
        myMap.insert(rand() % range, rand() % range);
    printf("Insert %u elements in my map = %.3f milliseconds\n\n", numInsert, timer.elapsed<float>() * 1000);
#endif

#if defined SEARCH_ELEMENTS
    timer.restart();
    for (int i = 0; i < numSearch; i++)
        map.find(rand() % range);
    printf("Search %u elements in std::map = %.3f milliseconds\n", numSearch, timer.elapsed<float>() * 1000);

    timer.restart();
    for (int i = 0; i < numSearch; i++)
        myMap.find(rand() % range);
    printf("Search %u elements in my map = %.3f milliseconds\n\n", numSearch, timer.elapsed<float>() * 1000);
#endif

#if defined ERASE_ELEMENTS
    timer.restart();
    for (int i = 0; i < numDelete; i++)
        map.erase(rand() % range);
    printf("Delete %u elements in a std::map = %.3f milliseconds\n", numDelete, timer.elapsed<float>() * 1000);

    timer.restart();
    for (int i = 0; i < numDelete; i++)
        myMap.erase(rand() % range);
    printf("Delete %u elements in my map = %.3f milliseconds\n\n", numDelete, timer.elapsed<float>() * 1000);
#endif

#if defined RANDOM_OPERATIONS
    timer.restart();
    for (int i = 0; i < numOps; ++i) {
        switch (rand() % 3) {
        case 0: map.insert(std::pair<int, int>(rand() % range, rand() % range)); break;
        case 1: map.erase(rand() % range); break;
        case 2: map.find(rand() % range); break;
        }
    }
    printf("Random sequence of %u operations with std::map = %.3f milliseconds\n", numOps, timer.elapsed<float>() * 1000);

    timer.restart();
    for (int i = 0; i < numOps; ++i) {
        switch (rand() % 3) {
        case 0: myMap.insert(rand() % range, rand() % range); break;
        case 1: myMap.erase(rand() % range); break;
        case 2: myMap.find(rand() % range); break;
        }
    }
    printf("Random sequence of %u operations with my map = %.3f milliseconds\n", numOps, timer.elapsed<float>() * 1000);
#endif

	return 0;
}

