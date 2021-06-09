int glbl1;
int glbl2;

int f01()
{
	glbl1 = glbl1 + 1;
	return 1;
}

int f00()
{
	glbl1 = glbl1 + 1;
	return 0;
}

int f11()
{
	glbl2 = glbl2 + 1;
	return 1;
}

int f10()
{
	glbl2 = glbl2 + 1;
	return 0;
}



int logical()
{
	glbl1 = 0;
	glbl2 = 0;

	f00() || f00() || f01() || f01() || f00() || f01();
	f11() && f11() && f10() && f11() && f10() && f11();
	return glbl1 * 10 + glbl2;
}