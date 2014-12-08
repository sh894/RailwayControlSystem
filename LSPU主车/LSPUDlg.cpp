// LSPUDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSPU.h"
#include "LSPUDlg.h"
#include "windows.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSPUDlg dialog

CLSPUDlg::CLSPUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLSPUDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLSPUDlg)
	m_var_mst_id = 4043;
	m_var_slv_id_1 = 4012;
	m_var_slv_id_2 = 4013;
	m_var_slv_id_3 = 4033;
	m_var_select = -1;
	m_var_ctrl = 0;
	m_qianyinli = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLSPUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLSPUDlg)
	DDX_Control(pDX, IDC_sign, m_sign);
	DDX_Control(pDX, IDC_EDIT4, m_ctrl_slv_id_3);
	DDX_Control(pDX, IDC_EDIT3, m_ctrl_slv_id_2);
	DDX_Control(pDX, IDC_EDIT2, m_ctrl_slv_id_1);
	DDX_Control(pDX, IDC_EDIT1, m_ctrl_mst);
	DDX_Control(pDX, IDC_RADIO1, m_ctrl_select);
	DDX_Control(pDX, IDC_BUTTON3, m_btn_send);
	DDX_Control(pDX, IDC_BUTTON2, m_btn_logoff);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_reg);
	DDX_Control(pDX, IDC_BUTTON4, m_btnStartSerialCom);
	DDX_Text(pDX, IDC_EDIT1, m_var_mst_id);
	DDV_MinMaxInt(pDX, m_var_mst_id, 0, 5000);
	DDX_Text(pDX, IDC_EDIT2, m_var_slv_id_1);
	DDV_MinMaxInt(pDX, m_var_slv_id_1, 0, 5000);
	DDX_Text(pDX, IDC_EDIT3, m_var_slv_id_2);
	DDX_Text(pDX, IDC_EDIT4, m_var_slv_id_3);
	DDV_MinMaxInt(pDX, m_var_slv_id_3, 0, 5000);
	DDX_Radio(pDX, IDC_RADIO1, m_var_select);
	DDX_Text(pDX, IDC_EDIT5, m_var_ctrl);
	DDV_MinMaxInt(pDX, m_var_ctrl, 0, 128);
	DDX_Text(pDX, IDC_EDIT6, m_qianyinli);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLSPUDlg, CDialog)
	//{{AFX_MSG_MAP(CLSPUDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_BUTTON5, OnStopAcce)
	ON_BN_CLICKED(IDC_BUTTON6, OnStop)
	ON_BN_CLICKED(IDC_BUTTON7, OnStopStop)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSPUDlg message handlers

BOOL CLSPUDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


	//初始化串口
	com = new RS485;
	//初始化注册状态
	is_reg = false;

	m_brush.CreateSolidBrush(RGB(193,210,240));    

	//初始化按钮状态
	m_btn_logoff.EnableWindow(FALSE);
