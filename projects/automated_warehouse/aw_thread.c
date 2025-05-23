#include "projects/automated_warehouse/aw_thread.h"

//
// You need to read carefully threads/synch.h and threads/synch.c
//
// In the code, a fucntion named "sema_down" implements blocking thread and
// makes list of blocking thread
//
// And a function named "sema_up" implements unblocing thread using blocking list
//
// You must implement blocking list using "blocking_threads" in this code.
// Then you can also implement unblocking thread.
//

struct list blocked_threads;

/**
 * A function unblocking all blocked threads in "blocked_threads"
 * It must be called by robot threads
 * Block the current thread and add it to the blocked threads
 */
void block_thread()
{
    enum intr_level old_level;

    ASSERT(!intr_context());

    old_level = intr_disable();
    list_push_back(&blocked_threads, &thread_current()->elem);
    thread_block();
    intr_set_level(old_level);
}

/**
 * A function unblocking all blocked threads in "blocked_threads"
 * It must be called by central control thread
 * Unblock all the blocked thread in "blocked_threads"
 */
void unblock_threads()
{
    struct list_elem *e;

    e = list_begin(&blocked_threads);
    while (e != list_end(&blocked_threads))
    {
        struct list_elem *next = list_next(e);
        struct thread *t = list_entry(e, struct thread, elem);
        thread_unblock(t);
        e = next;
    }
    // 모든 thread unblock 이후 list 초기화
    list_init(&blocked_threads);
}