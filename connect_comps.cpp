#include<iostream>
#include<queue>
using std::cout;
using std::endl;
using std::cin;
using std::queue;

const int MAXV = 100;
bool processed[MAXV + 1];
bool discovered[MAXV + 1];
int parent[MAXV + 1];

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
void init_bfs();
void bfs(graph* g, int start);
void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int v, int y);
void components(graph* g);

int main()
{
	graph* g = new graph;
	bool directed = false;

	init_graph(g, directed);
	read_graph(g, directed);
	cout << "\tContent of the graph:\n";
	print_graph(g);

	init_bfs();
	cout << "\tPerforming BFS...\n";
	bfs(g, 1);
	cout << endl;

	cout << "\n\tSearching connected components...\n";
	components(g);
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

void read_graph(graph* g, bool directed)
{
	int x = 0, y = 0, m = 0;

	cout << "Enter number of edges: ";
	cin >> m;
	cout << "Enter number of vertices: ";
	cin >> g->nvertices;

	for(int i = 1; i <= m; i++)
	{
		cout << "Enter vertices x and y: ";
		cin >> x >> y;
		insert_graph(g, x, y, directed);
	}
}

void insert_graph(graph* g, int x, int y, bool directed)
{
	edgenode* p = new edgenode;

	p->y = y;
	p->weight = 0;
	p->next = g->edges[x];
	g->edges[x] = p;
	g->degree[x]++;

	if(directed == false)
		insert_graph(g, y, x, true);
	else
		g->nedges++;
}

void print_graph(graph* g)
{
	edgenode* p;

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

void init_bfs()
{
	for(int i = 0; i < MAXV + 1; i++)
	{
		processed[i] = false;
		discovered[i] = false;
		parent[i] = -1;
	}
}

void bfs(graph* g, int start)
{
	int v = 0, y = 0;
	edgenode* p;
	queue<int> q;

	discovered[start] = true;
	q.push(start);
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
				discovered[y] = true;
				parent[y] = v;
				q.push(y);
			}
			p = p->next;
		}
		process_vertex_late(v);
	}
}

void process_vertex_early(int v)
{
	cout << "Processing the vertex: " << v << endl;
}

void process_vertex_late(int v)
{
}

void process_edge(int v, int y)
{
	cout << "Processing edge ( " << v << ", " << y << ")\n";
}

void components(graph* g)
{
	int c = 1;
	init_bfs();

	for(int i = 1; i <= g->nvertices; i++)
	{
		if(discovered[i] == false)
		{
			cout << "\nConnected component: #" << c << endl;
			bfs(g, i);
			c++;
		}
	}
}
