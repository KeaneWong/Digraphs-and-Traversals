//
//  AdjacencyListGraph.cpp
//  AdjacencyListGraphs
//
//  Created by Keane Wong on 9/29/20.
//  Copyright © 2020 Keane Wong. All rights reserved.
//
#include "AdjacencyListGraph.h"
#include <utility>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits.h>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <fstream>
using namespace std;

AdjacencyListGraph::AdjacencyListGraph()
{
    //unordered_map<string, AdjacencyListGraph::Vertex> vertices;
    //unordered_map<string, AdjacencyListGraph::Edge> Edges;
    Size = 0;
}
void AdjacencyListGraph::insertVertex(string Name, string Code)
{
    Vertex* v = new Vertex;
    v->name = Name;
    v->code = Code;
    vertices[Code] = v;
    Size++;
}
void AdjacencyListGraph::addEdge(float weight,string code,string Source, string Destination)
{
    Edge *e = new Edge;
    e->weight = weight;//weight is our analogue for weight
    e->edgeCode = code;//our edgeCode is essentially the edge's code
    unordered_map<string,AdjacencyListGraph::Vertex*>::const_iterator t = vertices.find(Source);//checking if our Source and Destination are even in the graph
    unordered_map<string,AdjacencyListGraph::Vertex*>::const_iterator y = vertices.find(Destination);
    if (t == vertices.end()|| y==vertices.end())
    {
        cout << "Error: Destination or source not in graph" << endl;
        return;
    }
    Vertex *v1 = vertices[Source];
    Vertex *v2 = vertices[Destination];
    e->source = v1;//links our edge to our vertex
    e->destination = v2;
    v1->edges[code] = e;//this links our edge and vertex. Note that we only do this for our source vertex since our edges by default go one way.
    v2->backedges[code] = e;
    Edges[code] = e;
    //cout << "Added edge successfully" << endl;
    
}

AdjacencyListGraph::Vertex* AdjacencyListGraph::opposite(Edge *e, Vertex* v)
{
    if(e->source->code == v->code )//checking if at least one of the nodes is our vertex. otherwise we return an error
    {
        return e->destination;
    }
    else if(e->destination->code == v->code)
    {
        return e->source;
    }
    else    //if we made it here then v is not one of e's adjacent vertices and we return nullptr
    {
        return nullptr;
    }
}

vector<AdjacencyListGraph::Vertex*> AdjacencyListGraph::endVertices(Edge* e)//gives us a vector always of size 2 with the connected vertices
{
    vector<AdjacencyListGraph::Vertex*> myPair;
    myPair.push_back(e->source);
    myPair.push_back(e->destination);
    return myPair;
}

void AdjacencyListGraph::displayAll()//dispays nodes, then the edges by name of source and destination
{
    unordered_map<string, AdjacencyListGraph::Vertex*>::const_iterator current = vertices.begin();
    
    cout << "Nodes: " << vertices.size()<<endl;
    while (current != vertices.end())
    {
        AdjacencyListGraph::Vertex* curVertex = current->second;
        cout << "Name: " << curVertex->name << endl;
        cout << "Code: " << curVertex->code << endl;
        current++;
    }
    cout << endl;
    unordered_map<string, AdjacencyListGraph::Edge*>::const_iterator current2 = Edges.begin();//displaying nodes
    cout << "Edges: " << Edges.size()<<endl;
    while (current2 != Edges.end())
    {
        AdjacencyListGraph::Edge* curVertex = current2->second;
        cout << "Edge Code: " << curVertex->edgeCode << endl;
        cout << "Source Node: " << curVertex->source->code << endl;
        cout << "Destination Node: " << curVertex->destination->code << endl;
        current2++;
    }
    cout << endl;
}


void AdjacencyListGraph::displayNodes()
{
    unordered_map<string, AdjacencyListGraph::Vertex*>::const_iterator current = vertices.begin();
    
    cout << "Nodes: " << vertices.size() << endl;
    while (current != vertices.end())
    {
        AdjacencyListGraph::Vertex* curVertex = current->second;
        cout << curVertex->code << '\t' <<curVertex->name << endl;
        current++;
    }
    cout << endl;
}
void AdjacencyListGraph::displayNodes(string filename)
{
    ofstream myFile;
    myFile.open(filename);
    unordered_map<string, AdjacencyListGraph::Vertex*>::const_iterator current = vertices.begin();
    
    while (current != vertices.end())
    {
        AdjacencyListGraph::Vertex* curVertex = current->second;
        myFile << curVertex->code << '\t' << curVertex->name << endl;
        current++;
    }
    myFile.close();
}

