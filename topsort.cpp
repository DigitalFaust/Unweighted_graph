#include<iostream>
#include<stack>
using std::cout;
using std::endl;
using std::cin;
using std::stack;

const int MAXV = 100;
int TIME = 0;
stack<int> sorted;
bool processed[MAXV + 1];
bool discovered[MAXV + 1];
int parent[MAXV + 1];
int entry_time[MAXV + 1];
int exit_time[MAXV + 1];

struct edgenode
{
	int y;
	int weight;
	edgenode* next;
};

struct graph
{
	edgenode* edges[MAXV + 1];
	int degree[MAXV + 1];
	int nvertices;
	int nedges;
	bool directed;
};

void init_graph(graph* g, bool directed);
void read_graph(graph* g);
void insert_edge(graph* g, int x, int y, bool directed);
void print_graph(graph* g);
void init_search(graph* g);
void dfs(graph* g, int v);
void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int v, int y);
void top_sort(graph* g);
void print_stack();

int main()
{
	graph* g = new graph;
	bool directed = true;
	//bool x = true;

	init_graph(g, directed);
	read_graph(g);
	cout << "Printing content of the graph...\n";
	print_graph(g);

	cout << "Performing topological sorting...\n";
	top_sort(g);
	print_stack();
	cout << endl;

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

void read_graph(graph* g)
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
		insert_edge(g, x, y, g->directed);
	}
}

void insert_edge(graph* g, int x, int y, bool directed)
{
	edgenode* p = new edgenode;

	p->y = y;
	p->weight = 0;
	p->next = g->edges[x];
	g->edges[x] = p;

	if(!directed)
		insert_edge(g, y, x, true);
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

	entry_time[v] = TIME++;
	discovered[v] = true;
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
		p = p->next;
	}

	process_vertex_late(v);
	exit_time[v] = TIME++;
	processed[v] = true;
}

void process_vertex_early(int v)
{
}

void process_vertex_late(int v)
{
	sorted.push(v);
}

void process_edge(int v, int y)
{
	if(discovered[y] && !processed[y])
		cout << "Found a back edge, not DAG: (" << v << ", " << y << ")\n";
}

void top_sort(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
	{
		if(!discovered[i])
			dfs(g, i);
	}
}

void print_stack()
{
	while(!sorted.empty())
	{
		cout << sorted.top() << " ";
		sorted.pop();
	}
}
