void removeOdd(vector<int>& v)
{
    vector<int>::iterator it = v.end() - 1;
    while (it != v.begin() - 1)
    {
        if (*it % 2 != 0)
            v.erase(it--);
        else 
            it--;
    }
}
