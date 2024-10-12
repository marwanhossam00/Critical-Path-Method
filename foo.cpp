#include <bits/stdc++.h>

using namespace std;

#define FASTIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define mem(nn) memset(nn, -1, sizeof nn)
#define all(v) v.begin(),v.end()
#define rep(i,a,b) for (int i = a; i <= b;i++)
#define ll long long int
#define pii pair<ll, ll>
#define pb push_back
#define ff first
#define ss second

struct Task{
    int id;
    int time;
    int in_deg, in_deg_rev;
    int es, ef, ls, lf;
    Task(){ es = 0; ef = 0; ls = 1e9; lf = 1e9; in_deg = 0; in_deg_rev = 0;}
};

int main(){
    FASTIO
    int n_tasks;  cin >> n_tasks;
    vector<Task> tasks(n_tasks+2);
    //It will work also in undirected graph settings
    vector<int> graph[n_tasks+2], rev_graph[n_tasks+2];
    vector<int> finish_dep;

    //Input
    rep(i, 1, n_tasks){
        Task _task;
        cin >> _task.id;
        cin >> _task.time;
        int n;  cin >> n;
        rep(j, 1, n){
            int x;  cin >> x;
            graph[x].pb(i);
            rev_graph[i].pb(x);
            tasks[i].in_deg++;
            tasks[x].in_deg_rev++;
        }
        tasks[i] = _task;
    }
    //Finish Dependencies
    int finish; cin >> finish;
    rep(i, 1, finish){
        int x;  cin >> x;
        finish_dep.pb(x);
        //Could be changed to undirected graph.
        graph[x].pb(n_tasks+1);
        rev_graph[n_tasks+1].pb(x);
    }
    tasks[n_tasks+1].id = n_tasks+1;

    queue<int> q;
    rep(i, 1, n_tasks){
        if(!tasks[i].in_deg){
            q.push(i);
            tasks[i].es = 0;
        }
    }
    vector<bool> vis(n_tasks+1, false);
    //BFS
    while(!q.empty()){
        int parent = q.front();
        q.pop();
        tasks[parent].ef = tasks[parent].es + tasks[parent].time;

        for(auto child: graph[parent]){
            tasks[child].in_deg--;
            tasks[child].es = max(tasks[parent].ef, tasks[child].es);
            if(!vis[child] && !tasks[child].in_deg){
                q.push(child);
                vis[child] = 1;
            }
        }
    }

    vis = vector<bool>(n_tasks+1, false);

    //Returning BFS
    for(auto x: finish_dep){
        if(!tasks[x].in_deg_rev){
            q.push(x);
            vis[x] = 1;
            tasks[x].lf = tasks[n_tasks+1].es;
        }
    }

    while(!q.empty()){
        int parent = q.front();
        q.pop();
        tasks[parent].ls = tasks[parent].lf - tasks[parent].time;

        for(auto child: rev_graph[parent]){
            tasks[child].in_deg_rev--;
            tasks[child].lf = min(tasks[child].lf, tasks[parent].ls);
            if(!vis[child] && !tasks[child].in_deg_rev){
                q.push(child);
                vis[child] = 1;
            }
        }
    }
    rep(i, 1, n_tasks+1){
        cout << "task " << tasks[i].id << '\n';
        cout << "es = " << tasks[i].es << '\n';
        cout << "ef = " << tasks[i].ef << '\n';
        cout << "ls = " << tasks[i].ls << '\n';
        cout << "lf = " << tasks[i].lf << '\n';
    }
}