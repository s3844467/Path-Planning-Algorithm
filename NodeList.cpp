#include "NodeList.h"
#include <iostream>

NodeList::NodeList()
{
    // initial length.
    this->length = 0; 
    for (int i = 0; i < length; i++)
    {
        this->nodes[i] = nullptr;
    }
}

/*
* Loops through the nodes array
* checks if each element is equal to nullptr.
*  If it's not = to nullptr, delete nodes.
*/
NodeList::~NodeList()
{
    for (int i = 0; i < length; i++)
    {
        if (nodes[i] != nullptr) 
        {
            delete this->nodes[i];
        }
    }
}

/*
* Deep copies the Nodelist constructor's variables.
* Loops through array of copy Nodelist and copies
* rows, columns and distance traveled.
*/
NodeList::NodeList(NodeList &other)
{
    this->length = (other.length);
    for (int i = 0; i < other.getLength(); i++)
    {
        this->nodes[i] = new Node(other.getNode(i)->getRow(),
                                  other.getNode(i)->getCol(),
                                  other.getNode(i)->getDistanceTraveled());
    }
}

int NodeList::getLength()
{
    return this->length;
}

/*
* adds a new node to the node array.
* increments length by 1 as new nodes get added.
*/
void NodeList::addElement(Node *newNode)
{
    nodes[length] = newNode;
    length = length + 1;
}


// returns a given element from the nodes array.
Node *NodeList::getNode(int i)
{
    return this->nodes[i];
}

/*
* If the nodes array contains the passed in node,
* return true.
*/
bool NodeList::searchNode(Node *node)
{
    bool checkNode = false;
    for (int i = 0; i < length; i++)
    {
        if (nodes[i]->equals(node))
        {
            checkNode = true;
        }
    }
    return checkNode;
}