void AdjacencyListGraph::displayNode(string codeName)
{
    if (vertices[codeName] != nullptr)
    {
        cout << vertices[codeName]->code << '\t' << vertices[codeName]->name << endl;
        unordered_map<string, AdjacencyListGraph::Edge*>::const_iterator current2 = vertices[codeName]->edges.begin();//displaying nodes
        cout << "Edges outgoing: " << endl;
        while (current2 != vertices[codeName]->edges.end())
        {
            AdjacencyListGraph::Edge* curVertex = current2->second;
            cout << curVertex->source->code << '\t' << curVertex->destination->code << '\t' << curVertex->weight << '\t' << curVertex->edgeCode << endl;
            current2++;
        }
        cout << endl;
    }
}



void AdjacencyListGraph::displayEdges()
{
    unordered_map<string, AdjacencyListGraph::Edge*>::const_iterator current2 = Edges.begin();//displaying Nodes
    cout << "Edges: " << Edges.size() << endl;
    while (current2 != Edges.end())
    {
        AdjacencyListGraph::Edge* curVertex = current2->second;
        cout << curVertex->source->code << '\t' << curVertex->destination->code << '\t' << curVertex->weight << '\t' << curVertex->edgeCode << endl;
        current2++;
    }
    cout << endl;
}
void AdjacencyListGraph::displayEdges(string filename)
{
    ofstream myFile;
    myFile.open(filename);
    unordered_map<string, AdjacencyListGraph::Edge*>::const_iterator current2 = Edges.begin();//displaying nodes
    
    while (current2 != Edges.end())
    {
        AdjacencyListGraph::Edge* curVertex = current2->second;
        myFile << curVertex->source->code <<'\t' << curVertex->destination->code << '\t' << curVertex->weight<< '\t' << curVertex->edgeCode << endl;
        current2++;
    }
    myFile.close();
}
void AdjacencyListGraph::deleteEdge(string code)
{
    AdjacencyListGraph::Edge* myEdge = Edges[code];
    vector<Vertex*> myPair = endVertices(myEdge);//start by getting end vertices so we can nullptr the deleted edge
    Vertex* source = myPair[0];//we only delete the edge with the side associated with the source. The destination doesnt have the edge technically connected to it since this is a digraphj
    source->edges.erase(code);//'deleting; from our vertex so we dont accidentally try to access an empty element
    Edges.erase(code);
    delete myEdge;
}
void AdjacencyListGraph::deleteEdge(string source, string destination)//overloaded delete for use with end vertices
{
    string tbdeleted;
    unordered_map<string,Edge*>::const_iterator il;
    for (il = vertices[source]->edges.begin();il!=vertices[source]->edges.end();il++)
    {
        if (il.operator*().second->destination->code == destination)
        {
            tbdeleted = il.operator*().second->edgeCode;
            deleteEdge(tbdeleted);//recycling is good for the environment
            cout << 'p' << endl;
        }
    }
}



void AdjacencyListGraph::deleteNode(string code)//input is the node's code
{
    Vertex* curVert = vertices[code];
    if (curVert == nullptr)
    {
        cout << "ERROR: CODE DOES NOT EXIST IN GRAPH" << endl;
        return;
    }
    unordered_map<string, AdjacencyListGraph::Edge*>::const_iterator current1 = curVert->edges.begin();
    
    while (current1 != curVert->edges.end())//deleting the edges associated with the node
    {
        string coode = current1->second->edgeCode;
        current1++;
        cout << "Deleting edge " << coode << endl;
        deleteEdge(coode);
    }
    current1 = curVert->backedges.begin();
    while (current1 != curVert->backedges.end())//deleting the edges associated with the node
    {
        string coode = current1->second->edgeCode;
        current1++;
        cout << "Deleting edge " << coode << endl;
        deleteEdge(coode);
    }
    vertices.erase(code);
    delete curVert;
    Size--;
}

int AdjacencyListGraph:: size()
{
    return Size;
}


