// 206766677 Omer.Apter@msmail.ariel.ac.il
#include <vector>
#include <iostream>
#pragma once
// using namespace std;
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
        bool __is_exact_equal(const Graph &g2) const;
        bool __contained_in(const Graph &g2) const;
        std::string create_graph_string() const;

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
        std::string printGraph() const;
        // return the edge from a to b if exists else return 0
        int getEdge(unsigned int row, unsigned int collumn) const;
        unsigned int get_num_of_nodes() const
        {
            return this->nodes_num;
        }
        friend std::ostream &operator<<(std::ostream &os, const Graph &g);
        // arithmetic
        friend Graph operator+(const Graph &g1, const Graph &g2);
        friend Graph operator-(const Graph &g1, const Graph &g2);
        Graph &operator+=(const Graph &g2);
        Graph &operator-=(const Graph &g2);
        friend Graph operator*(const Graph &g1, int scalar);
        friend Graph &operator*=(Graph &g1, int scalar);
        friend Graph operator/(const Graph &g1, int scalar);
        friend Graph &operator/=(Graph &g1, int scalar);
        friend Graph operator*(const Graph &g1, const Graph &g2);
        friend Graph &operator*=(Graph &g1, const Graph &g2);
        Graph &operator++(int dummy_flag);
        Graph &operator--(int dummy_flag);
        // unary
        friend Graph operator+(const Graph &g1);
        friend Graph operator-(const Graph &g1);
        // logical
        friend bool operator<(const Graph &g1, const Graph &g2);
        friend bool operator<=(const Graph &g1, const Graph &g2);
        friend bool operator>(const Graph &g1, const Graph &g2);
        friend bool operator>=(const Graph &g1, const Graph &g2);
        friend bool operator==(const Graph &g1, const Graph &g2);
    };

} // namespace ariel
