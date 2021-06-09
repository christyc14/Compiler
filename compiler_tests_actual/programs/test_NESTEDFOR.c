int forloop()
{
	int i = 6;
	int j = 5;
	int ret = 0;

	for (i = 0; i < 10; i = i + 1)
	{
		for (; j < 7; j = j + 2)
		{
			ret = ret + 1;
		}
		j = j - 8;
	}

	return ret;
}