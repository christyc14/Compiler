int if_true()
{
	int a = 1;
	int ret = 0;
	if (a) {
		ret = ret + 10;
	}
	ret = ret + 4;
	return ret;
}