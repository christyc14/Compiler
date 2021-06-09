int nestedWhile()
{
	int a = 10;
	int b;
	int res = 0;

	while (a)
	{
		b = 5;
		while (b)
		{
			res = res + 1;
			b = b - 1;
		}
		a = a - 1;
	}
	return res;
}