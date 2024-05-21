#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}};
    CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {8, 5},
        {2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {5, 0, 1, 5, 0},
        {8, 1, 0, 1, 6},
        {0, 2, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
    CHECK_THROWS(g1 + g5);
    CHECK_THROWS(g5 + g2);
}

TEST_CASE("Test Graph equals")
{
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {5, 0, 1, 5, 0},
        {8, 1, 0, 1, 6},
        {0, 2, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    ariel::Graph g2;
    g2.loadGraph(graph3);
    CHECK(g2 == g6);
    CHECK(g6 == g2);
}
TEST_CASE("Scalar Multiplication Operator (*)") {
    // Check scalar multiplication operator
    ariel::Graph g1;
    // Populate g1 with appropriate data
    std::vector<std::vector<int>> graph_data = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    g1.loadGraph(graph_data);

    ariel::Graph result = g1 * 2;
    // Check specific edge values after scalar multiplication
    CHECK(result.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]"); // ariel::Graph representation after scalar multiplication
}

TEST_CASE("Scalar Division Operator (/)") {
    // Check scalar division operator
    ariel::Graph g1;
    // Populate g1 with appropriate data
    std::vector<std::vector<int>> graph_data = {{0, 2, 0}, {2, 0, 2}, {0, 2, 0}};
    g1.loadGraph(graph_data);

    ariel::Graph result = g1 / 2;
    // Check specific edge values after scalar division
    CHECK(result.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]"); // ariel::Graph representation after scalar division
}
TEST_CASE("Addition Assignment Operator (+=)")
{
    // Check addition assignment operator
    ariel::Graph g1, g2, g3;
    // Populate g1 and g2 with appropriate data
    std::vector<std::vector<int>> graph1_data = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    std::vector<std::vector<int>> graph2_data = {{0, 1, 1}, {1, 0, 2}, {1, 2, 0}};
    std::vector<std::vector<int>> graph3_data = {{0, -1, 1}, {1, 0, -3}, {-1, 4, 2}};
    g1.loadGraph(graph1_data);
    g2.loadGraph(graph2_data);
    g3.loadGraph(graph3_data);

    g1 += g2;
    g2 += g3;
    // Check specific edge values after addition
    CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");  // Graph representation after addition
    CHECK(g2.printGraph() == "[0, 0, 2]\n[2, 0, -1]\n[0, 6, 2]"); // Graph representation after addition
}

TEST_CASE("Subtraction Assignment Operator (-=)")
{
    // Check subtraction assignment operator
    ariel::Graph g1, g2, g3;
    // Populate g1 and g2 with appropriate data
    std::vector<std::vector<int>> graph1_data = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    std::vector<std::vector<int>> graph2_data = {{0, 1, 1}, {1, 0, 2}, {1, 2, 0}};
    std::vector<std::vector<int>> graph3_data = {{0, -1, 1}, {1, 0, -3}, {-1, 4, 2}};
    g1.loadGraph(graph1_data);
    g2.loadGraph(graph2_data);
    g3.loadGraph(graph3_data);

    g1 -= g2;
    g2 -= g3;
    // Check specific edge values after subtraction
    CHECK(g1.printGraph() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]"); // Graph representation after subtraction
    CHECK(g2.printGraph() == "[0, 2, 0]\n[0, 0, 5]\n[2, -2, -2]");  // Graph representation after subtraction
}
TEST_CASE("Unary Plus Operator (+)")
{
    // Check unary plus operator
    ariel::Graph g1;
    // Populate g1 with appropriate data
    std::vector<std::vector<int>> graph_data = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    g1.loadGraph(graph_data);

    ariel::Graph result = +g1;
    // Check if result is the same as g1
    CHECK(result.printGraph() == g1.printGraph());
}

TEST_CASE("Unary Minus Operator (-)")
{
    // Check unary minus operator
    ariel::Graph g1;
    // Populate g1 with appropriate data
    std::vector<std::vector<int>> graph_data = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    g1.loadGraph(graph_data);

    ariel::Graph result = -g1;
    // Check specific edge values after unary minus
    CHECK(result.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]"); // ariel::Graph representation after unary minus
}

TEST_CASE("Less Than Operator (<)")
{
    // Check less than operator
    ariel::Graph g1, g2;
    // Populate g1 and g2 with appropriate data
    std::vector<std::vector<int>> graph1_data = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    std::vector<std::vector<int>> graph2_data = {{0, 1, 1}, {1, 0, 2}, {1, 2, 0}};
    g1.loadGraph(graph1_data);
    g2.loadGraph(graph2_data);

    CHECK(g1 < g2); // Check if g1 is less than g2
}

TEST_CASE("Less Than or Equal To Operator (<=)")
{
    // Check less than or equal to operator
    ariel::Graph g1, g2;
    // Populate g1 and g2 with appropriate data
    std::vector<std::vector<int>> graph1_data = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    std::vector<std::vector<int>> graph2_data = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
    g1.loadGraph(graph1_data);
    g2.loadGraph(graph2_data);

    CHECK(g1 <= g2); // Check if g1 is less than or equal to g2
}

TEST_CASE("Greater Than Operator (>)")
{
    // Check greater than operator
    ariel::Graph g1, g2;
    // Populate g1 and g2 with appropriate data
    std::vector<std::vector<int>> graph1_data = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    std::vector<std::vector<int>> graph2_data = {{0, 1, 1}, {1, 0, 2}, {1, 2, 0}};
    g1.loadGraph(graph1_data);
    g2.loadGraph(graph2_data);

    CHECK(g2 > g1); // Check if g2 is greater than g1
}

TEST_CASE("Greater Than or Equal To Operator (>=)")
{
    // Check greater than or equal to operator
    ariel::Graph g1, g2;
    // Populate g1 and g2 with appropriate data
    std::vector<std::vector<int>> graph1_data = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    std::vector<std::vector<int>> graph2_data = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
    g1.loadGraph(graph1_data);
    g2.loadGraph(graph2_data);

    CHECK(g2 >= g1); // Check if g2 is greater than or equal to g1
}