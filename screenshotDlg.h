
// screenshotDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"



// CscreenshotDlg �Ի���
class CscreenshotDlg : public CDialogEx
{
// ����
public:
	CscreenshotDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCREENSHOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedBtnModify();
	CEdit m_edit_ctrl;
	CEdit m_edit_alt;
	CEdit m_edit_key;

	CScreenshotToolDlg* dlg;
};
