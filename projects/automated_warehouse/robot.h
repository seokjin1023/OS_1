#ifndef _PROJECTS_PROJECT1_ROBOT_H__
#define _PROJECTS_PROJECT1_ROBOT_H__

#include "threads/thread.h"

/**
 * A Structure representing robot
 */
struct robot
{
    const char *name;
    int row;
    int col;
    int required_payload;
    int current_payload;

    // add
    int item_number;  // n번 물건
    char destination; // 어느 장소로 옮겨야 하는지지

    bool get_item;
};

void setRobot(struct robot *_robot, const char *name, int row, int col, int required_payload, int current_payload, int item_number, char destination, bool get_item);

#endif