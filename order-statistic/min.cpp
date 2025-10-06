#include <iostream>
#include <vector>

int min(std::vector<int> a)
{
    int res = a[0];

    for (int i = 1; i < a.size(); i++)
    {
        if (a[i] < res)
            res = a[i];
    }
    return res;
}

void min_max(std::vector<int> a, int &min, int &max)
{
    int n = a.size();
    min = max = a[0];
    int start = 1;

    if (n % 2 == 0)
    {
        if (a[0] < a[1])
        {
            min = a[0];
            max = a[1];
        }
        else
        {
            min = a[1];
            max = a[0];
        }
        start = 2;
    }

    for (int i = start; i < n; i += 2)
    {
        int local_min, local_max;

        if (a[i] < a[i + 1])
        {
            local_min = a[i];
            local_max = a[i + 1];
        }
        else
        {
            local_max = a[i];
            local_min = a[i + 1];
        }

        if (min > local_min)
            min = local_min;
        if (max < local_max)
            max = local_max;
    }
}