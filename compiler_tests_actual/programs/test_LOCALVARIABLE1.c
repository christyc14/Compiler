int func()
{
	int x;
	x = 6;
	{
		int y = 40;
		x = y;
	}
	return x;
}