#include "pch.h"
#include "CGameControl.h"

CGameControl::CGameControl() {
    for (int r = 0; r < MAX_ROW; ++r)
        for (int c = 0; c < MAX_COL; ++c)
            m_anMap[r][c] = BLANK;
}

CGameControl::~CGameControl() {}

void CGameControl::StartGame() {
    gameLogic.InitMap(m_anMap);
    m_graph.InitGraph(m_anMap);
}

int CGameControl::GetElement(int nRow, int nCol) {
    return m_anMap[nRow][nCol];
}

void CGameControl::SetFirstPoint(int nRow, int nCol) {
    m_ptSelFirst.row = nRow;
    m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol) {
    m_ptSelSecond.row = nRow;
    m_ptSelSecond.col = nCol;
}

bool CGameControl::Link() {
    return gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSecond);
}

Vertex* CGameControl::GetPoints(int& nCount) {
    int cnt = gameLogic.GetPathCount();
    const Vertex* p = gameLogic.GetPath();
    nCount = cnt;
    if (cnt <= 0) return nullptr;
    Vertex* arr = new Vertex[cnt];
    for (int i = 0; i < cnt; ++i) arr[i] = p[i];
    return arr;
}

void CGameControl::Clear() {
    gameLogic.Clear(m_anMap, m_ptSelFirst, m_ptSelSecond);
    m_graph.InitGraph(m_anMap);
}

bool CGameControl::IsWin() {
    return gameLogic.IsBlank(m_graph);
}

void CGameControl::Reset() {
    gameLogic.ResetGraph(m_anMap);
    m_graph.InitGraph(m_anMap);
}

bool CGameControl::Help(Vertex& out1, Vertex& out2) {
    if (gameLogic.IsBlank(m_graph)) return false;
    return gameLogic.SearchValidPath(m_graph, out1, out2);
}