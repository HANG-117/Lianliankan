#pragma once
#include "global.h"
class CGameLogic
{
	public:
        CGameLogic();
		~CGameLogic();
		void InitMap(int anMap[MAX_ROW][MAX_COL]);
		bool IsLink(int anMap[MAX_ROW][MAX_COL],Vertex v1,Vertex v2);
		void Clear(int anMap[MAX_ROW][MAX_COL],Vertex v1,Vertex v2);
};

