#include "Simplex.h"

Simplex::Simplex(std::vector<std::vector<float>> a, int m1, int m2, int m3)
{
    this->a = a;
    this->m1 = m1;
    this->m2 = m2;
    this->m3 = m3;
    this->m = m1 + m2 + m3;
    this->n = a[0].size() - 1;
}

Simplex::~Simplex()
{
}

void Simplex::solve()
{
    int icase, nm1m2;
    icase = simplx();
    if (icase == 1)
    {
        printf("\nunbounded objective function\n");
    }
    else if (icase == -1)
    {
        printf("\nno solutions satisfy constraints given\n");
    }
    else
    {
        nm1m2 = n + m1 + m2;
        char txt[nm1m2][4] =
            {"x1", "x2", "x3", "x4", "y1", "y2", "y3"}; // Cambiar
        printf("\n%11s", " ");
        for (int i = 0; i < n; i++)
        {
            if (izrov[i] < nm1m2)
            {
                printf("%10s", txt[izrov[i]]);
            }
        }

        printf("\n");
        for (int i = 0; i < m + 1; i++)
        {
            if (i == 0 || iposv[i - 1] < nm1m2)
            {
                if (i > 0)
                {
                    printf("%s", txt[iposv[i - 1]]);
                }
                else
                {
                    printf("  ");
                }

                printf("%10.2f", a[i][0]);
                for (int j = 1; j < n + 1; j++)
                {
                    if (izrov[j - 1] < nm1m2)
                    {
                        printf("%10.2f", a[i][j]);
                    }
                }

                printf("\n");
            }
        }
    }
}

int Simplex::simplx()
{
    int i, ip, is, k, kh, kp, nl1;
    float q1, bmax;
    std::cout << "s1" << std::endl;
    std::vector<int> l1;
    std::vector<int> l3;
    nl1 = n;
    for (k = 0; k < n; k++)
    {
        l1.push_back(k);
        izrov.push_back(k);
    }
    std::cout << "s2" << std::endl;
    for (i = 0; i < m; i++)
    {
        if (a[i + 1][0] < 0.0) // Borrar esto y verificar en constructor
        {
            // nrerror("Bad input tableau in simplx");
            std::cout << "Bad input tableau in simplx" << std::endl;
            return -2;
        }
        iposv.push_back(n + i);
    }
    std::cout << "s3" << std::endl;
    if (m2 + m3)
    {
        std::cout << "if.1" << std::endl;
        for (i = 0; i < m2; i++)
        {
            l3.push_back(1);
        }
        std::cout << "if.2" << std::endl;
        for (k = 0; k < n + 1; k++)
        {
            q1 = 0.0;
            for (i = m1; i < m; i++)
            {
                q1 += a[i + 1][k];
            }
            a[m + 1][k] = -q1; // m + 1 -> m + 2 (?
        }
        printA();
        std::cout << "if.3" << std::endl;
        bool p = true;
        for (;;)
        {
            if(p) std::cout << "if.3.for.1" << std::endl;
            simp1(m + 1, l1, nl1, 0, &kp, &bmax);
            if(p) std::cout << "if.3.for.2" << std::endl;
            if (bmax <= EPS && a[m + 1][0] < -EPS) // m + 1 -> m + 2 (?
            {
                return -1; // icase -1
            }
            else if (bmax <= EPS && a[m + 1][0] <= EPS) // m + 1 -> m + 2 (?
            {
                if(p)std::cout << "if.3.for.3" << std::endl;
                for (ip = m1 + m2; ip < m; ip++)
                {
                    if (iposv[ip] == ip + n)
                    {
                        simp1(ip, l1, nl1, 1, &kp, &bmax);
                        if (bmax > EPS)
                        {
                            goto one;
                        }
                    }
                }
                if(p)std::cout << "if.3.for.4" << std::endl;
                for (i = m1; i < m1 + m2; i++)
                {
                    if (l3[i - m1] == 1)
                    {
                        for (k = 0; k < n + 1; k++)
                        {
                            a[i + 1][k] = -a[i + 1][k];
                        }
                    }
                }
                if (p)printA();
                if(p)std::cout << "if.3.for.5" << std::endl;
                break;
            }
            simp2(&ip, kp);
            if(p)std::cout << "if.3.for.6" << std::endl;
            if (ip == -1)
            {
                return -1; // icase -1
            }
        one:
            if(p)std::cout << "if.3.for.7" << std::endl;
            simp3(m + 1, n, ip, kp);
            if (p)printA();
            if(p)std::cout << "if.3.for.8" << std::endl;
            if (iposv[ip] >= (n + m1 + m2)) // n + m1 + m2 |->| n + m1 + m2 + 1
            {
                if(p)std::cout << "if.3.for.9" << std::endl;
                for (k = 0; k < nl1; k++)
                {
                    if (l1[k] == kp)
                    {
                        break;
                    }
                }
                if(p)std::cout << "if.3.for.10" << std::endl;
                --nl1;
                for (is = k; is < nl1; is++)
                {
                    l1[is] = l1[is + 1];
                }
                if(p)std::cout << "if.3.for.11" << std::endl;
            }
            else
            {
                if(p)std::cout << "if.3.for.12" << std::endl;
                kh = iposv[ip] - m1 - n;
                if (kh >= 0 && l3[kh]) // kh >= 0 |->| kh >= 1
                {
                    l3[kh] = 0;
                    ++a[m + 1][kp + 1];          // m + 1 -> m + 2 (?
                    for (i = 0; i < m + 2; i++) // m + 1 -> m + 2 (?
                    {
                        a[i][kp + 1] = -a[i][kp + 1];
                    }
                }
                if (p)printA();
                if(p)std::cout << "if.3.for.13" << std::endl;
            }
            is = izrov[kp];
            izrov[kp] = iposv[ip];
            iposv[ip] = is;
            // p = false;
        }
        std::cout << "if.4" << std::endl;
    }
    std::cout << "s4" << std::endl;
    for (;;)
    {
        std::cout << "for2.1" << std::endl;
        simp1(0, l1, nl1, 0, &kp, &bmax);
        if (bmax <= EPS)
        {
            return 0; // icase = 0
        }
        std::cout << "for2.2" << std::endl;
        simp2(&ip, kp);
        if (ip == -1)
        {
            return 1; // icase  = 1
        }
        std::cout << "for2.3" << std::endl;
        simp3(m, n, ip, kp);
        printA();
        is = izrov[kp];
        izrov[kp] = iposv[ip];
        iposv[ip] = is;
        std::cout << "for2.4" << std::endl;
    }
}

