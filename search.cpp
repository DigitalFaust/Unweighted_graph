#include"search.h"
#include<iostream>
#include<queue>
using std::cout;
using std::endl;
using std::cin;
using std::queue;

namespace d_search
{
	bool FINISHED = false;
	int TIME = 0;
	bool processed[MAXV];
	bool discovered[MAXV];
	int parent[MAXV];
	int entry_time[MAXV];
	int exit_time[MAXV];
	graph* tt = new graph;

	void init_graph(graph* g, bool directed)
	{
		g->nvertices = 0;
		g->nedges = 0;
		g->directed = directed;

		for(int i = 1; i <= MAXV; i++)
		{
			g->edges[i] = nullptr;
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

	void dfs(graph* g, int v)
	{
		int y = -1;
		edgenode* p = new edgenode;
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

	void process_vertex_early(int x)
	{
		cout << "Processing the vertex: " << x << endl;
	}

	void process_vertex_late(int x)
	{
		tt->nvertices++;
	}

	void process_edge(int x, int y)
	{
		//cout << "Processing the edge: (" << x << ", " << y << ")\n";
		//if(discovered[y] && parent[x] != y)
		//	if(parent[parent[x]] == y)
		//	{
		//		cout << "A triangle is found: " << x << " " << y << " " << parent[x] << endl;
		//	}

		insert_edge(tt, x, y, tt->directed);
	}
}

namespace b_search
{
	bool processed[MAXV];
	bool discovered[MAXV];
	int parent[MAXV];

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

	void process_edge(int x, int y)
	{
		cout << "The edge (" << x << ", " << y << ") is processed\n";
	}

	void process_vertex_early(int x)
	{
		cout << "Processing the vertex: " << x << endl;
	}

	void process_vertex_late(int x)
	{
	}
}
