int f()
{
	int t1;
	int a[3][3];
	int t2;
	a[0][0] = 1;
	a[0][1] = 2;
	a[0][2] = 16;
	a[1][0] = 4;
	a[1][1] = 8;
	a[2][0] = 16;
	return a[0][0] + a[0][1] + a[1][0] + a[1][1];
}