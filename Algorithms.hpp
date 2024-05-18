//206766677 Omer.Apter@msmail.ariel.ac.il
#include <string>
#include "Graph.hpp"

namespace ariel
{
    class Algorithms
    {
    private:
        /* data */
    public:
        Algorithms(/* args */);
        ~Algorithms();
        static bool isConnected(Graph& g);
        static std::string shortestPath(Graph& g, int start, int end);
        static bool isContainsCycle(Graph& g);
        static std::string isBipartite(Graph& g);
        static int negativeCycle(Graph& g);
    };

} // namespace ariel
