struct s2 {
    char c1;
    char c2;
    char c3;
    int i1;
};

struct s1 {
    int i1;
    unsigned u1;
    char c1;
    char c2;
    int i2;
    struct s2 k1;
    char c3;
    char c4;
    char c5;
    char c6;
    char c7;
    struct s2 k2;
};

int f()
{
    struct s1 t1;
    struct s1 t2;
    struct s1 t3;

    t1.k2.i1 = 1;
    t1.k1.i1 = 2;
    t1.i1 = 4;

    t2.k2.i1 = 8;
    t2.k1.i1 = 16;
    t2.i1 = 32;

    return t1.k2.i1 + t1.k1.i1 + t2.k1.i1 + t2.i1;
}