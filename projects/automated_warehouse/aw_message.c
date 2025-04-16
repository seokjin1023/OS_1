#include "projects/automated_warehouse/aw_message.h"

/** message boxes from central control node to each robot */
struct message_box *boxes_from_central_control_node;
/** message boxes from robots to central control node */
struct message_box *boxes_from_robots;

void init_message_boxes(int robot_num) {
    boxes_from_central_control_node = malloc(sizeof(struct message_box) * robot_num);
    boxes_from_robots = malloc(sizeof(struct message_box) * robot_num);

    for(int i = 0; i < robot_num; i++) 
    {
        boxes_from_central_control_node[i].dirtyBit = 0;
        boxes_from_robots[i].dirtyBit = 0;
    }
}
