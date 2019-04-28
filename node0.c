#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt0;


/* students to write the following two routines, and maybe some others */

// Instantiate routing packet
struct rtpkt packet0;

//Define node number and value for "infinity"
#define NODENUMBER 0
#define INFINITY 999

void rtinit0() 
{
    // Initialization of minimum cost array
    packet0.mincost[0] = INFINITY;
    packet0.mincost[1] = INFINITY;
    packet0.mincost[2] = INFINITY;
    packet0.mincost[3] = INFINITY;

    printf("Initiating Node 0\n");

    // Sets all node distances to infinity
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            dt0.costs[i][j]= INFINITY;
        }
    }

    // Set default distances from node 0 to nodes 1, 2, and 3 according to figure 1


    // The costs data structure follows the format of the cost to(first index) that node via(second index) another node.
	dt0.costs[0][0] = 0;
    dt0.costs[1][1] = 1; // i.e. The cost to node 1 via node 1
    dt0.costs[2][2] = 3;
    dt0.costs[3][3] = 7;

    // Set known minimum costs
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(packet0.mincost[i] > dt0.costs[i][j]){ // If the cost to i via j is less than INFINITY
                packet0.mincost[i] = dt0.costs[i][j];
            }
        }
    }

    // Set packet source ID to the nodeNumber
    packet0.sourceid = NODENUMBER;

    // Simulate Layer 2 link for each destination ID

    packet0.destid = 1;
    tolayer2(packet0);

    packet0.destid = 2;
    tolayer2(packet0);

    packet0.destid = 3;
    tolayer2(packet0);

    printdt0(&dt0);
    printf("rtinit0 is complete\n");

}


void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
	int src = rcvdpkt->sourceid;
	int change = 0;
	int i = 0;
    extern float clocktime;
	
	printf("rtupdate0 time: %f\n source: %d\n", clocktime, src);
	
	for(i=0;i<4;i++){
		if(i != NODENUMBER){
			int cost = rcvdpkt->mincost[i]+dt0.costs[src][src];
			if (packet0.mincost[i] > cost){
				dt0.costs[i][src] = cost;
				packet0.mincost[i] = cost;
				change = 1;
			}
		}
	}
	if(change){
		packet0.destid = 1;
		tolayer2(packet0);

		packet0.destid = 2;
		tolayer2(packet0);

		packet0.destid = 3;
		tolayer2(packet0);
	}
}


printdt0(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)   
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}