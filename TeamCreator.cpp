/**
 * @author - Durga Prasad A G
 */

#include <iostream>
#include "RandomUsnPicker.h"
#include "UsnListGenerator.h"

using namespace std;

class TeamCreator {
public:
    static void teamCreatorTitle();

    static void menu();

    static void about();
};

int main() {
    TeamCreator::teamCreatorTitle();
    TeamCreator::menu();
}

void TeamCreator::teamCreatorTitle() {
    cout << "***** *****     *     *       *     ***** ***** *****     *     "
            "***** ****** *****"
         << endl;
    cout << "  *   *        * *    **     **     *     *  *  *        * *      "
            "* "
            "  *    * *  * "
         << endl;
    cout << "  *   *****   * * *   * *   * *     *     **    *****   * * *     "
            "* "
            "  *    * **   "
         << endl;
    cout << "  *   *      *     *  *  * *  *     *     *  *  *      *     *    "
            "* "
            "  *    * *  * "
         << endl;
    cout << "  *   ***** *       * *   *   *     ***** *   * ***** *       *   "
            "* "
            "  ****** *   *"
         << endl;
}

void TeamCreator::about() {
    cout << endl;
    cout << "About Team creator" << endl;
    cout << "Version   : 1.0.0" << endl;
    cout << "Developer : Durga Prasad A G" << endl;
    cout << "VTU USN   : 3BR18CS043" << endl;

    string response;
    do {
        cout << "\n\n\n\n\n";
        cout << "Type any alphabet or any digit to go back to main menu." << endl;
        cout << "Your response : ";
        cin >> response;
    } while (response[0] == '\0');
}

void TeamCreator::menu() {
    do {
        string choice;
        cout << endl;
        cout << "           Main menu" << endl;
        cout << "Type '1' - Create Teams using random USNs" << endl;
        cout << "Type '2' - Pick Random USN" << endl;
        cout << "Type '3' - Generate USN list" << endl;
        cout << "Type '4' - About" << endl;
        cout << "Type '5' - Exit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        if (choice.length() > 1) {
            cout << "Input must be in range 1 to 3. Please try again." << endl;
            continue;
        }

        if (choice[0] == '1') {
            Shuffle sf;
            sf.shuffler();
        } else if (choice[0] == '2') {
            RandomUsnPicker rup;
        } else if (choice[0] == '3') {
            UsnListGenerator ulg;
        } else if (choice[0] == '4') {
            TeamCreator::about();
        } else if (choice[0] == '5') {
            exit(EXIT_SUCCESS);
        } else {
            cout << "Input must be in range 1 to 3. Please try again." << endl;
        }
    } while (true);
}