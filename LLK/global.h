#pragma once
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