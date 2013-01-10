#pragma xmp nodes p(2)
#pragma xmp template t(0:9)
#pragma xmp distribute t(block) onto p
int a[10];
#pragma xmp align a[i] with t(i)

int main(int argc, char *argv[])
{
	int i;

	#pragma xmp loop on t(i)
	for(i = 0; i < 10; i++)
		a[i] = (i+1)*2;

	#pragma xmp loop on t(i)
	for(i = 0; i < 10; i++)
	{
		#pragma xmp task on p(1)
		printf("%d ",a[i]);
	}
	
	#pragma xmp task on p(1)
	printf("\n");
	
	return 0;
}
