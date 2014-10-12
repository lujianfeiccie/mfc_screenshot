#pragma once

#include "MyTracker.h"
#include "MyEdit.h"
#include "Resource.h"
// CScreenshotToolDlg �Ի���

class CScreenshotToolDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScreenshotToolDlg)

public:
	CScreenshotToolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CScreenshotToolDlg();
	// Generated message map functions
	//{{AFX_MSG(CCatchScreenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
// �Ի�������
	enum { IDD = IDD_SCREENSHOTTOOLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	HICON m_hIcon;

	int m_xScreen;
	int m_yScreen;
	
	BOOL m_bShowMsg;                //��ʾ��ȡ���δ�С��Ϣ
	BOOL m_bDraw;                   //�Ƿ�Ϊ��ȡ״̬
	BOOL m_bFirstDraw;              //�Ƿ�Ϊ�״ν�ȡ
	BOOL m_bQuit;                   //�Ƿ�Ϊ�˳�
	CPoint m_startPt;				//��ȡ�������Ͻ�
	CMyTracker m_rectTracker;     //��Ƥ����
	
	CBrush m_brush;					//
    HCURSOR m_hCursor;              //���
	CBitmap * m_pBitmap;            //����λͼ
	
	CRgn m_rgn;						//������������

public:
	HBITMAP CopyScreenToBitmap(LPRECT lpRect,BOOL bSave=FALSE);   //�������浽λͼ
	void DrawTip();                            //��ʾ������ʾ��Ϣ
	void DrawMessage(CRect &inRect,CDC * pDC);       //��ʾ��ȡ������Ϣ
	void PaintWindow();               //�ػ�����
	void ChangeRGB();	
	
	BOOL isShown;
	afx_msg void OnDestroy();

	int m_max_width;
	int m_max_height;
};
