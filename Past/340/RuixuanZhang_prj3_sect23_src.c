// Ruixuan Zhang
// gcc RZhang_prj3_sect23_src.c -lpthread -o RZhang_prj3_sect23_src

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

// The stack array size is 20
#define SIZE 20
#define POP_ORDER_SIZE 120

// represent a stack
struct Stack
{
    pthread_mutex_t lock;
    int data[SIZE];
    int top;
}stack;

// this global structure is used to pass data from thread back to main
struct global_t
{
    // represent whether all the number 1-120 have been pushed to stack
    bool pushFininsh;

    // Used by pthread 1
    // hold a running sum of the integers pushed on to the stack
    int pushSum;

    // Used by pthread 2
    // compute a running sum of integers popped from the stack
    int popSum;

    // 120-element array (popOrder) 
    // to record the order in which integers were popped from the stack
    int popOrder[POP_ORDER_SIZE];
    int idx;

}g;

// check that stack is empty
bool is_empty()
{
    bool ret;
    pthread_mutex_lock(&stack.lock);
    if (stack.top == 0)
        ret = true;
    else
        ret = false;
    pthread_mutex_unlock(&stack.lock);
    return ret;
}

// check that stack is full
int is_full()
{
    bool ret;
    pthread_mutex_lock(&stack.lock);
    if (stack.top == SIZE)
        ret = true;
    else
        ret = false;
    pthread_mutex_unlock(&stack.lock);
    return ret;
}

// push data into stack
// @return true if success; otherwise, false
bool push(int item)
{
    bool ret;
    pthread_mutex_lock(&stack.lock);
    if (!is_full())
    {
        stack.data[stack.top] = item;
        stack.top++;
        ret = true;
    }
    else
    {
        // stack is full
        sched_yield();
        ret = false;
    }
    pthread_mutex_unlock(&stack.lock);
    return ret;
}

// pop data from stack
// @return true if success; otherwise, false
bool pop(int* elem)
{
    int ret;
    pthread_mutex_lock(&stack.lock);
    if (!is_empty())
    {
        stack.top--;
        *elem = stack.data[stack.top];
        ret = true;
    }
    else
    {
        // stack is empty
        sched_yield();
        ret = false;
    }
    pthread_mutex_unlock(&stack.lock);
    return ret;
}

// Pthread 1 will push all integers from 1 to 120 on to the stack
void* thread_work1(void* varg)
{
    g.pushSum = 0;

    // pushes the integer numbers from 1 to 120
    int i = 0;
    while (i < 120)
    {
        // repeat push `i+1` until success
        while (!push(i + 1));
        g.pushSum += i + 1;

        // call sched_yield() after every 10 consecutive invocations
        if (i % 10 == 0)
        {
            sched_yield();
        }
        i++;
    }

    // set the finished flag
    g.pushFininsh = true;
    return NULL;
}

// pthread 2 pops the integers from the stack
void* thread_work2(void* varg)
{

    int i, elem;

    g.popSum = 0;
    g.idx = 0;

    // repeat until all the data has been push into stack, and the stack is empty
    while (!g.pushFininsh || !is_empty())
    {
        pthread_mutex_lock(&stack.lock);
        if (is_full())
        {
            // (1) If the stack is full, 
            // it will pop all integers from the stack and then call sched_yield()
            while (!is_empty())
            {
                while (!pop(&elem));
                g.popSum += elem;
                g.popOrder[g.idx++] = elem;
            }
            sched_yield();
        }
        else
        {
            // (2) If the stack is not full, 
            // it will pop just five integersand call sched_yield()
            // (3) If there are less than five integers on the stack, 
            // it will pop all of them and then call sched_yield()
            for (i = 0; i < 5 && !is_empty(); i++)
            {
                while (!pop(&elem));
                g.popSum += elem;
                g.popOrder[g.idx++] = elem;
            }
            sched_yield();
        }
        pthread_mutex_unlock(&stack.lock);

    }
    return NULL;
}

int main(int argc, char* argv[])
{
    int i;
    const char* filename;

    // get the command line parameter
    if (argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        printf("No input file specified!\n");
        return 0;
    }

    // clear the finished flag
    g.pushFininsh = false;

    // init the stack
    stack.top = 0;

    // set the lock re-enter by same thread
    pthread_mutexattr_t attribute;
    pthread_mutexattr_init(&attribute);
    pthread_mutexattr_settype(&attribute, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&stack.lock, &attribute);

    // create 2 thread
    pthread_t pid1, pid2;
    pthread_create(&pid1, NULL, thread_work1, NULL);
    pthread_create(&pid2, NULL, thread_work2, NULL);

    // wait until 2 thread finish
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    pthread_mutex_destroy(&stack.lock);

    // write the data into file
    FILE* output = fopen(filename, "w");
    // All 120 elements of Pthread 2 popOrder array
    for (i = 0; i < g.idx; i++)
    {
        fprintf(output, "%d ", g.popOrder[i]);
    }
    fprintf(output, "\n");

    // Value of Pthread 1 pushSum 
    fprintf(output, "%d\n", g.pushSum);

    // Value of Pthread 2 popSum
    fprintf(output, "%d\n", g.popSum);

    fclose(output);
    return 0;
}


