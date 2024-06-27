#include "tictactoeboard.h"
//#include "database_interface.h"

TicTacToeBoard::TicTacToeBoard(QWidget *parent)
    : QWidget{parent}
{
        //setFixedSize(300, 300)
        QGridLayout *layout = new QGridLayout(this);

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                QPushButton *button = new QPushButton(this);
                button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                button->setFont(QFont("Arial", 24));
                button->setText("");
                layout->addWidget(button, row, col);
                connect(button, &QPushButton::clicked, this, [=]() {
                    handleButtonClick(button, row, col);
                });
                buttons[row][col] = button;
            }
        }
    }

void TicTacToeBoard::handleButtonClick(QPushButton *button, int row, int col) {
    std::vector<int> board_buffer;
    if(gameLocked) return; //Do nothing if game is locked
    if (board[row][col] == 0) {
        // Board [0 2 0
        //        0 0 1
        //        0 2 0]
        QString playerSymbol = (currentPlayer == 1) ? "X" : "O";
        button->setText(playerSymbol);
        board[row][col] = currentPlayer;

        if (checkWin(currentPlayer)) {
            if (currentPlayer == 1)
            {
                player1Score++;
            }
            else
            {
                player2Score++;
            }
            QMessageBox::information(this, "Game Over", QString("Player %1 wins!").arg(currentPlayer));
           // QMessageBox::information(this, "Total Scores:", QString("Player 1: %1\nPlayer 2: %2").arg(player1Score).arg(player2Score));
            //emit scoreUpdate();
            // Save into database
            for(int i =0 ; i< 3 ;i++)
                for(int j =0 ; j< 3 ;j++)
                    board_buffer.push_back(board[i][j]);
            board_buffer.push_back(ai_mod);
            board_buffer.push_back(player1Score);
            board_buffer.push_back(player2Score);
            //history_insert(username,board_buffer);
            justReset = false; //To indicate this a valid game

            resetBoard(); // Last Thing
        } else if (checkDraw()) {
            QMessageBox::information(this, "Game Over", "It's a draw!");
            //QMessageBox::information(this, "Total Scores:", QString("Player 1: %1\nPlayer 2: %2").arg(player1Score).arg(player2Score));
            //emit scoreUpdate();

            // Save into database
            for(int i =0 ; i< 3 ;i++)
                for(int j =0 ; j< 3 ;j++)
                    board_buffer.push_back(board[i][j]);
            board_buffer.push_back(ai_mod);
            board_buffer.push_back(player1Score);
            board_buffer.push_back(player2Score);
            //history_insert(username,board_buffer);
            justReset = false; //To indicate this a valid game

            resetBoard(); // Last Thing

        } else {
            if(ai_mod)
            {
                if(currentPlayer == 1 )
                    {
                        int AI_mov = findBestMove();
                        int x = AI_mov /3;
                        int y = AI_mov %3;
                        currentPlayer = 2;
                        buttons[x][y]->click();
                    }
                else
                {
                    currentPlayer = 1;
                }

            }
            else
            {
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }

        }
    }
}

bool TicTacToeBoard::checkWin(int player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

bool TicTacToeBoard::checkDraw() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == 0)
                return false;
        }
    }
    return true;
}

void TicTacToeBoard::resetBoard() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            buttons[row][col]->setText("");
            board[row][col] = 0;
        }
    }
    currentPlayer = 1;
}
int TicTacToeBoard::evaluate()
{
// Checking for Rows & columns for X or O victory.
   for (int i = 0; i<3; i++)
{
       if (board[i][0]==board[i][1] &&
       board[i][1]==board[i][2])
   {
           if (board[i][0]==2)
               return +20;
           else if (board[i][0]==1)
               return -20;
   }
       if (board[0][i]==board[1][i] &&
       board[1][i]==board[2][i])
   {
           if (board[0][i]==2)
               return +20;

           else if (board[0][i]==1)
               return -20;
   }
}
// Checking for Diagonals for X or O victory.
   if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
{
       if (board[0][0]==2)
           return +20;
       else if (board[0][0]==1)
           return -20;
}

   if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
{
       if (board[0][2]==2)
           return +20;
       else if (board[0][2]==1)
           return -20;
}

// Else if none of them have won then return 0
return 0;
}
int TicTacToeBoard::minimax(bool isMax,int depth,int alpha,int beta)
{
    int score = evaluate();

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 20)
        return score-depth;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -20)
        return depth+score;

    // If there are no more moves and no winner then
    // it is a tie
    if (checkDraw()==true)
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){

                // Check if cell is empty
                if (board[i][j]==0){

                    // Make the move
                    board[i][j] = 2;
                    int eval = minimax( false, depth + 1, alpha, beta);
                        // Undo the move
                    board[i][j] = 0;
                    best = std::max( best,eval);


                    alpha = std::max(alpha, eval);
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else{
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){

                // Check if cell is empty
                if (board[i][j]==0){

                    // Make the move
                    board[i][j] = 1;
                    int eval = minimax( true, depth + 1, alpha, beta);
                    // Undo the move
                    board[i][j] = 0;
                    // Call minimax recursively and choose
                    // the minimum value
                    best = std::min(best,eval);
                    beta = std::min(beta, eval);
                    if (beta <= alpha) break;


                }
            }
        }
        return best;
    }
}
int TicTacToeBoard::findBestMove(){
    int bestVal = -1000;
    int bestMove;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int row = 0; row<3; row++){
        for (int col = 0; col<3; col++){

            // Check if cell is empty
            if (board[row][col]==0){

                // Make the move
                board[row][col] = 2;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(false,0,-1000,1000);

                // Undo the move
                board[row][col] = 0;

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal){
                    bestMove = 3*row+col;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}




