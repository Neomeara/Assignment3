// CSC 456 Assignment 3
// Nate O'Meara
// Due 11/21/2021

#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <vector>
// #include <new>

using namespace std;

// Function Prototypes
void memoryManager( int, int);
int allocate( int, int);
int deallocate( int );
int write( int, int);
int read( int, int);
void printMemory();
void runCommands(string);

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
vector<int> memory;


int main()
{

    memoryManager(10, 1);
    printMemory();
    allocate(4,2);
    write(2,0);
    read(2,0);
    printMemory();

    deallocate(2);
    printMemory();

    return 0;
}

void memoryManager(int memSize, int frameSize)
{

    // we need allocated memory
    // we need a list of free frames

    for (int i = 0; i < memSize; i++)
    {
        memory.push_back(0);
        freeFrameList.push_back(i);
        cout << memory[i] << ", ";
    }
    
}


int allocate(int allocSize, int pid)
{
    for (int i =0; i < processList.size(); i++)
    {
        if(processList[i].pid == pid)
        {
            cout << "Process: " << pid << " is already in use." << endl;
            return -1;
            
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
        process newProcess = {.pid = pid, .size = allocSize, .pageTable = new page[allocSize]};
        // newProcess.pageTable = new page[allocSize];
        for(int i =0; i < allocSize; i++)
        {
            int randomFrame = rand() % freeFrameList.size();
            newProcess.pageTable[i].frame = randomFrame;
            freeFrameList.erase(freeFrameList.begin() + randomFrame);
            // memory[randomFrame] = pid;
            

        }

        processList.push_back(newProcess);
    }


    return 1;
}

int deallocate( int pid)
{

    for (int i = 0; i < processList.size(); i++ )
    {
        if (processList[i].pid == pid)
        {
            for(int x =0; x < processList[i].size; x++)
            {
                int frameNum = processList[i].pageTable[x].frame;
                memory[frameNum] = 0;
                freeFrameList.push_back(frameNum);

            }

            processList.erase(processList.begin() + i);
        }
    }

    return 1;

}

int write( int pid, int logical_address)
{

    int value = 1;

    int processIndex = 0;

    for (int i = 0; i < processList.size(); i++)
    {
        if(processList[i].pid == pid)
        {
            processIndex = i;
        }
    }
    
    int frameIndex = processList[processIndex].pageTable[logical_address].frame;
    memory[frameIndex] = value;

    return 1;

}

int read( int pid, int logical_address)
{

    int value = 0;

    int processIndex = 0;

    for (int i = 0; i < processList.size(); i++)
    {
        if(processList[i].pid == pid)
        {
            processIndex = i;
        }
    }
    
    int frameIndex = processList[processIndex].pageTable[logical_address].frame;
    value = memory[frameIndex];

    cout << "The value from logical_address " << logical_address << " in process " << pid << " is: " << value << endl; 

    return 1;

}

void printMemory()
{
    cout << endl << "------------------ PHYSICAL MEMORY ---------------------" << endl << " | ";

    for (int i = 0; i < memory.size(); i++)
    {
        cout << memory[i] << " | ";
    }
    

    cout << endl << "------------------ FREE FRAME LIST ---------------------" << endl;

    for (int i = 0; i < freeFrameList.size(); i++)
    {
        cout << freeFrameList[i] << ", ";
    }
    

    cout << endl << "------------------ PROCESS LIST ------------------------" << endl;

    for (int i = 0; i < processList.size(); i++)
    {
        cout << "PID: " << processList[i].pid << " SIZE: " << processList[i].size << " | ";
    }
    cout << endl << endl;

}

void runCommands(string command)
{
    string command = "";


}