int comp()
{
	int var = 2;
	int ret = 0;
	if (var > 2)
	{
		ret = ret + 1;
	}
	if (2 > var)
	{
		ret = 2;
	}
	if (var == 2)
	{
		ret = ret + 2;
	}
	if (var == 5)
	{
		ret = 2;
	}
	if (var != 5)
	{
		ret = ret + 4;
	}
	if (var != 2)
	{
		ret = 2;
	}
	if (var >= 2)
	{
		ret = ret + 8;
	}
	if (var >= 6)
	{
		ret = ret + 16;
	}
	if (var >= 0)
	{
		ret = ret + 32;
	}
	if (var <= 2)
	{
		ret = ret + 64;
	}
	return ret;
}