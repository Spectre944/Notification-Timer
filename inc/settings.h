#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QVector>
#include <QCloseEvent>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    void get_settings(int, int, bool, bool, bool, bool, int);

    std::vector<int> return_setting();

    void Settings::closeEvent (QCloseEvent *event) override;

private slots:


private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
