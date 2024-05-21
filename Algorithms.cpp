// 206766677 Omer.Apter@msmail.ariel.ac.il
#include <vector>
#include <stdio.h>
#include <stdexcept>
#include <deque>
#include <iostream>
#include "Algorithms.hpp"
#include "Graph.hpp"

#define WHITE 0
#define GREY 1
#define BLACK 2
#define RED 3
#define BLUE 4
#define MAX INT16_MAX

using namespace std;
using ariel::Graph;
namespace ariel
{
    int run_bellman_ford(Graph &g, unsigned int start, int d[], unsigned int prev[]);
    void relax(Graph &g, unsigned int edgefrom, unsigned int edgeto, int d[], unsigned int prev[]);
    string dfsCircleFind(Graph &g);
    unsigned int dfsCircleVisit(Graph &g, unsigned int u, unsigned int color[], unsigned int prev[]);

    // checks if Graph g is a connected Graph by looking at g as an undirectional Graph.
    // using a bfs on g and grouping all the found nodes (use array group the starts with each index[node] as its own group).
    // checking if all nodes are in the same group
    bool Algorithms::isConnected(Graph &g)
    {
        unsigned int *group = (unsigned int *)malloc(g.get_num_of_nodes() * sizeof(int));
        for (unsigned int i = 0; i < g.get_num_of_nodes(); i++)
        {
            group[i] = i;
        }
        // implement of queue
        deque<unsigned int> q = deque<unsigned int>();
        q.push_front(0);

        while (!q.empty())
        {
            // queue pop
            unsigned int u = q.back();
            q.pop_back();

            for (unsigned int v = 0; v < g.get_num_of_nodes(); v++)
            {
                // v in adj[u] when looking at g as an undirected
                if (v != u && group[v] != group[u] && (g.getEdge(u, v) != 0 || g.getEdge(v, u) != 0))
                {
                    group[v] = group[u];
                    // queue push
                    q.push_front(v);
                };
            }
        }
        // if all v have the same group[v] value they are connected
        for (unsigned int i = 0; i < g.get_num_of_nodes(); i++)
        {
            if (group[i] != group[0])
            {
                free(group);
                return false;
            }
        }
        free(group);
        return true;
    }
    // run bellman ford and check the path from end to start while building a string representetion of the shortest path to return. will return "-1" if there is no path
    string Algorithms::shortestPath(ariel::Graph &g, int start, int end)
    {
        if (start == end)
            return to_string(start);

        // asumming success for malloc
        int *d = (int *)malloc(g.get_num_of_nodes() * sizeof(int));                      // represents lowest boundry.
        unsigned int *prev = (unsigned int *)malloc(g.get_num_of_nodes() * sizeof(int)); // represents the parent node in the shortest path from node start.

        int res = run_bellman_ford(g, 0, d, prev);

        // print the shortest (lowest weight)
        unsigned int v = (unsigned int)end;
        string out = to_string(end);
        while (v != start)
        {
            unsigned int u = prev[v];
            if (d[v] != g.getEdge(u, v) + d[u])
            {
                v = (unsigned int)start;
                out = "-1";
            }
            else
            {
                out = to_string(u) + "->" + out;
                v = u;
            }
        }
        return out;
    }
    // if g contains a cycle (is not a DAG) returns true and prints one cycle course in graph g.
    // if g is DAG returns false;
    bool Algorithms::isContainsCycle(ariel::Graph &g)
    {
        string ans = dfsCircleFind(g);
        if (ans != "0")
            cout << ans << std::endl;
        return ans == "0" ? false : true;
    }
    // using bfs and answer from tirgul 4 of algo 1 if Graph g is Bipartite return a string showing the 2 groups else return "0".
    string Algorithms::isBipartite(ariel::Graph &g)
    {
        int *color = (int *)malloc(g.get_num_of_nodes() * sizeof(int));
        for (int i = 0; i < g.get_num_of_nodes(); i++)
        {
            color[i] = WHITE;
        }
        // implement of queue
        deque<unsigned int> q = deque<unsigned int>();
        q.push_front(0);
        color[0] = BLUE;

        while (!q.empty())
        {
            // queue pop
            unsigned int u = q.back();
            q.pop_back();

            for (unsigned int v = 0; v < g.get_num_of_nodes(); v++)
            {
                // v in adj[u] when looking at g as an undirected
                if (v != u && (g.getEdge(u, v) != 0 || g.getEdge(v, u) != 0))
                {
                    if (color[u] == color[v])
                    {
                        free(color);
                        return "0";
                    }
                    else
                    {
                        if (color[v] == WHITE)
                        {
                            color[v] = (color[u] == BLUE) ? RED : BLUE;
                            // queue push
                            q.push_front(v);
                        }
                    }
                };
            }
        }
        string out = "The graph is bipartite: A={" + to_string(0);
        for (unsigned int i = 1; i < g.get_num_of_nodes(); i++)
        {
            if (color[i] == color[0])
                out += ", " + to_string(i);
        }
        out += "}, B={";
        bool first = true;
        for (unsigned int i = 1; i < g.get_num_of_nodes(); i++)
        {
            if (color[i] != color[0])
            {
                if (first)
                {
                    out += to_string(i);
                    first = false;
                }
                else
                {
                    out += ", " + to_string(i);
                }
            }
        }
        out+="}";
        return out;
    }
    // return 1 if there is a negetive cycle else 0
    int Algorithms::negativeCycle(ariel::Graph &g)
    {
        // asumming success for malloc
        int *d = (int *)malloc(g.get_num_of_nodes() * sizeof(int));
        unsigned int *prev = (unsigned int *)malloc(g.get_num_of_nodes() * sizeof(int));

        int res = run_bellman_ford(g, 0, d, prev);
        free(d);
        free(prev);
        return (res == -1) ? 1 : 0;
    }
    // return -1 if negative cycle else return 0
    int run_bellman_ford(Graph &g, unsigned int start, int d[], unsigned int prev[])
    {
        for (unsigned int i = 0; i < g.get_num_of_nodes(); i++)
        {
            d[i] = MAX;
            prev[i] = g.get_num_of_nodes();
        }
        d[start] = 0;

        // repeating number of nodes - 1 times
        for (unsigned int c = 0; c < g.get_num_of_nodes() - 1; c++)
        {
            // foreach edge
            for (unsigned int i = 0; i < g.get_num_of_nodes(); i++)
            {
                for (unsigned int j = 0; j < g.get_num_of_nodes(); j++)
                {
                    if (g.getEdge(i, j) != 0)
                        relax(g, i, j, d, prev);
                }
            }
        }

        // foreach edge
        for (unsigned int i = 0; i < g.get_num_of_nodes(); i++)
        {
            for (unsigned int j = 0; j < g.get_num_of_nodes(); j++)
            {
                if (g.getEdge(i, j) != 0)
                    if (d[j] > d[i] + g.getEdge(i, j))
                        return -1;
            }
        }
        return 0;
    }
    void relax(Graph &g, unsigned int edgefrom, unsigned int edgeto, int d[], unsigned int prev[])
    {
        if (d[edgeto] > d[edgefrom] + g.getEdge(edgefrom, edgeto))
        {
            d[edgeto] = d[edgefrom] + g.getEdge(edgefrom, edgeto);
            prev[edgeto] = edgefrom;
        }
    }

