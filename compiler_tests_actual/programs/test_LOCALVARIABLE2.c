int func()
{
	int ret = 0;
	int i = 0;

	if (1)
	{
		int x = 5;
		int y = 6;

		ret = x + ret;
	}

	while (i < 1)
	{
		int x = 5;
		int z = 10;
		int p = 2;
		ret = ret + z;
		i = i + 1;
	}
	return ret;
}