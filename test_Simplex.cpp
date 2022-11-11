#include "Simplex.h"

int main()
{
    int mp = 6;
    int np = 5;
    int m1 = 2;
    int m2 = 1;
    int m3 = 1;
    float c[mp][np] =
        {{0.0, 1.0, 1.0, 3.0, -0.5},
         {740.0, -1.0, 0.0, -2.0, 0.0},
         {0.0, 0.0, -2.0, 0.0, 7.0},
         {0.5, 0.0, -1.0, 1.0, -2.0},
         {9.0, -1.0, -1.0, -1.0, -1.0},
         {0.0, 0.0, 0.0, 0.0, 0.0}};

    std::vector<std::vector<float>> a;
    for(int i = 0; i < mp; i++)
    {
        std::vector<float> col;
        for(int j = 0; j < np; j++)
        {
            col.push_back(c[i][j]);
        }

        a.push_back(col);
    }

    Simplex *simplex = new Simplex(a, m1, m2, m3);
    simplex->solve();

    // float c2[4][3] = 
    //     {{0.0, 2.0, -4.0},
    //      {2.0, -6.0, 1.0},
    //      {8.0, 3.0, -4.0},
    //      {0.0, 0.0, 0.0}};

    // std::vector<std::vector<float>> a2;
    // for (int i = 0; i < 4; i++)
    // {
    //     std::vector<float> col2;
    //     for (int j = 0; j < 3; j++)
    //     {
    //         col2.push_back(c2[i][j]);
    //     }

    //     a2.push_back(col2);
    // }

    // Simplex *simplex2 = new Simplex(a2, 0, 0, 2);
    // simplex2->printA();
    // simplex2->solve();
}