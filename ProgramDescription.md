Nate O'Meara 
Operating Systems Programming Assignment 3
11/20/2021

How to run:
Use this command: g++ ./main.cpp -o main && ./main
Follow the prompts and run the program commands.


Project design:
For this program I follwed the assinment directions and created all of the functions with the same parameters as explained. I added my own function to handle the user input and run the user's commands. The Command runner is a basic swithc case statement.
I have never used vectors before and I took the opportunity to learn about them by using throughout the program. I used vectors for the Memory, freeFrameList, processList, and the process pageTables.
The bassic design is that a user will first create physical memory using the memory manager, then they are able to allocate space for a process using the page table as a logical address and intermediate between the process and the physical memory