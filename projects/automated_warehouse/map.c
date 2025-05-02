#include "map.h"

int alphabet_to_index(char alpha)
{
  return alpha - 'A'; // 'A'~'C' -> 0~2
}

// down_direction_map[0][0]
char dir_0_0[7][7] = {
    "XXXXXXX",
    "0LXXXXX",
    "XULXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[0][1]
char dir_0_1[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XDLXXXX",
    "0LXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[0][2]
char dir_0_2[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XDLXXXX",
    "XDXXXXX",
    "XDXXXXX",
    "0LXXXXX",
    "XXXXXXX",
};

// down_direction_map[1][0]
char dir_1_0[7][7] = {
    "XXXXXXX",
    "0LXXXXX",
    "XUXXXXX",
    "XULXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[1][1]
char dir_1_1[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "0LLXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[1][2]
char dir_1_2[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XDLXXXX",
    "XDXXXXX",
    "0LXXXXX",
    "XXXXXXX",
};

// down_direction_map[2][0]
char dir_2_0[7][7] = {
    "XXXXXXX",
    "0LXXXXX",
    "XUXXXXX",
    "XUXXXXX",
    "XULXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[2][1]
char dir_2_1[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "0LXXXXX",
    "XULXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[2][2]
char dir_2_2[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XDLXXXX",
    "0LXXXXX",
    "XXXXXXX",
};

// down_direction_map[3][0]
char dir_3_0[7][7] = {
    "XXXXXXX",
    "0LXXXXX",
    "XUXXRDX",
    "XUXXXDX",
    "XUXXXDX",
    "XULLLLX",
    "XXXXXXX",
};

// down_direction_map[3][1]
char dir_3_1[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXRDX",
    "0LXXXDX",
    "XUXXXDX",
    "XULLLLX",
    "XXXXXXX",
};

// down_direction_map[3][2]
char dir_3_2[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXRDX",
    "XXXXXDX",
    "XXXXXDX",
    "0LLLLLX",
    "XXXXXXX",
};

// down_direction_map[4][0]
char dir_4_0[7][7] = {
    "XXXXXXX",
    "0LXXXXX",
    "XUXXXXX",
    "XUXXRDX",
    "XUXXXDX",
    "XULLLLX",
    "XXXXXXX",
};

// down_direction_map[4][1]
char dir_4_1[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "0LXXRDX",
    "XUXXXDX",
    "XULLLLX",
    "XXXXXXX",
};

// down_direction_map[4][2]
char dir_4_2[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXRDX",
    "XXXXXDX",
    "0LLLLLX",
    "XXXXXXX",
};

// down_direction_map[5][0]
char dir_5_0[7][7] = {
    "XXXXXXX",
    "0LXXXXX",
    "XUXXXXX",
    "XUXXXXX",
    "XUXXDXX",
    "XULLLXX",
    "XXXXXXX",
};

// down_direction_map[5][1]
char dir_5_1[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "0LXXXXX",
    "XUXXDXX",
    "XULLLXX",
    "XXXXXXX",
};

// down_direction_map[5][2]
char dir_5_2[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXDXX",
    "0LLLLXX",
    "XXXXXXX",
};

// down_direction_map[6][0]
char dir_6_0[7][7] = {
    "XXXXXXX",
    "0LLLXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[6][1]
char dir_6_1[7][7] = {
    "XXXXXXX",
    "XDLLXXX",
    "XDXXXXX",
    "0LXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[6][2]
char dir_6_2[7][7] = {
    "XXXXXXX",
    "XDLLXXX",
    "XDXXXXX",
    "XDXXXXX",
    "XDXXXXX",
    "0LXXXXX",
    "XXXXXXX",
};

// up_direction_map[0]
char dir_0[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XR0XXXX",
    "XUXXXXX",
    "XUXXXXX",
    "XULLLLX",
    "XXXXXUX",
};

// up_direction_map[1]
char dir_1[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XR0XXXX",
    "XUXXXXX",
    "XULLLLX",
    "XXXXXUX",
};
// up_direction_map[2]
char dir_2[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XX0XXXX",
    "XXULLLX",
    "XXXXXUX",
};
// up_direction_map[3]
char dir_3[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXX0LX",
    "XXXXXUX",
    "XXXXXUX",
    "XXXXXUX",
    "XXXXXUX",
};
// up_direction_map[4]
char dir_4[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXX0LX",
    "XXXXXUX",
    "XXXXXUX",
    "XXXXXUX",
};
// up_direction_map[5]
char dir_5[7][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXX0XX",
    "XXXXULX",
    "XXXXXUX",
};
// up_direction_map[6]
char dir_6[7][7] = {
    "XXXXXXX",
    "XXX0LLX",
    "XXXXXUX",
    "XXXXXUX",
    "XXXXXUX",
    "XXXXXUX",
    "XXXXXUX",
};

int i_p[7][2] = {
    {2, 2}, // 1
    {3, 2}, // 2
    {4, 2}, // 3
    {2, 4}, // 4
    {3, 4}, // 5
    {4, 4}, // 6
    {1, 3}  // 7
};

int f_p[3][2] = {
    {1, 0}, // A
    {3, 0}, // B
    {5, 0}  // C
};

char down_direction_map[7][3][7][7];
char up_direction_map[7][7][7];
int item_position[7][2];
int finish_position[3][2];

void init_direction_map()
{
  memcpy(item_positions, i_p, sizeof(i_p));
  memcpy(finish_positions, f_p, sizeof(f_p));

  memcpy(down_direction_map[0][0], dir_0_0, sizeof(dir_0_0));
  memcpy(down_direction_map[0][1], dir_0_1, sizeof(dir_0_1));
  memcpy(down_direction_map[0][2], dir_0_2, sizeof(dir_0_2));
  memcpy(down_direction_map[1][0], dir_1_0, sizeof(dir_1_0));
  memcpy(down_direction_map[1][1], dir_1_1, sizeof(dir_1_1));
  memcpy(down_direction_map[1][2], dir_1_2, sizeof(dir_1_2));
  memcpy(down_direction_map[2][0], dir_2_0, sizeof(dir_2_0));
  memcpy(down_direction_map[2][1], dir_2_1, sizeof(dir_2_1));
  memcpy(down_direction_map[2][2], dir_2_2, sizeof(dir_2_2));
  memcpy(down_direction_map[3][0], dir_3_0, sizeof(dir_3_0));
  memcpy(down_direction_map[3][1], dir_3_1, sizeof(dir_3_1));
  memcpy(down_direction_map[3][2], dir_3_2, sizeof(dir_3_2));
  memcpy(down_direction_map[4][0], dir_4_0, sizeof(dir_4_0));
  memcpy(down_direction_map[4][1], dir_4_1, sizeof(dir_4_1));
  memcpy(down_direction_map[4][2], dir_4_2, sizeof(dir_4_2));
  memcpy(down_direction_map[5][0], dir_5_0, sizeof(dir_5_0));
  memcpy(down_direction_map[5][1], dir_5_1, sizeof(dir_5_1));
  memcpy(down_direction_map[5][2], dir_5_2, sizeof(dir_5_2));
  memcpy(down_direction_map[6][0], dir_6_0, sizeof(dir_6_0));
  memcpy(down_direction_map[6][1], dir_6_1, sizeof(dir_6_1));
  memcpy(down_direction_map[6][2], dir_6_2, sizeof(dir_6_2));

  memcpy(up_direction_map[0], dir_0, sizeof(dir_0));
  memcpy(up_direction_map[1], dir_1, sizeof(dir_1));
  memcpy(up_direction_map[2], dir_2, sizeof(dir_2));
  memcpy(up_direction_map[3], dir_3, sizeof(dir_3));
  memcpy(up_direction_map[4], dir_4, sizeof(dir_4));
  memcpy(up_direction_map[5], dir_5, sizeof(dir_5));
  memcpy(up_direction_map[6], dir_6, sizeof(dir_6));
}
