#ifndef TASKITEM_H
#define TASKITEM_H

#include <QListWidgetItem>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class taskitem : public QListWidgetItem
{
public:
    taskitem(const json& json_item);
private:
    std::string title;
    std::string description;
    std::time_t reminder_time;
};

#endif // TASKITEM_H
