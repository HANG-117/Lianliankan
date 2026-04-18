#pragma once
#include "afxdialogex.h"
#include "global.h"
#include "CGameControl.h"

class CGamedlg : public CDialogEx
{
    DECLARE_DYNAMIC(CGamedlg)

public:
    CGamedlg(CWnd* pParent = nullptr);
    virtual ~CGamedlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
    void InitElement(void);
    void InitBackground();
    CDC m_dcMem;
    CDC m_dcElement;
    CDC m_dcMask;
    CDC m_dcBG;
    CRect m_rtGameRect;
    CGameControl m_GameControl;

    CBitmap m_bmpBG;
    CBitmap m_bmpMem;
    CBitmap m_bmpElement;
    CBitmap m_bmpMask;

    void UpdateMap();
    void DrawTipFrame(int nRow, int nCol);
    void DrawTipLine(Vertex* vertexs, int nCount);
    void DrawTipFramePair(const Vertex& v1, const Vertex& v2);
    CPoint m_ptGameTop;
    CSize m_sizeElem;
    bool m_bFirstPoint;
    UINT_PTR m_nTimerID = 1;   // 定时器 ID 固定为 1
    int m_nTimeLeft = 600;     // 初始倒计时秒数（可调整）
    bool m_bPaused = false;    // 是否处于暂停
    bool m_bTimerRunning = false; // 定时器是否已启动
    bool m_bPlaying = false;   // 游戏是否在进行

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
    afx_msg void OnBnClickedBtnReset();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnStnClickedStaticTime();
    bool m_bRelaxMode = false;

};