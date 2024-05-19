#include "CellMap.h"
#include "Exceptions/CellOutOfRangeException.h"

namespace MineSweeper {
	using std::vector;
	using MineSweeper::Cell;


	CellMap::CellMap(int cols, int rows) {
			this->rows = rows;
			this->cols = cols;
				
			for (int i = 0; i < cols; i++) {
				cells.push_back(vector<MineSweeper::Cell>(rows));
				for (int j = 0; j < rows; j++) {
					cells[i][j] = Cell();
				}
			}
		}

	int CellMap::height() { return rows; }
	int CellMap::width() { return cols; }

	//Checks if map has a sell in given coordinates.
	bool CellMap::has_cell(int x, int y) {
		if (x >= 0 && x < cols && y >= 0 && y < rows) return true;
		return false;
	}

	//Mines random cells of the map. This method does not mine opened cells.
	void CellMap::plant_mines(int amount) {
		for (int i = 0; i < amount;) {
			int x = rand() % cols;
			int y = rand() % rows;

			//we only increment if current random cell both not mined and not opened
			if (!cells[x][y].is_mined() && !cells[x][y].is_opened()) {
				cells[x][y].put_mine();
				i++;
			}
		}

		cells_to_open = cols * rows - amount;
	}

	//returns cell by given coordinates
	Cell& CellMap::get_cell(int x, int y) {
		if (!has_cell(x, y))
			throw Exception::CellOutOfRangeException(x, y);

		return cells[x][y];
	}

	//counts surrounding mines of given cell
	int CellMap::count_surrounding_mines(int x, int y) {
		if (!has_cell(x, y))
			throw Exception::CellOutOfRangeException(x, y);

		//There's a chance given cell is either in the corner or border of the map, so we do some checkings.
		int mines = 0;
		//are there cells left to given sell (in other word, is given cell not located in left border)?
		if (x - 1 >= 0) {
			mines += int{get_cell(x-1,y).is_mined()};
			if (y - 1 >= 0) mines += int{get_cell(x-1,y-1).is_mined()};
			if (y + 1 < rows) mines += int{get_cell(x-1,y+1).is_mined()};
		}
		//are there cells right to given sell (in other word, is given cell not located in the right border)?
		if (x + 1 < cols) {
			mines += int{get_cell(x+1,y).is_mined()};
			if (y - 1 >= 0) mines += int{get_cell(x+1,y-1).is_mined()}; 
			if (y + 1 < rows) mines += int{get_cell(x+1,y+1).is_mined()};
		}
		//same for top & bottom
		if (y - 1 >= 0) mines += int{get_cell(x,y-1).is_mined()};
		if (y + 1 < rows) mines += int{get_cell(x,y+1).is_mined()};
		return mines;
	}

	int CellMap::open_recursively(int x, int y) {
		if (!has_cell(x, y))
			throw Exception::CellOutOfRangeException(x, y);
		if (get_cell(x, y).is_flagged() || get_cell(x,y).is_mined())
			return 0;

		get_cell(x,y).open();
		int cells_opened = 1;

		if (count_surrounding_mines(x, y) > 0) return cells_opened;

		if (x - 1 >= 0) {
			if (!get_cell(x-1, y).is_opened()) cells_opened += open_recursively(x-1, y);
			if (y - 1 >= 0 && !get_cell(x-1, y-1).is_opened()) cells_opened += open_recursively(x-1, y-1);
			if (y + 1 < rows && !get_cell(x-1, y+1).is_opened()) cells_opened += open_recursively(x-1, y+1);
		}
		if (x + 1 < cols) {
			if (!get_cell(x+1, y).is_opened()) cells_opened += open_recursively(x+1, y);
			if (y - 1 >= 0 && !get_cell(x+1, y-1).is_opened()) cells_opened += open_recursively(x+1, y-1);
			if (y + 1 < rows && !get_cell(x+1, y+1).is_opened()) cells_opened += open_recursively(x+1, y+1);
		}
		if (y - 1 >= 0 && !get_cell(x, y-1).is_opened()) cells_opened += open_recursively(x, y-1);
		if (y + 1 < rows && !get_cell(x, y+1).is_opened()) cells_opened += open_recursively(x, y+1);

		return cells_opened;
	}

	void CellMap::open_all() {
		for (int i = 0; i < cols; i++) {
			for (int j = 0; j < rows; j++) {
				cells[i][j].open();
			}
		}
	}
}