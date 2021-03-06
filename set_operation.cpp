#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    std::vector<int> v1{ 1,2,3,4,5,6,7,8,9,10 };
    std::vector<int> v2{ 1, 5,  7,  9,10 };

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    // intersection set
    std::vector<int> v_intersection;
    std::vector<int> v_difference;
    std::vector<int> v_union;
    std::set_intersection(v1.begin(), v1.end(),v2.begin(), v2.end(),std::back_inserter(v_intersection));
    std::set_union(v1.begin(), v1.end(),v2.begin(), v2.end(),std::back_inserter(v_union));
    std::set_difference(v1.begin(), v1.end(),v2.begin(), v2.end(),std::back_inserter(v_difference));
    
    // for(int i=0;i<v_intersection.size();i++)
    // 	cout<<v_intersection[i]<<" ";
    // cout<<endl;
    return 0;
}
