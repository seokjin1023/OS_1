#include "projects/automated_warehouse/robot.h"

#include <stdio.h>

/**
 * A function setting up robot structure
 */
void setRobot(struct robot *_robot, const char *name, int row, int col, int required_payload, int current_payload, int item_number, char destination)
{
    _robot->name = name;
    _robot->row = row;
    _robot->col = col;
    _robot->required_payload = required_payload;
    _robot->current_payload = current_payload;

    // add
    _robot->item_number = item_number;
    _robot->destination = destination;

    _robot->is_finished = false;
}