#include "Automat.hpp"

istream& operator>> (istream& in, Automat& ob){
    int m;
    in >> ob.nrStates >> m;
    ob.transitions.resize(ob.nrStates, vector <vector <int> > (ob.SZ));
    ob.transitionsInv.resize(ob.nrStates, vector <vector <int> > (ob.SZ));
    for (int i=0; i<m; i++){
        int x, y; char c;
        in >> x >> y >> c;
        ob.transitions[x][c - 'a'].push_back(y);
        ob.transitionsInv[y][c - 'a'].push_back(x);
    }
    in >> ob.initialState;
    in >> m; //number of final states
    ob.finalStates.resize(ob.nrStates + 1, 0);
    ob.isUseless.resize(ob.nrStates + 1, 0);
    for (int i=0; i<m; i++){
        int x;
        in >> x;
        ob.finalStates[x] = 1;
    }
    ob.removeUselessStates();
    return in;
}

void Automat::removeUselessStates(){
    queue <int> Q;
    for (int i=0; i < nrStates; i++){
        if (finalStates[i]) Q.push(i), isUseless[i] = 1;
    }
    while (!Q.empty()){
        int nod = Q.front();
        Q.pop();
        for (char c='a'; c<='z'; c++){
            for (int &it: transitionsInv[nod][c - 'a']){
                if (!isUseless[it]) Q.push(it), isUseless[it] = 1;
            }
        }
    }
    for (int i=0; i < nrStates; i++) isUseless[i] = !isUseless[i];
}

bool Automat::isAccepted(string& word, int nod, int idx) {
    if (idx == (int) word.length()) return finalStates[nod];
    if (!transitions[nod][word[idx] - 'a'].size()) return 0;
    for (int &it: transitions[nod][word[idx] - 'a']){
        if (isUseless[it]) continue;
        if (badStates[{it, idx + 2}]) continue;
        if (isAccepted(word, it, idx + 1)) return 1;
    }
    badStates[{nod, idx + 1}] = 1;
    return 0;
}

void Automat::firstWords(vector <string>& v, int n)const{
    queue < pair <int, string> > Q;
    unordered_set <string> S;
    Q.push({initialState, ""});
    while ((int) S.size() < n && !Q.empty()){
        pair <int, string> curr = Q.front();
        Q.pop();
        for (char c='a'; c <= 'z'; c++){
            for (const int &it: transitions[curr.first][c - 'a']){
                if (isUseless[it]) continue;
                if ((int) S.size() < n && finalStates[it]) S.insert(curr.second + c);
                Q.push({it, curr.second + c});
            }
        }
    }
    for (string it: S) v.push_back(it);
    sort(v.begin(), v.end(), [&](const string& unu, const string& doi){
        if (unu.length() == doi.length()){
            for (size_t i=0; i<unu.length(); i++){
                if (unu[i] == doi[i]) continue;
                return unu[i] < doi[i];
            }
        }
        return unu.length() < doi.length();
    });
}