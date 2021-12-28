


#include"socket.h"

int main(int argc,char* argv[])
{
	int fd=connect_server("127.0.0.1",9988);
	const char* srcfile=argv[1];
	const char* dstfile=argv[2];

	int len=strlen(dstfile)+1;
	doSend(fd,(const char* )&len,4);
	doSend(fd,(const char*)dstfile,len);

	struct stat statbuf;
	stat(srcfile,&statbuf);
	len=statbuf.st_size;
	doSend(fd,(const char*)&len,4);

	int fdin=open(srcfile,O_RDONLY);
	char buf[4096];
	while(len>0)
	{
		int ret=read(fdin,buf,sizeof(buf));
		if(ret<=0)
			break;
		doSend(fd,buf,ret);
		len -=ret;
	}
	close(fdin);
	close(fd);
}

