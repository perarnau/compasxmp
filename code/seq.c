int a[10];

int main(int argc, char *argv[])
{
	int i;
	
	for(i = 0; i < 10; i++)
		a[i] = (i+1)*2;

	for(i = 0; i < 10; i++)
		printf("%d ",a[i]);
	printf("\n");

	return 0;
}
