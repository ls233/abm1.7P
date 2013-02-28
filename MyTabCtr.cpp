// MyTabCtr.cpp : implementation file
//

#include "stdafx.h"
#include "Surface.h"
#include "MyTabCtr.h"
#include "Option.h"
#include "Orders.h"
#include "Result.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtr

CMyTabCtr::CMyTabCtr()
{
	m_tabPages[0]=new COption;
	m_tabPages[1]=new COrders;
	m_tabPages[2]=new CResult;

	m_nNumberOfPages=3;
}

CMyTabCtr::~CMyTabCtr()
{
	for(int nCount=0; nCount < m_nNumberOfPages; nCount++){
		delete m_tabPages[nCount];
	}
}
void CMyTabCtr::SetParent(CSurfaceView * parent)
{
	m_pCSurfaceView = parent;
}


void CMyTabCtr::Init()
{
	m_tabCurrent=0;
	((COption *)m_tabPages[0])->SetView(m_pCSurfaceView);
	((COrders *)m_tabPages[1])->SetView(m_pCSurfaceView);
	((CResult *)m_tabPages[2])->SetView(m_pCSurfaceView);

	m_tabPages[0]->Create(IDD_OPTION, this);
	m_tabPages[1]->Create(IDD_ORDERS, this);
	m_tabPages[2]->Create(IDD_RESULT, this);

	m_tabPages[0]->ShowWindow(SW_SHOW);
	m_tabPages[1]->ShowWindow(SW_HIDE);
	m_tabPages[2]->ShowWindow(SW_HIDE);

	SetRectangle();
}

void CMyTabCtr::SetRectangle()
{
	CRect tabRect, itemRect, rc;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);
	m_tabPages[0]->GetClientRect(&rc);
	//SetItemSize(rc.Size());

	nX=itemRect.left ;
	nY=itemRect.bottom+1;
	nXc=tabRect.right-itemRect.left-1;
	nYc=tabRect.bottom-nY-1;

	m_tabPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for(int nCount=1; nCount < m_nNumberOfPages; nCount++){
		m_tabPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	}
}


BEGIN_MESSAGE_MAP(CMyTabCtr, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTabCtr)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtr message handlers

void CMyTabCtr::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CTabCtrl::OnLButtonDown(nFlags, point);
	if(m_tabCurrent != GetCurFocus()){
		m_tabPages[m_tabCurrent]->ShowWindow(SW_HIDE);
		m_tabCurrent=GetCurFocus();
		m_tabPages[m_tabCurrent]->ShowWindow(SW_SHOW);
		m_tabPages[m_tabCurrent]->SetFocus();
	}
}
