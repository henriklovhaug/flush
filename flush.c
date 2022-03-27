#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>


int change_directory(const char *pathname)
{
    int ret;
    ret = chdir(pathname);
    if (ret == -1)
    {
        perror("could not change directory");
        return -1;
    }
    return 0;
}

int execute_command(const char *command)
{
    int ret;
    ret = system(command);
    if (ret == -1)
    {
        perror("could not execute command");
        return -1;
    }
    return 0;
}

int parse_input(char * input)
{
    char *token;
    char * parsed_array[2048];

    int i = 0;
    token = strtok(input, " ");
    while (token != NULL)
    {
        parsed_array[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    parsed_array[i] = NULL;

    execvp(parsed_array[0], parsed_array);

    return 0;
}

int main()
{
    while (1)
    {
        // print current directory
        printf("%s: ", getcwd(NULL, 0));
        char buf[PATH_MAX];
        fgets(buf, sizeof(buf), stdin);

        if (strcmp(buf, "exit\n") == 0)
        {
            exit(0);
        }
        int kek = fork();
        if(kek == 0)
        {
            parse_input(buf);
        }
        else
        {
            wait(NULL);
        }
//         char cd_command[3] = {0};
//         strncpy(cd_command, buf, 2);
//         if(strcmp(cd_command, "cd") == 0)
//         {
//             char garbage[PATH_MAX];
//             char pathname[PATH_MAX];
//             sscanf(buf, "%s %s", garbage, pathname);
//             change_directory(pathname);
//         }
//         else
//         {
//             execute_command(buf);
//         }
    }
}
