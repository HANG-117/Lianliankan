#pragma once
#include "global.h"
#include "CGameLogic.h"
#include "CGraph.h"

class CGameControl
{
private:
	CGraph m_graph;  // 用图结构替换原来的二维数组
	int m_anMap[MAX_ROW][MAX_COL];  // 保留二维数组用于显示和逻辑判断（暂时并行）
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
	// 返回动态分配的路径数组，并通过引用返回点数，调用者必须 delete[]
	Vertex* GetPoints(int& nCount);

	// 新增：getter 访问选中的点
	Vertex GetFirstPoint() const { return m_ptSelFirst; }
	Vertex GetSecPoint() const { return m_ptSelSecond; }

	// 新增：获取图对象（用于连通判断等）
	const CGraph& GetGraph() const { return m_graph; }
};