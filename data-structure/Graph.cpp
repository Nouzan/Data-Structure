#pragma once
#include <iostream>
#include "LinkQueue.h"
#include "FindSet.h"
using namespace std;

//默认以非负整数作为关键字，待以后编写了Map类，再扩展为可用任意类型作为关键字

struct Edge {
	int from;
	int to;
	int weight;
	Edge *nextEdge;
};

bool cmpWeight(Edge &a, Edge &b) {
	if (a.weight < b.weight) {
		return true;
	} else {
		return false;
	}
}

template<typename T>
int partition(T *A, int p, int q, bool (*cmp)(T&, T&)) {
	T x = A[q];
	int i, j = p - 1;
	for (i = p; i < q; i ++) {
		if(cmp(A[i], x)) {
			j++;
			T tmp = A[j];
			A[j] = A[i];
			A[i] = tmp;
		}
	}
	j++;
	T tmp = A[j];
	A[j] = A[q];
	A[q] = tmp;
	return j;
}

template<typename T>
void QuickSort(T *A, int p, int q, bool (*cmp)(T&, T&)) {
	if (p < q) {
		int r = partition(A, p, q, cmp);
		QuickSort(A, p, r - 1, cmp);
		QuickSort(A, r + 1, q, cmp);
	}
}

template<typename T>
struct Vertex {
	T value;
	int edgeNum;
	Edge *firstEdge;
};

template<typename T>
class Graph {
private:
	const static int maxSize = 100000;
	Vertex<T> vertexList[maxSize];
	Edge edgeList[maxSize];
	int vertexNum;
	int edgeNum;
	bool isDirect;
	// int edgeNum;
	Edge *getNewEdge() {
		return &edgeList[edgeNum++];
	}

	void addEdge(Edge e, bool isReverse = false) {
		Edge *newEdge = getNewEdge();
		int u;

		if (!isReverse) {
			u = e.from;
			newEdge->from = e.from;
			newEdge->to = e.to;
		} else {
			u = e.to;
			newEdge->from = e.to;
			newEdge->to = e.from;
		}

		newEdge->weight = e.weight;
		newEdge->nextEdge = NULL;

		if (vertexList[u].firstEdge) {
			Edge *edge = vertexList[u].firstEdge;
			while (edge->nextEdge) {
				edge = edge->nextEdge;
			}
			edge->nextEdge = newEdge;
		} else {
			vertexList[u].firstEdge = newEdge;
		}
	}

	void addEdge(int from, int to, int weight = 0) {
		Edge edge;
		edge.from = from;
		edge.to = to;
		edge.weight = weight;
		addEdge(edge);
	}

	void dfsVisit(int u, int *color, int *pre, int *f, int &t) const {
		color[u] = 1;
		cout << vertexList[u].value << " --> ";
		Edge *e = vertexList[u].firstEdge;
		t++;
		for (Edge *e = vertexList[u].firstEdge; e != NULL; e = e->nextEdge) {
			int v = e->to;
			if (color[v] == 0) {
				pre[v] = u;
				dfsVisit(v, color, pre, f, t);
			}
		}
		color[u] = 2;
		f[u] = ++t;
	}

public:
	Graph(bool dir = false) {
		vertexNum = 0;
		isDirect = dir;
		// edgeNum = 0;
	}

	Graph(T *A, int num, bool dir = false) {
		isDirect = dir;
		vertexNum = num;
		for(int i = 0; i < vertexNum; i ++) {
			vertexList[i].value = A[i];
			vertexList[i].firstEdge = NULL;
			vertexList[i].edgeNum = 0;
		}
	}

	Graph(T *A, int vNum, Edge *B, int eNum, bool dir = false) : Graph<T>(A, vNum, dir) {

		for(int i = 0; i < eNum; i ++) {
			addEdge(B[i]);
			if (!dir) {
				addEdge(B[i], true);
			}
		}
	}

	~Graph() {}

