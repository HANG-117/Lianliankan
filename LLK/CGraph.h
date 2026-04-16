#pragma once

#define MAX_VERTEX_NUM 16  // 最多 16 个顶点（4x4 游戏地图）

typedef int Vertices[MAX_VERTEX_NUM];  // 顶点数据类型（存储元素值）
typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // 邻接矩阵（存储边信息）

class CGraph
{
protected:
	Vertices m_Vertices;  // 顶点数组
	AdjMatrix m_AdjMatrix;  // 邻接矩阵
	int m_nVexnum;  // 顶点数量
	int m_nArcnum;  // 边的数量

public:
	CGraph();
	~CGraph();

	// 初始化图：根据游戏地图初始化顶点和边
	void InitGraph(int anMap[4][4]);

	// 获取顶点值
	int GetVertex(int index) const;

	// 判断两个顶点是否有边连接
	bool IsAdjacent(int v1, int v2) const;

	// 获取顶点数量
	int GetVexNum() const { return m_nVexnum; }

	// 获取边数量
	int GetArcNum() const { return m_nArcnum; }
};