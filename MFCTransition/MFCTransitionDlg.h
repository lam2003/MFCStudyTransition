
// MFCTransitionDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "FTPTypeDef.h"
#include "Markup.h"
#include "ClientSocket.h"
#include "afxcmn.h"

#define BAUDRATE 9600
#define SERVER_PORT 21005

#define MAXBUFFER 512
#define PROTOCOL_LEN 5

#define D 13
#define E 14
#define F 15

// CMFCTransitionDlg �Ի���
class CMFCTransitionDlg : public CDialogEx
{
// ����
public:
	CMFCTransitionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCTRANSITION_DIALOG };

	//LoginDlg m_loginDlg;
	ClientSocket *m_pClient;

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
	int m_d=-1, m_e=-1, m_f=-1;//d��ʾ�ϳɻ��棬e��ʾ¼��ģʽ��f��ʾ����ģʽ,���ص�״̬
	int up_d = -1, up_e = -1, up_f = -1;//������״̬
	int dn_d = -1, dn_e = -1, dn_f = -1;//����״̬
	UCHAR m_val;
	char isSet = -1;
	BOOL isUpdata = FALSE;

	BOOL m_connet, m_spConnect;  //m_connect���������Ƿ����ӣ�m_spConnect���������Ƿ�����
	volatile HANDLE m_hCom; //���ھ��
	OVERLAPPED m_osRead, m_osWrite; //�����ص���/д
	CWinThread *m_pThread;//���������߳�
	volatile HANDLE m_hPostMsgEvent;
	volatile HANDLE m_hNewCommandEvent;
	static UINT CommProc(LPVOID pParam); //���ڴ����߳�
	BOOL OpenCom(CString port);
	BOOL CloseCom();
	BOOL ConfigConnection();
	void OnAPICommNotify();
	long WriteComm(unsigned char *pBuf, long dwlength);
	LRESULT ParseSerialPack(WPARAM wParam, LPARAM lParam);
	LRESULT Send2SerialPort(WPARAM wParam, LPARAM lParam);

	int ParseXmlFile();
	BOOL CreateLoginXml(::CMarkup& xml, int &nRes);
	BOOL SetManageMode(UINT mode);
	BOOL SetRecordStatus(int recType, CString roomName, CString teacherName, CString courseName, CString notes);
	BOOL SetOrGetMode(BOOL flag, int sourceNum, int width, int height, int mplayout, int FrameRate, int bitRate);
	BOOL SendHearBeat(int rcdStatus, int rcdTime, int mpMode, int mpLayout);
	LRESULT Reconnect(WPARAM wParam, LPARAM lParam);
	BOOL CheckUpDown(int up, int dn){ return up == dn; };
	
	void UpdateLog(CString str);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox m_comboCom;
	CButton m_btnCom;
	CEdit m_editBaud;
	CButton m_btnConnect;
	afx_msg void OnBnClickedButtonConnect();
	CIPAddressCtrl m_ipServer;
	CEdit m_editLog;
	CString m_ipStr;
	afx_msg void OnBnClickedButtonCom();
};