	void AddEdge(Edge e) {
		addEdge(e);
		if (!isDirect)
			addEdge(e, true);
	}

	void AddEdge(int first, int second, int weight = 0) {
		addEdge(first, second, weight);
		if (!isDirect)
			addEdge(second, first, weight);
	}

	void ShowAL() const {
		for(int i = 0; i < vertexNum; i ++) {
			cout << vertexList[i].value << ": ";
			Edge *edge = vertexList[i].firstEdge;
			while(edge != NULL) {
				cout << "<" << vertexList[edge->from].value << ", " << edge->weight << ", " << vertexList[edge->to].value << ">" << " --> ";
				edge = edge->nextEdge;
			}
			cout << endl;
		}
	}

	void BFSPrint(int *pre, int *d, int src = 0) const {
		int *color = new int[vertexNum];
		LinkQueue<int> queue;
		for (int i = 0; i < vertexNum; i ++) {
			color[i] = 0;
			d[i] = 0;
			pre[i] = -1;
		}

		color[src] = 1;
		queue.EnQueue(src);
		while(!queue.IsEmpty()) {
			int u = queue.DeQueue();
			cout << vertexList[u].value << " --> ";
			Edge *e = vertexList[u].firstEdge;
			for (Edge *e = vertexList[u].firstEdge; e != NULL; e = e->nextEdge) {
				int v = e->to;
				if(color[v] == 0) {
					color[v] = 1;
					pre[v] = u;
					d[v] = d[u] + 1;
					queue.EnQueue(v);
				}
			}
			color[u] = 2;
		}
		cout << endl;
		delete[] color;
	}

	void DFSPrint(int *pre, int *f) const {
		int *color = new int[vertexNum];
		int t = 0;
		for (int i = 0; i < vertexNum; i ++) {
			color[i] = 0;
			pre[i] = -1;
			f[i] = 0;
		}

		for (int i = 0; i < vertexNum; i ++) {
			if (color[i] == 0) {
				dfsVisit(i, color, pre, f, t);
			}
		}
		cout << endl;
		delete[] color;
	}

	int Kruskal() {
		FindSet<int> *vSet = new FindSet<int>[vertexNum];
		int result = 0;

		for (int i = 0; i < vertexNum; i ++) {
			vSet[i].Set(i);
		}
		QuickSort(edgeList, 0, edgeNum - 1, cmpWeight);
		for (int i = 0; i < edgeNum; i ++) {
			int u = edgeList[i].from;
			int v = edgeList[i].to;

			if (vSet[u].Find().Get() != vSet[v].Find().Get()) {
				cout << "<" << vertexList[u].value << ", " << edgeList[i].weight << ", " << vertexList[v].value << ">" << " ";
				vSet[u].Union(vSet[v]);
				result += edgeList[i].weight;
			}
		}
		cout << endl;
		return result;
	}

	void relaxtion(int u, int *pre, int *d) {
		for (Edge *e = vertexList[u].firstEdge; e != NULL; e = e->nextEdge) {
			int v = e->to;
			if (d[v] > d[u] + e->weight) {
				d[v] = d[u] + e->weight;
				pre[v] = u;
			}
		}
	}

	void Dijkstra(int s, int *pre, int *d) {
		
	}

};

int main() {
	char A[5] = {'A', 'B', 'C', 'D', 'E'};
	Edge B[3];
	B[0].from = 0;
	B[0].to = 1;
	B[0].weight = 5;
	B[1].from = 1;
	B[1].to = 2;
	B[1].weight = 4;
	B[2].from = 3;
	B[2].to = 2;
	B[2].weight = 6;

	Graph<char> G(A, 5, B, 3);
	G.AddEdge(2, 4, 5);
	G.AddEdge(4, 3, 2);
	G.ShowAL();

	int pre[5], f[5];

	G.DFSPrint(pre, f);

	cout << G.Kruskal() << endl;

	return 0;
}
