#include <iostream>
#include <array>
#include <string.h>

#define MAXSIZE 16
#define SIDE 4

#define set0(a) memset(a, 0, sizeof(a))

int abs(int* a) {
    if (a > 0) return *a;
    return -*(a);
}

// copies an array (source / src) to another array (destination / dest)
void copyArray(int* src, int* dest) {
    for (int i = 0; i < MAXSIZE; i++) {
        *(dest+i) = *(src+i);
    }
}


/*State is the a class that holds the board configuration
It has the board values, blank space coordinates and a pointer to the respective parent it came from*/
class State {
    private:
        int values[MAXSIZE];
    
    public:
        int blankX, blankY;
        State* parent;

        //Constructors
        State();
        State(int values[MAXSIZE], int blankX, int blankY, State* parent);

        //Methods
        //Move function that creates another State, and makes the current state its parent 
        State* move(int dir);

        //function that checks if its possible to reach the "Norm" solution
        bool isPossible();

        //Checks if the current state is valid, meaning, if the blank space isn't offbounds
        bool isValid();

        //checks if current State is the same as another that already was passed through
        bool checkSameState(State* current);

        //simple print function
        void printBoard();
};

State::State() {
    set0(values);
    blankX = 0;
    blankY = 0;
    parent = NULL;

    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            int tmp;
            scanf("%d", &tmp);
            if (tmp == 0) {
                blankX = j;
                blankY = i;
            }
            values[i*SIDE +j] = tmp;
        }
    }
}

State::State(int vals[MAXSIZE], int posX, int posY, State* p) {
    copyArray(vals, values);
    blankX = posX;
    blankY = posY;
    parent = p;
}

State* State::move(int dir) {
    int tmp[MAXSIZE];
    set0(tmp);
    copyArray(values, tmp);
    int posX = blankX;
    int posY = blankY;
    int pos = posY*SIDE + posX;

    switch (dir) {
        // move up
        case 0:
            tmp[pos] = tmp[pos-4];
            pos -= 4;
            blankY -= 1;
            tmp[pos] = 0;
            break;
        
        // move right
        case 1:
            tmp[pos] = tmp[pos+1];
            pos += 1;
            blankX += 1;
            tmp[pos] = 0;
            break;

        // move down
        case 2:
            tmp[pos] = tmp[pos+4];
            pos += 4;
            blankY += 1;
            tmp[pos] = 0;
            break;
        
        // move left
        case 3:
            tmp[pos] = tmp[pos-1];
            pos -= 1;
            blankX -= 1;
            tmp[pos] = 0;
            break;
    }
    return new State(tmp, posX, posY, this);
}

bool State::isPossible() {
    // number of inversions
    int inv = 0;
    for (int i = 0; i < MAXSIZE; i++) {
        for (int j = i+1; j < MAXSIZE; j++) {
            inv += (values[i] > values[j] && values[i] != 0 && values[j] != 0);
        }
    }

    if (((4-blankY)%2 == 0 && inv%2 == 1) || ((4-blankY)%2 == 1 && inv%2 == 0)) return true;
    return false;
}

bool State::isValid() {
    return (blankX >= 0 && blankX < SIDE && blankY >= 0 && blankY < SIDE);
}

bool State::checkSameState(State* current) {
    if (current == NULL) return false;
    for (int i = 0; i < MAXSIZE; i++) {
        if (current->values[i] != values[i]) return this->checkSameState(current->parent);
    }
    return true;
}

void State::printBoard() {
    for (int i = 0; i < SIDE; i++) {
        printf("%d %d %d %d\n", values[i*SIDE], values[i*SIDE+1], values[i*SIDE+2], values[i*SIDE+3]);
    }
}

// Manhattan Function for A Star Search algorithm
int manhattanDistance(State* cur, State* goal) {
    return abs((cur->blankX+1) - (goal->blankX+1)) + abs((cur->blankY+1) - (goal->blankY+1));
}