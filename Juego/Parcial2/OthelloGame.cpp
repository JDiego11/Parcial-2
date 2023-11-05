#include "OthelloGame.h"

const int BOARD_SIZE = 8;

OthelloGame::OthelloGame() {
    board = new char*[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = new char[BOARD_SIZE];
    }
    currentPlayer = 'X';
    oppositePlayer = 'O'; // Inicializamos la variable
    initializeBoard();
}

OthelloGame::~OthelloGame() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void OthelloGame::initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    board[(BOARD_SIZE/2)-1] [(BOARD_SIZE/2)-1]  = 'X';
    board[(BOARD_SIZE/2)-1] [(BOARD_SIZE/2)]    = 'O';
    board[(BOARD_SIZE/2)]   [(BOARD_SIZE/2)-1]  = 'O';
    board[(BOARD_SIZE/2)]   [(BOARD_SIZE/2)]    = 'X';
}

void OthelloGame::displayBoard() {
    //cout << "\t";
    //system("cls");
    for(int i=0; i<BOARD_SIZE; i++) {
        //cout << (i + 1) << " ";
        if (i==0) cout << char(218);
        else cout << char(194);
        cout << char(196) << char(196) << char(196);

    }
     cout << char(191) << endl;

    //cout << "  1 2 3 4 5 6 7 8" << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        //cout << (i + 1);
        cout << char(179);
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout  << " " << board[i][j] << " " << char(179);
        }
        cout << endl;

        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i!=BOARD_SIZE-1) {
                if(j==0) cout << char(195);
                else cout << char(197);
            }
            else {
                if(j==0) cout << char(192);
                else cout << char(193);
            }

            //if (i==BOARD_SIZE)
            cout << char(196) << char(196) << char(196);
        }
        if (i!=BOARD_SIZE-1) cout << char(180) << endl;
        else cout << char(217) << endl;
    }
}

bool OthelloGame::isValidMove(int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ') {
        return false;
    }

    // Implement your own rules for a valid move here.
    bool valid = false;

    for (int rowDir = -1; rowDir <= 1; rowDir++) {
        for (int colDir = -1; colDir <= 1; colDir++) {
            if (rowDir == 0 && colDir == 0) continue;
            int r = row + rowDir;
            int c = col + colDir;
            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == oppositePlayer) {
                r += rowDir;
                c += colDir;
                if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == currentPlayer) {
                    valid = true;
                    break;
                }
            }
        }
    }

    return valid;
}

void OthelloGame::makeMove(int row, int col) {
    board[row][col] = currentPlayer;

    for (int rowDir = -1; rowDir <= 1; rowDir++) {
        for (int colDir = -1; colDir <= 1; colDir++) {
            if (rowDir == 0 && colDir == 0) continue;
            int r = row + rowDir;
            int c = col + colDir;
            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == oppositePlayer) {
                r += rowDir;
                c += colDir;
                if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == currentPlayer) {
                    int flipR = row + rowDir;
                    int flipC = col + colDir;
                    while (flipR != r || flipC != c) {
                        board[flipR][flipC] = currentPlayer;
                        flipR += rowDir;
                        flipC += colDir;
                    }
                }
            }
        }
    }
}

bool OthelloGame::isGameOver(Data data) {

    int xCount = countTiles('X');
    int oCount = countTiles('O');
    if (xCount + oCount == BOARD_SIZE * BOARD_SIZE) {
        short int option;
        if (xCount > oCount) {
            data.NewData("Jugador X", "Jugador O", 1, xCount);
            cout << "Jugador X gana!" << endl;
        } else if (oCount > xCount) {
            data.NewData("Jugador X", "Jugador O", 2, oCount);
            cout << "Jugador O gana!" << endl;
        } else {
            data.NewData("Jugador X", "Jugador O", 3, xCount);
            cout << "Es un empate." << endl;
        }displayBoard();
        data.WriteData();
        cout << "\nInformacion de la partida almacenada con exito \nDesea ver el historial de las partidas jugadas? \n1. Si \n2. No \nIngrese una opcion: ";
        cin >> option;
        if (option ==1 ){data.Winner_Historial();}
        return true;
    }
    return false;
}

int OthelloGame::countTiles(char player) {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == player) {
                count++;
            }
        }
    }
    return count;
}

void OthelloGame::play() {
    string FileName;
    cout << "Ingrese el nombre del archivo donde almacena el historial de juego: "; cin>> FileName;
    Data data(FileName);
    cout << "\nBienvenido\n" << endl;
    while (!isGameOver(data)) {
        displayBoard();
        cout << "Jugador " << currentPlayer << ", Ingrese su movimiento (Fila Columna): ";
        int row, col;
        cin >> row >> col;
        row--; // Convert to 0-based index
        col--;
        if (isValidMove(row, col)) {
            system("cls");
            makeMove(row, col);
            switchPlayer();
        } else {
            system("cls");
            cout << "Movimiento no valido. Intente de nuevo." << endl;
        }
    }
}

void OthelloGame::switchPlayer() {
    if (currentPlayer == 'X') {
        currentPlayer = 'O';
        oppositePlayer = 'X';
    } else {
        currentPlayer = 'X';
        oppositePlayer = 'O';
    }
}
