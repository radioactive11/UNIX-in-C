#include <stdio.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    // fd -> file descriptor
    int fd[2];

    // fd[0] is read and fd[1] is write

    if(pipe(fd) == -1)
    {
        printf("An error occourred while opening the pipe");
        return 1;
    }

    int id = fork();
    if(id == 0) // child
    {
        close(fd[0]);
        int x;
        printf("Enter a number: ");
        scanf("%d", &x);
        printf("\n");
        write(fd[1], &x, sizeof(int));
        close(fd[1]);

    }
    
    else // parent
    {
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        printf("Data from child proc is: %d \n", y);
        close(fd[0]);
    }

    return 0;
}
