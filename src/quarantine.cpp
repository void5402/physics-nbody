//ai gave me this code, maybe will use it to approximate and optimize code, and if im lucky i might get that cool side effect
#include <iostream>
#include <vector>
#include <cmath>

// Structure to represent a body in the simulation
struct Body {
    double x, y; // position
    double vx, vy; // velocity
    double mass; // mass
};

// Structure to represent a cell in the Barnes-Hut tree
struct Cell {
    double x, y; // center of mass
    double mass; // total mass
    int numBodies; // number of bodies in cell
    std::vector<Body*> bodies; // list of bodies in cell
    Cell* parent; // parent cell
    Cell* child[4]; // child cells
};

// Function to create a new cell
Cell* createCell(double x, double y, double mass) {
    Cell* cell = new Cell;
    cell->x = x;
    cell->y = y;
    cell->mass = mass;
    cell->numBodies = 0;
    cell->parent = nullptr;
    for (int i = 0; i < 4; i++) {
        cell->child[i] = nullptr;
    }
    return cell;
}

// Function to insert a body into the Barnes-Hut tree
void insertBody(Cell* cell, Body* body) {
    // If cell is a leaf node, add body to list of bodies
    if (cell->numBodies == 0) {
        cell->bodies.push_back(body);
        cell->numBodies++;
        return;
    }

    // If cell is not a leaf node, recursively insert body into child cell
    double dx = body->x - cell->x;
    double dy = body->y - cell->y;
    int childIndex = (dx > 0) * 2 + (dy > 0);
    if (cell->child[childIndex] == nullptr) {
        cell->child[childIndex] = createCell(cell->x + dx, cell->y + dy, 0);
    }
    insertBody(cell->child[childIndex], body);
}

// Function to compute the force between a body and a cell
void computeForce(Body* body, Cell* cell, double& fx, double& fy) {
    double dx = body->x - cell->x;
    double dy = body->y - cell->y;
    double r = sqrt(dx * dx + dy * dy);
    double force = cell->mass / (r * r);
    fx += force * dx / r;
    fy += force * dy / r;
}

// Function to traverse the Barnes-Hut tree and compute forces
void traverseTree(Cell* cell, Body* body, double& fx, double& fy) {
    // If cell is a leaf node, compute force between body and each body in cell
    if (cell->numBodies > 0) {
        for (Body* otherBody : cell->bodies) {
            double dx = body->x - otherBody->x;
            double dy = body->y - otherBody->y;
            double r = sqrt(dx * dx + dy * dy);
            double force = otherBody->mass / (r * r);
            fx += force * dx / r;
            fy += force * dy / r;
        }
        return;
    }

    // If cell is not a leaf node, recursively traverse child cells
    double dx = body->x - cell->x;
    double dy = body->y - cell->y;
    int childIndex = (dx > 0) * 2 + (dy > 0);
    if (cell->child[childIndex] != nullptr) {
        traverseTree(cell->child[childIndex], body, fx, fy);
    }

    // If cell is "far enough" away, compute force between body and cell
    double r = sqrt(dx * dx + dy * dy);
    if (r > 1.0) { // adjust this value to control the accuracy of the simulation
        computeForce(body, cell, fx, fy);
    }
}

int main() {
    // Create a list of bodies
    std::vector<Body> bodies;
    bodies.push_back({0, 0, 0, 0, 1});
    bodies.push_back({1, 0, 0, 0, 1});
    bodies.push_back({0, 1, 0, 0, 1});
    bodies.push_back({1, 1, 0, 0, 1});

    // Create the Barnes-Hut tree
    Cell* root = createCell(0, 0, 0);
    for (Body& body : bodies) {
        insertBody(root, &body);
    }

    // Compute forces between bodies
    for (Body& body : bodies) {
        double fx = 0, fy = 0;
        traverseTree(root, &body, fx, fy);
        std::cout << "Force on body " << body.x << " " << body.y << ": " << fx << " " << fy << std::endl;
    }

    return 0;
}
