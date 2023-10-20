#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <string>
#include <cstring>
#include <locale>
#include <codecvt>
#include <fstream>

#include <QMainWindow>
#include <QMessageBox>

#include "actions.h"
#include "listwidget.h"

#define sconcat(a,b) a#b

#include <nlohmann/json.hpp>

using json=nlohmann::json;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tasks = &listwidget::getInstance();
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
void MainWindow::load(){
    std::string path = GetExePath();
    std::string datapath = "./data";
    if (!(std::filesystem::exists(datapath) && std::filesystem::is_directory(datapath))){
        if (std::filesystem::exists(datapath)){
            if (!std::filesystem::remove(datapath)){
                QMessageBox::warning(this,"Error",sconcat("Unable to remove file/directory ",datapath));
            }
        }
        CreateDirectoryFunc(L"./data");
    }
    std::ifstream f("./data/data.json");
    json j;
    std::string line;
    std::getline(f, line);
    f.clear();
    f.seekg(0);
    if (line.empty()){
        std::ofstream x("./data/data.json");
        x << "{}" << std::endl;
        x.close();
    }
    try{
        f >> j;
    }
    catch(nlohmann::json_abi_v3_11_2::detail::parse_error){}

    if (j.empty()){
        j["tasks"] = json::array();
    }
    this->tasks->loadwidgets(j["tasks"]);
}