void AdjacencyListGraph::printDijkstra(string startCode, string endCode)
{
    vector<Edge*> printlist;
    float totalCost;
    totalCost = dijkstra (printlist, startCode, endCode);
    if (printlist.size() == 0)
    {
        cout << "ERROR: INVALID DESTINATIONS OR EDGES NOT FOUND" << endl;
        //return;
    }
    
    for (int i = 0; i < printlist.size(); i++)
    {
        cout << "City: "<<printlist.at(i)->source->name << endl;
        cout << "EDGE number "<<printlist.at(i)->edgeCode;
        cout << " going to:" << endl << printlist.at(i)->destination->name << endl;
        cout << "Cost: " << printlist.at(i)->weight << endl;
    }
    cout << "Total weight of path: " <<totalCost<< endl<<endl;
}

void AdjacencyListGraph::printDijkstraRoundTrip(string startCode, string endCode) //we can easily just conglomerate dijkstras algorithm from one way to another.
{
    vector<Edge*> printlist1;
    float totalCost = 0;
    totalCost+=dijkstra(printlist1, startCode, endCode);
    vector<Edge*> printlist2;
    totalCost+=dijkstra(printlist2, endCode, startCode);
    if (printlist1.size() == 0 || printlist2.size() == 0)//if the size is 0 for either it means theres no way to get from one node to another
    {
        cout << "ERROR: INVALID DESTINATION NODES OR EDGES NOT FOUND" << endl;
        return;
    }
    
    for (int i = 0; i < printlist1.size(); i++)
    {
        cout << "City: " << printlist1.at(i)->source->name << endl;
        cout << "Edge Code " << printlist1.at(i)->edgeCode;
        cout << " going to " << printlist1.at(i)->destination->name << endl;
        cout << "Cost: " << printlist1.at(i)->weight << endl;
    }
    cout << "Return route: " << endl;
    for (int i = 0; i < printlist2.size(); i++)
    {
        cout << "City: " << printlist2.at(i)->source->name << endl;
        cout << "Edge Code " << printlist2.at(i)->edgeCode;
        cout << " going to " << printlist2.at(i)->destination->name << endl;
        cout << "Cost: " << printlist2.at(i)->weight << endl;
    }
    cout << "Total weight of path: " <<totalCost<< endl << endl;;
    
}

