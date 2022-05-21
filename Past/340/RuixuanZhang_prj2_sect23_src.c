// Ruixuan Zhang
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sched.h>
#include <assert.h>

// max length of a line
#define MAX_LINE_LENGTH 256

// max buffer length
#define MAX_BUFFER_SIZE 100

// size of 1st buffer
#define BUFFER1_SIZE 10

// size of 2nd buffer
#define BUFFER2_SIZE 20

// this token indicate the end of thread 1
// it is put into array queue, 
// when received, thread 2 konw that thread 1 is end.
#define THREAD_1_END_FLAG "**END**"


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////      Utils functiuon  ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// print str into console, replace printf
void myprintf(const char * str)
{
    int i;
    for (i = 0; str[i]; i++)
    {
        write(STDOUT_FILENO, str + i, 1);
    }
}

// convert integer into string, replace `sprintf`, `itoa`
void int2string(int n, char * str)
{
    // n is zero
    if (n == 0)
    {
        strcpy(str, "0");
        return;
    }

    // n is non-zero, split the digits
    char digits[20];
    int i, idx = 0;
    while (n > 0)
    {
        digits[idx] = n % 10;
        idx++;
        n /= 10;
    }

    // convert digits into string
    for (i = 0; i < idx; i++)
    {
        str[i] = digits[idx - 1 - i] + '0';
    }
    str[idx] = 0;
}

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////    Buffer Array ADT   ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// buffer array structure
struct buffered_array_t
{
    char * lines[MAX_BUFFER_SIZE];
    int in;
    int out;
    int size;   // size of the buffer, 10 or 20
};

// create a buffer with certain size
struct buffered_array_t * buffer_create(int size)
{
    struct buffered_array_t * buffer;
    buffer = (struct buffered_array_t *)malloc(sizeof(struct buffered_array_t));
    assert(buffer);
    buffer->in = 0;
    buffer->out = 0;
    buffer->size = size;
    return buffer;
}

// destroy the buffer
void buffer_destroy(struct buffered_array_t * buffer)
{
    free(buffer);
}

// check that buffer is full
int buffer_full(struct buffered_array_t * buffer)
{
    return (buffer->in + 1) % buffer->size == buffer->out;
}

// check that buffer is empty
int buffer_empty(struct buffered_array_t * buffer)
{
    return buffer->in == buffer->out;
}

// add element into buffer
void buffer_enqueue(struct buffered_array_t * buffer, char * data)
{
    buffer->lines[buffer->in] = data;
    buffer->in = (buffer->in + 1) % buffer->size;
}

// remove element from buffer
char * buffer_dequeue(struct buffered_array_t * buffer)
{
    char * ret = buffer->lines[buffer->out];
    buffer->out = (buffer->out + 1) % buffer->size;
    return ret;
}


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////    GLOBAL VARIABLE    ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// file descripter
int g_fd;

// 2 buffer array
struct buffered_array_t * buffer1;
struct buffered_array_t * buffer2;


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////     WORKING THREAD 1  ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// read next line from file, replace of `fgets`
char * read_next_line()
{
    char c;
    int ret;
    char line[MAX_LINE_LENGTH];
    int i = 0;
    while (1)
    {
        // read a char from file
        ret = read(g_fd, &c, 1);
        if (ret != 1)
        {
            // arrive at eof
            break;
        }
        if (c == '\r')
        {
            // ignore it
            continue;
        }
        if (c == '\n')
        {
            break;
        }

        line[i] = c;
        i++;
    }
    line[i] = 0;

    if (ret != 1 && i == 0)
    {
        // nothing is read from file, and we do not read any letter 
        // it means we arrive at the end of the file
        return NULL;
    }

    // make a copy of string
    return strdup(line);
}

