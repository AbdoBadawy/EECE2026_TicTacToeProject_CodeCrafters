#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

namespace Ui {
class profile;
}

class profile : public QWidget
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    void updateProfile();
    ~profile();


private:
    Ui::profile *ui;
};

#endif // PROFILE_H
