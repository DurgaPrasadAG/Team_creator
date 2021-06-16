/**
 * @author - Durga Prasad A G
 */

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "Shuffle.h"

using namespace std;

class RandomUsnPicker {
public:
    vector<unsigned int> usnList;

    /**
     * This is the main function. It calls file Handling function
     * from the Shuffle class and if file is not empty then it calls pickRandomUsn function.
     */
    void init();

    /**
     * This function picks random usn from the generated_usn file.
     */
    void pickRandomUSN();

    /**
     * This default constructor calls init function.
     */
    RandomUsnPicker() { init(); }
};