void listAll(string path, const File* f)  // two-parameter overload
{
    
    if (f->files() == nullptr)
    {
        cout << path<< endl;
        return;
    }
    else
        cout << path + "/" << endl;
    vector<File*>::const_iterator it = f->files()->begin();
    while (it != f->files()->end())
    {
        listAll(path + "/" + (*it)->name(), *it);
        it++;
    }
}
