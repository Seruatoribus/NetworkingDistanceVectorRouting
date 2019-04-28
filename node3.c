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
} dt3;

/* students to write the following two routines, and maybe some others */

// Instantiate routing packet
struct rtpkt packet3;

//Define node number and value for "infinity"
#define NODENUMBER 3
#define INFINITY 999

rtinit3() 
{
// Initialization of minimum cost array
    packet3.mincost[0] = INFINITY;
    packet3.mincost[1] = INFINITY;
    packet3.mincost[2] = INFINITY;
    packet3.mincost[3] = INFINITY;

    printf("Initiating Node 3\n");

    // Sets all node distances to infinity
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            dt3.costs[i][j]= INFINITY;
        }
    }

    // Set default distances from node 0 to nodes 1, 2, and 3 according to figure 1


    // The costs data structure follows the format of the cost to(first index) that node via(second index) another node.
    dt3.costs[0][0] = 7;
    dt3.costs[3][3] = 0; // i.e. The cost to node 3 via node 3
    dt3.costs[2][2] = 2;

    // Set known minimum costs
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(packet3.mincost[i] > dt3.costs[i][j]){ // If the cost to i via j is less than INFINITY
                packet3.mincost[i] = dt3.costs[i][j];
            }
        }
    }

    // Set packet source ID to the nodeNumber
    packet3.sourceid = NODENUMBER;

    // Simulate Layer 2 link for each destination ID

    packet3.destid = 0;
    tolayer2(packet3);

    packet3.destid = 2;
    tolayer2(packet3);


    printdt3(&dt3);
    printf("rtinit3 is complete\n");
}


void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
    int src = rcvdpkt->sourceid;
	int change = 0;
	int i = 0;
    extern float clocktime;
	
	printf("rtupdate3 time: %f\n source: %d\n", clocktime, src);
	
	for(i=0;i<4;i++){
		if(i != NODENUMBER){
			int cost = rcvdpkt->mincost[i]+dt3.costs[src][src];
			if (packet3.mincost[i] > cost){
				dt3.costs[i][src] = cost;
				packet3.mincost[i] = cost;
				change = 1;
			}
		}
	}
	if(change){
		packet3.destid = 0;
		tolayer2(packet3);

		packet3.destid = 2;
		tolayer2(packet3);
	}
}


printdt3(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}