    // colors w=0, g=1 b=2
    // uses dfs on graph g, if on dfs we find a back edge (GREY node in color array) we return the cycle course from the found node else return "0"
    //
    string dfsCircleFind(Graph &g)
    {
        unsigned int *color = (unsigned int *)malloc(g.get_num_of_nodes() * sizeof(int)); // represents the color in dfs run
        unsigned int *prev = (unsigned int *)malloc(g.get_num_of_nodes() * sizeof(int));  // represents the parent node in shortest path from node 0
        for (unsigned int i = 0; i < g.get_num_of_nodes(); i++)
        {
            color[i] = WHITE;
            prev[i] = g.get_num_of_nodes();
        }
        unsigned int cyclestarter = g.get_num_of_nodes();
        for (unsigned int v = 0; v < g.get_num_of_nodes(); v++)
        {
            if (color[v] == WHITE)
            {
                unsigned int temp = dfsCircleVisit(g, v, color, prev);
                if (temp != g.get_num_of_nodes())
                {
                    cyclestarter = temp;
                    v = g.get_num_of_nodes();
                }
            }
        }
        string s;
        if (cyclestarter != g.get_num_of_nodes())
        {
            s = to_string(cyclestarter);
            unsigned int c = cyclestarter;
            do
            {
                c = prev[c];
                s += "<-" + to_string(c);
            } while (c != cyclestarter);
        }
        else
        {
            s = to_string(0);
        }
        free(color);
        free(prev);
        return s;
    }
    // the dfs recursive function, runs until reaching a leaf node and returns the numbers of nodes
    //  or until it finds a back edge (GREY node) and returns the GREY node(where a cycle starts and ends).
    unsigned int dfsCircleVisit(Graph &g, unsigned int u, unsigned int color[], unsigned int prev[])
    {
        color[u] = GREY;
        for (unsigned int v = 0; v < g.get_num_of_nodes(); v++)
        {
            if (v != u && g.getEdge(u, v) != 0)
            {
                if (color[v] == WHITE)
                {
                    prev[v] = u;
                    return dfsCircleVisit(g, v, color, prev);
                }
                else
                {
                    if (color[v] == GREY && v != prev[u])
                    {
                        prev[v] = u;
                        return v;
                    }
                }
            }
        }
        color[u] = BLACK;
        return g.get_num_of_nodes();
    }
} // namespace ariel
