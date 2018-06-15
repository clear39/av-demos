/* 
 * JPEG������
 * JPEG Analysis
 *
 * ������ Lei Xiaohua
 * leixiaohua1020@126.com
 * �й���ý��ѧ/���ֵ��Ӽ���
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 */

#include "stdafx.h"
#include "SpecialVIJPG.h"
#include "SpecialVIJPGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSpecialVIJPGDlg �Ի���




CSpecialVIJPGDlg::CSpecialVIJPGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpecialVIJPGDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpecialVIJPGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_V_I_JPG_BASICINFO, m_vijpgbasicinfo);
	DDX_Control(pDX, IDC_V_I_JPG_INPUTURL, m_vijpginputurl);
	DDX_Control(pDX, IDC_V_I_JPG_CONSOLE, m_vijpgconsole);
	DDX_Control(pDX, IDC_V_I_JPG_OUTPUT_DCT, m_vijpgoutputdct);
	DDX_Control(pDX, IDC_V_I_JPG_OUTPUT_Y, m_vijpgoutputy);
	DDX_Radio(pDX, IDC_V_I_JPG_OUTPUT_RAW, m_vijpgoutputraw);
	DDX_Control(pDX, IDC_V_I_JPG_LANG, m_vijpglang);
}

BEGIN_MESSAGE_MAP(CSpecialVIJPGDlg, CDialogEx)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_V_I_JPG_INPUTURL_OPEN, &CSpecialVIJPGDlg::OnBnClickedVIJpgInputurlOpen)
	ON_BN_CLICKED(IDC_V_I_JPG_INPUTURL_FILEDIALOG, &CSpecialVIJPGDlg::OnBnClickedVIJpgInputurlFiledialog)
	ON_BN_CLICKED(IDC_V_I_JPG_ABOUT, &CSpecialVIJPGDlg::OnBnClickedVIJpgAbout)
	ON_WM_DROPFILES()
	ON_CBN_SELCHANGE(IDC_V_I_JPG_LANG, &CSpecialVIJPGDlg::OnSelchangeVIJpgLang)
END_MESSAGE_MAP()


// CSpecialVIJPGDlg ��Ϣ�������

