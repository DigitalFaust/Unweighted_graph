#include<iostream>
#include<queue>
#include<stack>
using std::stack;
using std::cout;
using std::cin;
using std::endl;
using std::queue;

const int MAXV = 100;
bool processed[MAXV + 1];
bool discovered[MAXV + 1];
int parent[MAXV + 1];
stack<int> s;

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
void init_bfs(graph* g);
void bfs(graph* g, int start);
void process_edge(int x, int y);
void process_vertex_early(int x);
void process_vertex_late(int x);
void find_path(int start, int end, int parent[]);

int main()
{
	graph* g = new graph;
	bool directed = false;

	init_graph(g, directed);
	read_graph(g, directed);
	print_graph(g);

	cout << "Starting breadth-first search...\n";
	bfs(g, 1);

	cout << "The shortest path from 1 to 5 is: ";
	find_path(1, 5, parent);
	cout << endl;

	cout << "Poped values: ";
	while(!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
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
	edgenode *p = new edgenode;
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
	int v = -1, y = -1;
	edgenode* p = NULL;
	queue<int> q;

	init_bfs(g);
	q.push(start);
	discovered[start] = true;
	while(!q.empty())
	{
		v = q.front();
		q.pop();
		process_vertex_early(v);
		p = g->edges[v];
		processed[v] = true;
		cout << v << ": ";
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
		cout << endl;
	}
}

void process_edge(int x, int y)
{
	cout << "(" << x << ", " << y << ") ";
	//cout << "The edge (" << x << ", " << y << ") is processed\n";
}

void process_vertex_early(int x)
{
	//cout << "Processing the vertex: " << x << endl;
}

void process_vertex_late(int x)
{
	s.push(x);
}

void find_path(int start, int end, int parent[])
{
	if((start == end) || (end == -1))
		cout << start << " ";
	else
	{
		find_path(start, parent[end], parent);
		cout << end << " ";
	}
}
