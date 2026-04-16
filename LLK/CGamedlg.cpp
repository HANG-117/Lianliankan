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
	// 先尝试从文件加载背景位图（相对路径），失败则回退到资源
	HBITMAP hBmpBG = (HBITMAP)::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);

	if (hBmpBG) {
		m_bmpBG.Attach(hBmpBG);
	}
	else {
		m_bmpBG.LoadBitmap(IDB_MAIN_BG);
	}

	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(&m_bmpBG);

	// 离屏位图（保存整个窗口或游戏区的绘制结果）
	m_dcMem.CreateCompatibleDC(&dc);
	m_bmpMem.CreateCompatibleBitmap(&dc, 800, 600);  // 根据窗口大小调整
	m_dcMem.SelectObject(&m_bmpMem);

	// 把背景拷贝到离屏 DC（以后所有的绘制都先到 m_dcMem）
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
}

BOOL CGamedlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitBackground();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CGamedlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// 把离屏DC内容 blit 到屏幕
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}


void CGamedlg::InitElement() {
	CClientDC dc(this);
	HBITMAP hBmpElement = (HBITMAP)::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBmpElement) {
		m_bmpElement.Attach(hBmpElement);
	}
	else {
		m_bmpElement.LoadBitmap(IDB_BITMAP1); // 资源回退，根据实际资源调整
	}
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(&m_bmpElement);

	HBITMAP hmask = (HBITMAP)::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hmask) {
		m_bmpMask.Attach(hmask);
	}
	else {
		m_bmpMask.LoadBitmap(IDB_BITMAP2); // 资源回退，根据实际资源调整
	}
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(&m_bmpMask);
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
	m_GameControl.StartGame();
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
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
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	// 只拷贝游戏区域背景（覆盖之前绘制的方框和线条）
	m_dcMem.BitBlt(
		m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(),
		&m_dcBG, m_rtGameRect.left, m_rtGameRect.top,
		SRCCOPY
	);

	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			int nInfo = m_GameControl.GetElement(i, j);
			// 如果为空，不绘制元素
			if (nInfo == BLANK) continue;

			// 先绘制遮罩（SRCPAINT），再绘制元素图（SRCAND）
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo * nElemH, SRCAND);
		}
	}
}

void CGamedlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 判断是否在游戏区外
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > 3 || nCol > 3) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	if (m_bFirstPoint) {
		// 第一次点击：绘制选中方框
		UpdateMap();  // 先重绘地图（清除之前的装饰）
		DrawTipFrame(nRow, nCol);
		InvalidateRect(m_rtGameRect, FALSE);
		UpdateWindow();  // 立即刷新屏幕

		m_GameControl.SetFirstPoint(nRow, nCol);
		m_bFirstPoint = false;
	}
	else {
		// 第二次点击：判断是否能消除
		m_GameControl.SetSecPoint(nRow, nCol);

		if (m_GameControl.Link()) {
			// 能连通：绘制两个方框 + 线条
			UpdateMap();  // 先更新地图
			Vertex firstPt = m_GameControl.GetFirstPoint();
			DrawTipFrame(firstPt.row, firstPt.col);
			DrawTipFrame(nRow, nCol);

			int nCount = 0;
			Vertex* vertexs = m_GameControl.GetPoints(nCount);
			if (vertexs && nCount >= 2) {
				// 绘制完整路径（放在 UpdateMap 之后，这样线条不会被覆盖）
				DrawTipLine(vertexs, nCount);
			}

			InvalidateRect(m_rtGameRect, FALSE);
			UpdateWindow();  // 立即刷新显示线条和方框

			// 延迟后消除图片
			Sleep(300);

			m_GameControl.Clear();
			UpdateMap();
			InvalidateRect(m_rtGameRect, FALSE);
			UpdateWindow();  // 再刷新一次显示消除后的结果

			if (vertexs) delete[] vertexs;
		}
		else {
			// 不能连通：只绘制两个方框
			UpdateMap();
			Vertex firstPt = m_GameControl.GetFirstPoint();
			DrawTipFrame(firstPt.row, firstPt.col);
			DrawTipFrame(nRow, nCol);

			InvalidateRect(m_rtGameRect, FALSE);
			UpdateWindow();  // 立即刷新显示

			// 短延迟后清除
			Sleep(500);

			UpdateMap();
			InvalidateRect(m_rtGameRect, FALSE);
			UpdateWindow();
		}

		// 重置为等待第一个点击
		m_bFirstPoint = true;
	}
}

void CGamedlg::DrawTipFrame(int nRow, int nCol) {
	// 把框画到离屏 DC 上
	CRect rtTipFrame;

	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;

	// 在离屏DC画边框（空心）
	CPen pen(PS_SOLID, 2, RGB(233, 43, 43));
	CPen* pOldPen = m_dcMem.SelectObject(&pen);
	m_dcMem.SelectStockObject(NULL_BRUSH);
	m_dcMem.Rectangle(rtTipFrame);
	m_dcMem.SelectObject(pOldPen);
}

void CGamedlg::DrawTipLine(Vertex* vertexs, int nCount)
{
	if (vertexs == nullptr || nCount < 2) return;

	// 在离屏DC绘制线条（必须在 UpdateMap 之后调用，否则会被覆盖）
	CPen penLine(PS_SOLID, 3, RGB(0, 255, 0));
	CPen* pOldPen = m_dcMem.SelectObject(&penLine);

	// 按顺序连接每个顶点
	for (int i = 0; i < nCount - 1; ++i) {
		int x1 = m_ptGameTop.x + vertexs[i].col * m_sizeElem.cx + m_sizeElem.cx / 2;
		int y1 = m_ptGameTop.y + vertexs[i].row * m_sizeElem.cy + m_sizeElem.cy / 2;
		int x2 = m_ptGameTop.x + vertexs[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2;
		int y2 = m_ptGameTop.y + vertexs[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2;
		m_dcMem.MoveTo(x1, y1);
		m_dcMem.LineTo(x2, y2);
	}

	m_dcMem.SelectObject(pOldPen);
}