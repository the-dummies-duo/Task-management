#include "mainwindow.h"
#include "actions.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QAction>
#include <QObject>
#include <QPushButton>
#include <string>
#include <locale>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Task-management_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    Actions action = Actions(&w);
    QAction* action_Quit = w.findChild<QAction*>("action_Quit");
    QAction* action_GitHub = w.findChild<QAction*>("actionOur_GitHub");
    QAction* action_change_label = w.findChild<QAction*>("actionChange_test_label");
    QPushButton* action_Save = w.findChild<QPushButton*>("SaveButton");
    QObject::connect(action_Quit, &QAction::triggered, &action, &Actions::action_Quit);
    QObject::connect(action_GitHub,&QAction::triggered,&action, &Actions::action_GitHub);
    QObject::connect(action_change_label, &QAction::triggered, &action, &Actions::action_debug_text);
    QObject::connect(action_Save, &QPushButton::clicked, &action, &Actions::action_Save);
    //printf(Actions::Instance());
    QMetaObject::connectSlotsByName(&action);
    return a.exec();
}
