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
    std::vector<float> currentSolution, solutionProblem1, solutionProblem2;
    float upperBound;
    int lowerBound, varIndex, e;
    currentSolution = originalProblem->solve();
    if(!currentSolution.empty())
    {
        upperBound = currentSolution[0];
        heap.emplace(upperBound, originalProblem);
    }

    while (!heap.empty())
    {
        currentItr = heap.begin();
        upperBound = currentItr->first;
        currentProblem = currentItr->second;
        currentSolution = currentProblem->getSolution();
        lowerBound = getlowerBound(currentProblem);
        heap.erase(currentItr);
        currentProblem->printSolution();
        std::cout << "Lower Bound: " << lowerBound << " Upper Bound: " << upperBound << std::endl;
        if ((float)lowerBound == upperBound)
        {
            // Borrar Simplex's que se quedan en el heap
            std::cout << "Solucion encontrada" << std::endl;
            // delete currentProblem;
            return currentSolution;
        }

        varIndex = getFarthestIntegerVariable(currentSolution);
        // std::cout << varIndex << std::endl;
        e = (int) currentSolution[varIndex];
        copyProblem1 = currentProblem->copy();
        copyProblem2 = currentProblem->copy();
        copyProblem1->insertConstraint(e, varIndex, 1);
        copyProblem2->insertConstraint(e + 1, varIndex, 2);
        solutionProblem1 = copyProblem1->solve();
        solutionProblem2 = copyProblem2->solve();
        std::cout << "Rama 1: " << "x" << varIndex << " <= " << e;
        if(!solutionProblem1.empty())
        {
            std::cout << " Tiene solucion" << std::endl;
            heap.emplace(solutionProblem1[0], copyProblem1);
        }
        else
        {
            std::cout << " NO Tiene solucion" << std::endl;
            delete copyProblem1;
        }

        std::cout << "Rama 2: " << "x" << varIndex << " >= " << e + 1;
        if(!solutionProblem2.empty())
        {
            std::cout << " Tiene solucion" << std::endl;
            heap.emplace(solutionProblem2[0], copyProblem2);
        }
        else
        {
            std::cout << " NO Tiene solucion" << std::endl;
            delete copyProblem2;
        }

        delete currentProblem;
    }
    
    std::cout << "El problema no tiene solucion" << std::endl;
    std::vector<float> emptyVector;
    return emptyVector;
}

int MIPSolver::getlowerBound(Simplex *problem)
{
    int lowerBound = problem->initialA[0][0];
    std::vector<float> solution = problem->getSolution();
    for(size_t i = 1; i < solution.size(); i++)
    {
        lowerBound += problem->initialA[0][i] * (int) solution[i];
    }

    return lowerBound;
}

int MIPSolver::getFarthestIntegerVariable(std::vector<float> solution)
{
    int var = -1;
    float maxDiff = 0.0;
    float diff;
    for(int i = 1; i < (int) solution.size(); i++)
    {
        diff = solution[i] - (int) solution[i];
        if(diff > maxDiff)
        {
            maxDiff = diff;
            var = i;
        }
    }

    return var;
}
