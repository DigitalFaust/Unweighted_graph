#include<iostream>
#include<queue>
#include"bfsh.h"
using std::cout;
using std::cin;
using std::endl;
using std::queue;

namespace bfspace
{
	bool processed[SIZE];
	bool discovered[SIZE];
	int parent[SIZE];
	int dmtr[SIZE];
	int induced[SIZE];
	int incident[SIZE];
	int k = 0;

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
			dmtr[i] = 0;
			incident[i] = 0;
		}
	}

	void bfs(graph* g, int start)
	{
		int v = -1, y = -1;
		edgenode* p = NULL;
		int cnt_edges = 0;
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
			while(p != NULL)
			{
				y = p->y;
				cnt_edges++;
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
			if(cnt_edges >= k)
				induced[v] = cnt_edges;
			process_vertex_late(v);
			cnt_edges = 0;
		}
	}

	void process_edge(int x, int y)
	{
		cout << "The edge (" << x << ", " << y << ") is processed\n";
		dmtr[y] = dmtr[x] + 1;
	}

	void process_vertex_early(int x)
	{
		cout << "Processing the vertex: " << x << endl;
	}

	void process_vertex_late(int x)
	{
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
}
