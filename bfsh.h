#ifndef BSFH_H
#define BFSH_H

namespace bfspace
{
	constexpr int MAXV = 100;
	constexpr int SIZE = MAXV + 1;
	extern bool processed[SIZE];
	extern bool discovered[SIZE];
	extern int parent[SIZE];
	extern int dmtr[SIZE];
	extern int incident[SIZE];
	extern int induced[SIZE];
	extern int k;

	struct edgenode
	{
		int y;
		int weight;
		edgenode* next;
	};

	struct graph
	{
		edgenode* edges[SIZE];
		int degree[SIZE];
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
}

#endif //BFSH_H
