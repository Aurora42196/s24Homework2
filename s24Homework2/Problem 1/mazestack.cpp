//
//  main.cpp
//  s24Homework2
//
//  Created by Cameron Maiden on 4/28/24.
//

///////////////////////////////////////////////////////////////////////////
//  Function declarations
///////////////////////////////////////////////////////////////////////////

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
         // Return true if there is a path from (sr,sc) to (er,ec)
         // through the maze; return false otherwise

///////////////////////////////////////////////////////////////////////////
//  Class implementations
///////////////////////////////////////////////////////////////////////////

class Coord
{
public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};

///////////////////////////////////////////////////////////////////////////
//  Function implementations
///////////////////////////////////////////////////////////////////////////

/// Push the starting coordinate (sr,sc) onto the coordinate stack and
///     update maze[sr][sc] to indicate that the algorithm has encountered
///     it (i.e., set maze[sr][sc] to have a value other than '.').
/// While the stack is not empty,
/// {   Pop the top coordinate off the stack. This gives you the current
///         (r,c) location that your algorithm is exploring.
///     If the current (r,c) coordinate is equal to the ending coordinate,
///         then we've solved the maze so return true!
///     Check each place you can move from the current cell as follows:
///         If you can move EAST and haven't encountered that cell yet,
///             then push the coordinate (r,c+1) onto the stack and update
///             maze[r][c+1] to indicate the algorithm has encountered it.
///         If you can move SOUTH and haven't encountered that cell yet,
///             then push the coordinate (r+1,c) onto the stack and update
///             maze[r+1][c] to indicate the algorithm has encountered it.
///         If you can move WEST and haven't encountered that cell yet,
///             then push the coordinate (r,c-1) onto the stack and update
///             maze[r][c-1] to indicate the algorithm has encountered it.
///         If you can move NORTH and haven't encountered that cell yet,
///             then push the coordinate (r-1,c) onto the stack and update
///             maze[r-1][c] to indicate the algorithm has encountered it.
/// }
/// There was no solution, so return false

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////
//  main function
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stack>

using namespace std;

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','X','.','.','X','.','X' },
        { 'X','.','X','X','X','.','.','.','.','X' },
        { 'X','.','X','.','X','X','X','X','.','X' },
        { 'X','X','X','.','.','.','.','.','.','X' },
        { 'X','.','.','.','X','.','X','X','.','X' },
        { 'X','.','X','.','X','.','.','X','.','X' },
        { 'X','.','X','X','X','X','.','X','.','X' },
        { 'X','.','.','X','.','.','.','X','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    
    if (pathExists(maze, 4,3, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;

}
