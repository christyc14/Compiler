int f1(int x) { return x + 1; }
int f2(int x) { return f1(x + 1); }
int f3(int x) { return f2(x + 1); }
int f4(int x) { return f3(x + 1); }
int f5(int x) { return f4(x + 1); }
int f6(int x) { return f5(x + 1); }
int f7(int x) { return f6(x + 1); }
int f8(int x) { return f7(x + 1); }
int f9(int x) { return f8(x + 1); }
int f10(int x) { return f9(x + 1); }
int f11(int x) { return f10(x + 1); }
int f12(int x) { return f11(x + 1); }
int f13(int x) { return f12(x + 1); }
int f14(int x) { return f13(x + 1); }
int f15(int x) { return f14(x + 1); }
int f16(int x) { return f15(x + 1); }

int start()
{
	return f16(6) + f8(3) + f3(2);
}