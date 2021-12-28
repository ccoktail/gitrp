

#include"socket.h"


int main()
{

	int server_fd=create_server(9988,"0.0.0.0",250);
	if(server_fd<0)
	{
		return -1;
	}
	int newfd=doAccept(server_fd,NULL,NULL);
	if(newfd<0)
		return -2;{
	}
	while(1)
	{
		int filenamelen;
		int ret=doRecv(newfd,(char*)&filenamelen,4);
		if(ret!=4)
		{
			printf("doRecv\n");
			return -3;
		}
		char* filename=malloc(filenamelen);
		ret=doRecv(newfd,filename,filenamelen);

		int fdout=open(filename,O_WRONLY|O_TRUNC);
		if(fdout<0)
		{
			fdout=open(filename,O_WRONLY|O_CREAT,0777);
			if(fdout<0)
			{
				printf("errno openfile");
				return -4;
			}
		}
		free(filename);
		int filelen;
		ret=doRecv(newfd,(char*)&filelen,4);
		char buf[4096];
		while(filelen>0)
		{
			ret=read(newfd,buf,sizeof(buf));
			if(ret>0)
			{
				filelen -= ret;
				write(fdout,buf,ret);
			}
			else if(ret==0)
			{
				break;
			}
			else if(ret<0)
			{
				if(errno==EINTR);
					continue;
					break;
			}
			close(fdout);
		}


		
	}



