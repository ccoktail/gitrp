#include "socket.h"
#include<sys/epoll.h>
#include<sys/wait.h>

void epoll_add(int epollfd,int fd,int events)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=events;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
}

int main()
{
	int server=create_server(9988,"0.0.0.0",250);

	int epollfd=epoll_create(512);
	
	epoll_add(epollfd,server,EPOLLIN);
#if 0	
	struct epoll_event ev;
	ev.events=EPOLLIN;
	ev.data.fd=server;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,server,&ev);
#endif
	struct epoll_event ev_out[8];
	while(1)
	{
		int ret=epoll_wait(epollfd,ev_out,8,2000);
		if(ret>0)
		{
			int i;
			for(i=0;i<ret;++i)
			{
				int fd=ev_out[i].data.fd;
				if(fd==server)
				{
					int newfd=accept(fd,NULL,NULL);
					//ev.data.fd=newfd;;
					//epoll_ctl(epollfd,EPOLL_CTL_ADD,newfd,&ev);
					epoll_add(epollfd,newfd,EPOLLIN);
				}
				else
				{
					char buf[1024];
					int r=read(fd,buf,sizeof(buf));
					if(r>0)
					{
						printf("%s\n",buf);
					}
					else if(r<0 && errno==EINTR)
					{
					
					}
					else //r==0 || (r<0 && errno !=EINTR)
					{
						close(fd);
					}

				}
			}
		}
	}
}
