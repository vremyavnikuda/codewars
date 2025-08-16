// #include <iostream>
// #include <vector>
// using namespace std;

// int main() {
//     int n_1;
//     cin >> n_1;
    
//     vector<int> a(n_1);
//     for (int i = 0; i < n_1; i++) {
//         cin >> a[i];
//     }
    
//     vector<int> vec_1;
//     int ex1 = 1;
    
//     for (int i = 1; i < n_1; i++) {
//         if (a[i] <= a[i-1]) {
//             vec_1.push_back(ex1);
//             ex1 = 1;
//         } else {
//             ex1++;
//         }
//     }
//     vec_1.push_back(ex1);
//     cout << vec_1.size() << endl;
//     for (int i = 0; i < vec_1.size(); i++) {
//         if (i > 0) cout << " ";
//         cout << vec_1[i];
//     }
//     cout << endl;
//     return 0;
// }
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n1;
    cin >> n1;
    vector<int> ex1;
    ex1.reserve(n1);
    
    int p1, cu1;
    cin >> p1;
    
    int c1 = 1;
    
    for (int i = 1; i < n1; i++) {
        cin >> cu1;
        
        if (cu1 <= p1) {
            ex1.push_back(c1);
            c1 = 1;
        } else {
            c1++;
        }
        p1 = cu1;
    }
    
    ex1.push_back(c1);
    
    cout << ex1.size() << '\n';
    
    for (size_t i = 0; i < ex1.size(); i++) {
        if (i > 0) cout << ' ';
        cout << ex1[i];
    }
    cout << '\n';
    
    return 0;
}