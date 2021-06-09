int pointer(int* p)
{
	p = p + *(p + 3);
	return *p;
}

int driver()
{
    {
        int x[5];
        x[0] = 1;
        x[1] = 13;
        x[2] = 4;
        x[3] = 1;
        x[4] = 16;
        return pointer(x);
    }

}
