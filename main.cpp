#include "MIPSolver.h"
#include <ctime>

int main()
{
    clock_t ti, tf;
    double dt = 0;
    MIPSolver solver;
    std::string fileName;
    std::cout << "Solucionador de problemas de programacion lineal entera" << std::endl;
    std::cout << "Ingrese el nombre del archivo que contiene la matriz que representa el problema: ";
    std::cin >> fileName;

    Simplex simplex = Simplex(fileName);
    ti = clock();
    std::vector<float> solution = solver.solve(simplex);
    tf = clock();
    dt = (tf - ti) / (double)CLOCKS_PER_SEC;

    if(solution.size() == 0)
    {
        std::cout << "El problema no tiene solucion con parametros enteros" << std::endl;
    }
    else
    {
        std::cout << "La solucion del problema es:" << std::endl;
        std::cout << "Valor maximizado: " << solution[0] << std::endl; 
        for (size_t i = 1; i < solution.size(); i++)
        {
            std::cout << "x" << i << ": " << solution[i] << std::endl;
        }
        std::cout << std::endl;
    }


    std::cout << "Tiempo de ejecucion: " << dt << " segundos" << std::endl;
}
