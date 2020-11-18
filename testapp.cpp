#include "graph.h"

std::unique_ptr<Graph> createSimple();

int main() {
    string myStr = "test";
    Graph myG(myStr);

    std::unique_ptr<Graph> simple = createSimple();
    return 0;
}