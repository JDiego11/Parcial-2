#ifndef OTHELLOGAME_H
#define OTHELLOGAME_H

#include "data.h"
#include <iostream>

using namespace std;

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
    bool isGameOver(Data);
    void switchPlayer();
    int countTiles(char player);
    bool isEnclosed(int row, int col, int rowDir, int colDir);
};

#endif // OTHELLOGAME_H