//	m_btn_send.EnableWindow(FALSE);
	m_btnStartSerialCom.EnableWindow(FALSE);
	m_ctrl_select.SetCheck(1);

	m_Font = new CFont;
	m_Font->CreateFont(50,20,0,0,100,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS,"楷体");
    m_sign.SetFont(m_Font,FALSE);


	CString str = "res\\05.jpg";
	file.Open (str,CFile::modeRead);file.GetStatus (str,fstatus);cb=fstatus.m_size ;
	hGlobal=GlobalAlloc(GMEM_MOVEABLE,cb);
	pvData=NULL;
	pvData=GlobalLock(hGlobal);
	file.ReadHuge (pvData,cb);
	GlobalUnlock(hGlobal);
	CreateStreamOnHGlobal(hGlobal,TRUE,&pStm);      
	SUCCEEDED(OleLoadPicture(pStm,fstatus.m_size ,TRUE,IID_IPicture,(LPVOID *)&pPic));		 
	pStm->Release ();       
	pPic->get_Width(&hmWidth);
	pPic->get_Height (&hmHeight);
	CPaintDC dc(this); 

	this->Invalidate(TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLSPUDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLSPUDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	CClientDC dc(this);
	GetClientRect(&rect);
	ClientToScreen(&rect); 
	double x,y;
	x=rect.Width();
	y=rect.Height();

	pPic->Render(dc,0,0,(DWORD)x,(DWORD)y,0,hmHeight,hmWidth,-hmHeight,NULL);    
	
	dc.SetStretchBltMode(COLORONCOLOR) ;//降低图片失真

//	this->ShowWindow(SW_SHOWMAXIMIZED);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLSPUDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLSPUDlg::OnButton1() 
{

	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
    switch(m_var_mst_id)
	{
	case 4043:m_var_mst_id=1;break;
	case 4012:m_var_mst_id=2;break;
        case 4013:m_var_mst_id=3;break;
	case 4033:m_var_mst_id=4;break;
	}
	switch(m_var_slv_id_1)
	{
	case 4043:m_var_slv_id_1=1;break;
	case 4012:m_var_slv_id_1=2;break;
       case 4013:m_var_slv_id_1=3;break;
	case 4033:m_var_slv_id_1=4;break;
	}
	switch(m_var_slv_id_2)
	{
	case 4043:m_var_slv_id_2=1;break;
	case 4012:m_var_slv_id_2=2;break;
       case 4013:m_var_slv_id_2=3;break;
	case 4033:m_var_slv_id_2=4;break;
	}
	switch(m_var_slv_id_3)
	{
	case 4043:m_var_slv_id_3=1;break;
	case 4012:m_var_slv_id_3=2;break;
       case 4013:m_var_slv_id_3=3;break;
	case 4033:m_var_slv_id_3=4;break;
	}
	frame *reg = new frame;
	reg->set_type(MSG_MST_LOCO_REG);

	if(this->m_var_select == 0){//主车注册
		reg->set_type(MSG_MST_LOCO_REG);
		mst_id = loc_id = m_var_mst_id;
		
		//设置从车1ID
		memcpy(reg->getFrame() + 9, &m_var_slv_id_1,sizeof(short));

		//设置从车2ID
		memcpy(reg->getFrame() + 11,&m_var_slv_id_2,sizeof(short));
		
		//设置从车3ID
		memcpy(reg->getFrame() + 13,&m_var_slv_id_3,sizeof(short));
	}
	else{//从车注册
		reg->set_type(MSG_SLV_LOCO_REG);
		mst_id = m_var_mst_id;
		loc_id = m_var_slv_id_1;
		//设置从车ID 
		memcpy(reg->getFrame() + 9, &m_var_slv_id_1,sizeof(short));
	}

	//设置本车ID 主车ID
	memcpy(reg->getFrame() + 5, &mst_id,sizeof(short));
	memcpy(reg->getFrame() + 7, &loc_id,sizeof(short));

	//发送失败
	if(!this->com->send(*reg)){
		std::cout<<"发送失败"<<std::endl;
	}
	std::cout<<"发送注册帧成功"<<std::endl;

	frame *reg_receive = new frame; 
    Sleep(5000);
	if(!this->com->receive(reg_receive)){

		is_reg = false;
		std::cout<<"注册失败"<<std::endl;
	}

	else if(reg_receive->getFrameType() == MSG_REG_REPLY){
		std::cout<<"注册失败"<<"收到注册失败"<<std::endl;
	}

	else if(reg_receive->getFrameType() == MSG_OCU_IP_REPLY){
		std::cout<<"注册成功"<<std::endl;
		this->is_reg = true;
	}

	//设置按钮状态
	if (is_reg)
	{
		m_btn_logoff.EnableWindow(TRUE);
		m_ctrl_select.EnableWindow(FALSE);
		m_btn_reg.EnableWindow(FALSE);
		m_btn_send.EnableWindow(TRUE);
		m_btnStartSerialCom.EnableWindow(TRUE);
	}

	
	this->Invalidate(TRUE);
}

void CLSPUDlg::OnButton2() 
{
	


	//创建注销帧
	frame *logoff = new frame(MSG_LOG_OFF);
	//组标识
	memcpy(logoff->getFrame() + 5, &mst_id,sizeof(short));
	//本车标识
	memcpy(logoff->getFrame() + 7, &loc_id,sizeof(short));
	//发送注销帧
	Sleep(5000);
	if (!com->send(*logoff))
	{
		std::cerr<<"注销帧发送失败"<<std::endl;
		return;
	}

	std::cout<<"发送注册帧成功"<<std::endl;

	Sleep(500);

	frame *logoff_reply = new frame();

	com->receive(logoff_reply);



	if (is_reg == false)
	{
		m_btn_reg.EnableWindow(TRUE);
		m_btn_logoff.EnableWindow(FALSE);
		m_btnStartSerialCom.EnableWindow(FALSE);
//		m_btn_send.EnableWindow(FALSE);
	}
	this->Invalidate(TRUE);
}


unsigned int CLSPUDlg::SerialComListenProc(LPVOID param){

	std::cout<<"监听线程已经启动"<<std::endl;
	CLSPUDlg *dl = (CLSPUDlg*)param;
	while(true){
		frame *fr = new frame;
		dl->com->receive(fr);

		//打印控制信息
		if (fr->getFrameType())
		{
			dl->act(fr);
		}
		delete fr;
		Sleep(50);
	}
	
}

void CLSPUDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CString caption;
	m_btnStartSerialCom.GetWindowText(caption);
	if(caption == "启动串口线程")
	{
		m_btnStartSerialCom.SetWindowText("停止串口线程");
		m_bStopSerialCom = FALSE;
		AfxBeginThread(SerialComListenProc, this, THREAD_PRIORITY_NORMAL);
		m_btn_logoff.EnableWindow(TRUE);
	}
	else
	{
		m_btnStartSerialCom.SetWindowText("启动串口线程");
		m_bStopSerialCom = TRUE;
		
	}	
	this->Invalidate(TRUE);
}

void CLSPUDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	m_ctrl_mst.EnableWindow(TRUE);
	m_ctrl_slv_id_1.EnableWindow(TRUE);
	m_ctrl_slv_id_2.EnableWindow(TRUE);
	m_ctrl_slv_id_3.EnableWindow(TRUE);
}

void CLSPUDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_ctrl_slv_id_2.EnableWindow(FALSE);
	m_ctrl_slv_id_3.EnableWindow(FALSE);	
}

void CLSPUDlg::act(frame *fr){

	switch (fr->getFrameType())
	{
	case MSG_OCU_IP_REPLY:
		is_reg = true;
		m_btn_logoff.EnableWindow(TRUE);
		m_ctrl_select.EnableWindow(FALSE);
		m_btn_reg.EnableWindow(FALSE);
		m_btn_send.EnableWindow(TRUE);
		m_btnStartSerialCom.EnableWindow(TRUE);
		std::cout<<"收到注册成功"<<std::endl;
		break;
	case MSG_REG_REPLY:
		is_reg = false;
		std::cout<<"收到注册失败"<<std::endl;
	case MSG_LOGOFF_REPLY:
		if(fr->getFrame()[9]==0x00){
			is_reg = false;
			std::cout<<"收到注销成功"<<std::endl;
		}
		else{
			std::cout<<"收到注销失败"<<std::endl;
		}
		break;
	case MSG_CTL:
		printf("收到控制信息：");
		for(int i = 0; i < fr->getLength(); ++i){
			printf("%d ",fr->getFrame()[i]);
		}
		printf("\n");
		int temp = fr->getFrame()[9];
		if(temp == 1){
			CString str = "加速";
			
			SetDlgItemText(IDC_sign,str);
		}
		else if(temp == 2){
			CString str = "停止加速";
			
			SetDlgItemText(IDC_sign,str);
		}
		else if(temp == 3){
			CString str = "制动";
			
			SetDlgItemText(IDC_sign,str);
		}
		else if(temp == 4){
			CString str = "停止制动";
			
			SetDlgItemText(IDC_sign,str);
		}
	}

}

