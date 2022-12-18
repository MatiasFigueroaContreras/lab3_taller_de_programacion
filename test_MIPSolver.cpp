#include "MIPSolver.h"

int main()
{
    MIPSolver solver = MIPSolver();
    Simplex simplex = Simplex("ejemplo.txt");
    std::vector<float> sol1 = solver.solve(simplex);

    std::cout << "Solucion ejemplo 1:" << std::endl;
    for (size_t i = 0; i < sol1.size(); i++)
    {
        std::cout << sol1[i] << " ";
    }
    std::cout << std::endl << std::endl;

    Simplex simplex2 = Simplex("ejemplo2.txt");
    std::vector<float> sol2 = solver.solve(simplex2);

    std::cout << "Solucion ejemplo 2:" << std::endl;
    for (size_t i = 0; i < sol2.size(); i++)
    {
        std::cout << sol2[i] << " ";
    }
    std::cout << std::endl << std::endl;

    Simplex simplex3 = Simplex("ejemplo3.txt");
    std::vector<float> sol3 = solver.solve(simplex3);

    std::cout << "Solucion ejemplo 3:" << std::endl;
    for (size_t i = 0; i < sol3.size(); i++)
    {
        std::cout << sol3[i] << " ";
    }
    std::cout << std::endl << std::endl;

    Simplex simplex4 = Simplex("ejemplo4.txt");
    std::vector<float> sol4 = solver.solve(simplex4);

    std::cout << "Solucion ejemplo 4:" << std::endl;
    for (size_t i = 0; i < sol4.size(); i++)
    {
        std::cout << sol4[i] << " ";
    }
    std::cout << std::endl;
}
