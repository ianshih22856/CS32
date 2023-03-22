
int countIsIn(const double a1[], int n1, const double a2[], int n2)
{
    if (n1 <= 0)
        return 1;
    if (n2 <= 0 || n1 > n2)
        return 0;
    int counter = 0;
    if (a1[n1 - 1] == a2[n2 - 1])
    {
        if (n1 == 1)
        {
            counter++;
            counter += countIsIn(a1, n1, a2, n2 - 1);
            return counter;
        }
        if (n2 == 1)
            return 0;
        counter += countIsIn(a1, n1 - 1, a2, n2 - 1);
        counter += countIsIn(a1, n1, a2, n2 - 1);
    }
    else
        counter+=countIsIn(a1, n1, a2, n2 - 1);
    return counter;
}

// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}
void divide(double a[], int n, double divider, int& firstNotGreater, int& firstLess)
{
    if (n < 0)
    n = 0;

        // It will always be the case that just before evaluating the loop
        // condition:
        //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
        //  Every element earlier than position firstNotGreater is > divider
        //  Every element from position firstNotGreater to firstUnknown-1 is
        //    == divider
        //  Every element from firstUnknown to firstLess-1 is not known yet
        //  Every element at position firstLess or later is < divider

    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < divider)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > divider)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}
void order(double a[], int n)
{
    if (n <= 1)
        return;
    int notGreater, less;
    divide(a, n, a[n - 1], notGreater, less);
    order(a, n - 1); 
}

