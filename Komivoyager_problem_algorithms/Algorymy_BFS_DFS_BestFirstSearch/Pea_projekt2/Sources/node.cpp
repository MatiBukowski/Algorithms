//
// Created by mateu on 05.11.2024.
//

#include "node.h"

#include <iostream>

using namespace std;

Node::Node(int Level, int Distance, int Bound, int Cities_number, int Path_size) {
    level = Level;
    distance = Distance;
    bound = Bound;
    cities_number = Cities_number;
    path_size = Path_size;
}

Node::~Node() {
    delete[] visited;
    delete[] path_array;
}

int Node::getLevel() {
    return level;
}

int Node::getDistance() {
    return distance;
}

int Node::getBound() {
    return bound;
}

void Node::create_visited_array(bool Visited[]) {
    visited = new bool[cities_number];
    for(int i = 0; i < cities_number; i++) {
        visited[i] = Visited[i];
    }
    // visited = Visited;
}

bool* Node::getVisited() {
    return visited;
}

void Node::displayVisited() {
    for (int i = 0; i < 8; i++) {
        cout << visited[i] << " ";
    }
    cout << endl;
}

int* Node::make_path(int* current_path) {
    path_array = new int[path_size-1];                  // path_size już jest powiększone o 1 w porównaniu z rodzicem
    for (int i = 0; i < path_size-1; i++) {
        path_array[i] = current_path[i];
    }
    return path_array;
}

void Node::add_to_path(int city) {
    int* new_path_array = new int[path_size];

    if(path_array != nullptr) {
        for(int i = 0; i < path_size-1; i++) {
            new_path_array[i] = path_array[i];
        }
        delete [] path_array;
    }
    new_path_array[path_size-1] = city;


    path_array = new_path_array;
    // path_array = new int[path_size];
    // for(int i = 0; i < path_size-1; i++) {
    //     path_array[i] = new_path_array[i];
    // }
    //
    // delete[] new_path_array;
}

int* Node::getPathArray() {
    return path_array;
}

int Node::getPathSize() {
    return path_size;
}

