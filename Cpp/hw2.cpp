/*
	
	Homework 2

	Implement Dijkstra's Algorithm
	
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <queue>
using namespace std;

/*
	PART 1

	Define a graph class

*/

// Small function for generating random edges and weight

inline double prob() { return (static_cast<double>(rand())/RAND_MAX); }

inline int rand_weight(int w) { return (rand() % w + 1); }

class Graph
{
public:
	Graph();
	Graph(int s, double d, int w);
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


/*

	PART 2

	Define a Priority-Queue class

*/

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


/*

	PART 3

	Define a Shortest-Path class

*/


// List storing the path

struct Point
{
	int index;
	Point* next;
};

class ShortestPath
{
public:
	ShortestPath();
	ShortestPath(Graph g);
	int path_size(int start, int end);
	Point* spath(int start, int end);

private:
	int n;
	bool* close;
	PriorityQueue open;
	int* distance;
	Point* ptr;
	Point* head;
	Graph g_path;
};

// Constructor

ShortestPath::ShortestPath()
{
	g_path = Graph();
	n = 0;
	close = new bool[1];
	ptr = head = NULL;
	distance = new int[1];
}

ShortestPath::ShortestPath(Graph g)
{
	g_path = g;
	n = g_path.vertices();
	close = new bool[n];
	for (int i = 0; i < n; ++i) close[i] = false;
	head = ptr = NULL;
	distance = new int[n];
}

// Return shortest path by a list

Point* ShortestPath::spath(int start, int end)
{
	head = new Point;
	head->index = start;
	head->next = NULL;
	//cout << "1 : " << start << endl;

	if (start == end) return head;

	int parent = start;
	int* lst;
	Point* prev = head;

	open = PriorityQueue(g_path, parent);
	close[parent] = true;
	distance[0] = 0;


	//cout << "    distance = " << distance[0] << endl;

	for (int i = 1; i < n; ++i)
	{
		// quit if no element in queue

		if (open.size() == 0) break;

		parent = open.top();
		close[parent] = true;

		ptr = new Point;
		ptr->index = parent;
		ptr->next = NULL;
		prev->next = ptr;

		//cout << i << " : " << parent << endl;


		distance[i] = open.minValue();
		// cout << "    distance = " << distance[i] << endl;

		open.minPriority();
		if (close[end] == true) return head;

		lst = g_path.neighbours(parent);
		for (int j = 0; j < n; ++j)
		{
			if (lst[j] >= 0)
			{
				if (!close[lst[j]]) open.insert(lst[j], g_path.get_edge_value(parent, lst[j]));
			}
		}
		prev = ptr;	
	}
	if (close[end]) return head;
	else return NULL;
}

int ShortestPath::path_size(int start, int end)
{
	if (ptr->index != end || head->index != start)
	{
		Point* p = spath(start, end);
	}
	int dis = 0;
	for (int i = 0; i < n; ++i)
	{
		dis += distance[i];
	}
	return dis;
}


/*

	PART 4

	Main function for testing

*/


int main()
{
	// Generate a random graph with 50 vertices, max distance = 20, density = 0.1

	Graph eg_g = Graph(50, 0.1, 20);
	int n = eg_g.vertices();
	int k;

	// Print distance between vertices

	cout << "matrix for paths" << endl;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << eg_g.get_edge_value(i, j);
			if (j == n - 1) cout << endl;
			else cout << '\t';
		}
	}
	/*
	PriorityQueue pq = PriorityQueue(eg_g, 0);
	cout << "size is " << pq.size() << endl;
	cout << "minimum weight is " << pq.minValue() << " by " << pq.top() << endl;
	int size = pq.size();
	for (int i = 0; i < size; ++i)
	{
		pq.minPriority();
	}
	*/

	// Calculate shortest path between 0 and 10;

	ShortestPath sp = ShortestPath(eg_g);
	Point* list = sp.spath(0, 10);

	// Print vertices of shortest path and minimum cost

	cout << endl << endl << "Shortest path is: " << endl;
	while (list != NULL)
	{
		cout << list->index;
		list = list->next;
		if (list != NULL) cout << " - ";
	}
	cout << endl;
	cout << "cost is " << sp.path_size(0, 5) << endl;

	return 0;
}