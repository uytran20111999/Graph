#include<iostream>
#include<vector>
#include<climits>
#include<fstream>
using namespace std; 
struct vertex {
	int key; 
	int index;
	vertex * p;
};
struct graph {
	vector<vertex> vertices;
	int numedges;
	int **edge;
};
int ** creat2Darr (int n){
	int ** u = new int*[n];
	for (int i = 0; i < n; i++) {
		u[i] = new int[n];
	}
	return u;
}
void del2d(int ** u,int n){
	for (int i = 0; i < n; i++) {
		if (u[i] != nullptr)delete[]u[i];
	}
	delete[]u;
}
bool isExist(const vector<vertex*> & a,vertex b) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i]->index == b.index)return 1;
		int k = 0;
	}
	 return 0;
}
vertex * ExtractMin(vector<vertex*>& a) {
	if (!a.empty()) {
		vertex* temp = a[0];
		int j = 0;
		for (int i = 0; i < a.size(); i++) {
			if (temp->key > a[i]->key) { temp = a[i]; j = i; }
		}
		swap(a[j], a[a.size() - 1]);
		a.pop_back();
		return temp;
	}
	else return NULL;
}
void MST_PRIME(graph & G , int i){
	for (int r = 0; r < G.vertices.size(); r++) {
		G.vertices[r].index = r;
		G.vertices[r].key = INT_MAX;
		G.vertices[r].p = NULL;
	}
	G.vertices[i].key = 0;
	vector <vertex*> Q;
	for (int w = 0; w < G.vertices.size(); w++)
	{
		Q.push_back( &G.vertices[w]);
	}
	while (!Q.empty()) {
		vertex * u = ExtractMin(Q);
		for (int i = 0; i < G.numedges; i++) {
			if (G.edge[u->index][i] != -1) {
				if (isExist(Q, G.vertices[i]) && G.edge[u->index][i] < G.vertices[i].key) {
					G.vertices[i].p = u;
					G.vertices[i].key = G.edge[u->index][i];
				}
			}
		}
	}
}
void printMST(graph& G) {
	for (int i = 0; i < G.vertices.size(); i++) {
		if (G.vertices[i].p != NULL) {
			cout << G.vertices[i].p->index << "-------------------" << G.vertices[i].index << " : " << G.vertices[i].key << endl;
		}
	}
}
void relax(vertex&u,vertex&v , graph & G){
	if (v.key > u.key + G.edge[u.index][v.index]) {
		v.p = &u;
		v.key = u.key + G.edge[u.index][v.index];
	}
}
void init(graph& G) {
	for (int r = 0; r < G.vertices.size(); r++) {
		G.vertices[r].index = r;
		G.vertices[r].key = INT_MAX;
		G.vertices[r].p = NULL;
	}
}
bool bellman(graph&G, int s) {
	init(G);
	G.vertices[s].key = 0;
	for (int z = 1; z <= G.vertices.size() - 1; z++) {
		for (int i = 0; i < G.numedges; i++) {
			for (int j = 0; j< G.numedges;j++){
				if (G.edge[i][j] != INT_MAX) {
					relax(G.vertices[i], G.vertices[j], G);
				}
			}
		}
	}
	for (int i = 0; i < G.numedges; i++) {
		for (int j = 0; j< G.numedges; j++) {
			if (G.edge[i][j] != INT_MAX) {
				if (G.vertices[j].key > G.vertices[i].key + G.edge[i][j]) {
					return false;
				}
			}
		}
	}
	return true;
}
void printT(vertex s, vertex* p){
	if (p->index == s.index) {
		cout << s.index;
	}
	else if (p->p != NULL) {
		printT(s, p->p);
		cout << "----->" << p->index;

	}
	else {
		cout << " no path " << endl; exit(0);
	}
}
void dijsktra(graph&G , int s){
	init(G);
	G.vertices[s].key = 0;
	vector<vertex*> Q;
	for (int i = 0; i < G.vertices.size(); i++) {
		Q.push_back(&G.vertices[i]);
	}
	while (!Q.empty()) {
		vertex * u = ExtractMin(Q);
		for (int i = 0; i < G.numedges; i++) {
			if (G.edge[u->index][i] != INT_MAX)
			relax(*u, G.vertices[i], G);
		}

	}
}
void main(){
/*	ifstream in("sample.txt");
	int edges;
	in >> edges;
	graph G;
	G.numedges = edges;
	G.edge = creat2Darr(edges);
	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < edges; j++) {
			int temp = -1;
			in >> temp;
			G.edge[i][j] = temp;
		}
	}
	G.vertices.resize(edges);
	MST_PRIME(G, 0);
	int sum = 0;
	for (int i = 0; i < G.vertices.size(); i++) {
		sum += G.vertices[i].key;
	}
	cout << sum << endl;
	printMST(G);
	del2d(G.edge, edges);*/
/*	ifstream in("bellman.txt");
	int edges;
	in >> edges;
	graph G;
	G.numedges = edges;
	G.edge = creat2Darr(edges);
	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < edges; j++) {
			int temp = -1;
			in >> temp;
			G.edge[i][j] = temp;
		}
	}
	G.vertices.resize(edges);
	bellman(G, 0);
	printT(G.vertices[0], &G.vertices[1]);
	del2d(G.edge, edges);*/
	ifstream in("dijsktra.txt");
	int edges;
	in >> edges;
	graph G;
	G.numedges = edges;
	G.edge = creat2Darr(edges);
	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < edges; j++) {
			int temp = -1;
			in >> temp;
			G.edge[i][j] = temp;
		}
	}
	G.vertices.resize(edges);
	dijsktra(G, 0);
	printT(G.vertices[0], &G.vertices[4]);
	del2d(G.edge, edges);



}