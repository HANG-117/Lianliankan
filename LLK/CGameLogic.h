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
    int ConvertCoordToIndex(int row, int col) const;
    void ConvertIndexToCoord(int idx, int& row, int& col) const;
    bool IsStraight(const CGraph& graph, Vertex v1, Vertex v2);
    bool Is1Corner(const CGraph& graph, Vertex v1, Vertex v2);
    bool Is2Corner(const CGraph& graph, Vertex v1, Vertex v2);
};