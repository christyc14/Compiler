struct s1 {
    int var1;
    int var2;
};

struct s2
{
    int var1;
    int var2;
    int var3;
};

int f()
{
    struct s1 z1;
    struct s1 z2;
    struct s2 z3;
    z1.var1 = 1;
    z1.var2 = 2;
    z2.var1 = 4;
    z2.var2 = 8;
    z3.var1 = 16;
    z3.var2 = 32;
    z3.var3 = 64;

    return z1.var1 + z1.var2 + z2.var1 + z2.var2 + z3.var1 + z3.var2 + z3.var3;
}