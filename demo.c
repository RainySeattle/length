#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
float calc(char *str, int lineNum);

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
		buf[i-1].lineNumber = i;
		printf("%d\t", buf[i-1].lineNumber);
		puts(buf[i-1].str);
	}

	///解析转换规则
	int j;
	char tmp[10];
	for(j=0; j<6; j++)
	{
		sscanf(buf[j].str, "%*s %[^=]", &convRules[j].measurement);
		convRules[j].measurement[3] = '\0';  //截取单位前三个字符，英文单词规避复数问题
		sscanf(buf[j].str, "%*[^=]=%[^m]", &tmp);
		convRules[j].meter = atof(tmp);

		puts(convRules[j].measurement);
		//puts(tmp);
		printf("\t%f\n",convRules[j].meter);
	}





	float calc(char *str, int lineNum)
	{
		float result;
		int i;
		if (lineNum >=8 && lineNum <= 13)
		{
			float num;
			char sNum[10];
			char meas[10];
			sscanf(str, "%[^ ]", &sNum);
			sscanf(str, "%*s %s", &meas);
			meas[3] = '\0';  //截取单位前三个字符，英文单词规避复数问题
			num = atof(sNum);
			for (i=0; i<6; i++)
			{
				if (strcmp(convRules[i].measurement, meas) == 0)
				{
					puts(convRules[i].measurement); //test
					result = num * convRules[i].meter;
				}

			}

			//printf("\n\n%f", num); //test
			//puts(meas); //test
		}


		return result;

	}

	printf("\n\n\n%.2f m\n\n", calc(buf[7].str, buf[7].lineNumber));


	fclose(fp);
	return 0;


}



