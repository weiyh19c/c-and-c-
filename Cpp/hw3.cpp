//====================================================================
/*
	Homework 3

	Compute Prim MST
*/
//====================================================================
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

//====================================================================
/*
	PART 1

	Define a graph class
*/
//====================================================================

// Small function for generating random edges and weight

inline double prob() { return (static_cast<double>(rand())/RAND_MAX); }

inline int rand_weight(int w) { return (rand() % w + 1); }

class Graph
{
public:
	Graph();
	Graph(int s, double d, int w);
	Graph(string filename);
	int vertices();
	int edges();
	bool adjacent(int x, int y);
	int* neighbours(int x);
	void add_edge(int x, int y);
	void delete_edge(int x, int y);
	int get_node_value(int x);
	int get_edge_value(int x, int y);
	void set_edge_value(int x, int y, int v);

private:
	int size;
	double density;
	int max_weight;
	int edge;
	bool** path;
	int** weight;
};

// Constructor

Graph::Graph()
{
	size = 1;
	density = 0;
	max_weight = 1;
	edge = 0;
	path = new bool*[1];
	path[0] = new bool[1];
	path[0][0] = false;
	weight = new int*[1];
	weight[1] = new int[1];
}

Graph::Graph(int s, double d, int m)
{
	size = s; 
	density = d;
	max_weight = m;
	edge = 0;
	path = new bool*[size];
	weight = new int*[size];
	srand(time(0));

	for (int i = 0; i < size; ++i)
	{
		path[i] = new bool[size];
		weight[i] = new int[size];
	}


	// Generate random matrix

	for (int i = 0; i < size; ++i)
	{
		for (int j = i; j < size; ++j)
		{
			if (i == j) path[i][j] = false;
			else
			{
				path[i][j] = path[j][i] = (prob() < density);
				if (path[i][j]) 
				{
					weight[i][j] = weight[j][i] = rand_weight(max_weight);
					edge++;
				}

			}
		}
	}

}

Graph::Graph(string filename)
{
	ifstream fin;
	fin.open(filename);
	fin >> size;

	path = new bool*[size];
	weight = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		path[i] = new bool[size];
		weight[i] = new int[size];
	}

	int i, j;

	while (!fin.eof())
	{
		fin >> i;
		fin >> j;
		fin >> weight[i][j];
		path[i][j] = (weight[i][j] > 0);
	}

}

int Graph::vertices() { return size; }

int Graph::edges() { return edge; }

bool Graph::adjacent(int x, int y) { return path[x][y]; }

// List for adjacent nodes
int* Graph::neighbours(int x)
{
	int n = 0;
	int* nbs = new int[size];
	for (int i = 0; i < size; ++i)
	{
		nbs[i] = -1;
		if (path[x][i]) 
		{
			nbs[n] = i;
			n++;
		}

	}
	return nbs;
}

void Graph::add_edge(int x, int y)
{
	if (!path[x][y])
	{
		path[x][y] = path[y][x] = true;
		weight[x][y] = weight[x][y] = rand_weight(max_weight);
		edge++;
	}
}

void Graph::delete_edge(int x, int y)
{
	if (path[x][y])
	{
		path[x][y] = path[y][x] = false;
		weight[x][y] = weight[y][x] = 0;
		edge--;
	}
}

int Graph::get_node_value(int x)
{
	int v = 0;
	for (int i = 0; i < size; ++i)
	{
		v += weight[x][i];
	}
	return v;
}

int Graph::get_edge_value(int x, int y) { return (weight[x][y]); }

void Graph::set_edge_value(int x, int y, int a) { weight[x][y] = weight[y][x] = a; }


//====================================================================
/*
	PART 2

	Define a Priority-Queue class
*/
//====================================================================

// Define element of prorioty queue to parent node
// with index of node, value of distance and pointer to next node

struct Node
{
	int vertex;
	int value;
	Node* next;
};

class PriorityQueue
{
public:
	PriorityQueue();
	PriorityQueue(Graph g, int start);
	int top();
	int minValue();
	int size();
	void minPriority();
	void chgPriority(int index, int p);
	bool contains(int index);
	void insert(int index, int p);

private:
	Node* queue_top;
	Node* queue_rear;
	Node* ptr;
	void minOnTop();
};

// Let node with minimum distance on top 

void PriorityQueue::minOnTop()
{
	ptr = queue_top->next;
	int temp_p, temp_i;
	while (ptr != NULL)
	{
		if (ptr->value < queue_top->value)
		{
			temp_i = ptr->vertex;
			temp_p = ptr->value;
			ptr->vertex = queue_top->vertex;
			ptr->value = queue_top->value;
			queue_top->vertex = temp_i;
			queue_top->value = temp_p;
		}
		ptr = ptr->next;
	}
}

// Constructor

PriorityQueue::PriorityQueue() 
{  
	queue_top = new Node;
	queue_top->vertex = -1;
	queue_top->value = 0;
	queue_top->next = NULL;
	queue_rear = NULL;
};

PriorityQueue::PriorityQueue(Graph g, int start)
{
	int n = g.vertices();
	int* lst = g.neighbours(start);

	queue_top = NULL;
	Node* prev = new Node;

	for (int i = 0; i < n; ++i)
	{
		if (lst[i] >= 0)
		{
			ptr = new Node;
			ptr->next = NULL;
			if (queue_top == NULL)
			{
				queue_top = ptr;
			}
			else
			{
				prev->next = ptr;
			}
			ptr->vertex = lst[i];
			ptr->value = g.get_edge_value(start, lst[i]);
			prev = ptr;
		}
	}
	queue_rear = prev;
	if (queue_top != NULL) minOnTop();
	// cout << "Queue completed" << endl;
}


