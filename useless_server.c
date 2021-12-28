#include"socket.h"


int main()
{
	int fd=create_server(9988,"0.0.0.0",250);
	if(fd<0)
	{
		return 1;
	}
	int newfd=doAccept(fd,NULL,NULL);


	char buf[4096];
	
	int ret=doRecv(newfd,buf,16);

	char bufAck[]="ok";
	ret=doSend(newfd,bufAck,sizeof(bufAck));
}
