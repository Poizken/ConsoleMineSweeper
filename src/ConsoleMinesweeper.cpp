#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <exception>
#include <cursesw.h>
#include "MineSweeper/Exceptions/MinesweeperException.h"
#include "MineSweeper/Exceptions/CellOutOfRangeException.h"
#include "MineSweeper/Cell.h"
#include "MineSweeper/CellMap.h"
#include "Menu.h"

int main() {
    srand(time(0));
    //ncurses init
    initscr();
    noecho();
    curs_set(0);
    start_color();
    setlocale(LC_ALL, "");

    //get keycodes
    //keypad(stdscr, true);
    //while (1) { int i = getch(); printw("%d\n", i); refresh(); }

    int game_width = 0;
    int game_height = 0;

    getmaxyx(stdscr, game_height, game_width);
    WINDOW* game_window = newwin(game_height - 1, game_width - 1, 0, 0);
    keypad(game_window, true);

    main_menu(game_window);
    endwin();
    return 0;
}