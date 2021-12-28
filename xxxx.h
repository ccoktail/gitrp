#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/stat.h>

#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

static void setnonblock(int fd)
{
	uint32_t flags=fcntl(fd,F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(fd,F_SETFL,&flags);	
}

static int connect_server(const char* ip,unsigned short port)
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);
	int ret=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret<0)
	{
		close(fd);
		return -1;
	}
	return fd;

}


static int create_server(const char* ip,unsigned short port,int backlog)
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd<0)
	{
		perror("socket");
		return fd;
	}
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	add.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);

	int ret=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret<0)
	{
		perror("bind");
		return -2;
	}
	listen(fd,backlog);
	return fd;
}


static int doAccept(int fd,struct sockaddr* addr,socklen_t addrlen)
{
	while(1)
	{
		int newfd=accept(fd,addr,addrlen);
		if(newfd<0 && errno==EINTR)
		{
			continue;
		}
		
		return newfd;
	}
	return -1;
}


static int doRecv(int fd,char* buf,int size)
{
	int alreadyread=0;
	while(size>0)
	{
		int ret=read(fd,buf+alreadyread,size);
		if(ret>0)
		{
			size-=ret;
			alreadyread+=ret;
		}
		else if(ret==0)
			break;
		else if(ret<0)
		{
			if(errno==EINTR)
				continue;
			break;
		}
	}
	return alreadyread;
}


int doSend(int fd,const char* buf,int size)
{
	int alreadysend=0;
	while(size>0)
	{
		int ret=write(fd,buf+alreadysend,size);
		if(ret<0)
		{
			alreadysend+=ret;
			size-=ret;
		}
		else 
		{
			if(errno==EINTR)
				continue;
			break;
		}
	}
	return alreadysend;
}












