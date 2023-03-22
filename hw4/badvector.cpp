
void removeBad(vector<Movie*>& v)
{
    vector<Movie*>::iterator it = v.end() - 1;
    while (it != v.begin() - 1)
    {
        if ((*it)->rating() < 50)
            {
                delete *it;
                v.erase(it--);
            }
        else 
            it--;
    }
}

