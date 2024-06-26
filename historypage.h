#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H

#include <QWidget>
#include <QListWidget>
#include <QPainter>

namespace Ui {
class HistoryPage;
class ViewBoard;
}

class ViewBoard : public QWidget
{
    Q_OBJECT

public:
    explicit ViewBoard(QWidget *parent = nullptr);

    void setBoard(const int board[3][3]); // Method to set the board state

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int board[3][3]; // 3x3 array to hold board state
};


class HistoryPage : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryPage(QWidget *parent = nullptr);
    void initState(); // Zero every thing
    void getNumberGamesFromDataBase(const std::string& username); // Get All games from
    void updateHistoryList(); //update history list

    // This funtion only pulls data from the data base
    // This function is called only when history tab is opened

    ~HistoryPage();

private slots:


    void on_historyList_itemDoubleClicked(QListWidgetItem *item);

    void on_nextBoardButton_clicked();

    void on_perviousBoardButton_clicked();

private:
    Ui::HistoryPage *ui;
    int historyTotalGames=0;
    std::vector<int> dataBaseGameVector; //Big vector contain all games ?!
    //std::vector<char> *dataBaseGameVectors; // Get only one game at a time
    struct Game{
        int num=0; // game number in history
        int player1Score=0;
        int player2Score=0;
        bool mode=0; // 1 -> AI , 0-> Multiplayer
        int numberBoards=0;
        struct GameBoard
        {
            int boardNumber=0; // board number in a game
           // int boardState=0;
            int boardPlayer1Score=0;
            int boardPlayer2Score=0;
            int board[3][3];
            std::vector<int>::iterator boardPointer;
        }gameBoard;
}game;

    void getGameFromVectorBuffer(int historyItem); // Parse the game and update gameBoard
    /*
     * Game in database:
            Vector of int:
            [0:8]-> board
            9-> mode ()
            10 -> player1score (so far)
            11-> player2score (so far)
     */
    void updateGameView();
    void updateBoardView();

};


#endif // HISTORYPAGE_H
