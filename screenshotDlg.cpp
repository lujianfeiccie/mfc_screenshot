
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
}

BEGIN_MESSAGE_MAP(CscreenshotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SCREENSHOT, &CscreenshotDlg::OnBnClickedBtnScreenshot)
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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



void CscreenshotDlg::OnBnClickedBtnScreenshot()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxGetMainWnd()->ShowWindow(SW_MINIMIZE );  
    Sleep(500);  
  
    HWND hWnd = ::GetDesktopWindow();//�����Ļ��HWND.  
    HDC hScreenDC = ::GetDC(hWnd);   //�����Ļ��HDC.  
    HDC MemDC = ::CreateCompatibleDC(hScreenDC);  
    RECT rect;   
    ::GetWindowRect(hWnd,&rect);  
    SIZE screensize;  
    screensize.cx=rect.right-rect.left;  
    screensize.cy=rect.bottom-rect.top;  
    HBITMAP hBitmap = ::CreateCompatibleBitmap(hScreenDC,screensize.cx,screensize.cy);  
    HGDIOBJ hOldBMP = ::SelectObject(MemDC,hBitmap);  
    ::BitBlt(MemDC,0,0,screensize.cx,screensize.cy,hScreenDC,rect.left,rect.top,SRCCOPY);  
    ::SelectObject(MemDC,hOldBMP);  
    ::DeleteObject(MemDC);  
    ::ReleaseDC(hWnd,hScreenDC);  
  
  
//  if(this->m_bSaveToFile)  
        this->WriteBmpToFile(hBitmap);  
      
//  if(this->m_bCopyToClip)  
        this->CopyBmpToClipBoard(hBitmap);  
  
//  if(this->m_bOpenMspaint)  
        ::ShellExecute(NULL,L"open",L"mspaint.exe",/*���û�ͼ����*/  
            this->m_str_save_path,  
            NULL,  
            SW_SHOWMAXIMIZED);  
  
    AfxGetMainWnd()->ShowWindow(SW_NORMAL);     //�ָ�������ʾģʽ   

}

void CscreenshotDlg::WriteBmpToFile(HBITMAP hBitmap)
{
	HDC hDC =::CreateDC(L"DISPLAY",NULL,NULL,NULL);   
    int iBits = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);//��ǰ�ֱ�����ÿ��������ռ�ֽ���    
    ::DeleteDC(hDC);  
  
    WORD   wBitCount;   //λͼ��ÿ��������ռ�ֽ���      
    if (iBits <= 1)  
        wBitCount = 1;  
    else if (iBits <= 4)  
        wBitCount = 4;  
    else if (iBits <= 8)  
        wBitCount = 8;  
    else if (iBits <= 24)  
        wBitCount = 24;  
    else  
        wBitCount = iBits;  
              
    DWORD   dwPaletteSize=0;    //��ɫ���С�� λͼ�������ֽڴ�С   
    if (wBitCount <= 8)        
        dwPaletteSize = (1 << wBitCount) *    sizeof(RGBQUAD);      
      
  
    BITMAP  bm;        //λͼ���Խṹ  
    ::GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);    
  
      
    BITMAPINFOHEADER   bi;       //λͼ��Ϣͷ�ṹ       
    bi.biSize            = sizeof(BITMAPINFOHEADER);    
    bi.biWidth           = bm.bmWidth;  
    bi.biHeight          = bm.bmHeight;  
    bi.biPlanes          = 1;  
    bi.biBitCount        = wBitCount;  
    bi.biCompression     = BI_RGB; //BI_RGB��ʾλͼû��ѹ��  
    bi.biSizeImage       = 0;  
    bi.biXPelsPerMeter   = 0;  
    bi.biYPelsPerMeter   = 0;  
    bi.biClrUsed         = 0;  
    bi.biClrImportant    = 0;  
      
    DWORD dwBmBitsSize = ((bm.bmWidth * wBitCount+31)/32) * 4 * bm.bmHeight;      
    HANDLE hDib  = ::GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));  //Ϊλͼ���ݷ����ڴ�  
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);  
    *lpbi = bi;  
      
    HANDLE hPal = ::GetStockObject(DEFAULT_PALETTE);  // �����ɫ��   
    HANDLE  hOldPal=NULL;   
    if (hPal)  
    {  
        hDC = ::GetDC(NULL);  
        hOldPal = SelectPalette(hDC,(HPALETTE)hPal, FALSE);  
        RealizePalette(hDC);  
    }  
    ::GetDIBits(hDC, hBitmap, 0, (UINT) bm.bmHeight,(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,(BITMAPINFO*)lpbi,DIB_RGB_COLORS);// ��ȡ�õ�ɫ�����µ�����ֵ  
    if (hOldPal)//�ָ���ɫ��  
    {  
        SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);  
        RealizePalette(hDC);  
        ::ReleaseDC(NULL, hDC);  
    }     
     
    BITMAPFILEHEADER   bmfHdr; //λͼ�ļ�ͷ�ṹ       
    bmfHdr.bfType = 0x4D42;  // "BM"    // ����λͼ�ļ�ͷ  
    DWORD dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;    
    bmfHdr.bfSize = dwDIBSize;  
    bmfHdr.bfReserved1 = 0;  
    bmfHdr.bfReserved2 = 0;  
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;  
      
    HANDLE hFile = CreateFile(/*m_strFilePath*/this->m_str_save_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);//����λͼ�ļ�     
    DWORD dwWritten;  
    WriteFile(hFile, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);   // д��λͼ�ļ�ͷ  
    WriteFile(hFile, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);// д��λͼ�ļ���������  
      
    GlobalUnlock(hDib);   //���     
    GlobalFree(hDib);  
    CloseHandle(hFile); 
}

void CscreenshotDlg::CopyBmpToClipBoard(HBITMAP hBitmap)
{
	OpenClipboard() ;   //�򿪼����壬����λͼ������������   
    EmptyClipboard();   
    SetClipboardData(CF_BITMAP, hBitmap);  
    CloseClipboard();   //�رռ�����
}