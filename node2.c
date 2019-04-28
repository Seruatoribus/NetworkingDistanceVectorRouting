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
} dt2;


/* students to write the following two routines, and maybe some others */

// Instantiate routing packet
struct rtpkt packet2;

//Define node number and value for "infinity"
#define NODENUMBER 2
#define INFINITY 999

rtinit2() 
{
// Initialization of minimum cost array
    packet2.mincost[0] = INFINITY;
    packet2.mincost[1] = INFINITY;
    packet2.mincost[2] = INFINITY;
    packet2.mincost[3] = INFINITY;

    printf("Initiating Node 2\n");

    // Sets all node distances to infinity
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            dt2.costs[i][j]= INFINITY;
        }
    }

    // Set default distances from node 2 to nodes 0, 1, and 3 according to figure 1


    // The costs data structure follows the format of the cost to(first index) that node via(second index) another node.
    dt2.costs[0][0] = 3;
    dt2.costs[1][1] = 1; // i.e. The cost to node 1 via node 1
    dt2.costs[2][2] = 0;
    dt2.costs[3][3] = 2;

    // Set known minimum costs
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(packet2.mincost[i] > dt2.costs[i][j]){ // If the cost to i via j is less than INFINITY
                packet2.mincost[i] = dt2.costs[i][j];
            }
        }
    }

    // Set packet source ID to the nodeNumber
    packet2.sourceid = NODENUMBER;

    // Simulate Layer 2 link for each destination ID

    packet2.destid = 0;
    tolayer2(packet2);

    packet2.destid = 1;
    tolayer2(packet2);

    packet2.destid = 3;
    tolayer2(packet2);

    printdt2(&dt2);
    printf("rtinit2 is complete\n");
}


void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
    int src = rcvdpkt->sourceid;
	int change = 0;
	int i = 0;
    extern float clocktime;
	
	printf("rtupdate2 time: %f\n source: %d\n", clocktime, src);
	
	for(i=0;i<4;i++){
		if(i != NODENUMBER){
			int cost = rcvdpkt->mincost[i]+dt2.costs[src][src];
			if (packet2.mincost[i] > cost){
				dt2.costs[i][src] = cost;
				packet2.mincost[i] = cost;
				change = 1;
			}
		}
	}
	if(change){
		packet2.destid = 1;
		tolayer2(packet2);

		packet2.destid = 0;
		tolayer2(packet2);

		packet2.destid = 3;
		tolayer2(packet2);
	}
}


printdt2(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}