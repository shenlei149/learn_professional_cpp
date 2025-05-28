#include <algorithm>
#include <set>
#include <vector>

namespace graph
{

template<typename T>
class DirectedGraph;

namespace details
{

template<typename T>
class GraphNode
{
public:
	// Constructs a GraphNode for the given value.
	explicit GraphNode(DirectedGraph<T> *graph, T t)
		: graph_(graph)
		, data_(std::move(t))
	{
	}

	// Returns a reference to the stored value.
	[[nodiscard]]
	const T &
	Value() const noexcept
	{
		return data_;
	}

	// Type alias for the container type used to store the adjacency list.
	using adjacency_list_type = std::set<std::size_t>;

	// Returns a reference to the adjacency list.
	[[nodiscard]]
	auto &
	GetAdjacentNodesIndices()
	{
		return adjacentNodeIndices_;
	}

	[[nodiscard]]
	const auto &
	GetAdjacentNodesIndices() const
	{
		return adjacentNodeIndices_;
	}

	void
	RemoveNodeIndex(std::size_t nodeIndex)
	{
		adjacentNodeIndices_.erase(nodeIndex);

		std::vector<std::size_t> indices(std::begin(adjacentNodeIndices_), std::end(adjacentNodeIndices_));
		std::for_each(std::begin(indices),
					  std::end(indices),
					  [nodeIndex](std::size_t &index)
					  {
						  if (index > nodeIndex)
						  {
							  --index;
						  }
					  });

		adjacentNodeIndices_.clear();
		adjacentNodeIndices_.insert(std::begin(indices), std::end(indices));
	}

private:
	// A pointer to the graph this node is in.
	DirectedGraph<T> *graph_;
	T data_;

	adjacency_list_type adjacentNodeIndices_ {};
};

} // namespace details

template<typename T>
class DirectedGraph
{
	template<typename DirectedGraph>
	class ConstDirectedGraphIterImpl
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;

		using value_type = typename DirectedGraph::value_type;
		using difference_type = std::ptrdiff_t;
		using pointer = const value_type *;
		using reference = const value_type &;
		using node_container_iterator = typename DirectedGraph::node_container_type::const_iterator;

		// Bidirectional iterators must supply a default constructor.
		ConstDirectedGraphIterImpl() = default;

		explicit ConstDirectedGraphIterImpl(node_container_iterator it)
			: nodeIter_(it)
		{
		}

		reference
		operator*() const
		{
			return nodeIter_->Value();
		}

		pointer
		operator->() const
		{
			return &nodeIter_->Value();
		}

		ConstDirectedGraphIterImpl &
		operator++()
		{
			++nodeIter_;
			return *this;
		}

		ConstDirectedGraphIterImpl
		operator++(int)
		{
			auto old { *this };
			++*this;
			return old;
		}

		ConstDirectedGraphIterImpl &
		operator--()
		{
			--nodeIter_;
			return *this;
		}

		ConstDirectedGraphIterImpl
		operator--(int)
		{
			auto old { *this };
			--*this;
			return old;
		}

		// Defaulted operator==.
		bool operator==(const ConstDirectedGraphIterImpl &) const = default;

	private:
		// friend class DirectedGraph<value_type>;
		node_container_iterator nodeIter_;
	};

public:
	using value_type = T;
	using reference = value_type &;
	using const_reference = const value_type &;
	using iterator = ConstDirectedGraphIterImpl<DirectedGraph>;
	using const_iterator = const ConstDirectedGraphIterImpl<DirectedGraph>;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

public: // Iterator member functions
	iterator
	begin() noexcept
	{
		return iterator { std::begin(nodes_) };
	}

	iterator
	end() noexcept
	{
		return iterator { std::end(nodes_) };
	}

	const_iterator
	begin() const noexcept
	{
		return const_iterator { std::begin(nodes_) };
	}

	const_iterator
	end() const noexcept
	{
		return const_iterator { std::end(nodes_) };
	}

	const_iterator
	cbegin() const noexcept
	{
		return begin();
	}

	const_iterator
	cend() const noexcept
	{
		return end();
	}

public:
	// For insert to be successful, the value shall not be in the graph yet.
	// Returns true if a new node with given value has been added to
	// the graph, and false if there was already a node with the given value.
	std::pair<iterator, bool> Insert(T nodeValue);

	// Returns true if the given node value was erased, false otherwise.
	bool Erase(const T &nodeValue);

	// Returns true if the edge was successfully created, false otherwise.
	bool InsertEdge(const T &fromNodeValue, const T &toNodeValue);

	// Returns true if the given edge was erased, false otherwise.
	bool EraseEdge(const T &fromNodeValue, const T &toNodeValue);

	// Removes all nodes from the graph.
	void
	Clear() noexcept
	{
		nodes_.clear();
	}

	// Returns a reference to the value in the node with given index
	// without bounds checking.
	const_reference
	operator[](size_type index) const
	{
		return nodes_[index].Value();
	}

	const_reference
	at(size_type index) const
	{
		return nodes_.at(index).Value();
	}

	// Two directed graphs are equal if their sets of nodes are equal (where
	// nodes with the same T value are considered equal) and the same number
	// of edges between each corresponding pair of nodes.
	// The order in which the nodes and edges have been added does not
	// affect equality.
	bool operator==(const DirectedGraph &rhs) const;

