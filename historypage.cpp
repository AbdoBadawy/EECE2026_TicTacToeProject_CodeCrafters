#include "historypage.h"
#include "ui_historypage.h"
#include "database_interface.h"
extern std::string username;
HistoryPage::HistoryPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryPage)
{
    ui->setupUi(this);
}

HistoryPage::~HistoryPage()
{
    delete ui;
}

void HistoryPage::initState()
{
    historyTotalGames =0;
    game.num=0;
    dataBaseGameVector.clear();
    game.player1Score=0;
    game.player2Score=0;
    game.mode=false;
    game.numberBoards=0;
    game.gameBoard.boardNumber=0;
    //game.gameBoard.boardState=0;
    game.gameBoard.boardPlayer1Score=0;
    game.gameBoard.boardPlayer2Score=0;
    for(int i = 0 ; i<3;i++)
        for(int j=0; j<3;j++)
             game.gameBoard.board[i][j]=0;
    updateBoardView();
    updateGameView();
    updateHistoryList();
}

void HistoryPage::getNumberGamesFromDataBase(const std::string& username)
{
    //historyTotalGames= get_wins(username)+get_loses(username)+get_draws(username);
    vector<int> Buffer(get_history_int(username));
    //std::cout<<"Buffer size= "<<Buffer.size()<<std::endl;
    dataBaseGameVector.assign(Buffer.begin(),Buffer.end());
    //for(auto j = Buffer.begin();j<Buffer.end();j++)
    //    std::cout<<*j<<std::endl;
    auto i = dataBaseGameVector.begin();
    for(;i < dataBaseGameVector.end();i+=12)
    {
        if(*i==3) historyTotalGames++;
    }
   // std::cout<<"Total number of games= "<<historyTotalGames<<std::endl;
}
// Get All games from
// This funtion only pulls data from the data base
// This function is called only when history tab is opened

void HistoryPage::updateHistoryList()
{
    char item_name[20];
    ui->historyList->clear();
    for(int i = historyTotalGames; i > 0;i--)
    {
        sprintf(item_name,"Game %d",i);
      //  std::cout<< item_name<<std::endl;
        ui->historyList->addItem(QString(item_name));
        *item_name=0;
    }
}//update history list
void HistoryPage::getGameFromVectorBuffer(int historyItem)
{
    auto itr = dataBaseGameVector.begin();
    int game_index = historyItem + 1; //ensure that this starts from 1 !!
    int board_number = 0;
    // History Item starts from 0
    for(;game_index > 0;itr+=12)
    {
        if(*itr == 3) // this is a sign for end of game
        {
            game_index --;
            if (game_index ==0)
                break;
            board_number=-1; // must be -1
        }
        board_number++;
    }
    if(board_number==0)
    {/*
        initState();
        getNumberGamesFromDataBase(username); //for now
        updateHistoryList();
        */
        game.num=0;
        dataBaseGameVector.clear();
        game.player1Score=0;
        game.player2Score=0;
        game.mode=false;
        game.numberBoards=0;
        game.gameBoard.boardNumber=0;
        //game.gameBoard.boardState=0;
        game.gameBoard.boardPlayer1Score=0;
        game.gameBoard.boardPlayer2Score=0;
        for(int i = 0 ; i<3;i++)
            for(int j=0; j<3;j++)
                 game.gameBoard.board[i][j]=0;
        updateBoardView();
        updateGameView();
        return;
    }
    game.num = historyTotalGames - historyItem; // ensure proper number
    itr--; // now it points to 11
    game.mode = *(itr-2);
    game.numberBoards = board_number;
    game.gameBoard.boardPlayer1Score = *(itr-1);
    game.gameBoard.boardPlayer2Score = *itr;
    game.gameBoard.boardPointer = (itr-11);
    for(int i =0 ; i<3 ;i++)
    {
        for(int j =0 ;j<3;j++)
        {
         game.gameBoard.board[i][j] = *(itr-11+i*3+j);
       //  std::cout<< game.gameBoard.board[i][j] << std::endl;
        }
    }
    game.player1Score = *(itr-(board_number-1)*12-1);
    game.player2Score = *(itr-(board_number-1)*12);
    game.gameBoard.boardNumber = 1;
   // std::cout << "game mode "<< game.mode <<endl;
    //std::cout << "game.numberBoards = "<< game.numberBoards <<std::endl;
    //std::cout << "game.player1Score = " << game.player1Score  <<std::endl ;
    //std::cout << "game.player2Score " << game.player2Score <<std::endl;
}// Parse the game and update gameBoard
/*
 * Game in database:
        Vector of int:
        [0:8]-> board
        9-> mode ()
        10 -> player1score (so far)
        11-> player2score (so far)
 */
