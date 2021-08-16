/**
 * @author - Durga Prasad A G
 */

#include "Shuffle.h"

void Shuffle::generateCsv(unsigned int usnListSize, unsigned int sizeOfOneTeam) {
    string filename("generated_teams.csv");

    file_out.open(filename, ios_base::out);
    if (!file_out.is_open()) {
        cout << "Failed to open " << filename << '\n';
    } else {
        string message;

        string subject;
        message = "Enter the name of the subject to display in teams file : ";
        cin.ignore();
        subject = getTeamDetails(message);

        string teamName;
        message = "Enter the name for the team serial number \n"
                  "(Example : Team, SSN, Group, Batch) : ";
        teamName = getTeamDetails(message);

        int teamNo = 0;
        file_out << "Team Creator X " << subject << endl;
        for (int i = 0; i < usnListSize; i++) {
            if (i % sizeOfOneTeam == 0) {
                teamNo++;
                file_out << endl << teamName << " " << teamNo << ',';
            }
            file_out << " " << usnList[i] << ',';
        }
        file_out.close();

        string response;
        cout << endl;
        cout << "Team created successfully. \n" << endl;
        cout << "Do you want to view Generated Team?" << endl;
        cout << "This will exit Team Creator and open Generated Teams file." << endl;
        cout << "Generated teams may require internet connection to open it "
                "in MS Excel/any csv viewer. " << endl;

        while (true) {
            cout << "Your response (Yes - 'y', open file/No - any alphabet or any digit): ";
            cin >> response;

            if (response.length() > 1) {
                cout << "Expected 'y' to continue or press any alphabet or any digit to go back to main menu." << endl;
                continue;
            }

            if (response == "y" || response == "Y") {
                cout << "Trying to open Generated file..." << endl;
                try {
                    system(".\\generated_teams.csv");
                    exit(EXIT_SUCCESS);
                } catch (...) {
                    cout << "Failed to open " << filename << endl;
                }
            } else {
                break;
            }
        }
    }
}

void Shuffle::shuffle(unsigned int usnListSize) {
    srand(time(nullptr));

    for (unsigned int i = usnListSize - 1; i > 0; i--) {
        unsigned int j = rand() % (i + 1);
        swap(usnList[i], usnList[j]);
    }
}

bool Shuffle::openFile() {
    int number;
    ifstream input_file("generated_usn.txt");

    if (!input_file.is_open()) {
        cout << "generated_usn.txt file doesn't exist." << endl;
        cout << "You need to Generate USN list. "
                "It will automatically create generated_usn.txt file." << endl;
        return true;
    } else if (input_file.peek() == EOF) {
        cout << "USN list is empty." << endl;
        cout << "You need to Generate USN list..." << endl;
        return true;
    } else {
        while (input_file >> number) {
            usnList.push_back(number);
        }
        return false;
    }
}

void Shuffle::shuffler() {
    string response;
    while (true) {
        cout << "Type 'c' to continue or type any alphabet or any digit to go back to main menu." << endl;
        cout << "Your response : ";
        cin >> response;

        if (response.length() > 1) {
            cout << "Expected 'c' to continue or press any alphabet or any digit to go back to main menu." << endl;
            continue;
        }

        maxMembersInOneTeam(response);
        break;
    }
}

void Shuffle::maxMembersInOneTeam(const string &s) {
    bool isFileEmpty;
    if (s == "c" || s == "C") {
        isFileEmpty = openFile();
        if (!isFileEmpty) {
            shuffle(usnList.size());

            string teamSize;
            unsigned int teamSizeInt;
            while (true) {
                cout << "what should be the team size? (2 to 7): ";
                cin >> teamSize;

                if (teamSize.length() > 1 || !isdigit(teamSize[0])) {
                    cout << "Enter Team size in range 2 to 7 only." << endl;
                    continue;
                } else {
                    teamSizeInt = stoi(teamSize);
                    if (teamSizeInt <= 1 || teamSizeInt >= 8) {
                        cout << "Team size must be in range 2 to 7 only." << endl;
                        continue;
                    }
                }

                break;
            }
            generateCsv(usnList.size(), teamSizeInt);
        }
    }
}

string Shuffle::getTeamDetails(const string &subject) {
    string teamDetails;
    while (true) {
        cout << subject;
        getline(cin, teamDetails);

        if (teamDetails.length() == 0) {
            cout << "No Input received" << endl;
            continue;
        }
        break;
    }

    return teamDetails;
}