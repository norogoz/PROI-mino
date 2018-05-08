#ifndef MINO_H
#define MINO_H

#include "point.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Mino
{
    public:
        Mino(int);
        Mino(const Mino&);
        ~Mino();

        Mino& operator=(const Mino&);

        int numberOfShapes;

        static char **grid;
        static int cX, cY;

        static int allGrid(int, int);
        static int deallGrid();
        static int findEmpty();
        static void printGrid();

        int nextShape();
        int canPut();
        int putShape();
        int delShape(int, int);

        Point< int > *G;

    private:
        int counter = 0;
        int N;
        bool **tab;

        static int gridX, gridY;


        vector< Point< int >> P0;
        vector< vector< Point< int >>> P;

        bool areNeighbours(int, int);
        void generateShapes();
};

#endif // MINO_H
