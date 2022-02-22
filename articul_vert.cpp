#include<iostream>
using std::cout;
using std::cin;
using std::endl;

const int MAXV = 100;
bool FINISHED = false;
int TIME = 0;
enum edge { TREE, BACK, UNDEFINED };

bool processed[MAXV];
bool discovered[MAXV];
int parent[MAXV];
int entry_time[MAXV];
int exit_time[MAXV];
int reachable_ancestor[MAXV];
int tree_out_degree[MAXV];
int articulations[MAXV];

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
void read_graph(graph* g);
void insert_edge(graph* g, int x, int y, bool directed);
void print_graph(graph* g);
void init_search(graph* g);
void dfs(graph* g, int v);
void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int v, int y);
edge classify_edge(int v, int y);

int main()
{
	graph* g = new graph;
	bool directed = false;

	init_graph(g, directed);
	read_graph(g);
	cout << "Content of the graph:\n";
	print_graph(g);

	cout << "Searching for articulation vertices...\n";
	dfs(g, 1);
	cout << endl;

	cout << "Not articulation vertices: ";
	for(int i = 1; i <= g->nvertices; i++)
		if(articulations[i] == false)
			cout << i << " ";
	cout << endl;

	cout << "Articulation vertices: ";
	for(int i = 1; i <= g->nvertices; i++)
		if(articulations[i] == true)
			cout << i << " ";
	cout << endl;

	return 0;
}

void init_graph(graph* g, bool directed)
{
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for(int i = 1; i <= g->nvertices; i++)
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
		cout << i << " : ";
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
		articulations[i] = false;
		parent[i] = -1;
		entry_time[i] = 0;
		exit_time[i] = 0;
		reachable_ancestor[i] = -1;
		tree_out_degree[i] = 0;
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
	reachable_ancestor[v] = v;
}

void process_vertex_late(int v)
{
	bool root;
	int time_v;
	int time_parentv;

	if(parent[v] < 1)
		if(tree_out_degree[v] > 1)
		{
			cout << "Root articulation vertex: " << v << endl;
			articulations[v] = true;
			return;
		}

	root = parent[parent[v]] < 1;
	if(!root)
	{
		if(reachable_ancestor[v] == parent[v])
		{
			cout << "Parent articulation vertex: " << parent[v] << endl;
			articulations[parent[v]] = true;
		}
		else if(!root && (reachable_ancestor[v] == v))
		{
			cout << "Bridge articulation vertex: " << parent[v] << endl;
			articulations[parent[v]] = true;
			if(tree_out_degree[v] > 0)
			{
				cout << "Bridge_articulation vertex: " << v << endl;
				articulations[v] = true;
			}
		}
	}
	
	time_v = entry_time[reachable_ancestor[v]];
	time_parentv = entry_time[reachable_ancestor[parent[v]]];
	if(time_v < time_parentv)
		reachable_ancestor[parent[v]] = reachable_ancestor[v];
}

void process_edge(int v, int y)
{
	edge type = classify_edge(v, y);

	if(type == TREE)
		tree_out_degree[v]++;
	else if(type == BACK && parent[v] != y)
		if(entry_time[reachable_ancestor[v]] > entry_time[y])
			reachable_ancestor[v] = y;
}

edge classify_edge(int v, int y)
{
	if(parent[y] == v)
		return TREE;
	if(discovered[y] && parent[v] != y)
		return BACK;

	return UNDEFINED;
}
