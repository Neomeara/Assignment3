// CSC 456 Assignment 3
// Nate O'Meara
// Due 11/21/2021

#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include "A3.h"

using namespace std;

// Function Prototypes
void memoryManager(int, int);
int allocate( int, int);




// Global Variables
void* freeFrameList;

int main()
{

    cout << "Hello World\n";

    memoryManager(30, 1);



    return 0;
}

void memoryManager(int memSize, int frameSize)
{
    int freeFrameList[memSize] = {0};

    for (int i =0; i < memSize; i++)
    {
        cout << freeFrameList[i] << endl;
    }
    
}


int allocate(int allocSize, int pid)
{



    return 0;
}