#include "profile1.h"
#include "ui_profile.h"
#include "database_interface.h"
extern std::string username;
profile::profile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::profile)
{
    ui->setupUi(this);
}

profile::~profile()
{
    delete ui;
}

void profile::on_pushButton_clicked()
{
    QString Age_local=QString::fromStdString(get_age(username));
    QString Username_local=QString::fromStdString(username);
    QString Phone_local=QString::fromStdString(get_phone(username));
    QString wins_local=QString::number(get_wins(username));
    QString loses_local=QString::number(get_loses(username));
    QString draws_local=QString::number(get_draws(username));
    QString gender_local;
    if(get_gender(username)){
        gender_local="Male";
    }
    else{ gender_local="Female";}
    QString Rank_local;
    if((get_loses(username))>=(get_draws(username))){
        Rank_local="begginer";}
    if((get_loses(username))<(get_draws(username))){
        Rank_local="good";}
    if((get_loses(username))<(get_draws(username))*2){
        Rank_local="Legend";}



    ui->label_wins->setText(wins_local);
    ui->label_draws->setText(draws_local);
    ui->label_loses->setText(loses_local);
    ui->label_Phone->setText(Phone_local);
    ui->label_Gender->setText(gender_local);
    ui->label_Username->setText(Username_local);
    ui->label_Age->setText(Age_local);
    ui->label_Rank->setText(Rank_local);

}
