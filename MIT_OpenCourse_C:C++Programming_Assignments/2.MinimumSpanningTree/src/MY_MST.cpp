#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class State {
private:
  size_t _node;
  double _dist;

public:
  State(size_t Node, double Dist) : _node(Node), _dist(Dist) {}
  size_t node() const { return _node; }
  double dist() const { return _dist; }
};

class AjecentList {
private:
  vector<vector<State>> _adj;
  AjecentList() = delete;

public:
  AjecentList(istream &input);
  const vector<State> &adj(size_t node) const { return _adj[node]; }
  void print();
  size_t size() const { return _adj.size(); }
};

inline bool operator<(const State &a, const State &b) {
  return a.dist() > b.dist();
}

AjecentList::AjecentList(istream &input) : _adj{} {
  int nVex;
  int nEdge;
  input >> nVex >> nEdge;
  _adj.resize(nVex);
  double weight;
  size_t w, v;
  for (size_t e = 0; e < nEdge; e++) {
    input >> w >> v >> weight;
    _adj[w].push_back(State{v, weight});
    _adj[v].push_back(State{w, weight});
  }
}

void AjecentList::print() {
  for (size_t i = 0; i < _adj.size(); i++) {
    cout << i << ":";
    for (auto state : _adj[i]) {
      std::cout << "(" << state.node() << ", " << state.dist() << ") ";
    }
    cout << endl;
  }
}

double Prim(const AjecentList &adj) {
  cout << "prim" << endl;
  unordered_map<int, bool> visited;
  priority_queue<State> pq;
  pq.push(State{0, 0.0}); //括号还是花括号？
  double weight = 0.0;
  while (visited.size() < adj.size()) {
    auto top = pq.top();
    pq.pop();
    // cout << top.node() << endl;
    if (visited.count(top.node()) == 0) {
      visited[top.node()] = true;
      weight += top.dist();
      for (auto vertex : adj.adj(top.node()))
        pq.push(vertex);
    }
  }
  return weight;
  cout << weight << endl;
}

int main() {
  ifstream input{"../test_data/mst.2.in.txt"};
  ofstream output{"../test_data/mst.2.out.txt"};
  if (input.is_open()) {
    cout << "open file" << endl;
    // AjecentList adj(input);
    auto adj = AjecentList{input};
    adj.print();
    output << fixed << setprecision(8);
    output << Prim(adj) << endl;
    cout << "write result" << endl;
  } else {
    cerr << "Could not open the file!";
    return 1;
  }
  return 0;
}
