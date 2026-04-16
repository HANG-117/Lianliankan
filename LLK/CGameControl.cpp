#include "pch.h"
#include "CGameControl.h"
#include "CGameLogic.h"
CGameControl::CGameControl() {

}
CGameControl::~CGameControl() {
}
void CGameControl::StartGame() {
    gameLogic.InitMap(m_anMap);

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
    return gameLogic.IsLink(m_anMap, m_ptSelFirst, m_ptSelSecond);
}

Vertex* CGameControl::GetPoints() {
    Vertex * pVertex = new Vertex[2];
    pVertex[0] = m_ptSelFirst;
    pVertex[1] = m_ptSelSecond;
    return pVertex;
}

void CGameControl::Clear() {
    gameLogic.Clear(m_anMap,m_ptSelFirst, m_ptSelSecond);
}