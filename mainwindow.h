#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void toggle_ip_battery_saver(bool new_state);

    void toggle_it_turbo_boost(bool new_state);

protected:
    void read_state() const;

    bool read_checkbox_state(QCheckBox* chk) const;
    void set_checkbox_state(QCheckBox* chk, bool value);

    QString file_for_checkbox(QCheckBox* chk) const;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
