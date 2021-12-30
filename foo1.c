


#include<stdio.h>
#include<stdlib.h>

void foo2(int num)
{
	if(num==0)
		return ;
	foo2(num/2);
	printf("%d",num%2);
	return;
}

int dec2bin(int n)
{
	int sum;
	if(n==1)
	{
		return 1;
	}
	else
	{
		if(n==0)
		{
			return 0;
		}
		sum=dec2bin(n/2)*10+n%2;
	}
	return sum;
}


int main(int argc,char* argv[])
{
	int n=atoi(argv[1]);
	//foo2(n);
	int ret=dec2bin(n);
	printf("%d\n",ret);
	return 0;
}
