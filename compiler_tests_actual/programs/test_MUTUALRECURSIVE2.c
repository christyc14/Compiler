int func2(int a, int b);
int func3(int a, int b);


int func1(int a, int b)
{
	if (a == 0)
	{
		return 5 +b;
	}
	return func2(a - 1, b + 1);
}

int func2(int a, int b)
{
	if (a == 0)
	{
		return 10+b;
	}
	return func3(a - 1, b + 1);
}

int func3(int a, int b)
{
	if (a == 0)
	{
		return 15+b;
	}
	return func1(a - 1, b + 1);
}