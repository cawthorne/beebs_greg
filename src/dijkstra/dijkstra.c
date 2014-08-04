#include <stdio.h>
#include <stdlib.h>

#include "support.h"

#ifdef SMALL_D
  #define NUM_NODES                          4
#elif defined(LARGE_D)
  #define NUM_NODES                          15
#else
  #define NUM_NODES                          15
#endif

#define NONE                               9999

struct _NODE
{
   int iDist;
   int iPrev;
};
typedef struct _NODE NODE;

struct _QITEM
{
   int iNode;
   int iDist;
   int iPrev;
   struct _QITEM *qNext;
};
typedef struct _QITEM QITEM;

QITEM *qHead = NULL;

#ifdef SMALL_D
   int AdjMatrix[NUM_NODES][NUM_NODES] = {{32,  32,  54,  12},
      {76,  54,  65,  14},
      {38,  31,  75,  40},
      {80,  16,  53,  14}};
#elif defined(LARGE_D)
   int AdjMatrix[NUM_NODES][NUM_NODES] = {{35, 6, 86, 58, 25, 3, 89, 31, 5, 84, 74, 7, 18, 27, 15}, {3, 62, 92, 13, 44, 91, 45, 28, 49, 54, 75, 10, 29, 18, 2}, {17, 16, 7, 0, 8, 69, 84, 45, 63, 25, 24, 48, 55, 46, 74}, {95, 90, 27, 0, 73, 89, 52, 91, 64, 21, 16, 83, 5, 14, 5}, {63, 65, 48, 90, 73, 76, 30, 37, 18, 34, 72, 70, 31, 87, 43}, {72, 51, 79, 58, 96, 52, 60, 46, 37, 2, 16, 17, 76, 15, 19}, {73, 77, 5, 51, 18, 44, 16, 5, 55, 75, 16, 31, 71, 59, 48}, {41, 29, 82, 93, 72, 55, 60, 81, 57, 75, 10, 98, 15, 76, 41}, {66, 78, 1, 57, 54, 1, 71, 22, 47, 30, 81, 60, 61, 42, 4}, {36, 81, 90, 18, 85, 67, 39, 14, 37, 71, 22, 1, 9, 39, 73}, {5, 24, 81, 55, 67, 62, 85, 61, 8, 20, 97, 87, 81, 14, 16}, {74, 31, 51, 19, 44, 15, 40, 64, 37, 94, 30, 24, 13, 73, 92}, {76, 63, 7, 11, 46, 25, 87, 61, 58, 7, 38, 7, 25, 69, 7}, {12, 47, 20, 86, 51, 48, 53, 33, 23, 19, 50, 47, 64, 93, 52}, {77, 58, 73, 24, 44, 60, 14, 95, 53, 53, 48, 98, 53, 83, 59}};
#else
   int AdjMatrix[NUM_NODES][NUM_NODES] = {{32, 32, 54, 12, 52, 56, 8, 30, 44, 94},
   {76, 54, 65, 14, 89, 69, 4, 16, 24, 47},
   {38, 31, 75, 40, 61, 21, 84, 51, 86, 41},
   {80, 16, 53, 14, 94, 29, 77, 99, 16, 29},
   {59, 7, 14, 78, 79, 45, 54, 83, 8, 94},
   {94, 41, 3, 61, 27, 19, 33, 35, 78, 38},
   {3, 55, 41, 76, 49, 68, 83, 23, 67, 15},
   {68, 28, 47, 12, 82, 6, 26, 96, 98, 75},
   {7, 1, 46, 39, 12, 68, 41, 28, 31, 0},
   {82, 97, 72, 61, 39, 48, 11, 99, 38, 49}};
#endif

int g_qCount = 0;
NODE rgnNodes[NUM_NODES];
int ch;
int iPrev, iNode;
int i, iCost, iDist;

void enqueue (int iNode, int iDist, int iPrev)
{
   QITEM *qNew = (QITEM *) malloc(sizeof(QITEM));
   QITEM *qLast = qHead;

   qNew->iNode = iNode;
   qNew->iDist = iDist;
   qNew->iPrev = iPrev;
   qNew->qNext = NULL;

   if (!qLast)
   {
      qHead = qNew;
   }
   else
   {
      while (qLast->qNext) qLast = qLast->qNext;
      qLast->qNext = qNew;
   }
   g_qCount++;
}


QITEM* dequeue (int *piNode, int *piDist, int *piPrev)
{
   QITEM *qKill = qHead;

   if (qHead != 0)
   {
      *piNode = qHead->iNode;
      *piDist = qHead->iDist;
      *piPrev = qHead->iPrev;
      qHead = qHead->qNext;
      g_qCount--;
      return qKill;
   }
   return 0;
}


int qcount (void)
{
   return(g_qCount);
}

