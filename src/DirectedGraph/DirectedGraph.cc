#include "DirectedGraph.h"

namespace graph
{ // for compile

std::size_t
test()
{
	DirectedGraph<int> graph;
	graph.Insert(1);
	graph.Insert(2);
	graph.Insert(3);
	graph.Insert(4);
	graph.Insert(5);

	graph.InsertEdge(1, 3);
	graph.InsertEdge(2, 3);
	graph.InsertEdge(2, 4);
	graph.InsertEdge(2, 5);
	graph.InsertEdge(4, 5);

	graph.EraseEdge(2, 4);
	graph.Erase(4);

	return graph.size();
}

} // namespace graph
