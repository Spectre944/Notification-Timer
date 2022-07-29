#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "popup.h"
#include "settings.h"

#include <QMainWindow>
#include <QTimer>
#include <QScreen>
#include <QDate>
#include <QSystemTrayIcon>
#include <QLabel>
#include <QSound>
#include <QSettings>
#include <QDir>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


    bool settingsCheck = false;
    bool start_stop = true;

    float main_opacity = 1.0f;

    char change_pos = 0;

    int first_interval = 50;
    int second_interval = 20;

    bool onTopCheck = false;
    bool showNextNotification = true;
    bool soundEnable = true;
    bool notificationEnable = true;

    Settings *SettWindow = new Settings;

    QTime *ct = new QTime;

    //For tracking mouse coordinates
    QPoint *m_startPoint = new QPoint;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mainProcess(void);
    void showTime(void);
    void showNotif(void);

private slots:
    void resizeEvent(QResizeEvent*);

    void saveSettings();

    void loadSettings();



    //void showMessage(QIcon ico);

    QRect return_rect_size ();

    void on_start_Stop_Timer_clicked();

    void on_open_Settings_clicked();

    void mousePressEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    //QSystemTrayIcon *trayIcon;
    PopUp *popUp;

    QSound *sound_20 = new QSound("://sound/Windows Notify System Generic.wav", this);
    QSound *sound_ex = new QSound("://sound/Alarm07.wav", this);

    QImage tmp_im_20 = QImage("://images/focus.png");
    QImage tmp_im_Ex = QImage("://images/exercise.png");

    //Load and save settings after exit
    QSettings *settings;



};



#endif // MAINWINDOW_H
