#include "pch.h"
#include "CGameLogic.h"
#include <algorithm>
#include <queue>

CGameLogic::CGameLogic() {
	m_nVexNum = 0;
}

CGameLogic::~CGameLogic() {
}

void CGameLogic::InitMap(int anMap[MAX_ROW][MAX_COL]) {
	int antemp[MAX_ROW][MAX_COL] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			anMap[i][j] = antemp[i][j];
		}
	}
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

// 简化的 BFS：不计算拐点，只搜索路径
// 后续在 ReconstructPath 中验证拐点数是否合法
bool CGameLogic::BFS(const CGraph& graph, int startIdx, int endIdx, std::vector<int>& parent, std::vector<int>& corners) {
	std::queue<int> q;
	std::vector<bool> visited(MAX_VERTEX_NUM, false);

	q.push(startIdx);
	visited[startIdx] = true;
	parent[startIdx] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		if (u == endIdx) {
			return true;
		}

		// 遍历相邻顶点
		for (int v = 0; v < graph.GetVexNum(); v++) {
			if (graph.IsAdjacent(u, v) && !visited[v]) {
				// 关键检查：中间节点必须为空（BLANK = -1），除非是终点
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

// 计算路径中的拐点数
int CountCorners(const std::vector<int>& path) {
	if (path.size() <= 2) return 0;  // 直线（0 个拐点）

	int cornerCount = 0;
	for (size_t i = 1; i < path.size() - 1; i++) {
		int prevIdx = path[i - 1];
		int currIdx = path[i];
		int nextIdx = path[i + 1];

		int prevRow = prevIdx / 4, prevCol = prevIdx % 4;
		int currRow = currIdx / 4, currCol = currIdx % 4;
		int nextRow = nextIdx / 4, nextCol = nextIdx % 4;

		// 前一段方向
		bool prevHorizontal = (prevRow == currRow);
		// 后一段方向
		bool nextHorizontal = (currRow == nextRow);

		// 如果方向改变，则是拐点
		if (prevHorizontal != nextHorizontal) {
			cornerCount++;
		}
	}

	return cornerCount;
}

// 根据父节点数组重构路径，并验证拐点数
bool CGameLogic::ReconstructPath(int startIdx, int endIdx, const std::vector<int>& parent, const std::vector<int>& corners) {
	m_nVexNum = 0;
	std::vector<int> path;

	int curr = endIdx;
	while (curr != -1) {
		path.push_back(curr);
		curr = parent[curr];
	}

	// 反向路径
	std::reverse(path.begin(), path.end());

	// 计算实际拐点数
	int actualCorners = CountCorners(path);

	// 验证：拐点数不能超过 2（即最多 3 段直线）
	if (actualCorners > 2) {
		return false;  // 路径超过 3 段直线，不合法
	}

	// 保存路径的关键点
	if (path.size() > 0) {
		// 保存起点
		{
			int idx = path[0];
			int row, col;
			ConvertIndexToCoord(idx, row, col);
			m_avPath[m_nVexNum].row = row;
			m_avPath[m_nVexNum].col = col;
			m_avPath[m_nVexNum].info = 0;
			m_nVexNum++;
		}

		// 找出并保存所有拐点
		for (size_t i = 1; i < path.size() - 1 && m_nVexNum < 4; i++) {
			int prevIdx = path[i - 1];
			int currIdx = path[i];
			int nextIdx = path[i + 1];

			int prevRow = prevIdx / 4, prevCol = prevIdx % 4;
			int currRow = currIdx / 4, currCol = currIdx % 4;
			int nextRow = nextIdx / 4, nextCol = nextIdx % 4;

			// 前一段方向
			bool prevHorizontal = (prevRow == currRow);
			// 后一段方向
			bool nextHorizontal = (currRow == nextRow);

			// 如果方向改变，则是拐点
			if (prevHorizontal != nextHorizontal) {
				m_avPath[m_nVexNum].row = currRow;
				m_avPath[m_nVexNum].col = currCol;
				m_avPath[m_nVexNum].info = 0;
				m_nVexNum++;
			}
		}

		// 保存终点
		if (m_nVexNum < 4) {
			int idx = path[path.size() - 1];
			int row, col;
			ConvertIndexToCoord(idx, row, col);
			m_avPath[m_nVexNum].row = row;
			m_avPath[m_nVexNum].col = col;
			m_avPath[m_nVexNum].info = 0;
			m_nVexNum++;
		}
	}

	return true;
}

bool CGameLogic::IsLink(const CGraph& graph, Vertex v1, Vertex v2) {
	m_nVexNum = 0;

	// 基本判断
	if (v1.row == v2.row && v1.col == v2.col) return false;
	if (v1.row < 0 || v1.row >= MAX_ROW || v1.col < 0 || v1.col >= MAX_COL) return false;
	if (v2.row < 0 || v2.row >= MAX_ROW || v2.col < 0 || v2.col >= MAX_COL) return false;

	int val1 = graph.GetVertex(ConvertCoordToIndex(v1.row, v1.col));
	int val2 = graph.GetVertex(ConvertCoordToIndex(v2.row, v2.col));

	if (val1 == BLANK || val2 == BLANK || val1 != val2) return false;

	// BFS 搜索
	int startIdx = ConvertCoordToIndex(v1.row, v1.col);
	int endIdx = ConvertCoordToIndex(v2.row, v2.col);
	std::vector<int> parent(MAX_VERTEX_NUM, -1);
	std::vector<int> corners(MAX_VERTEX_NUM, 0);

	if (BFS(graph, startIdx, endIdx, parent, corners)) {
		// 找到路径后，验证拐点数是否合法
		if (ReconstructPath(startIdx, endIdx, parent, corners)) {
			return true;
		}
	}

	return false;
}