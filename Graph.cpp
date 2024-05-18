// 206766677 Omer.Apter@msmail.ariel.ac.il
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include "Graph.hpp"

using namespace std;
namespace ariel
{
    void Graph::loadGraph(vector<vector<int>> g)
    {
        unsigned int nodes = g.size();
        for (unsigned int i = 0; i < nodes; i++)
        {
            if (nodes != g[i].size())
            {
                throw std::invalid_argument{"Invalid graph: The graph is not a square matrix."};
            }
        }
        if (this->actual_graph != nullptr)
        {
            free(this->actual_graph);
        }
        this->num_edges = 0;
        this->nodes_num = nodes;
        this->actual_graph = (int *)malloc(nodes * nodes * sizeof(int));
        if (this->actual_graph != NULL)
        {
            for (unsigned int row = 0; row < nodes; row++)
            {
                for (unsigned int col = 0; col < nodes; col++)
                {
                    int edge = g[row].at(col);
                    this->num_edges += (edge != 0) ? 1 : 0;
                    this->setedge(row, col, edge);
                }
            }
        }
    }

    void Graph::setedge(unsigned int a, unsigned int b, int value)
    {
        // need to check if parameters in range for safer code
        if (a >= nodes_num || b >= nodes_num) {
                throw std::out_of_range("Node index out of range.");
            }
        this->actual_graph[this->nodes_num * a + b] = value;
    }

    int Graph::getedge(unsigned int row, unsigned int collumn)
    {
        // need to check if parameters in range for safer code
        if (row >= nodes_num || col >= nodes_num) {
                throw std::out_of_range("Node index out of range.");
            }
        return this->actual_graph[this->nodes_num * row + collumn];
    }

    void Graph::printGraph()
    {
        cout << "Graph with " << this->nodes_num << " vertices and " << this->num_edges << " edges" << std::endl;
    }

    Graph::~Graph()
    {
        if (this->graph_loaded == true)
            free(this->actual_graph);
    }
}
