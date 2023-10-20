#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "debug.h"
#include "listwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow *GetMainWindow();
    void openNewTask();
    void load();
private:
    listwidget* tasks;
    Ui::MainWindow *ui;
};
#ifdef _WIN32
std::string WinExePath();
#else
std::string getExecutablePath();
#endif
#endif // MAINWINDOW_H
