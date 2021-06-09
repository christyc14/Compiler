int whileZero()
{
	int var = 3;
	int cnt = 0;
	while (0 < cnt)
	{
		var = var + 5;
		cnt = cnt - 1;
	}
	return var;
}