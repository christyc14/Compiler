int switch2()
{
	int var;
	int ret = 0;
	var = 4;
	switch (var)
	{
	case 0:
		ret += 1;
		break;
	case 4:
		ret += 2;
		break;
	case 2:
		ret += 4;
		break;
	default:
		ret += 8;
	}
	ret += 16;
	return ret;
}