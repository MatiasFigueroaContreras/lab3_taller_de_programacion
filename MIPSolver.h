#include "Simplex.h"
#include <map>

/*
    Descripcion de la clase MIPSolver:
    Esta clase representa un solucionador de problemas de
    programacion lineal entera.
*/
class MIPSolver
{
private:
    
public:
    MIPSolver();
    ~MIPSolver();
    std::vector<float> solve(Simplex originalProblem);
    int getLowerBound(Simplex problem);
    int getFarthestIntegerVariable(std::vector<float> solution);
};