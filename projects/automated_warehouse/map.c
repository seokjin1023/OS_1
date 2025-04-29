#include "map.h"

int alphabet_to_index(char alpha)
{
  return alpha - 'A'; // 'A'~'C' -> 0~2
}

// down_direction_map[0][0]
char dir_0_0[6][7] = {
    "XX0XXXX",
    "XRUXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[0][1]
char dir_0_1[6][7] = {
    "XXXXXXX",
    "XDXXXXX",
    "0LXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[0][2]
char dir_0_2[6][7] = {
    "XXXXXXX",
    "XDXXXXX",
    "XRDXXXX",
    "XXDXXXX",
    "XXDXXXX",
    "XX0XXXX",
};

// down_direction_map[1][0]
char dir_1_0[6][7] = {
    "XX0XXXX",
    "XXULXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[1][1]
char dir_1_1[6][7] = {
    "XXXXXXX",
    "XXXDXXX",
    "0LLLXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[1][2]
char dir_1_2[6][7] = {
    "XXXXXXX",
    "XXXDXXX",
    "XXDLXXX",
    "XXDXXXX",
    "XXDXXXX",
    "XX0XXXX",
};

// down_direction_map[2][0]
char dir_2_0[6][7] = {
    "XX0XXXX",
    "XXUXDXX",
    "XXULLXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[2][1]
char dir_2_1[6][7] = {
    "XXXXXXX",
    "XXXXDXX",
    "0LLLLXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[2][2]
char dir_2_2[6][7] = {
    "XXXXXXX",
    "XXXXDXX",
    "XXDLLXX",
    "XXDXXXX",
    "XXDXXXX",
    "XX0XXXX",
};

// down_direction_map[3][0]
char dir_3_0[6][7] = {
    "XX0XXXX",
    "XXUXXDX",
    "XXULLLX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[3][1]
char dir_3_1[6][7] = {
    "XXXXXXX",
    "XXXXXDX",
    "0LLLLLX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
};

// down_direction_map[3][2]
char dir_3_2[6][7] = {
    "XXXXXXX",
    "XXXXXDX",
    "XXDLLLX",
    "XXDXXXX",
    "XXDXXXX",
    "XX0XXXX",
};

// down_direction_map[4][0]
char dir_4_0[6][7] = {
    "XX0XXXX",
    "XXUXXXX",
    "XXUXXXX",
    "XRUXXXX",
    "XUXXXXX",
    "XXXXXXX",
};

// down_direction_map[4][1]
char dir_4_1[6][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "0LXXXXX",
    "XUXXXXX",
    "XUXXXXX",
    "XXXXXXX",
};

// down_direction_map[4][2]
char dir_4_2[6][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XRDXXXX",
    "XX0XXXX",
};

// down_direction_map[5][0]
char dir_5_0[6][7] = {
    "XX0XXXX",
    "XXUXXXX",
    "XXUXXXX",
    "XXULXXX",
    "XXXUXXX",
    "XXXXXXX",
};

// down_direction_map[5][1]
char dir_5_1[6][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "0LLXXXX",
    "XXULXXX",
    "XXXUXXX",
    "XXXXXXX",
};

// down_direction_map[5][2]
char dir_5_2[6][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXDLXXX",
    "XX0XXXX",
};

// down_direction_map[6][0]
char dir_6_0[6][7] = {
    "XX0XXXX",
    "XXUXXXX",
    "XXUXXXX",
    "XXULLXX",
    "XXXXUXX",
    "XXXXXXX",
};

// down_direction_map[6][1]
char dir_6_1[6][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "0LLXXXX",
    "XXULLXX",
    "XXXXUXX",
    "XXXXXXX",
};

// down_direction_map[6][2]
char dir_6_2[6][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXDLLXX",
    "XXDXUXX",
    "XX0XXXX",
};

// up_direction_map[0]
char dir_0[6][7] = {
    "XXXXXXX",
    "X0XXXXX",
    "XULXXXX",
    "XXULLLX",
    "XXXXXUX",
    "XXXXXUX",
};

// up_direction_map[1]
char dir_1[6][7] = {
    "XXXXXXX",
    "XXX0XXX",
    "XXXULLX",
    "XXXXXUX",
    "XXXXXUX",
    "XXXXXUX",
};
// up_direction_map[2]
char dir_2[6][7] = {
    "XXXXXXX",
    "XXXX0XX",
    "XXXXULX",
    "XXXXXUX",
    "XXXXXUX",
    "XXXXXUX",
};
// up_direction_map[3]
char dir_3[6][7] = {
    "XXXXXXX",
    "XXXXX0X",
    "XXXXXUX",
    "XXXXXUX",
    "XXXXXUX",
    "XXXXXUX",
};
// up_direction_map[4]
char dir_4[6][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XDLLLLX",
    "X0XXXUX",
    "XXXXXUX",
};
// up_direction_map[5]
char dir_5[6][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXDLLX",
    "XXX0XUX",
    "XXXXXUX",
};
// up_direction_map[6]
char dir_6[6][7] = {
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXXXXX",
    "XXXX0LX",
    "XXXXXUX",
};

char down_direction_map[7][3][6][7];
char up_direction_map[7][6][7];

void init_direction_map()
{
  int item_position[7][2] = {
      {1, 1}, // 1
      {1, 3}, // 2
      {1, 4}, // 3
      {1, 5}, // 4
      {4, 1}, // 5
      {4, 3}, // 6
      {4, 4}  // 7
  };

  int finish_position[3][2] = {
      {0, 2}, // A
      {2, 0}, // B
      {5, 2}  // C
  };

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
