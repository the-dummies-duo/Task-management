#include "newtask.h"
#include "ui_newtask.h"
#include "mainwindow.h"
#include "actions.h"
#include "listwidget.h"
#include "manager.h"

#include "includes.h"


#define concat(a,b) a#b

newTask::newTask(bool newtask,QJsonObject* original,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newTask)
{
    this->newtask = newtask;
    this->original = original;
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
    QPushButton* del = findChild<QPushButton*>("deletebutton");
    if (!newtask){
        del->setEnabled(true);
        QObject::connect(del,&QPushButton::clicked,this,[this](){this->delete_();});
    }
    if (original && (*original)["reminder_date"].toInt() != 0){
        dt->setDateTime(QDateTime::fromSecsSinceEpoch((*original)["reminder_date"].toInt()));
    }
    if (original){
        QPlainTextEdit* title = findChild<QPlainTextEdit*>("title_textedit");
        QPlainTextEdit* description = findChild<QPlainTextEdit*>("des_textedit");
        title->setPlainText((*original)["title"].toString());
        description->setPlainText((*original)["description"].toString());
    }
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
    const std::string path = QApplication::applicationDirPath().toStdString();
    const std::string datapath = "./data";

    const std::string jsonpath = "./data/data.json";
    auto j = manager::readdatajson();
    if (j.empty()){
        j["tasks"] = QJsonArray();
    }

    QJsonObject taskobj;;
    QJsonArray tasksarray = j["tasks"].toArray();
    taskobj["title"] = title_text;
    taskobj["description"] = des_text;
    taskobj["id"] = QUuid::createUuid().toString();
    QCheckBox* cb = findChild<QCheckBox*>("remindercb");
    if (cb->isChecked()){
        QDateTimeEdit* dt = findChild<QDateTimeEdit*>("reminderdatetime");
        time_t t = dt->dateTime().toSecsSinceEpoch();
        taskobj["reminder_date"] = t;
    }
    else{
        taskobj["reminder_date"] = 0;
    }
    if (!newtask){
        QJsonObject original = *this->original;
        tasksarray.erase(std::find(tasksarray.begin(), tasksarray.end(), original));
        j["tasks"] = tasksarray;
    }
    taskobj["invoked"] = false;
    tasksarray.append(taskobj);
    j["tasks"] = tasksarray;
    manager::writejson(j);
    listwidget* tasks = &listwidget::getInstance();
    tasks->loadwidgets(j);
    QDialog::accept();
}

void newTask::reject(){
    QDialog::reject();
}
void newTask::delete_(){
    QPlainTextEdit* title = findChild<QPlainTextEdit*>("title_textedit");
    QPlainTextEdit* description = findChild<QPlainTextEdit*>("des_textedit");
    QString title_text = title->toPlainText();
    QString des_text = description->toPlainText();
    const std::string path = QApplication::applicationDirPath().toStdString();
    const std::string datapath = "./data";

    const std::string jsonpath = "./data/data.json";
    auto j = manager::readdatajson();
    if (j.empty()){
        j["tasks"] = QJsonArray();
    }

    QJsonObject taskobj;;
    QJsonArray tasksarray = j["tasks"].toArray();
    taskobj["title"] = title_text;
    taskobj["description"] = des_text;
    taskobj["id"] = QUuid::createUuid().toString();
    QCheckBox* cb = findChild<QCheckBox*>("remindercb");
    if (cb->isChecked()){
        QDateTimeEdit* dt = findChild<QDateTimeEdit*>("reminderdatetime");
        time_t t = dt->dateTime().toSecsSinceEpoch();
        taskobj["reminder_date"] = t;
    }
    else{
        taskobj["reminder_date"] = 0;
    }
    if (!newtask){
        QJsonObject original = *this->original;
        tasksarray.erase(std::find(tasksarray.begin(), tasksarray.end(), original));
        j["tasks"] = tasksarray;
    }
    taskobj["invoked"] = false;
    j["tasks"] = tasksarray;
    manager::writejson(j);
    listwidget* tasks = &listwidget::getInstance();
    tasks->loadwidgets(j);
    QDialog::accept();
}
