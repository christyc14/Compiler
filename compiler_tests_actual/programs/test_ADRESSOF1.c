int f()
{
	int x[3];
	int* y1 = &x[0];
	int* y2 = &x[2];
	return y2 - y1;
}