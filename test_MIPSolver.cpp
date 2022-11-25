#include "MIPSolver.h"

int main()
{
    MIPSolver *solver = new MIPSolver();
    Simplex *simplex = new Simplex("ejemplo2.txt");

    std::vector<float> sol = solver->solve(simplex);
    
    for(size_t i = 0; i < sol.size(); i++)
    {
        std::cout << sol[i] << " ";
    }
    std::cout << std::endl;
}