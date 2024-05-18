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
            // free(this->actual_graph);
            delete[] this->actual_graph;
        }
        this->num_edges = 0;
        this->nodes_num = nodes;
        // this->actual_graph = (int *)malloc(nodes * nodes * sizeof(int));
        this->actual_graph = new int[nodes * nodes];
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

    void Graph::loadGraph(Graph g)
    {
        unsigned int nodes = g.get_num_of_nodes();
        if (this->actual_graph != nullptr)
        {
            // free(this->actual_graph);
            delete[] this->actual_graph;
        }
        this->num_edges = 0;
        this->nodes_num = nodes;
        // this->actual_graph = (int *)malloc(nodes * nodes * sizeof(int));
        this->actual_graph = new int[nodes * nodes];
        if (this->actual_graph != NULL)
        {
            for (unsigned int row = 0; row < nodes; row++)
            {
                for (unsigned int col = 0; col < nodes; col++)
                {
                    int edge = g.getedge(row, col);
                    this->num_edges += (edge != 0) ? 1 : 0;
                    this->setedge(row, col, edge);
                }
            }
        }
    }

    void Graph::setedge(unsigned int a, unsigned int b, int value)
    {
        // need to check if parameters in range for safer code
        if (a >= nodes_num || b >= nodes_num)
        {
            throw std::out_of_range("Node index out of range.");
        }
        this->actual_graph[this->nodes_num * a + b] = value;
    }

    int Graph::getedge(unsigned int row, unsigned int collumn) const
    {
        // need to check if parameters in range for safer code
        if (row >= nodes_num || collumn >= nodes_num)
        {
            throw std::out_of_range("Node index out of range.");
        }
        return this->actual_graph[this->nodes_num * row + collumn];
    }

    Graph &Graph::operator+=(const Graph &g2)
    {
        if (this->nodes_num != g2.nodes_num)
        {
            throw out_of_range("The + operation can only be used for graphs with the same number of nodes");
        }
        uint number_of_nodes = this->nodes_num;
        this->num_edges = 0;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = this->getedge(row, col) + g2.getedge(row, col);
                this->setedge(row, col, new_val);
                if (new_val != 0)
                    this->num_edges++;
            }
        }

        return *this;
    }

    Graph &Graph::operator-=(const Graph &g2)
    {
        if (this->nodes_num != g2.nodes_num)
        {
            throw out_of_range("The + operation can only be used for graphs with the same number of nodes");
        }
        uint number_of_nodes = this->nodes_num;
        this->num_edges = 0;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = this->getedge(row, col) - g2.getedge(row, col);
                this->setedge(row, col, new_val);
                if (new_val != 0)
                    this->num_edges++;
            }
        }

        return *this;
    }

    Graph Graph::operator*(int scalar)
    {
        uint number_of_nodes = this->nodes_num;
        Graph g_res{number_of_nodes};
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = this->getedge(row, col) * scalar;
                g_res.setedge(row, col, new_val);
                if (new_val != 0)
                    g_res.num_edges++;
            }
        }

        return g_res;
    }

    Graph &Graph::operator++(int dummy_flag)
    {
        uint number_of_nodes = this->nodes_num;
        this->num_edges = 0;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                if (this->getedge(row, col) != 0)
                {
                    int new_val = this->getedge(row, col) + 1;
                    this->setedge(row, col, new_val);
                    if (new_val != 0)
                        this->num_edges++;
                }
            }
        }

        return *this;
    }

    Graph &Graph::operator--(int dummy_flag)
    {
        uint number_of_nodes = this->nodes_num;
        this->num_edges = 0;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                if (this->getedge(row, col) != 0)
                {
                    int new_val = this->getedge(row, col) - 1;
                    this->setedge(row, col, new_val);
                    if (new_val != 0)
                        this->num_edges++;
                }
            }
        }

        return *this;
    }

    void Graph::printGraph() const
    {
        cout << "Graph with " << this->nodes_num << " vertices and " << this->num_edges << " edges" << std::endl;
    }

    // creates an empty graph with param nodenum number of nodes
    Graph::Graph(unsigned int nodenum)
    {
        this->actual_graph = new int[nodenum * nodenum];
        this->nodes_num = nodenum;
        this->num_edges = 0;
        this->graph_loaded = true;
    }

    Graph::~Graph()
    {
        if (this->graph_loaded == true)
        {
            // free(this->actual_graph);
            delete[] this->actual_graph;
        }
    }
    Graph operator+(const Graph &g1, const Graph &g2)
    {
        if (g1.nodes_num != g2.nodes_num)
        {
            throw out_of_range("The + operation can only be used for graphs with the same number of nodes");
        }
        uint number_of_nodes = g1.nodes_num;
        Graph g_res(number_of_nodes);
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getedge(row, col) + g2.getedge(row, col);
                g_res.setedge(row, col, new_val);
                if (new_val != 0)
                    g_res.num_edges++;
            }
        }

        return g_res;
    }
    Graph operator-(const Graph &g1, const Graph &g2)
    {
        if (g1.nodes_num != g2.nodes_num)
        {
            throw out_of_range("The + operation can only be used for graphs with the same number of nodes");
        }
        uint number_of_nodes = g1.nodes_num;
        Graph g_res(number_of_nodes);
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getedge(row, col) - g2.getedge(row, col);
                g_res.setedge(row, col, new_val);
                if (new_val != 0)
                    g_res.num_edges++;
            }
        }

        return g_res;
    }
    Graph operator+(const Graph &g1)
    {
        uint number_of_nodes = g1.nodes_num;
        Graph g_res(number_of_nodes);
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getedge(row, col);
                g_res.setedge(row, col, +new_val);
            }
        }

        return g_res;
    }
    Graph operator-(const Graph &g1)
    {
        uint number_of_nodes = g1.nodes_num;
        Graph g_res(number_of_nodes);
        g_res.num_edges = g1.num_edges;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getedge(row, col);
                g_res.setedge(row, col, -new_val);
            }
        }

        return g_res;
    }
}