BOOL CSpecialVIJPGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	//Propertylist��ʼ��------------------------
	m_vijpgbasicinfo.EnableHeaderCtrl(FALSE);
	m_vijpgbasicinfo.EnableDescriptionArea();
	m_vijpgbasicinfo.SetVSDotNetLook();
	m_vijpgbasicinfo.MarkModifiedProperties();
	//�ѵ�һ�е�����һЩ-----------------------
	HDITEM item; 
	item.cxy=190; 
	item.mask=HDI_WIDTH; 
	m_vijpgbasicinfo.GetHeaderCtrl().SetItem(0, new HDITEM(item)); 
	//m_vijpgbasicinfo.SetGroupNameFullWidth(FALSE,TRUE);
	//��ʼ��----------------
	SOIgroup=new CMFCPropertyGridProperty(_T("SOI (Start of Image)"));
	APP0group=new CMFCPropertyGridProperty(_T("APP0 (Application)"));
	DQTgroup=new CMFCPropertyGridProperty(_T("DQT (Define Quantization Table)"));
	SOF0group=new CMFCPropertyGridProperty(_T("SOF0 (Start of Frame)"));
	DHTgroup=new CMFCPropertyGridProperty(_T("DHT (Define Huffman Table)"));
	SOSgroup=new CMFCPropertyGridProperty(_T("SOS (Start of Scan)"));
	//-----------------------

	//-----------
	m_vijpgoutputraw=0;
	UpdateData(FALSE);
	cinfo.Format(_T(""));
	strcpy(jpgurl,"");
	//--------
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_vijpglang.InsertString(0,_T("Chinese"));
	m_vijpglang.InsertString(1,_T("English"));



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSpecialVIJPGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSpecialVIJPGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	//���Ի���Ӧ����ӵ�OnInitDialog�У�����û��Ч��
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSpecialVIJPGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSpecialVIJPGDlg::OnBnClickedVIJpgInputurlOpen()
{
	SystemClear();

	
	CString strFilePath;
	m_vijpginputurl.GetWindowText(strFilePath);



	if(strFilePath.IsEmpty()==TRUE){
		text.LoadString(IDS_INPUTURL_ERROR);
		AfxMessageBox(text);
		return ;
	}

#ifdef _UNICODE
	USES_CONVERSION;
	strcpy(jpgurl,W2A(strFilePath));
#else
	strcpy(jpgurl,strFilePath);
#endif

	int argc=4;
	char **argv=(char **)malloc(MAX_URL_LENGTH);
	argv[0]=(char *)malloc(MAX_URL_LENGTH);
	argv[1]=(char *)malloc(MAX_URL_LENGTH);
	argv[2]=(char *)malloc(MAX_URL_LENGTH);
	argv[3]=(char *)malloc(MAX_URL_LENGTH);
	strcpy(argv[0],"dummy");
	strcpy(argv[1],jpgurl);
	UpdateData(TRUE);
	switch(m_vijpgoutputraw){
	case 0:strcpy(argv[2],"yuv420p");
		strcpy(argv[3],"output.yuv");
		break;
	case 1:strcpy(argv[2],"rgb24");
		strcpy(argv[3],"output.tga");
		break;
	case 2:strcpy(argv[2],"bgr24");
		strcpy(argv[3],"output.tga");
		break;
	case 3:strcpy(argv[2],"grey");
		strcpy(argv[3],"output.y");
		break;
	default:strcpy(argv[2],"yuv420p");
		strcpy(argv[3],"output.yuv");
		break;
	}

	jpeg_mindec(this,argc,argv);
	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	free(argv[3]);
	free(argv);
	ShowBInfo();
}

//����BasicInfo
int CSpecialVIJPGDlg::AppendBInfo(char *dst_group1,char *property_name1,char *value1,char *remark1){
	//Ϊ�˼���Unicode
	CString dst_group,property_name,value,remark;
#ifdef _UNICODE
	USES_CONVERSION;
	dst_group.Format(_T("%s"),A2W(dst_group1));
	property_name.Format(_T("%s"),A2W(property_name1));
	value.Format(_T("%s"),A2W(value1));
	remark.Format(_T("%s"),A2W(remark1));
#else
	dst_group.Format(_T("%s"),dst_group1);
	property_name.Format(_T("%s"),property_name1);
	value.Format(_T("%s"),value1);
	remark.Format(_T("%s"),remark1);
#endif

	if(dst_group.Compare(_T("SOI"))==0){
		SOIgroup->AddSubItem(new CMFCPropertyGridProperty(property_name, (_variant_t)value, remark));
	}else if(dst_group.Compare(_T("APP0"))==0){
		APP0group->AddSubItem(new CMFCPropertyGridProperty(property_name, (_variant_t)value, remark));
	}else if(dst_group.Compare(_T("DQT"))==0){
		DQTgroup->AddSubItem(new CMFCPropertyGridProperty(property_name, (_variant_t)value, remark));
	}else if(dst_group.Compare(_T("SOF0"))==0){
		SOF0group->AddSubItem(new CMFCPropertyGridProperty(property_name, (_variant_t)value, remark));
	}else if(dst_group.Compare(_T("DHT"))==0){
		DHTgroup->AddSubItem(new CMFCPropertyGridProperty(property_name, (_variant_t)value, remark));
	}else if(dst_group.Compare(_T("SOS"))==0){
		SOSgroup->AddSubItem(new CMFCPropertyGridProperty(property_name, (_variant_t)value, remark));
	}else{
	}

	return 0;
}

