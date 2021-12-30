#include"socket.h"


int main()
{
	int fd=create_server(9989,"127.0.0.1",10);
	if(fd<0)
	{
		perror("create server");
	}
	struct sockaddr_in addr;
	socklen_t len;
	while(1)

	{int newfd=accept(fd,(struct sockaddr*)&addr,&len);
		if(newfd<0)
		{
			perror("accept");
		}
		char buf[1024];
		read(newfd,buf,sizeof(buf));
		printf("read ok\n");
		printf("data is %s\n",buf);
		printf("ip is %s\n",(unsigned char* )inet_ntoa(addr.sin_addr));
		printf("port is %d\n",ntohs(addr.sin_port));
	}
}
