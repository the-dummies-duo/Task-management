#include "newtask.h"
#include "ui_newtask.h"
#include "mainwindow.h"
#include "actions.h"
#include "listwidget.h"

#include <fstream>

#include <QPlainTextEdit>
#include <QMessageBox>
#include <QObject>
#include <QCheckBox>
#include <QDateTimeEdit>
#include <QObject>

#include <nlohmann/json.hpp>

#define concat(a,b) a#b
using json = nlohmann::json;

newTask::newTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newTask)
{
    ui->setupUi(this);
    QCheckBox* cb = findChild<QCheckBox*>("remindercb");
    cb->setCheckState(Qt::CheckState::Checked);
    QDateTimeEdit* dt = findChild<QDateTimeEdit*>("reminderdatetime");
    QObject::connect(cb,&QCheckBox::stateChanged,this,[cb,dt](int state){
            if (state == Qt::Checked){
                dt->setEnabled(true);
            }
            else if (state == Qt::Unchecked){
                dt->setEnabled(false);
            }
    });
}

newTask::~newTask()
{
    delete ui;
}
void newTask::accept(){
    QPlainTextEdit* title = findChild<QPlainTextEdit*>("title_textedit");
    QPlainTextEdit* description = findChild<QPlainTextEdit*>("des_textedit");
    QString title_text = title->toPlainText();
    QString des_text = description->toPlainText();
    std::string path = GetExePath();
    std::string datapath = "./data";
    if (!(std::filesystem::exists(datapath) && std::filesystem::is_directory(datapath))){
        if (std::filesystem::exists(datapath)){
            if (!std::filesystem::remove(datapath)){
                QMessageBox::warning(this,"Error",concat("Unable to remove file/directory ",datapath));
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
    catch(nlohmann::json_abi_v3_11_2::detail::parse_error){
#if _DEBUG
        std::cout << "error encountered, handling it" <<std::endl;
        std::getline(f, line);
        std::cout << line << std::endl;
#endif
        f >> j;
    }

    if (j.empty()){
        j["tasks"] = json::array();
    }
    json taskobj;
    taskobj["title"] = title_text.toStdString();
    taskobj["description"] = des_text.toStdString();
    QCheckBox* cb = findChild<QCheckBox*>("remindercb");
    if (cb->isChecked()){
        QDateTimeEdit* dt = findChild<QDateTimeEdit*>("reminderdatetime");
        time_t t = dt->dateTime().toSecsSinceEpoch();
        taskobj["reminder_date"] = t;
    }
    else{
        taskobj["reminder_date"] = 0;
    }
    j["tasks"].push_back(taskobj);
    std::ofstream x("./data/data.json",std::ios::out|std::ios::trunc);
    std::cout << j << std::endl;
    x << j << std::endl;
    listwidget* tasks = &listwidget::getInstance();
    tasks->loadwidgets(j["tasks"]);
    QDialog::accept();
}

void newTask::reject(){
    QDialog::reject();
}
