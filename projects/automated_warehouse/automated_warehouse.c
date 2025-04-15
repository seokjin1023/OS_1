#include <stdio.h>
#include <string.h>

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

#include "devices/timer.h"

#include "projects/automated_warehouse/aw_manager.h"

struct robot* robots;

// test code for central control node thread
void test_cnt(){
        while(1){
                print_map(robots, 4);
                thread_sleep(1000);
                block_thread();
        }
}

// test code for robot thread
void test_thread(void* aux){
        int idx = *((int *)aux);
        int test = 0;
        while(1){
                printf("thread %d : %d\n", idx, test++);
                thread_sleep(idx * 1000);
        }
}

//첫 번째 인자를 숫자로 바꿔서 return해주는 함수
int to_number(const char *str) {
    if (str == NULL || *str == '\0') { //NULL
        printf("Error: empty argument\n");
        return -1; 
    }

    for (const char *p = str; *p; p++) { //Not Integer
        if (!isdigit((unsigned char)*p)) {
            printf("Error: non-digit character in input '%s'\n", str);
            return -1;
        }
    }

    return atoi(str);
}

//두 번째 인자를 : 기준 split해서 char**배열로 return
char** split_colon_dynamic(const char* input, int* count) {
    char* str = strdup(input);  // 원본 보호용 복사본
    char* token;
    int capacity = 4;  // 초기 배열 크기
    int size = 0;

    char** result = malloc(capacity * sizeof(char*));

    token = strtok(str, ":");
    while (token != NULL) {
        if (size >= capacity) {
            capacity *= 2;  // 공간이 부족하면 2배로 증가
            result = realloc(result, capacity * sizeof(char*));
        }
        result[size++] = strdup(token);  // 각 토큰 복사해서 저장
        token = strtok(NULL, ":");
    }

    *count = size;
    free(str);
    return result;
}

// entry point of simulator
void run_automated_warehouse(char **argv)
{
        init_automated_warehouse(argv); // do not remove this

        printf("implement automated warehouse!\n");

        /*
        real case robots
        */
        int robot_num = to_number(argv[1]);
        int pair_num = 0;

        if(robot_num == -1) {
            printf("Error: Invalid robot num(argv[1])");
            return;
        }

        char** num_place_pair = split_colon_dynamic(argv[2], pair_num);
        if(pair_num != robot_num) {
            printf("Error: pair는 robot과 1:1 매칭되어야 한다.");
            return;
        }

        robots = malloc(sizeof(struct robot) * robot_num);
        for(int i = 0; i < robot_num; i++) {
            char robot_name[10];
            int item_number = num_place_pair[i][0] - '0';
            char destination = num_place_pair[i][1];
            snprintf(robot_name, sizeof(robot_name), "R%d", i + 1);
            setRobot(&robots[i], robot_name, 5, 6, 1, 0, item_number, destination);
        }


        // example of create thread
        tid_t* threads = malloc(sizeof(tid_t) * (robot_num + 1));
        int idxs[4] = {1, 2, 3, 4};
        threads[0] = thread_create("CNT", 0, &test_cnt, NULL);
        threads[1] = thread_create("R1", 0, &test_thread, &idxs[1]);
        threads[2] = thread_create("R2", 0, &test_thread, &idxs[2]);
        threads[3] = thread_create("R3", 0, &test_thread, &idxs[3]);

        // if you want, you can use main thread as a central control node
        
}