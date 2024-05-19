#include "Menu.h"

//this needs to be refactored

void display_options(std::vector<std::string> options, int current_option, WINDOW* win, int y_offset, int x_offset) {
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	for (int i = 0; i < options.size(); i++) {
		if (i == current_option) {
			mvwprintw(win, y_offset + i, x_offset, ("<" + options[i] + ">").c_str());
		}
		else {
			mvwprintw(win, y_offset + i, x_offset, options[i].c_str());
		}
	}
}

void display_map(WINDOW* win, MineSweeper::CellMap map, int y_offset, int x_offset, int active_cell_x, int active_cell_y) {
	for (int y = 0; y < map.height(); y++) {
		for (int x = 0; x < map.width(); x++) {
			if (x == active_cell_x && y == active_cell_y) {
				mvwprintw(win, y_offset + y, x_offset + x, "x");
				continue;
			}

			MineSweeper::Cell cell = map.get_cell(x,y);
			if (!cell.is_opened() && !cell.is_flagged()) mvwaddch(win,y_offset + y, x_offset + x, ACS_CKBOARD);
			else if(cell.is_flagged()) mvwprintw(win, y_offset + y, x_offset + x, ">");
			else if(cell.is_mined()) mvwprintw(win, y_offset + y, x_offset + x, "*");
			else {
				int mines_nearby = map.count_surrounding_mines(x, y);
				if(mines_nearby > 0) mvwprintw(win, y_offset + y, x_offset + x, "%d", mines_nearby);
				else mvwprintw(win, y_offset + y, x_offset + x, ".");
			}
		}
	}
}

void difficulty_menu(WINDOW* win) {
	std::vector<std::string> options = { "Easy", "Medium", "Hard", "Back to menu"};

	int active_option = 0;
	int key;
	while (1) {
		wclear(win);
		box(win, 0, 0);
		mvwprintw(win, 1, 1, "Choose the difficulty:");
		display_options(options, active_option, win, 3, 1);
		key = wgetch(win);

		switch (key) {
		case 259:
			if (active_option > 0) active_option--;
			break;
		case 258:
			if (active_option < options.size() - 1) active_option++;
			break;
		case 10:
			if (active_option < 3) game(win, active_option);
			else main_menu(win);
			break;
		}
	}

	return;
}

void about(WINDOW* win) {
	wclear(win);
	box(win, 0, 0);
	mvwprintw(win, 1, 1, "This is the open source minesweeper game clone, implemented");
	mvwprintw(win, 2, 1, "using C++ and ncurses library! Enjoy it :)");
	mvwprintw(win, 3, 1, "Author: Grigory Vorobiov");
	mvwprintw(win, 6, 1, "Press any key to continue..");
	wgetch(win);
	main_menu(win);
}

void main_menu(WINDOW* win) {
	std::vector<std::string> options = { "Start the game", "About", "Exit" };
	int active_option = 0;

	int key;

	while (1) {
		wclear(win);
		box(win, 0, 0);
		mvwprintw(win, 1, 1, "Welcome to the clone of the windows minesweeper game! Use arrow keys to navigate.");
		display_options(options, active_option, win, 2, 1);
		key = wgetch(win);
		
		switch (key) {
			case 259:
				if (active_option > 0) active_option--;
				break;
			case 258:
				if (active_option < options.size() - 1) active_option++;
				break;
			case 10:
				switch (active_option) {
					case 0:
						difficulty_menu(win);
						break;
					case 1:
						about(win);
						break;
					case 2:
						return;
				}
		}
	}

	return;
}

void game(WINDOW* win, int difficulty) {
	wclear(win);
	box(win, 0, 0);

	int map_width;
	int map_height;
	int active_cell_x = 0;
	int active_cell_y = 0;
	int mines;
	bool first_cell = true;
	
	int cells_to_open;

	switch (difficulty) {
	case 0:
		map_width = map_height = 9;
		mines = 8;
		break;
	case 1:
		map_width = map_height = 16;
		mines = 30;
		break;
	case 2:
		map_width = 30;
		map_height = 16;
		mines = 70;
		break;
	}

	MineSweeper::CellMap map(map_width, map_height);
	cells_to_open = map_width * map_height - mines;

	int key;
	while (1) {
		wclear(win);
		box(win, 0, 0);
		display_map(win, map, 1, 1, active_cell_x, active_cell_y);
		if (cells_to_open == 0) {
			mvwprintw(win, map_height + 5, 1, "You won! Yaay!");
			mvwprintw(win, map_height + 6, 1, "Press any key to continue.");
			wgetch(win);
			difficulty_menu(win);
		}
		mvwprintw(win, map_height + 1, 1, "Cells left: %d", cells_to_open);
		key = wgetch(win);

		switch (key) {
			case 'w':
			case 'W':
				if (active_cell_y > 0) active_cell_y--;
				break;
			case 's':
			case 'S':
				if (active_cell_y < map_height - 1) active_cell_y++;
				break;
			case 'a':
			case 'A':
				if (active_cell_x > 0) active_cell_x--;
				break;
			case 'd':
			case 'D':
				if (active_cell_x < map_width - 1) active_cell_x++;
				break;
			case 'e':
			case 'E':
			{
				MineSweeper::Cell& cell = map.get_cell(active_cell_x, active_cell_y);

				if (first_cell) {
					map.get_cell(active_cell_x, active_cell_y).open();
					map.plant_mines(mines);
					cells_to_open -= map.open_recursively(active_cell_x, active_cell_y);
					first_cell = false;
				}
				else if (cell.is_mined()) {
					map.open_all();
					display_map(win, map, 1, 1, active_cell_x, active_cell_y);
					mvwprintw(win, map_height + 5, 1, "You got exploded :P HAAAAA");
					wgetch(win);
					difficulty_menu(win);
				}

				else if (!cell.is_flagged()) cells_to_open -= map.open_recursively(active_cell_x, active_cell_y);
				break;
			}
			case 'q':
			case 'Q':
			{
				MineSweeper::Cell& cell = map.get_cell(active_cell_x, active_cell_y);
				
				if (cell.is_flagged()) cell.deflag();
				else cell.put_flag();
				break;
			}
		}
	}

	map.plant_mines(mines);
	display_map(win, map, 1, 1, active_cell_x, active_cell_y);
	refresh();
	wgetch(win);
}
