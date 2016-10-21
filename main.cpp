#include"Header.h"
#include"TopologicalSort.h"
#define rep(i,n) for(int i=0;i<n;++i)

int main()
{
	freopen("input.txt", "r", stdin);
	//if(!Kahn())printf("Had cycle\n");
	//dfsVisit();
	//cout << hascycle()<<endl;
	dfsDetectCycle();
	return 0;
}