int PriorityQueue::top() { return queue_top->vertex; }

int PriorityQueue::minValue() {return queue_top->value; }

// Return number of elements in queue

int PriorityQueue::size()
{
	int n = 0;
	ptr = queue_top;
	while (ptr != NULL) 
	{
		++n;
		ptr = ptr->next;
	}
	return n;
}

bool PriorityQueue::contains(int index)
{
	ptr = queue_top;
	while (ptr != NULL)
	{
		if (ptr->vertex == index) return true;
		ptr = ptr->next;
	}
	return false;
}

// Pop up element on top & sort again

void PriorityQueue::minPriority()
{
	// cout << "min value is " << minValue() << " by node of " << top() << endl;
	queue_top = queue_top->next;
	if (queue_top == NULL) 
	{
		queue_rear = NULL;
		// cout << "Queue is empty now" << endl;
	}
	else minOnTop();
}

// Change the priority of existing vertex with smaller new value
void PriorityQueue::chgPriority(int index, int p)
{
	ptr = queue_top;
	while (ptr != NULL)
	{
		if ((ptr->vertex == index) && (ptr->value > p)) 
		{
			ptr->value = p;
			break;
		}
		ptr = ptr->next;
	}
	if (queue_top != NULL) minOnTop();
}

// See if certain index in the queue, if not, insert
void PriorityQueue::insert(int index, int p)
{
	if (contains(index)) chgPriority(index, p);
	else
	{
		Node* nd = new Node;
		nd->vertex = index;
		nd->value = p;
		nd->next = NULL;
		queue_rear->next = nd;
		queue_rear = nd;
		minOnTop();
	}
}

//====================================================================
/*
	PART 3

	Define a Prim Minimum Spanning Tree class
*/
//====================================================================

// List storing the path

struct Point
{
	int index;
	Point* next;
};

class MinimumSpanTree
{
public:
	MinimumSpanTree();
	MinimumSpanTree(Graph g, int start);
	int size();
	Point* path_list();
	int* cost_list();
	int total_cost();

private:
	int m_size;
	bool* m_close;
	PriorityQueue m_open;
	int* m_cost;
	Point* m_ptr;
	Point* m_head;
};

// Constructor

MinimumSpanTree::MinimumSpanTree()
{
	m_size = 0;
	m_close = new bool[1];
	m_ptr = m_head = NULL;
	m_cost = new int[1];
}

MinimumSpanTree::MinimumSpanTree(Graph g, int start)
{
	m_size = g.vertices();
	m_close = new bool[m_size];
	for (int i = 0; i < m_size; ++i) m_close[i] = false;
	m_cost = new int[m_size];
	m_head = m_ptr = NULL;

	m_close[start] = true;
	m_open = PriorityQueue(g, start);
	m_cost[0] = 0;

	m_head = new Point;
	m_head->index = start;
	m_head->next = NULL;

	// Define temp variables used in for cycle
	int m_next_vertex;
	Point* parent_p = m_head;
	int* adjacent_point;

	for (int i = 1; i < m_size; ++i)
	{
		if (m_open.size() == 0) break;

		// Get point with current minimum cost
		m_next_vertex = m_open.top();

		// Put the point in close set
		m_close[m_next_vertex] = true;

		// Get this cost in cost list
		m_cost[i] = m_open.minValue();

		// Pop the element up
		m_open.minPriority();

		// Put the point in order, after parent node
		m_ptr = new Point;
		m_ptr->index = m_next_vertex;
		m_ptr->next = NULL;
		parent_p->next = m_ptr;


		// Update cost of the new node in PriorityQueue
		adjacent_point = g.neighbours(m_next_vertex);
		for (int j = 0; j < m_size; ++j)
		{
			if (adjacent_point[j] >= 0)
			{
				if (!m_close[adjacent_point[j]])
				{
					m_open.insert(adjacent_point[j], g.get_edge_value(m_next_vertex, adjacent_point[j]));
				}
			}
		}
		parent_p = m_ptr;
	}
}


int MinimumSpanTree::size() { return m_size; }

Point* MinimumSpanTree::path_list() { return m_head; }

int* MinimumSpanTree::cost_list() { return m_cost; }

int MinimumSpanTree::total_cost()
{
	int total = 0;
	if (m_cost[m_size] == 0) return total;
	else
	{
		for (int i = 0; i < m_size; ++i) total += m_cost[i];
	}
	return total;
}



//====================================================================
/*
	PART 4

	Main function for testing
*/
//====================================================================

int main()
{
	// Read from text file for cost data

	string f = "Sample_Data.txt";
	Graph g = Graph(f);
	int n = g.vertices();

	cout << "matrix for paths" << endl;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << g.get_edge_value(i, j);
			if (j == n - 1) cout << endl;
			else cout << '\t';
		}
	}

	// Generate MST item for simulation

	MinimumSpanTree mst = MinimumSpanTree(g, 0);
	Point* list = mst.path_list();
	Point* next;
	int* c_list = mst.cost_list();
	int i = 1;


	// Print vertices of shortest path and minimum cost

	cout << endl << endl << "Shortest path is ---- " << endl << endl;
	while (list != NULL)
	{
		if (list->next == NULL) 
		{
			cout << endl << "The end" << endl;
			break;
		}
		else
		{
			next = list->next;
			cout << list->index << " to " << next->index << ", cost = " << c_list[i] << endl;
			list = next;
			++i;
		}

	}
	cout << endl << endl;
	cout << "Total cost is " << mst.total_cost() << endl;


	return 0;
}