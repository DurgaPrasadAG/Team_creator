/**
 * @author - Durga Prasad A G
 */

#include "RandomUsnPicker.h"

void RandomUsnPicker::init() {
    bool isFileEmpty;
    isFileEmpty = sf.openFile();

    if (!isFileEmpty) {
        shuffleUsn();
        pickRandomUsn();
    }
}

void RandomUsnPicker::pickRandomUsn() {
    unsigned int i = 0;
    string choice;

    do {
        if (i == rUsnList.size()) {
            cout << "Last USN from the USN list has been reached. Shuffling UsnList again." << endl;
            i = 0;
            rUsnList.clear();
            shuffleUsn();
        }
        cout << "USN : " << rUsnList[i] << endl;

        while (true) {
            cout << "Do you to pick another USN ? (Yes - 'y'/No - any alphabet or any digit): ";
            cin >> choice;

            if (choice.length() > 1) {
                cout << "Expected 'y' to continue or press any alphabet or any digit to go back to main menu." << endl;
                continue;
            }
            break;
        }
        i++;
    } while (choice == "y" || choice == "Y");
}

void RandomUsnPicker::shuffleUsn() {
    sf.shuffle(sf.usnList.size());
    rUsnList = sf.usnList;
}