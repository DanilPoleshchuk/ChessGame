/*
 * board.h
 * ������ ������ � ������
 */
#pragma once

// ������ �����
#define BOARD_SIZE 8  

// ������������ �������
enum piece_color {
   WHITE, // �����
   BLACK  // ������
};

/* 
 * ������� ��������� �������� ����
 * board - ������� ������� ����
 * current_player - ������� ����� (����� ��� ������)
 */
void draw_board(const char board[BOARD_SIZE][BOARD_SIZE], const piece_color current_player);

/*
 * ������� �������� ������� �������
 * board - ������� ������� ����
 * piece  - ������ ������� ���������� ������
 * current_player - ������� ����� (����� ��� ������)
 * start_x start_y - ���������� ������ ������
 * end_x end_y - ���������� ���� ���������� ��������� ������
 * silent - �� �������� ������ � ������� 
 * ���������� ���������� ������� �������
 */
bool is_valide_move(char board[BOARD_SIZE][BOARD_SIZE], const char piece, const piece_color current_player, const int start_x, const int start_y, const int end_x, const int end_y, const bool silent);

/* 
 * ������� ����������� ������ (������ ��� �����)
 * piece  - ������
 * ���������� ������, ��������������� ��������� ������
 */
piece_color get_color(const char piece);
