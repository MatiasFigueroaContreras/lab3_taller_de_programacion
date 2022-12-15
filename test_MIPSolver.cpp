#include "MIPSolver.h"

int main()
{
    MIPSolver solver = MIPSolver();
    std::cout << "Antes carga archivo" << std::endl;
    Simplex simplex = Simplex("ejemplo2.txt");
    std::cout << "Archivo cargado" << std::endl;
    simplex.printProblemMatrix();
    std::vector<float> sol = solver.solve(simplex);
    
    for(size_t i = 0; i < sol.size(); i++)
    {
        std::cout << sol[i] << " ";
    }
    std::cout << std::endl;
}