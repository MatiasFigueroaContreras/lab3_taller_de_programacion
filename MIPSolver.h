#include "Simplex.h"
#include <map>

class MIPSolver
{
private:
    
public:
    MIPSolver();
    ~MIPSolver();
    std::vector<float> solve(Simplex *originalProblem);
    int getlowerBound(Simplex *problem);
    int getFarthestIntegerVariable(std::vector<float> solution);
};