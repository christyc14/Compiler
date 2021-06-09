int f1(int a);
int f2(int a);

int main()
{
	return !(2500 == f1(f2(f1(5))));
}