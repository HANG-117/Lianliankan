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
// 0拐角：判断两点是否在同一直线且中间畅通
bool CGameLogic::IsStraight(const CGraph& graph, Vertex v1, Vertex v2){
    if (v1.row != v2.row && v1.col != v2.col) return false;

    if (v1.row == v2.row) {
        int step = (v1.col < v2.col) ? 1 : -1;
        for (int c = v1.col + step; c != v2.col; c += step) {
            if (graph.GetVertex(ConvertCoordToIndex(v1.row, c)) != BLANK) return false;
        }
    }
    else {
        int step = (v1.row < v2.row) ? 1 : -1;
        for (int r = v1.row + step; r != v2.row; r += step) {
            if (graph.GetVertex(ConvertCoordToIndex(r, v1.col)) != BLANK) return false;
        }
    }
    return true;
}

// 1拐角：利用矩形的对角特性检查两个交点
bool CGameLogic::Is1Corner(const CGraph& graph, Vertex v1, Vertex v2) {
    // 检查交点 1: (v1.row, v2.col)
    if (graph.GetVertex(ConvertCoordToIndex(v1.row, v2.col)) == BLANK) {
        Vertex p = { v1.row, v2.col, 0 };
        if (IsStraight(graph, v1, p) && IsStraight(graph, p, v2)) {
            // 成功，直接把三点连线写入数组
            m_avPath[0] = v1;
            m_avPath[1] = p;
            m_avPath[2] = v2;
            m_nVexNum = 3;
            return true;
        }
    }
    // 检查交点 2: (v2.row, v1.col)
    if (graph.GetVertex(ConvertCoordToIndex(v2.row, v1.col)) == BLANK) {
        Vertex p = { v2.row, v1.col, 0 };
        if (IsStraight(graph, v1, p) && IsStraight(graph, p, v2)) {
            // 成功，直接把三点连线写入数组
            m_avPath[0] = v1;
            m_avPath[1] = p;
            m_avPath[2] = v2;
            m_nVexNum = 3;
            return true;
        }
    }
    return false; // 失败时不会碰 m_avPath
}

// 2拐角：从起点发散十字射线
bool CGameLogic::Is2Corner(const CGraph& graph, Vertex v1, Vertex v2) {
    // 1. 水平向左右扫描
    for (int dir = -1; dir <= 1; dir += 2) {
        for (int c = v1.col + dir; c >= 0 && c < MAX_COL; c += dir) {
            if (graph.GetVertex(ConvertCoordToIndex(v1.row, c)) != BLANK) break;

            Vertex p = { v1.row, c, 0 };
            // 如果射线上的点 p 能 1折 连到终点 v2，此时 Is1Corner 已经把 [p, 拐角, v2] 写进了前 3 个格子
            if (Is1Corner(graph, p, v2)) {
                // 巧妙移位：把这 3 个点往后挪，把起点 v1 补在最前面
                m_avPath[3] = m_avPath[2];
                m_avPath[2] = m_avPath[1];
                m_avPath[1] = m_avPath[0];
                m_avPath[0] = v1;
                m_nVexNum = 4;
                return true;
            }
        }
    }

    // 2. 垂直向上下扫描
    for (int dir = -1; dir <= 1; dir += 2) {
        for (int r = v1.row + dir; r >= 0 && r < MAX_ROW; r += dir) {
            if (graph.GetVertex(ConvertCoordToIndex(r, v1.col)) != BLANK) break;

            Vertex p = { r, v1.col, 0 };
            if (Is1Corner(graph, p, v2)) {
                m_avPath[3] = m_avPath[2];
                m_avPath[2] = m_avPath[1];
                m_avPath[1] = m_avPath[0];
                m_avPath[0] = v1;
                m_nVexNum = 4;
                return true;
            }
        }
    }
    return false;
}

// 主接口
bool CGameLogic::IsLink(const CGraph& graph, Vertex v1, Vertex v2) {
    m_nVexNum = 0;
    if (v1.row == v2.row && v1.col == v2.col) return false;
    if (v1.row < 0 || v1.row >= MAX_ROW || v1.col < 0 || v1.col >= MAX_COL) return false;
    if (v2.row < 0 || v2.row >= MAX_ROW || v2.col < 0 || v2.col >= MAX_COL) return false;

    int val1 = graph.GetVertex(ConvertCoordToIndex(v1.row, v1.col));
    int val2 = graph.GetVertex(ConvertCoordToIndex(v2.row, v2.col));
    if (val1 == BLANK || val2 == BLANK || val1 != val2) return false;

    // 1. 尝试直连 (0个拐角)
    if (IsStraight(graph, v1, v2)) {
        m_avPath[0] = v1;
        m_avPath[1] = v2;
        m_nVexNum = 2;
        return true;
    }

    // 2. 尝试一个拐角 (内部自动记录路径)
    if (Is1Corner(graph, v1, v2)) return true;

    // 3. 尝试两个拐角 (内部自动记录路径)
    if (Is2Corner(graph, v1, v2)) return true;

    return false;
}