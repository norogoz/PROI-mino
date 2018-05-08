#include "mino.h"

using namespace std;
char** Mino::grid;
int Mino::gridX, Mino::gridY, Mino::cX, Mino::cY;

Mino::Mino(int n=2) : N(n)
{
    //alokacja pamieci
    tab = new bool*[N];
    for(int i = 0; i < N; ++i)
        tab[i] = new bool[N];

    //inicjalizacja
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            tab[i][j] = false;
        }
    }

    //alokacja pamieci
    G = new Point<int>[N];

    //generowanie trywialnych ksztaltow - linie
    for( int i = 0; i < N; i++ )
    {
        G[i](0,i);
        P0.push_back( G[i] );
    }
    P.push_back( P0 );
    P0.clear();

    for( int i = 0; i < N; i++ )
    {
        G[i](i,0);
        P0.push_back( G[i] );
    }
    P.push_back( P0 );
    P0.clear();

    //generowanie nietrywialnych ksztaltow
    generateShapes();

    numberOfShapes = P.size();
    nextShape();
}

Mino::Mino(const Mino& other): N(other.N)
{
    //alokacja pamieci
    tab = new bool*[N];
    for(int i = 0; i < N; ++i)
        tab[i] = new bool[N];

    //inicjalizacja
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            tab[i][j] = false;
        }
    }

    //alokacja pamieci
    G = new Point<int>[N];

    //kopiowanie ksztaltow
    numberOfShapes = other.numberOfShapes;
    for( int i = 0; i < numberOfShapes; ++i) P.push_back( other.P[i] );

    nextShape();
    //copy ctor
}

Mino::~Mino()
{
    for(int i = 0; i < N; ++i) {
        delete[] tab[i];
    }

    delete[] tab;
    delete[] G;
    //dtor
}

Mino& Mino::operator=(const Mino& rhs)
{
    P.clear();
    numberOfShapes = rhs.numberOfShapes;
    counter = 0;
    for( int i = 0; i < numberOfShapes; ++i) P.push_back( rhs.P[i] );

    return *this;
}

int Mino::allGrid(int X, int Y) //alokuje pamiec dla pola, ktore wypelniamy n-minami
{
    gridX = X; gridY = Y;

    grid = new char*[gridX];
    for( int i = 0; i < X; ++i )
        grid[i] = new char[gridY];

    for( int i = 0; i < gridY; ++i)
        for( int j = 0; j < gridX; ++j)
            grid[j][i] = 'O';

    return 1;
}

int Mino::deallGrid() //dealokuje
{
    for( int i = 0; i < gridX; ++i)
        delete [] grid[i];
    delete [] grid;

    return 1;
}

int Mino::findEmpty() //wyszukiwanie pustych miejsc
{
    for( int y = 0; y < gridY; ++y)
        for( int x = 0; x < gridX; ++x)
            if( grid[x][y] == 'O' )
            {
                cX = x; cY = y; return 1;
            }
    return 0;
}

void Mino::printGrid()
{
    for( int y = gridY-1; y >= 0; --y)
    {
        for( int x = 0; x < gridX; ++x)
        {
            cout << Mino::grid[x][y];
        }
        cout << endl;
    }
    cout << endl;
}

int Mino::nextShape()
{
    for( int i = 0; i < N; ++i )
        G[i] = P[counter][i];

    if( counter == numberOfShapes-1 ) counter = 0;
    else counter++;

    return 1;
}

int Mino::canPut()
{
    for( int i = 0; i < N; ++i )
    {
        if( cX + G[i].x >= gridX ) return 0;
        if( cY + G[i].y >= gridY ) return 0;
        if( cX + G[i].x < 0 ) return 0;
        if( cY + G[i].y < 0 ) return 0;
        if( grid[cX + G[i].x][cY + G[i].y] != 'O' ) return 0;
    }
    return 1;
}

int Mino::putShape()
{
    if( canPut() )
    {
        for( int i = 0; i < N; ++i) grid[cX + G[i].x][cY + G[i].y] = '*';
        findEmpty();
        return 1;
    }
    return 0;
}

int Mino::delShape(int x, int y)
{
    for( int i = 0; i < N; ++i) grid[x + G[i].x][y + G[i].y] = 'O';
    findEmpty();

    return 1;
}

bool Mino::areNeighbours(int x, int y)
{
    if( !tab[x][y] )
    {
        if( counter == 0 ) return true;
        if( tab[max(0, x-1)][y] ) return true;
        if( tab[min(N-1, x+1)][y] ) return true;
        if( tab[x][max(0, y-1)] ) return true;
        if( tab[x][min(N-1, y+1)] ) return true;
    }
    return false;
}

void Mino::generateShapes()
{
    if( counter == N )
    {
        for( int i = 0; i < N; i++)
        {
            P0.push_back( G[i] );
        }

        sort( P0.begin(), P0.end() );

        for( int i = 1; i < N; i++)
        {
            P0[i] -= P0[0];
        }
        P0[0]-=P0[0];

        if( find( P.begin(), P.end(), P0 ) == P.end() )
        {
            P.push_back( P0 );
        }

        P0.clear();
    }
    else if( counter == 0 )
    {
        for( int y = 0; y < N-1; y++)
        {
            if( areNeighbours(0,y) )
            {
                tab[0][y] = true;
                G[counter](0,y);
                counter++;

                generateShapes();

                tab[0][y] = false;
                counter--;
            }
        }
    }
    else if( counter < N )
    {
        for( int x = 0; x < N-1; x++)
            for( int y = 0; y < N-1; y++)
            {
                if( areNeighbours(x,y) )
                {
                    tab[x][y] = true;
                    G[counter](x,y);
                    counter++;

                    generateShapes();

                    tab[x][y] = false;
                    counter--;
                }
            }
    }
}




