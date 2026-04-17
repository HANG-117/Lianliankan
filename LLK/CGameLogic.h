#pragma once
#include "global.h"
#include "CGraph.h"
#include <vector>

class CGameLogic
{
public:
    CGameLogic();
    ~CGameLogic();

    void InitMap(int anMap[MAX_ROW][MAX_COL]);
    bool IsLink(const CGraph& graph, Vertex v1, Vertex v2);
    void Clear(int anMap[MAX_ROW][MAX_COL], Vertex v1, Vertex v2);
    int GetVexPath(Vertex avPath[4]) const;
    int GetPathCount() const { return m_nVexNum; }
    const Vertex* GetPath() const { return m_avPath; }
    bool IsBlank(const CGraph& graph);
    void ResetGraph(int anMap[MAX_ROW][MAX_COL]);
    bool SearchValidPath(const CGraph& graph, Vertex& out1, Vertex& out2);

private:
    Vertex m_avPath[4];
    int m_nVexNum;
    bool BFS(const CGraph& graph, int startIdx, int endIdx, std::vector<int>& parent, std::vector<int>& corners);
    bool ReconstructPath(int startIdx, int endIdx, const std::vector<int>& parent, const std::vector<int>& corners);
    int ConvertCoordToIndex(int row, int col) const;
    void ConvertIndexToCoord(int idx, int& row, int& col) const;
};