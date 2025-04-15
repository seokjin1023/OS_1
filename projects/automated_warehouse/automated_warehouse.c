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

//첫 번째 인자를 숫자로 바꿔서 return해주는 함수수
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

// entry point of simulator
void run_automated_warehouse(char **argv)
{
        init_automated_warehouse(argv); // do not remove this

        printf("implement automated warehouse!\n");

        // test case robots
        robots = malloc(sizeof(struct robot) * 4);
        setRobot(&robots[0], "R1", 5, 5, 0, 0);
        setRobot(&robots[1], "R2", 0, 2, 0, 0);
        setRobot(&robots[2], "R3", 1, 1, 1, 1);
        setRobot(&robots[3], "R4", 5, 5, 0, 0);

        /*
        real case robots
        */
        int robot_num = to_number(argv[1]);
        if(robot_num == -1) {
            printf("Error: Invalid robot num(argv[1])");
            return;
        }

        // example of create thread
        tid_t* threads = malloc(sizeof(tid_t) * 4);
        int idxs[4] = {1, 2, 3, 4};
        threads[0] = thread_create("CNT", 0, &test_cnt, NULL);
        threads[1] = thread_create("R1", 0, &test_thread, &idxs[1]);
        threads[2] = thread_create("R2", 0, &test_thread, &idxs[2]);
        threads[3] = thread_create("R3", 0, &test_thread, &idxs[3]);

        // if you want, you can use main thread as a central control node
        
}