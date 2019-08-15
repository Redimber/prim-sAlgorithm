//
//  main.cpp
//  Prim'sAlgorithm
//
//  Created by Ibrahim El Mountasser on 8/15/19.
//  Copyright © 2019 Ibrahim El Mountasser. All rights reserved.
//
//In this programming problem you'll code up Prim's minimum spanning tree algorithm.
//
//Download the text file below.
//
//edges.txt
//This file describes an undirected graph with integer edge costs. It has the format
//
//[number_of_nodes] [number_of_edges]
//
//[one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]
//
//[one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]
//
//...
//
//For example, the third line of the file is "2 3 -8874", indicating that there is an edge connecting vertex #2 and vertex #3 that has cost -8874.
//
//You should NOT assume that edge costs are positive, nor should you assume that they are distinct.
//
//Your task is to run Prim's minimum spanning tree algorithm on this graph. You should report the overall cost of a minimum spanning tree --- an integer, which may or may not be negative --- in the box below.
//
//IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn) time implementation of Prim's algorithm should work fine. OPTIONAL: For those of you seeking an
//additional challenge, try implementing a heap-based version. The simpler approach, which should already give you a healthy speed-up, is to maintain relevant edges in a heap (with
//keys = edge costs).
//The superior approach stores the unprocessed vertices in the heap, as described in lecture. Note this requires a heap that supports deletions, and you'll probably need to maintain
//some kind of
//mapping between vertices and their positions in the heap.

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

void addEdge(std::vector <std::pair<int, int>> adj[], int u, int v, int wt) {
    adj[u].push_back(std::make_pair(v, wt));
    adj[v].push_back(std::make_pair(u, wt));
}

long long primAlgo(std::vector <std::pair<int, int>> adj[]) {
    long long result = 0;
    std::vector <std::pair<int, int>> heap;
    heap.push_back(std::make_pair(1, 0));
    for (int i=2; i<=500; i++) {
        heap.push_back(std::make_pair(i, INT_MAX));
    }
    
    while (!heap.empty()) {
        auto it = std::min_element(heap.begin(), heap.end(), [](auto& lhs, auto& rhs ) { return lhs.second < rhs.second;});
        int vr = it->first;
        result += it->second;
        heap.erase(it);
        for (auto &p : adj[vr]) {
            int pair = p.first;
            for (auto &pr : heap) {
                if (pr.first == pair) {
                    if (pr.second > p.second) {
                        pr.second = p.second;
                    }
                }
            }
            
        }
    }
    
    return result;
}
int main(int argc, const char * argv[]) {
    std::vector<std::pair<int, int>> adj[501];
    std::ifstream file("edges.txt");
    int u,v,wt;
    std::cout<<"building the graph..."<<std::endl;
    while (file>>u>>v>>wt) {
        std::cout<<u<<"-"<<v<<" : "<<wt<<std::endl;
        addEdge(adj, u, v, wt);
    }
    std::cout<<primAlgo(adj);
    
    return 0;
}