void CLSPUDlg::OnButton3()   //加速
{
	UpdateData(TRUE);
 	frame *ctrl = new frame(MSG_CTL);
 switch(m_var_mst_id)
	{
	case 4043:m_var_mst_id=43;break;
	case 4012:m_var_mst_id=12;break;
        case 4013:m_var_mst_id=13;break;
	case 4033:m_var_mst_id=33;break;
	}
	switch(m_var_slv_id_1)
	{
	case 4043:m_var_slv_id_1=43;break;
	case 4012:m_var_slv_id_1=12;break;
       case 4013:m_var_slv_id_1=13;break;
	case 4033:m_var_slv_id_1=33;break;
	}
	switch(m_var_slv_id_2)
	{
	case 4043:m_var_slv_id_2=43;break;
	case 4012:m_var_slv_id_2=12;break;
       case 4013:m_var_slv_id_2=13;break;
	case 4033:m_var_slv_id_2=33;break;
	}
	switch(m_var_slv_id_3)
	{
	case 4043:m_var_slv_id_3=43;break;
	case 4012:m_var_slv_id_3=12;break;
       case 4013:m_var_slv_id_3=13;break;
	case 4033:m_var_slv_id_3=33;break;
	}
	short temp = 1;
	mst_id = loc_id = m_var_mst_id;


	memcpy(ctrl->getFrame() + 9, &temp, sizeof(temp));
	memcpy(ctrl->getFrame() + 5, &mst_id, sizeof(mst_id));
	memcpy(ctrl->getFrame() + 7, &loc_id, sizeof(loc_id));
	memcpy(ctrl->getFrame()+10,&m_qianyinli,sizeof(m_qianyinli));

	printf("发送控制信息:%s\n","加速");
 	com->send(*ctrl);
	CString str = "加速";
	SetDlgItemText(IDC_sign,str);
	this->Invalidate(TRUE);
}

void CLSPUDlg::OnStopAcce() //停止加速
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
 	frame *ctrl = new frame(MSG_CTL);
 switch(m_var_mst_id)
	{
	case 4043:m_var_mst_id=43;break;
	case 4012:m_var_mst_id=12;break;
        case 4013:m_var_mst_id=13;break;
	case 4033:m_var_mst_id=33;break;
	}
	switch(m_var_slv_id_1)
	{
	case 4043:m_var_slv_id_1=43;break;
	case 4012:m_var_slv_id_1=12;break;
       case 4013:m_var_slv_id_1=13;break;
	case 4033:m_var_slv_id_1=33;break;
	}
	switch(m_var_slv_id_2)
	{
	case 4043:m_var_slv_id_2=43;break;
	case 4012:m_var_slv_id_2=12;break;
       case 4013:m_var_slv_id_2=13;break;
	case 4033:m_var_slv_id_2=33;break;
	}
	switch(m_var_slv_id_3)
	{
	case 4043:m_var_slv_id_3=43;break;
	case 4012:m_var_slv_id_3=12;break;
       case 4013:m_var_slv_id_3=13;break;
	case 4033:m_var_slv_id_3=33;break;
	}
	short temp = 2;
	mst_id = loc_id = m_var_mst_id;

	memcpy(ctrl->getFrame() + 9, &temp, sizeof(temp));
	memcpy(ctrl->getFrame() + 5, &mst_id, sizeof(mst_id));
	memcpy(ctrl->getFrame() + 7, &loc_id, sizeof(loc_id));
 
	printf("发送控制信息:%s\n","停止加速");
 	com->send(*ctrl);
	CString str = "停止加速";
	SetDlgItemText(IDC_sign,str);
	this->Invalidate(TRUE);
	
}

void CLSPUDlg::OnStop()   //制动
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
 	frame *ctrl = new frame(MSG_CTL);
 switch(m_var_mst_id)
	{
	case 4043:m_var_mst_id=43;break;
	case 4012:m_var_mst_id=12;break;
        case 4013:m_var_mst_id=13;break;
	case 4033:m_var_mst_id=33;break;
	}
	switch(m_var_slv_id_1)
	{
	case 4043:m_var_slv_id_1=43;break;
	case 4012:m_var_slv_id_1=12;break;
       case 4013:m_var_slv_id_1=13;break;
	case 4033:m_var_slv_id_1=33;break;
	}
	switch(m_var_slv_id_2)
	{
	case 4043:m_var_slv_id_2=43;break;
	case 4012:m_var_slv_id_2=12;break;
       case 4013:m_var_slv_id_2=13;break;
	case 4033:m_var_slv_id_2=33;break;
	}
	switch(m_var_slv_id_3)
	{
	case 4043:m_var_slv_id_3=43;break;
	case 4012:m_var_slv_id_3=12;break;
       case 4013:m_var_slv_id_3=13;break;
	case 4033:m_var_slv_id_3=33;break;
	}
	short temp = 3;
	mst_id = loc_id = m_var_mst_id;

	memcpy(ctrl->getFrame() + 9, &temp, sizeof(temp));
	memcpy(ctrl->getFrame() + 5, &mst_id, sizeof(mst_id));
	memcpy(ctrl->getFrame() + 7, &loc_id, sizeof(loc_id));
 
	printf("发送控制信息:%s\n","制动");
 	com->send(*ctrl);
	CString str = "制动";
	SetDlgItemText(IDC_sign,str);
	this->Invalidate(TRUE);
	
}

