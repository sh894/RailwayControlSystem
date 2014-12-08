// LSPUDlg.h : header file
//

#if !defined(AFX_LSPUDLG_H__63100137_DC79_415F_9E2C_03B91F5526D8__INCLUDED_)
#define AFX_LSPUDLG_H__63100137_DC79_415F_9E2C_03B91F5526D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLSPUDlg dialog
DWORD WINAPI listen_com(LPVOID p);
class CLSPUDlg : public CDialog
{
// Construction
public:
	CFont *m_Font;
	CBrush    m_brush;  

	IPicture * pPic;
	IStream  * pStm;
	CRect rect;
	CFileStatus fstatus;
	CFile file;
	LONG  cb;
	HGLOBAL  hGlobal;
	LPVOID pvData;
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;

	CLSPUDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLSPUDlg)
	enum { IDD = IDD_LSPU_DIALOG };
	CEdit	m_sign;
	CEdit	m_ctrl_slv_id_3;
	CEdit	m_ctrl_slv_id_2;
	CEdit	m_ctrl_slv_id_1;
	CEdit	m_ctrl_mst;
	CButton	m_ctrl_select;
	CButton	m_btn_send;
	CButton	m_btn_logoff;
	CButton	m_btn_reg;
	CButton	m_btnStartSerialCom;
	short	m_var_mst_id;
	short	m_var_slv_id_1;
	short	m_var_slv_id_2;
	short	m_var_slv_id_3;
	int		m_var_select;
	short	m_var_ctrl;
	BYTE	m_qianyinli;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSPUDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	//串口指针
	RS485 *com;
	//注册状态
	bool is_reg;
	//主车ID
	short mst_id;
	//本车ID
	short loc_id;
	//串口启动状态
	bool m_bStopSerialCom;
	//串口线程函数
	static	unsigned int SerialComListenProc(LPVOID param);


	void act(frame *fr);
//	DWORD WINAPI listen_com(LPVOID p);
	// Generated message map functions
	//{{AFX_MSG(CLSPUDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnStopAcce();
	afx_msg void OnStop();
	afx_msg void OnStopStop();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSPUDLG_H__63100137_DC79_415F_9E2C_03B91F5526D8__INCLUDED_)
