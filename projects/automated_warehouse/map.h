#ifndef _PROJECTS_PROJECT1_MAP_H__
#define _PROJECTS_PROJECT1_MAP_H__

int item_positions[7][2];
int finish_positions[3][2];

// start/end index를 주면 거기에 맞는 6x7 direction배열으로 이동 위치 파악
extern char down_direction_map[7][3][6][7];
extern char up_direction_map[7][6][7];

int alphabet_to_index(char alpha);

void init_direction_map(void);

#endif