int CSpecialVIJPGDlg::ShowBInfo(){
	m_vijpgbasicinfo.AddProperty(SOIgroup);
	m_vijpgbasicinfo.AddProperty(APP0group);
	m_vijpgbasicinfo.AddProperty(DQTgroup);
	m_vijpgbasicinfo.AddProperty(SOF0group);
	m_vijpgbasicinfo.AddProperty(DHTgroup);
	m_vijpgbasicinfo.AddProperty(SOSgroup);
	return TRUE;
}


//����CInfo
int CSpecialVIJPGDlg::AppendCInfo(char *str){
	CString temp_str;

#ifdef _UNICODE
	USES_CONVERSION;
	temp_str.Format(_T("%s\r\n"),A2W(str));
#else
	temp_str.Format(_T("%s\r\n"),str);
#endif

	cinfo.Append(temp_str);
	m_vijpgconsole.SetWindowText(cinfo);
	return 0;
}

void CSpecialVIJPGDlg::SystemClear(){
	cinfo.Format(_T(""));
	SOIgroup->RemoveAllOptions();
	APP0group->RemoveAllOptions();
	DQTgroup->RemoveAllOptions();
	SOF0group->RemoveAllOptions();
	DHTgroup->RemoveAllOptions();
	SOSgroup->RemoveAllOptions();
	m_vijpgbasicinfo.RemoveAll();

	//��ʼ��----------------
	SOIgroup=new CMFCPropertyGridProperty(_T("SOI (Start of Image)"));
	APP0group=new CMFCPropertyGridProperty(_T("APP0 (Application)"));
	DQTgroup=new CMFCPropertyGridProperty(_T("DQT (Define Quantization Table)"));
	SOF0group=new CMFCPropertyGridProperty(_T("SOF0 (Start of Frame)"));
	DHTgroup=new CMFCPropertyGridProperty(_T("DHT (Define Huffman Table)"));
	SOSgroup=new CMFCPropertyGridProperty(_T("SOS (Start of Scan)"));
	//----------------------

}

void CSpecialVIJPGDlg::OnBnClickedVIJpgInputurlFiledialog()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("JPEG Files (*.jpg;*.jpeg)|*.jpg;*.jpeg|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,_T("jpg"),NULL,NULL,lpszfilter);//TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի��� 
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();

	m_vijpginputurl.SetWindowText(FilePathName);
}


void CSpecialVIJPGDlg::OnBnClickedVIJpgAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}


void CSpecialVIJPGDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnDropFiles(hDropInfo);
	LPTSTR pFilePathName =(LPTSTR)malloc(MAX_URL_LENGTH);
	::DragQueryFile(hDropInfo, 0, pFilePathName,MAX_URL_LENGTH);  // ��ȡ�Ϸ��ļ��������ļ�������ؼ���
	m_vijpginputurl.SetWindowText(pFilePathName);
	::DragFinish(hDropInfo);   // ע����������٣��������ͷ�Windows Ϊ�����ļ��ϷŶ�������ڴ�
	free(pFilePathName);
}


void CSpecialVIJPGDlg::OnSelchangeVIJpgLang()
{
	//�����ļ�·��
	char conf_path[300]={0};
	//���exe����·��
	GetModuleFileNameA(NULL,(LPSTR)conf_path,300);//
	//���exe�ļҼ�·��
	strrchr( conf_path, '\\')[0]= '\0';//
	//_getcwd(realpath,MYSQL_S_LENGTH);
	printf("%s",conf_path);
	strcat(conf_path,"\\configure.ini");
	//д�������ļ�
	switch(m_vijpglang.GetCurSel()){
	case 0:WritePrivateProfileStringA("Settings","language","Chinese",conf_path);break;
	case 1:WritePrivateProfileStringA("Settings","language","English",conf_path);break;
	default:break;
	}
	//�������
	char exe_path[300]={0};
	//���exe����·��
	GetModuleFileNameA(NULL,(LPSTR)exe_path,300);
	ShellExecuteA( NULL,"open",exe_path,NULL,NULL,SW_SHOWNORMAL);
	OnCancel();
}
