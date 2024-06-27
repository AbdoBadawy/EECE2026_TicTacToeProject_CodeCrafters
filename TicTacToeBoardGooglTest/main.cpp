#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QApplication>
#include "tictactoeboard.h"
#include <string.h>

class TicTacToeBoardTest : public ::testing::Test {
protected:
    void SetUp() override {
        board = new TicTacToeBoard(nullptr);
    }

    void TearDown() override {
        delete board;
    }

    TicTacToeBoard* board;
};

/*TEST_F(TicTacToeBoardTest, InitialState) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            EXPECT_EQ(board->board[row][col], 0);
            EXPECT_EQ(board->buttons[row][col]->text(), "");
        }
    }
}
*/

TEST_F(TicTacToeBoardTest, HandleButtonClick) {
    QPushButton* button = board->buttons[0][0];
    board->handleButtonClick(button, 0, 0);
    EXPECT_EQ(button->text(), "X");
    EXPECT_EQ(board->board[0][0], 1);
}

TEST_F(TicTacToeBoardTest, CheckWin) {
    board->board[0][0] = 1;
    board->board[0][1] = 1;
    board->board[0][2] = 1;
    EXPECT_TRUE(board->checkWin(1));

    board->board[0][0] = 2;
    board->board[1][0] = 2;
    board->board[2][0] = 2;
    EXPECT_TRUE(board->checkWin(2));
}

TEST_F(TicTacToeBoardTest, CheckDraw) {
    int drawBoard[3][3] = {
        {1, 2, 1},
        {1, 2, 2},
        {2, 1, 1}
    };
    memcpy(board->board, drawBoard, 3 * 3 * sizeof(int));
    EXPECT_TRUE(board->checkDraw());
}

TEST_F(TicTacToeBoardTest, ResetBoard) {
    board->board[0][0] = 1;
    board->board[0][1] = 2;
    board->resetBoard();
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            EXPECT_EQ(board->board[row][col], 0);
            EXPECT_EQ(board->buttons[row][col]->text(), "");
        }
    }
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
