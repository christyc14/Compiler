int fff()
{
	int a = 3;
	int b = 4;
	int ret = 0;
	if (a < 2)
	{
		ret = ret + 1;
	}
	else if(b < 5)
	{
		ret = ret + 2;
	}
	else {
		ret = ret + 4;
	}
	if (a < 4)
		ret = ret + 8;
	ret = ret + 16;
	return ret;
}