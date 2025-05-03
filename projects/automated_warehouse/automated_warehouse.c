#include <stdio.h>
#include <string.h>
#include <ctype.h> // isdigit 추가

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

#include "devices/timer.h"
#include "devices/shutdown.h"

#include "projects/automated_warehouse/aw_manager.h"
#include "projects/automated_warehouse/aw_message.h"

#include "projects/automated_warehouse/map.h"

struct semaphore cnt_sema;

struct robot *robots;
int robot_num;
int check_message = 0;

// strdup 대체 함수
char *my_strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy)
        memcpy(copy, s, len);
    return copy;
}

// cnt에서 보낸 값을 모두 읽었다고 했을 때 boolean으로 확인해주는 함수
bool robot_all_move()
{

    for (int i = 0; i < robot_num; i++)
    {
        ASSERT(boxes_from_central_control_node != NULL);
        // dirtyBit == 1이라는게 읽지 않았다는 의미
        if (boxes_from_central_control_node[i].dirtyBit == 1)
        {
            return false;
        }
    }
    return true;
}

// 로봇의 위치를 받아서 저장
int **get_robot_position(int **robot_position)
{
    // 로봇의 위치를 받아서 저장
    for (int i = 0; i < robot_num; i++)
    {
        ASSERT(boxes_from_robots != NULL);
        if (boxes_from_robots[i].dirtyBit != 1)
        {
            printf("robot %d don't send msg", i);
            continue;
        }
        struct message robot_pos = boxes_from_robots[i].msg;
        boxes_from_robots[i].dirtyBit = 0;
        robot_position[i][0] = robot_pos.row;
        robot_position[i][1] = robot_pos.col;
    }
}

// 모든 로봇의 운송이 끝났다면 true 반환
bool transport_over()
{
    for (int i = 0; i < robot_num; i++)
    {
        if (robots[i].is_finished == false)
            return false;
    }
    return true;
}

void check_moving_item(bool *moving_item)
{
    for (int i = 0; i < robot_num; i++)
    {
        if (robots[i].is_finished)
            continue;
        if (robots[i].row == ROW_W && robots[i].col == COL_W)
            continue;

        moving_item[robots[i].item_number - 1] = true;
    }
}

// central control node thread
void cnt()
{
    int **robot_position = malloc(sizeof(int *) * robot_num);
    for (int i = 0; i < robot_num; i++)
        robot_position[i] = malloc(sizeof(int) * 2);

    bool moving_item[7];
    for (int i = 0; i < 7; i++)
        moving_item[i] = false;

    while (1)
    {
        // semaphore로 대기했다가 로봇이 데이터를 보낼 때마다 확인
        sema_down(&cnt_sema);

        // check_message가 robot_num과 같을 때 즉, 모두 block되었을 때
        if (robot_all_move())
        {
            // 만약 모든 로봇이 운송을 끝냈다면 종료(하역 장소에 존재)
            if (transport_over())
            {
                printf("is over\n");
                shutdown_power_off();
            }

            // 로봇의 위치들이 어디인지 저장
            get_robot_position(robot_position);

            // 로봇의 위치 모두 확인 후 print_map 호출
            print_map(robots, robot_num);

            // 현재 로봇들이 어떤 물건을 배송하고 있는지 확인
            check_moving_item(moving_item);

            /*
             * 로봇의 위치를 통해 움직일 위치 지정
             *
             * 유의 사항
             * 1. 물건을 받는 위치(숫자)에 로봇이 존재할 경우
             *    그 바로 위 or 아래에 로봇이 오지 못하도록 한다.
             *
             * message_box에 덧씌우기
             */
            for (int i = 0; i < robot_num; i++)
            {
                int row = robots[i].row;
                int col = robots[i].col;
                for (int j = 0; j < 7; j++)
                {
                    if (row == item_positions[j][0] && col == item_positions[j][1])
                    {
                        robots[i].current_payload = 1;
                    }
                }
                for (int j = 0; j < 3; j++)
                {
                    if (row == finish_positions[j][0] && col == finish_positions[j][1])
                    {
                        robots[i].is_finished = true;
                    }
                }

                char direction;

                if (robots[i].current_payload != 0)
                    direction = down_direction_map[robots[i].item_number - 1][alphabet_to_index(robots[i].destination)][robots[i].row][robots[i].col];
                else
                    direction = up_direction_map[robots[i].item_number - 1][robots[i].row][robots[i].col];

                if (robots[i].is_finished)
                    direction = 'X';

                // 시작 지점의 robot 중 해당 item을 움직이는 로봇이 있으면 X
                if (row == ROW_W && col == COL_W)
                {
                    if (moving_item[robots[i].item_number - 1])
                        direction = 'X';
                    else
                        moving_item[robots[i].item_number - 1] = true;
                }

                struct message msg =
                    {
                        robots[i].row,
                        robots[i].col,
                        robots[i].current_payload,
                        robots[i].required_payload,
                        direction // direction만 의미 O
                    };
                boxes_from_central_control_node[i].msg = msg;
                boxes_from_central_control_node[i].dirtyBit = 1;
            }

            for (int i = 0; i < 7; i++)
                moving_item[i] = false;

            unblock_threads();
            increase_step();
        }
    }

    for (int i = 0; i < robot_num; i++)
    {
        free(robot_position[i]);
    }
    free(robot_position);
}

