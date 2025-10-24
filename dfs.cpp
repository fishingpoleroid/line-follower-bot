#include <bits/stdc++.h>
using namespace std;

#define ROW 10
#define COL 10

typedef pair<int, int> Pair;


struct Node {
    int gridX, gridY;
    int distance;
    bool walkable;
    Node *parent;

    Node() {
        walkable = false;
        gridX = 0;
        gridY = 0;
        distance = INT_MAX;
        parent = nullptr;
    }

    Node (bool _walkable, int _gridX, int _gridY) {
        walkable = _walkable;
        gridX = _gridX;
        gridY = _gridY;
        distance = INT_MAX;
        parent = nullptr;
    }
};


class Grid {
public:
    Node grid[ROW][COL];
    int size;

    Grid (int _grid[ROW][COL]) {
        size = ROW * COL;
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
        vector<Node*> neighbours;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                int row = node->gridX + i;
                int col = node->gridY + j;
                Node* neighbour = GetNode(row, col);
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

    void RetracePath(Pair startPos, Pair endPos) {
        Node *startNode = grid->GetNode(startPos.first, startPos.second);
        Node *targetNode = grid->GetNode(endPos.first, endPos.second);
        
        if (targetNode == nullptr || targetNode->distance == INT_MAX) {
            cout << "Failed to find a path." << endl;
            return;
        }

        stack<Node *> path;
        Node *currentNode = targetNode;
        while (currentNode != startNode) {
            path.push(currentNode);
            currentNode = currentNode->parent;
        }
        path.push(startNode); 

        cout << "Path: " << endl;
        int totalCost = 0;
        Node* prevNode = path.top(); 
        path.pop();
        cout << "-> (" << prevNode->gridX << ", " << prevNode->gridY << ") ";

        while (!path.empty()) {
            Node *p = path.top();
            path.pop();
            cout << "-> (" << p->gridX << ", " << p->gridY << ") ";
            
            totalCost += GetDistance(prevNode, p);
            prevNode = p; 
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

    void dfs(Pair startPos) {
        Node* startNode = grid->GetNode(startPos.first, startPos.second);
        
        if (startNode == nullptr || !startNode->walkable) {
            return;
        }

        stack<Node*> nodeStack;
        unordered_set<Node*> visited;

        startNode->distance = 0;
        startNode->parent = startNode;
        
        nodeStack.push(startNode);
        visited.insert(startNode);

        while (!nodeStack.empty()) {
            Node* currentNode = nodeStack.top();
            nodeStack.pop();

            for (Node* neighbour : grid->GetNeighbours(currentNode)) {
                if (neighbour->walkable && visited.count(neighbour) == 0) {
                    
                    visited.insert(neighbour); 
                    
                    neighbour->distance = currentNode->distance + 1;
                    neighbour->parent = currentNode;
                    
                    nodeStack.push(neighbour);
                }
            }
        }
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

    pathfinder.dfs(src);
    
    pathfinder.RetracePath(src, dest);

    return 0;
}