int AdjacencyListGraph::dijkstra(vector<Edge*> &returnThis, string startCode, string endCode) //intput is an output array, a previous array, and the starting index
{
    
    vector<tuple<float,Vertex*,Edge*> > returnQueue;//this is what we're using to hold our nodes, each node having a vertex, a weight to get there from the start node, and the edge that takes it to get there
    unordered_map<string, tuple<float, Vertex*, Edge*> > Q;//this contains the current weight of the node and the code of its most recent edge that leads to it. We're using this as a priority queue, sorting by weight
    bool foundStart = false;//just a boolean to check if our starting code is even there
    bool foundEnd = false; //checking if our end code is valid
    unordered_map<string, Vertex*>::const_iterator u;
    for (unordered_map<string, Vertex*>::const_iterator u = vertices.begin(); u != vertices.end(); u++) //initializing our elements to infinity for everything but our start node
    {
        tuple<float,Vertex*,Edge*> myTuple;//need to store weight, vertex, and associated edge
        string coooode = u.operator*().second->code;//getting the code so we can try to match it with our startCode
        if (coooode != startCode && coooode != endCode)
        {
            get<0>(myTuple) = INFINITY;//associatted weight with getting to that vertex
        }
        else if (coooode == endCode)
        {
            get<0>(myTuple) = INFINITY;
            foundEnd = true;
        }
        else//if we found our code we set it to 0 instead
        {
            get<0>(myTuple) = 0;
            foundStart = true;
        }
        get<1>(myTuple) = u.operator*().second;//adding in our vertices by pointer
        get<2>(myTuple) = nullptr;
        Q[coooode] = myTuple;    //add each node into queue
    }
    if (!foundStart)//indicates an invalid start code
    {
        cout << "ERROR: Start code not found" << endl;
        return 0;
    }
    if (!foundEnd)//indicates an invalid end code
    {
        cout << "ERROR: End code not found" << endl;
        return 0;
    }
    
    C isless;//comparator object, contained in our private variables
    
    unordered_map<string, bool> hasVisited;//map just to track which places we've visited. By default its all false
    while (!Q.empty()) {
        //cout << "Q size " << Q.size() << endl;
        //cout << "MADE IT HERE" << endl;
        unordered_map<string, tuple<float, Vertex*, Edge*>> ::const_iterator i;
        i = min_element(Q.begin(), Q.end(), isless);
        Vertex* curVertex = get<1>(i.operator*().second);
        //cout << "Min element is " << get<1>(i.operator*().second)->code << endl;
        
        for (auto it : vertices[curVertex->code]->edges) //going through the adjacent edges one by one
        {
            if (!hasVisited[it.second->destination->code] && ((get<0>(i.operator*().second) + (it.second->weight)) < get<0>(Q[it.second->destination->code]))) //if the weight of the edge plus the weight of our current vertex is less than what we have down
            {
                //cout << "Assigning weight: "<<  (get<0>(i.operator*().second) + (it.second->weight)) << endl;
                //cout << "Assigning edge: " << it.second->edgeCode << endl;
                get<0>(Q[it.second->destination->code]) = (get<0>(i.operator*().second) + (it.second->weight));//then we assign it the new path length value
                get<2>(Q[it.second->destination->code]) = it.second;//we then assign it the edge that leads to it
                
            }
        }
        returnQueue.push_back(i.operator*().second);//we push the tuple into a temporary holding place
        string code3 = curVertex->code;
        //cout << "CODE: " << code3<<endl;
        hasVisited[get<1>(i.operator*().second)->code] = true;//setting our current node as visited so we don't hit it again.
        Q.erase(i);//erasing so that we don't go over it again.
        /*
         for (unordered_map<string, tuple<float, Vertex*, Edge*> >::const_iterator myIt = Q.begin(); myIt != Q.end(); myIt++)//troubleshooting cout loop just to make sure we're deleting a node every iteration
         {
         cout << myIt.operator*().first << endl;
         }
         */
    }
    tuple<float, Vertex*, Edge*> currrVertex;
    
    vector<tuple<float, Vertex*, Edge*>>::iterator ib;
    //cout << endl << "Currently in returnQueue: " << endl;
    for (ib = returnQueue.begin(); ib != returnQueue.end(); ib++)
    {
        //cout << "1. " << get<1>(ib.operator*())->name << " Edge: ";
        if (get<2>(ib.operator*()) != nullptr)
        {
            //cout << get<2>(ib.operator*())->edgeCode << " Goes back to "<< get<2>(ib.operator*())->source->code;
        }
        //cout << endl;
    }
    for (ib = returnQueue.begin(); ib != returnQueue.end(); ib++)
    {
        //cout << "TEST:" << get<1>(ib.operator*())->name << "SIZE: " << returnQueue.size()<<endl;
        if (get<1>(ib.operator*())->code == endCode)
        {
            
            currrVertex = ib.operator*();//finding our vertex so we can backtrack
            returnQueue.erase(ib);
            
            ib = returnQueue.end();
            
            break;
        }
    }
    bool found1 = false;
    stack<tuple<float, Vertex*, Edge*>> returnStack;
    int numLoops = 0;
    while (!found1)
    {
        
        for (ib = returnQueue.begin(); ib != returnQueue.end(); ib++)
        {
            //get<2> returns the edge that leads to the node associated with currrVertex
            if ((get<2>(currrVertex))->source->code == (get<1>(ib.operator*()))->code)//we're looking for the tuple that contains the vertex connected to our current vertex by backtracking from edge.
            {
                //cout << "Pushing the following element into our stack: "<<get<1>(currrVertex)->code << endl;
                //push it into our stack
                returnStack.push(currrVertex);
                //our new current vertex is the current iterator
                currrVertex = ib.operator*();
                returnQueue.erase(ib);
                if (get<1>(currrVertex)->code == startCode)
                {
                    //if we backtracked and hit our starting index then we've created a full path from our destination back to our source
                    found1 = true;//end our loop and now we have a full path, in backwards order, in our stack
                }
                break;
            }
            
        }
        numLoops++;//tracking how many loops we've made
        if (numLoops > (returnQueue.size()+1) && !found1)//There is at most n edges (n being the number of vertices) between one node and another if it is reachable
            //So if we exceed this number of searches and still haven't found our startcode then the end and beginning are not connected
        {
            cout << "Start code and end Code are not connnected" << endl;
            return 0;
        }
    }
    float totalCost=0;
    int p = returnStack.size();
    for (int ie = 0; ie < p; ie++)//popping the stack into the return vector. This gives us a path in the right order
    {
        
        //cout << "Name: " << get<2>(returnStack.top())->edgeCode << endl;
        returnThis.push_back(get<2>(returnStack.top()));
        totalCost += get<2>(returnStack.top())->weight;//the sum of the weight of the edges is equal to the total weight
        returnStack.pop();
        //if we're at the bottom of the stack, record the weight to get to the last element and return it
    }
    return totalCost;
}


