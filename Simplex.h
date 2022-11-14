#include <iostream>
#include <vector>
#include <string>
#define EPS 1.0e-6

class Simplex
{
private:
    int m;
    int n;
    int simplx();
    void simp1(int mm, std::vector<int> ll, int nll, int iabf, int *kp, float *bmax);
    void simp2(int *ip, int kp);
    void simp3(int i1, int k1, int ip, int kp);
    double fabs(double x);

public:
    std::vector<std::vector<float>> a;
    int m1; // numero de restricciones <=
    int m2; // ... >=
    int m3; // igualdad
    std::vector<int> izrov;
    std::vector<int> iposv;

    Simplex(std::vector<std::vector<float>> a, int m1, int m2, int m3);
    ~Simplex();
    void solve();
    void insertConstraint(float b, int var, int type);
    Simplex *copy();
    void printA();
};
