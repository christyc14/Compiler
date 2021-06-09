struct s1 {
    int i1;
    unsigned u1;
    char c;
    int i2;
    double d1;
};


int f()
{
    struct s1 s;
    s.i1 = 5;
    s.i2 = 6;
    s.u1 = -5;
    s.c = 'c';
    s.d1 = 50.0;
    return s.i1 + s.i2;
}
