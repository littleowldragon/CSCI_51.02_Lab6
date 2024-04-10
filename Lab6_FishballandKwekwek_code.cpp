#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctime>
#include <cstdio>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "Failed to fork process." << std::endl;
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        execl("/usr/bin/xclock", "myXclock", NULL);
    }
    else
    {
        // Parent process
        int count = 0;
        while (true)
        {
            time_t now = time(0);
            tm *local_time = localtime(&now);
            char time_str[100];
            strftime(time_str, sizeof(time_str), "[%Y-%m-%d] %H:%M:%S", local_time);
            std::cout << time_str << std::endl;

            if (++count % 3 == 0)
            {
                std::cout << "\"This program has gone on for far too long. Type Ctrl+C to abort this timer application.\"" << std::endl;
            }

            sleep(10);
        }
    }

    return 0;
}