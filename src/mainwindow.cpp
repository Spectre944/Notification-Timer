#include "inc/mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Get path of exe app and create settings ini in this folder
    QString tmp_dir = QDir::currentPath() + "/settings.ini";

    settings = new QSettings(tmp_dir, QSettings::IniFormat, this);
    loadSettings();

    //Create notification window
    //************************************************************************************************//
    popUp = new PopUp();
    //************************************************************************************************//


    //start timer and connet it to function that refrsh time and display notifications
    //************************************************************************************************//
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::mainProcess);
    timer->start(1000);
    //************************************************************************************************//


}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::mainProcess()
{
    showTime();
    showNotif();
}

void MainWindow::showNotif()
{
    QTime ct = QTime::currentTime();

    int min = ct.msecsSinceStartOfDay()/(1000*60);   

    if((first_interval == 0) || (second_interval == 0))
        return;

    if(showNextNotification)
    {
        QTime tmp = ct;

        tmp = tmp.addSecs((first_interval - (min%first_interval))*60);

        ui->labelNextNotifTime->setText(tmp.toString("hh:mm" ));
    }
    else
    { ui->labelNextNotifTime->setText("");}


    if(ct.second() == 0)
    {
        if(min%first_interval == 0)
        {

            if(soundEnable) { sound_ex->play(); }

            if(notificationEnable) { popUp->setPopupTextAndImage("Exercise", tmp_im_Ex); popUp->show(); }
        }
    }
    if(ct.second() == 30)
    {
        if(min%second_interval == 0)
        {

           if(soundEnable) { sound_20->play(); }

           if(notificationEnable) { popUp->setPopupTextAndImage("20/20/20", tmp_im_20); popUp->show(); }
        }
    }
    else
    { }

}

void MainWindow::showTime()
{

    QTime ct = QTime::currentTime();

    ui->lcdNumber_Hours->display(ct.hour());
    ui->lcdNumber_Minutes->display(ct.minute());
    ui->lcdNumber_Seconds->display(ct.second());
}

void MainWindow::resizeEvent(QResizeEvent* event)
{

}

void MainWindow::on_start_Stop_Timer_clicked()
{
    if(ui->start_Stop_Timer->isChecked())
    {
        timer->start(1000);
        ui->lcdFrame->show();
    }
    else
    {
        ui->lcdFrame->hide();
        timer->stop();
        ui->labelNextNotifTime->setText("");
    }
}

void MainWindow::on_open_Settings_clicked()
{

    if(ui->open_Settings->isChecked())
    {
        SettWindow->get_settings(first_interval, second_interval, notificationEnable, soundEnable, onTopCheck, showNextNotification, main_opacity*100);

        SettWindow->show();
    }
    else
    {

       std::vector<int> sett = SettWindow->return_setting();

       first_interval = sett.at(0);
       second_interval = sett.at(1);
       soundEnable = sett.at(2);
       notificationEnable = sett.at(3);
       showNextNotification = sett.at(4);
       onTopCheck = sett.at(5);
       main_opacity = (sett.at(6)/100.0f);


       if(onTopCheck)
        {setWindowFlag(Qt::WindowStaysOnTopHint, true);}
       else
        {setWindowFlag(Qt::WindowStaysOnTopHint, false);}

       this->setWindowOpacity(main_opacity);

       this->hide();
       this->show();

       SettWindow->hide();

    }

}


void MainWindow::saveSettings()
{
    settings->setValue("geometry", geometry());

    settings->setValue("First_Interval", first_interval);
    settings->setValue("Second_Interval", second_interval);

    settings->setValue("Sound_Enable", soundEnable);
    settings->setValue("Notifications_Enable", notificationEnable);
    settings->setValue("ShowNextNotif", showNextNotification);
    settings->setValue("StayOnTop", onTopCheck);

    settings->setValue("Window_Opacity", main_opacity);


}

void MainWindow::loadSettings()
{

    //move to right bottom corner
    //************************************************************************************************//
    QScreen* screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    this->move(size.width()-this->width(),size.height()-this->height());
    //************************************************************************************************//


    //default size if no settings loaded
    setGeometry(settings->value("geometry", QRect(size.width()-this->width(), size.height()-this->height(), 320, 160)).toRect());

    first_interval = settings->value("First_Interval", 60).toInt();
    second_interval = settings->value("Second_Interval", 20).toInt();

    soundEnable = settings->value("Sound_Enable", true).toBool();
    notificationEnable = settings->value("Notifications_Enable", true).toBool();
    showNextNotification = settings->value("ShowNextNotif", true).toBool();
    onTopCheck = settings->value("StayOnTop", true).toBool();

    main_opacity = settings->value("Window_Opacity", 1.0f).toFloat();

    Qt::WindowFlags flags;

    if(onTopCheck)
        {flags |= Qt::WindowStaysOnTopHint;}
    else
        {setWindowFlag(Qt::WindowStaysOnTopHint, false);}

    flags |= Qt::FramelessWindowHint;

    setWindowFlags(flags);

    setAttribute(Qt::WA_TranslucentBackground);

    this->hide();
    this->show();

    this->setWindowOpacity(main_opacity);

}

QRect MainWindow::return_rect_size()
{

  QRect tmp = ui->centralwidget->rect();

  return tmp;

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{


  if (event->button() == Qt::LeftButton) {
    /*Capture coordinates when pressed*/
   *m_startPoint = frameGeometry().topLeft() - event->globalPos();


  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
  /*Move window*/
   this->move(event->globalPos() + *m_startPoint);

}




