#include <stdio.h>
#include <list>
#include <stack>
using namespace std;

#define min(a,b) (((a) < (b)) ? (a) : (b))

#define N 15

list<int>  e[N];
int pre[N], parent[N], visited[N], is_articulate[N], child[N], low[N];
int is_bridge[N][N];
int _clock = 0;
int bcc_count = 0;
stack<pair<int, int>> sta;

void explore(int z)
{
	pre[z] = low[z] = _clock ++;
	visited[z] = 1;

	for(auto it = e[z].begin(); it != e[z].end() ; it ++)
	{
		int w = *it;
		if (w == parent[z])
			continue;

		if (visited[w] == 0)
		{
			child[z] ++;
			parent[w] = z;
			sta.push(pair<int, int>(z, w));
			explore(w);
			low[z] = min(low[z], low[w]);

			if (low[w] >= pre[z] && parent[z] != -1)
			{
				is_articulate[z] = 1;

				while (true)
				{
					pair<int, int> edge = sta.top();
					printf("%d-%d  ", edge.first, edge.second);
					sta.pop();
					if (edge.first == z && edge.second == w)
					{
						bcc_count++;
						break;
					}
				}
				printf("\n");
			}
			if (low[w] > pre[z])
				is_bridge[z][w] = 1;
		}
		else if (pre[w] < pre[z])
		{
			sta.push(pair<int, int>(z, w));
			low[z] = min(low[z], pre[w]);
		}
	}
}

void DFS()
{
	_clock = 1;
	for (int v = 0; v < N; v++)
	{
		parent[v] = -1;
		visited[v] = 0;
		is_articulate[v] = 0;
		child[v] = 0;
		low[v] = -1;
	}

	for (int u = 0; u < N; u++)
	{
		for (int v = 0; v < N; v++)
		{
			is_bridge[u][v] = 0;
		}
	}

	for (int v = 0; v < N; v++)
	{
		if (visited[v] == 0)
		{
			explore(v);
			if (child[v] > 1)
				is_articulate[v] = 1;
			else
				bcc_count++;

			while (!sta.empty())
			{
				pair<int, int> edge = sta.top();
				printf("%d-%d  ", edge.first, edge.second);
				sta.pop();
			}
			printf("\n");
		}
	}
}

int main()
{
	// graph definition
	//e[0].push_front(1); e[0].push_front(6);
	//e[1].push_front(0); e[1].push_front(2); e[1].push_front(3); e[1].push_front(5);
	//e[2].push_front(1); e[2].push_front(3); e[2].push_front(4);
	//e[3].push_front(1); e[3].push_front(2); e[3].push_front(4);
	//e[4].push_front(2); e[4].push_front(3);
	//e[5].push_front(1); e[5].push_front(6); e[5].push_front(7); e[5].push_front(8); 
	//e[6].push_front(0); e[6].push_front(5);
	//e[7].push_front(5); e[7].push_front(8);
	//e[8].push_front(5); e[8].push_front(7); e[8].push_front(9);
	//e[9].push_front(8); 
	//e[10].push_front(11);
	//e[11].push_front(10);

	e[0].push_front(1); e[0].push_front(14);
	e[1].push_front(0); e[1].push_front(3); e[1].push_front(13);
	e[2].push_front(3);
	e[3].push_front(1); e[3].push_front(2); e[3].push_front(4); e[3].push_front(12);
	e[4].push_front(3); e[4].push_front(11);
	e[5].push_front(6); e[5].push_front(7); e[5].push_front(8);
	e[6].push_front(5); e[6].push_front(7);
	e[7].push_front(5); e[7].push_front(6); e[7].push_front(8); e[7].push_front(10);
	e[8].push_front(5); e[8].push_front(7); e[8].push_front(9);
	e[9].push_front(8); e[9].push_front(10); e[9].push_front(11);
	e[10].push_front(7); e[10].push_front(9); e[10].push_front(11);
	e[11].push_front(3); e[11].push_front(4); e[11].push_front(9); e[11].push_front(10);
	e[12].push_front(3);
	e[13].push_front(1); e[13].push_front(14);
	e[14].push_front(0); e[14].push_front(13);

	// do DFS and output biconnected components at the same time
	printf("Biconnected components\n");
	DFS();
	printf("There are %d biconnected components\n\n", bcc_count);

	// output articulation
	printf("Articulations\n");
	for (int v = 0; v < N; v++)
	{
		if (is_articulate[v] == 1)
			printf("%d ", v);
	}

	// output bridges
	printf("\nBridges\n");
	for (int u = 0; u < N; u++)
	{
		for (int v = 0; v < N; v++)
		{
			if (is_bridge[u][v] == 1)
				printf("(%d, %d) ", u, v);
		}
	}

	printf("\n");
	//cout << "Above are " << visit_count << " biconnected components in graph";

	return 0;
}