int _global_array[5];

int f()
{
	_global_array[0] = 5;
	_global_array[1] = 10;
	_global_array[2] = 9;
	_global_array[3] = 6;
	_global_array[4] = 3;
	return _global_array[1 * 2 + 3 - 2 * (3 - 2)];
}