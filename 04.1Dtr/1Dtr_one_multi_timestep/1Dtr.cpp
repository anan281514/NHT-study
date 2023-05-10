// 1Dtr.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int main()
{

	FILE *outputT;
	double length; //定义长度
	double TL, TR; //定义左侧右侧温度
	double den, c, k;
	double s;
	double dt;   //定义几何，边界，热物性

	//---------------------------------------------------------------

	int n; //定义n个网格
	int tstep;
	int maxtstep;
	//--------------------------------------------------------------------

	double dx;
	double T0[101], T[101]; //最多计算九个网格，加两个边界网格一共十一个，C的数组从0开始即此处为0-10
	double ae0[101], aw0[101], ap0[101], ap1[101], b[101];
	int i;

	length = 3;
	TL = 3; TR = 5;
	den = 100; c = 1000; k = 10;
	s = 10;
	dt = 1;

	n = 99; //划分网格数量
	maxtstep = 200000;// 给出最大计算时间步长
	//---------------------------------------------------------------------

	dx = length / n;
	for (i = 2; i < n; i++) //注意这里i=2指的是从第二个网格开始，因为这里是内网格
	{
		ae0[i] = k / dx;
		aw0[i] = k / dx;
		ap0[i] = den * c * dx / dt - ae0[i] - aw0[i];
		ap1[i] = den * c * dx / dt;
		b[i] = s * dx;

	}
	i = 1;
	ae0[i] = k / dx;
	aw0[i] = k / (dx / 2);;
	ap0[i] = den * c * dx / dt - ae0[i] - aw0[i]; //注意这个式子有正值要求，即T0越大T应该越大，当dx越小，dt不变时，很容易这个式子变为负数，因此dx和dt有限制关系。
	ap1[i] = den * c * dx / dt;
	b[i] = s * dx;

	i = n;
	ae0[i] = k / (dx / 2);
	aw0[i] = k / dx;
	ap0[i] = den * c * dx / dt - ae0[i] - aw0[i];
	ap1[i] = den * c * dx / dt;
	b[i] = s * dx;

	for (i = 1; i <= n; i++)
	{
		T0[i] = 3;

	}
	T0[0] = TL;
	T0[n + 1] = TR;   //这里对应于上边的，我们在这里限定了最多九个网格，当网格为九个时，n=9，那么i的下限就是0，代表左侧温度，i的上限就是10=n+1，代表右侧温度
	
	outputT = fopen("T.txt", "w");
	for (tstep = 1; tstep <= maxtstep; tstep++) //进行时间步迭代时，新一时刻T0的值就是上一时刻对应位置T1的值
	{                                          //这个大括号很重要，不然上一句的循环不知道包含了哪些东西
		fprintf(outputT,"%i  ", tstep);
		for (i = 1; i <= n; i++)
		{
			T[i] = (ae0[i] * T0[i + 1] + aw0[i] * T0[i - 1] + ap0[i] * T0[i] + b[i]) / ap1[i]; //当地网格的计算式，注意小括号
			fprintf(outputT,"%e  ", T[i]);
		}
		fprintf(outputT,"\n");
		for (i = 1; i <= n; i++)
		{
			T0[i] = T[i];
		}
	}
	fclose(outputT);

	//这是一个时间步的循环，要在外边进行循环的嵌套
	return 0;
}
//------------------以上可以计算多个时间步长，并且将计算结果输出到T.txt文件。
