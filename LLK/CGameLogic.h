#pragma once
#include "global.h"
#include "CGraph.h"
#include <queue>
#include <vector>

class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();

	void InitMap(int anMap[MAX_ROW][MAX_COL]);
	// 判断是否可以连通（基于图结构，使用 BFS，最多 3 段直线）
	bool IsLink(const CGraph& graph, Vertex v1, Vertex v2);
	void Clear(int anMap[MAX_ROW][MAX_COL], Vertex v1, Vertex v2);

	// 教程风格接口：拷贝路径到传入数组并返回顶点数
	int GetVexPath(Vertex avPath[4]) const;

	// 向后兼容：返回路径计数与路径指针（只读）
	int GetPathCount() const { return m_nVexNum; }
	const Vertex* GetPath() const { return m_avPath; }

private:
	// 保存关键顶点（最多起点 + 两拐点 + 终点 = 4）
	Vertex m_avPath[4];
	int m_nVexNum;

	// BFS 辅助函数
	bool BFS(const CGraph& graph, int startIdx, int endIdx, std::vector<int>& parent, std::vector<int>& corners);
	// 修改返回类型为 bool
	bool ReconstructPath(int startIdx, int endIdx, const std::vector<int>& parent, const std::vector<int>& corners);
	int ConvertCoordToIndex(int row, int col) const;
	void ConvertIndexToCoord(int idx, int& row, int& col) const;
};