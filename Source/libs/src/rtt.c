//  D ← [∞,∞, . . . , ∞] /* n copies of ∞ */
//  D[s] ← 0
//  P ← [ ]
//  Q ← V /* list of nodes to visit */
//  while length(Q) > 0 do
//     find v ∈ Q such that D[v] is minimal
//     Q ← remove(Q, v)
//     for each u ∈ adj(v) ∩ Q do
//         if D[u] > D[v] + w(vu) then
//            D[u] ← D[v] + w(vu)
//            P[u] ← v
//  return (D, P)

#include <stdio.h>
#include <stdlib.h>
#include "../libs/rtt.h"
#include "../libs/graph.h"
#include "../libs/utils.h"
#include "../libs/heap.h"
#include "../libs/item.h"
