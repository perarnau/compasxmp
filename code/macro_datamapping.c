// utility stringyfication for xmp pragmas
#define S(x) #x
#define SX(x) S(x)
#define N 10

#pragma xmp nodes p(2)
_Pragma(SX(xmp template t(0:N-1)))
#pragma xmp distribute t(block) onto p
int a[N];
#pragma xmp align a[i] with t(i)

int main(int argc, char *argv[])
{
	int i;

	#pragma xmp loop on t(i)
	for(i = 0; i < N; i++)
		a[i] = (i+1)*2;

	#pragma xmp loop on t(i)
	for(i = 0; i < N; i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
