#if !defined(AFX_ORDERS_H__35C4B7AC_DECE_42C9_962D_DE79242B519D__INCLUDED_)
#define AFX_ORDERS_H__35C4B7AC_DECE_42C9_962D_DE79242B519D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Orders.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COrders dialog
class CSurfaceView;
class COrders : public CDialog
{
// Construction
public:
	void UpdateData();
	COrders(CWnd* pParent = NULL);   // standard constructor
	void SetView(CSurfaceView * pview);
	CSurfaceView * m_pCSurfaceView;

// Dialog Data
	//{{AFX_DATA(COrders)
	enum { IDD = IDD_ORDERS };
	double	m_DifCoef;
	double	m_RAFT_PROBABILITY_TO_MERGE;
	double	m_Snap25_D;
	double	m_Ppob_SynSNAP25Vamp_Dis;
	double	m_Ppob_SynSNAP25_Dis;
	double	m_Ppob_SntSNAP25Snt_Dis;
	int		m_StepsNumber;
	double	m_Stx_D;
	double	m_Vamp_D;
	double	m_D_ESF;
	int		m_initStxNumber;
	int		m_initNSFnumber;
	int		m_initSNAP25Number;
	int		m_initVampNumber;
	double	m_SNAP25Pin_raft;
	double	m_SNAP25Pour_raft;
	double	m_StxPin_raft;
	double	m_StxPout_raft;
	double	m_Vamp_Pin_raft;
	double	m_Vamp_Pout_raft;
	double	m_Ppob_Syn_Bind_SNAP25;
	double	m_Ppob_SynSNAP25_BindVamp;
	double	m_initStxInRaftFract;
	double	m_initSnap25InRaftFract;
	double	m_initNSFInRaftFract;
	double	m_initVampInRaftFract;
	double	m_Snt_SNAP25_Pin_raft;
	double	m_Snt_SNAP25_Vamp_Pin_raft;
	double	m_Snt_SNAP25_Vamp_Pout_raft;
	double	m_Snt_SNAP25_Pout_raft;
	int		m_RaftNumber;
	int		m_MeanRaftSize;
	double	m_P_NSF_on_Snt_Snap;
	double	m_Snap25_D_inRaft;
	double	m_Snt_D_inRaft;
	double	m_Vamp_D_inRaft;
	double	m_initSntSnap25inRaftFraction;
	double	m_initSntSnap25VampinRaftFraction;
	int		m_initSntSnap25Number;
	int		m_initSntSnap25VampNumber;
	int		m_initSnt_Snap25VampAlphaNum;
	double	m_initSnt_Snap25VampAlphaInRaftFract;
	double	m_Ppob_SynSNAPVamp_BindAlpha;
	double	m_SntSNAP_VampAlpha_Pin_raft;
	double	m_SntSNAP_VampAlpha_Pout_raft;
	double	m_D_Alpha;
	int		m_LifeTime_Alpha;
	int		m_LifeTime_NSF;
	BOOL	m_NSFtoRemoveCompl;
	double	m_Ppob_SntSNAP25VampAlpha_Dis;
	double	m_Ppob_Snt_bind_Snt;
	double	m_Ppob_SntSnt_Dis;
	double	m_Ppob_SntSnt_bind_Snt;
	double	m_Ppob_SntSntSnt_Dis;
	double	m_SntSnt_Pin_raft;
	double	m_SntSnt_Pout_raft;
	double	m_SntSntSnt_Pin_raft;
	double	m_SntSntSnt_Pout_raft;
	double	m_initSntSntInRaftFract;
	double	m_initSntSntSnt_InRaftFract;
	int		m_initSntSnt_num;
	int		m_m_initSntSntSnt_num;
	double	m_initAlphaInRaftFract;
	int		m_initAlphaNum;
	double	m_Ptransloc_Alpha;
	double	m_Ptransloc_NSF;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrders)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COrders)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORDERS_H__35C4B7AC_DECE_42C9_962D_DE79242B519D__INCLUDED_)
