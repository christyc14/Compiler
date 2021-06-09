int recursion(int k, int acc)
{
	if (k == 0)
	{
		return acc;
	}
	return recursion(k - 1, acc + 1) + recursion(k - 1, acc + 1);
}