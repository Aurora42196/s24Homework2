//
//  mazequeue.cpp
//  s24Homework2
//
//  Created by Cameron Maiden on 4/30/24.
//

///////////////////////////////////////////////////////////////////////////
//  Function declarations
///////////////////////////////////////////////////////////////////////////

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
         // Return true if there is a path from (sr,sc) to (er,ec)
         // through the maze; return false otherwise

///////////////////////////////////////////////////////////////////////////
//  main function (COMMENT THE FUNCTION OUT BEFORE TURNING IT IN!!!!!!)
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <queue>

using namespace std;

//int main()
//{
//    char maze[10][10] = {
//        // 0   1   2   3   4   5   6   7   8   9
//        { 'X','X','X','X','X','X','X','X','X','X' }, // 0
//        { 'X','.','.','.','X','.','.','X','.','X' }, // 1
//        { 'X','.','X','X','X','.','.','.','.','X' }, // 2
//        { 'X','.','X','.','X','X','X','X','.','X' }, // 3
//        { 'X','X','X','.','.','.','.','.','.','X' }, // 4
//        { 'X','.','.','.','X','.','X','X','.','X' }, // 5
//        { 'X','.','X','.','X','.','.','X','.','X' }, // 6
//        { 'X','.','X','X','X','X','.','X','.','X' }, // 7
//        { 'X','.','.','X','.','.','.','X','.','X' }, // 8
//        { 'X','X','X','X','X','X','X','X','X','X' }  // 9
//    };
//    
//    if (pathExists(maze, 4,3, 1,8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//    
//}

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

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr,sc));
    maze[sr][sc] = '#';
    
    while(!coordQueue.empty())
    {
        Coord curr = coordQueue.front();
        //cerr << "Coordinate popped from the queue: [" << curr.r() << "][" << curr.c() << "]" << endl;
        coordQueue.pop();
        
        if (curr.r() == er && curr.c() == ec) // if the current coordinate is equal to the ending coordinate
            return true;
        
// Check each place you can move from the current cell as follows:
///         If you can move EAST and haven't encountered that cell yet,
///             then push the coordinate (r,c+1) onto the stack and update
///             maze[r][c+1] to indicate the algorithm has encountered it.
        if(maze[curr.r()][curr.c()+1] != 'X' && maze[curr.r()][curr.c()+1] != '#') // if EAST discoverable
        {
            coordQueue.push(Coord(curr.r(), curr.c()+1));
            maze[curr.r()][curr.c()+1] = '#';
        }
        
///         If you can move SOUTH and haven't encountered that cell yet,
///             then push the coordinate (r+1,c) onto the stack and update
///             maze[r+1][c] to indicate the algorithm has encountered it.
        if(maze[curr.r()+1][curr.c()] != 'X' && maze[curr.r()+1][curr.c()] != '#') // if SOUTH discoverable
        {
            coordQueue.push(Coord(curr.r()+1, curr.c()));
            maze[curr.r()+1][curr.c()] = '#';
        }
        
///         If you can move WEST and haven't encountered that cell yet,
///             then push the coordinate (r,c-1) onto the stack and update
///             maze[r][c-1] to indicate the algorithm has encountered it.
        if(maze[curr.r()][curr.c()-1] != 'X' && maze[curr.r()][curr.c()-1] != '#') // if WEST discoverable
        {
            coordQueue.push(Coord(curr.r(), curr.c()-1));
            maze[curr.r()][curr.c()-1] = '#';
        }
        
///         If you can move NORTH and haven't encountered that cell yet,
///             then push the coordinate (r-1,c) onto the stack and update
///             maze[r-1][c] to indicate the algorithm has encountered it.
        if(maze[curr.r()-1][curr.c()] != 'X' && maze[curr.r()-1][curr.c()] != '#') // if NORTH discoverable
        {
            coordQueue.push(Coord(curr.r()-1, curr.c()));
            maze[curr.r()-1][curr.c()] = '#';
        }

    }
    return false;
}

