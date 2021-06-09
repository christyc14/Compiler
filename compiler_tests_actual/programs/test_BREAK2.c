int break2()
{
	int i = 0;
	int j = 0;
	int ret = 0;

	for (i = 0; i < 5; i = i + 1)
	{
		for (j = 0; j < 10; j = j + 1)
		{
			ret = ret + 1;
			if (j > 6)
			{
				break;
			}
			ret = ret + 1;
		}
	}


	i = 0;
	
	while (i < 5)
	{
		j = 0;
		while (j < 10)
		{
			j = j + 1;
			ret = ret + 1;
			if (j > 6)
			{
				break;
			}
			ret = ret + 1;
		}
		i = i + 1;
	}
	ret = ret + 1;
	
	return ret;
}