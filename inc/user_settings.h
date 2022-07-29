#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

#include <QWidget>

namespace Ui {
class User_Settings;
}

class User_Settings : public QWidget
{
    Q_OBJECT




public:
    explicit User_Settings(QWidget *parent = nullptr);
    ~User_Settings();
    int return_first_interval(void);
    int return_second_interval(void);
    void show_window(void);

private:
    Ui::User_Settings *ui;
};

#endif // USER_SETTINGS_H
