#ifndef OTHELLOGAME_H
#define OTHELLOGAME_H

#include <iostream>
using namespace std;

const int BOARD_SIZE = 8;

class OthelloGame {
public:
    OthelloGame();
    ~OthelloGame();
    void play();

private:
    char **board;
    char currentPlayer;
    char oppositePlayer; // Agregamos esta variable

    void initializeBoard();
    void displayBoard();
    bool isValidMove(int row, int col);
    void makeMove(int row, int col);
    bool isGameOver();
    void switchPlayer();
    int countTiles(char player);
    bool isEnclosed(int row, int col, int rowDir, int colDir);
};

#endif // OTHELLOGAME_H
