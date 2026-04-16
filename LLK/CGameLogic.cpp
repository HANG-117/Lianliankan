#include "pch.h"
#include "CGameLogic.h"
#include "global.h"
CGameLogic::CGameLogic() {

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

bool CGameLogic::IsLink(int anMap[MAX_ROW][MAX_COL], Vertex v1, Vertex v2) {
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
    int nCol2 = v2.col;
	if (nRow1 == nRow2 && nCol1 == nCol2) {
		return false;
	}

	// 2. 检查两个方块的图案是否相同 (注意数组索引是 [y][x])
	if (anMap[nRow1][nCol1] == anMap[nRow2][nCol2]) {
		// 3. 检查该位置是否已经被消除了（假设 -1 代表空地，避免点击空白处也能消除）
		if (anMap[nRow1][nCol1] == -1 || anMap[nRow2][nCol2] == -1){
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}

void CGameLogic::Clear(int anMap[MAX_ROW][MAX_COL], Vertex v1, Vertex v2) {
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}