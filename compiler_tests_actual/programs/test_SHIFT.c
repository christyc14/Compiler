int shift()
{
	int k = 640;
	k = k >> 4;
	k = k + 6;
	k = k << 2;
	return k;
}