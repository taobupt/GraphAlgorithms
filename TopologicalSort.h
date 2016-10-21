#include"Header.h"




// topological sort
bool Kahn()// a way of topological sort
{
	int num = 0;
	scanf("%d", &num);
	printf("the graph has %d nodes\n", num);
	unordered_map<int, int>indegree;
	unordered_map<int, list<int>>adj;
	queue<int>q;
	int edgeStart = 0, edgeEnd = 0;
	while (scanf("%d%d", &edgeStart, &edgeEnd)==2)
	{
		
		adj[edgeStart].push_back(edgeEnd);
		indegree[edgeEnd]++;
		if (indegree.find(edgeStart) == indegree.end())indegree[edgeStart] = 0;
	}
	for (unordered_map<int, int>::iterator it = indegree.begin(); it != indegree.end(); ++it)
	{
		if (it->second == 0)q.push(it->first);
	}
	int node = 0;
	while (!q.empty())
	{
		node = q.front();
		q.pop();
		num--;
		if(num!=0)printf("%d ->", node);
		else printf("%d", node);
		for (auto it = adj[node].begin(); it != adj[node].end(); ++it)
		{
			--indegree[*it];
			if (indegree[*it] == 0)q.push(*it);
		}
	}
	printf("\n");
	return num == 0;//detect cycle
}




// topological sort by dfs
void dfs(int node, unordered_map<int, bool>& vis, unordered_map<int, list<int>>& adj,stack<int>& stk)
{
	for (int x : adj[node])
	{
		if (!vis[x])
		{
			vis[x] = true;
			dfs(x, vis, adj,stk);
			stk.push(x);
		}
	}
}


void dfsVisit()
{
	int num = 0;
	scanf("%d", &num);//number of nodes
	printf("the graph has %d nodes\n", num);
	unordered_map<int, list<int>>adj;
	unordered_map<int, bool>vis;
	int edgeStart = 0, edgeEnd = 0;//input 
	while (scanf("%d%d", &edgeStart, &edgeEnd) == 2)
	{
		adj[edgeStart].push_back(edgeEnd);
		vis[edgeStart] = false;
		vis[edgeEnd] = false;
	}
	stack<int>stk;
	for (auto it = vis.begin(); it != vis.end(); ++it)
	{
		if (!it->second)
		{
			it->second = true;
			dfs(it->first, vis, adj,stk);
			stk.push(it->first);
		}
	}
	while (!stk.empty())
	{
		printf("%d ", stk.top());
		stk.pop();
	}
}









//--- undirected graph detect cycle  time complexity O(ELogV).
class UnionFind
{
public:
	UnionFind(vector<int>num)
	{
		for (int x : num)father[x] =x;
	}

	int findroot(int x)
	{
		if (x != father[x])
		{
			father[x] = father[father[x]];
			x = father[x];
		}
		return x;
	}

	void Union(int x, int y)
	{
		int xx = findroot(x);
		int yy = findroot(y);
		if (xx != yy)father[yy] = xx;
	}

private:
	unordered_map<int, int>father;
};


//undirected graph
struct Edge{
	int src;
	int des;
	Edge(int src, int des) :src(src), des(des){}
};
bool hascycle()
{
	int num = 0;
	scanf("%d", &num);//number of nodes
	printf("the graph has %d nodes\n", num);
	unordered_set<int>s;
	int edgeStart = 0, edgeEnd = 0;//input 
	vector<Edge>edge;
	while (scanf("%d%d", &edgeStart, &edgeEnd) == 2)
	{
		edge.push_back(Edge(edgeStart, edgeEnd));
		s.insert(edgeStart);
		s.insert(edgeEnd);
	}
	vector<int>nums(s.begin(), s.end());
	UnionFind uf(nums);
	for (Edge it : edge)
	{
		int xx = uf.findroot(it.src);
		int yy = uf.findroot(it.des);
		if (xx != yy)uf.Union(xx, yy);
		else return true;
	}
	return false;
}

// directed graph detect cycle by dfs

class Graph{
public:
	Graph(vector<int>nums,vector<Edge>edge)
	{
		vertexs = nums;
		for (Edge e : edge)
		{
			//adj[e.des].push_back(e.src);
			adj[e.src].push_back(e.des);
		}
		for (int x : nums)
		{
			parent[x] = -1;
			color[x] = "WHITE";
		}
	}

	void addEdge( Edge e)
	{
		adj[e.des].push_back(e.src);
		adj[e.src].push_back(e.des);
	}
public:
	vector<int>vertexs;
	unordered_map<int, int>parent;
	unordered_map<int, string>color;
	unordered_map<int, list<int>>adj;
};

void PrintCycle(int v, int u, Graph& g)
{
	if (v == u)printf("%d ", v);
	else
	{
		PrintCycle(g.parent[v], u, g);
		printf("%d ", v);
	}
}

void Visit(int u, Graph& g)
{
	bool cycle = false;
	g.color[u] = "GRAY";
	int vv = 0;
	for (int v : g.adj[u])
	{
		if (g.color[v] == "WHITE")
		{
			g.parent[v] = u;
			Visit(v, g);
		}
		else if (g.color[v] == "GRAY")
		{
			cycle = true;
			vv = v;
			g.parent[v] = u;
			break;
		}
	}
	g.color[u] = "BLACK";
	if(cycle)PrintCycle(u, vv,g);
}

void dfsDetectCycle()
{
	int num = 0;
	scanf("%d", &num);//number of nodes
	unordered_set<int>s;
	int edgeStart = 0, edgeEnd = 0;//input 
	vector<Edge>edge;
	while (scanf("%d%d", &edgeStart, &edgeEnd) == 2)
	{
		edge.push_back(Edge(edgeStart, edgeEnd));
		s.insert(edgeStart);
		s.insert(edgeEnd);
	}
	vector<int>vertex(s.begin(), s.end());
	Graph g(vertex, edge);
	for (int u : g.vertexs)
	{
		if (g.color[u] == "WHITE")Visit(u,g);
	}
}