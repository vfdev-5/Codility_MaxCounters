// STD
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

// Algorithm complexity should be O(N+A.size())
std::vector<int> MaxCounters(int N, const std::vector<int> & A)
{
    std::vector<int> out(N);

    std::vector<int>::const_iterator it = A.begin();
    int maxCounter=0;
    int totalMaxCounter = 0;
    long long flag = 0;
    for (;it!=A.end();++it)
    {
        int index = *it - 1;
        if (index == N)
        {
            totalMaxCounter += maxCounter;
            // reset
            flag = 0;
            maxCounter = 0;

        }
        else
        {

            if ((flag & (1 << index)) == 0)
            { // need reset
                out[index] = 0;
                flag |= (1 << index);
            }
            out[index]++;
            maxCounter = out[index] > maxCounter ? out[index] : maxCounter;
        }

    }

    for (int i=0;i<N;i++)
    {
        if ((flag & (1 << i)) == 0)
        { // need reset
            out[i] = 0;
            flag |= (1 << i);
        }
        out[i]+= totalMaxCounter;
    }

    return out;
}


// Algorithm complexity should be O(N*A.size())
std::vector<int> MaxCounters2(int N, const std::vector<int> & A)
{
    std::vector<int> out(N);

    std::vector<int>::const_iterator it = A.begin();
    int maxCounter=0;
    for (;it!=A.end();++it)
    {
        int index = *it - 1;
        if (index == N)
        {
            for (int i=0;i<N;i++)
            {
                out[i]= maxCounter;
            }
        }
        else
        {
            out[index]++;
            maxCounter = out[index] > maxCounter ? out[index] : maxCounter;
        }

    }
    return out;
}



int main()
{

    std::cout << "Max Counter problem" << std::endl;

    int N = 3;
    int M = 10;
    std::vector<int> A(M);
    int mco = 2;
    for (int i=0;i<M;i++)
    {
        int r = std::rand() % (N+1) + 1;
        A[i] = r;
        if (r == N+1) mco++;
        std::cout << r << std::endl;
    }
    A.push_back(N+1);
    A.push_back(N+1);
    std::cout << "max counter ops = " << mco << std::endl;


    std::vector<int> out = MaxCounters(N, A);
    std::vector<int> out2 = MaxCounters2(N, A);

    if (out.size() != out2.size())
    {
        std::cerr << "Sizes are not equal !!!" << std::endl;
        return 1;
    }

    double diff = 0.0;
    for (int i=0; i<out.size();i++)
    {
        diff += std::abs(out[i] - out2[i]);
    }
//    if (diff > 1e-5)
//    {
//        std::cerr << "Results are not equal !!!" << std::endl;
        std::cout << "Outputs : " << std::endl;

        for (int i=0;i<out.size();i++)
        {
            std::cout << out[i] << " <-> " << out2[i] << std::endl;
        }
//        return 1;
//    }

    std::cout << "diff = " << diff << std::endl;
    return 0;
}

