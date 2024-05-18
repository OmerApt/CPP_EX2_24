// 206766677 Omer.Apter@msmail.ariel.ac.il
#include <vector>
#pragma once

namespace ariel
{
    class Graph
    {
    private:
        // number of nodes
        unsigned int nodes_num;
        // number of edges
        unsigned int num_edges;
        // use 1d array to represent matrice
        int *actual_graph;
        // if have loaded graph
        bool graph_loaded;
        // for initilazing graph
        void setedge(unsigned int a, unsigned int b, int value);

    public:
        Graph()
        {
            this->actual_graph = nullptr;
            this->nodes_num = 0;
            this->num_edges = 0;
            this->graph_loaded = false;
        };
        Graph(unsigned int nodenum);
        ~Graph();
        void loadGraph(std::vector<std::vector<int>> g);
        // copy load
        void loadGraph(Graph g);
        void printGraph() const;
        // return the edge from a to b if exists else return 0
        int getedge(unsigned int row, unsigned int collumn) const;
        unsigned int get_num_of_nodes() const
        {
            return this->nodes_num;
        }
        // binary + -
        friend Graph operator+(const Graph &g1, const Graph &g2);
        friend Graph operator-(const Graph &g1, const Graph &g2);
        Graph &operator+=(const Graph &g2);
        Graph &operator-=(const Graph &g2);
        Graph operator*(int scalar);
        Graph &operator++(int dummy_flag);
         Graph &operator--(int dummy_flag);
        // unary + -
        friend Graph operator+(const Graph &g1);
        friend Graph operator-(const Graph &g1);
    };

} // namespace ariel
