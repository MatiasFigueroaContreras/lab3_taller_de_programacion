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

    std::cout << "\t\tProblema 1" << std::endl;
    Simplex *simplex = new Simplex(a, m1, m2, m3);
    std::vector<float> par1 = simplex->solve();
    for(size_t i = 0; i < par1.size(); i++)
    {
        std::cout << par1[i] << " ";
    }
    std::cout << std::endl;

    simplex->insertConstraint(2, 1, 2);
    simplex->printProblemMatrix();

    float c2[4][5] = 
        {{0.0, 2.0, -4.0, 0.0, 0.0},
         {2.0, -6.0, 1.0, -1.0, 0.0},
         {8.0, 3.0, -4.0, 0.0, -1.0},
         {0.0, 0.0, 0.0, 0.0, 0.0}};

    std::vector<std::vector<float>> a2;
    for (size_t i = 0; i < 4; i++)
    {
        std::vector<float> col2;
        for (int j = 0; j < 5; j++)
        {
            col2.push_back(c2[i][j]);
        }

        a2.push_back(col2);
    }
    std::cout << std::endl << "\t\tProblema 2" << std::endl;
    Simplex *simplex2 = new Simplex(a2, 0, 0, 2);
    std::vector<float> par2 = simplex2->solve();
    for(size_t i = 0; i < par2.size(); i++)
    {
        std::cout << par2[i] << " ";
    }
    std::cout << std::endl;
    simplex2->insertConstraint(2, 1, 3);
    simplex2->printProblemMatrix();
}