// working function of thread 1
void * work1(void * pArg)
{
    int again = 1;
    while (again)
    {
        // read a line from file
        char * line = read_next_line();
        if (line == NULL)
        {
            // arrive at eof, send signal: THREAD_1_END_FLAG, indicate the end of file
            again = 0;
            line = strdup(THREAD_1_END_FLAG);
        }

        // wait until buffer1 is NOT full
        while (buffer_full(buffer1))
        {
            sched_yield();
        }

        // put the line into queue
        buffer_enqueue(buffer1, line);
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////     WORKING THREAD 2  ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// remove the non-alpha non-digit letter
void clean_line(char * line)
{
    int i;
    for (i = 0; line[i]; i++)
    {
        if ((line[i] == ' ') ||
            !(('0' <= line[i] && line[i] <= '9')
                || ('A' <= line[i] && line[i] <= 'Z')
                || ('a' <= line[i] && line[i] <= 'z')))
        {
            line[i] = ' ';
        }
    }
}

// working function of thread 2
void * work2(void * pArg)
{
    int line_counter = 0;
    char buf1[MAX_LINE_LENGTH];
    char buf2[MAX_LINE_LENGTH];
    int again = 1;
    while (again)
    {
        // wait until buffer1 is NOT empty
        while (buffer_empty(buffer1))
        {
            sched_yield();
        }

        // pick a line
        char * line = buffer_dequeue(buffer1);
        if (strcmp(line, THREAD_1_END_FLAG) == 0)
        {
            // (1) thread 1 is end
            again = 0;

            // pass the `line_counter` to thread 3
            strcpy(buf1, "*LINE COUNT = ");
            int2string(line_counter, buf2);
            strcat(buf1, buf2);
            strcat(buf1, "*");

            // wait until buffer2 is NOT full
            while (buffer_full(buffer2))
            {
                sched_yield();
            }

            // put this flag into queue
            buffer_enqueue(buffer2, strdup(buf1));
        }
        else
        {
            // (2) thread 1 is NOT end
            clean_line(line);

            // split the token
            char *  p = strtok(line, " ");
            while (p)
            {
                while (buffer_full(buffer2))
                {
                    sched_yield();
                }

                // add the word into queue
                buffer_enqueue(buffer2, strdup(p));
                p = strtok(NULL, " ");
            }
        }
        free(line);

        // increase line count
        line_counter++;
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////     WORKING THREAD 3  ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// working function of thread 3
void * work3(void * pArg)
{
    int word_counter = 0;
    char buf1[MAX_LINE_LENGTH];
    char buf2[MAX_LINE_LENGTH];

    int again = 1;
    while (again)
    {
        // wait until buffer1 is NOT empty
        while (buffer_empty(buffer2))
        {
            sched_yield();
        }

        // pick a string from queue
        char * line = buffer_dequeue(buffer2);

        // this the `line_counter` from thread 2
        if (strncmp(line, "*LINE COUNT = ", 10) == 0)
        {
            again = 0;

            // put it to console
            myprintf(line);
            myprintf("\n");
        }
        else
        {
            // put the word into console
            myprintf("*");
            myprintf(line);
            myprintf("*");
            myprintf("\n");
            word_counter++;
        }
        free(line);
        // sleep(1);
    }

    // display word count
    strcpy(buf1, "*WORD COUNT = ");
    int2string(word_counter, buf2);
    strcat(buf1, buf2);
    strcat(buf1, "*");
    myprintf(buf1);
    myprintf("\n");
    return NULL;
}

int main(int argc, char *argv[])
{
    const char * filename;

    assert(argc == 2);
    filename = argv[1];

    // 3 thread id
    pthread_t pthread1;
    pthread_t pthread2;
    pthread_t pthread3;

    // open file, create buffer
    g_fd = open(filename, O_RDONLY);
    buffer1 = buffer_create(BUFFER1_SIZE);
    buffer2 = buffer_create(BUFFER2_SIZE);

    // create 3 thread
    pthread_create(&pthread1, NULL, work1, NULL);
    pthread_create(&pthread2, NULL, work2, NULL);
    pthread_create(&pthread3, NULL, work3, NULL);

    // wait 3 thread
    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
    pthread_join(pthread3, NULL);

    // free resource
    close(g_fd);
    buffer_destroy(buffer1);
    buffer_destroy(buffer2);
    return 0;
}


