#include"socket.h"


int main()
{

	int fd[2];
	if(socketpair(AF_UNIX,SOCK_STREAM,0,fd))
	{
		perror("sockerpair");
	}
	pid_t pid=fork();
	if(pid>0)
	{
		char buf[1024];
		read(fd[0],buf,sizeof(buf));
		printf("父进程%s\n",buf);
		return 0;
	}
	write(fd[1],"hello",6);
}
