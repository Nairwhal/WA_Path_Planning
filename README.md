# The Algorithm

Considering the integer grid-structure, I decided to go with A\*, where my heuristic=risk\*10+airDistance+pathDistance. The 10 for multiplying the risk by was chosen rather arbitrarily, but seemed to ensure the program executed fast for risk-heavy paths while avoiding risky areas for destinations outside of risky areas. The main issue I didn't foresee was needing to modify the section which checks if a node has been visited to instead check if a node was visited *and* it's path length was less than the proposed path to that node. This is due to the range limit, and because it was possible for risky areas to have heuristically less costly paths, which have large path lengths, and thus, specifically for the destination 50 units away, it was possible the program wouldn't explore the straight path to it through the risk-heavy area, and thus fault. Aside from that caveat, it's a standard implementation of the A\* algorithm.

#### Notes:

- The results_fig.png was taking very long to generate? As such, it currently isn't showing my paths, but I'll attempt to let it generate tomorrow (9/18/25)
