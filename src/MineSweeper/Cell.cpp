#include "Cell.h"

namespace MineSweeper {

	//checks if this cell is mined
	bool Cell::is_mined() { return mined; }
	//checks if this cell is flagged
	bool Cell::is_flagged() { return flagged; }
	//checks if cell is opened
	bool Cell::is_opened() { return opened; }
	//puts mine into this cell
	void Cell::put_mine() { mined = true; }
	//puts flag into this cell
	void Cell::put_flag() { flagged = true; }
	//removes flag from this cell
	void Cell::deflag() { flagged = false; }
	//opens this cell
	void Cell::open() { opened = true; }
}