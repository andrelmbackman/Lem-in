# Lem-in

Lem-in is an algorithmic project that aims to find the quickest way to get n ants across a farm.

### Project Goals

The main goal of the project is to find the shortest path to get all ants from the start room to the end room. This path should be represented by the least number of lines possible. At each turn, only the ants that moved should be displayed. Each ant can move only once per turn, and it can only move through a tube. The room at the receiving end must be empty. The solution must be displayed on the standard output in the following format:

    number_of_ants
    the_rooms
    the_links
    L1-A L2-B L3-C ...


where 1, 2, and 3 represent the ants' numbers (going from 1 to number_of_ants), and A, B and C represent the rooms' names.
### Description of the Farm

The farm is represented by rooms that are connected through links. The farm has a start room and an end room. Ants start in the start room and must find their way to the end room. Each room can only contain one ant at a time. The goal is to bring all the ants to the end room in as few turns as possible.

The farm is defined by two parts: rooms and links. The rooms are defined by name coord_x coord_y, and the links are defined by name1-name2. All of it is broken by comments that start with #. The rooms’ names won’t necessarily be numbers, and they won’t necessarily be in the right and continuous order. Rooms’ coordinates will always be integers. Lines that start with ## are commands modifying the properties of the line that comes right after. For example, ##start signals the ant farm’s entrance and ##end its exit. Any unknown command will be ignored. Any non-compliant or empty lines will automatically stop the ant farm’s reading, as well as the orderly processing of the acquired data. If there isn’t enough data to process normally, the program will display an error message.
### Rules and Constraints

    The executable file must be named lem-in.
    The program must be written in C in accordance with the Norm.
    You are only allowed to use the following functions: malloc, free, read, write, strerror, perror, and exit.
    You must handle errors in a sensitive manner. In no way can your program quit in an unexpected manner (Segmentation fault, 
    bus error, double free, etc.).
    Your program cannot have memory leaks.
    You must submit a Makefile. The Makefile needs to compile the project. It can only recompile the program if necessary.

### Usage

To compile the program, run:
    make

To execute the program, run the following command:
    ./lem-in < [path_to_file]

where [path_to_file] is the path to the file that contains the definition of the farm.
### Example
    $> ./lem-in < subject.map
    3
    ##start
    0 1 0
    ##end
    1 5 0
    2 9 0
    3 13 0
    0-2
    2-3
    3-1
    L1-2
    L1-3 L2-2
    L1-1 L2-3 L
