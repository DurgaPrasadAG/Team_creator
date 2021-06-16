/**
 * @author - Durga Prasad A G
 */

#pragma once

#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

class Shuffle {
private:
    fstream file_out;

    /**
     * This function generates CSV file.
     * @param usnListSize - Size of the USN list of generated_usn file.
     * @param sizeOfOneTeam - Creates a team of specified value.
     */
    void generateCsv(unsigned int usnListSize, unsigned int sizeOfOneTeam);

    /**
     * This function is to ask the user how many members in 1 team.
     * @param s - user input of maximum members in 1 team.
     */
    void maxMembersInOneTeam(const string &s);

    /**
     * Function asks user input for subject of a team.
     * @param subject - Subject of a team
     * @return subject
     */
    static string getTeamDetails(const string &subject);
public:
    /**
     * This function is a implementation of Fisher-Yates Algorithm
     * Shuffles vector elements of usn list size from the end and stops i value reach 1.
     * @param usnListSize - usn list size
     */
    void shuffleVectorElements(unsigned int usnListSize);

    /**
     * This is the main function of Shuffle. This calls maxMembersInOneTeam function.
     */
    void shuffler();

    vector<unsigned int> numbers;

    /**
     * This function opens generated_usn file to read USNs.
     * @return True - If file is empty
     */
    bool fileHandling();
};