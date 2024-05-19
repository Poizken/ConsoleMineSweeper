#include<cursesw.h>
#include <vector>
#include <string>
#include <MineSweeper/CellMap.h>

void main_menu(WINDOW* win);
void game(WINDOW* win, int difficulty);
void display_options(std::vector<std::string> options, int current_option, WINDOW* win, int y_offset, int x_offset);
void display_map(WINDOW* win, MineSweeper::CellMap map, int y_offset, int x_offset, int active_cell_x, int active_cell_y);
void difficulty_menu(WINDOW* win);
void about(WINDOW* win);
void main_menu(WINDOW* win);
void game(WINDOW* win, int difficulty);
