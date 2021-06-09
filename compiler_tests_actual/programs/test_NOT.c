int notfunc()
{
	int a = 5;
	int ret = 0;
	if (!(a < 5))
	{
		ret = ret + 1;
	}
	if (!(5 < a))
	{
		ret = ret + 2;
	}
	if (!a)
	{
		ret = ret + 4;
	}
	if (!(!(!(!a))))
	{
		ret = ret + 8;
	}
	return ret;
}