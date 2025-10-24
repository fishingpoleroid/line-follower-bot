#include <bits/stdc++.h>
using namespace std;

#define ROW 10
#define COL 10

typedef pair<int, int> Pair;


struct Node {
    int gridX, gridY;
    int gCost, hCost;
    bool walkable;
    Node *parent;

    Node() {
        walkable = false;
        gridX = 0;
        gridY = 0;
        gCost = INT_MAX;
        hCost = 0;
        parent = nullptr;
    }

    Node (bool _walkable, int _gridX, int _gridY) {
        walkable = _walkable;
        gridX = _gridX;
        gridY = _gridY;
        gCost = INT_MAX;
        hCost = 0;
        parent = nullptr;
    }

    int getFCost() {
        return gCost + hCost;
    }
};


class Grid {
public:
    Node grid[ROW][COL];

    Grid (int _grid[ROW][COL]) {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                grid[i][j] = Node(_grid[i][j] == 1, i, j);
            }
        }
    }

    Node *GetNode(int row, int col) {
        if (row >= 0 && row < ROW && col >= 0 && col < COL) {
            return &grid[row][col];
        }
        return nullptr;
    }

    vector<Node*> GetNeighbours(Node *node) {
        vector<Node *> neighbours;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                int row = node->gridX + i;
                int col = node->gridY + j;

                Node *neighbour = GetNode(row, col);
                if (neighbour != nullptr) {
                    neighbours.push_back(neighbour);
                }
            }
        }
        return neighbours;
    }
};


class Pathfinding {
public:
    Grid *grid;

    Pathfinding(Grid *_grid) {
        this->grid = _grid;
    }

    void RetracePath(Node *startNode, Node *endNode) {
        stack<Node *> path;
        Node *currentNode = endNode;

        while (currentNode != startNode) {
            path.push(currentNode);
            currentNode = currentNode->parent;
        }
        path.push(startNode);

        cout << "Path: " << endl;

        while (!path.empty()) {
            Node *p = path.top();
            path.pop();
            cout << "-> (" << p->gridX << ", " << p->gridY << ") ";
        }
        cout << endl;
    }

    int GetDistance(Node *nodeA, Node *nodeB) {
        int distX = abs(nodeA->gridX - nodeB->gridX);
        int distY = abs(nodeA->gridY - nodeB->gridY);

        if (distX > distY) {
            return 14 * distY + 10 * (distX - distY);
        }
        return 14 * distX + 10 * (distY - distX);
    }

    void FindPath(Pair startPos, Pair endPos) {
        Node *startNode = grid->GetNode(startPos.first, startPos.second);
        Node *targetNode = grid->GetNode(endPos.first, endPos.second);

        vector<Node *> openSet;
        unordered_set<Node *> closedSet;

        openSet.push_back(startNode);
        startNode->gCost = 0;
        startNode->hCost = GetDistance(startNode, targetNode);
        startNode->parent = startNode;

        while (!openSet.empty()) {
            Node *currentNode = openSet[0];
            int currentNodeIndex = 0;

            for (int i = 0; i < openSet.size(); i++) {
                if (openSet[i]->getFCost() < currentNode->getFCost() || 
                (openSet[i]->getFCost() == currentNode->getFCost() && openSet[i]->hCost < currentNode->hCost)) {
                    currentNode = openSet[i];
                    currentNodeIndex = i;        
                }
            }
            openSet.erase(openSet.begin() + currentNodeIndex);
            closedSet.insert(currentNode);

            if (currentNode == targetNode) {
                RetracePath(startNode, targetNode);
                return;
            }

            for (Node *neighbour : grid->GetNeighbours(currentNode)) {
                if (!neighbour->walkable || closedSet.count(neighbour)) {
                    continue;
                }

                int moveCost = GetDistance(currentNode, neighbour);
                int newMovementCostToNeighbour = currentNode->gCost + moveCost;

                bool inOpenSet = false;
                for (const auto &node : openSet) {
                    if (node == neighbour) {
                        inOpenSet = true;
                        break;
                    }
                }

                if (newMovementCostToNeighbour < neighbour->gCost || !inOpenSet) {
                    neighbour->gCost = newMovementCostToNeighbour;
                    neighbour->hCost = GetDistance(neighbour, targetNode);
                    neighbour->parent = currentNode;

                    if (!inOpenSet) {
                        openSet.push_back(neighbour);
                    }
                }
            }
        }
        cout << "Failed to find a path." << endl;
    }
};


int main() {
    int simpleGrid[ROW][COL] = {{1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                                {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
                                {1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
                                {1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
                                {1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
                                {1, 0, 0, 0, 1, 1, 1, 0, 1, 0},
                                {1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
                                {1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
                                {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 0, 1, 0, 1}};

    Grid grid(simpleGrid);
    Pathfinding pathfinder(&grid);

    Pair src = make_pair(9, 0);
    Pair dest = make_pair(0, 9);

    pathfinder.FindPath(src, dest);

    return 0;
}