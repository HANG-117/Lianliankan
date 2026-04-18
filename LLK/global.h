#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

typedef struct tagVertex
{
	int row;
    int col;
	int info;
}Vertex;

// global.h
#define MAX_ROW 10
#define MAX_COL 10
#define MAX_VERTEX_NUM (MAX_ROW * MAX_COL)
#define BLANK -1

#define IMAGE_TYPE_NUM 10  
// global.h 底部添加

#define RANK_FILE "rank.dat"
#define MAX_RANK_COUNT 5

// 读取排行榜
inline std::vector<int> LoadRank() {
    std::vector<int> scores;
    std::ifstream ifs(RANK_FILE, std::ios::binary);
    int score;
    while (ifs.read((char*)&score, sizeof(int))) {
        scores.push_back(score);
    }
    ifs.close();
    return scores;
}

// 保存成绩
inline void SaveToRank(int newScore) {
    std::vector<int> scores = LoadRank();
    scores.push_back(newScore);
    // 按时间从大到小排序（剩余时间越多越好）
    std::sort(scores.begin(), scores.end(), std::greater<int>());
    // 只保留前5名
    if (scores.size() > MAX_RANK_COUNT) scores.resize(MAX_RANK_COUNT);

    std::ofstream ofs(RANK_FILE, std::ios::binary | std::ios::trunc);
    for (int s : scores) {
        ofs.write((char*)&s, sizeof(int));
    }
    ofs.close();
}