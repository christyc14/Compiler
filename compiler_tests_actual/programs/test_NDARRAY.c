int f()
{
	int t1;
	int a[2][1][1][4][5];
	a[0][0][0][0][0] = 1;
	a[0][0][0][0][1] = 2;
	a[0][0][0][0][2] = 4;
	a[0][0][0][1][0] = 8;
	a[0][0][0][1][1] = 16;
	a[0][0][0][2][0] = 32;
	return a[0][0][0][0][0] + a[0][0][0][1][1] + 64;
}