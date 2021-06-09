int continue1()
{
	int i = 0;
	int ret = 0;

	while (i < 15)
	{
		i = i + 1;
		if (i > 6)
		{
			continue;
		}
		ret = ret + 1;
	}

	for (i = 0; i < 15; i = i + 1)
	{
		if (i > 6)
		{
			continue;
		}
		ret = ret + 1;
	}

	return ret;
}