void AdjacencyListGraph::printDijkstraNode(string startCode, string endCode)
{
    vector<Edge*> printlist;
    int numStops = dijkstraNode(printlist, startCode, endCode);
    if (printlist.size() == 0)
    {
        cout << "ERROR: INVALID NODES OR EDGES NOT FOUND" << endl;
        return;
    }
    float totalStops = 0;
    for (int i = 0; i < printlist.size(); i++)
    {
        cout << "Node: " << printlist.at(i)->source->name << endl;
        cout << "Edge code: " << printlist.at(i)->edgeCode;
        cout << " going to " << printlist.at(i)->destination->name << endl;
    }
    cout << "Number of node visits: " << numStops << endl<<endl;
}

int AdjacencyListGraph::dijkstraNode(vector<Edge*>& returnThis, string startCode, string endCode) //exactly the same as dijkstra except that every edge has weight of 1.
{
    
    vector<tuple<float, Vertex*, Edge*> > returnQueue;//this is what we're using to hold our nodes, each node having a vertex, a weight to get there from the start node, and the edge that takes it to get there
    unordered_map<string, tuple<float, Vertex*, Edge*> > Q;//this contains the current weight of the node and the code of its most recent edge that leads to it. We're using this as a priority queue, sorting by weight
    bool foundStart = false;//just a boolean to check if our starting code is even there
    bool foundEnd = false; //checking if our end code is valid
    unordered_map<string, Vertex*>::const_iterator u;
    for (unordered_map<string, Vertex*>::const_iterator u = vertices.begin(); u != vertices.end(); u++) //initializing our elements to infinity for everything but our start node
    {
        tuple<float, Vertex*, Edge*> myTuple;//need to store weight, vertex, and associated edge
        string coooode = u.operator*().second->code;//getting the code so we can try to match it with our startCode
        if (coooode != startCode && coooode != endCode)
        {
            get<0>(myTuple) = INFINITY;//associatted weight with getting to that vertex
        }
        else if (coooode == endCode)
        {
            get<0>(myTuple) = INFINITY;
            foundEnd = true;
        }
        else//if we found our code we set it to 0 instead
        {
            get<0>(myTuple) = 0;
            foundStart = true;
        }
        get<1>(myTuple) = u.operator*().second;//adding in our vertices by pointer
        get<2>(myTuple) = nullptr;
        Q[coooode] = myTuple;    //add each node into queue
    }
    if (!foundStart)//indicates an invalid start code
    {
        cout << "ERROR: Start code not found" << endl;
        return 0;
    }
    if (!foundEnd)//indicates an invalid end code
    {
        cout << "ERROR: End code not found" << endl;
        return 0;
    }
    
    C isless;//comparator object, contained in our private variables
    
    unordered_map<string, bool> hasVisited;//map just to track which places we've visited. By default its all false
    while (!Q.empty()) {

        unordered_map<string, tuple<float, Vertex*, Edge*>> ::const_iterator i;
        i = min_element(Q.begin(), Q.end(), isless);
        Vertex* curVertex = get<1>(i.operator*().second);

        
        for (auto it : vertices[curVertex->code]->edges) //going through the adjacent edges one by one
        {
            if (!hasVisited[it.second->destination->code] && ((get<0>(i.operator*().second) + 1) < get<0>(Q[it.second->destination->code]))) //if the weight of the edge plus the weight of our current vertex is less than what we have down
            {
                cout << "Assigning weight: "<< (get<0>(i.operator*().second) + 1) << endl;
                cout << "Assigning edge: " << it.second->edgeCode << endl;
                get<0>(Q[it.second->destination->code]) = (get<0>(i.operator*().second) + 1);//then we assign it the new path length value
                get<2>(Q[it.second->destination->code]) = it.second;//we then assign it the edge that leads to it
                
            }
        }
        returnQueue.push_back(i.operator*().second);//we push the tuple into a temporary holding place
        string code3 = curVertex->code;
        //cout << "CODE: " << code3<<endl;
        hasVisited[get<1>(i.operator*().second)->code] = true;//setting our current node as visited so we don't hit it again.
        Q.erase(i);//erasing so that we don't go over it again.
        /*
         for (unordered_map<string, tuple<float, Vertex*, Edge*> >::const_iterator myIt = Q.begin(); myIt != Q.end(); myIt++)//troubleshooting cout loop just to make sure we're deleting a node every iteration
         {
         cout << myIt.operator*().first << endl;
         }
         */
    }
    tuple<float, Vertex*, Edge*> currrVertex;
    
    vector<tuple<float, Vertex*, Edge*>>::iterator ib;
    //deprecated testing code
    /*
    for (ib = returnQueue.begin(); ib != returnQueue.end(); ib++)
    {
        if (get<2>(ib.operator*()) != nullptr)
        {
            //cout << get<2>(ib.operator*())->edgeCode << " Goes back to "<< get<2>(ib.operator*())->source->code;
        }
        //cout << endl;
    }*/
    for (ib = returnQueue.begin(); ib != returnQueue.end(); ib++)
    {
        //cout << "TEST:" << get<1>(ib.operator*())->name << "SIZE: " << returnQueue.size()<<endl;
        if (get<1>(ib.operator*())->code == endCode)
        {
            
            currrVertex = ib.operator*();//finding our vertex so we can backtrack
            returnQueue.erase(ib);
            
            ib = returnQueue.end();
            
            break;
        }
    }
    bool found1 = false;
    stack<tuple<float, Vertex*, Edge*>> returnStack;
    int numLoops = 0;
    while (!found1)
    {
        
        for (ib = returnQueue.begin(); ib != returnQueue.end(); ib++)
        {
            //get<2> returns the edge that leads to the node associated with currrVertex
            if ((get<2>(currrVertex))->source->code == (get<1>(ib.operator*()))->code)//we're looking for the tuple that contains the vertex connected to our current vertex by backtracking from edge.
            {
                //cout << "Pushing the following element into our stack: "<<get<1>(currrVertex)->code << endl;
                //push it into our stack
                returnStack.push(currrVertex);
                //our new current vertex is the current iterator
                currrVertex = ib.operator*();
                returnQueue.erase(ib);
                if (get<1>(currrVertex)->code == startCode)
                {
                    //if we backtracked and hit our starting index then we've created a full path from our destination back to our source
                    found1 = true;//end our loop and now we have a full path, in backwards order, in our stack
                }
                break;
            }
            
        }
        numLoops++;//tracking how many loops we've made
        if (numLoops > (returnQueue.size() + 1) && !found1)//There is at most n edges (n being the number of vertices) between one node and another if it is reachable
            //So if we exceed this number of searches and still haven't found our startcode then the end and beginning are not connected
        {
            cout << "Start code and end Code are not connnected" << endl;
            return 0;
        }
    }
    int p = returnStack.size();//the size is how many stops you make, since we're tracking the minimum number of stops.
    for (int ie = 0; ie < p; ie++)//popping the stack into the return vector. This gives us a path in the right order
    {
        
        //cout << "Name: " << get<2>(returnStack.top())->edgeCode << endl;
        returnThis.push_back(get<2>(returnStack.top()));
        returnStack.pop();
    }
    return p;
}
vector<vector<string>> AdjacencyListGraph::AllPaths(string curVertex, string endVertex)//function just in case we want traversal information for other than display reasons
{
    vector< vector<string>> returnVector;
    vector<string> curPath;
    unordered_map<string, bool> hasVisited;
    AllPathsRecurs(curVertex, endVertex, hasVisited, returnVector, curPath);
    return returnVector;
}

