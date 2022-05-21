// name: Ruixuan Zhang
// how to compile:
// gcc *.c -o proj1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// size of the chunk
#define SIZE (128)

// process working function
void parent_work(const char * input_filename, int pipe_fd)
{
    // input_filename = "g.txt";
    int fd = open(input_filename, O_RDONLY);
    if (fd == -1)
    {
        printf("[ERROR] cannot read file %s!\n", input_filename);
        return;
    }

    int num_read, num_write;
    char buf[SIZE];
    
    while (1)
    {
        // read the 128 trunk
        num_read = read(fd, buf, SIZE);
        if (num_read <= 0)
        {
            break;
        }
        num_write = write(pipe_fd, buf, num_read);
        assert(num_write == num_read);
    }

    close(fd);
}

// process working function
void child_work(const char * output_filename, int pipe_fd)
{
    int fd = open(output_filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("[ERROR] cannot create %s!\n", output_filename);
        return;
    }

    char buf[SIZE];
    int num_read;
    while (1)
    {
        // read the contents of the pipe in 128-character chunks
        num_read = read(pipe_fd, buf, SIZE);
        if (num_read == 0)
        {
            break;
        }
        write(fd, buf, num_read);
        write(1, buf, num_read);
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int fd_pipe[2];
    const char * input_filename;
    const char * output_filename;

    if (argc != 3)
    {
        printf("Usage: ./proj1 [source_file_name] [target_file_name]\n");
        return 0;
    }

    // get source file name and target file name
    input_filename = argv[1];
    output_filename = argv[2];

    // create pipe
    pipe(fd_pipe);

    // create process
    pid = fork();

    assert(pid != -1);
    if (pid > 0)
    {
        // parent
        close(fd_pipe[0]);
        parent_work(input_filename, fd_pipe[1]);
        close(fd_pipe[1]);
        waitpid(pid, NULL, 0);
    }
    else
    {
        // child
        close(fd_pipe[1]);
        child_work(output_filename, fd_pipe[0]);
        close(fd_pipe[0]);
    }

    return 0;
}


