/**
 * @author - Durga Prasad A G
 */

#include "RandomUsnPicker.h"

void RandomUsnPicker::init() {
    Shuffle sf;
    bool isFileEmpty;
    isFileEmpty = sf.fileHandling();

    if (!isFileEmpty) {
        sf.shuffleVectorElements(sf.numbers.size());

        for (unsigned int &number : sf.numbers) {
            usnList.push_back(number);
        }
        pickRandomUSN();
    }
}

void RandomUsnPicker::pickRandomUSN() {
    unsigned int i = 0;
    string choice;

    do {
        if (i == usnList.size()) {
            cout << "Last USN from the USN list has been reached. Shuffling USNs again." << endl;
            i = 0;
            usnList.clear();
            init();
        }
        cout << "USN : " << usnList[i] << endl;

        bool stop = false;
        while (!stop) {
            cout << "Do you to pick another USN ? (Yes - 'y'/No - any key): ";
            cin >> choice;

            if (choice.length() > 1) {
                cout << "Expected 'y' to continue or press any key to go back to main menu." << endl;
                continue;
            }
            stop = true;
        }
        i++;
    } while (choice == "y" || choice == "Y");
}