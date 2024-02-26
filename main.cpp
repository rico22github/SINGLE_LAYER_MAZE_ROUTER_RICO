#include<bits/stdc++.h>
#define MAXN 10005 // Initial size
using namespace std;

int n; // For initializing grid zize: n X n

bool grid[MAXN][MAXN]; // For checking grid elements

vector<pair<int,int> > prev[MAXN]; // For printing path

// These arrays are used to get row and column
// numbers of 4 neighbours of a given cell
int xx[]={-1,0,1,0};
int yy[]={0,1,0,-1};

// To store matrix cell cordinates
struct Point
{
    int x, y;
};

// A Data Structure for queue used in BFS
struct queueNode
{
    Point pt;
};

// return true if row number and column number is in range
bool check(int x,int y)
{
    return x >= 0 && x < n && y >= 0 && y < n;
}

// To check if adjacent cell is valid or not
bool can_go(int x, int y)
{
    return check(x,y) && grid[x][y]!=true;
}

//Retrun true for the shortest path
bool BFS(Point source, Point destination)
{

    //Clearing the previous paths
    for(int i = 0; i < n; i++)
    {
        prev[i].clear();
    }

    //A queue for BFS
    queue<Point> Q;

    //Initializing prev & mark all the cell as not visited
    bool visited[n][n];

    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            prev[i].push_back({-1,-1});

            visited[i][j] = false;
        }
    }

    //Mark the source cell as visited
    visited[source.x][source.y] = true;

    // Enqueuing source cell
    Q.push(source);

    //A BFS starting from source cell
    while(!Q.empty())
    {
        Point pt = Q.front();

        // Dequeuing the front cell in the queue
        Q.pop();

        for(int i = 0; i < 4; i++)
        {
            int row = pt.x + xx[i];
            int col = pt.y + yy[i];

            if(can_go(row,col)||(destination.x == row && destination.y == col))
            {
                if(!visited[row][col])
                {
                    visited[row][col] = true;
                    Point new_point = {row, col};
                    // Storing the previous path
                    prev[row][col] = {pt.x, pt.y};
                    // Enqueuing its adjacent cells
                    Q.push(new_point);

                    // Return true if destination is reached
                    if(pt.x == destination.x && pt.y == destination.y) return true;
                }
            }
        }
    }
    return false; // Return false if destination cannot be reached
}

// Function to print the shortest path
void printPath(Point source, Point destination)
{
    if(BFS(source,destination) == false)
    {
        cout << "Given Route is not Possible" << endl << endl;
        return;
    }

    vector<Point>path;
    Point way = destination;
    path.push_back(way);

    // While loop for traversing back from destination to source
    while(prev[way.x][way.y].first != -1  && prev[way.x][way.y].second != -1)
    {
        path.push_back({prev[way.x][way.y].first, prev[way.x][way.y].second});
        way = {prev[way.x][way.y].first, prev[way.x][way.y].second};
    }

    //Printing the path
    for(int i = path.size()-1; i >= 0; i--)
    {
        cout<< "(" << path[i].x << "," << path[i].y<< ")";

        if(i>0) cout << " -> ";

        //Marking the used path
        grid[path[i].x][path[i].y]=true;
    }

    cout << endl << endl;

    return ;
}

// Driver program to test above function
int main()
{
    cout << "The Grid Size: ";
    cin >> n; // Grid Size: n X n
    cout << endl;

    //Initializing all the grid cells to be false
    for(int i = 0; i < n; i++)
    {
        memset(grid[i], false, sizeof(grid[i]));
    }

    string type;

    cout << "The obstruction, source and destination cells" << endl << endl;

    //Selecting obstruction, source & destination cells
    while(1)
    {
        cin >> type;
        if(type == "obstruction")
        {
            int x, y;
            cin >> x >> y;
            grid[x][y] = true;
            cout << "\nThe Obstruction Cell: (" << x << ", " << y << ")" << endl << endl;
        }
        else if(type=="net")
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Point source = {x1, y1};
            Point destination = {x2, y2};
            cout << "\nHere, the Source Cell: (" << x1 << ", " << y1 << ")" << endl;
            cout << "The Destination Cell: (" << x2 << ", " << y2 << ")" << endl;
            cout << "\nThe Shortest Path:-" << endl << endl;
            printPath(source, destination); //Call printPath function
        }
    }
}