int dijkstra(int chStart, int chEnd)
{
   for (ch = 0; ch < NUM_NODES; ch++)
   {
      rgnNodes[ch].iDist = NONE;
      rgnNodes[ch].iPrev = NONE;
   }

   if (chStart == chEnd)
   {
      return 0;
   }
   else
   {
      rgnNodes[chStart].iDist = 0;
      rgnNodes[chStart].iPrev = NONE;

      enqueue (chStart, 0, NONE);

      while (qcount() > 0)
      {
         QITEM *tmp = dequeue (&iNode, &iDist, &iPrev);
         if(tmp != 0)
            free(tmp);
         for (i = 0; i < NUM_NODES; i++)
         {
            iCost = AdjMatrix[iNode][i];
            if (iCost != NONE)
            {
               if ((NONE == rgnNodes[i].iDist) ||
                     (rgnNodes[i].iDist > (iCost + iDist)))
               {
                  rgnNodes[i].iDist = iDist + iCost;
                  rgnNodes[i].iPrev = iNode;
                  enqueue (i, iDist + iCost, iNode);
               }
            }
         }
      }
   }

   return rgnNodes[chEnd].iDist;
}


int main() {
   int i,j,n;

   int output[NUM_NODES * NUM_NODES];
   int output_count = 0;

#ifdef SMALL_D
   int check_output[NUM_NODES * NUM_NODES] = {0, 76, 38, 80, 28, 0, 31, 16, 54, 65, 0, 53, 12, 14, 40, 0};
#elif defined(LARGE_D)
   int check_output[NUM_NODES * NUM_NODES] = {0, 3, 17, 21, 36, 21, 20, 15, 18, 27, 5, 34, 24, 12, 34, 6, 0, 16, 27, 35, 27, 21, 21, 17, 32, 11, 31, 23, 18, 35, 6, 9, 0, 12, 19, 18, 5, 19, 1, 16, 9, 20, 7, 18, 19, 6, 9, 0, 0, 19, 18, 5, 19, 1, 16, 9, 19, 7, 18, 19, 14, 17, 8, 20, 0, 26, 13, 27, 9, 24, 17, 28, 15, 26, 27, 3, 6, 20, 24, 19, 0, 23, 18, 1, 16, 8, 15, 22, 15, 37, 22, 16, 19, 19, 30, 32, 0, 36, 18, 30, 26, 34, 21, 34, 14, 19, 21, 24, 24, 35, 16, 5, 0, 17, 14, 24, 31, 21, 31, 19, 5, 8, 22, 24, 18, 24, 23, 18, 0, 30, 8, 37, 29, 17, 37, 5, 8, 12, 12, 21, 2, 17, 20, 3, 0, 10, 17, 7, 17, 31, 19, 22, 16, 16, 35, 16, 15, 10, 17, 22, 0, 30, 23, 31, 29, 6, 9, 12, 12, 22, 3, 17, 21, 4, 1, 11, 0, 7, 18, 31, 11, 14, 5, 5, 24, 11, 10, 15, 6, 9, 14, 13, 0, 23, 24, 18, 18, 14, 14, 33, 15, 19, 24, 15, 30, 14, 30, 21, 0, 33, 8, 2, 5, 5, 22, 18, 10, 22, 4, 16, 12, 20, 7, 20, 0};
#else
   int check_output[NUM_NODES * NUM_NODES] = {
      0,  7, 38, 23, 14, 36,  3, 29,  7, 14,
      28,  0, 31, 16,  7, 34, 31, 28,  1, 39,
      39, 25,  0, 32, 14,  3, 32,  9, 26, 43,
      12, 14, 40,  0, 21, 43, 15, 12, 15, 26,
      40, 36, 48, 28,  0, 27, 43, 33, 12, 39,
      36, 22, 21, 29, 29,  0, 29,  6, 23, 40,
      8,  4, 35, 20, 11, 33,  0, 26,  5, 11,
      30, 16, 47, 32, 23, 35, 23,  0, 17, 34,
      28, 24, 55, 16,  8, 35, 31, 28,  0, 38,
      23, 19, 41, 16,  8, 35, 15, 28,  0,  0};
#endif

   initialise_board();
   start_trigger();

   /* finds 10 shortest paths between nodes */
   for(n = 0; n < REPEAT_FACTOR >> 9; ++n) {
      output_count = 0;
      for(j = 0; j < NUM_NODES; j++) {
         for (i=0; i < NUM_NODES; i++) {
            output[output_count] = dijkstra(i,j);
            output_count++;
         }
      }
   }

   stop_trigger();

   int to_return = 0;
   for (i = 0; i < output_count; i++) {
	//printf("%d, ", output[i]);
      if (output[i] != check_output[i]) {
         to_return = -1;
         break;
      }
   }

   return to_return;
}

/* vim: set ts=3 sw=3 et: */
