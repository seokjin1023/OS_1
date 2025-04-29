#include "projects/automated_warehouse/robot.h"

/**
 * A function setting up robot structure
 */
void setRobot(struct robot *_robot, const char *name, int row, int col, int required_payload, int current_payload, int item_number, char destination, bool get_item)
{
    _robot->name = name;
    _robot->row = row;
    _robot->col = col;
    _robot->required_payload = required_payload;
    _robot->current_payload = current_payload;

    // add
    _robot->item_number = item_number;
    _robot->destination = destination;
    _robot->get_item = get_item;
}