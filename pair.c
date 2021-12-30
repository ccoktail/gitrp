#include"socket.h"

int main()
{
	int fd[2];
	int ret=socketpair(AF_UNIX,SOCK_STREAM,0,fd);
	if(ret<0)
	{
		perror("socketpair");
	}
	pid_t pid=fork();
	if(pid>0)
	{
		char buf[1024];
		read(fd[0],buf,sizeof(buf));
		printf("%s\n",buf);
		return 0;
	}
	write(fd[1],"hello",6);
}
