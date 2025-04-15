#include <stdio.h>
#include <string.h>
#include <ctype.h> // isdigit 추가

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

#include "devices/timer.h"

#include "projects/automated_warehouse/aw_manager.h"

struct robot *robots;

// strdup 대체 함수
char *my_strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy)
        memcpy(copy, s, len);
    return copy;
}

// test code for central control node thread
void test_cnt()
{
    while (1)
    {
        print_map(robots, 4);
        thread_sleep(1000);
        block_thread();
    }
}

// test code for robot thread
void test_thread(void *aux)
{
    int idx = *((int *)aux);
    int test = 0;
    while (1)
    {
        printf("thread %d : %d\n", idx, test++);
        thread_sleep(idx * 1000);
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

    int robot_num = to_number(argv[1]);
    int pair_num = 0;

    if (robot_num == -1)
    {
        printf("Error: Invalid robot num(argv[1])");
        return;
    }

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
    int *idxs = malloc(sizeof(int) * (robot_num));
    for (int i = 0; i < robot_num; i++)
        idxs[i] = i + 1;

    // 중심제어 시스템
    threads[0] = thread_create("CNT", 0, &test_cnt, NULL);
    printf("create cnt thread\n");

    // 직접 로봇을 움직일 thread들
    for (int i = 0; i < robot_num; i++)
    {
        char robot_name[10];
        snprintf(robot_name, sizeof(robot_name), "R%d", idxs[i]);
        threads[idxs[i]] = thread_create(robot_name, 0, &test_thread, &idxs[i]);
        printf("create robot thread %d\n", idxs[i]);
    }
}