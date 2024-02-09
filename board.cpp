/*
 * board.cpp
 * Модуль работы с доской
 */
#include "board.h"
#include <iostream>
#include <cctype>

using namespace std;

/*
 * Функция отрисовки игрового поля
 * board - текущее игровое поле
 * current_player - текущий игрок (белые или черные)
 */
void draw_board(const char board[BOARD_SIZE][BOARD_SIZE], const piece_color current_player) {
   if (current_player == piece_color::WHITE) {
      cout << "    a   b   c   d   e   f   g   h " << endl;
      cout << "  +---+---+---+---+---+---+---+---+" << endl;
      for (int i = 0; i < BOARD_SIZE; i++) {
         cout << BOARD_SIZE - i << " ";
         for (int j = 0; j < BOARD_SIZE; j++) {
            cout << "| " << board[i][j] << " ";
         }
         cout << "| " << BOARD_SIZE - i << endl;
         cout << "  +---+---+---+---+---+---+---+---+" << endl;
      }
      cout << "    a   b   c   d   e   f   g   h " << endl;
   } else {
      cout << "    h   g   f   e   d   c   b   a " << endl;
      cout << "  +---+---+---+---+---+---+---+---+" << endl;
      for (int i = 0; i < BOARD_SIZE; i++) {
         cout << i + 1 << " ";
         for (int j = 0; j < BOARD_SIZE; j++) {
            cout << "| " << board[BOARD_SIZE - 1 - i][BOARD_SIZE - 1 - j] << " ";
         }
         cout << "| " << i + 1 << endl;
         cout << "  +---+---+---+---+---+---+---+---+" << endl;
      }
      cout << "    h   g   f   e   d   c   b   a " << endl;
   }
}

/*
 * Функция проверки игровых условий
 * board - текущее игровое поле
 * piece  - фигура которой собираются ходить
 * current_player - текущий игрок (белые или черные)
 * start_x start_y - координаты взятой фигуры
 * end_x end_y - координаты куда собираются поставить фигуру
 * silent - не выводить ничего в консоль
 * Возвращает валидность игровых условий
 */
