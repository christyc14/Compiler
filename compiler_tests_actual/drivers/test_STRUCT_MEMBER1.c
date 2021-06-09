struct s {
    int var;
};

int f()
{
    struct s z;
    z.var = 21;
    return z.var;
}