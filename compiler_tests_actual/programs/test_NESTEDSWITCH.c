int nestedSwitch()
{
	int i = 4;
	int j = 10;
	int ret = 0;

	switch (i)
	{
	case 0:
		ret += 1;
		break;
	case 8:
		ret += 2;
		break;
	case 4:
		ret += 4;
		switch (j)
		{
		case 5:
			ret += 8;
			break;
		case 10:
			ret += 16;
			break;
		case 15:
			ret += 32;
			break;
		default:
			ret += 64;
			break;
		}
		ret += 128;
		break;
	default:
		ret += 256;
	}
	ret += 512;
	return ret;
}