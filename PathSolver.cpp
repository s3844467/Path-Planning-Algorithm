#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    this->nodesExplored = new NodeList();
    this->openList = new NodeList();
}

PathSolver::~PathSolver()
{
    delete openList;
}

/*
* Follows the Forward Search Algorithm from the start to goal node.
* It follows the shortest path to get to the goal node.
*/
void PathSolver::forwardSearch(Env env)
{
    // creates start and goal node.
    Node *startNode = new Node(0, 0, 0);
    Node *goalNode = new Node(0, 0, 0);
    // initalises 'p' - the list of positions.
    openList = new NodeList();

    // for loops create the 20x20 environment.
    for (int i = 0; i < ENV_DIM; i++)
    {
        // if the location is 'S'
        for (int j = 0; j < ENV_DIM; j++)
        {
            if (env[i][j] == SYMBOL_START)
            {
                // clear up memory.
                delete startNode;         
                // create a start location.     
                startNode = new Node(i, j, 0);
                //add element to list of positions.
                openList->addElement(startNode);
            }
            // if the location is 'G'
            else if (env[i][j] == SYMBOL_GOAL) 
            {
                delete goalNode;
                // create the goal location.
                goalNode = new Node(i, j, 0); 
            }
        }
    }

    //initialises presentNode to startNode. 
    Node *presentNode = startNode;

    // do-while loop that continues until goal location is found.
    do
    {
        /*
        * Loops through the position from the last element.
        * Creates a new position for comparison that is one element 
        * after current position.
        * Checks if the closed list contains current position, 
        * or current position distance to goal is shorter than the 
        * new position's distance to goal 
        * & if closed list doesn't contain new position.
        * If these conditions are met, current position = new position.
        */
        for (int i = 0; i < openList->getLength() - 1; i++)
        {
            Node *newNode = openList->getNode(i + 1);

            if ((nodesExplored->searchNode(presentNode)) 
            || (presentNode->getEstimatedDist2Goal(goalNode) 
            >= newNode->getEstimatedDist2Goal(goalNode) 
            && !(nodesExplored->searchNode(newNode))))
            {
                presentNode = newNode;
            }
        }

        // intialise current positions location (row, col).
        int currentRow = presentNode->getRow();
        int currentCol = presentNode->getCol();

        /*
        * For north direction, subtract 1 from current row to
        * go up. 
        * If the position above is empty or has the goal location,
        * intialise goUp position, and subtract 1 from row and
        * add 1 to distance traveled.
        * If the goUp position is not in the list of positions,
        * add it to the list of positions.
        */
        if (env[currentRow - 1][currentCol] == SYMBOL_EMPTY 
            || env[currentRow - 1][currentCol] == SYMBOL_GOAL)
        {
            Node *goUp = new Node(currentRow - 1,
                                  currentCol, 
                                  presentNode->getDistanceTraveled() + 1);
            if (!openList->searchNode(goUp))
            {
                openList->addElement(goUp);
            }
        }

        /*
        * For south direction, add 1 to current row to
        * go down. 
        * If the position below is empty or has the goal location,
        * intialise goDown position, and add 1 from row and
        * add 1 to distance traveled.
        * If the goDown position is not in the list of positions,
        * add it to the list of positions.
        */
        if (env[currentRow + 1][currentCol] == SYMBOL_EMPTY 
            || env[currentRow + 1][currentCol] == SYMBOL_GOAL)
        {
            Node *goDown = new Node(currentRow + 1, 
                                    currentCol, 
                                    presentNode->getDistanceTraveled() + 1);
            if (!openList->searchNode(goDown))
            {
                openList->addElement(goDown);
            }
        }

        /*
        * For west direction, subtract 1 from current col to
        * go left. 
        * If the position on left is empty or has the goal location,
        * intialise goLeft position, and minus 1 from col and
        * add 1 to distance traveled.
        * If the goLeft position is not in the list of positions,
        * add it to the list of positions.
        */
        if (env[currentRow][currentCol - 1] == SYMBOL_EMPTY 
            || env[currentRow][currentCol - 1] == SYMBOL_GOAL)
        {
            Node *goLeft = new Node(currentRow, 
                                    currentCol - 1, 
                                    presentNode->getDistanceTraveled() + 1);
            if (!openList->searchNode(goLeft))
            {
                openList->addElement(goLeft);
            }
        }

        /*
        * For east direction, add 1 to current col to
        * go right. 
        * If the position on right is empty or has the goal location,
        * intialise goRight position, and add 1 to col and
        * add 1 to distance traveled.
        * If the goRight position is not in the list of positions,
        * add it to the list of positions.
        */
        if (env[currentRow][currentCol + 1] == SYMBOL_EMPTY 
            || env[currentRow][currentCol + 1] == SYMBOL_GOAL)
        {
            Node *goRight = new Node(currentRow, 
                                     currentCol + 1, 
                                     presentNode->getDistanceTraveled() + 1);
            if (!openList->searchNode(goRight))
            {
                openList->addElement(goRight);
            }
        }

        // add the current position to the positions explored (closedList).
        nodesExplored->addElement(presentNode); 

    } while (!presentNode->equals(goalNode));
}

