/*
* Ujwal Kumar Mamidi, s3844467
* I started of with the Nodes.cpp file. As it was simple
* Getters and setters, it didn't take too long to implement.
* 
*
*
*
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList *solution);

int main(int argc, char **argv)
{
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl
    //           << std::endl;

    // Load Environment
    Env env;
    readEnvStdin(env);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver *pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList *exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList *solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;
}

void readEnvStdin(Env env)
{
    // creates the environment by rows and cols.
    // standard input reads rows and cols.
    for (int i = 0; i < ENV_DIM; i++)
    {
        for (int j = 0; j < ENV_DIM; j++)
        {
            std::cin >> env[i][j];
        }
    }
}

void printEnvStdout(Env env, NodeList *solution)
{
    // each direction's arrows.
    char moveUp = '^';
    char moveDown = 'v';
    char moveRight = '>';
    char moveLeft = '<';

    // loops through the getPath list of positions. 
    for (int i = 0; i < solution->getLength(); i++)
    {
        // gets path's row and col
        int getNodeRow = solution->getNode(i)->getRow();
        int getNodeCol = solution->getNode(i)->getCol();

        /*
        * checks if the environment's position = to start
        * or goal.
        * If so, check directions. 
        * Checksif current position is equal to new position.
        * If so, env(col and row) = arrow direction
        */

        if (env[getNodeRow][getNodeCol] != SYMBOL_START 
            && env[getNodeRow][getNodeCol] != SYMBOL_GOAL)
        {
            Node *nextElement = solution->getNode(i + 1);

            //north
            if ((getNodeRow - 1) == nextElement->getRow() 
                && getNodeCol == nextElement->getCol())
            {
                env[getNodeRow][getNodeCol] = moveUp;
            }

            //south
            if ((getNodeRow + 1) == nextElement->getRow() 
                && getNodeCol == nextElement->getCol())
            {
                env[getNodeRow][getNodeCol] = moveDown;
            }

            //east
            if (getNodeRow == nextElement->getRow() 
                && (getNodeCol + 1) == nextElement->getCol())
            {
                env[getNodeRow][getNodeCol] = moveRight;
            }

            //west
            if (getNodeRow == nextElement->getRow() 
                && (getNodeCol - 1) == nextElement->getCol())
            {
                env[getNodeRow][getNodeCol] = moveLeft;
            }
        }
    }

    // prints out 20x20 environment.
    for (int i = 0; i < ENV_DIM; i++)
    {
        for (int j = 0; j < ENV_DIM; j++)
        {
            std::cout << env[i][j];
        }
        std::cout << std::endl;
    }
}

void testNode()
{
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node *node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList()
{
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList *nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node *b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node *b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node *getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}