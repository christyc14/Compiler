int pointer(int*);

int main()
{
    int x[5];
    x[0] = 8;
    x[1] = 2;
    x[2] = 4;
    x[3] = 1;
    x[4] = 16;
    return !(pointer(x) == 2);
}
