#include "leveldata.hpp"

const LevelGraph& GetLevelGraph()
{
    static LevelGraph levelGraph;

    LevelNode node1;
    node1.id = "Node1";
    node1.levelData = {
        "00000010000000000",
        "00000000000000001",
        "00000000000000001",
        "00000000000010001",
        "00000000000010001",
        "00000000000010001",
        "00000000000010001",
        "00000000100000001",
        "00000000100000001",
        "10000000000000001",
        "00000000000000000",
        "00000000000000000",
        "11111111111111111"
    };
    node1.connectedNodes = {"","Node2","",""}; //up,right,down,left

    LevelNode node2;
    node2.id = "Node2";
    node2.levelData = {
        "11111111100000011",
        "11000000000000000",
        "11000000000000000",
        "11000000000000000",
        "11000000011000011",
        "11000000000000010",
        "11000110000000010",
        "11000000000000010",
        "11000000011000010",
        "10000011000000010",
        "00000000000000010",
        "00000000000000000",
        "11111111111111111"
    };
    node2.connectedNodes = {"", "", "", "Node1"};//up, right, down, left

    levelGraph.AddNode(node1);
    levelGraph.AddNode(node2);

    return levelGraph;
}

const std::vector<std::string> getLevelData(const std::string& nodeId)
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
    
    // If the node with the specified id is found return its level data
    if (nodeIndex != -1)
    {
        const LevelNode& node = levelGraph.GetNode(nodeIndex);
        return node.levelData;
    }
    
    // Return an empty vector if the node with the specified id is not found
    return std::vector<std::string>();
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
