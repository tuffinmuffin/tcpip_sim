#include "graph.h"

#include <memory>

#if 0

 +---+---+
 |       | 0/0
 + R0_re +---------------------------------------------------------|
 |       |                                                         |
 +---+---+                                                         |
    | 0/4                                                          |
    |                                                              |
    |                                                              | 0/1
 +---+---+                                                     +---+---+
 |       | 0/3                                              0/2|       |
 + R2_re + ----------------------------------------------------+ R1_re +
 |       |                                                     |       |
 +---+---+                                                     +---+---+


#endif


std::unique_ptr<Graph> createSimple() {
    std::unique_ptr<Graph> network_p(new Graph("Hello World Generic Graph"));
    Graph& network = *network_p.get();
    network.insertNode("R0_re");
    network.insertNode("R1_re");
    network.insertNode("R2_re");

    network.attachNodes("R0_re", "R1_re", "0/0", "0/1", 1);
    network.attachNodes("R0_re", "R2_re", "0/4", "0/5", 1);
    network.attachNodes("R1_re", "R2_re", "0/2", "0/3", 1);

    return network_p;
}