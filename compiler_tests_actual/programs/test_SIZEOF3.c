struct s1 {
    int i1;
    unsigned u1;
    double d1;
};

int s()
{
    struct s1 p;
    return sizeof(p) + sizeof(struct s1);
}