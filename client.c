#include"socket.h"


int main()
{
	int fd=connect_server("127.0.0.1",9988);
	if(fd<0)
	{
		perror("connect");
		return -1;
	}
	write(fd,"heihei",7);
	char buf[1024];
	read(fd,buf,sizeof(buf));
	printf("%s\n",buf);
	return 0;
}
