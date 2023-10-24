#include "mainwindow.h"
#include "includes.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <string>

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "actions.h"
#include "listwidget.h"

#define sconcat(a,b) a#b

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
    const QString jsonpath_q = "./data/data.json";
    QDir d("./data");
    if (!d.exists()){
        d.mkdir(".");
    }
    QFile jsonfile(jsonpath_q);
    if (!jsonfile.open(QIODevice::ReadWrite)){
        qWarning("Couldn't open json file at ./data/data.json");
    }
    QByteArray data = jsonfile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    if (obj.empty()){
        obj["tasks"] = QJsonArray();
    }
    timer = new QTimer();
    timer->setInterval(5000);
    QObject::connect(timer, &QTimer::timeout,this,[](){
        const QString jsonpath_q = "./data/data.json";

        bool changed = false;
        QFile jsonfile(jsonpath_q);
        if (!jsonfile.open(QIODevice::ReadWrite)){
            qWarning("Couldn't open json file at ./data/data.json");
        }
        QByteArray data = jsonfile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject j = doc.object();
        QJsonObject temp = QJsonObject(j);
        int index = -1;
        for (const auto& item_ : temp["tasks"].toArray()){
            index++;
            QJsonObject item = item_.toObject();
            if (item["invoked"].toBool()){
                continue;
            }
            time_t rem_t = item["reminder_date"].toInt();
            if (rem_t == 0){
                continue;
            }
            auto now = std::chrono::system_clock::now();
            time_t now_ts = std::chrono::system_clock::to_time_t(now);

            if (now_ts >= rem_t){
                QMessageBox box;
                box.setWindowTitle(item["title"].toString());
                box.setText(item["description"].toString());
                box.addButton(QMessageBox::Ok);
                box.addButton(QMessageBox::Ignore);
                box.addButton("Delete task",QMessageBox::ButtonRole::ActionRole);
                box.exec();
                QAbstractButton* clickedButton = box.clickedButton();
                QJsonArray tasks = j["tasks"].toArray();
                if (clickedButton->text() == "OK"){
                    QJsonObject task = tasks[index].toObject();
                    task["invoked"] = true;
                    changed = true;
                    tasks[index] = task;
                    j["tasks"] = tasks;
                }
                else if (clickedButton->text() == "Delete task"){
                    tasks.erase(std::find_if(tasks.begin(), tasks.end(), [&item](const auto& item__) {
                        QJsonObject item_ = item__.toObject();
                                         return item_ == item;
                    }));
                    changed = true;
                    j["tasks"] = tasks;
                }
                else if (clickedButton->text() == "Ignore"){
                    //int index = std::find(tasks.begin(),tasks.end(),item) - tasks.begin();
                    QJsonObject task = tasks[index].toObject();
                    task["reminder_date"] = now_ts+300;
                    changed = true;


                    tasks[index] = task;
                    j["tasks"] = tasks;

                }
            }

        }
        if(changed){
            QFile x("./data/data.json");
            x.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);

            QJsonDocument temp_doc = QJsonDocument();
            temp_doc.setObject(j);
            QByteArray writedata = temp_doc.toJson();
            x.write(writedata);

            listwidget* tasks = &listwidget::getInstance();
            tasks->loadwidgets(j);
        }
    });
    timer->start();
    this->tasks->loadwidgets(obj);
}
