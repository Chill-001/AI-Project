#include <stdio.h>
#include "state.cpp"

// include algorithms from algorithms folder
#include "algorithms/aStar.cpp"


int main() {
    State start;
    State goal; 

    if(start.isPossible() != goal.isPossible()) {
        printf("No path can connect from the start State to the goal State.\n");
        return 0;
    }

    /*
    int mode = 0;

    switch (mode)
    {
    case 1:
        //dfs
        break;
    case 2:
        //iddfs
        break;
    case 3:
        //bfs
        break;
    case 4:
        //greedy
        break;
    case 5:
        //aStar
        break;
    default:
        printf("No mode selected.\n");
        break;
    }
    */
}