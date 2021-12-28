#include"socket.h"
#include<list>
using namespace std;


int main()
{
	int server=create_server(9988,"0.0.0.0",250);
	int maxfd=server;
	list<int> clients;
	
	while(1)
	{
		fd_set set;
		struct timeval tv;
		tv.tv_sec=2;
		tv.tv_usec=0;
		
		maxfd=server;
		FD_ZERO(&set);
		FD_SET(server,&set);

		for(auto it=clients.begin();it!=clients.end();++it)
		{
			FD_SET(*it,&set);
			if(*it>maxfd)maxfd=*it;

		}
		int ret=select(maxfd+1,&set,NULL,NULL,&tv);
		if(ret>0)
		{
			if(FD_ISSET(server,&set))
			{
			
				int newfd=doAccept(server,NULL,NULL);
				clients.push_back(newfd);
			}
		}
		for(auto it=clients.begin();it!=clients.end();)
		{
		
			int newfd=*it;
			if(FD_ISSET(newfd,&set))
			{
				char buf[1024];
				ret=read(newfd,buf,sizeof(buf));
				if(ret>0)
				{
					printf("%s\n",buf);
					write(newfd,"zuoshen?",9);
				}
				else if(ret<0 && errno==EINTR)
				{
					//
				}
				else
				{
					close(newfd);
					it=clients.erase(it);
					continue;
				}
			}
			++it;
		}
	
	}


}
