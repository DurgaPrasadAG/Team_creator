/**
 * @author - Durga Prasad A G
 */

#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

class UsnListGenerator {
private:
    fstream file_out;
    string filename = "generated_usn.txt";
    string startingUsn;
    string endingUsn;
    string anotherSeries{};
    string message, error;

    unsigned int count = 0;
    unsigned int startingUsnInt{};
    unsigned int endingUsnInt{};

    vector<unsigned int> startingUsnList;
    vector<unsigned int> endingUsnList;
    vector<unsigned int> skipUsnList;
    vector<unsigned int> nonSeqUsnList;

    bool doNotExecute = false;
    bool usnValidated = false;

    /**
     * This function displays the title of the menu &
     * USN format to input.
     * @param s - Title of the menu
     */
    static void guide(const string &s);

    /**
     * This function Generates Sequential rUsnList of Given USN range & writes it into
     * the file.
     */
    void writeSeqUsnList();

    /**
     * This function writes Non Sequential rUsnList entered by the user to the file.
     */
    void writeNonSeqUsnList();

    /**
     * This function which gets the data of USN which includes USN validation,
     * skipping rUsnList and write sequential rUsnList to the file.
     */
    void seqUsnListGenerator();

    /**
     * This function which gets the data of USN which includes USN validation,
     * and write Non-sequential rUsnList to the file.
     */
    void nonSeqUsnListGenerator();

    /**
     * This function checks if USN entered is numeric or contains Non-numeric value.
     * @param usn - USN as a input
     * @return Returns true if USN contains numeric value.
     */
    static bool isNumber(const string &usn);

    /**
     * This is the main function for opening file for creating a new USN list or Overwrite
     * existing USN list at eof.
     */
    void openFile();

    /**
     * Menu function which asks for type of USN list generation.
     */
    void generateUsnList();

    /**
     * USN validation function.
     * Checks for USN length, is Non-numeric value & input 0.
     * @param usn - Input entered by the user.
     * @return True if USN is valid.
     */
    static bool usnValidator(const string &usn);

    /**
     * Gets starting USN value and calls
     * usnValidator function for Usn validation.
     */
    void getStartingUsnValue();

    /**
     * Gets ending USN value and calls
     * usnValidator function for Usn validation.
     */
    void getEndingUsnValue();

    /**
     * This function skips the rUsnList entered by the user.
     */
    void usnSkipper();

    /**
     * Asks user if they want to include another series USN.
     * This function can also be used to continue the same series USN too.
     * @return If yes, then continue generating and writing sequential rUsnList.
     */
    string askAnotherSeries();

    /**
     * This function clears all the previously entered rUsnList in the file.
     * Creates new file if it file doesn't exist.
     * @return If yes, then Clear all rUsnList in the file.
     */
    bool createNewUsnList();

    /**
     * This function is for starting USN validation.
     * @return True, If starting USN is completely validated.
     */
    bool startingUsnValidator();

    /**
     * This function is for ending USN validation.
     * @return True - If ending USN is completely validated.
     */
    bool endingUsnValidator();

    /**
     * Function to ask the user to continue or go back to the previous menu.
     * @param message - Message to display.
     * @param error - Error message
     * @return input
     */
    static string ask(const string &message, const string &error);
public:

    UsnListGenerator() {
        openFile();
        generateUsnList();
    }
};