#pragma xmp nodes p(4)

#pragma xmp template tb(0:19)
#pragma xmp distribute tb(block) onto p
int b[20];
#pragma xmp align b[i] with tb(i)

#pragma xmp template tc(0:19)
#pragma xmp distribute tc(cyclic) onto p
int c[20];
#pragma xmp align c[i] with tc(i)

#pragma xmp template tbc(0:19)
#pragma xmp distribute tbc(cyclic(2)) onto p

// gblock not implemented

int main(int argc, char *argv[])
{
	int i;
	int id = xmp_node_num();
	int res[20];

	#pragma xmp loop on tb(i)
	for(i = 0; i < 20; i++)
		b[i] = id;
	
	#pragma xmp loop on tc(i)
	for(i = 0; i < 20; i++)
		c[i] = id;

	#pragma xmp gmove
	res[:] = b[:];

	#pragma xmp task on p(1)
	{
		printf("Block distribution\n");
		for(i = 0; i < 20; i++)
			printf("%d ",res[i]);
		printf("\n");
	}
	
	#pragma xmp gmove
	res[:] = c[:];

	#pragma xmp task on p(1)
	{
		printf("Cyclic distribution\n");
		for(i = 0; i < 20; i++)
			printf("%d ",res[i]);
		printf("\n");
	}
/*
 *	BUG in GMOVE implem right now...
	#pragma xmp gmove
	res[:] = bc[:];

		
	#pragma xmp task on p(1)
	{
		printf("Block Cyclic (2) distribution\n");
		for(i = 0; i < 20; i++)
			printf("%d ",res[i]);
		printf("\n");
	}
*/
	#pragma xmp task on p(1)
	printf("Block Cyclic (2) distribution\n");

	char str[80],buf[80];
	snprintf(str,80,"%d:",id);	
	
	for(i = 0; i < 20; i++)
	{
		#pragma xmp task on tbc(i)
		{
			snprintf(buf,80," %d",i);
			strncat(str,buf,80);
		}
	}
	printf("%s\n",str);


	return 0;
}
