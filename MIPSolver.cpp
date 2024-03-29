#include "MIPSolver.h"

/*
    Metodo: Constructor
    Descripcion: este metodo permite crear un objeto MIPSolver.
    Parametros: no posee.
    Retorno: La direccion del objeto creado.
*/
MIPSolver::MIPSolver()
{
}

/*
    Descripcion: este metodo permite eliminar el objeto.
    Parametros: no posee.
    Retorno: no posee.
*/
MIPSolver::~MIPSolver()
{
}

/*
    Metodo:
    Descripcion: este metodo resuelve un problema de programacion
        lineal entera.
    Parametros:
        -originalProblem: problema a resolver.
    Retorno:
        -Si encuntra solucion: Arreglo con el valor maximizado y los valores 
            enteros de los parametros de la funcion a maximizar.
        -Si NO encuntra solucion: Arreglo vacio.
*/
std::vector<float> MIPSolver::solve(Simplex originalProblem)
{
    std::multimap<float, Simplex, std::greater<float>> heap;
    std::multimap<float, Simplex, std::greater<float>>::iterator currentItr;
    std::vector<float> currentSolution, solutionProblem1, solutionProblem2;
    float upperBound;
    int lowerBound, varIndex, e;
    currentSolution = originalProblem.solve();

    if(!currentSolution.empty())
    {
        upperBound = currentSolution[0];
        heap.emplace(upperBound, originalProblem);
    }

    while (!heap.empty())
    {
        currentItr = heap.begin();
        upperBound = currentItr->first;
        Simplex currentProblem = currentItr->second;
        currentSolution = currentProblem.getSolution();
        lowerBound = getLowerBound(currentProblem);
        heap.erase(currentItr);
        if ((float)lowerBound == upperBound)
        {
            return currentSolution;
        }

        varIndex = getFarthestIntegerVariable(currentSolution);
        e = (int) currentSolution[varIndex];
        Simplex copyProblem1 = currentProblem.copy();
        Simplex copyProblem2 = currentProblem.copy();
        copyProblem1.insertConstraint(e, varIndex, 1);
        copyProblem2.insertConstraint(e + 1, varIndex, 2);
        solutionProblem1 = copyProblem1.solve();
        solutionProblem2 = copyProblem2.solve();
        if(!solutionProblem1.empty())
        {
            heap.emplace(solutionProblem1[0], copyProblem1);
        }

        if(!solutionProblem2.empty())
        {
            heap.emplace(solutionProblem2[0], copyProblem2);
        }
    }
    
    std::vector<float> emptyVector;
    return emptyVector;
}

/*
    Metodo:
    Descripcion: este metodo obtiene el limite inferior de la
        solucion de un problema simplex, tomando la parte entera
        de los parametros para calcular la funcion maximizada con
        estos valores.
    Parametros:
        -problem: problema a calcular el limite inferior
    Retorno: limite inferior de la solucion, es decir la funcion
        maximizada con valores enteros de la solucion.
*/
int MIPSolver::getLowerBound(Simplex problem)
{
    int lowerBound = problem.initialA[0][0];
    std::vector<float> solution = problem.getSolution();
    for(size_t i = 1; i < solution.size(); i++)
    {
        lowerBound += problem.initialA[0][i] * (int) solution[i];
    }

    return lowerBound;
}

/*
    Metodo:
    Descripcion: este metodo obtiene el valor mas lejano a un entero,
        dado el vector solucion de un problema resuelto por Simplex. 
    Parametros:
        -solution: solucion del problema resuelto por Simplex
    Retorno: indice del valor mas lejano a un entero.
*/
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
