//
//  main.cpp
//  lixiang
//
//  Created by misok on 14-11-21.
//  Copyright (c) 2014年 misok. All rights reserved.
//

//input:pair pair int int int
//output:pair<pair<int,int>,int>;
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <string>
#include <map>
#include <vector>
#define MAXN 100010

using namespace std;

int m,n;
int a[MAXN];
map<string,int> id;
pair<pair<int,int>,int> cost[3*MAXN];
int sct=1;
pair<int,int> c[3*MAXN];
vector<int> e[3*MAXN];
bool vis[3*MAXN];

int get_id(string &s) {
    for (int i = 0; i < s.size(); i++)
    if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 'a'-'A';
    if (id[s]) return id[s];
    for (int i = 0; i < s.size(); i++)
    if (s[i] == 'r' || s[i] == 'R') cost[sct].first.first++;
    cost[sct].first.second = s.size();
    cost[sct].second = sct;
    return id[s] = sct++;
}

void dfs(int u) {
    vis[u] = 1;
    for (int i = 0; i < e[u].size(); i++) {
        if (!vis[e[u][i]]) {
            c[e[u][i]] = c[u];
            dfs(e[u][i]);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        a[i] = get_id(s);
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s,t;
        cin >> s >> t;
        int x = get_id(s), y = get_id(t);
        e[y].push_back(x);
    }
    sort(cost,cost+sct);
    for (int i = 0; i < sct; i++) {
        if (!vis[cost[i].second]) {
            c[cost[i].second] = cost[i].first;
            dfs(cost[i].second);
        }
    }
    long long ans1 = 0, ans2 = 0;
    for (int i = 0; i < m; i++) {
        ans1 += c[a[i]].first;
        ans2 += c[a[i]].second;
    }
    cout << ans1 << ' ' << ans2 << '\n';
}
