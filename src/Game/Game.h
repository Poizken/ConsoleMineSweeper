#pragma once
#include "../MineSweeper/CellMap.h"

namespace Game {
	//Enumeration of possible game statuses: 
	enum class GameStatus { NOT_STARTED, //Everything is ready but player has not opened the first cell.
		STARTED, //Player opened at least one cell, game is going.
		WIN, //Player opened all cells and won.
		LOSS //Player hit mined cell and lost.
	};

	//This class represents the container of the game. It contains the cellmap and operates with it by the game's rules.
	class Game {
		private:
			//map of cells
			MineSweeper::CellMap _map;
			//width of the map in cells
			int _map_width;
			//height of the map in cells
			int _map_height;
			//the amount of mines to plant
			int _mines_to_plant;

			//Amount of unopened non-mined cells. If this variable equals 0, this means that all cells without mines are opened and player won.
			int _cells_left;
			//Game status
			GameStatus _status;

		public:
			Game(int map_width, int map_height, int mines_to_plant);

			/* Opens cell by given coordinates. If game's status == GameStatus::NOT_STARTED, or in other words, if this is the first opened cell,
			this metod plants mines into the map, ensuring that player cannot hit the mine on the very first cell.
			If cell on given coordinates is mined, game's status is set to GameStatus::LOSS and all cells are automatically opened.
			If cell is both non-mined and non-flagged, method opens the cell and all cells nearby in case they're not neighbours of mined cells.
			*/
			void open_cell(int x, int y);
			//Puts flag on cell by given coordinates
			void put_flag(int x, int y);
			//Returns status of the game
			GameStatus status();
			//Returns amount of unopened cells without mines.
			int cells_left();
			//Returns the map of cells
			const MineSweeper::CellMap& get_map();
	};
}
