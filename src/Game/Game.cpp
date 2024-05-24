#include "Game.h"

namespace Game {
	Game::Game(int map_width, int map_height, int mines_to_plant) : _map(MineSweeper::CellMap(map_width, map_height)) {
		_map_width = map_width;
		_map_height = map_height;
		_mines_to_plant = mines_to_plant;
		_cells_left = _map_width * _map_height - _mines_to_plant;
		_status = GameStatus::NOT_STARTED;
	}

	void Game::open_cell(int x, int y) {
		MineSweeper::Cell& cell = _map.get_cell(x, y);

		//If we put mines before player opens first cell, there's always chance they will hit mined cell. To prevent this, we plant mines
		//only after player opens the first cell. 
		if (_status == GameStatus::NOT_STARTED) {
			_map.get_cell(x, y).open();
			_map.plant_mines(_mines_to_plant);
			_cells_left -= _map.open_recursively(x, y);
			_status = GameStatus::STARTED;
		}
		//If player hits mined cell, we open all cells and set game's status to GameStatus::LOSS
		else if (cell.is_mined()) {
			_map.open_all();
			_status = GameStatus::LOSS;
		} 
		else if (!cell.is_flagged()) _cells_left -= _map.open_recursively(x, y);

		if (_cells_left == 0) _status = GameStatus::WIN;
	}

	void Game::put_flag(int x, int y) {
		MineSweeper::Cell& cell = _map.get_cell(x, y);

		if (cell.is_flagged()) cell.deflag();
		else cell.put_flag();
	}

	const MineSweeper::CellMap& Game::get_map() {
		return _map;
	}

	GameStatus Game::status() {
		return _status;
	}

	int Game::cells_left() {
		return _cells_left;
	}
}