	// Swaps all nodes between this graph and the given graph.
	// Starting with lowercase letters is to meet STL requirements
	void
	swap(DirectedGraph &other) noexcept
	{
		nodes_.swap(other.nodes_);
	}

	// Returns the number of nodes in the graph.
	[[nodiscard]]
	size_type
	size() const noexcept
	{
		return nodes_.size();
	}

	[[nodiscard]]
	size_type
	max_size() const noexcept
	{
		return nodes_.max_size();
	}

	[[nodiscard]]
	bool
	empty() const noexcept
	{
		return nodes_.empty();
	}

	// Returns a set with the values of the adjacent nodes of a given node.
	// If the given node does not exist, an empty set is returned.
	[[nodiscard]]
	std::set<T>
	GetAdjacentNodesValues(const typename details::GraphNode<T>::adjacency_list_type &indices) const;

private:
	using node_container_type = std::vector<details::GraphNode<T>>;

	std::size_t
	GetIndexOfNode(typename node_container_type::const_iterator node) const noexcept
	{
		return node - std::cbegin(nodes_);
	}

	void
	RemoveAllLinksTo(typename node_container_type::const_iterator nodeIter)
	{
		const std::size_t nodeIndex { GetIndexOfNode(nodeIter) };
		for (auto &&node : nodes_)
		{
			node.RemoveNodeIndex(nodeIndex);
		}
	}

	// Helper member function to return an iterator to the given node, or the
	// end iterator if the given node is not in the graph.
	typename node_container_type::iterator FindNode(const T &nodeValue);
	typename node_container_type::const_iterator FindNode(const T &nodeValue) const;

private:
	node_container_type nodes_;

	friend class ConstDirectedGraphIterImpl<DirectedGraph>;
};

template<typename T>
void
swap(DirectedGraph<T> &first, DirectedGraph<T> &second) noexcept
{
	first.swap(second);
}

template<typename T>
inline std::pair<typename DirectedGraph<T>::iterator, bool>
DirectedGraph<T>::Insert(T nodeValue)
{
	auto iter { FindNode(nodeValue) };
	if (iter != std::end(nodes_))
	{
		// Value is already in the graph, return false.
		return { iterator { iter }, false };
	}

	nodes_.emplace_back(this, std::move(nodeValue));
	return { iterator { std::prev(std::end(nodes_)) }, true };
}

template<typename T>
inline bool
DirectedGraph<T>::Erase(const T &nodeValue)
{
	auto iter { FindNode(nodeValue) };
	if (iter == std::end(nodes_))
	{
		return false;
	}

	RemoveAllLinksTo(iter);
	nodes_.erase(iter);
	return true;
}

template<typename T>
inline bool
DirectedGraph<T>::InsertEdge(const T &fromNodeValue, const T &toNodeValue)
{
	const auto from { FindNode(fromNodeValue) };
	const auto to { FindNode(toNodeValue) };
	if (from == std::end(nodes_) || to == std::end(nodes_))
	{
		return false;
	}

	const std::size_t toIndex { GetIndexOfNode(to) };
	return from->GetAdjacentNodesIndices().insert(toIndex).second;
}

template<typename T>
inline bool
DirectedGraph<T>::EraseEdge(const T &fromNodeValue, const T &toNodeValue)
{
	const auto from { FindNode(fromNodeValue) };
	const auto to { FindNode(toNodeValue) };
	if (from == std::end(nodes_) || to == std::end(nodes_))
	{
		return false;
	}

	const std::size_t toIndex { GetIndexOfNode(to) };
	from->GetAdjacentNodesIndices().erase(toIndex);
	return true;
}

template<typename T>
inline bool
DirectedGraph<T>::operator==(const DirectedGraph &rhs) const
{
	if (nodes_.size() != rhs.nodes_.size())
	{
		return false;
	}

	for (auto &&node : nodes_)
	{
		const auto rhsNodeIter { rhs.FindNode(node.Value()) };
		if (rhsNodeIter == std::end(rhs.nodes_))
		{
			return false;
		}

		const auto adjacentLhsValues { GetAdjacentNodesValues(node.GetAdjacentNodesIndices()) };
		const auto adjacentRhsValues { GetAdjacentNodesValues(rhsNodeIter->GetAdjacentNodesIndices()) };
		if (adjacentLhsValues != adjacentRhsValues)
		{
			return false;
		}
	}

	return true;
}

template<typename T>
inline std::set<T>
DirectedGraph<T>::GetAdjacentNodesValues(
	const typename details::GraphNode<T>::adjacency_list_type &indices) const
{
	std::set<T> values;
	for (auto &&index : indices)
	{
		values.insert(nodes_[index].Value());
	}

	return values;
}

template<typename T>
inline typename DirectedGraph<T>::node_container_type::iterator
DirectedGraph<T>::FindNode(const T &nodeValue)
{
	return std::find_if(std::begin(nodes_),
						std::end(nodes_),
						[&](const auto &node)
						{
							return node.Value() == nodeValue;
						});
}

template<typename T>
inline typename DirectedGraph<T>::node_container_type::const_iterator
DirectedGraph<T>::FindNode(const T &nodeValue) const
{
	return std::find_if(std::cbegin(nodes_),
						std::cend(nodes_),
						[&](const auto &node)
						{
							return node.Value() == nodeValue;
						});
}

} // namespace graph
