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
	CRect m_rtGameRect;  // 游戏区域矩形
	CGameControl m_GameControl;

	// 保存位图对象为成员，保证生命周期
	CBitmap m_bmpBG;
	CBitmap m_bmpMem;
	CBitmap m_bmpElement;
	CBitmap m_bmpMask;

	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);
	// 修改：接受任意点数组及点数
	void DrawTipLine(Vertex* vertexs, int nCount);
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