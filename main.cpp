// CSC 456 Assignment 3
// Nate O'Meara
// Due 11/21/2021

#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <string>
#include <sstream>


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

    string command = "";
    cout << "Enter a command or exit to quit: ";
    getline(cin, command);
    while ( command != "exit")
    {

        runCommands(command);
    
        cout << "\nEnter a command or exit to quit: ";
        getline(cin, command);

    }

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
    }
    
}


int allocate(int allocSize, int pid)
{
    for (int i =0; i < processList.size(); i++)
    {
        if(processList[i].pid == pid)
        {
            cout << "Process " << pid << " is already in use." << endl;
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
        for(int i =0; i < allocSize; i++)
        {
            int randomFrame = rand() % freeFrameList.size();
            newProcess.pageTable[i].frame = randomFrame;
            freeFrameList.erase(freeFrameList.begin() + randomFrame);
            

        }

        processList.push_back(newProcess);
    }


    return 1;
}

int deallocate( int pid)
{

     int processIndex = -1;

    for (int i = 0; i < processList.size(); i++)
    {
        if(processList[i].pid == pid)
        {
            processIndex = i;
        }
    }

    if(processIndex == -1)
    {
        cout << "\nNo process found with id of: "<<pid << endl;
        return -1;
    }

    for(int x = 0; x < processList[processIndex].size; x++)
            {
                int frameNum = processList[processIndex].pageTable[x].frame;
                freeFrameList.push_back(frameNum);

            }

            processList.erase(processList.begin() + processIndex);

    return 1;

}

int write( int pid, int logical_address)
{

    int value = 1;

    int processIndex = -1;

    for (int i = 0; i < processList.size(); i++)
    {
        if(processList[i].pid == pid)
        {
            processIndex = i;
        }
    }


    if(processIndex == -1)
    {
        cout << "\nNo process found with id of: "<<pid << endl;
        return -1;
    }
    else if (logical_address > processList[processIndex].size)
    {
        cout << "\nNo logical_address found with location of: "<<logical_address << endl;
        return -1;
    }
    
    int frameIndex = processList[processIndex].pageTable[logical_address].frame;
    memory[frameIndex] = value;

    return 1;

}

int read( int pid, int logical_address)
{

    int value = 0;

    int processIndex = 0;

    if(processIndex == -1)
    {
        cout << "\nNo process found with id of: "<<pid << endl;
        return -1;
    }
    else if (logical_address > processList[processIndex].size)
    {
        cout << "\nNo logical_address found with location of: "<<logical_address << endl;
        return -1;
    }

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
    stringstream ssCommand(command);

    char functionName = '0';
    string param1 = "";
    string param2 = "";

    ssCommand >> functionName >> param1 >> param2;

    functionName = tolower(functionName);
    switch (functionName)
    {
        case 'm' :
            // ssCommand << param1 << param2;

            memoryManager(stoi(param1), stoi(param2));

            break;
        
        case 'a' :
            // ssCommand << param1 << param2;
            allocate(stoi(param1), stoi(param2));
            break;
        
        case 'w' :
            // ssCommand << param1 << param2;
            write(stoi(param1), stoi(param2));


            break;
        
        case 'r' :
            // ssCommand << param1 << param2;
            read(stoi(param1), stoi(param2));

            break;
        
        case 'd' :
            // ssCommand << param1;
            deallocate(stoi(param1));
            break;
        
        case 'p' :
            printMemory();
            break;

        default:
            cout << "\n Unknown command - Please try again\n";
            break;
        }


}