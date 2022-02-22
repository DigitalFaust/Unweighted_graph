#include<iostream>
#include"bfsh.h"
using std::cout;
using std::cin;
using std::endl;
using namespace bfspace;

void print_dmtr(graph* g);

int main()
{
	graph *g = new graph;
	bool directed = false;

	init_graph(g, directed);
	read_graph(g, directed);
	print_graph(g);

	cout << "Counting the graph's diameter...\n";
	for(int i = 1; i <= g->nvertices; i++)
	{
		if(discovered[i] == false)
			bfs(g, i);
	}
	print_dmtr(g);

	return 0;
}

void print_dmtr(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
		cout << "[" << i << " : " << dmtr[i] << "] ";
	cout << endl;
}
