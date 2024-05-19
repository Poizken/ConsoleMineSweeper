#ifndef MSEXCEPTION_H
#define MSEXCEPTION_H

#include <exception>

namespace MineSweeper {
	namespace Exception{
		class MinesweeperException : public std::exception {};
	}
}

#endif