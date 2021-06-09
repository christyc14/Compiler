int switch1()
{
	int var;
	int ret = 0;
	var = 2;
	switch (var)
	{
	case 0:
		ret += 1;
	case 2:
		ret += 2;
	case 7:
		ret += 4;
	default:
		ret += 8;
	}
	ret += 16;
	return ret;
}