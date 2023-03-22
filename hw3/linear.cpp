bool anyTrue(const double a[], int n)
{
    if (n <= 0)
        return false;
    if (somePredicate(a[n - 1]))
        return true;
    else if(anyTrue(a, n - 1))
        return true;
    return false;
}
int countTrue(const double a[], int n)
{
    if (n <= 0)
        return 0;
    int counter = 0;
    if (somePredicate(a[n - 1]))
    {
        counter++;
    }
    counter+=countTrue(a, n - 1);
    return counter; 
}

int firstTrue(const double a[], int n)
{
    if (n <= 0)
        return -1;
    int i = -1;
    if (somePredicate(a[n - 1]))
        i = n - 1;
    if (firstTrue(a, n - 1) != -1)
        i = firstTrue(a, n - 1);
    return i;
}

int indexOfMinimum(const double a[], int n)
{
    if (n <= 0)
        return -1;
    int minIndex = n - 1;
    if (a[minIndex] > a[indexOfMinimum(a, n - 1)])
    {
        minIndex = indexOfMinimum(a, n - 1);
        if (minIndex == -1)
            minIndex = 0;
    }
    return minIndex;
}
bool isIn(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0 || n1 > n2)
        return false;
    if (n1 <= 0)
        return true;
    
    if (a1[n1 - 1] == a2[n2 - 1])
    {
        if (n1 == 1)
            return true;
        if (n2 == 1)
            return false;
        return isIn(a1, n1 - 1, a2, n2 - 1);
    }
    else
    {
        return (isIn(a1, n1, a2, n2 - 1));
    }
    return false;
}
