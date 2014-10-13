
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
	CButton m_cbx_max_width;
	CButton m_cbx_max_height;
	CEdit m_edit_max_width;
	CEdit m_edit_max_height;
	CModelConfig *config;
	afx_msg void OnDestroy();


	afx_msg void OnBnClickedCheckMaxWidth();
	afx_msg void OnBnClickedCheckMaxHeight();
};
