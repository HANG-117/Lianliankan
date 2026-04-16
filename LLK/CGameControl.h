#pragma once
#include "global.h"
#include "CGameLogic.h"
class CGameControl
{
	private:
		int m_anMap[MAX_ROW][MAX_COL];
		CGameLogic gameLogic;
		Vertex m_ptSelFirst;
		Vertex m_ptSelSecond;

	public :
		CGameControl();
		~CGameControl();
		void StartGame();
		int GetElement(int nRow, int nCol);
		void SetFirstPoint(int nRow, int nCol);
		void SetSecPoint(int nRow, int nCol);
		bool Link();
		void Clear();
		Vertex* GetPoints();
};

