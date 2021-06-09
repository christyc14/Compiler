int arr[10];

int f()
{
	int x = 1;
	int y = 2;
	arr[0] = 5;
	arr[5] = 10;
	arr[9] = 3000;

	return arr[5] + x + y;
}