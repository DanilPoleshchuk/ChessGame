/*
 * board.h
 * ћодуль работы с доской
 */
#pragma once

// –азмер доски
#define BOARD_SIZE 8  

// ѕеречисление игроков
enum piece_color {
   WHITE, // Ѕелые
   BLACK  // „ерные
};

/* 
 * ‘ункци€ отрисовки игрового пол€
 * board - текущее игровое поле
 * current_player - текущий игрок (белые или черные)
 */
void draw_board(const char board[BOARD_SIZE][BOARD_SIZE], const piece_color current_player);

/*
 * ‘ункци€ проверки игровых условий
 * board - текущее игровое поле
 * piece  - фигура которой собираютс€ ходить
 * current_player - текущий игрок (белые или черные)
 * start_x start_y - координаты вз€той фигуры
 * end_x end_y - координаты куда собираютс€ поставить фигуру
 * silent - не выводить ничего в консоль 
 * ¬озвращает валидность игровых условий
 */
bool is_valide_move(char board[BOARD_SIZE][BOARD_SIZE], const char piece, const piece_color current_player, const int start_x, const int start_y, const int end_x, const int end_y, const bool silent);

/* 
 * ‘ункци€ определени€ игрока (черные или белые)
 * piece  - фигура
 * ¬озвращает игрока, соответсвующего указанной фигуре
 */
piece_color get_color(const char piece);
