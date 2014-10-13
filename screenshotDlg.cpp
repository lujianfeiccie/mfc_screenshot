
// screenshotDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "screenshot.h"
#include "screenshotDlg.h"
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


// CscreenshotDlg �Ի���




CscreenshotDlg::CscreenshotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CscreenshotDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CscreenshotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_edit_alt);
	DDX_Control(pDX, IDC_EDIT3, m_edit_key);
	DDX_Control(pDX, IDC_CHECK_MAX_WIDTH, m_cbx_max_width);
	DDX_Control(pDX, IDC_CHECK_MAX_HEIGHT, m_cbx_max_height);
	DDX_Control(pDX, IDC_EDIT_MAX_WIDTH, m_edit_max_width);
	DDX_Control(pDX, IDC_EDIT_MAX_HEIGHT, m_edit_max_height);
}

BEGIN_MESSAGE_MAP(CscreenshotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CscreenshotDlg::OnBnClickedBtnModify)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_MAX_WIDTH, &CscreenshotDlg::OnBnClickedCheckMaxWidth)
	ON_BN_CLICKED(IDC_CHECK_MAX_HEIGHT, &CscreenshotDlg::OnBnClickedCheckMaxHeight)
END_MESSAGE_MAP()


// CscreenshotDlg ��Ϣ�������

BOOL CscreenshotDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_edit_ctrl.SetReadOnly();
	m_edit_ctrl.SetWindowTextW(L"Ctrl");
	m_edit_alt.SetReadOnly();
	m_edit_alt.SetWindowTextW(L"Alt");

	config = CModelConfigTool::Load();
	m_edit_key.SetWindowTextW(config->m_edit_key);	

	m_cbx_max_height.SetCheck(config->m_cbx_max_height);
	m_cbx_max_width.SetCheck(config->m_cbx_max_width);

	OnBnClickedCheckMaxWidth();
	OnBnClickedCheckMaxHeight();

	m_edit_max_height.SetWindowTextW(config->m_edit_max_height);
	m_edit_max_width.SetWindowTextW(config->m_edit_max_width);

	dlg = new CScreenshotToolDlg;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CscreenshotDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CscreenshotDlg::OnPaint()
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
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CscreenshotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




BOOL CscreenshotDlg::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
		case WM_KEYDOWN:
		{
			Util::LOG(L"lParam=%c",pMsg->wParam);
			CString key;
			m_edit_key.GetWindowTextW(key);
			if(key == pMsg->wParam )
			{
				if(dlg==NULL)
				{
					dlg = new CScreenshotToolDlg;
				}
				if(m_cbx_max_width.GetCheck())
				{
					CString max_width;
					m_edit_max_width.GetWindowTextW(max_width);
					dlg->m_max_width = _wtoi(max_width);
				}
				else
				{
					dlg->m_max_width = -1;
				}
				if(m_cbx_max_height.GetCheck())
				{
					CString max_height;
					m_edit_max_height.GetWindowTextW(max_height);
					dlg->m_max_height = _wtoi(max_height);
				}
				else
				{
					dlg->m_max_height = -1;
				}
				dlg->DoModal();
				delete dlg;
				dlg=NULL;;
				
				return TRUE;
			}
		}
		break;
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 

return CDialog::PreTranslateMessage(pMsg);
}

void CscreenshotDlg::OnBnClickedBtnModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CscreenshotDlg::OnDestroy()
{
	config->m_cbx_max_height = m_cbx_max_height.GetCheck();
	config->m_cbx_max_width = m_cbx_max_width.GetCheck();
	m_edit_key.GetWindowTextW(config->m_edit_key);
	m_edit_max_height.GetWindowTextW(config->m_edit_max_height);
	m_edit_max_width.GetWindowTextW(config->m_edit_max_width);
	CModelConfigTool::Save(config);
	delete config;
	config = NULL;
	if(dlg!=NULL)
	{
		delete dlg;
	}
	dlg = NULL;
	CDialog::OnDestroy();
}

void CscreenshotDlg::OnBnClickedCheckMaxWidth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_cbx_max_width.GetCheck())
	{
		m_edit_max_width.EnableWindow();
	}
	else
	{
		m_edit_max_width.EnableWindow(FALSE);
	}
}


void CscreenshotDlg::OnBnClickedCheckMaxHeight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_cbx_max_height.GetCheck())
	{
		m_edit_max_height.EnableWindow();
	}
	else
	{
		m_edit_max_height.EnableWindow(FALSE);
	}
}