void HistoryPage::updateGameView()
{
    ui->gameNumberLabel->setText(QString::fromStdString(to_string(game.num)));
    if(game.mode)
        ui->gameModeLabel->setText("AI mode");
    else
        ui->gameModeLabel->setText("Multi player mode");
    ui->gamePlayer1ScoreLabel->setText(QString::number(game.player1Score));
    ui->gamePlayer2ScoreLabel->setText(QString::number(game.player2Score));
    ui->gameNumberBoardsLabel->setText(QString::number(game.numberBoards));

}
void HistoryPage::updateBoardView(){
  ui->currentBoard->setBoard(game.gameBoard.board);
  ui->boardNumberLabel->setText(QString::number(game.gameBoard.boardNumber));
  ui->boardPlayer1ScoreLabel->setText(QString::number(game.gameBoard.boardPlayer1Score));
  ui->boardPlayer2ScoreLabel->setText(QString::number(game.gameBoard.boardPlayer2Score));
}




//// HERE ViewBoard
ViewBoard::ViewBoard(QWidget *parent) : QWidget(parent)
{
    // Initialize board with empty values or any initial setup
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = 0; // 0 represents empty, 1 represents X, 2 represents O, etc.
        }
    }
}

void ViewBoard::setBoard(const int board[3][3])
{
    // Set the board state with the provided array
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            this->board[i][j] = board[i][j];
        }
    }
    update(); // Trigger repaint
}

void ViewBoard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Optional, for better rendering

    int num;
    // Calculate cell size based on widget size
    int cellWidth = width() / 3;
    int cellHeight = height() / 3;

    // Draw the Tic Tac Toe board based on the board array
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            // Calculate the rectangle for each cell
            QRect cellRect(j * cellWidth, i * cellHeight, cellWidth, cellHeight);

            // Draw based on the board state
            if (board[i][j] == 1) {
                // Draw X
                painter.drawLine(cellRect.topLeft(), cellRect.bottomRight());
                painter.drawLine(cellRect.bottomLeft(), cellRect.topRight());
            } else if (board[i][j] == 2) {
                // Draw O
                //painter.drawText(cellRect,"O");
                painter.drawEllipse(cellRect);
            }
        }
    }

    // Draw grid lines (optional)
    painter.setPen(Qt::black);
    for (int i = 0; i <= 3; ++i) {
        painter.drawLine(i * cellWidth, 0, i * cellWidth, height());
        painter.drawLine(0, i * cellHeight, width(), i * cellHeight);
    }
}


void HistoryPage::on_historyList_itemDoubleClicked(QListWidgetItem *item)
{
   // std::cout<< ui->historyList->row(item) <<std::endl;
    getGameFromVectorBuffer(ui->historyList->row(item));
    updateBoardView();
    updateGameView();
}


void HistoryPage::on_nextBoardButton_clicked()
{
    if (game.gameBoard.boardNumber >= game.numberBoards) return;
    game.gameBoard.boardPointer-=12;
    game.gameBoard.boardNumber++;

    game.gameBoard.boardPlayer1Score = *(game.gameBoard.boardPointer+10);
    game.gameBoard.boardPlayer2Score = *(game.gameBoard.boardPointer+11);
    for(int i =0 ; i<3 ;i++)
    {
        for(int j =0 ;j<3;j++)
        {
         game.gameBoard.board[i][j] = *(game.gameBoard.boardPointer+i*3+j);
         //std::cout<< game.gameBoard.board[i][j] << std::endl;
        }
    }
    updateBoardView();
}


void HistoryPage::on_perviousBoardButton_clicked()
{
    if (game.gameBoard.boardNumber <= 1) return;
    game.gameBoard.boardPointer+=12;
    game.gameBoard.boardNumber--;

    game.gameBoard.boardPlayer1Score = *(game.gameBoard.boardPointer+10);
    game.gameBoard.boardPlayer2Score = *(game.gameBoard.boardPointer+11);
    for(int i =0 ; i<3 ;i++)
    {
        for(int j =0 ;j<3;j++)
        {
         game.gameBoard.board[i][j] = *(game.gameBoard.boardPointer+i*3+j);
         //std::cout<< game.gameBoard.board[i][j] << std::endl;
        }
    }
    updateBoardView();
}


