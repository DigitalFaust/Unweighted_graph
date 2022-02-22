#include<iostream>
#include"bfsh.h"
using std::cout;
using std::endl;
using namespace bfspace;

void print_induced(graph* g);

int main()
{
	graph* g = new graph;
	bool directed = false;

	init_graph(g, directed);
	read_graph(g, directed);
	print_graph(g);
	
	cout << "Enter k: ";
	std::cin >> k;
	bfs(g, 1);
	cout << "The induced graph of degree not less than " << k << ": ";
	print_induced(g);

	return 0;
}

void print_induced(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
	{
		if(induced[i] != 0)
			cout << "[" << i << " : " << induced[i] << "] ";
	}
	cout << endl;
}
