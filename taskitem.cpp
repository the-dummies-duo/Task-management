#include "taskitem.h"


taskitem::taskitem(const json& json_item)
{
    bool date_;
    if (json_item["reminder_date"] != 0){
        date_ = true;

    }
    else{
        date_ = false;
    }
}
