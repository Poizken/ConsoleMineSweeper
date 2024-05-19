#ifndef CELL_H
#define CELL_H

namespace MineSweeper {
	class Cell {
	private:
		bool mined = false;
		bool flagged = false;
		bool opened = false;
	public:
		//checks if this cell is mined
		bool is_mined();
		//checks if this cell is flagged
		bool is_flagged();
		//checks if cell is opened
		bool is_opened();
		//puts mine into this cell
		void put_mine();
		//puts flag into this cell
		void put_flag();
		//removes flag from this cell
		void deflag();
		//opens this cell
		void open();
	};
}

#endif