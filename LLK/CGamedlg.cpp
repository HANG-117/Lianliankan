// CGamedlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGamedlg.h"


// CGamedlg 对话框

IMPLEMENT_DYNAMIC(CGamedlg, CDialogEx)

CGamedlg::CGamedlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{

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
END_MESSAGE_MAP()


// CGamedlg 消息处理程序

void CGamedlg::InitBackground()
{
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	CClientDC dc(this);

	m_dcMem.CreateCompatibleDC(&dc);

	m_dcMem.SelectObject(bmp);


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
	UpdateMap();
	
	Invalidate(FALSE);
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
	int anMap[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			m_anMap[i][j] = anMap[i][j];
		}
	}
	int nLeft = 50;
	int nTop = 50;
	int nElemW = 40;
	int nElemH = 40;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			//m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, m_anMap[i][j] * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCAND);
		}
	}
}
