#include "user_settings.h"
#include "ui_user_settings.h"

User_Settings::User_Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User_Settings)
{
    ui->setupUi(this);
}

User_Settings::~User_Settings()
{
    delete ui;
}

int User_Settings::return_first_interval()
{
    return first_interval;
}

int User_Settings::return_second_interval()
{
    return second_interval;
}

void User_Settings::show_window()
{

}