bool is_valide_move(char board[BOARD_SIZE][BOARD_SIZE], const char piece, const piece_color current_player, const int start_x, const int start_y, const int end_x, const int end_y, const bool silent) {
   //если фигура не на доске 
   if (start_x < 0 || start_x >= BOARD_SIZE || start_y < 0 || start_y >= BOARD_SIZE || end_x < 0 || end_x >= BOARD_SIZE || end_y < 0 || end_y >= BOARD_SIZE) {
      return false;
   }

   // е=выбрал ли игрок пустую ячейку вместо фигуры 
   if (board[start_y][start_x] == ' ') {
      if (!silent)
         cout << "Вы выбрали пустую ячейку!" << endl;
      return false;
   }

   // 
   if (board[start_y][start_x] != piece) {
      return false;
   }

   //нельзя сходить в ту же точку на которой изначально стояла фигура
   if (start_x == end_x && start_y == end_y) {
      if (!silent)
         cout << "Вы не можете сходить фигурой в одну и ту же точку! " << endl;
      return false;
   }

   //чтобы свои же фигуры ты не съел
   if (get_color(board[end_y][end_x]) == current_player && board[end_y][end_x] != ' ') {
      if (!silent)
         cout << "Ты тупой, своих не хавай! " << endl;
      return false;
   }

   //свой ли ход
   if (get_color(piece) != current_player) {
      if (!silent)
         cout << "Сейчас не ваш ход!" << endl;
      return false;
   }

   // логика ходьбы 
   char piece_type = tolower(piece);
   int dx = end_x - start_x;
   int dy = end_y - start_y;
   piece_color opposite_player = current_player == piece_color::WHITE ? piece_color::BLACK : piece_color::WHITE;
   switch (piece_type) {
      //пешки
      case 'p':
         //логика для белых пешек 
         if (current_player == piece_color::WHITE) {
            //ход вперед на один
            if (dy == -1 && dx == 0 && board[end_y][end_x] == ' ') {
               return true;
            }
            //ход вперед на две клетки из начального положения
            else if (start_y == 6 && dy == -2 && dx == 0 && board[end_y][end_x] == ' ' && board[start_y - 1][start_x] == ' ') {
               return true;
            }
            //ход для поедания по диагонали
            else if (abs(dx) == 1 && dy == -1 && get_color(board[end_y][end_x]) == piece_color::BLACK && board[end_y][end_x] != ' ') {
               board[start_y][start_x + dx] = ' ';
               return true;
            }
            //ход для поедания по диагонали (взятие на проходе)
            else if (start_y == 5 && abs(dx) == 1 && dy == -1 && get_color(board[start_y][start_x + dx]) == piece_color::BLACK && board[start_y][start_x + dx] == 'p' && board[end_y][end_x] != ' ') {
               board[start_y][start_x + dx] = ' ';
               return true;
            }
         }
         //логика для черных пешек 
         else {
            //ход вперед на один
            if (dy == 1 && dx == 0 && board[end_y][end_x] == ' ') {
               return true;
            }
            //ход вперед на две клетки из начального положения
            else if (start_y == 1 && dy == 2 && dx == 0 && board[end_y][end_x] == ' ' && board[start_y + 1][start_x] == ' ') {
               return true;
            }
            //ход поедания по диагонали
            else if (abs(dx) == 1 && dy == 1 && get_color(board[end_y][end_x]) == piece_color::WHITE && board[end_y][end_x] != ' ') {
               board[start_y][start_x + dx] = ' ';
               return true;
            }
            //ход поедания по диагонали (взятие на проходе)
            else if (start_y == 4 && abs(dx) == 1 && dy == 1 && get_color(board[start_y][start_x + dx]) == piece_color::WHITE && board[start_y][start_x + dx] == 'p' && board[end_y][end_x] != ' ') {
               board[start_y][start_x + dx] = ' ';
               return true;
            }

         }
         return false;
         //кони
      case 'n':
         if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
            return true;
         }
         return false;
      case 'q': // ферзь
      case 'k': // король
      case 'r': // ладья 
      case 'b': // слон          
         {
            bool rock_valid = true;
            //горизонтальное движение
            if (dx != 0 && dy == 0) {
               int step_x = (dx > 0) ? 1 : -1;
               for (int x = start_x + step_x; x != end_x && rock_valid; x += step_x) {
                  bool is_last = x == end_x;
                  if (is_last) {
                     if (board[end_y][end_x] == ' ')
                        rock_valid = true;
                     else if (get_color(board[end_y][end_x]) == opposite_player)
                        rock_valid = true;
                     else
                        rock_valid = false;
                  } else {
                     if (board[start_y][x] != ' ') {
                        rock_valid = false; // есть препятствие на пути
                     }
                  }
               }
            }
            //вертикальное движение
            else if (dx == 0 && dy != 0) {
               int step_y = (dy > 0) ? 1 : -1;
               for (int y = start_y + step_y; y != end_y && rock_valid; y += step_y) {
                  bool is_last = y == end_y; if (is_last) {
                     if (board[end_y][end_x] == ' ')
                        rock_valid = true;
                     else if (get_color(board[end_y][end_x]) == opposite_player)
                        rock_valid = true;
                     else
                        rock_valid = false;
                  } else {
                     if (board[y][start_x] != ' ') {
                        rock_valid = false; // есть препятствие 
                     }
                  }
               }
            } else {
               rock_valid = false;
            }
            bool bishop_valid = true;
            //диагональное движение
            if (dx != 0 && dy != 0 && abs(dx) == abs(dy)) {
               int step_x = (dx > 0) ? 1 : -1;
               int step_y = (dy > 0) ? 1 : -1;
               for (int i = 1; i <= abs(dx) && bishop_valid; ++i) {
                  bool is_last = i == abs(dx);
                  if (is_last) {
                     if (board[end_y][end_x] == ' ')
                        bishop_valid = true;
                     else if (get_color(board[end_y][end_x]) == opposite_player)
                        bishop_valid = true;
                     else
                        bishop_valid = false;
                  } else {
                     if (board[start_y + i * step_y][start_x + i * step_x] != ' ') {
                        bishop_valid = false; // есть препятствие на пути
                     }
                  }
               }
            } else {
               bishop_valid = false;
            }
            if (piece_type == 'r')
               return rock_valid;
            else if (piece_type == 'b')
               return bishop_valid;
            else if (piece_type == 'q')
               return rock_valid || bishop_valid;
            else
               return (rock_valid || bishop_valid) && abs(dx) <= 1 && abs(dy) <= 1;
         }
   }
   return false;
}

/*
 * Функция определения игрока (черные или белые)
 * piece  - фигура
 * Возвращает игрока, соответсвующего указанной фигуре
 */
piece_color get_color(const char piece) {
   if (islower(piece)) {
      return piece_color::BLACK;
   }
   return piece_color::WHITE;
}
