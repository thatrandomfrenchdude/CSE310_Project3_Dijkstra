//
//  main.cpp
//  Project03
//
//  Created by Nicholas Debeurre on 4/16/17.
//  Copyright © 2017 Samoji. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "main.h"
#include "heap.h"
#include "graph.h"
#include "util.h"

using namespace std;

int main()
{
    //declares variables
    ifstream myFile ("GRAPHinput.txt");
    Graph *myGraph = NULL;
    int n;
    int m;
    int u; //start node
    int v; //end node
    int w; //weight
    int s; //shortest path start
    int t; //shortest path finish
    int count = 0;
    
    char ch = 'i';
    do
    {
        cout << "Project 3 Main Menu\n";
        cout << "Pick a letter please\n";
        cout << "\tR: reads an edge weighted directed graph and builds adjacency lists\n";
        cout << "\tW: writes the current information to the screen\n";
        cout << "\tP s t: decreases the key of the element at index i to the value v\n";
        cout << "\tS: Quit the program\n";
        cin >> ch;
        switch (ch)
        {
            case 'R':
            {
                if (count == 0)
                {
                    if (myFile.is_open())
                    {
                        if (myFile.peek() == EOF)
                        {
                            cout << "Error: the file is empty";
                            break;
                        }
                        else
                        {
                            myFile >> n;
                            myFile >> m;
                            myGraph = newGraph(n, m);
                            for (int i = 1; i <= m; i++)
                            {
                                myFile >> u; //start
                                myFile >> v; //end
                                myFile >> w; //weight
                                addEdge(u, v, w, myGraph); //adds an edge
                            }
                            break;
                        }
                    }
                    else
                    {
                        cout << "Error: the file is not open or does not exist";
                        break;
                    }
                }
            }
            case 'W':
            {
                Graph *temp = myGraph;
                printGraph(temp);
                cout << "\n";
                break;
            }
            case 'P':
            {
                if (myGraph == NULL)
                {
                    flush();
                    printf("Error: graph not initialized\n");
                    break;
                }
                else
                {
                    cin >> s;
                    cin >> t;
                    dijkstra(myGraph, s, t, false);
                    break;
                }
            }
            case 'Q':
            {
                if (myGraph == NULL)
                {
                    flush();
                    printf("Error: graph not initialized\n");
                    break;
                }
                else
                {
                    cin >> s;
                    cin >> t;
                    dijkstra(myGraph, s, t, true);
                    break;
                }
            }
            case 'S':
            {
		break;
            }
            default:
                cout << "\nInvalid input: Please use uppercase letters!\n\n";
        }
    } while (ch != 'S');
    return 0;
}