void CLSPUDlg::OnStopStop() //停止制动
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
 	frame *ctrl = new frame(MSG_CTL);
 switch(m_var_mst_id)
	{
	case 4043:m_var_mst_id=43;break;
	case 4012:m_var_mst_id=12;break;
        case 4013:m_var_mst_id=13;break;
	case 4033:m_var_mst_id=33;break;
	}
	switch(m_var_slv_id_1)
	{
	case 4043:m_var_slv_id_1=43;break;
	case 4012:m_var_slv_id_1=12;break;
       case 4013:m_var_slv_id_1=13;break;
	case 4033:m_var_slv_id_1=33;break;
	}
	switch(m_var_slv_id_2)
	{
	case 4043:m_var_slv_id_2=43;break;
	case 4012:m_var_slv_id_2=12;break;
       case 4013:m_var_slv_id_2=13;break;
	case 4033:m_var_slv_id_2=33;break;
	}
	switch(m_var_slv_id_3)
	{
	case 4043:m_var_slv_id_3=43;break;
	case 4012:m_var_slv_id_3=12;break;
       case 4013:m_var_slv_id_3=13;break;
	case 4033:m_var_slv_id_3=33;break;
	}
	short temp = 4;
	mst_id = loc_id = m_var_mst_id;

	memcpy(ctrl->getFrame() + 9, &temp, sizeof(temp));
	memcpy(ctrl->getFrame() + 5, &mst_id, sizeof(mst_id));
	memcpy(ctrl->getFrame() + 7, &loc_id, sizeof(loc_id));

	printf("发送控制信息:%s\n","停止制动");
 	com->send(*ctrl);
	CString str = "停止制动";
	SetDlgItemText(IDC_sign,str);
	this->Invalidate(TRUE);
	
}

HBRUSH CLSPUDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC -> SetBkColor(RGB(255,255,255));

	// TODO: Change any attributes of the DC here
	if (pWnd-> GetDlgCtrlID()==IDC_sign)
	{ 
		CBrush   brush   ; 
		brush.CreateStockObject   (   NULL_BRUSH   )   ; 
		pDC-> SetTextColor(RGB(256,256,256)); //设置字体颜色
//		pDC-> SetBkMode(TRANSPARENT); //设置字体背景为透明
		return   (HBRUSH)   brush.m_hObject   ;	
	
	}
	
	if (pWnd-> GetDlgCtrlID()==IDC_RADIO1
		||pWnd-> GetDlgCtrlID()==IDC_RADIO2
		||pWnd-> GetDlgCtrlID()==IDC_STATIC
		||pWnd-> GetDlgCtrlID()==IDC_EDIT1
		||pWnd-> GetDlgCtrlID()==IDC_EDIT2
		||pWnd-> GetDlgCtrlID()==IDC_EDIT3
		||pWnd-> GetDlgCtrlID()==IDC_EDIT4)
	{ 
		CBrush   brush   ; 
		
		brush.CreateStockObject   (   NULL_BRUSH   )   ; 
		pDC-> SetBkMode(TRANSPARENT); //设置字体背景为透明
		return   (HBRUSH)   brush.m_hObject   ;	
	}
	
	return    m_brush; 
}

void CLSPUDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
}

void CLSPUDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
	this->Invalidate(TRUE);
}

void CLSPUDlg::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CLSPUDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CLSPUDlg::OnChangeEdit6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
