#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>

#include <stdexcept>

#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setup the UI
    ui->setupUi(this);
    read_state();

    // Connect the buttons
    connect(
        ui->chkBattery,
        SIGNAL(toggled(bool)),
        this,
        SLOT(toggle_ip_battery_saver(bool)));
    connect(
        ui->chkTurboBoost,
        SIGNAL(toggled(bool)),
        this,
        SLOT(toggle_it_turbo_boost(bool)));
}

void MainWindow::toggle_ip_battery_saver(bool new_state)
{
    set_checkbox_state(ui->chkBattery, new_state);
}

void MainWindow::toggle_it_turbo_boost(bool new_state)
{
    set_checkbox_state(ui->chkTurboBoost, new_state);
}

void MainWindow::read_state() const
{
    read_checkbox_state(ui->chkBattery);
    read_checkbox_state(ui->chkTurboBoost);
}

bool MainWindow::read_checkbox_state(QCheckBox* chk) const
{
    // Define the file
    QFile file(file_for_checkbox(chk));

    // Determine enabled based on whether the file exists
    if (file.exists())
    {
        chk->setEnabled(true);
    }
    else
    {
        chk->setEnabled(false);
        chk->setCheckState(Qt::CheckState::Unchecked);
        return false;
    }

    // Attempt to open the file for reading
    if (!file.open(QFile::OpenModeFlag::ReadOnly))
    {
        throw std::runtime_error("unable to open file");
    }

    // Read the resulting file
    QString text = file.readAll().trimmed();

    // Determine checked state
    if (text == "0")
    {
        chk->setCheckState(Qt::CheckState::Unchecked);
    }
    else if (text == "1")
    {
        chk->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        throw std::runtime_error("unknown check state provided");
    }

    // Close the file
    file.close();

    // Return the state value
    return chk->isChecked();
}

void MainWindow::set_checkbox_state(QCheckBox* chk, bool value)
{
    // Define the file
    QFile file(file_for_checkbox(chk));

    // Return if no file exists
    if (!file.exists())
    {
        throw std::runtime_error("cannot write to non-existant system file");
    }

    // Attempt to write the file
    if (file.open(QFile::OpenModeFlag::WriteOnly))
    {
        // Attempt to write a 0 for false or 1 for true
        if (value)
        {
            file.write(QByteArray("1"));
        }
        else
        {
            file.write(QByteArray("0"));
        }

        // Close the file
        file.close();
    }

    // Read the state value
    read_checkbox_state(chk);
}

QString MainWindow::file_for_checkbox(QCheckBox* chk) const
{
    if (chk == ui->chkBattery)
    {
        return "/sys/bus/platform/drivers/ideapad_acpi/VPC2004:00/conservation_mode";
    }
    else if (chk == ui->chkTurboBoost)
    {
        return "/sys/devices/system/cpu/intel_pstate/no_turbo";
    }
    else
    {
        throw std::runtime_error("no file denoted for checkbox");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

