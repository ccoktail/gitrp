#include"socket.h"

int main()
{

	int fd=connect_server("127.0.0.1",9989);
	if(fd<0)
	{
		perror("connect");
	}
	write(fd,"hello",6);

}
