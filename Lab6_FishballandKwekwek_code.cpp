#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <iomanip>
#include <chrono>
using namespace std;

int main (int argc, char* argv[]) {
    int repetition = 0;

    if(fork() == 0) {
        cout << "Child ID: " << getpid() << endl;

        if(execl("/usr/bin/xclock", "myXclock", NULL) == -1) {
            cout << "Error" << endl; //error
        }
    }
    else {
        while(true) {
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            std:tm localtime = *std::localtime(&time);

            std::cout << std::put_time(&localtime, "[%Y-%m-%d] %T") << std::endl;
            repetition++;
            if(repetition == 3) {
                std::cout << "\"This program has gone on for far too long. Type Ctrl+C to abort this timer application.\"" << std::endl;
                repetition = 0;
            }
            sleep(10);
        }
    }
    return 0;
}