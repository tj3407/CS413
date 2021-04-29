#include <iostream>
#include <vector>
using namespace std;

void printVect(vector<int> s) {
    for (int i = 0; i < s.size(); i++)
        cout << s[i] << " ";
    cout << endl;
}

// add all the elements of w to v (append w to v).
void  append(vector<vector<int>>& v, const vector<vector<int>>& w) {
    for (int i = 0; i < w.size(); i++)
        v.push_back(w[i]);
}

// insert c into every possible position of s to create a list of new vectors.
vector<vector<int>> makeVects(int c, vector<int> s) {
    vector<vector<int>> temp;
    for (int i = 0; i <= s.size(); i++) {
        vector<int> t = s;
        vector<int>::iterator it = t.begin();
        t.insert(it + i,c);  // insert c at intex i into t
        temp.push_back(t);  // add this vector to the list
    }
    return temp;  // temp contains all the vectors formed by inserting c at any position of s
}

// Starting from the original vector s, make a list of vectors containing every permutation of s.
// For example if s is [0,1,2] then the return vector
// will be [ [ 2 1 0] [1 2 0] [1 0 2] [2 0 1] [0 2 1] [0 1 2] ].
// The order of the elements is unimportant, we just need all six permutation to appear.
vector<vector<int>> makeAll(vector<int> s) {
    vector<vector<int>> temp;
    if (s.empty()) { temp.push_back(s); return temp; }
    int c = s.back();
    vector<int> rest = s;
    rest.pop_back();
    temp = makeAll(rest);
    vector<vector<int>> result;
    for (int i = 0; i < temp.size(); i++)  
        append(result, makeVects(c, temp[i]));
    return result;
}

// return true if there is an edge from vertex v to vertex w
bool isEdge(vector<int> alists[], int v, int w) {
    // FILL IN
    for (int i = 0; i < alists[v].size(); i++) {
        if (alists[v][i] == w) {
            return true;
        }
    }

    return false;
}

// f is a permutation array meaning indexes from the set {0,...size-1}
// f represents a bijection from the vertices of the first graph to the vertices of the second graph.
// We want to check if f preserves edges such that if there's an edge from v to w in the first graph.
// then there will be an edge from f[v] to f[w] in the second graph.
// g represents the inverse mapping from vertices of the second graph to vertices of the first graph.
// We also need to check that an edge from v to w in the second graph will correspond to an edge from
// g[v] to g[w] in the first graph.
bool isIsomorphism(vector<int> alists[], vector<int> blists[], vector<int> f, int size)
{
    for (int u = 0; u < size; u++) {
        // FILL IN
        for (int v = 0; v < alists[u].size(); v++) {
            int alistElement = alists[u][v];
            if (!isEdge(blists, f[u], f[alistElement])) {
                return true;
            }
        }
    }
    vector<int> g(f.size());
    for (int i = 0; i < size; i++) {
      g[f[i]] = i; // g is the inverse function of f
    }
    for (int u = 0; u < size; u++) {
        // FILL IN
        for (int v = 0; v < blists[u].size(); v++) {
            int blistElement = blists[u][v];
            if (!isEdge(alists, g[u], g[blistElement])) {
                return true;
            }
        }
    }
    return false;
}

bool areIsomorphic(vector<int> alists[], vector<int> blists[], int size, vector<int> & f) {
    f = vector<int>(); // f will be set to the permutation that worked if an isomorphism is found
    vector<int> sequence;
    for (int i = 0; i < size; i++) sequence.push_back(i);
    vector<vector<int>> perms = makeAll(sequence);
    // FILL IN
    // (Loop through perms and call isIsomorphism with perms[i] as the third argument.)
    for (int i = 0; i < perms.size(); i++) {
        if (!isIsomorphism(alists, blists, perms[i], size)) {
            return false;
        }
    }
    return true;
}

int main()
{
    vector<int> perm;

    vector<int> plists[10] = { {5,7,8},{2,5,6}, {1,3,7}, {2,4,8}, {3,5,9}, {0,1,4}, {1,8,9}, {0,2,9}, {0,3,6}, {4,6,7} };
    
    vector<int> qlists[10] = { {7,8,9},{2,6,9}, {1,3,8}, {2,4,7}, {3,5,9}, {4,6,8}, {1,5,7}, {0,3,6}, {0,2,5}, {0,1,4} };

    vector<int> rlists[10] = { {7,8,9},{2,6,8}, {1,3,9}, {2,4,7}, {3,5,9}, {4,6,8}, {1,5,7}, {0,3,6}, {0,1,5}, {0,2,4} };

    if (areIsomorphic(plists, qlists, 10, perm)) {
        cout << "p and q are isomorphic with f = ";
        printVect(perm);
    }
    else cout << "p and q are not isomorphic." << endl;
    if (areIsomorphic(plists, rlists, 10, perm)) {
        cout << "p and r are isomorphic with f = ";
        printVect(perm);
    }
    else cout << "p and r are not isomorphic." << endl;
    if (areIsomorphic(qlists, rlists, 10, perm)) {
        cout << "q and r are isomorphic with f = ";
        printVect(perm);
    }
    else cout << "q and r are not isomorphic." << endl;


    vector<int> slists[8] = { {1,3,7},{0,2,6}, {1,3,5}, {0,2,4}, {3,5,7}, {2,4,6}, {1,5,7}, {0,4,6} };

    vector<int> tlists[8] = { {1,2,7},{0,2,4}, {0,1,3}, {2,4,6}, {1,3,5}, {4,6,7}, {3,5,7}, {0,5,6} };

    vector<int> ulists[8] = { {1,2,7},{0,2,5}, {0,1,3}, {2,4,7}, {3,5,6}, {1,4,6}, {4,5,7}, {0,3,6} };

    cout << endl;
    
    if (areIsomorphic(slists, tlists, 8, perm)) {
        cout << "s and t are isomorphic with f = ";
        printVect(perm);
    }
    else cout << "s and t are not isomorphic." << endl;

    if (areIsomorphic(slists, ulists, 8, perm)) {
        cout << "s and u are isomorphic with f = ";
        printVect(perm);
    }
    else cout << "s and u are not isomorphic." << endl;

    if (areIsomorphic(tlists, ulists, 8, perm)) {
        cout << "t and u are isomorphic with f = ";
        printVect(perm);
    }
    else cout << "t and u are not isomorphic." << endl;
}