#include "pch.h"
#include "CGameLogic.h"
#include <algorithm>
#include <queue>
#include <vector>
#include <random>
#include <ctime>

CGameLogic::CGameLogic() { m_nVexNum = 0; }
CGameLogic::~CGameLogic() {}

void CGameLogic::InitMap(int anMap[MAX_ROW][MAX_COL]) {
    int total = MAX_ROW * MAX_COL;
    int pairCount = total / 2;
    std::vector<int> pool;
    for (int i = 0; i < pairCount; ++i) {
        int img = i % IMAGE_TYPE_NUM;
        pool.push_back(img);
        pool.push_back(img);
    }
    std::mt19937 rng((unsigned int)time(nullptr));
    std::shuffle(pool.begin(), pool.end(), rng);
    int idx = 0;
    for (int i = 0; i < MAX_ROW; ++i)
        for (int j = 0; j < MAX_COL; ++j)
            anMap[i][j] = pool[idx++];
}

void CGameLogic::Clear(int anMap[MAX_ROW][MAX_COL], Vertex v1, Vertex v2) {
    anMap[v1.row][v1.col] = BLANK;
    anMap[v2.row][v2.col] = BLANK;
}

int CGameLogic::GetVexPath(Vertex avPath[4]) const {
    if (avPath != nullptr && m_nVexNum > 0) {
        for (int i = 0; i < m_nVexNum && i < 4; ++i) avPath[i] = m_avPath[i];
    }
    return m_nVexNum;
}

int CGameLogic::ConvertCoordToIndex(int row, int col) const {
    return row * MAX_COL + col;
}
void CGameLogic::ConvertIndexToCoord(int idx, int& row, int& col) const {
    row = idx / MAX_COL;
    col = idx % MAX_COL;
}

bool CGameLogic::BFS(const CGraph& graph, int startIdx, int endIdx, std::vector<int>& parent, std::vector<int>& corners) {
    std::queue<int> q;
    std::vector<bool> visited(MAX_VERTEX_NUM, false);
    q.push(startIdx);
    visited[startIdx] = true;
    parent[startIdx] = -1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == endIdx) return true;
        for (int v = 0; v < graph.GetVexNum(); v++) {
            if (graph.IsAdjacent(u, v) && !visited[v]) {
                int vertexVal = graph.GetVertex(v);
                if (vertexVal == BLANK || v == endIdx) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

int CountCorners(const std::vector<int>& path) {
    if (path.size() <= 2) return 0;
    int cornerCount = 0;
    for (size_t i = 1; i < path.size() - 1; i++) {
        int prevIdx = path[i - 1];
        int currIdx = path[i];
        int nextIdx = path[i + 1];
        int prevRow = prevIdx / MAX_COL, prevCol = prevIdx % MAX_COL;
        int currRow = currIdx / MAX_COL, currCol = currIdx % MAX_COL;
        int nextRow = nextIdx / MAX_COL, nextCol = nextIdx % MAX_COL;
        bool prevHorizontal = (prevRow == currRow);
        bool nextHorizontal = (currRow == nextRow);
        if (prevHorizontal != nextHorizontal) cornerCount++;
    }
    return cornerCount;
}

bool CGameLogic::ReconstructPath(int startIdx, int endIdx, const std::vector<int>& parent, const std::vector<int>& corners) {
    m_nVexNum = 0;
    std::vector<int> path;
    int curr = endIdx;
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    std::reverse(path.begin(), path.end());
    int actualCorners = CountCorners(path);
    if (actualCorners > 2) return false;
    if (path.size() > 0) {
        int idx = path[0], row, col;
        ConvertIndexToCoord(idx, row, col);
        m_avPath[m_nVexNum++] = { row, col, 0 };
        for (size_t i = 1; i < path.size() - 1 && m_nVexNum < 4; i++) {
            int prevIdx = path[i - 1], currIdx = path[i], nextIdx = path[i + 1];
            int prevRow = prevIdx / MAX_COL, prevCol = prevIdx % MAX_COL;
            int currRow = currIdx / MAX_COL, currCol = currIdx % MAX_COL;
            int nextRow = nextIdx / MAX_COL, nextCol = nextIdx % MAX_COL;
            bool prevHorizontal = (prevRow == currRow);
            bool nextHorizontal = (currRow == nextRow);
            if (prevHorizontal != nextHorizontal) {
                m_avPath[m_nVexNum++] = { currRow, currCol, 0 };
            }
        }
        if (m_nVexNum < 4) {
            idx = path[path.size() - 1];
            ConvertIndexToCoord(idx, row, col);
            m_avPath[m_nVexNum++] = { row, col, 0 };
        }
    }
    return true;
}

bool CGameLogic::IsLink(const CGraph& graph, Vertex v1, Vertex v2) {
    m_nVexNum = 0;
    if (v1.row == v2.row && v1.col == v2.col) return false;
    if (v1.row < 0 || v1.row >= MAX_ROW || v1.col < 0 || v1.col >= MAX_COL) return false;
    if (v2.row < 0 || v2.row >= MAX_ROW || v2.col < 0 || v2.col >= MAX_COL) return false;
    int val1 = graph.GetVertex(ConvertCoordToIndex(v1.row, v1.col));
    int val2 = graph.GetVertex(ConvertCoordToIndex(v2.row, v2.col));
    if (val1 == BLANK || val2 == BLANK || val1 != val2) return false;
    int startIdx = ConvertCoordToIndex(v1.row, v1.col);
    int endIdx = ConvertCoordToIndex(v2.row, v2.col);
    std::vector<int> parent(MAX_VERTEX_NUM, -1);
    std::vector<int> corners(MAX_VERTEX_NUM, 0);
    if (BFS(graph, startIdx, endIdx, parent, corners)) {
        if (ReconstructPath(startIdx, endIdx, parent, corners)) return true;
    }
    return false;
}

bool CGameLogic::IsBlank(const CGraph& graph) {
    for (int i = 0; i < graph.GetVexNum(); ++i) {
        if (graph.GetVertex(i) != BLANK)
            return false;
    }
    return true;
}

void CGameLogic::ResetGraph(int anMap[MAX_ROW][MAX_COL]) {
    std::mt19937 rng((unsigned int)time(nullptr));
    for (int k = 0; k < 100; ++k) {
        int r1 = rng() % MAX_ROW, c1 = rng() % MAX_COL;
        int r2 = rng() % MAX_ROW, c2 = rng() % MAX_COL;
        std::swap(anMap[r1][c1], anMap[r2][c2]);
    }
}

bool CGameLogic::SearchValidPath(const CGraph& graph, Vertex& out1, Vertex& out2) {
    for (int r1 = 0; r1 < MAX_ROW; ++r1) {
        for (int c1 = 0; c1 < MAX_COL; ++c1) {
            int idx1 = r1 * MAX_COL + c1;
            int val1 = graph.GetVertex(idx1);
            if (val1 == BLANK) continue;
            for (int r2 = r1; r2 < MAX_ROW; ++r2) {
                for (int c2 = (r2 == r1 ? c1 + 1 : 0); c2 < MAX_COL; ++c2) {
                    int idx2 = r2 * MAX_COL + c2;
                    int val2 = graph.GetVertex(idx2);
                    if (val2 == BLANK || val1 != val2) continue;
                    Vertex v1{ r1, c1, 0 }, v2{ r2, c2, 0 };
                    if (IsLink(graph, v1, v2)) {
                        out1 = v1;
                        out2 = v2;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}