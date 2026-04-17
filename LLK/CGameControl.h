#pragma once
#include "global.h"
#include "CGameLogic.h"
#include "CGraph.h"

class CGameControl
{
private:
    CGraph m_graph;
    int m_anMap[MAX_ROW][MAX_COL];
    CGameLogic gameLogic;
    Vertex m_ptSelFirst;
    Vertex m_ptSelSecond;

public:
    CGameControl();
    ~CGameControl();
    void StartGame();
    int GetElement(int nRow, int nCol);
    void SetFirstPoint(int nRow, int nCol);
    void SetSecPoint(int nRow, int nCol);
    bool Link();
    void Clear();
    Vertex* GetPoints(int& nCount);
    Vertex GetFirstPoint() const { return m_ptSelFirst; }
    Vertex GetSecPoint() const { return m_ptSelSecond; }
    const CGraph& GetGraph() const { return m_graph; }
    bool IsWin();
    void Reset();
    bool Help(Vertex& out1, Vertex& out2);
};