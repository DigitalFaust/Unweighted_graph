#include<iostream>
#include<stack>
#include<iomanip>
using std::setw;
using std::cout;
using std::cin;
using std::endl;
using std::stack;

const int MAXV = 100;
int TIME = 0;
int FOUND_COMPONENTS = 0;
stack<int> active;
enum edge { BACK, CROSS, UNDEFINED };

bool processed[MAXV + 1];
bool discovered[MAXV + 1];
int parent[MAXV + 1];
int entry_time[MAXV + 1];
int exit_time[MAXV + 1];
int low[MAXV + 1];
int scc[MAXV + 1];

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
void dfs(graph* g);
void strong_components(graph* g);
void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int x, int y);
void pop_component(int x);
void print_scc(graph* g);
edge classify(int x, int y);

int main()
{
	graph* g = new graph;
	bool directed = true;

	init_graph(g, directed);
	read_graph(g);
	cout << "Printing content of the graph...\n";
	print_graph(g);
	cout << endl;

	cout << "Searching strongly connected components...\n";
	strong_components(g);
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
	g->degree[x]++;

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

void dfs(graph* g, int v)
{
	int y = 0;
	edgenode* p = NULL;

	TIME++;
	entry_time[v] = TIME;
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
	TIME++;
	exit_time[v] = TIME;
	processed[v] = true;
}

void strong_components(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
	{
		low[i] = i;
		scc[i] = -1;
	}

	init_search(g);

	for(int i = 1; i <= g->nvertices; i++)
	{
		if(!discovered[i])
			dfs(g, i);
	}

	print_scc(g);
}

void process_vertex_early(int v)
{
	active.push(v);
}

void process_vertex_late(int v)
{
	if(low[v] == v)
		pop_component(v);

	if(entry_time[low[v]] < entry_time[low[parent[v]]])
		low[parent[v]] = low[v];
}

void process_edge(int x, int y)
{
	edge type = classify(x, y);

	if(type == BACK)
		if(entry_time[low[x]] > entry_time[y])
			low[x] = y;
	if(type == CROSS)
		if(scc[y] == -1)
			if(entry_time[low[x]] > entry_time[y])
				low[x] = y;
}

void pop_component(int v)
{
	int t = 0;

	scc[v] = ++FOUND_COMPONENTS;
	while((t = active.top()) != v)
	{
		active.pop();
		scc[t] = FOUND_COMPONENTS;
	}
	active.pop();
}

void print_scc(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
		cout << "|" << setw(3) << i;
	cout << endl;

	for(int i = 1; i <= g->nvertices; i++)
		cout << "|" << setw(3) << scc[i];
	cout << endl;
}

edge classify(int x, int y)
{
	if(discovered[y] && !processed[y])
		return BACK;
	if(processed[y] && (entry_time[y] < entry_time[x]))
		return CROSS;

	return UNDEFINED;
}
