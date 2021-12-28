


#include"socket.h"


int main()
{

	int fd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9988);
	addr.sin_addr.s_addr=INADDR_ANY;
	
	bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	char buf[1024];
#if 0	
	struct sockaddr_in baddr;
	baddr.sin_family=AF_INET;
	baddr.sin_port=htons(10011);
	baddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	sendto(fd,"i am client",12,0,(struct sockaddr*)&baddr,sizeof(baddr));
	
	recv(fd,buf,sizeof(buf),0);
	printf("%s\n",buf);
#endif	
	struct sockaddr peer_addr;
	socklen_t addr_len=sizeof(peer_addr);
	recvfrom(fd,buf,sizeof(buf),0,&peer_addr,&addr_len);
	printf("%s\n",buf);
	sendto(fd,"heiheihei",10,0,&peer_addr,addr_len);
}

