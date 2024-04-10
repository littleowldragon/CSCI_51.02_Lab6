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
        int repetition = 0;
        while (true)
        {
                        auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            std:tm localtime = *std::localtime(&time);

            std::cout << std::put_time(&localtime, "[%Y-%m-%d] %T") << std::endl;
            repetition++;
            if(repetition == 3) {
                std::cout << "\"This program has gone on for far too long. Type Ctrl+C to abort this timer application.\"" << std::endl;
                repetition = 0;

            sleep(10);
        }
    }

    return 0;
}