void AdjacencyListGraph::AllPathsDisplay(string curVertex, string endVertex)//display function
{
    vector<vector<string>> returnVector;
    vector<string> curPath;
    unordered_map<string, bool> hasVisited;
    AllPathsRecurs(curVertex, endVertex, hasVisited, returnVector, curPath);
    if (returnVector.size()==0)
    {
        cout << "ERROR: NO PATHS AVAILABLE" << endl;
        return;
    }
    cout << "Available traversal paths: " << endl;
    for (int i = 0; i < returnVector.size(); i++)
    {
        cout << i+1<<": "<< Edges[returnVector.at(i).front()]->source->code;//printing out the very first element
        vector<string> curVector = returnVector.at(i);
        while (!curVector.empty())
        {
            Edge* myEdge = Edges[curVector.front()];
            cout << "-->" << myEdge->edgeCode << "-->" << myEdge->destination->code;//printing out paths edge by edge
            curVector.erase(curVector.begin());
        }
        cout << endl;
    }
    cout << endl;
}

void AdjacencyListGraph::AllPathsRecurs(string curVertex, string endVertex, unordered_map<string, bool>& hasVisited, vector<vector<string>>& returnVector, vector<string>& curPath)
{
    hasVisited[curVertex] = true;//marking this node as having been visited
    if (vertices[endVertex]->code == vertices[curVertex]->code)//if we reached our destination, the path we've been accumulating works out
    {
        
        returnVector.push_back(curPath);
    }
    else
    {
        unordered_map<string, Edge*>::const_iterator it;
        for (it = vertices[curVertex]->edges.begin(); it != vertices[curVertex]->edges.end();++it)//traversing through all the adjacent edges
        {
            if (!hasVisited[it.operator*().second->destination->code])//if we've visited it we don't wanna investigate it
            {
                string newVertex = it.operator*().second->destination->code;// then we move our current node to there
                curPath.push_back(it.operator*().second->edgeCode);//and then we add it to the current path, just in case we find our goal node
                AllPathsRecurs(newVertex, endVertex, hasVisited, returnVector, curPath);
            }
        }
    }
    hasVisited[curVertex] = false;//setting it false so we don't exclude this node from other parallel paths but it does exclude it from the searches from subsequent recursive calls
    vector<string>::iterator iq = curPath.end();
    if (curPath.size()!=1)
    {
        iq--;//we need to delete one of the nodes each time we finish a recursive call so nodes that are in the paths we visited don't show up in the new ones we go through
        curPath.erase(iq);
    }
    
    return;//done. Go back
}


