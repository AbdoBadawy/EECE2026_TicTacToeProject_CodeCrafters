#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "database_interface.h"
#include <iostream>
#include"signup.h"
extern std::string username;

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{   QString UserName,Password;
    UserName= ui->lineEdit_UserName->text();
    Password= ui->lineEdit_Password->text();
    std::string username=UserName.toStdString();
    std::string password=Password.toStdString();




    if (login(username,password)){
            ui->label_check->setText("username and password are correct");

            this->hide();
            this->done(Accepted);
            ::username=username;
        }
        else
            ui->label_check->setText("username and password are not correct");


    }



void LoginWindow::on_LoginWindow_finished(int result)
{
    if (result == Rejected) // Exiting Only if rejected
        exit(EXIT_SUCCESS); // I don't know why QApplication::quit() doesn't work well
}


void LoginWindow::on_pushButton_2_clicked()
{
    signup Dialog_Register ;
    Dialog_Register.setModal(true);
    Dialog_Register.exec();
}

