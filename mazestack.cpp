#include <stack>
#include <iostream>
#include <string>
using namespace std;
// Push the starting coordinate (sr,sc) onto the coordinate stack and
// update maze[sr][sc] to indicate that the algorithm has encountered
// it (i.e., set maze[sr][sc] to have a value other than '.').
// While the stack is not empty,
// {   Pop the top coordinate off the stack. This gives you the current
//     (r,c) location that your algorithm is exploring.
// If the current (r,c) coordinate is equal to the ending coordinate,
//     then we've solved the maze so return true!
// Check each place you can move from the current cell as follows:
//     If you can move EAST and haven't encountered that cell yet,
//         then push the coordinate (r,c+1) onto the stack and update
//         maze[r][c+1] to indicate the algorithm has encountered it.
//     If you can move NORTH and haven't encountered that cell yet,
//         then push the coordinate (r-1,c) onto the stack and update
//         maze[r-1][c] to indicate the algorithm has encountered it.
//     If you can move WEST and haven't encountered that cell yet,
//         then push the coordinate (r,c-1) onto the stack and update
//         maze[r][c-1] to indicate the algorithm has encountered it.
//     If you can move SOUTH and haven't encountered that cell yet,
//         then push the coordinate (r+1,c) onto the stack and update
//         maze[r+1][c] to indicate the algorithm has encountered it.
// }
// There was no solution, so return false

class Coord
{
    public:
        Coord(int r, int c) : m_row(r), m_col(c) {}
        int r() const { return m_row; }
        int c() const { return m_col; }
    private:
        int m_row;
        int m_col;
};
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;

    Coord startCoord(sr, sc);
    Coord endCoord(er,ec);
    coordStack.push(startCoord);
    maze[sr][sc] = '*';
    int counter = 1;
    while (!coordStack.empty())
    {
        Coord top = coordStack.top();
        coordStack.pop();
        cout << counter << ". r: " << top.r() << ", c: " << top.c() << endl;
        if (top.r() == endCoord.r() && top.c() == endCoord.c())
            return true;
        //North
        if (maze[top.r() - 1][top.c()] == '.')
        {
            Coord north(top.r() - 1, top.c());
            coordStack.push(north);
            maze[top.r() - 1][top.c()] = '*';
        }
        //South
        if (maze[top.r() + 1][top.c()] == '.')
        {
            Coord south(top.r() + 1, top.c());
            coordStack.push(south);
            maze[top.r() + 1][top.c()] = '*';
        }
        //West
        if (maze[top.r()][top.c() - 1] == '.')
        {
            Coord west(top.r(), top.c() - 1);
            coordStack.push(west);
            maze[top.r()][top.c() - 1] = '*';
        }
        //East
        if (maze[top.r()][top.c() + 1] == '.')
        {
            Coord east(top.r(), top.c() + 1);
            coordStack.push(east);
            maze[top.r()][top.c() + 1] = '*';
        }
        counter++;
    }
    return false;
}

          