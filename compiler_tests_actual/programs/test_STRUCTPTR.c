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


int f1(struct s1* p)
{
    p->i2 = 20;
    return p->i1+p->i2-p->i3;
}


int f2()
{
    int t;
    struct s1 s;
    s.i1 = 10;
    s.c2 = 'c';
    s.i2 = 20;
    s.c4 = 'p';
    s.i3 = -50;
    t=f1(&s);
    s.i1 = 2;
    return (s.i1 + s.i2 - s.i3)*t;
}