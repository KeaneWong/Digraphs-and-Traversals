#include "AdjacencyListGraph.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main()
{
    AdjacencyListGraph myGraph;
    string inputFile;
    cout << "Input the airport input file name: " << endl;
    cin >> inputFile;
    ifstream myFile;
    myFile.open(inputFile);
    string curLine;
    while (std::getline(myFile,curLine))
    {
        string name;
        string code;
        for (int i = 0; i < curLine.size(); i++)
        {
            if (curLine[i] == ' ')
            {
                code = curLine.substr(0, i);//gives us a substring consisting of just the key
                name = curLine.substr(i + 1, curLine.size()); // assumes the rest of the string is just the name
                break;
            }
        }
        
        myGraph.insertVertex(name, code);
    }
    myFile.close();
    cout << "Input the flights input file name: " << endl;
    cin>>inputFile;
    myFile.open(inputFile);
    string flightNumber;
    string Destination;
    string Source;
    float cost;
    while (myFile >> Source>>Destination>>cost >> flightNumber)
    {
        myGraph.addEdge(cost, flightNumber, Source, Destination);
    }
    string input1;
    cout << "Choose from the following options: " << endl;
    cout << "1. Display airport information" << endl;
    cout << "2. Find a cheapest flight from one airport to another airport" << endl;
    cout << "3. Find a cheapest roundtrip from one airport to another airport" << endl;
    cout << "4. Add a flight from one airport to another airport"<<endl;
    cout << "5. Delete a flight from one airport to another airport" << endl;
    cout << "6. Find a flight with fewest stops from one airport to another airport"<<endl;
    cout << "7. Find all flights from one airport to another airport" << endl;
    cout << "8. Find an order to visit all airports starting from an airport" << endl;
    cout << "9. Delete an existing airport"<<endl;
    cout << "Q.Exit" << endl;
    //C:\Users\keane\Downloads\P4Airports.txt
    //C:\Users\keane\Downloads\P4Flights.txt
    //C:\Users\keane\Downloads\P4FlightsRev1.txt
    while (cin >> input1)
    {
        int input;
        if (input1 == "Q")
        {
            input = -1;
        }
        else
        {
            input = std::stoi(input1);
        }
        switch (input) {
            case 1: {
                
                cout << "Enter the source airport code (enter 0 to display all airports): " << endl;
                string soruce;
                cin >> soruce;
                if (soruce == "0")
                {
                    myGraph.displayNodes();
                    break;
                }
                
                myGraph.displayNode(soruce);
                break;
            }
            case 2: {
                cout << "Enter the source airport code: " << endl;
                string soruce;
                cin >> soruce;
                cout << "Enter the destination airport code: " << endl;
                string dsetination;
                cin >> dsetination;
                myGraph.printDijkstra(soruce, dsetination);
                break;
            }
            case 3: {
                cout << "Enter the source airport code: " << endl;
                string soruce;
                cin >> soruce;
                cout << "Enter the destination airport code: " << endl;
                string dsetination;
                cin >> dsetination;
                myGraph.printDijkstraRoundTrip(soruce, dsetination);
                break;
            }
            case 4: {
                
                cout << "Enter the code of the source city: " << endl;
                string soruce;
                cin >> soruce;
                cout << "Enter the code of the destination city: " << endl;
                string dsetination;
                cin >> dsetination;
                cout << "Enter the flight number: " << endl;
                string fNumber;
                cin >> fNumber;
                cout << "Finally, enter the cost: " << endl;
                float cosut;
                cin >> cosut;
                myGraph.addEdge(cosut, fNumber, soruce, dsetination);
                cout << "Added successfully" << endl;
                break;
            }
            case 5: {
                cout << "Enter the flight code (Enter 1) or enter the source and destination node codes (Enter 2)? " << endl;
                int inpuit;
                cin >> inpuit;
                switch (inpuit) {
                    case 1:
                    {
                        cout << "Enter flight code: " << endl;
                        string tbdeleted;
                        cin >> tbdeleted;
                        myGraph.deleteEdge(tbdeleted);
                        //cout << "Deleted successfully" << endl;
                        break;
                    }
                        
                    case 2:
                    {
                        cout << "Enter source airport code: " << endl;
                        string soruce;
                        cin >> soruce;
                        cout << "Enter the destination airport code: " << endl;
                        string dsetination;
                        cin >> dsetination;
                        myGraph.deleteEdge(soruce, dsetination);
                        cout << "Deleted successfully" << endl;
                        break;
                    }
                    default:
                        cout << "Deletion cancelled" << endl;
                        break;
                        
                }
                break;
            }
            case 6: {
                cout << "Enter the source airport code: " << endl;
                string soruce;
                cin >> soruce;
                cout << "Enter the destination airport code: " << endl;
                string dsetination;
                cin >> dsetination;
                myGraph.printDijkstraNode(soruce, dsetination);
                break;
            }
            case 7:
            {
                cout << "Enter the source airport code: " << endl;
                string soruce;
                cin >> soruce;
                cout << "Enter the destination airport code: " << endl;
                string dsetination;
                cin >> dsetination;
                myGraph.AllPathsDisplay(soruce, dsetination);
                break;
            }
            case 8: {
                cout << "Enter the starting airport: " << endl;
                string startPort;
                cin>>startPort;
                myGraph.TraverseAllDisplay(startPort);
                break;
            }
            case 9: {
                cout << "Enter the code of the airport to be deleted: " << endl;
                string tbdeleted;
                cin >> tbdeleted;
                myGraph.deleteNode(tbdeleted);
                break;
            }
            case 0: {
                myGraph.displayAll();
                break;
            }
            case -1:
            {
                cout << "Enter the name of the output file for the updated flights: " << endl;
                string p = "C:\\Users\\keane\\Downloads\\P4FlightsRev1.txt";//doing it manually because for some reason i cannot get this to work/
                myGraph.displayEdges(p);
                cin >> p;
                myGraph.displayEdges(p);
                cout << "Confirm exit? (Q) " << endl;
                string qw;
                cin >> qw;
                if (qw == "Q")
                {
                    exit(0);
                }
                
                break;
            }
            default:
                break;
        }
        cout << "Choose from the following options: " << endl;
        cout << "1. Display airport information" << endl;
        cout << "2. Find a cheapest flight from one airport to another airport" << endl;
        cout << "3. Find a cheapest roundtrip from one airport to another airport" << endl;
        cout << "4. Add a flight from one airport to another airport" << endl;
        cout << "5. Delete a flight from one airport to another airport" << endl;
        cout << "6. Find a flight with fewest stops from one airport to another airport" << endl;
        cout << "7. Find all flights from one airport to another airport" << endl;
        cout << "8. Find an order to visit all airports starting from an airport" << endl;
        cout << "9. Delete an existing airport" << endl;
        cout << "Q.Exit" << endl;
        
    }
    
}
