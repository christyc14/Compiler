int inc()
{
	int k = 7;
	int j = 3;
	int ret1 = 0;
	int ret2 = 0;
	int ret3 = 0;
	int ret4 = 0;

	ret1 = k++;
	ret2 = ++k;
	
	ret3 = j--;
	ret4 = --j;

	return (ret2 - ret3) * (ret4 - ret1)*ret1;

}