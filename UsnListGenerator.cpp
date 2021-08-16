/**
 * @author - Durga Prasad A G
 */

#include "UsnListGenerator.h"

void UsnListGenerator::openFile() {
    bool flag = true;
    do {
        string choice;
        cout << endl;
        cout << "\t\t";
        cout << "File handling" << endl;
        cout << "Type '1' - Create a new USN List." << endl;
        cout << "Type '2' - Overwrite and add USN at end of file." << endl;
        cout << "Type '3' - Back to main menu" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        if (choice.length() > 1) {
            cout << "Please input choice in range 1 to 3 only." << endl;
            continue;
        } else {
            switch (choice[0]) {
                case '1':
                    flag = createNewUsnList();
                    break;
                case '2':
                    cout << "Opening " << filename << " file..." << endl;
                    file_out.open(filename, ios::in | ios::out | ios::app);
                    checkIsFileEmpty();
                    flag = false;
                    break;
                case '3':
                    file_out.close();
                    fileAppending = false;
                    doNotExecute = true;
                    return;
                default:
                    cout << "Please input choice in range 1 to 3 only." << endl;
                    flag = true;
            }
        }
    } while (flag);

    if (!file_out.is_open()) {
        cout << "Failed to open " << filename << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Opened " << filename << " file successfully." << endl;
    }
}

void UsnListGenerator::generateUsnList() {
    if (doNotExecute) {
        return;
    } else {
        string choice;

        do {
            cout << "\n\t\t";
            cout << "USN list generator" << endl;
            cout << "Type '1' - Non-sequential USN list generator" << endl;
            cout << "Type '2' - Sequential USN list generator" << endl;
            cout << "Type '3' - Back to file handling menu" << endl;
            cout << "Enter your choice : ";
            cin >> choice;

            if (choice.length() > 1) {
                cout << "Expected range is 1 to 3 only." << endl;
                continue;
            }

            switch (choice[0]) {
                case '1':
                    nonSeqUsnListGenerator();
                    break;
                case '2':
                    seqUsnListGenerator();
                    break;
                case '3':
                    file_out.close();
                    openFile();
                    generateUsnList();
                    break;
                default:
                    cout << "Expected range is 1 to 3 only." << endl;
            }
        } while (choice != "3");
    }
}

void UsnListGenerator::guide(const string &s) {
    cout << s << endl;
    cout << "USN format : series+last 3 digits of usn (18043/19___)" << endl;
}

void UsnListGenerator::seqUsnListGenerator() {
    string s = "\n\tSequential USN List Generator";
    guide(s);

    do {
        bool stop = false;
        while (!stop) {
            getStartingUsnValue();
            stop = startingUsnValidator();
        }

        getEndingUsnValue();

        usnSkipper();
        writeSeqUsnList();
        anotherSeries = askAnotherSeries();

        seqCount++;
    } while (anotherSeries == "y" || anotherSeries == "Y");
}

void UsnListGenerator::writeSeqUsnList() {
    bool generateUsn = false;

    if (skipUsnList.empty()) {
        for (unsigned int i = startingUsnInt; i <= endingUsnInt; i++) {
            file_out << i << endl;
        }
    } else {
        unsigned int j = 0;

        for (unsigned int i = startingUsnInt; i <= endingUsnInt; i++) {
            if (i == skipUsnList[j]) {
                j++;
                continue;
            } else {
                file_out << i << endl;
            }
        }

        if ((endingUsnInt - startingUsnInt) == skipUsnList.size() - 1) {
            generateUsn = true;
        }
        skipUsnList.clear();
    }

    if (generateUsn) {
        cout << "Every USN is skipped" << endl;
    } else {
        cout << "USN list generated successfully. \n" << endl;
    }
}

void UsnListGenerator::nonSeqUsnListGenerator() {
    string s = "\n\tNon-sequential USN List Generator";
    guide(s);
    cout << "Type 'create' to create Non-sequential USN list\n";
    cout << "---> Type USN in ascending order only. <---" << endl;

    string usn;
    int usnInt;
    do {
        cout << "Enter USN : ";
        cin >> usn;

        if (usn == "create" || usn == "Create" || usn == "CREATE") {
            break;
        }

        if (!usnValidator(usn)) {
            continue;
        }

        unsigned int nonSeqUsnInt = stoi(usn);
        if (!endingUsnList.empty()) {
            unsigned int lastEndingSeqUsn = endingUsnList[endingUsnList.size() - 1];
            if (nonSeqUsnInt <= lastEndingSeqUsn) {
                cout << usn << " must be greater than " << lastEndingSeqUsn << endl;
                continue;
            }
        } else if (nonSeqCount >= 1) {
            if (nonSeqUsnInt <= nonSeqUsnList[nonSeqCount - 1]) {
                cout << usn << " must be greater than " << nonSeqUsnList[nonSeqCount - 1] << endl;
                continue;
            }
        }

        usnInt = stoi(usn);
        nonSeqUsnList.push_back(usnInt);
        nonSeqCount++;
    } while (true);

    writeNonSeqUsnList();
}

void UsnListGenerator::writeNonSeqUsnList() {
    for (auto &&i : nonSeqUsnList) {
        file_out << i << endl;
    }

    if (!nonSeqUsnList.empty()) {
        cout << "USN list generated successfully." << endl;
    } else {
        cout << "USN list is not generated because USN isn't provided." << endl;
    }
}

