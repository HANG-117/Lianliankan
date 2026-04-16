#include "pch.h"
#include "CGraph.h"

CGraph::CGraph() {
	m_nVexnum = 0;
	m_nArcnum = 0;
	// 初始化顶点和邻接矩阵
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertices[i] = -1;  // -1 表示空
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}
}

CGraph::~CGraph() {
}

void CGraph::InitGraph(int anMap[4][4]) {
	// 清空之前的图
	m_nVexnum = 0;
	m_nArcnum = 0;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertices[i] = -1;
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}

	// 步骤1：将地图转换为顶点
	// 地图中的每个格子对应一个顶点，顶点值为地图中的元素值
	int vexIndex = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_Vertices[vexIndex] = anMap[i][j];  // 存储元素值
			vexIndex++;
		}
	}
	m_nVexnum = 16;  // 4x4 = 16 个顶点

	// 步骤2：建立边的关系
	// 规则：两个顶点有边相连当且仅当：
	//   (1) 两个顶点值相同（元素相同）
	//   (2) 至少有一个顶点为空（BLANK = -1）（允许路径经过空位）
	for (int i = 0; i < 16; i++) {
		for (int j = i + 1; j < 16; j++) {
			// 判断顶点 i 和 j 是否应该有边
			// 获取行列坐标
			int i_row = i / 4, i_col = i % 4;
			int j_row = j / 4, j_col = j % 4;

			// 只有相邻的顶点才能有边（上下左右）
			int dist_row = abs(i_row - j_row);
			int dist_col = abs(i_col - j_col);

			// 如果是相邻顶点（上下或左右）
			if ((dist_row + dist_col == 1)) {
				// 有边的条件：
				// (1) 两个顶点都不为空，且值相同
				// (2) 或至少有一个为空（路径可以经过空位）
				int val_i = m_Vertices[i];
				int val_j = m_Vertices[j];

				// 连通的条件：
				// 两点值相同，且路径存在空位或两点都非空
				if (val_i == val_j || val_i == -1 || val_j == -1) {
					m_AdjMatrix[i][j] = true;
					m_AdjMatrix[j][i] = true;  // 无向图
					m_nArcnum++;
				}
			}
		}
	}
}

int CGraph::GetVertex(int index) const {
	if (index >= 0 && index < m_nVexnum) {
		return m_Vertices[index];
	}
	return -1;
}

bool CGraph::IsAdjacent(int v1, int v2) const {
	if (v1 >= 0 && v1 < m_nVexnum && v2 >= 0 && v2 < m_nVexnum) {
		return m_AdjMatrix[v1][v2];
	}
	return false;
}