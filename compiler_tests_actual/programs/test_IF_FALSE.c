int if_false()
{
	int ret = 0;
	int a = 1;
	if (ret) {
		ret = ret + 10;
	}
	ret = ret + 4;
	return ret;
}