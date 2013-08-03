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

int main()
{
	FILE *fp;
	FILE *fpw;
	CONVRULE convRules[6];
	BUF buf[17];

	int i = 0;

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		printf("could not open file");
		return 0;
	}
	if ((fpw = fopen("output.txt", "w")) == NULL)
	{
		printf("could not write to file");
		return 0;
	}

	///读取到buf
	while (!feof(fp))
	{
		fgets(buf[i].str, 128, fp);
		i++;
		buf[i-1].lineNumber = i;
	}

	///解析转换规则
	int j;
	for(j=0; j<6; j++)
	{
		sscanf(buf[j].str, "%*f %s %*c %f %*c", convRules[j].measurement, &convRules[j].meter);
		convRules[j].measurement[3] = '\0';  //截取单位前三个字符，规避英文单词复数问题
	}

	float calc(char *str, int lineNum)
	{
		float result;

		//////////////////////
		if (lineNum >=8 && lineNum <= 13)
		{
			float num;
			char meas[10];
			int i;

			sscanf(str,"%f %s", &num, meas);
			meas[3] = '\0';  //截取单位前三个字符，规避英文单词复数问题

			if (strcmp(meas, "fee") == 0)
			{
				strcpy(meas, "foo");
			}                              //对feet特殊处理。。。

			for (i=0; i<6; i++)
			{
				if (strcmp(convRules[i].measurement, meas) == 0)
					result = num * convRules[i].meter;
			}
		}
		//////////////////////
		if (lineNum >= 14 && lineNum <=15)
		{
			float num1, num2;
			char meas1[10];
			char meas2[10];
			char sign;

			sscanf(str,"%f %s %c %f %s",&num1, meas1, &sign, &num2, meas2 );
			meas1[3] = meas2[3] = '\0';
			if (strcmp(meas1, "fee") == 0)
				strcpy(meas1, "foo");
			if (strcmp(meas2, "fee") == 0)
				strcpy(meas2, "foo");

			int pos1, pos2, i;
			for (i=0; i<6; i++)
			{
				if (strcmp(meas1, convRules[i].measurement) == 0)
					pos1 = i;
				if (strcmp(meas2, convRules[i].measurement) == 0)
					pos2 = i;
			}

			if (sign == '+')
				result = num1 * convRules[pos1].meter + num2 * convRules[pos2].meter;
			if (sign == '-')
				result = num1 * convRules[pos1].meter - num2 * convRules[pos2].meter;
		}
		/////////////////////////
		if (lineNum >= 16 && lineNum <=17)
		{
			float num1, num2, num3;
			char meas1[10];
			char meas2[10];
			char meas3[10];
			char sign1;
			char sign2;

			sscanf(str,"%f %s %c %f %s %c %f %s",&num1, meas1, &sign1, &num2, meas2, &sign2, &num3, meas3);
			meas1[3] = meas2[3] = meas3[3] = '\0';
			if (strcmp(meas1, "fee") == 0)
				strcpy(meas1, "foo");
			if (strcmp(meas2, "fee") == 0)
				strcpy(meas2, "foo");
			if (strcmp(meas3, "fee") == 0)
				strcpy(meas3, "foo");

			int pos1, pos2, pos3, i;
			for (i=0; i<6; i++)
			{
				if (strcmp(meas1, convRules[i].measurement) == 0)
					pos1 = i;
				if (strcmp(meas2, convRules[i].measurement) == 0)
					pos2 = i;
				if (strcmp(meas3, convRules[i].measurement) == 0)
					pos3 = i;
			}

			if (sign1 == '+' && sign2 == '+')
				result = num1 * convRules[pos1].meter + num2 * convRules[pos2].meter + num3 *convRules[pos3].meter;
			if (sign1 == '+' && sign2 == '-')
				result = num1 * convRules[pos1].meter + num2 * convRules[pos2].meter - num3 *convRules[pos3].meter;
			if (sign1 == '-' && sign2 == '+')
				result = num1 * convRules[pos1].meter - num2 * convRules[pos2].meter + num3 *convRules[pos3].meter;
			if (sign1 == '-' && sign2 == '-')
				result = num1 * convRules[pos1].meter - num2 * convRules[pos2].meter - num3 *convRules[pos3].meter;
		}
		/////////////////////////
		return result;
	}

	fprintf(fpw, "%s", "leocuit@foxmail.com");
	fprintf(fpw, "%c%c", '\n', '\n');

	for (i=7; i<17; i++)
	{
		fprintf(fpw, "%.2f m%c", calc(buf[i].str, buf[i].lineNumber), '\n');
	}

	printf("calculate completed, file write succeeded!");


	fclose(fp);
	fclose(fpw);
	return 0;
}



