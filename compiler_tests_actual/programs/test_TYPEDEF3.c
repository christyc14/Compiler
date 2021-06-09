typedef double def;
typedef double var;
typedef int index;
typedef double arr[32];
typedef double* pointer;


def prog()
{
	index i = 5.0;
	arr a = { 10.0,5.0,6.0,50.0,20.0,40.0,-5.0 };
	pointer p;
	p = a;
	return p[i] + p[i - 2];
}