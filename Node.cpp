#include "Node.h"
#include <iostream>

Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node()
{
}

int Node::getRow()
{
    return this->row;
}

int Node::getCol()
{
    return this->col;
}

int Node::getDistanceTraveled()
{
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

/*
 * Calculate formula: Manhattan_distance = |colp − colG| + |rowp − rowG|
 * Estimated distance = distance_travelled + Manhattan distance
 */
int Node::getEstimatedDist2Goal(Node *goal)
{
    int colDist = abs(this->getCol() - goal->getCol()); 
    int rowDist = abs(this->getRow() - goal->getRow()); 
    int manhattanDist = colDist + rowDist;
    int estimatedDist = this->getDistanceTraveled() + manhattanDist;
    return estimatedDist;
}

/*
 * Checks if the current node = another node.
 * Compare rows and columns and return true if same.
 */
bool Node::equals(Node *compareNode) 
{
    bool isSame = false;
    if (((this->getRow() == compareNode->getRow()) 
        && (this->getCol() == compareNode->getCol())))
    {
        isSame = true;
    }
    return isSame;
}