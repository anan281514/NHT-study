// 1Dtr.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

int main()
{
	double length; //定义长度
	double TL, TR; //定义左侧右侧温度
	double den, c, k;
	double s;
	double dt;   //定义几何，边界，热物性

	//---------------------------------------------------------------

	int n; //定义n个网格

	//--------------------------------------------------------------------

	double dx;
	double T0[11], T[11]; //最多计算九个网格，加两个边界网格一共十一个，C的数组从0开始即此处为0-10
	double ae0[11], aw0[11], ap0[11], ap1[11], b[11];
	int i;

	length = 3;
	TL = 3; TR = 5;
	den = 100; c = 1000; k = 10;
	s = 10;
	dt = 100;

	n = 3; //划分三个网格
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
	ap0[i] = den * c * dx / dt - ae0[i] - aw0[i];
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


	for (i = 1; i <= n; i++)
	{
		T[i] = (ae0[i] * T0[i + 1] + aw0[i] * T0[i - 1] + ap0[i] * T0[i] + b[i]) / ap1[i]; //当地网格的计算式，注意小括号
		printf("%e  ", T[i]);
	}
	return 0;
}
//------------------以上可以计算一个时间步长，但是我们想看多个时间步一直到稳态。
