int ack(int m, int n)
{
    int arr[500];
    arr[499] = 1;

    if (m == 0) {
        return n + arr[499];
    }
    else if ((m > 0) && (n == 0)) {
        return ack(m - 1, 1);
    }
    else if ((m > 0) && (n > 0)) {
        return ack(m - 1, ack(m, n - 1));
    }
}