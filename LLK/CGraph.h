#pragma once
#include "global.h"

typedef int Vertices[MAX_VERTEX_NUM];
typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

class CGraph
{
protected:
    Vertices m_Vertices;
    AdjMatrix m_AdjMatrix;
    int m_nVexnum;
    int m_nArcnum;
public:
    CGraph();
    ~CGraph();
    void InitGraph(int anMap[MAX_ROW][MAX_COL]);
    int GetVertex(int index) const;
    bool IsAdjacent(int v1, int v2) const;
    int GetVexNum() const { return m_nVexnum; }
    int GetArcNum() const { return m_nArcnum; }
};