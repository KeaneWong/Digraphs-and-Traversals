//
//  AdjacencyListGraph.h
//  AdjacencyListGraphs
//
//  Copyright © 2020 Keane Wong. All rights reserved.
//
#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
using namespace std;


class AdjacencyListGraph
{
public:
    AdjacencyListGraph();                   //constructor default object
    
    void insertVertex(string Name, string Code);        //Adds a vertex with a given name and its associated code
    
    void addEdge(float weight, string code, string Source, string Destination);//Adds an associated edge between two nodes that have already been inserted into the graph by insertVertex
    
    void displayAll();                      //displays nodes in order of insertion and then edges in order of insertion to console
    
    void displayNodes();                    //displays all node's code and name in order of insertion spaced by tabs and separated by lines to console
    
    void displayNodes(string filename);     //outputs the nodes in format code, tab, then name, into a file of name filename
    
    void displayNode(string codeName);      //displays information about node searched by code to console
    
    void displayEdges();                    //displays edges present in the system for debugging
    
    void displayEdges(string filename);     //outputs the edges in format source node code, tab, destination node code, tab, and then edge code to a file of name filename to console
    
    void printDijkstra(string startCode, string endCode);   //displays cheapest path from one node to another starting from node of code startCode, to string endCode, evaluated by weight of edges to  console
    
    void printDijkstraNode(string startCode, string endCode);   //displays the path of least node traversals from node of code startCode to node of code endCode
    
    void printDijkstraRoundTrip(string startCode, string endCode);  //round trip cheapest paths evaluated by weight of edges from node of code startCode to node of code endCode
    
    void AllPathsDisplay(string curVertex, string endVertex);       //prints all distinct possible paths from one node to another to console
    
    void TraverseAllDisplay(string curVertex);  //given a code of a node, curVertex, finds a path to traverse all other nodes and prints to console
    
private:
    struct Vertex;  //node struct
    struct Edge;    //edge struct
    struct Edge
    {
        string edgeCode;//analogue for edge code
        float weight;   //value of a given edge, initialize as 1 if all weights are the same
        Vertex *source;//we are a directed graph (return flights are not necessarily symmetric) so we can have a unique vertex for source and destination
        Vertex *destination;
    };
    struct Vertex
    {
        string name;//node name
        string code;//node code
        unordered_map<string,Edge*> edges;//edges stored in an unordered map so we can access edges by key or flight number.
        //this is our effective 'adjacency list' that allows us direct access to the edges in O(1) constant time
        unordered_map<string, Edge*> backedges;//edges that we lead to this node. We don't use this except for the delete function
    };
    int dijkstraNode(vector<Edge*>& returnThis, string startCode, string endCode);//Returns a path from one airport to another thats the least number of stops. The size of the vector is how many stops it takes to get there.
    
    int dijkstra(vector<Edge*>& returnThis, string startCode, string endCode);//returns a vector containing the cheapest path of edges from one airport to another in order. Cost of flights is contained within the edges already so the total cost is just the sum of the edges costs within
    
    void AllPathsRecurs(string curVertex, string endVertex, unordered_map<string, bool>& hasVisited, vector<vector<string> >& returnVector, vector<string>& curPath);
    
    void TraverseAllRecurs(string curVertex, unordered_map<string, bool>& hasVisited, vector<string>& curPath); //function used to help traversal in the dijkstra functions
    
public:
    
    Vertex* opposite(Edge *e, Vertex *v);   //returns the vertex opposite of a given vertex and given an edge
    vector<Vertex*> endVertices(Edge* e);   //returns a list of destination (source and destination) vertices given an edge
    
    int size();                             //number of nodes in graph
    
    void deleteEdge(string code);           //deletes and edge based on the code of the edge
    void deleteEdge(string source, string destination);//overloaded delete function to use the codes of vertices instead of the code associated with the edge.
    void deleteNode(string code);
    vector<vector<string> > AllPaths(string curVertex, string endVertex);//a vertex of queues, all with a traversal in order from one airport to another. Returns all possible paths fomr one node to another
    class C                                 //comparison object used to compare weights and paths
    {
    public:
        bool operator()(pair<string,tuple<float,Vertex*,Edge*> > A, pair<string,tuple<float,Vertex*,Edge*> > B)const//we're using pairs because thats the type unordered maps use
        {
            return get<0>(A.second) < get<0>(B.second);
        }
    };
private:
    unordered_map<string, Vertex*> vertices;    //Our adjacency list supplement. Normally we'd use an array of lists for our adjacency list but this supports better random access
    unordered_map<string, Edge*> Edges;         //edge list helps us look up flights in constant time, which we wouldn't be able to do with the array of lists implementation.
                                                //this way we can still access a vertice's edges in constant time by looking at the unordered maps associated with each vertex and can also look up by flight number directly using our edge list
    int Size;                                   //Size variable of nodes
    
};
