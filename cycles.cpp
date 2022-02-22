#include<iostream>
#include<iomanip>
using std::setw;
using std::cout;
using std::cin;
using std::endl;

const int MAXV = 100;
bool FINISHED = false;
int TIME = 0;
bool processed[MAXV];
bool discovered[MAXV];
int parent[MAXV];
int entry_time[MAXV];
int exit_time[MAXV];

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
void insert_edge(graph* g, int x, int y, bool directed);
void print_graph(graph* g);
void init_search(graph* g);
void dfs(graph* g, int v);
void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int v, int y);
void print_relations(graph* g);

int main()
{
	graph* g = new graph;
	bool directed = false;

	init_graph(g, directed);
	read_graph(g, directed);
	print_graph(g);

	cout << "\nPerforming dfs...\n";
	init_search(g);
	dfs(g, 1);

	cout << "Relations\n";
	print_relations(g);

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
	
	cout << "Enter a number of edges: ";
	cin >> m;
	cout << "Enter a number of vertices: ";
	cin >> g->nvertices;

	for(int i = 1; i <= m; i++)
	{
		cout << "Enter vertices x and y: ";
		cin >> x >> y;
		insert_edge(g, x, y, directed);
	}
}

void insert_edge(graph* g, int x, int y, bool directed)
{
	edgenode* p = new edgenode;

	p->y = y;
	p->weight = 0;
	p->next = g->edges[x];
	g->edges[x] = p;
	g->degree[x]++;

	if(directed == false)
		insert_edge(g, y, x, true);
	else
		g->nedges++;
}

void print_graph(graph* g)
{
	edgenode* p = NULL;

	for(int i = 1; i <= g->nvertices; i++)
	{
		cout << i << ": ";
		p = g->edges[i];
		while(p != NULL)
		{
			cout << p->y << " ";
			p = p->next;
		}
		cout << endl;
	}
	cout << endl;
}

void init_search(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
	{
		processed[i] = false;
		discovered[i] = false;
		parent[i] = -1;
		entry_time[i] = 0;
		exit_time[i] = 0;
	}
}

void dfs(graph* g, int v)
{
	int y = 0;
	edgenode* p = NULL;
	if(FINISHED) return;

	discovered[v] = true;
	entry_time[v] = TIME++;
	process_vertex_early(v);
	p = g->edges[v];

	while(p != NULL)
	{
		y = p->y;
		if(!discovered[y])
		{
			parent[y] = v;
			process_edge(v, y);
			dfs(g, y);
		}
		else if(!processed[y] || g->directed)
			process_edge(v, y);
		if(FINISHED) return;
		p = p->next;
	}

	process_vertex_late(v);
	exit_time[v] = TIME++;
	processed[v] = true;
}

void process_vertex_early(int v)
{
	cout << "Processing the vertex: " << v << endl;
}

void process_vertex_late(int v)
{
}

void process_edge(int x, int y)
{
	if(discovered[y] && (parent[x] != y))
	{
		cout << "Found a cycle from " << y << " to " << x << endl;
		cout << endl;
		FINISHED = true;
	}
}

void print_relations(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
	{
		cout << "|" << setw(3) << i ;
	}
	cout << endl;
	for(int i = 1; i <= g->nvertices; i++)
	{
		cout << "|" << setw(3) << parent[i];
	}
	cout << endl;
}
