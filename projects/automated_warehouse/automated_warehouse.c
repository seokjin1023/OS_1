#include <stdio.h>
#include <string.h>
#include <ctype.h> // isdigit 추가

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

#include "devices/timer.h"

#include "projects/automated_warehouse/aw_manager.h"
#include "projects/automated_warehouse/aw_message.h"

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


//cmt에서 보낸 값을 모두 읽었다고 했을 때 boolean으로 확인해주는 함수
bool robot_all_move() {
    for(int i = 0; i < robot_num; i++) {
        if(boxes_from_central_control_node[i].dirtyBit == 1)
            return false;
    }
    return true;
}
//central control node thread
void cnt()
{
    while(1)
    {
        //semaphore로 대기했다가 로봇이 데이터를 보낼 때마다 확인인
        sema_down(&cnt_sema);

        //check_message가 robot_num과 같을 때 즉, 모두 block되었을 때
        if(robot_all_move())
        {
            unblock_threads();
            increase_step();
            print_map(robots, robot_num);
            check_message = 0;
            /*
            * 로봇이 보낸 값들을 모두 받아서 움직일 위치 지정 후 
            * 움직일 위치에 대한 지정은 모든 위치를 확인 후 어떤 함수로 확인
            * 다른 thread 위치까지 고려해서 알려줘야 할지는 고민 중중
            * message_box에 덧씌우기
            */
        }
    }
}

void thread_action(void * aux)
{
    while(1) {
        int idx = *((int *)aux);
        printf("thread %d execute", idx);

        struct message to_move = boxes_from_central_control_node[idx].msg;
        boxes_from_central_control_node[idx].dirtyBit = 0;

        /*
        * to_move에서 cnt가 알려준 방향으로 이동
        * 만약 이동할 공간을 다른 robot이 점유 중이라면 대기(이동 X)
        */
        
        struct message msg = {
            robots[idx].row,
            robots[idx].col,
            robots[idx].current_payload,
            robots[idx].required_payload,
            -1 //cmd -> cnt to robot == 의미 없음.
        };
        
        boxes_from_robots[idx].dirtyBit = 1;
        boxes_from_robots[idx].msg = msg;

        block_thread(robots[idx]);
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
    init_automated_warehouse(argv); // do not remove this

    printf("implement automated warehouse!\n");

    robot_num = to_number(argv[1]);
    int pair_num = 0;

    if (robot_num == -1)
    {
        printf("Error: Invalid robot num(argv[1])");
        return;
    }
    //robot의 message box들 생성
    init_message_boxes(robot_num);

    char **num_place_pair = split_colon_dynamic(argv[2], &pair_num); // ✅ &pair_num 전달

    if (pair_num != robot_num)
    {
        printf("Error: pair는 robot과 1:1 매칭되어야 한다.");
        return;
    }

    robots = malloc(sizeof(struct robot) * robot_num);
    printf("Generate robots\n");
    for (int i = 0; i < robot_num; i++)
    {
        char robot_name[10];
        int item_number = num_place_pair[i][0] - '0';
        char destination = num_place_pair[i][1];
        snprintf(robot_name, sizeof(robot_name), "R%d", i + 1);
        setRobot(&robots[i], robot_name, 5, 6, 1, 0, item_number, destination);
        printf("robot name: %s, item_number: %d, destination: %c\n", robots[i].name, robots[i].item_number, robots[i].destination);
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
    printf("create cnt thread\n");

    // 직접 로봇을 움직일 thread들
    for (int i = 0; i < robot_num; i++)
    {
        char robot_name[10];
        snprintf(robot_name, sizeof(robot_name), "R%d", i);
        int *arg = malloc(sizeof(int));
        *arg = i;

        threads[i + 1] = thread_create(robot_name, 0, &thread_action, arg);
        printf("create robot thread %d\n", i);
    }
}