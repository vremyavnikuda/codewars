// #include <bits/stdc++.h>
// using namespace std;

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int a;
//     if (!(cin >> a))
//         return 0;
//     vector<int> b(a + 1);
//     int c = -1;
//     for (int d = 1; d <= a; ++d)
//     {
//         cin >> b[d];
//         if (b[d] == 0)
//             c = d;
//     }
//     vector<long long> e(a + 1);
//     for (int d = 1; d <= a; ++d)
//         cin >> e[d];

//     vector<vector<int>> a_A(a + 1);
//     for (int d = 1; d <= a; ++d)
//         if (b[d] != 0)
//             a_A[b[d]].push_back(d);

//     vector<int> b_B(a + 1, -1), a_1(a + 1, -1), b_1;
//     b_1.reserve(a);
//     vector<int> c_1;
//     c_1.reserve(a);

//     vector<pair<int, int>> d_1;
//     d_1.reserve(a);
//     d_1.push_back({c, 0});
//     int e_1 = 0;
//     while (!d_1.empty())
//     {
//         auto [f, g] = d_1.back();
//         d_1.pop_back();
//         if (g == 0)
//         {
//             b_B[f] = e_1++;
//             d_1.push_back({f, 1});
//             for (int h : a_A[f])
//                 d_1.push_back({h, 0});
//         }
//         else
//         {
//             a_1[f] = e_1 - 1;
//             b_1.push_back(f);
//         }
//     }

//     vector<long long> c_A(a + 1, 0);
//     long long d_A = 0;
//     for (int f : b_1)
//     {
//         long long g = e[f];
//         for (int h : a_A[f])
//             g += c_A[h];
//         c_A[f] = g;
//     }
//     d_A = c_A[c];

//     if (d_A % 3 != 0)
//     {
//         cout << "NO\n";
//         return 0;
//     }
//     long long e_A = d_A / 3;
//     long long f_A = 2 * e_A;

//     vector<int> g_A(a);
//     for (int h = 1; h <= a; ++h)
//         g_A[b_B[h]] = h;

//     vector<int> h_A(a + 1, 0), i_A(a + 1, 0);
//     for (int h = 1; h <= a; ++h)
//     {
//         if (h != c && c_A[h] == e_A)
//             h_A[h] = 1;
//         if (h != c && c_A[h] == f_A)
//             i_A[h] = 1;
//     }

//     vector<int> j_A(a + 1, 0);
//     for (int h = 0; h < a; ++h)
//     {
//         int k = g_A[h];
//         j_A[h + 1] = j_A[h] + h_A[k];
//     }
//     auto k_A = [&](int h) -> int
//     {
//         int L = b_B[h], R = a_1[h];
//         return j_A[R + 1] - j_A[L];
//     };

//     int l_A = 0;
//     for (int h = 1; h <= a; ++h)
//         l_A += h_A[h];
//     bool m_A = false;
//     if (l_A >= 2)
//     {
//         for (int h = 1; h <= a && !m_A; ++h)
//             if (h_A[h])
//             {
//                 int inside = k_A(h);
//                 if (l_A - inside >= 1)
//                 {
//                     m_A = true;
//                     break;
//                 }
//             }
//     }

//     if (!m_A)
//     {
//         for (int h = 1; h <= a && !m_A; ++h)
//             if (i_A[h])
//             {
//                 int inside = k_A(h);
//                 if (c_A[h] == e_A)
//                     inside -= 1;
//                 if (inside >= 1)
//                 {
//                     m_A = true;
//                     break;
//                 }
//             }
//     }

//     cout << (m_A ? "YES\n" : "NO\n");
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

int a, b;
vector<int> c;
vector<long long> d, e;
vector<vector<int>> a_A;
long long b_B, a_1;
int b_1 = 0;
bool c_1 = false;

long long dfs(int f)
{
    long long g = d[f];
    for (int h_1 : a_A[f])
        g += dfs(h_1);
    e[f] = g;
    if (f != b)
    {
        if (g == a_1)
            b_1++;
        if (g == 2 * a_1 && b_1 > 0)
            c_1 = true;
    }
    return g;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a;
    c.resize(a + 1);
    d.resize(a + 1);
    a_A.resize(a + 1);

    for (int i_1 = 1; i_1 <= a; ++i_1)
    {
        cin >> c[i_1];
        if (c[i_1] == 0)
            b = i_1;
    }
    for (int i_1 = 1; i_1 <= a; ++i_1)
        cin >> d[i_1];
    for (int i_1 = 1; i_1 <= a; ++i_1)
        if (c[i_1] != 0)
            a_A[c[i_1]].push_back(i_1);

    e.assign(a + 1, 0);
    b_B = dfs(b);
    if (b_B % 3 != 0)
    {
        cout << "NO\n";
        return 0;
    }
    a_1 = b_B / 3;
    dfs(b);
    if (c_1 || b_1 >= 2)
        cout << "YES\n";
    else
        cout << "NO\n";
}
