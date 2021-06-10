#include <stdio.h>
int process(int x) 
{
	int y = 4, z;
	z = x + 12;
	z = x + 12;
    y = y;
    y = y + 0 - 0;
    y = y * 1 / 1;
	y = y + 32 - 4 * 7 / 10;
	y = x * y  + x * y - y * x - x + y * x + y * y + x / x - 12 + 59 / 2;
	y  = y * 3 + 14 * 24 - x * 12 / 4 + 4 * 5 - 10 * 2 - 5 / 6;	
	return y;
}

int mod(int a1, int b1)
{
	return a1 - (a1 / b1) * b1;
}

int main () {
	int a = (-4 * 2 + 108) / 17, b = 32 / 8 * 2 - 1, c = 13 - 1 * 4 / 2;
	int d = a + b;
	int e = a + b + c / 1;
	int f = a * b - c;
	int g1 = 42, g2 = 4, i = 0, j = 0, array[4];
	int g, h, k;
	f = a + b + c + 1500 - f;
	while (i < 4)
	{
		j = 15 * i;
		array[i] = j;
		i = i + 1;
	}
	while (i < 7) 
	{
		k = g2 * g2;
		g1 = g1 + k + i * 12 - 4 * g2 + 5 + 7 / 3;
		g = process(f) + 2 * a  - f + c * d;
		if (mod(f,2) > 0)
		{
			h = i -1;
			printf("h:%d\n",h);
		}
		if (process(a) == process(a + 3 - 2 - 1)) 
		{
			printf("f--->h:%d\n",h);
			f = f - 2 + 1;
			printf("before h:%d\n",h);
			array[mod(f, 4)] = array[mod(f, 4)] + h + g - e;
			printf("after h:%d\n",h);
		}
		a = a + 2 + 1;
		i = i + 1;
		i = i + 1;
	}
	printf("%d\n",array[0]);
	printf("%d\n",array[1]);
	printf("%d\n",array[2]);
	printf("%d\n",array[3]);
	return 0;
}

