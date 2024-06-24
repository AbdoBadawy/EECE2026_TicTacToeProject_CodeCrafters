#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <iostream>
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
{
    //if Logged in close the window
    this->done(Accepted);
    // if it is wrong login Show Error Message and try agin

    //if closed
      //  this->done(Rejected);

}


void LoginWindow::on_LoginWindow_finished(int result)
{
    if (result == Rejected) // Exiting Only if rejected
        exit(EXIT_SUCCESS); // I don't know why QApplication::quit() doesn't work well
}

