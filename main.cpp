#include "mainwindow.h"
#include "actions.h"
#include <QApplication>
#include <QPushButton>
#include <QAction>
#include <QObject>
#include "includes.h"

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
    QAction* action_New = w.findChild<QAction*>("action_New");
    QObject::connect(action_Quit, &QAction::triggered, &action, &Actions::action_Quit);
    QObject::connect(action_GitHub,&QAction::triggered,&action, &Actions::action_GitHub);
    QObject::connect(action_New, &QAction::triggered, &action, &Actions::action_New);
    //printf(Actions::Instance());
    QMetaObject::connectSlotsByName(&action);
    w.load();
    return a.exec();
}
