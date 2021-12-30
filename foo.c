

int foo(int n)
{
	if(n==1)
		return 1;
	else
		return n+foo(n-1);
}

int main()
{
	printf("%d\n",foo(100));
}