void AdjacencyListGraph::TraverseAllDisplay(string curVertex)//display function
{
    vector<vector<string>> returnVector;
    vector<string> curVector;
    unordered_map<string, bool> hasVisited;
    TraverseAllRecurs(curVertex, hasVisited, curVector);
    if (curVector.size() == 0)
    {
        cout << "ERROR: NO EDGES AVAILABLE" << endl;
        return;
    }
    cout << "Total paths to all nodes: " << endl;
    while (!curVector.empty())
    {
        Edge* myEdge = Edges[curVector.front()];
        cout << "-->" << myEdge->edgeCode << "-->" << myEdge->destination->code;//printing out paths edge by edge
        curVector.erase(curVector.begin());
    }
    cout << endl;
    cout << endl;
}

void AdjacencyListGraph::TraverseAllRecurs(string curVertex,unordered_map<string, bool>& hasVisited, vector<string>& curPath)
{
    hasVisited[curVertex] = true;//marking this node as having been visited
    
    unordered_map<string, Edge*>::const_iterator it;
    for (it = vertices[curVertex]->edges.begin(); it != vertices[curVertex]->edges.end();++it)//traversing through all the adjacent edges
    {
        if (!hasVisited[it.operator*().second->destination->code])//if we've visited it we don't wanna investigate it
        {
            string newVertex = it.operator*().second->destination->code;// then we move our current node to there
            curPath.push_back(it.operator*().second->edgeCode);//and then we add it to the current path, just in case we find our goal node
            //cout << "Pushing " << it.operator*().second->edgeCode << endl;
            //queue<string> newCurPath(curPath);//making a copy to pass to our function because if we use the original, itll pass by reference and
            TraverseAllRecurs(newVertex, hasVisited, curPath);
        }
    }
    //hasVisited[curVertex] = false;//setting it false so we don't exclude this node from other parallel paths but it does exclude it from the searches from subsequent recursive calls
    
    
    
    return;//done. Go back
}
