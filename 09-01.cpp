#include <iostream>
#include <algorithm>

using namespace std;

void count_enum(int t, int p, int u, int s, int e)
{
    int count = e / t + 1, n_s = -1, n_p = -1, n_u = -1, n_t = -1;
    for (int num_s = 0; num_s <= e / s; num_s++)
    {
        for (int num_u = 0; num_u <= (e - num_s * s) / u; num_u++)
        {
            for (int num_p = 0; num_p <= (e - num_s * s - num_u * u) / p; num_p++)
            {
                for (int num_t = 0; num_t <= (e - num_s * s - num_u * u - num_p * p) / t; num_t++)
                {
                    if (num_s * s + num_u * u + num_p * p + num_t * t == e)
                    {
                        if (num_s + num_u + num_p + num_t < count)
                        {
                            count = num_s + num_u + num_p + num_t;
                            n_s = num_s;
                            n_p = num_p;
                            n_u = num_u;
                            n_t = num_t;
                        }
                    }
                }
            }
        }
    }
    if (n_s == -1 || n_p == -1 || n_u == -1 || n_t == -1)
    {
        cout << "no";
    }
    else
        cout << "s " << n_s << " u " << n_u << " p " << n_p << " t " << n_t;
}

struct Wave
{
    int omega, k;
};

bool operator<(Wave const &lha, Wave const &rha)
{
    return lha.omega < rha.omega;
}

bool operator==(Wave const &lha, Wave const &rha)
{
    return lha.omega == rha.omega && lha.k == rha.k;
}

int bin(Wave* a, int n, Wave val){
    int l=0, r = n-1;
    while (r>l){
        int m = (r+l)/2;
        if (a[m] < val) {
            l = m+1;
        }
        else if (val < a[m]){
            r = m - 1;
        }
        else return m;
    }
    if (a[l] == val){
        return l;
    }
    else return -1;
}

void find_pare(){
    int n;
    cin >> n;
    Wave *waves = new Wave[n];
    for (int i = 0; i < n; i++)
    {
        cin >> waves[i].omega >> waves[i].k;
    }
    sort(waves, waves + n);
    int w0, k0;
    int n_1=-1, n_2=-1;
    cin >> w0 >> k0;
    for (int i = 0; i < n; i++)
    {
        Wave  w = {w0 - waves[i].omega, k0 - waves[i].k};
        int num_2 = bin(&waves[i], n-i, w);
        if (num_2>=0) {n_1 = i+1; n_2 = num_2+1;}
        
    }
    if (n_2>=0) {cout << n_1 << " "<< n_2;}
    else cout << "no";
} 

int* count_din(int* coins, int const n, int e){
    sort(coins, coins+n);
    int coin_0 = *coins;
    int size = e;
    int** best_way = new int*[size+1];
    for (int i = 0; i <= size; i++)
        best_way[i] = new int [n+1];
    for (int i=0;i<=size;i++){
        for (int j=0;j<n;j++){
            best_way[i][j]=0;
        }
        best_way[i][n]=-1;
    }
    best_way[0][n]=0;

    for (int i=coin_0;i<=size;i++){
        int j = 0;
        int qua = i, num = -1;
        while (j<n && (i-coins[j]>=0)){
            int cur_coin = coins[j];
            if (best_way[i-cur_coin][n]>=0){
                if (best_way[i-cur_coin][n]<=qua){
                    qua = best_way[i-cur_coin][n];
                    num = j;
                }
            }
            j++;
        }
        if (num>=0){
            for (int j=0;j<=n;j++){
                best_way[i][j] = best_way[i-coins[num]][j];
            }
            best_way[i][num]++;
            best_way[i][n]++;
        }
    }
    return best_way[e];
}

int delta(int *a, int n, int m_1, int m_2, int& min)
{
    if (n > 0)
    {
        int cur = *a;
        delta(a+1, n - 1, m_1 + cur, m_2, min);
        delta(a+1, n - 1, m_1, m_2 + cur, min);
    }
    else
    {
        if (abs(m_2 - m_1)<min) min=abs(m_2 - m_1);
    }
    return min;
}

int main()
{
    //перебор 4 монеток
    /*int t, p, u, s, e;
    cin >> t >> p >> u >> s >> e;
    count_enum(t, p, u, s, e);*/

    //поиск возможной пары
    //find_pare();

    //динамика монеток
    /*int n; cin >> n;
    int* coins = new int[n];
    for (int i=0;i<n;i++){
        cin>>coins[i];
    }
    int e; cin >> e;
    
    int* res = count_din(coins, n, e);
    for (int i=0;i<n;i++){
        cout << res[i]<< " ";
    }
    delete[] coins; delete[] res;*/

    //распределeние на кучки
    int n; cin >> n;
    int* a = new int[n];
    int min=0;
    for (int i=0;i<n;i++){
        cin>>a[i]; min+=a[i];
    }
    int delt = delta(a, n, 0, 0, min);
    cout << min;
    delete[] a;
    return 0;
}
//написать динамику для неканонического разложения + разделение на кучки с мин разностью