// CGamedlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGamedlg.h"
#include "iostream"

// CGamedlg 对话框

IMPLEMENT_DYNAMIC(CGamedlg, CDialogEx)

CGamedlg::CGamedlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	m_bFirstPoint = true;

	m_rtGameRect = CRect(m_ptGameTop.x, m_ptGameTop.y,
		m_ptGameTop.x + 4 * m_sizeElem.cx,
		m_ptGameTop.y + 4 * m_sizeElem.cy);

	
}

CGamedlg::~CGamedlg()
{
}

void CGamedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGamedlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGamedlg::OnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGamedlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_IDEA, &CGamedlg::OnBnClickedBtnIdea)
	ON_BN_CLICKED(IDC_BTN_RESTART, &CGamedlg::OnBnClickedBtnRestart)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CGamedlg 消息处理程序

void CGamedlg::InitBackground()
{
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	CClientDC dc(this);
	m_dcBG.CreateCompatibleDC(&dc);

	// 将位图资源选入DC（此处 hBmpBG 应为已加载的背景位图句柄）
	m_dcBG.SelectObject(hBmpBG);

	// 初始化内存DC（用于离屏绘制）
	m_dcMem.CreateCompatibleDC(&dc);           // 创建与屏幕兼容的内存DC
	CBitmap bmpMem;                            // 声明位图对象
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);  // 创建 800×600 像素的兼容位图
	m_dcMem.SelectObject(&bmpMem);             // 将位图选入内存DC

	// 绘制背景到内存DC中：将 m_dcBG 的内容（背景图）拷贝到 m_dcMem 的 (0,0) 处
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);


}

BOOL CGamedlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitBackground();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGamedlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600,&m_dcMem,0,0,SRCCOPY);
}


void CGamedlg::InitElement() {
	CClientDC dc(this);
	HANDLE hbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


	m_dcElement.CreateCompatibleDC(&dc);

	m_dcElement.SelectObject(hbmp);

	HANDLE hmask = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


	m_dcMask.CreateCompatibleDC(&dc);

	m_dcMask.SelectObject(hmask);


}
void CGamedlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

}

void CGamedlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGamedlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGamedlg::OnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GameControl.StartGame();
	UpdateMap();
	
	InvalidateRect(m_rtGameRect,FALSE);
}	

void CGamedlg::OnBnClickedBtnPause()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGamedlg::OnBnClickedBtnIdea()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGamedlg::OnBnClickedBtnRestart()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CGamedlg::UpdateMap() {
	
	
	int nLeft = 50;
	int nTop = 50;
	int nElemW = 40;
	int nElemH = 40;
	m_dcMem.BitBlt(
		m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(),
		&m_dcBG, m_rtGameRect.left, m_rtGameRect.top,
		SRCCOPY
	);

	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			int nInfo = m_GameControl.GetElement(i, j);
			//m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo * nElemH, SRCAND);
		}
	}
}

void CGamedlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > 3 || nCol > 3) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint) {
		DrawTipFrame(nRow, nCol);
		m_GameControl.SetFirstPoint(nRow, nCol);

	}
	else {
		DrawTipFrame(nRow, nCol);
        m_GameControl.SetSecPoint(nRow, nCol);
		//TODO: 判断两个点是否可以消除
		if (m_GameControl.Link()){
			Vertex *vertexs = m_GameControl.GetPoints();
            DrawTipLine(vertexs);
			m_GameControl.Clear();
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
	}
	m_bFirstPoint = !m_bFirstPoint;
}

void CGamedlg::DrawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;

	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;

	dc.FrameRect(rtTipFrame, &brush);
}


void CGamedlg::DrawTipLine(Vertex vertexs[2])
{
	// 获取设备上下文
	CClientDC dc(this);

	// 设置画笔：实线、宽度2像素、颜色为纯绿色 RGB(0, 255, 0)
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	// 将画笔选入DC，并保存原画笔
	CPen* pOldPen = dc.SelectObject(&penLine);

	// 绘制连接线（两条线段）
	dc.MoveTo(
		m_ptGameTop.x + vertexs[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + vertexs[0].row * m_sizeElem.cy + m_sizeElem.cy / 2
	);
	dc.LineTo(
		m_ptGameTop.x + vertexs[1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + vertexs[1].row * m_sizeElem.cy + m_sizeElem.cy / 2
	);

	// 恢复原画笔（重要：避免资源泄漏和后续绘图异常）
	dc.SelectObject(pOldPen);
}