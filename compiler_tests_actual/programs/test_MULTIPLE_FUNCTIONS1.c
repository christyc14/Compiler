int func1(int x)
{
	return x + 3;
}

int func2()
{
	return func1(5) + func1(10);
}