NodeList *PathSolver::getNodesExplored()
{
    return 0;
}

/*
* Utilises the backtracking algorithm going from Goal to Start.
* However, it revereses the array so that the path goes from
* start to goal.
*/
NodeList *PathSolver::getPath(Env env)
{
    //Initialise a goal List.
    NodeList *getToGoal = new NodeList();
    // deep copy of nodesExplored
    NodeList *copyNodesExplored = new NodeList(*nodesExplored);
    Node *startNode = copyNodesExplored->getNode(0);
    // get the last element from nodesExplored(goalnode).
    Node *presentNode = copyNodesExplored->getNode
                        (copyNodesExplored->getLength() - 1); 
    //add current node to list of goal position.
    getToGoal->addElement(presentNode);

    /*
    * Do-while loop that continues until goal is reached.
    * checks if the present node is start node. 
    */
    do
    {
        /*
        * Loops through the list of positions explored
        * Gets a deep copy of the path
        */
        for (int i = 0; i < copyNodesExplored->getLength(); i++)
        {
            // creates a next position node that gets any position
            // from positions explored.
            Node *surroundingNode = copyNodesExplored->getNode(i);
            // compares distances of next position and current position.
            // subtracts 1 from distance traveled.
            bool checkNodesDist = surroundingNode->getDistanceTraveled() 
                                  == presentNode->getDistanceTraveled() - 1;

            /*
            * Checks directions North, South, East, West respectfully.
            * For north, subtract 1 from current row position.
            * For south, add 1 to current row position.
            * For east, add 1 to current col position.
            * For west, subtract 1 from current col position.
            * Add new position to goal path.
            * current position = new position.
            */
            if (surroundingNode->getRow() == presentNode->getRow() - 1 
                && surroundingNode->getCol() == presentNode->getCol())
            {
                if (checkNodesDist)
                {
                    getToGoal->addElement(surroundingNode);
                    presentNode = surroundingNode;
                }
            }

            // South
            if (surroundingNode->getRow() == presentNode->getRow() + 1 
                && surroundingNode->getCol() == presentNode->getCol())
            {
                if (checkNodesDist)
                {
                    getToGoal->addElement(surroundingNode);
                    presentNode = surroundingNode;
                }
            }

            // East
            if (surroundingNode->getRow() == presentNode->getRow() 
                && surroundingNode->getCol() == presentNode->getCol() + 1)
            {
                if (checkNodesDist)
                {
                    getToGoal->addElement(surroundingNode);
                    presentNode = surroundingNode;
                }
            }

            // West
            if (surroundingNode->getRow() == presentNode->getRow() 
                && surroundingNode->getCol() == presentNode->getCol() - 1)
            {
                if (checkNodesDist)
                {
                    getToGoal->addElement(surroundingNode);
                    presentNode = surroundingNode;
                }
            }
        }
    } while (!presentNode->equals(startNode));

    // reverse the array to go from start to finish.
    NodeList *reversePath = new NodeList(); 
    for (int i = 0; i < getToGoal->getLength(); i++)
    {
        reversePath->addElement(getToGoal->getNode(getToGoal->getLength() - 1 - i));
    }

    return reversePath;
}

