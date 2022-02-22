#include<iostream>
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
void dfs(graph* g, int start, int level);
void process_vertex_early(int x, int level);
void process_vertex_late(int x);
void process_edge(int x, int y);

int main()
{
	graph* g = new graph;
	bool directed = true;

	init_graph(g, directed);
	read_graph(g, directed);
	print_graph(g);

	cout << "\nStarting depth-first search...\n";
	init_search(g);
	dfs(g, 1, 1);
	
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

	cout << endl;
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
		entry_time[i] = -1;
		exit_time[i] = -1;
	}
}

void dfs(graph* g, int v, int level)
{
	int y = -1;
	edgenode* p = new edgenode;
	if(FINISHED) return;

	discovered[v] = true;
	entry_time[v] = TIME++;
	process_vertex_early(v, level);
	p = g->edges[v];

	while(p != NULL)
	{
		y = p->y;
		if(!discovered[y])
		{
			parent[y] = v;
			process_edge(v, y);
			dfs(g, y, level + 1);
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

void process_vertex_early(int x, int level)
{
	cout << "Processing the vertex: " << x << endl;
	if ((level % 2) == 0)
		cout << x << " is on an even level\n";
	else
		cout << x << " is on an odd level\n";

}

void process_vertex_late(int x)
{
	cout << "Finished processing the vertex: " << x << endl;
}

void process_edge(int x, int y)
{
	cout << "Processing the edge: (" << x << ", " << y << ")\n";
}
