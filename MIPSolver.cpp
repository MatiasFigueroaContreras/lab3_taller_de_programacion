#include "MIPSolver.h"

MIPSolver::MIPSolver()
{
}
MIPSolver::~MIPSolver()
{
}
std::vector<float> MIPSolver::solve(Simplex *originalProblem)
{
    std::multimap<float, Simplex *, std::greater<float>> heap;
    std::multimap<float, Simplex *, std::greater<float>>::iterator currentItr;
    Simplex *currentProblem, *copyProblem1, *copyProblem2;
    std::vector<float> currentSolution;
    float maxValue;
    int minValue, varIndex, e;
    currentSolution = originalProblem->solve();
    maxValue = currentSolution[0];
    heap.emplace(maxValue, originalProblem);
    while (!heap.empty())
    {
        currentItr = heap.begin();
        maxValue = currentItr->first;
        currentProblem = currentItr->second;
        currentSolution = currentProblem->getSolution();
        minValue = getMinValue(currentSolution);
        heap.erase(currentItr);
        if ((float)minValue == maxValue)
        {
            // Borrar Simplex's que se quedan en el heap
            return currentSolution;
        }
        varIndex = getVarCloseInt(currentSolution);
        e = (int)currentSolution[varIndex];
        copyProblem1 = currentProblem->copy();
        copyProblem2 = currentProblem->copy();
        copyProblem1->insertConstraint(e, varIndex, 1);
        copyProblem2->insertConstraint(e + 1, varIndex, 2);
    }
}


