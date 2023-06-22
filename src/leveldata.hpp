#ifndef LEVELDATA_HPP
#define LEVELDATA_HPP

#include <vector>
#include <string>

struct LevelNode
{
    std::string id;
    std::vector<std::string> levelData;
    std::vector<std::string> connectedNodes;
};

class LevelGraph
{
private:
    std::vector<LevelNode> nodes;

public:
    void AddNode(const LevelNode& node)
    {
        nodes.push_back(node);
    }

    const LevelNode& GetNode(int index) const
    {
        return nodes.at(index);
    }

    int GetNodeCount() const
    {
        return nodes.size();
    }
};

const LevelGraph& GetLevelGraph();
const std::vector<std::string> getLevelData(const std::string& nodeId);
std::string getNextNode(const std::string& currentNodeId, const std::string& exitDirection);


#endif // LEVELDATA_HPP

