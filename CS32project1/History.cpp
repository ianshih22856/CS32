#include <iostream>
#include "History.h"
using namespace std;

History::History(int nRows, int nCols)
{
    m_nrows = nRows;
    m_ncols = nCols;
}

bool History::record(int r, int c)
{
    if (r < 1 || r > m_nrows)
        return false;
    if (c < 1 || c > m_ncols)
        return false;
    counterArray[r][c]++;
    return true;
}
void History::display() const
{
    clearScreen();
    int r, c;
    for (r = 1; r <= m_nrows; r++)
    {
        for (c = 1; c <= m_ncols; c++)
        {
            if (counterArray[r][c] <= 0)
                cout << ".";
            else if (counterArray[r][c] <= 25)
                //Convert integer to char using ASCII values
                cout << char(64 + counterArray[r][c]);
            else 
                cout << "Z";
        }
        cout << endl;
    }
    cout << endl;
}
