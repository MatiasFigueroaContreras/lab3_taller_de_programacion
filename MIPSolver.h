#include "Simplex.h"
#include <map>

class MIPSolver
{
private:
    
public:
    MIPSolver();
    ~MIPSolver();
    std::vector<float> solve(Simplex *originalProblem);
    int getMinValue(std::vector<float> solution);
    int getVarCloseInt(std::vector<float> solution);
};