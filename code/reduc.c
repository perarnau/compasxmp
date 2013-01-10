#pragma xmp nodes p(2)
#pragma xmp template t(0:9)
#pragma xmp distribute t(block) onto p
int a[10];
#pragma xmp align a[i] with t(i)


double asum(int n, double a0)
{
	int i;
	double asum;
	asum = a0;
	#pragma xmp loop on t(i) reduction(+:asum)
	for(i = 0; i < 10; i++)
		asum += asum + a[i];
	return asum;
}

int main(int argc, char *argv[])
{
	int i;
	double s;

	#pragma xmp loop on t(i)
	for(i = 0; i < 10; i++)
		a[i] = i;

	s = asum(10,0.0);

	#pragma xmp task on p(1)
	printf("sum: %f\n",s);
	return 0;
}
