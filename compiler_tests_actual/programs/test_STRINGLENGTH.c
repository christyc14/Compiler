int g()
{
    int i = 0;
    char* p = "Hello something long";
    while (*p != '\0')
    {
        i++;
        p++;
    }
    return i;
}