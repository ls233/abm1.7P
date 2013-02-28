#if !defined(AFX_OPTION_H__452A9AC3_7A2C_11D7_9256_0002B33546D4__INCLUDED_)
#define AFX_OPTION_H__452A9AC3_7A2C_11D7_9256_0002B33546D4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Option.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COption dialog
class CSurfaceView;
class COption : public CDialog
{
	CSurfaceView * m_pCSurfaceView;
	void FillComboZoom(int zoom) ;
// Construction
public:
	COption(CWnd* pParent = NULL);   // standard constructor
	void UpdateData();
	void SetZoom(int, int,int );
	void SetView(CSurfaceView * pview);
	void OnFinishSim()
	{
		OnCancelSim();
	};
// Dialog Data
	//{{AFX_DATA(COption)
	enum { IDD = IDD_OPTION };
	CComboBox	m_ComboZoom;
	CButton	m_StepBtn;
	int		m_RecNum;
	int		m_Step;
	int		m_StepNum;
	int		m_Cur_Ag_Number;
	int		m_TimerInitialisator;
	int		m_Cur_Raft_Number;
	BOOL	m_StepBy;
	BOOL	m_Check_Draw_Indexes;
	int		m_Win_Update_Timer;
	int		m_Simulation_Duration;
	BOOL	m_CHEK_Draw_Rec;
	BOOL	m_Check_Draw_SM_names;
	BOOL	m_Check_Draw_SM;
	BOOL	m_CHEK_Draw_Ag;
	BOOL	m_CHEK_Draw_Ag_Indexes;
	BOOL	m_CHEK_Draw_SM_Ind;
	BOOL	m_CHEK_Draw_Raft;
	BOOL	m_CHEK_Draw_Raft_Ind;
	BOOL	m_CHEK_Draw_Names;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COption)
	public:
	virtual BOOL Create( CSurfaceView * pParent) ;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COption)
	virtual BOOL OnInitDialog();
	afx_msg void OnBeginSim();
	afx_msg void OnCancelSim();
	afx_msg void OnDrawBtn();
	afx_msg void OnCheckStep();
	afx_msg void OnNextStep();
	afx_msg void OnSelendokComboZoom();
	afx_msg void OnUpdateEditZoom();
	afx_msg void OnCHEKDrawIndexes();
	afx_msg void OnUpdateEDITWinUpdateTimer();
	afx_msg void OnUpdateEDITTimerInitialisator();
	afx_msg void OnKillfocusEDITWinUpdateTimer();
	afx_msg void OnKillfocusEDITTimerInitialisator();
	afx_msg void OnCHEKDrawRec();
	afx_msg void OnCHEKDrawSM();
	afx_msg void OnCHEKDrawSMnames();
	afx_msg void OnCHEKDrawAg();
	afx_msg void OnCHEKDrawAgIndexes();
	afx_msg void OnCHEKDrawSMInd();
	afx_msg void OnCHEKDrawRaft();
	afx_msg void OnCHEKDrawRaftInd();
	afx_msg void OnCHEKDrawNames();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTION_H__452A9AC3_7A2C_11D7_9256_0002B33546D4__INCLUDED_)
