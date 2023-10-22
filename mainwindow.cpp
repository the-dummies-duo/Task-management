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
#include <QTimer>
#include <QDir>

#include "actions.h"
#include "listwidget.h"
#include "qabstractbutton.h"

#define sconcat(a,b) a#b

#include <nlohmann/json.hpp>

using json=nlohmann::json;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tasks = &listwidget::getInstance();
    setFixedSize(600,400);
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

void MainWindow::load(){
    const std::string jsonpath = "./data/data.json";
    QDir d("./data");
    if (!d.exists()){
        d.mkdir(".");
    }
    std::ifstream f(jsonpath);
    json j;
    std::string line;
    std::getline(f, line);
    f.clear();
    f.seekg(0);
    if (line.empty()){
        std::ofstream x(jsonpath);
        x << "{}" << std::endl;
        x.close();
    }
    try{
        f >> j;
    }
    catch(nlohmann::json_abi_v3_11_2::detail::parse_error){}
    f.close();
    if (j.empty()){
        j["tasks"] = json::array();
    }
    timer = new QTimer();
    timer->setInterval(5000);
    QObject::connect(timer, &QTimer::timeout,this,[](){
        //std::cout << "timer invoked" << std::endl;
        const std::string jsonpath = "./data/data.json";
        bool changed = false;
        std::ifstream f(jsonpath);
        json j;
        f >> j;
        f.close();
        json temp = json(j);
        int index = -1;
        for (json& item : temp["tasks"]){
            index++;
            if (item["invoked"]){
                continue;
            }
            time_t rem_t = item["reminder_date"];
            if (rem_t == 0){
                continue;
            }
            auto now = std::chrono::system_clock::now();
            time_t now_ts = std::chrono::system_clock::to_time_t(now);
            //std::cout << now_ts << " " << rem_t << std::endl;
            if (now_ts >= rem_t){
                QMessageBox box;
                box.setWindowTitle(QString::fromStdString((std::string)item["title"]));
                box.setText(QString::fromStdString((std::string)item["description"]));
                box.addButton(QMessageBox::Ok);
                box.addButton(QMessageBox::Ignore);
                box.addButton("Delete task",QMessageBox::ButtonRole::ActionRole);
                box.exec();
                QAbstractButton* clickedButton = box.clickedButton();
                if (clickedButton->text() == "OK"){
                    item["invoked"] = true;
                    changed = true;
                }
                else if (clickedButton->text() == "Delete task"){
                    j["tasks"].erase(std::remove_if(j["tasks"].begin(), j["tasks"].end(), [&item](const json& item_) {
                                         return item_ == item;
                                    }), j["tasks"].end());
                    changed = true;
                }
                else if (clickedButton->text() == "Ignore"){
                    int index = std::find(j["tasks"].begin(),j["tasks"].end(),item) - j["tasks"].begin();
                    j["tasks"][index]["reminder_date"] = now_ts+300;
                    changed = true;
                    std::cout << j["tasks"][index] << std::endl;
                    std::cout << j["tasks"][index]["reminder_date"] << std::endl;

                }
            }

        }
        if(changed){
            std::ofstream x(jsonpath,std::ios::out|std::ios::trunc);
            //std::cout << j << std::endl;
            x << j << std::endl;
            //std::cout << j;
            listwidget* tasks = &listwidget::getInstance();
            tasks->loadwidgets(j);
        }
    });
    timer->start();
    this->tasks->loadwidgets(j);
}
