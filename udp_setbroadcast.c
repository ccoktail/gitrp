

#include"socket.h"

int main()
{	
	int fd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10011);
	addr.sin_addr.s_addr=INADDR_ANY;
	bind(fd,(struct sockaddr*)&addr,sizeof(addr));

	int optval=1;
	setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&optval,sizeof(optval));
	
	struct sockaddr_in baddr;
	baddr.sin_family=AF_INET;
	baddr.sin_port=htons(9988);
	baddr.sin_addr.s_addr=inet_addr("255.255.255.255");
	
	sendto(fd,"i am broadcast",15,0,(struct sockaddr*)&baddr,sizeof(baddr));
	printf("already send broadcast\n");
	//????
	
	char buf[1024];     
	recv(fd,buf,sizeof(buf),0);
	printf("%s\n",buf);
}
