// 206766677 Omer.Apter@msmail.ariel.ac.il
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include "Graph.hpp"

using namespace std;
namespace ariel
{
    // creates an empty graph with param nodenum number of nodes
    Graph::Graph(unsigned int nodenum)
    {
        this->actual_graph = new int[nodenum * nodenum];
        this->nodes_num = nodenum;
        this->num_edges = 0;
        this->graph_loaded = true;
    }
    // deconstructor of Graph
    Graph::~Graph()
    {
        if (this->graph_loaded == true)
        {
            // free(this->actual_graph);
            delete[] this->actual_graph;
        }
    }
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
        // std::fill(this->actual_graph,this->actual_graph+(nodes*nodes),0);
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
        this->graph_loaded = true;
    }

    // returns a copy of Graph. otherwise works the same
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
        // std::fill(this->actual_graph,this->actual_graph+(nodes*nodes),0);
        if (this->actual_graph != NULL)
        {
            for (unsigned int row = 0; row < nodes; row++)
            {
                for (unsigned int col = 0; col < nodes; col++)
                {
                    int edge = g.getEdge(row, col);
                    this->num_edges += (edge != 0) ? 1 : 0;
                    this->setedge(row, col, edge);
                }
            }
        }
        this->graph_loaded = true;
    }
    // set the edge((a,b)) to be value.
    void Graph::setedge(unsigned int a, unsigned int b, int value)
    {
        // need to check if parameters in range for safer code
        if (a >= nodes_num || b >= nodes_num)
        {
            throw std::invalid_argument("Node index out of range.");
        }
        this->actual_graph[this->nodes_num * a + b] = value;
    }

    // check if this Graph is the same as Graph g2 (it checks values not the object itself)
    bool Graph::__is_exact_equal(const Graph &g2) const
    {
        uint number_of_nodes = this->get_num_of_nodes();
        if (number_of_nodes != g2.get_num_of_nodes()) // number of node needs to be equal
            return false;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                if (this->getEdge(row, col) != g2.getEdge(row, col))
                {
                    return false;
                }
            }
        }
        return true;
    }

    // check if this Graph matrice is a part of Graph g2 matrice.
    bool Graph::__contained_in(const Graph &g2) const
    {
        uint number_of_nodes = this->get_num_of_nodes();
        if (number_of_nodes > g2.get_num_of_nodes()) // a matrice sized n+1 cant be a part of matrice sized n
            return false;

        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                if (this->getEdge(row, col) != g2.getEdge(row, col))
                {
                    return false;
                }
            }
        }
        return true;
    }
    // return the value of edge(row,collumn), will throw error if the parameters are out of range
    int Graph::getEdge(unsigned int row, unsigned int collumn) const
    {
        // need to check if parameters in range for safer code
        if (row >= nodes_num || collumn >= nodes_num)
        {
            throw std::invalid_argument("Node index out of range.");
        }
        return this->actual_graph[this->nodes_num * row + collumn];
    }
    // return a string represntion of this Graph
    std::string Graph::printGraph() const
    {
        return this->create_graph_string();
    }
    // returns a string of This Graph edges matrice
    std::string Graph::create_graph_string() const
    {
        uint number_of_nodes = this->nodes_num;
        string str = "";
        for (uint row = 0; row < number_of_nodes; row++)
        {
            str.append("[");
            for (uint col = 0; col < number_of_nodes; col++)
            {
                str.append(to_string(this->getEdge(row, col)));
                if (col < number_of_nodes - 1)
                    str.append(", ");
            }
            str.append("]");
            if (row < number_of_nodes - 1)
                str.append("\n");
        }
        return str;
    }

    // overload of opetaor +=, will add the matrice of Graph g2 to this Graph matrice
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
                int new_val = this->getEdge(row, col) + g2.getEdge(row, col);
                this->setedge(row, col, new_val);
                if (new_val != 0)
                    this->num_edges++;
            }
        }

        return *this;
    }
    // overload of opetaor -=, will subtract the matrice of Graph g2 to this Graph matrice
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
                int new_val = this->getEdge(row, col) - g2.getEdge(row, col);
                this->setedge(row, col, new_val);
                if (new_val != 0)
                    this->num_edges++;
            }
        }

        return *this;
    }
    // overload of opetaor * with scalar, will return Graph g_res which is the result of multiplying Graph g1 Matrice with scalar
    Graph operator*(const Graph &g1, int scalar)
    {
        uint number_of_nodes = g1.get_num_of_nodes();
        Graph g_res{number_of_nodes};
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getEdge(row, col) * scalar;
                g_res.setedge(row, col, new_val);
                if (new_val != 0)
                    g_res.num_edges++;
            }
        }

        return g_res;
    }
    // overload of opetaor *= with scalar, will multiply Graph g1 matrice with scalar and return reference to Graph g1
    Graph &operator*=(Graph &g1, int scalar)
    {
        uint number_of_nodes = g1.get_num_of_nodes();
        g1.num_edges = 0;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getEdge(row, col) * scalar;
                g1.setedge(row, col, new_val);
                if (new_val != 0)
                    g1.num_edges++;
            }
        }

        return g1;
    }
    // overload of opetaor * with scalar, will return Graph g_res which is the result of dividing Graph g1 Matrice with scalar (equal to g1*(1/scalar))
    Graph operator/(const Graph &g1, int scalar)
    {
        uint number_of_nodes = g1.get_num_of_nodes();
        Graph g_res{number_of_nodes};
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getEdge(row, col) / scalar;
                g_res.setedge(row, col, new_val);
                if (new_val != 0)
                    g_res.num_edges++;
            }
        }

        return g_res;
    }
    // overload of opetaor /= with scalar, will divide Graph g1 matrice with scalar (equal to g1*(1/scalar)) and return reference to Graph g1
    Graph &operator/=(Graph &g1, int scalar)
    {
        uint number_of_nodes = g1.get_num_of_nodes();
        g1.num_edges = 0;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getEdge(row, col) / scalar;
                g1.setedge(row, col, new_val);
                if (new_val != 0)
                    g1.num_edges++;
            }
        }

        return g1;
    }
    // will add 1 for each existing edge(where getedge(row,col)!=0) on this Graph matrice and return reference to this Graph
    Graph &Graph::operator++(int dummy_flag)
    {
        uint number_of_nodes = this->nodes_num;
        this->num_edges = 0;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                if (this->getEdge(row, col) != 0)
                {
                    int new_val = this->getEdge(row, col) + 1;
                    this->setedge(row, col, new_val);
                    if (new_val != 0)
                        this->num_edges++;
                }
            }
        }

        return *this;
    }
    // will subtract 1 for each existing edge(where getedge(row,col)!=0) on this Graph matrice and return reference to this Graph
    Graph &Graph::operator--(int dummy_flag)
    {
        uint number_of_nodes = this->nodes_num;
        this->num_edges = 0;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                if (this->getEdge(row, col) != 0)
                {
                    int new_val = this->getEdge(row, col) - 1;
                    this->setedge(row, col, new_val);
                    if (new_val != 0)
                        this->num_edges++;
                }
            }
        }

        return *this;
    }

    // overload of opetaor +, will return Graph g_res which matrice is the result of matrice addition of Graph g1 matrice and g2 matrice
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
                int new_val = g1.getEdge(row, col) + g2.getEdge(row, col);
                g_res.setedge(row, col, new_val);
                if (new_val != 0)
                    g_res.num_edges++;
            }
        }

        return g_res;
    }
    // overload of opetaor -, will return Graph g_res which matrice is the result of matrice subtraction of Graph g1 matrice and g2 matrice
    Graph operator-(const Graph &g1, const Graph &g2)
    {
        if (g1.nodes_num != g2.nodes_num)
        {
            throw out_of_range("The - operation can only be used for graphs with the same number of nodes");
        }
        uint number_of_nodes = g1.nodes_num;
        Graph g_res(number_of_nodes);
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getEdge(row, col) - g2.getEdge(row, col);
                g_res.setedge(row, col, new_val);
                if (new_val != 0)
                    g_res.num_edges++;
            }
        }

        return g_res;
    }
    // overload of opetaor *, will return Graph g_res which matrice is the result of matrice multiplication of Graph g1 matrice to g2 matrice
    Graph operator*(const Graph &g1, const Graph &g2)
    {
        if (g1.nodes_num != g2.nodes_num)
        {
            throw invalid_argument("The * operation can only be used for graphs with the same number of nodes");
        }
        uint number_of_nodes = g1.nodes_num;
        Graph g_res(number_of_nodes);
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = 0;
                // matrix multiplication
                for (uint j = 0; j < number_of_nodes; j++)
                {
                    new_val += g1.getEdge(row, j) * g2.getEdge(j, col);
                }
                g_res.setedge(row, col, new_val);
                if (new_val != 0)
                    g_res.num_edges++;
            }
        }

        return g_res;
    }
    // overload of opetaor *=,will multiply Graph g1 matrice with g2 matrice,save it to Graph g1 and return refrence to Graph g1
    Graph &operator*=(Graph &g1, const Graph &g2)
    {
        if (g1.nodes_num != g2.nodes_num)
        {
            throw out_of_range("The * operation can only be used for graphs with the same number of nodes");
        }
        uint number_of_nodes = g1.nodes_num;
        Graph gcpy = g1 * g2;
        g1.num_edges = gcpy.num_edges;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = gcpy.getEdge(row, col);
                g1.setedge(row, col, new_val);
            }
        }
        return g1;
    }
    // overload of unary opetaor +, will return Graph g_res where g_res.getEdge(a,b)==|g1.getEdge(a,b)|
    Graph operator+(const Graph &g1)
    {
        uint number_of_nodes = g1.nodes_num;
        Graph g_res(number_of_nodes);
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getEdge(row, col);
                g_res.setedge(row, col, +new_val);
            }
        }

        return g_res;
    }
    // overload of unary opetaor -, will return Graph g_res where g_res.getEdge(a,b)==|g1.getEdge(a,b)|*-1
    Graph operator-(const Graph &g1)
    {
        uint number_of_nodes = g1.nodes_num;
        Graph g_res(number_of_nodes);
        g_res.num_edges = g1.num_edges;
        for (uint row = 0; row < number_of_nodes; row++)
        {
            for (uint col = 0; col < number_of_nodes; col++)
            {
                int new_val = g1.getEdge(row, col);
                g_res.setedge(row, col, -new_val);
            }
        }

        return g_res;
    }

     // overload of opetaor <,will return if Graph g1 is smaller then Graph g2
    bool operator<(const Graph &g1, const Graph &g2)
    {
        bool smallerthen;
        smallerthen = g1.__contained_in(g2);
        smallerthen |= (g1.num_edges < g2.num_edges);
        smallerthen |= (g1.nodes_num < g2.nodes_num);
        return smallerthen;
    }
// overload of opetaor <=,will return if Graph g1 is smaller or equal to Graph g2
    bool operator<=(const Graph &g1, const Graph &g2)
    {
        return g1 < g2 || g1 == g2;
    }
// overload of opetaor >,will return if Graph g1 is bigger then Graph g2
    bool operator>(const Graph &g1, const Graph &g2)
    {
        return g2 < g1;
    }
// overload of opetaor >=,will return if Graph g1 is bigger or equal to Graph g2
    bool operator>=(const Graph &g1, const Graph &g2)
    {
        return g1 > g2 || g1 == g2;
    }
// overload of opetaor <,will return if Graph g1 is equal to Graph g2
    bool operator==(const Graph &g1, const Graph &g2)
    {
        uint number_of_nodes = g1.nodes_num;
        bool ans = g1.__is_exact_equal(g2);
        ans |= (!(g1 < g2) && !(g1 > g2));
        return ans;
    }
// overload of opetaor <<, will Insert Graph g string reprentetion to  ostream os and return reference of ostream os
    ostream &operator<<(ostream &os, const Graph &g)
    {
        std::operator<<(os, '"');
        std::operator<<(os, g.printGraph());
        std::operator<<(os, '"');
        return os;
    }
}
