#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

class TicTacToeBoard : public QWidget
{
    Q_OBJECT
public:
    explicit TicTacToeBoard(QWidget *parent = nullptr);
    void handleButtonClick(QPushButton *button, int row, int col);
    bool checkWin(int player);
    bool checkDraw();
    void resetBoard();

    int player1Score = 0;
    int player2Score = 0;
    bool ai_mod=false;
    bool gameLocked=false;
    int board[3][3] = {0};
    bool justReset = false;
    QPushButton *buttons[3][3];
//signals:
    //void scoreUpdate();

private:
    int currentPlayer = 1;
    int evaluate();
	int minimax(bool isMax,int depth,int alpha,int beta);
	int findBestMove();


};


#endif // TICTACTOEBOARD_H
