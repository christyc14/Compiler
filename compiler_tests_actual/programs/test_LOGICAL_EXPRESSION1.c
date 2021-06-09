int logical()
{
	int var1 = 1;
	int res = 0;

	if (var1 && 0)
	{
		res = res + 1;
	}
	if (var1 && 1)
	{
		res = res + 2;
	}
	if (var1 || 0)
	{
		res = res + 4;
	}
	if (0 || 1 && 0)
	{
		res = res + 8;
	}
	if (var1 && 0 || (var1 || 1 && 1 || 0) && 0)
	{
		res = res + 16;
	}
	return res;
}
