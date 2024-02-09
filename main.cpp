/*
 * main.cpp
 * Основной модуль программы игры в шахматы.
 * Применяемая нотация:
 * r - ладья
 * n - конь
 * b - слон
 * q - ферзь
 * k - король
 * p - пешка
 */
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "board.h"

using namespace std;

// Тип игры
enum game_types {
   GAME_PERSON = 1, // Игра с человеком
   GAME_PC          // Игра с компьютером
};

/*
 * Точка входа приложения
 */
int main() {
   char board[BOARD_SIZE][BOARD_SIZE] = {
      {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
      {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
      {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
   };
   piece_color current_player = piece_color::WHITE;

   // Диалог при входе в программ
   setlocale(LC_ALL, "Rus");
   cout << "Выберите режим игры" << endl;
   cout << "1) против человека" << endl;
   cout << "2) против компьютера" << endl;
   cout << "ваш выбор: ";
   int game_type_val;
   cin >> game_type_val;
   game_types game_type = static_cast<game_types>(game_type_val);

   bool exit_flag = false;
   while (!exit_flag) {
      bool bot_complete = false;
      draw_board(board, game_type == GAME_PC ? piece_color::WHITE : current_player);
      if (current_player == piece_color::WHITE) {
         cout << "Сейчас ходят белые фигуры" << endl;
      } else {
         cout << "Сейчас ходят черные фигуры" << endl;
      }
      // фрагмент который нацелен на игру с ботом 
      if (game_type == GAME_PC && current_player == piece_color::BLACK) {
         cout << "Бот сходил" << endl;
         vector<pair<pair<int, int>, pair<int, int>>> possibleMoves = vector<pair<pair<int, int>, pair<int, int>>>();

         for (int startY = 0; startY < BOARD_SIZE; startY++) {
            for (int startX = 0; startX < BOARD_SIZE; startX++) {
               char piece = board[startY][startX];
               piece_color computerColor = get_color(piece);
               if (computerColor == piece_color::BLACK) {
                  // Проверяем возможные ходы для этой фигуры
                  for (int endY = 0; endY < BOARD_SIZE; endY++) {
                     for (int endX = 0; endX < BOARD_SIZE; endX++) {
                        if (is_valide_move(board, piece, computerColor, startX, startY, endX, endY, true)) {
                           possibleMoves.push_back({{startX, startY}, {endX, endY}});
                        }
                     }
                  }
               }
            }
         }

         // Выбираем случайный ход из доступных вариантов
         srand(static_cast<unsigned int>(time(0)));

         int randomIndex = possibleMoves.empty() ? 0 : (rand() % static_cast<int>(possibleMoves.size()));
         pair<pair<int, int>, pair<int, int>> selectedMove = possibleMoves[randomIndex];
         int startX = selectedMove.first.first;
         int startY = selectedMove.first.second;
         int endX = selectedMove.second.first;
         int endY = selectedMove.second.second;

         // Выполняем выбранный ход
         board[endY][endX] = board[startY][startX];
         board[startY][startX] = ' ';

         cout << "Компьютер сделал ход: " << static_cast<char>('a' + startX) << 8 - startY << " " << static_cast<char>('a' + endX) << 8 - endY << endl;
         current_player = (current_player == piece_color::BLACK) ? piece_color::WHITE : piece_color::BLACK;
         bot_complete = true;
      }

      if (!bot_complete) {
         //добавить сюда условие на режим игры (соло или с другом). если с другом то весь нижний код бомба, если же нет, тогда
         cout << "Напишите «сдаюсь» для выхода из программы. " << endl;
         cout << "Укажите фигуру и куда ей сходить через пробел (пример: a2 a3) или «сдаюсь» для выхода из программы: ";
         string s1;
         cin >> s1;
         bool s1_ok = false;
         if (s1 == string("сдаюсь") || s1 == string("б¤ обм"))
            exit_flag = true;
         char startCol, endCol;
         int startRow, endRow;
         if (s1.size() == 2) {
            startCol = s1[0];
            startRow = static_cast<int>(s1[1]) - static_cast<int>('0');
            s1_ok = (static_cast<int>(startCol) >= int('A') && int(startCol) <= int('H') || static_cast<int>(startCol) >= int('a') && int(startCol) <= int('h')) && static_cast<int>(startRow) >= 1 && int(startRow) <= 8;
         } else {
            startCol = ' ';
            startRow = 0;
         }
         bool s2_ok = false;
         if (!exit_flag && s1_ok) {
            string s2;
            cin >> s2;
            if (s2.size() == 2) {
               endCol = s2[0];
               endRow = static_cast<int>(s2[1]) - static_cast<int>('0');
               s2_ok = (static_cast<int>(endCol) >= int('a') && int(endCol) <= int('h') || static_cast<int>(endCol) >= int('A') && int(endCol) <= int('H')) && static_cast<int>(endRow) >= 1 && int(endRow) <= 8;
            } else {
               endCol = ' ';
               endRow = 0;
            }
         } else {
            cin.clear();
            cin.ignore(32767, '\n');
         }
         if (!exit_flag && s1_ok && s2_ok) {
            int sX = tolower(startCol) - static_cast<int>('a');
            int sY = BOARD_SIZE - startRow;
            int endX = tolower(endCol) - static_cast<int>('a');
            int endY = BOARD_SIZE - endRow;
            if (sX >= 0 && sX < BOARD_SIZE &&
               sY >= 0 && sY < BOARD_SIZE && 
               endX >= 0 && endX < BOARD_SIZE &&
               endY >= 0 && endY < BOARD_SIZE &&               
               is_valide_move(board, board[sY][sX], current_player, sX, sY, endX, endY, false)) {
               board[endY][endX] = board[sY][sX];
               board[sY][sX] = ' ';
               current_player = (current_player == piece_color::BLACK) ? piece_color::WHITE : piece_color::BLACK;
            }
         }
      }
   }
   return 0;
}
