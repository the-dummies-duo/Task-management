#include "mainwindow.h"
#include "actions.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QAction>
#include <QObject>

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
    Actions* action = Actions::Instance();
    QAction* action_Quit = w.findChild<QAction*>("action_Quit");
    QAction* action_GitHub = w.findChild<QAction*>("actionOur_GitHub");
    QObject::connect(action_Quit, &QAction::triggered, action, qOverload<>(&Actions::action_Quit));
    QObject::connect(action_GitHub,&QAction::triggered,action,qOverload<>(&Actions::action_GitHub));
    //printf(Actions::Instance());
    QMetaObject::connectSlotsByName(action);
    return a.exec();
}
