/**
 * 处理SIGCHLD信号,为免留下僵死进程应使用waitpid函数,而不是wait.
 */
#include "echo.h"

void sig_chld_bad(int signo){
    pid_t pid;
    int stat;

    pid = wait(&stat);
    printf("child %d terminated\n", pid);
    return;
}

void sig_chld(int signo){
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0){
        printf("child %d terminated\n", pid);
    }
    return;
}
