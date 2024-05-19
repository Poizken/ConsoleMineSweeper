#ifndef CELLMAP_H
#define CELLMAP_H

#include "Cell.h"
#include <vector>

namespace MineSweeper {
	class CellMap {
		private:
			//this vector contains rows of cells. in other words, cells[x][y] means cell of xth column and yth row
			std::vector<std::vector<MineSweeper::Cell>> cells;
			int rows;
			int cols;
			int cells_to_open;
		public:
			//initializing map
			CellMap(int cols, int rows);
			int height();
			int width();
			//Checks if map has a sell in given coordinates.
			bool has_cell(int x, int y);
			//Mines random cells of the map. This method does not mine opened cells.
			void plant_mines(int amount);
			//returns cell by given coordinates
			MineSweeper::Cell& get_cell(int x, int y);
			//counts surrounding mines of given cell
			int count_surrounding_mines(int x, int y);
			int open_recursively(int x, int y);
			void open_all();
	};
}

#endif