void Simplex::simp1(int mm, std::vector<int> ll, int nll, int iabf, int *kp, float *bmax)
{
    int k;
    float test;

    if (nll <= 0) // <=  ->   < (?
    {
        *bmax = 0.0;
    }
    else
    {
        *kp = ll[0];
        *bmax = a[mm][*kp + 1]; // kp + 1 -> kp (?
        for (k = 1; k < nll; k++)
        {
            if (iabf == 0)
            {
                test = a[mm][ll[k] + 1] - (*bmax); // ll[k] + 1 -> ll[k] (?
            }
            else
            {
                test = fabs(a[mm][ll[k]] + 1) - fabs(*bmax); // ll[k] + 1 -> ll[k] (?
            }
            if (test > 0.0)
            {
                *bmax = a[mm][ll[k] + 1]; // ll[k] + 1 -> ll[k] (?
                *kp = ll[k];
            }
        }
    }
}

void Simplex::simp2(int *ip, int kp)
{

    int k, i;
    float qp, q0, q, q1;

    kp = kp + 1; // kp + 1 (?
    *ip = -1;     // ip = 0 -> ip = -1 y verificar en solve simplx
    for (i = 0; i < m; i++)
    {
        if (a[i + 1][kp] < -EPS)
        {
            break;
        }
    }

    if (i > m) // i >= m   ->  i > m   ||  -> i + 1 > m
    {
        return;
    }

    q1 = -a[i + 1][0] / a[i + 1][kp];
    *ip = i;
    for (i = *ip + 1; i < m; i++)
    {
        if (a[i + 1][kp] < -EPS)
        {
            q = -a[i + 1][0] / a[i + 1][kp];
            if (q < q1)
            {
                *ip = i;
                q1 = q;
            }
            else if (q == q1)
            {
                for (k = 0; k < n; k++)
                {
                    qp = -a[*ip + 1][k + 1] / a[*ip + 1][kp];
                    q0 = -a[i + 1][k + 1] / a[i + 1][kp];
                    if (q0 != qp)
                    {
                        break;
                    }
                }
                if (q0 < qp)
                {
                    *ip = i;
                }
            }
        }
    }
}

void Simplex::simp3(int i1, int k1, int ip, int kp)
{
    int kk, ii;
    float piv;

    piv = 1.0 / a[ip + 1][kp + 1];
    for (ii = 0; ii < i1 + 1; ii++)
    {
        if (ii - 1 != ip)
        {
            a[ii][kp + 1] *= piv;
            for (kk = 0; kk < k1 + 1; kk++)
            {
                if (kk - 1 != kp)
                {
                    a[ii][kk] -= a[ip + 1][kk] * a[ii][kp + 1];
                }
            }
        }
    }

    for (kk = 0; kk < k1 + 1; kk++)
    {
        if (kk - 1 != kp)
        {
            a[ip + 1][kk] *= -piv;
        }
    }

    a[ip + 1][kp + 1] = piv;
}

double Simplex::fabs(double x)
{
    if (x < 0.0)
    {
        return x * -1;
    }

    return x;
}

void Simplex::printA()
{
    for (std::size_t i = 0; i < a.size(); i++)
    {
        for (std::size_t j = 0; j < a[0].size(); j++)
        {
            printf("%10.2f", a[i][j]);
        }
        printf("\n");
    }
}