int pointer(int* p)
{
	p = p + *(p + 3);
	return *p;
}
