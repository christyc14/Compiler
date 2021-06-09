int arr[10];


int fill()
{
	arr[0] = 1;
	arr[2] = 2;
	arr[4] = 4;
	arr[5] = 8;
	arr[6] = 16;
	arr[8] = 32;
	return 0;
}

int get(int a)
{
	return arr[a];
}

int f1()
{
	int temp = 0;
	temp = fill();
	return get(6);
}