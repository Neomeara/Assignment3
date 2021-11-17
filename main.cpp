// CSC 456 Assignment 3
// Nate O'Meara
// Due 11/21/2021

#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <vector>

using namespace std;

// Function Prototypes
void memoryManager(int, int);
int allocate( int, int);

struct page 
{
    int number;
    int pid;
    int frame;
};
struct process
{
    int pid;
    int size;
    page* pageTable;
};

// Global Variables
vector<int> freeFrameList;
vector<process> processList;
int* memory;


int main()
{

    cout << "Hello World\n";
    process p;
    p.pid =1;
    p.size =2;
    processList.insert(processList.end(), p);
    memoryManager(10, 1);
    cout << "Allocate: "<< allocate(2,1);



    return 0;
}

void memoryManager(int memSize, int frameSize)
{

    // we need allocated memory
    // we need a list of free frames
    memory = new int[memSize] {0};
    

    for (int i =0; i < memSize; i++)
    {
        freeFrameList.push_back(i);
        cout << memory[i] << endl;
    }
    
}


int allocate(int allocSize, int pid)
{

    page* pages = new page[allocSize];
    for (int i =0; i < allocSize; i++)
    {
        pages[i].number = 1;
        pages[i].pid = pid;
        
    }

    int processListIndex =0;
    for (int i =0; i < processList.size(); i++)
    {
        if(processList[i].pid == pid)
        {
            processListIndex = i;
            break;
        }
    }

    // See if there are enough free frames
    if (freeFrameList.size() < allocSize)
    {
        cout << "There are not enough free frames" << endl;
        return -1;
    }
    else
    {
        processList[processListIndex].pageTable = new page[allocSize];
        for(int i =0; i < allocSize; i++)
        {
            int randomFrame = rand() % freeFrameList.size();
            processList[processListIndex].pageTable[i].frame = randomFrame;
            freeFrameList.erase(freeFrameList.begin() + randomFrame);
            memory[randomFrame] = pid;

        }
    }


    return 1;
}