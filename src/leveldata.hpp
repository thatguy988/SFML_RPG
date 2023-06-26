#ifndef LEVELDATA_HPP
#define LEVELDATA_HPP

#include <vector>
#include <string>

struct LevelNode
{
    std::string id;
    std::vector<std::vector<int>> levelData; 
    std::vector<std::string> connectedNodes;
    int width; // Width of the level used for view stay in boundaries
    int height; // Height of the level used for view stay in boundaries
};

class LevelGraph
{
private:
    std::vector<LevelNode> nodes;

public:
    void AddNode(const LevelNode& node);
    const LevelNode& GetNode(int index) const;
    int GetNodeCount() const;
};

const LevelGraph& GetLevelGraph();
const std::vector<std::vector<int>> getLevelData(const std::string& nodeId);

std::string getNextNode(const std::string& currentNodeId, const std::string& exitDirection);

#endif // LEVELDATA_HPP
