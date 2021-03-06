#include <stdio.h>
#include <list>
#include <stack>
using namespace std;

#define min(a,b) (((a) < (b)) ? (a) : (b))

#define N 15

list<int>  e[N];
int pre[N], post[N], visited[N];
int _clock = 0;

void explore(int z)
{
	pre[z] = _clock ++;
	visited[z] = 1;

	for(auto it = e[z].begin(); it != e[z].end() ; it ++)
	{
		int w = *it;
		if (visited[w] == 0)
		{
			printf("(%d, %d) is a tree edge\n", z, w);
			explore(w);
		}
		else if (pre[z] < pre[w])
		{
			printf("(%d, %d) is a forward edge\n", z, w);
		}
		else if (post[w] < 0)
		{
			printf("(%d, %d) is a back edge\n", z, w);
		}
		else
			printf("(%d, %d) is a cross edge\n", z, w);
	}

	post[z] = _clock++;
}

void DFS()
{
	for (int v = 0; v < N; v++)
	{
		visited[v] = 0;
		pre[v] = post[v] = -1;
	}


	for (int v = 0; v < N; v++)
	{
		if (visited[v] == 0)
		{
			explore(v);
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

	//e[0].push_front(1); e[0].push_front(14);
	//e[1].push_front(0); e[1].push_front(3); e[1].push_front(13);
	//e[2].push_front(3);
	//e[3].push_front(1); e[3].push_front(2); e[3].push_front(4); e[3].push_front(12);
	//e[4].push_front(3); e[4].push_front(11);
	//e[5].push_front(6); e[5].push_front(7); e[5].push_front(8);
	//e[6].push_front(5); e[6].push_front(7);
	//e[7].push_front(5); e[7].push_front(6); e[7].push_front(8); e[7].push_front(10);
	//e[8].push_front(5); e[8].push_front(7); e[8].push_front(9);
	//e[9].push_front(8); e[9].push_front(10); e[9].push_front(11);
	//e[10].push_front(7); e[10].push_front(9); e[10].push_front(11);
	//e[11].push_front(3); e[11].push_front(4); e[11].push_front(9); e[11].push_front(10);
	//e[12].push_front(3);
	//e[13].push_front(1); e[13].push_front(14);
	//e[14].push_front(0); e[14].push_front(13);

	e[0].push_front(1); e[0].push_front(2);
	e[1].push_front(0); e[1].push_front(2); e[1].push_front(3); 
	e[2].push_front(0); e[2].push_front(1); e[2].push_front(3);
	e[3].push_front(1); e[3].push_front(2); e[3].push_front(4);
	e[4].push_front(5); e[4].push_front(3);
	e[5].push_front(4);
	e[6].push_front(7);
	e[7].push_front(6); e[7].push_front(8);
	e[8].push_front(7); e[8].push_front(9);
	e[9].push_front(8); 
	
	// do DFS and classify edges at the same time
	DFS();

	return 0;
}