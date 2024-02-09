/*
 * main.cpp
 * �������� ������ ��������� ���� � �������.
 * ����������� �������:
 * r - �����
 * n - ����
 * b - ����
 * q - �����
 * k - ������
 * p - �����
 */
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "board.h"

using namespace std;

// ��� ����
enum game_types {
   GAME_PERSON = 1, // ���� � ���������
   GAME_PC          // ���� � �����������
};

/*
 * ����� ����� ����������
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

   // ������ ��� ����� � ��������
   setlocale(LC_ALL, "Rus");
   cout << "�������� ����� ����" << endl;
   cout << "1) ������ ��������" << endl;
   cout << "2) ������ ����������" << endl;
   cout << "��� �����: ";
   int game_type_val;
   cin >> game_type_val;
   game_types game_type = static_cast<game_types>(game_type_val);

   bool exit_flag = false;
   while (!exit_flag) {
      bool bot_complete = false;
      draw_board(board, game_type == GAME_PC ? piece_color::WHITE : current_player);
      if (current_player == piece_color::WHITE) {
         cout << "������ ����� ����� ������" << endl;
      } else {
         cout << "������ ����� ������ ������" << endl;
      }
      // �������� ������� ������� �� ���� � ����� 
      if (game_type == GAME_PC && current_player == piece_color::BLACK) {
         cout << "��� ������" << endl;
         vector<pair<pair<int, int>, pair<int, int>>> possibleMoves = vector<pair<pair<int, int>, pair<int, int>>>();

         for (int startY = 0; startY < BOARD_SIZE; startY++) {
            for (int startX = 0; startX < BOARD_SIZE; startX++) {
               char piece = board[startY][startX];
               piece_color computerColor = get_color(piece);
               if (computerColor == piece_color::BLACK) {
                  // ��������� ��������� ���� ��� ���� ������
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

         // �������� ��������� ��� �� ��������� ���������
         srand(static_cast<unsigned int>(time(0)));

         int randomIndex = possibleMoves.empty() ? 0 : (rand() % static_cast<int>(possibleMoves.size()));
         pair<pair<int, int>, pair<int, int>> selectedMove = possibleMoves[randomIndex];
         int startX = selectedMove.first.first;
         int startY = selectedMove.first.second;
         int endX = selectedMove.second.first;
         int endY = selectedMove.second.second;

         // ��������� ��������� ���
         board[endY][endX] = board[startY][startX];
         board[startY][startX] = ' ';

         cout << "��������� ������ ���: " << static_cast<char>('a' + startX) << 8 - startY << " " << static_cast<char>('a' + endX) << 8 - endY << endl;
         current_player = (current_player == piece_color::BLACK) ? piece_color::WHITE : piece_color::BLACK;
         bot_complete = true;
      }

      if (!bot_complete) {
         //�������� ���� ������� �� ����� ���� (���� ��� � ������). ���� � ������ �� ���� ������ ��� �����, ���� �� ���, �����
         cout << "�������� �������� ��� ������ �� ���������. " << endl;
         cout << "������� ������ � ���� �� ������� ����� ������ (������: a2 a3) ��� �������� ��� ������ �� ���������: ";
         string s1;
         cin >> s1;
         bool s1_ok = false;
         if (s1 == string("������") || s1 == string("ᤠ���"))
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
