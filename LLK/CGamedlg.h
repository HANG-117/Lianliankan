#pragma once
#include "afxdialogex.h"
#include "global.h"
#include "CGameControl.h"
// CGamedlg 对话框

class CGamedlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGamedlg)

public:
	CGamedlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGamedlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	void InitElement(void);
	void InitBackground();
	CDC m_dcMem;
	CDC m_dcElement;
	CDC m_dcMask;
	CDC m_dcBG;  
	CRect m_rtGameRect;  // 添加在类的 private 部分，用于存储游戏区域矩形
	CGameControl m_GameControl;

	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex Vertexs[2]);
	CPoint m_ptGameTop;
	CSize m_sizeElem;
	bool m_bFirstPoint;
	
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClickedBtnStart();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnIdea();
	afx_msg void OnBnClickedBtnRestart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
