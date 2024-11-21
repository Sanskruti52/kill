#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
pid_t child_pid;
void handle_sigchild(int sig)
{
	int status;
	pid_t pid=waitpid(child_pid,&status,WNOHANG);
	if(pid==child_pid)
	{
		printf("Child process terminated...\n");
		exit(0);
	}
}
void handle_alarm(int sig)
{
	printf("Time is up!Killing child process...");
	kill(child_pid,SIGKILL);
}
int main()
{
	signal(SIGCHLD,handle_sigchild);
	signal(SIGALRM,handle_alarm);
	child_pid=fork();
	if(child_pid<0)
	{
		printf("Fork is failed");
		exit(0);
	}
	if(child_pid==0)
	{
		execlp("sleep","sleep",3,NULL);
		printf("execlp is failed\n");
		exit(0);
	}
	else
	{
		alarm(5);
		printf("Parent:Waiting for child process to be finish...\n");
		while(1)
		{
			pause();
		}
	}
	return 0;
}
		
