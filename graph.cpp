#include<iostream>
using std::cout;
using std::cin;
using std::endl;

const int MAXV = 100;

struct edgenode
{
	int y;
	int weight;
	edgenode* next;
};

struct graph
{
	edgenode* edges[MAXV];
	int degree[MAXV];
	int nvertices;
	int nedges;
	bool directed;
};

void init_graph(graph* g, bool directed);
void read_graph(graph* g, bool directed);
void insert_graph(graph* g, int x, int y, bool directed);
void print_graph(graph* g);

int main()
{
	graph* g = new graph;
	bool directed = false;

	init_graph(g, directed);
	read_graph(g, directed);
	cout << "Content of the graph:\n";
	print_graph(g);

	return 0;
}

void init_graph(graph* g, bool directed)
{
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
	for(int i = 1; i <= MAXV; i++)
	{
		g->edges[i] = NULL;
		g->degree[i] = 0;
	}
}

void read_graph(graph* g, bool directed)
{
	int x = 0, y = 0, m = 0;
	cout << "Enter number of edges: ";
	cin >> m;
	cout << "Enter number of vertices: ";
	cin >> g->nvertices;
	for(int i = 1; i <= m; i++)
	{
		cout << "Enter the vertex x: ";
		cin >> x;
		cout << "Enter the vertex y: ";
		cin >> y;
		insert_graph(g, x, y, directed);
	}
}

void insert_graph(graph* g, int x, int y, bool directed)
{
	edgenode* temp = new edgenode;
	temp->y = y;
	temp->weight = 0;
	temp->next = g->edges[x];
	g->edges[x] = temp;
	g->degree[x]++;
	if(directed == false)
		insert_graph(g, y, x, true);
	else
		g->nedges++;
}

void print_graph(graph* g)
{
	edgenode* p = NULL;

	for(int i = 1; i <= g->nvertices; i++)
	{
		p = g->edges[i];
		cout << i << ": ";
		while(p != NULL)
		{
			cout << p->y << " ";
			p = p->next;
		}
		cout << endl;
	}

	cout << endl;
}
