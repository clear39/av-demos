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

#pragma once

#include "resource.h"
#include "stdafx.h"
#include "loadjpeg.h"
// CSpecialVIJPGDlg �Ի���
class CSpecialVIJPGDlg : public CDialogEx
{
// ����
public:
	CSpecialVIJPGDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SPECIAL_V_I_JPG };

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
	CMFCPropertyGridProperty *SOIgroup;
	CMFCPropertyGridProperty *APP0group;
	CMFCPropertyGridProperty *DQTgroup;
	CMFCPropertyGridProperty *SOF0group;
	CMFCPropertyGridProperty *DHTgroup;
	CMFCPropertyGridProperty *SOSgroup;
	CMFCPropertyGridCtrl m_vijpgbasicinfo;
	CEdit m_vijpginputurl;
	char jpgurl[MAX_URL_LENGTH];
	afx_msg void OnBnClickedVIJpgInputurlOpen();
	int AppendBInfo(char *dst_group,char *property_name,char *value,char *remark);
	int ShowBInfo();
	CEdit m_vijpgconsole;
	CString cinfo;
	int AppendCInfo(char *str);
	CButton m_vijpgoutputdct;
	//	CButton m_vijpgoutputraw;
	CButton m_vijpgoutputy;
	int m_vijpgoutputraw;
	void SystemClear();
	afx_msg void OnBnClickedVIJpgInputurlFiledialog();
	afx_msg void OnBnClickedVIJpgAbout();
	//-----
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//���ض������
	CString text;
	CComboBox m_vijpglang;
	afx_msg void OnSelchangeVIJpgLang();
};
