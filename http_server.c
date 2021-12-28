

#include"socket.h"

int main()
{
	int fd=create_server(8080,"0.0.0.0",250);


	int newfd=accept(fd,NULL,NULL);
	char buf[4096];
	if(newfd>0)
	{
		read(newfd,buf,sizeof(buf));
		printf("%s\n",buf);
	}
}
