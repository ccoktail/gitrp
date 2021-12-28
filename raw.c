#include"socket.h"
#include<sys/ioctl.h>
#include<net/ethernet.h>
#include<linux/if_ether.h>
#include<linux/if_packet.h>
#include<linux/if_arp.h>
void dump_mac(const char* header,char* buf,int start)
{
	printf("%s",header);
	int i;
	for(i=start;i<6+start;++i)
	{
		//以两位显示
		printf("%02x:",(int)(unsigned char)buf[i]);
	}
	printf("\n");
	
}

unsigned short get_type(char* buf)
{
	unsigned short type=*(unsigned short*)(buf+12);
	//printf("type:%04x\n",type);
	return ntohs(type);
}

unsigned char get_ptype(unsigned char* ip)
{
	return ip[9];
}

unsigned char* get_ip_start(char* buf)
{
	return buf+14;	
}


unsigned char* get_tcp_start(unsigned char* ip)
{
	int hlen=(ip[0] & 0xf)*4;
	//printf("hlen=%d\n",hlen);//20
	return ip+hlen;
}

unsigned char* get_tcp_data(unsigned char* tcp)
{
	int hlen=((tcp[12] & 0xf0)>>4)*4;
	return tcp+hlen;
}

void handle(char* buf,int length)
{
	unsigned short type=get_type(buf);
	if(type != 0x0800)
	{
		return ;
	}
	unsigned char* ip=get_ip_start(buf);
	unsigned char ptype=get_ptype(ip);
	if((int)ptype==17)
		return;
	unsigned char* tcp=get_tcp_start(ip);
	unsigned char* tcp_data=get_tcp_data(tcp);
	printf("%s\n\n",(char*)tcp_data);
	//tcp--->6 ,  udp-->17
	//printf("protocol type is %d\n",(int)ptype);
	//dump_mac("dst:",buf,0);
	//dump_mac("src:",buf,6);
	//printf("-----------------------\n");
}

int main()
{
	int sock=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
	if(sock<0)
	{
	
		perror("socket");
		return 0;
	}
	struct ifreq ifstruct;
	strcpy(ifstruct.ifr_name,"eth0");

	ioctl(sock,SIOCGIFINDEX,&ifstruct);
	ioctl(sock,SIOCGIFHWADDR,&ifstruct);
	ioctl(sock,SIOCGIFFLAGS,&ifstruct);

	ifstruct.ifr_flags |= IFF_PROMISC;
	ioctl(sock,SIOCSIFFLAGS,&ifstruct);

	struct sockaddr_ll sll;
	sll.sll_family=AF_PACKET;
	sll.sll_ifindex=ifstruct.ifr_ifindex;
	sll.sll_protocol=htons(ETH_P_ALL);
	sll.sll_hatype=ARPHRD_ETHER;
	sll.sll_pkttype=PACKET_OTHERHOST;
	sll.sll_halen=ETH_ALEN;
	sll.sll_addr[6]=0;
	sll.sll_addr[7]=0;
	bind(sock,(struct sockaddr*)&sll,sizeof(struct sockaddr_ll));

	char buf[1514];
	while(1)
	{
		//buf==以太帧数据
		int ret=read(sock,buf,sizeof(buf));
		if(ret<0)
		{
		
			perror("read");
			return 0;
		}
		//printf("ret is %d\n",ret);
		handle(buf,ret);
	}
	return 0;
}
