#ifndef INCLUDES_H
#define INCLUDES_H

#include <QObject>
#include <QWidget>
#include <QApplication>
#include <iostream>
#include <string>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVector>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMainWindow>
#include <QTimer>
#include <QJsonObject>
#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <stdlib.h>
#include <typeinfo>
#include <locale>
#include <algorithm>
#include <QScrollArea>
#include <QSize>
#include <QFont>
#include <qvariant.h>
#include <cstdint>
#include <typeinfo>
#include <QFile>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include <QJsonValue>
#include <codecvt>
#include <QUuid>
#include <QDateTimeEdit>
#include <QAbstractButton>
#include <QDateTime>
#include <QCloseEvent>

#include <QMessageBox>
#ifdef _WIN32
#define CreateDirectoryFunc(path) CreateDirectory(path,NULL)
#include <windows.h>
#else
#include <sys/stat.h>
#define CreateDirectoryFunc(path) mkdir(path,NULL)
#endif
#endif // INCLUDES_H
