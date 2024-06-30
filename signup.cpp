#include "signup.h"
#include "ui_signup.h"
#include"database_interface.h"
#include <QMessageBox>
signup::signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);
}

signup::~signup()
{
    delete ui;
}

void signup::on_pushButton_SignUp_clicked()
{
    QString UserName,Password,Phone;
    qint64 Age,Gender;


    UserName= ui->lineEdit_UserName_1->text();
    Password= ui->lineEdit_Password_1->text();
    Phone= ui->lineEdit_Phone->text();
    Age=ui->lineEdit_Age->text().toInt();
    if(ui->radioButton->isChecked())
        Gender = 1; //male
    else if (ui->radioButton_2-> isChecked())
        Gender = 0; //female

    std::string username=UserName.toStdString();
    std::string password=Password.toStdString();
    std::string phone=Phone.toStdString();


    if (signUp(username,password, phone, Gender,Age)){
        QMessageBox ::information(this,tr("Save"),tr("Saved"));

        this->hide();
        this->done(Accepted);

    }
    else
    {
        QMessageBox::critical(this,tr("Error."),"Error in sign" );


    }
}

