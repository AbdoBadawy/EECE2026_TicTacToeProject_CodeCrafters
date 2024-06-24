#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startLoginWindow();
private slots:
    void on_pushButton_clicked();
    void scoreUpdateLabels();

    void on_pushButton_2_clicked();

    //void on_historyTab_currentChanged(int index);

    //void on_mainTabs_currentChanged(int index);

    void signOut();

    void on_actionAbout_QT_triggered();

    void on_actionAbout_us_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
