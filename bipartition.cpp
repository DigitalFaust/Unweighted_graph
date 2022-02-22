#include<iostream>
#include<queue>
using std::cout;
using std::endl;
using std::cin;
using std::queue;

const int MAXV = 100;
bool bipartite = true;
enum color { BLACK, WHITE, UNCOLORED };
bool processed[MAXV + 1];
bool discovered[MAXV + 1];
int parent[MAXV + 1];
color colors[MAXV + 1];

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
void init_bfs(graph* g);
void bfs(graph* g, int start);
void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int v, int y);
color complement(color v);
void bipartition(graph* g);
void print_colors(graph* g);

int main()
{
	graph* g = new graph;
	bool directed = false;

	init_bfs(g);
	init_graph(g, directed);
	read_graph(g, directed);
	cout << "\tContent of the graph:\n\n";
	print_graph(g);
	cout << endl;

	cout << "\nPerforming bipartition..\n\n";
	bipartition(g);
	cout << endl;

	cout << "\nPrinting colors...\n\n";
	print_colors(g);
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
	edgenode* p = NULL;

	cout << "Enter number of edges: ";
	cin >> m;
	cout << "Enter number of vertices: ";
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

void init_bfs(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
	{
		processed[i] = false;
		discovered[i] = false;
		parent[i] = -1;
	}
}

void bfs(graph* g, int start)
{
	int v = 0, y = 0;
	edgenode* p = NULL;
	queue<int> q;

	q.push(start);
	discovered[start] = true;

	while(!q.empty())
	{
		v = q.front();
		q.pop();
		process_vertex_early(v);
		p = g->edges[v];
		processed[v] = true;
		
		while(p != NULL)
		{
			y = p->y;
			if(processed[y] == false || g->directed)
				process_edge(v, y);
			if(discovered[y] == false)
			{
				q.push(y);
				discovered[y] = true;
				parent[y] = v;
			}
			p = p->next;
		}
		process_vertex_late(v);
	}
}

void process_vertex_early(int v)
{
}

void process_vertex_late(int v)
{
}

void process_edge(int v, int y)
{
	if(colors[v] == colors[y])
	{
		bipartite = false;
		cout << "The graph cannot be biparted because of the edge: (" << v << ", " << y << ")\n";
	}

	colors[y] = complement(colors[v]);
}

color complement(color v)
{
	if(v == BLACK) return WHITE;
	if(v == WHITE) return BLACK;
	return UNCOLORED;
}

void bipartition(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
		colors[i] = UNCOLORED;
	
	init_bfs(g);
	bipartite = true;
	for(int i = 1; i <= g->nvertices; i++)
	{
		if(discovered[i] == false)
		{
			colors[i] = WHITE;
			bfs(g, i);
		}
	}
	if(bipartite)
		cout << "The graph is bipartite\n";
	else
		cout << "The graph is not bipartite\n";
}

void print_colors(graph* g)
{
	edgenode* p = NULL;

	for(int i = 1; i <= g->nvertices; i++)
	{
		cout << "[" << i << " : " << colors[i] << "] ";
		p = g->edges[i];
		while(p != NULL)
		{
			cout << "-> [" << p->y << " : " << colors[p->y] << "] ";
			p = p->next;
		}
		cout << endl;
	}
	cout << endl;
}
