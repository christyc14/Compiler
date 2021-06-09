int pointer()
{
	int v = 10;
	int* p = &v;
	int** pp = &p;
	int*** ppp = &pp;
	int**** pppp = &ppp;
	int***** ppppp = &pppp;
	v = 17;
	return *****ppppp;
}
