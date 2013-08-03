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
	for(j=0; j<6; j++)
	{
		sscanf(buf[j].str, "%*f %s %*c %f %*c", convRules[j].measurement, &convRules[j].meter);
		convRules[j].measurement[3] = '\0';  //截取单位前三个字符，规避英文单词复数问题

		puts(convRules[j].measurement);
		//puts(tmp);
		printf("\t%f\n",convRules[j].meter);
	}





	float calc(char *str, int lineNum)
	{
		float result;

		//////////////////////
		if (lineNum >=8 && lineNum <= 13)
		{
			float num;
			char sNum[10];
			char meas[10];
			int i;

			sscanf(str, "%[^ ]", &sNum);
			sscanf(str, "%*s %s", &meas);
			meas[3] = '\0';  //截取单位前三个字符，英文单词规避复数问题
			if (strcmp(meas, "fee") == 0)
			{
				strcpy(meas, "foo");
			}                              //对feet特殊处理。。。
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
		//////////////////////
		if (lineNum >= 14 && lineNum <=15)
		{

		}



		return result;

	}

	printf("\n\n\n%.2f m\n\n", calc(buf[12].str, buf[12].lineNumber));


	fclose(fp);
	return 0;


}



