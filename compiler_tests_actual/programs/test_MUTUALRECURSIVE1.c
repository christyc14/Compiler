int odd(int a);

int even(int a)
{
	if (a == 0)
		return 10;
	return odd(a-1);
}

int odd(int a)
{
	if (a == 0)
		return 15;
	return even(a-1);
}