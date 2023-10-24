#ifndef MANAGER_H
#define MANAGER_H
#include "includes.h"

class manager
{
public:
    manager();
    static QJsonObject readdatajson();
    static void writejson(const QJsonObject& j);
};

#endif // MANAGER_H
