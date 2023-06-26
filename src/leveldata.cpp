#include "leveldata.hpp"

void LevelGraph::AddNode(const LevelNode& node)
{
    nodes.push_back(node);
}

const LevelNode& LevelGraph::GetNode(int index) const
{
    return nodes.at(index);
}

int LevelGraph::GetNodeCount() const
{
    return nodes.size();
}

const LevelGraph& GetLevelGraph()
{
    static LevelGraph levelGraph;

    LevelNode node1;
    node1.id = "Node1";
    node1.levelData = {
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    node1.connectedNodes = {"", "Node2", "", ""}; // up, right, down, left
    node1.width = node1.levelData[0].size();
    node1.height = node1.levelData.size();

    LevelNode node2;
    node2.id = "Node2";
    node2.levelData = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0, 0, 1, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    node2.connectedNodes = {"Node3", "", "", "Node1"}; // up, right, down, left
    node2.width = node2.levelData[0].size();
    node2.height = node2.levelData.size();


    LevelNode node3;
    node3.id = "Node3";
    node3.levelData = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 2, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1}
    };
    node3.connectedNodes = {"", "", "Node2", ""}; // up, right, down, left
    node3.width = node3.levelData[0].size();
    node3.height = node3.levelData.size();

    levelGraph.AddNode(node1);
    levelGraph.AddNode(node2);
    levelGraph.AddNode(node3);

    return levelGraph;
}

//use 2 for exit direction up so they will spawn at bottom of window
// 3 for exit direction right so they will spawn at left of window
// 4 for exit direction left so they will spawn at right of window
//5 for exit direction down so they will spawn at top of window


const std::vector<std::vector<int>> getLevelData(const std::string& nodeId)
{
    const LevelGraph& levelGraph = GetLevelGraph();
    int nodeIndex = -1;

    // Find the index of the node with the specified id
    for (int i = 0; i < levelGraph.GetNodeCount(); ++i)
    {
        const LevelNode& node = levelGraph.GetNode(i);
        if (node.id == nodeId)
        {
            nodeIndex = i;
            break;
        }
    }

    // If the node with the specified id is found, convert the levelData from string to vector<vector<int>>
    if (nodeIndex != -1)
    {
        const LevelNode& node = levelGraph.GetNode(nodeIndex);
        std::vector<std::vector<int>> levelData;

        // Convert each string row to vector<int> row
        for (const std::vector<int>& row : node.levelData) // Update this line
        {
            levelData.push_back(row);
        }

        return levelData;
    }

    // Return an empty vector if the node with the specified id is not found
    return std::vector<std::vector<int>>();
}



std::string getNextNode(const std::string& currentNodeId, const std::string& exitDirection)
{
    const LevelGraph& levelGraph = GetLevelGraph();
    int nodeIndex = -1;

    // Find the index of the current node
    for (int i = 0; i < levelGraph.GetNodeCount(); ++i)
    {
        const LevelNode& node = levelGraph.GetNode(i);
        if (node.id == currentNodeId)
        {
            nodeIndex = i;
            break;
        }
    }

    // If the current node is found retrieve the connected nodes and determine the next node based on the exit direction
    if (nodeIndex != -1)
    {
        const LevelNode& currentNode = levelGraph.GetNode(nodeIndex);
        const std::vector<std::string>& connections = currentNode.connectedNodes;

        if (exitDirection == "up" && !connections.empty())
        {
            return connections[0]; // Up connection
        }
        else if (exitDirection == "right" && !connections.empty())
        {
            return connections[1]; // Right connection
        }
        else if (exitDirection == "down" && !connections.empty())
        {
            return connections[2]; // Down connection
        }
        else if (exitDirection == "left" && !connections.empty())
        {
            return connections[3]; // Left connection
        }
    }

    // If no connection in the given exit direction or the current node is not found return an empty string
    return "";
}
