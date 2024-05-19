#include "CellOutOfRangeException.h"

namespace MineSweeper::Exception {

    CellOutOfRangeException::CellOutOfRangeException(int x, int y) {
        this->x = x;
        this->y = y;
    }
    
    //char* CellOutOfRangeException::what() { return "Attempt of accessing coordinates outside of the map"; }
}