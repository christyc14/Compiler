struct s1 {
    int i1;
    unsigned u1;
    char c1;
    char c2;
    int i2;
    char c3;
    char c4;
    char c5;
    char c6;
    int i3;
};


int f1(struct s1 k)
{
    return k.i1 + k.i2 - k.i3;
}


int f2()
{
    struct s1 s;
    s.i1 = 10;
    s.c2 = 'c';
    s.i2 = 20;
    s.c4 = 'p';
    s.i3 = -50;
    return f1(s);
}