#include "inc/settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    //setWindowFlags(Qt::FramelessWindowHint);


    QIcon tmp_ico(QIcon(":/images/settings_icon.svg"));
    setWindowIcon(tmp_ico);


}

Settings::~Settings()
{
    delete ui;
}

void Settings::get_settings(int f_interval,
                            int s_interval,
                            bool notif_en,
                            bool sound_en,
                            bool stay_on_top,
                            bool show_next_event,
                            int opacity)
{
    // load interval settings
    //************************************************************************************************//
    QString tmp_str = QString::number(f_interval);
    ui->lineEdit->setText(tmp_str);

    tmp_str = QString::number(s_interval);
    ui->lineEdit_2->setText(tmp_str);
    //************************************************************************************************//


    //Set checkbox state after loading
    //************************************************************************************************//

    ui->sound->setChecked(sound_en);
    ui->notifications->setChecked(notif_en);
    ui->showNextEvent->setChecked(show_next_event);
    ui->stayOnTop->setChecked(stay_on_top);

    ui->horizontalSlider->setValue(opacity);
}

std::vector<int> Settings::return_setting()
{
    std::vector<int> tmp[10];

     //Addint to vector setting and returning to mainwindow
     tmp->push_back(ui->lineEdit->text().toInt());
     tmp->push_back(ui->lineEdit_2->text().toInt());
     tmp->push_back(ui->sound->isChecked());
     tmp->push_back(ui->notifications->isChecked());
     tmp->push_back(ui->showNextEvent->isChecked());
     tmp->push_back(ui->stayOnTop->isChecked());
     tmp->push_back(ui->horizontalSlider->value());

     return *tmp;

}

void Settings::Settings::closeEvent(QCloseEvent *event)
{
        //send signal to MainWindows to save settings
}


