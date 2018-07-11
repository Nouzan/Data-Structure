#pragma once
#include <iostream>
#include "LinkQueue.h"
using namespace std;

//默认以非负整数作为关键字，待以后编写了Map类，再扩展为可用任意类型作为关键字

struct Edge {
	int from;
	int to;
	int weight;
	Edge *nextEdge;
};

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
	int vertexNum;
	bool isDirect;
	// int edgeNum;
	void addEdge(Edge e, bool isReverse = false) {
		Edge *newEdge = new Edge();
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

	~Graph() {
		for(int i = 0; i < vertexNum; i ++) {
			Edge *edge = vertexList[i].firstEdge;
			while(edge != NULL) {
				Edge *deleteEdge = edge;
				edge = edge->nextEdge;
				delete deleteEdge;
			}
			cout << endl;
		}
	}

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

};

int main() {
	char A[5] = {'A', 'B', 'C', 'D', 'E'};
	Edge B[3];
	B[0].from = 0;
	B[0].to = 1;
	B[1].from = 1;
	B[1].to = 2;
	B[2].from = 3;
	B[2].to = 2;
	Graph<char> G(A, 5, B, 3, true);
	G.AddEdge(2, 4, 5);
	G.AddEdge(4, 3);
	G.ShowAL();

	int pre[5], f[5];

	G.DFSPrint(pre, f);

	for(int i = 0; i < 5; i ++) {
		cout << A[i] << ": " << f[i] << endl;
	}

	return 0;
}