// 로봇이 이동할 위치에 있는지 확인
bool can_move(int idx, int row, int col)
{
    // 특수한 경우(2,3)으로 갈 때 (3,3)에 있는게 있으면 가면 안됨. 반대도 마찬가지
    if (col == 1)
    {
        for (int i = 0; i < robot_num; i++)
        {
            if (i == idx)
                continue;
            if (robots[i].col == 1)
                return false;
        }
    }
    if (col == 5)
    {
        for (int i = 0; i < robot_num; i++)
        {
            if (i == idx)
                continue;
            if (robots[i].col == 5 && robots[i].row != ROW_W)
                return false;
        }
    }
    // 이동할 위치에 로봇이 존재하는지 확인
    for (int i = 0; i < robot_num; i++)
    {
        if (robots[i].row == row && robots[i].col == col)
        {
            if ((row == ROW_A && col == COL_A) || (row == ROW_B && col == COL_B) || (row == ROW_C && col == COL_C))
                continue;
            else
                return false;
        }
    }
    return true;
}
// 실제 로봇 이동
void thread_action(void *aux)
{
    while (1)
    {
        int idx = *((int *)aux);

        char direction = boxes_from_central_control_node[idx].msg.cmd;
        boxes_from_central_control_node[idx].dirtyBit = 0;
        __sync_synchronize();

        /*
         * cnt가 알려준 방향으로 이동(by cmd)
         */
        int move_row = 0;
        int move_col = 0;
        switch (direction)
        {
        case 'U':
            move_row = -1;
            break;
        case 'D':
            move_row = 1;
            break;
        case 'L':
            move_col = -1;
            break;
        case 'R':
            move_col = 1;
            break;
        default:
            break;
        }

        // 만약 이동할 위치에 로봇이 있다면 '대기'
        if (can_move(idx, robots[idx].row + move_row, robots[idx].col + move_col))
        {
            robots[idx].row += move_row;
            robots[idx].col += move_col;
        }

        // 위치 메세지 등 robot -> cnt
        struct message msg = {
            robots[idx].row,
            robots[idx].col,
            robots[idx].current_payload,
            robots[idx].required_payload,
            0 // cmd -> cnt to robot == 의미 없음.
        };

        boxes_from_robots[idx].dirtyBit = 1;
        boxes_from_robots[idx].msg = msg;

        sema_up(&cnt_sema);
        block_thread();
    }
}

// 첫 번째 인자를 숫자로 바꿔서 return해주는 함수
int to_number(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        printf("Error: empty argument\n");
        return -1;
    }

    for (const char *p = str; *p; p++)
    {
        if (!isdigit((unsigned char)*p))
        {
            printf("Error: non-digit character in input '%s'\n", str);
            return -1;
        }
    }

    return atoi(str);
}

char **split_colon_dynamic(const char *input, int *count)
{
    char *str = my_strdup(input); // 원본 보호용 복사본
    char *token;
    char *save_ptr;

    int capacity = 4;
    int size = 0;
    char **result = malloc(capacity * sizeof(char *));

    token = strtok_r(str, ":", &save_ptr);
    while (token != NULL)
    {
        if (size >= capacity)
        {
            capacity *= 2;
            result = realloc(result, capacity * sizeof(char *));
        }
        result[size++] = my_strdup(token);
        token = strtok_r(NULL, ":", &save_ptr);
    }

    *count = size;
    free(str);
    return result;
}

// entry point of simulator
//  argv[1]: robot num, argv[2]: item number and destination (ex: 1A:2B:3C:4D)
void run_automated_warehouse(char **argv)
{
    sema_init(&cnt_sema, 0);
    init_automated_warehouse(argv); // do not remove this
    init_direction_map();

    robot_num = to_number(argv[1]);
    int pair_num = 0;

    if (robot_num == -1)
    {
        printf("Error: Invalid robot num(argv[1])");
        shutdown_power_off();
    }
    // robot의 message box들 생성
    init_message_boxes(robot_num);

    char **num_place_pair = split_colon_dynamic(argv[2], &pair_num);

    if (pair_num != robot_num)
    {
        printf("Error: pair는 robot과 1:1 매칭되어야 한다.");
        shutdown_power_off();
    }

    robots = malloc(sizeof(struct robot) * robot_num);
    char **robot_name = malloc(sizeof(char *) * robot_num);
    for (int i = 0; i < robot_num; i++)
    {
        robot_name[i] = malloc(sizeof(char) * 10);
        snprintf(robot_name[i], sizeof(10), "R%d", i + 1);
    }
    for (int i = 0; i < robot_num; i++)
    {
        int item_number = num_place_pair[i][0] - '0';
        char destination = num_place_pair[i][1];
        if (item_number < 1 || item_number > 7)
        {
            printf("Error: item number is out of range(1~7)\n");
            shutdown_power_off();
        }
        if (!(destination == 'A' || destination == 'B' || destination == 'C'))
        {
            printf("Error: destination is out of range(A~C)\n");
            shutdown_power_off();
        }
        setRobot(&robots[i], robot_name[i], ROW_W, COL_W, 1, 0, item_number, destination);
    }

    /*
     * Create threads for cnt and robots
     * thread parameter에 관한 설명
     * 첫 번째 인자: thread name
     * 두 번째 인자: thread priority (0이면 default)
     * 세 번째 인자: thread function(실제 실행될 함수)
     * 네 번째 인자: thread function에 전달할 인자
     * thread_create()는 thread를 생성하고, 생성된 thread는 ready queue에 들어간다.
     */
    tid_t *threads = malloc(sizeof(tid_t) * (robot_num + 1));

    // 중심제어 시스템
    threads[0] = thread_create("CNT", 0, &cnt, NULL);

    // 직접 로봇을 움직일 thread들
    for (int i = 0; i < robot_num; i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i;

        threads[i + 1] = thread_create(robot_name[i], 0, &thread_action, arg);
    }
}