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
	int epollfd1=epoll_create(512);
	epoll_add(epollfd,server,EPOLLIN);
	epoll_add(epollfd,epollfd1,EPOLLIN);	
	struct epoll_event ev_out[8];
	while(1)
	{
		int ret=epoll_wait(epollfd,ev_out,8,2000);
		if(ret>0)
		{
			int i;
			int fd=ev_out[i].data.fd;
			if(fd==server)
			{
				int newfd=accept(fd,NULL,NULL);
				epoll_add(epollfd1,newfd,EPOLLIN);
			}
			else
			{
				struct epoll_event ev_out1[8];
				int ret1=epoll_wait(epollfd1,ev_out1,8,0);
				if(ret1>0)
				{
					int j;
					for(j=0;j<ret1;++i)
					{
						int fd1=ev_out1[j].data.fd;
						char buf[1024];
						int r=read(fd1,buf,sizeof(buf));
						if(r>0)
						{
							printf("%s\n",buf);
						}
						else
						{
							close(fd1);
						}

					}
				}

			}
		}
	}
}
