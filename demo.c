#include <stdio.h>
#include <stdlib.h>


typedef struct
{
	char measurement[8];
	float meter;
}CONVRULE;
typedef struct
{
	char str[40];
	int lineNumber;
}BUF;

int main()
{
	FILE *fp;
	CONVRULE convRules[6];
	BUF buf[17];

	int i = 0;

	if((fp = fopen("input.txt", "r")) == NULL)
	{
		printf("could not open file");
		return 0;
	}

	///读取到buf
	while (!feof(fp))
	{
		fgets(buf[i].str, 128, fp);
		i++;
		buf[i].lineNumber = i;
		//printf("%d\t", buf[i].lineNumber);
		//puts(buf[i-1].str);
	}

	///解析转换规则
	int j;
	char tmp[10];
	for(j=0; j<6; j++)
	{
		sscanf(buf[j].str, "%*s %[^=]", &convRules[j].measurement);
		sscanf(buf[j].str, "%*[^=]=%[^m]", &tmp);
		convRules[j].meter = atof(tmp);

		//puts(convRules[j].measurement);
		//puts(tmp);
		//printf("\t%f\n",convRules[j].meter);
	}



	fclose(fp);
	return 0;


}
