//  main.cpp
//  Created by Sina Pilehchiha on 2019-02-07.
//  Copyright © 2019 TeamNumber02. All rights reserved.

//  local includes
#include "Kwaymergesort.h"

//  comparison function for sorting by clientID
bool byClientID(CLAIM const &c1, CLAIM const &c2) {
    if (std::strcmp(c1.clientID, c2.clientID) != 0) {
        
        //    convert clientID character arrays into integers in order to compare their values.
        if      (atoi(c1.clientID) < atoi(c2.clientID))  return true;
        else if (atoi(c1.clientID) > atoi(c2.clientID))  return false;
    }
    
    //  the sorter gets here when clientIDs are the same. now it tries to sort based on compensationAmounts.
    //  convert compensationAmount character arrays into floats in order to compare their values.
    if      (atof(c1.compensationAmount) < atof(c2.compensationAmount))  return true;
    else return false;
}

// comparison function for sorting by chromosome, then by start.
bool byCompensationAmount(CLAIM const &c1, CLAIM const &c2) {
    return (atof(c1.compensationAmount) > atof(c2.compensationAmount));
}

//  a program shall contain a global function named main, which is the designated start of the program.
int main(int argc, char* argv[]) {
    
    //  this argument is given to the executable pogram via the command line interface.
    std::string inputFile = argv[1];
    
    //  allow the sorter to use an arbitrary amount (in bytes) of memory for sorting.
    std::string bufferSize = argv[2];
    
    //  once the buffer is full, the sorter will dump the buffer's content to a temporary file and grab another chunk from the input file.
    std::string temporaryPath = argv[3]; // allows you to write the intermediate files anywhere you want.
    
    //  create a new instance of the KwayMergeSort class.
    KwayMergeSort* claim_sorter = new KwayMergeSort (inputFile       ,
                                                     "outputFile.txt",
                                                     bufferSize      ,
                                                     temporaryPath   ,
                                                     byClientID)     ;
    
    //  mark the beginning of the execution of the sorting procedure
    const clock_t BEGINNING = clock();
    
    //  this is the main call to the sorting procedure.
    claim_sorter->Sort();
    claim_sorter->sumOfCompensationAmounts();
    KwayMergeSort* claim_sorter2 = new KwayMergeSort ("sumOfCompensationAmountsFile.txt",
                                                      "outputFile2.txt"                 ,
                                                      bufferSize                        ,
                                                      temporaryPath                     ,
                                                      byCompensationAmount)             ;
    claim_sorter2->Sort();
    claim_sorter2->showTopTenCostlyClients();
    
    //  report the execution time (in minutes)
    const double EXECUTION_TIME = (double)(clock() - BEGINNING) / CLOCKS_PER_SEC / 60;
    
    //  print out the time elapsed sorting.
    std::cout << "\n" << EXECUTION_TIME << "\n";
}
