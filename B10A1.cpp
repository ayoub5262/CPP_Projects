#include <iostream>
#include <algorithm>
#include <list>
#include <cassert>

struct Activity
{
    int s;
    int e;
};

bool compareActivity(const Activity &a, const Activity &b)
{
    /**********************************************************/
    /**** Langaufgabe 10.1: ****/
    return a.e < b.e;
    /**********************************************************/
}

void activitySelection(std::list<Activity> &list, Activity arr[], int n)
{
    /**********************************************************/
    /**** Langaufgabe 10.1: ****/
    std::sort(arr, arr + n, compareActivity);
    list.push_back(arr[0]);
    int last_end_time = arr[0].e;
    for (int i = 1; i < n; i++){
        if (arr[i].s >= last_end_time){
            list.push_back(arr[i]);
            last_end_time = arr[i].e;
        }
    }
    /**********************************************************/
}

int main()
{
    int n;
    std::cin >> n;
    assert(n > 0);

    Activity *arr = new Activity[n];

    for (int i = 0; i < n; i++){
        int s, e;
        std::cin >> s >> e;
        arr[i] = {s, e};
    }

    std::list<Activity> list;
    activitySelection(list, arr, n);

    std::cout << "Maximale Anzahl: " << list.size() << std::endl;
    std::cout << "Zeitplan: ";

    for (Activity act : list)
        std::cout << "(" << act.s << ", " << act.e << ") ";
    std::cout << std::endl;

    delete[] arr;
    return 0;
}