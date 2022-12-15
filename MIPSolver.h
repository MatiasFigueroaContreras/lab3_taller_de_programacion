#include "Simplex.h"
#include <map>

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