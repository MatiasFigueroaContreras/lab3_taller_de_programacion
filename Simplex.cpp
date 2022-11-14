#include "Simplex.h"

Simplex::Simplex(std::vector<std::vector<float>> a, int m1, int m2, int m3)
{
    int m = m1 + m2 + m3;
    for(int i = 0; i < m; i++)
    {
        if (a[i + 1][0] < 0.0)
        {
            throw std::invalid_argument("Bad input tableau");
        }
    }

    this->a = a;
    this->m1 = m1;
    this->m2 = m2;
    this->m3 = m3;
    this->m = m;
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
        std::cout << std::endl << "unbounded objective function" << std::endl;
    }
    else if (icase == -1)
    {
        std::cout << std::endl << "no solutions satisfy constraints given" << std::endl;
    }
    else
    {
        nm1m2 = n + m1 + m2;
        std::string txt[nm1m2];
        for(int i = 0; i < n; i++)
        {
            txt[i] = "x" + std::to_string(i + 1);
        }
        for(int i = n; i < nm1m2; i++)
        {
            txt[i] = "y" + std::to_string(i + 1 - n);
        }

        std::cout << std::string(11, ' ');
        for (int i = 0; i < n; i++)
        {
            if (izrov[i] < nm1m2)
            {
                txt[izrov[i]].insert(txt[izrov[i]].begin(), 10 - txt[izrov[i]].length(), ' ');
                std::cout << txt[izrov[i]];
            }
        }

        std::cout << std::endl;
        for (int i = 0; i < m + 1; i++)
        {
            if (i == 0 || iposv[i - 1] < nm1m2)
            {
                if (i > 0)
                {
                    std::cout << txt[iposv[i - 1]];
                }
                else
                {
                    std::cout << "  ";
                }

                std::string ai0 = std::to_string(a[i][0]);
                ai0 = ai0.substr(0, ai0.find(".")+3);
                ai0.insert(ai0.begin(), 10 - ai0.length(), ' ');
                std::cout << ai0;
                for (int j = 1; j < n + 1; j++)
                {
                    if (izrov[j - 1] < nm1m2)
                    {
                        std::string aij = std::to_string(a[i][j]);
                        aij = aij.substr(0, aij.find(".") + 3);
                        aij.insert(aij.begin(), 10 - aij.length(), ' ');
                        std::cout << aij;
                    }
                }
                std::cout << std::endl;
            }
        }
    }
}

int Simplex::simplx()
{
    int i, ip, is, k, kh, kp, nl1;
    float q1, bmax;
    std::vector<int> l1;
    std::vector<int> l3;
    nl1 = n;
    for (k = 0; k < n; k++)
    {
        l1.push_back(k);
        izrov.push_back(k);
    }
    for (i = 0; i < m; i++)
    {
        iposv.push_back(n + i);
    }

    if (m2 + m3)
    {
        for (i = 0; i < m2; i++)
        {
            l3.push_back(1);
        }
        for (k = 0; k < n + 1; k++)
        {
            q1 = 0.0;
            for (i = m1; i < m; i++)
            {
                q1 += a[i + 1][k];
            }
            a[m + 1][k] = -q1; // m + 1 -> m + 2 (?
        }

        for (;;)
        {
            simp1(m + 1, l1, nl1, 0, &kp, &bmax);
            if (bmax <= EPS && a[m + 1][0] < -EPS) // m + 1 -> m + 2 (?
            {
                return -1; // icase -1
            }
            else if (bmax <= EPS && a[m + 1][0] <= EPS) // m + 1 -> m + 2 (?
            {
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
                break;
            }
            simp2(&ip, kp);
            if (ip == -1)
            {
                return -1; // icase -1
            }
        one:
            simp3(m + 1, n, ip, kp);
            if (iposv[ip] >= (n + m1 + m2)) // n + m1 + m2 |->| n + m1 + m2 + 1
            {
                for (k = 0; k < nl1; k++)
                {
                    if (l1[k] == kp)
                    {
                        break;
                    }
                }

                --nl1;
                for (is = k; is < nl1; is++)
                {
                    l1[is] = l1[is + 1];
                }
            }
            else
            {
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
            }
            is = izrov[kp];
            izrov[kp] = iposv[ip];
            iposv[ip] = is;
        }
    }

    for (;;)
    {
        simp1(0, l1, nl1, 0, &kp, &bmax);
        if (bmax <= EPS)
        {
            return 0; // icase = 0
        }

        simp2(&ip, kp);
        if (ip == -1)
        {
            return 1; // icase  = 1
        }

        simp3(m, n, ip, kp);
        is = izrov[kp];
        izrov[kp] = iposv[ip];
        iposv[ip] = is;
    }
}

void Simplex::simp1(int mm, std::vector<int> ll, int nll, int iabf, int *kp, float *bmax)
{
    int k;
    float test;

    if (nll <= 0)
    {
        *bmax = 0.0;
    }
    else
    {
        *kp = ll[0];
        *bmax = a[mm][*kp + 1];
        for (k = 1; k < nll; k++)
        {
            if (iabf == 0)
            {
                test = a[mm][ll[k] + 1] - (*bmax);
            }
            else
            {
                test = fabs(a[mm][ll[k]] + 1) - fabs(*bmax);
            }
            if (test > 0.0)
            {
                *bmax = a[mm][ll[k] + 1];
                *kp = ll[k];
            }
        }
    }
}

void Simplex::simp2(int *ip, int kp)
{

    int k, i;
    float qp, q0, q, q1;

    kp = kp + 1;
    *ip = -1;
    for (i = 0; i < m; i++)
    {
        if (a[i + 1][kp] < -EPS)
        {
            break;
        }
    }

    if (i > m)
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

void Simplex::insertConstraint(float b, int var, int type)
{
    std::vector<float> constraint (this->a[0].size(), 0.0);
    constraint[0] = b;
    constraint[var] = -1.0; // ?
    switch (type)
    {
    case 1:
        this->a.insert(this->a.begin() + m1 + 1, constraint);
        break;
    case 2:
        this->a.insert(this->a.begin() + m1 + m2 + 1, constraint);
        break;
    case 3:
        this->a.insert(this->a.end() + m + 1, constraint);
        break;
    default:
        break;
    }
}

Simplex *Simplex::copy()
{
    Simplex *s = new Simplex(a, m1, m2, m3);
    s->izrov = this->izrov;
    s->iposv = this->iposv;
    return s;
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