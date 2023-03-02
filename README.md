# Lem-in

Lem-in is an algorithmic project that aims to find the quickest way to get n ants across a farm. Pair project created in collaboration with Leo Tran. https://github.com/Officialrwn

### Project Goals

The main goal of the project is to find the shortest path to get all ants from the start room to the end room. This path should be represented by the least number of lines possible. At each turn, only the ants that moved should be displayed. Each ant can move only once per turn, and it can only move through a tube. The room at the receiving end must be empty. The solution must be displayed on the standard output in the following format:

    number_of_ants
    the_rooms
    the_links
    L1-A L2-B L3-C ...


where 1, 2, and 3 represent the ants' numbers (going from 1 to number_of_ants), and A, B and C represent the rooms' names.

### How the algorithm works
#### Breadth-first search finds the shortest path and/or augmenting paths
![bfs](https://user-images.githubusercontent.com/88145164/222154617-88aae94e-4f88-4966-bdd7-ace0b8bc5b13.gif)

#### The ants get sent with optimal distribution of flow to prevent bottlenecks
![send_ants](https://user-images.githubusercontent.com/88145164/222154821-677c3183-3628-4d85-8aff-8ce2162a9d84.gif)
#### An example of what this looks like in practice can be found at the bottom of this README.

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
##### To compile the program, run:
     $> make

##### To execute the program, run:
     $> ./lem-in < [path_to_file]
where [path_to_file] is the path to the file that contains the definition of the farm.    
##### Or simply make \<test1-test4\>, such as:
      $> make test1

### Example
    $> ./lem-in < eval_tests/cases/solution.map
    10
    ##start
    s 0 5
    ##end
    end 10 5
    a 1 1
    b 2 5
    c 2 10
    d 4 1
    e 6 1
    f 4 4
    g 3 9
    h 4 10
    i 7 4
    j 5 5
    k 5 10
    l 9 4
    m 8 5
    n 7 10
    o 9 10
    s-a
    s-b
    s-c
    a-d
    b-f
    c-g
    c-h
    d-e
    e-i
    f-i
    f-j
    g-j
    g-h
    h-k
    i-l
    j-m
    k-n
    l-end
    m-end
    n-o
    o-end
    #
    #       a -- d - e
    #      /           \
    #     /   f ------- i -- l
    #    /   /   \             \
    #   S - b     j ----- m ---- end
    #    \       /              /
    #     \    g               /
    #      \ /  |             /
    #       c - h - k - n - o 

    L1-b L2-a L3-c
    L1-f L4-b L2-d L5-a L3-h L6-c
    L1-j L4-f L7-b L2-e L5-d L8-a L3-k L6-h L9-c
    L1-m L4-j L7-f L10-b L2-i L5-e L8-d L3-n L6-k L9-h
    L1-end L4-m L7-j L10-f L2-l L5-i L8-e L3-o L6-n L9-k
    L4-end L7-m L10-j L2-end L5-l L8-i L3-end L6-o L9-n
    L7-end L10-m L5-end L8-l L6-end L9-o
    L10-end L8-end L9-end
