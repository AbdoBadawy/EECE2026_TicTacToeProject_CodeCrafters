#include "mainwindow.h"
#include <iostream>
#include "./ui_mainwindow.h"
#include "database_interface.h"
extern std::string username;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainTabs->setCurrentIndex(0);
}
void MainWindow::startLoginWindow()
{
    LoginWindow loginWindow;
    loginWindow.setModal(true);
    int status = loginWindow.exec();
    if(status==QDialog::Accepted) // Right Login
    {
        this->show();
        // Reseting Board and labels
        ui->player2Name->setText("");
        ui->modText->setText("");
        ui->XO_Board->player1Score =0;
        ui->XO_Board->player2Score =0;
        emit ui->XO_Board->scoreUpdate();
        ui->XO_Board->resetBoard();
        ui->XO_Board->gameLocked = true;
    }
    else //Closing
    {
        QApplication::quit();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::scoreUpdateLabels()
{
    ui->score1Label->setText(QString::number(ui->XO_Board->player1Score));
    ui->score2Label->setText(QString::number(ui->XO_Board->player2Score));
}
void MainWindow::on_pushButton_clicked()
{
    ui->XO_Board->resetBoard();
}


void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox msg;
    //Selecting Game Mode
    msg.setWindowTitle("Play mode");
    msg.setText("Single Player or Multi Player?");
    QPushButton* single =msg.addButton("Single Player",QMessageBox::YesRole);
    QPushButton* multi  =msg.addButton("Multi Player",QMessageBox::NoRole);
    msg.addButton("Cancel",QMessageBox::RejectRole);
    msg.exec();

    if (msg.clickedButton()==single)
    {
       // QMessageBox::information(this,"What he chose","He chose single");
        // Start AI mode
        ui->XO_Board->ai_mod =true;
        ui->player2Name->setText("AI");
        ui->modText->setText("AI mode");
        ui->XO_Board->gameLocked = false;

        //Reseting Game

        ui->XO_Board->player1Score =0;
        ui->XO_Board->player2Score =0;
        emit ui->XO_Board->scoreUpdate();
        ui->XO_Board->resetBoard();

        // Send all  3 to database
        if(ui->XO_Board->justReset) {
            return; // Don't save in database
        }
        std::vector<int> board_buffer= {3,3,3,3,3,3,3,3,3,3,3,3};
        history_insert(username,board_buffer);
        ui->XO_Board->justReset = true; //To indicate this a reset

    }
    else if(msg.clickedButton()== multi)
    {
       // QMessageBox::information(this,"What he chose","He chose Multi");
        ui->XO_Board->ai_mod = false;
        //Start 2-player mode
        ui->player2Name->setText("Player 2");
        ui->modText->setText("2 Players mode");
        ui->XO_Board->gameLocked = false;

        //Reseting Game

        ui->XO_Board->player1Score =0;
        ui->XO_Board->player2Score =0;
        emit ui->XO_Board->scoreUpdate();
        ui->XO_Board->resetBoard();

        // Send all  3 to database
        if(ui->XO_Board->justReset) {
            return; // Don't save in database
        }
        std::vector<int> board_buffer= {3,3,3,3,3,3,3,3,3,3,3,3};
        history_insert(username,board_buffer);
        ui->XO_Board->justReset = true; //To indicate this a reset
    }
}

void MainWindow::signOut()
{
    MainWindow::hide();
    startLoginWindow();
}

void MainWindow::on_actionAbout_QT_triggered()
{
    QApplication::aboutQt();
}


void MainWindow::on_actionAbout_us_triggered()
{
    QMessageBox::information(this,"About us","Github repo Here");
}

void MainWindow::on_mainTabs_currentChanged(int index)
{
    if(index != 2)
        return;
    ui->widget->initState();
    ui->widget->getNumberGamesFromDataBase(username); //for now
    ui->widget->updateHistoryList();
}