bool UsnListGenerator::isNumber(const string &usn) {
    return all_of(usn.begin(), usn.end(),
                  [](char c) {
                      return isdigit(c) != 0;
                  }
    );
}

bool UsnListGenerator::usnValidator(const string &usn) const {
    if (usn.length() != 5) {
        cout << "USN length must be of length 5 only." << endl;
        return false;
    } else if (!isNumber(usn)) {
        cout << "USN must be a number, e.g., 18043." << endl;
        return false;
    } else if (usn[0] == '0') {
        cout << "USN beginning with 0 or if USN itself 0 is not valid" << endl;
        return false;
    } else if (fileAppending) {
        if (stoi(usn) <= lastUsn) {
            cout << "USN must be greater than last USN in generated_usn.txt file" << endl;
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }
}

void UsnListGenerator::getStartingUsnValue() {
    while (true) {
        cout << "Enter Starting USN : ";
        cin >> startingUsn;

        if (!usnValidator(startingUsn)) {
            continue;
        }

        if (!nonSeqUsnList.empty()) {
            if (stoi(startingUsn) <= nonSeqUsnList[nonSeqUsnList.size() - 1]) {
                cout << "Starting USN must be greater than previously entered USN." << endl;
                continue;
            }
        }

        break;
    }
    startingUsnInt = stoi(startingUsn);
    startingUsnList.push_back(startingUsnInt);
}

void UsnListGenerator::getEndingUsnValue() {
    while (true) {
        cout << "  Enter ending USN : ";
        cin >> endingUsn;

        if (!usnValidator(endingUsn)) continue;

        startingUsnInt = stoi(startingUsn);
        endingUsnInt = stoi(endingUsn);

        if (endingUsnInt <= startingUsnInt) {
            cout << "Ending USN must be greater than starting USN..." << endl;
            continue;
        }
        break;
    }

    endingUsnList.push_back(endingUsnInt);
}

void UsnListGenerator::usnSkipper() {
    string skip;
    message = "Do you want to skip some usn? (Y/N): ";
    error = "Expected 'y' to continue "
            "Type any alphabet or any digit to go back to usn list generator menu";

    skip = ask(message, error);

    if (skip == "y" || skip == "Y") {
        cout << "Type 'stop' to stop skipping USN" << endl;
        cout << "---> Type USN in ascending order only. <---" << endl;
        string skipUSN;
        unsigned int i = 0;
        do {
            cout << "Enter USN : ";
            cin >> skipUSN;

            if (skipUSN == "stop") break;

            if (!usnValidator(skipUSN)) continue;

            if (skipUSN > endingUsn) {
                cout << skipUSN << " shouldn't be greater than ending USN." << endl;
                continue;
            } else if (skipUSN < startingUsn) {
                cout << skipUSN << " shouldn't be smaller than starting USN." << endl;
                continue;
            } else if (i >= 1) {
                if (stoi(skipUSN) <= skipUsnList[i - 1]) {
                    cout << skipUSN << " must be greater than previously entered USN." << endl;
                    continue;
                }
            }

            skipUsnList.push_back(stoi(skipUSN));
            i++;
        } while (true);
    }
}

string UsnListGenerator::askAnotherSeries() {
    message = "Do you want to add another series usn ? (Yes - 'y' /N0 - any alphabet or any digit): ";
    error = "Expected 'y' to continue or "
            "Type any alphabet or any digit to go back to usn list generator menu";
    string response = ask(message, error);

    return response;
}

string UsnListGenerator::ask(const string &message, const string &error) {
    string input;
    while (true) {
        cout << message;
        cin >> input;

        if (input.length() > 1) {
            cout << error << endl;
            continue;
        }
        break;
    }
    return input;
}

bool UsnListGenerator::createNewUsnList() {
    string confirm;
    bool flag = true;
    bool cont = false;
    do {
        cout << "Type 'C' to continue. (No - any alphabet or any digit): ";
        cin >> confirm;

        if (confirm.length() > 1) {
            cout << "Expected 'C' or type any alphabet or any digit to go back to file handling menu" << endl;
        } else if (confirm == "c" || confirm == "C") {
            nonSeqCount = 0;
            if (!nonSeqUsnList.empty()) {
                nonSeqUsnList.clear();
            }

            seqCount = 0;
            if (!startingUsnList.empty()) {
                startingUsnList.clear();
                endingUsnList.clear();
            }

            cout << "Opening " << filename << " file..." << endl;
            file_out.open(filename, ios::out | ios::trunc);
            flag = false;
        } else {
            flag = false;
            cont = true;
        }
    } while (flag);

    return cont;
}

bool UsnListGenerator::startingUsnValidator() {
    bool stop = true;

    if (seqCount >= 1) {
        unsigned int suInt = startingUsnInt;

        if (suInt <= endingUsnList[seqCount - 1]) {
            cout << "USN must be greater than ending USN." << endl;
            startingUsnList.pop_back();
            stop = false;
        }
    }
    return stop;
}

void UsnListGenerator::checkIsFileEmpty() {
    if (file_out.peek() != EOF) {
        file_out.seekp(-8, ios::end);
        file_out >> lastUsn;
        fileAppending = true;
    } else {
        file_out.close();
        file_out.open(filename, ios::out | ios::app);
    }
}