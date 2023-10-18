#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <string>
#include <cstring>
#include <locale>
#include <codecvt>
#include <QMainWindow>

#ifdef _WIN32
#define pathify(str) (str.replace(str.find('/'), 1, "\\"))
#define CreateDirectoryFunc(path) CreateDirectory(path,NULL)
#define GetExePath WinExePath
#include <windows.h>
#else
#define pathify(str) str
#define GetExePath getExecutablePath
#include <sys/stat.h>
#define CreateDirectoryFunc(path) mkdir(path,NULL)
#endif
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
MainWindow* MainWindow::GetMainWindow()
{
    foreach (QWidget *w, qApp->topLevelWidgets())
        if (MainWindow* mainWin = qobject_cast<MainWindow*>(w))
            return mainWin;
    return nullptr;
}
std::string wstringToString(const std::wstring& wstr) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>{}.to_bytes(wstr);
}

#ifdef _WIN32
std::string WinExePath() {
    wchar_t buffer[MAX_PATH] = { 0 };
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return wstringToString(std::wstring(buffer).substr(0, pos));
}

#else
std::string getExecutablePath() {
    char exePath[4096];  // Allocate a buffer to store the path
    ssize_t len = readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);

    if (len != -1) {
        exePath[len] = '\0';  // Null-terminate the path
        return std::string(exePath);
    } else {
        return ""; // Return an empty string on error
    }
}
#endif
