#include "mino.h"

#define X 5
#define Y 7
#define MINO1 6
#define MINO2 4

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system ("clear");
#endif
}

int fillGrid( Mino& A, Mino& B )
{
    if( !Mino::findEmpty() ) return 1;

    int x = Mino::cX, y = Mino::cY;

    for( int i = 0; i < A.numberOfShapes; ++i, A.nextShape() )
    {
        if( A.canPut() )
            {
                A.putShape();
                //Mino::printGrid();

                if( fillGrid(A, B) )
                {
                    clearScreen();
                    Mino::printGrid();
                    A.delShape(x, y);
                    for ( int j = i; j < A.numberOfShapes; ++j, A.nextShape() );
                    getchar();
                    return 1;
                }

                A.delShape(x, y);
                //Mino::printGrid();
            }
    }

    for( int i = 0; i < B.numberOfShapes; ++i, B.nextShape() )
    {
        if( B.canPut() )
            {
                B.putShape();
                //Mino::printGrid();

                if( fillGrid(A, B) )
                {
                    clearScreen();
                    Mino::printGrid();
                    B.delShape(x, y);
                    for ( int j = i; j < B.numberOfShapes; ++j, B.nextShape() );
                    getchar();
                    return 1;
                }

                B.delShape(x, y);
                //Mino::printGrid();
            }
    }

    return 0;
}

int analyzeSolution()
{
    int a = MINO1, b = MINO2, s = X*Y;

    if( s % a == 0 || s % b == 0 ) return 1;

    while( s > 0 )
    {
        s -= a;
        if( s % b == 0 ) return 1;
    }
    return 0;
}

int main()
{
    Mino::allGrid(X,Y);
    Mino A(MINO1);
    Mino B(MINO2);

    if( analyzeSolution() )
    {
        cout << "Szukanie rozwiazania." << endl;
        fillGrid(A, B);
        clearScreen();
        Mino::printGrid();
    }
    else
    {
        cout << "Rozwiazanie nie istnieje." << endl;
    }

    getchar();

    Mino::deallGrid();
    return 0;
}
