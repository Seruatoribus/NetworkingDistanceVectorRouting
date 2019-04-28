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

int connectcosts1[4] = { 1,  0,  1, 999 };

struct distance_table 
{
  int costs[4][4];
} dt1;


/* students to write the following two routines, and maybe some others */

// Instantiate routing packet
struct rtpkt packet1;

//Define node number and value for "infinity"
#define NODENUMBER 1
#define INFINITY 999

rtinit1() 
{
// Initialization of minimum cost array
    packet1.mincost[0] = INFINITY;
    packet1.mincost[1] = INFINITY;
    packet1.mincost[2] = INFINITY;
    packet1.mincost[3] = INFINITY;

    printf("Initiating Node 1\n");

    // Sets all node distances to infinity
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            dt1.costs[i][j]= INFINITY;
        }
    }

    // Set default distances from node 1 to nodes 0, 2, and 3 according to figure 1


    // The costs data structure follows the format of the cost to(first index) that node via(second index) another node.
    dt1.costs[0][0] = 1;
    dt1.costs[1][1] = 0; // i.e. The cost to node 1 via node 1
    dt1.costs[2][2] = 1;

    // Set known minimum costs
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(packet1.mincost[i] > dt1.costs[i][j]){ // If the cost to i via j is less than INFINITY
                packet1.mincost[i] = dt1.costs[i][j];
            }
        }
    }

    // Set packet source ID to the nodeNumber
    packet1.sourceid = NODENUMBER;

    // Simulate Layer 2 link for each destination ID

    packet1.destid = 0;
    tolayer2(packet1);

    packet1.destid = 2;
    tolayer2(packet1);

    printdt1(&dt1);
    printf("rtinit1 is complete\n");
}


rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
    int src = rcvdpkt->sourceid;
	int change = 0;
	int i = 0;
    extern float clocktime;
	
	printf("rtupdate1 time: %f\n source: %d\n", clocktime, src);
	
	for(i=0;i<4;i++){
		if(i != NODENUMBER){
			int cost = rcvdpkt->mincost[i]+dt1.costs[src][src];
			if (packet1.mincost[i] > cost){
				dt1.costs[i][src] = cost;
				packet1.mincost[i] = cost;
				change = 1;
			}
		}
	}
	if(change){
		packet1.destid = 0;
		tolayer2(packet1);

		packet1.destid = 2;
		tolayer2(packet1);

	}
}


printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler1(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}

