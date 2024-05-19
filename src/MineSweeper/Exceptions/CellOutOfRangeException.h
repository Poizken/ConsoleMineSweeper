#ifndef MSEXCEPTIONCOOR_H
#define MSEXCEPTIONCOOR_H

#include "MinesweeperException.h"

namespace MineSweeper::Exception {
    class CellOutOfRangeException : public MineSweeper::Exception::MinesweeperException {
    public:
        int x;
        int y;
        CellOutOfRangeException(int x, int y);
    };
}

#endif