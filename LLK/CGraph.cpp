#include "pch.h"
#include "CGraph.h"

CGraph::CGraph() {
    m_nVexnum = 0;
    m_nArcnum = 0;
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        m_Vertices[i] = -1;
        for (int j = 0; j < MAX_VERTEX_NUM; j++) {
            m_AdjMatrix[i][j] = false;
        }
    }
}
CGraph::~CGraph() {}

void CGraph::InitGraph(int anMap[MAX_ROW][MAX_COL]) {
    m_nVexnum = MAX_ROW * MAX_COL;
    m_nArcnum = 0;
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        m_Vertices[i] = anMap[i / MAX_COL][i % MAX_COL];
        for (int j = 0; j < MAX_VERTEX_NUM; j++) {
            m_AdjMatrix[i][j] = false;
        }
    }
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        int i_row = i / MAX_COL, i_col = i % MAX_COL;
        for (int d = 0; d < 4; ++d) {
            int dr[4] = { -1, 1, 0, 0 }, dc[4] = { 0, 0, -1, 1 };
            int nr = i_row + dr[d], nc = i_col + dc[d];
            if (nr >= 0 && nr < MAX_ROW && nc >= 0 && nc < MAX_COL) {
                int j = nr * MAX_COL + nc;
                int val_i = m_Vertices[i], val_j = m_Vertices[j];
                if (val_i == val_j || val_i == BLANK || val_j == BLANK) {
                    m_AdjMatrix[i][j] = true;
                    m_nArcnum++;
                }
            }
        }
    }
}

int CGraph::GetVertex(int index) const {
    if (index >= 0 && index < m_nVexnum) return m_Vertices[index];
    return -1;
}
bool CGraph::IsAdjacent(int v1, int v2) const {
    if (v1 >= 0 && v1 < m_nVexnum && v2 >= 0 && v2 < m_nVexnum)
        return m_AdjMatrix[v1][v2];
    return false;
}