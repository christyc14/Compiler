int nestedIf()
{
	int a = 3;
	int ret = 0;
	if (a < 7)
	{
		ret = ret + 1;
		if (a < 4)
		{
			ret = ret + 2;
		}
		else
		{
			ret = ret + 4;
		}
		ret = ret + 8;
	}
	else
	{
		ret = ret + 16;
	}
	ret = ret + 32;
	return ret;
}