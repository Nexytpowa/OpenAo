// AtumLauncherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AtumLauncher.h"
#include "AtumLauncherDlg.h"
#include <iostream>
#include <strstream>
#include <fstream>
#include "dbgout_c.h"
#include "ftpdownload.h"
#include <direct.h>
#include "PreServerIPDlg.h"
#include "md5_lib_src.h"
#include "LoginSuccessDlg.h"
#include "Wininet.h"
#include "ZipArchive/ZipArchive.h"
// ysw
#include <afxhtml.h>
#include "MGameDecryption.h"
#include "AtumError.h"
#include "HttpManager.h"					// 2007-01-08 by cmkwon
#include "screenkeyboarddlg.h"				// 2007-09-10 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� -
#include "DlgGuardAgreement.h"				// 2009-08-31 by cmkwon, Gameforge4D ���Ӱ��� ����â ���� - 

#include <thread>



// 2012-03-21 by hskim, �ٽ��� ��� �߰� [�ڵ� ������Ʈ/�ɼ� �߰�/����͸� �ý���]
#ifdef S_HACK_SHIELD_AUTO_UPDATE_HSKIM
#include "ConfigHackShield.h"

#pragma comment(lib, "HSUpChk.lib")
#pragma comment(lib, "version.lib")
#include "Security/HSUpChk.h"
#endif
// 2012-03-21 by hskim, �ٽ��� ��� �߰� [�ڵ� ������Ʈ/�ɼ� �߰�/����͸� �ý���]

#include <MachineID.h>	// 2016-01-09 Future, MAC Blocking

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NOTICE_FILE_NAME "notice.txt"
#define DELFILELIST_FILE_NAME "deletefilelist.txt"

#define STRING_SERVER_GROUP_NAME_DELIMIT				" "
#define TICKGAP_NETWORK_STATE_WORST_PING_TICK			1500		// 2007-06-21 by cmkwon, ��� Ping �ӵ��� �����ϵ��� ������

struct SWINDOW_DEGREE
{
	char	*szWindowDegreeName;
	int		nCX;
	int		nCY;
	int		nDegree;
};

// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �߰���
SWINDOW_DEGREE g_pWindowDegreeList[] =
{
	{STRMSG_WINDOW_DEGREE_1024x768_LOW,		1024, 768, 0},
	{STRMSG_WINDOW_DEGREE_1024x768_MEDIUM,	1024, 768, 1},
	{STRMSG_WINDOW_DEGREE_1024x768_HIGH,	1024, 768, 2},

	{STRMSG_WINDOW_DEGREE_W1280x720_LOW,	1280, 720, 0},
	{STRMSG_WINDOW_DEGREE_W1280x720_MEDIUM,	1280, 720, 1},
	{STRMSG_WINDOW_DEGREE_W1280x720_HIGH,	1280, 720, 2},
	
	{STRMSG_WINDOW_DEGREE_W1280x800_LOW,	1280, 800, 0},
	{STRMSG_WINDOW_DEGREE_W1280x800_MEDIUM,	1280, 800, 1},
	{STRMSG_WINDOW_DEGREE_W1280x800_HIGH,	1280, 800, 2},
	
	{STRMSG_WINDOW_DEGREE_1280x960_LOW,		1280, 960, 0},
	{STRMSG_WINDOW_DEGREE_1280x960_MEDIUM,	1280, 960, 1},
	{STRMSG_WINDOW_DEGREE_1280x960_HIGH,	1280, 960, 2},
	
	{STRMSG_WINDOW_DEGREE_1280x1024_LOW,	1280, 1024, 0},
	{STRMSG_WINDOW_DEGREE_1280x1024_MEDIUM,	1280, 1024, 1},
	{STRMSG_WINDOW_DEGREE_1280x1024_HIGH,	1280, 1024, 2},
	{ "1360x768 (low)", 1360, 768, 0 },
	{ "1360x768 (medium)", 1360, 768, 1 },
	{ "1360x768 (high)", 1360, 768, 2 },

	{ "1366x768 (low)", 1366, 768, 0 },
	{ "1366x768 (medium)", 1366, 768, 1 },
	{ "1366x768 (high)", 1366, 768, 2 },
	// 2008-02-11 by cmkwon, �ػ� �߰�(1440x900) - 
	{STRMSG_WINDOW_DEGREE_1440x900_LOW,		1440, 900, 0},
	{STRMSG_WINDOW_DEGREE_1440x900_MEDIUM,	1440, 900, 1},
	{STRMSG_WINDOW_DEGREE_1440x900_HIGH,	1440, 900, 2},

	{STRMSG_WINDOW_DEGREE_W1600x900_LOW,	1600, 900, 0},
	{STRMSG_WINDOW_DEGREE_W1600x900_MEDIUM,	1600, 900, 1},
	{STRMSG_WINDOW_DEGREE_W1600x900_HIGH,	1600, 900, 2},
	{ "1600x1024 (low)", 1600, 1024, 0 },
	{ "1600x1024 (medium)", 1600, 1024, 1 },
	{ "1600x1024 (high)", 1600, 1024, 2 },	
	{STRMSG_WINDOW_DEGREE_1600x1200_LOW,	1600, 1200, 0},
	{STRMSG_WINDOW_DEGREE_1600x1200_MEDIUM,	1600, 1200, 1},
	{STRMSG_WINDOW_DEGREE_1600x1200_HIGH,	1600, 1200, 2},

	{STRMSG_WINDOW_DEGREE_1680x1050_LOW		,	1680, 1050, 0},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{STRMSG_WINDOW_DEGREE_1680x1050_MEDIUM	,	1680, 1050, 1},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{STRMSG_WINDOW_DEGREE_1680x1050_HIGH	,	1680, 1050, 2},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{ "1768x992 (low)", 1768, 992, 0 },
	{ "1768x992 (medium)", 1768, 992, 1 },
	{ "1768x992 (high)", 1768, 992, 2 },
	{STRMSG_WINDOW_DEGREE_1920x1080_LOW		,	1920, 1080, 0},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{STRMSG_WINDOW_DEGREE_1920x1080_MEDIUM	,	1920, 1080, 1},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{STRMSG_WINDOW_DEGREE_1920x1080_HIGH	,	1920, 1080, 2},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 

	{STRMSG_WINDOW_DEGREE_1920x1200_LOW		,	1920, 1200, 0},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{STRMSG_WINDOW_DEGREE_1920x1200_MEDIUM	,	1920, 1200, 1},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{STRMSG_WINDOW_DEGREE_1920x1200_HIGH	,	1920, 1200, 2},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{ "Borderless (low)", 0, 0, 0 },
	{ "Borderless (medium)", 0, 0, 1 },
	{ "Borderless (high)", 0, 0, 2 },

	{NULL, 0, 0, 0}		// 2007-12-28 by cmkwon, ���� �����ϱ� ����
};



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


#define ICON_IMAGE_ID		IDB_ICON_VTC

/////////////////////////////////////////////////////////////////////////////
// CAtumLauncherDlg dialog
// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - ���� ������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){   return 0;}

CAtumLauncherDlg::CAtumLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent), m_ctrlServerList(IDB_SERVERUSER_VTC, IDB_LISTBG_VTC, ICON_IMAGE_ID)
{
	//{{AFX_DATA_INIT(CAtumLauncherDlg)
	m_nServer = -1;
	m_szAccountName = _T("");
	m_szPassword = _T("");
	m_staticNumFileCtrl = _T("");
	m_nWindowDegree = 0;
	m_ctlbWindowMode = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pUpdateWinsocket = 0;
	m_nOldSel = 0;
//	m_pFieldWinsocket = 0;
	m_bControlEnabled = TRUE;

	m_StaticBrushBlack.CreateSolidBrush(RGB(0, 0, 0));
	m_StaticBrushGray.CreateSolidBrush(RGB(23, 23, 23));
	m_ListBrushGray.CreateSolidBrush(RGB(212, 208, 200));
	
	

/*	/// 2012-05-10 by jhseol, ���þ� - EP4 �ö���鼭 ��� ����. �ּ�ó��
	// 2008-12-17 by ckPark ���þ� ����
	// ���þƾƴ� ����� �������� �Ѵ�
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	m_listBrush.CreateStockObject(NULL_BRUSH);
#else
	m_listBrush.CreateSolidBrush(RGB(29,29,40));
#endif
	// end 2008-12-17 by ckPark ���þ� ����
*/
	m_listBrush.CreateSolidBrush(RGB(29,29,40));



	m_progressBk.CreateSolidBrush(RGB(79,79,79));	
	m_progressBar.CreateSolidBrush(RGB(99, 123, 246));	

	//m_pUpdateFTPManager	= NULL;
	m_pHost = NULL;
	m_pHttpManager		= NULL;				// 2007-01-08 by cmkwon
	SetFTPUpdateState(UPDATE_STATE_INIT);


	strcpy(m_szLocalIP, "127.0.0.1");

	m_nBirthYear		= 0;				// 2007-06-05 by cmkwon

	///////////////////////////////////////////////////////////////////////////////
	// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ 
	m_nMaxNetworkCheckCount		= 5;
	m_nCurNetworkCheckCount		= -1;
	m_dwNetworkCheckSendTick	= 0;
	m_dwSumPacketTickGap		= 0;

	///////////////////////////////////////////////////////////////////////////////
	// 2007-09-07 by cmkwon, ��Ʈ�� ��ó �������̽� ���� - �ʱ�ȭ ��ġ ����
	m_Cur_Percent				= 0;
	m_SelectFlag				= FALSE;	
	m_bCancelFlag				= FALSE;
	m_bProcessingVersionUpdate	= FALSE;
	m_bShowPreServerIPDlg		= TRUE;

	// 2007-09-11 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� -
	m_pScreenKeyboardDlg			= NULL;
	m_pInputEditFromScreenKeyboard	= NULL;
	m_bHideScreenKeyboardByScreenKeyboardWindow	= FALSE; // 2007-09-18 by cmkwon, ȭ��Ű���� ���� - 

	m_vectServerGroupList.clear();		// 2008-02-14 by cmkwon, ��ó���� �����׷� ���� ������ ���� ���࿡ ������ ������ ���� - 

	m_bGuardAgreementReg		= FALSE;	// 2009-08-31 by cmkwon, Gameforge4D ���Ӱ��� ����â ���� -
}

void CAtumLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_REMEMBER_ID, m_ctlBtnRememberID);
	DDX_Control(pDX, IDC_COMBO_SERVER_LIST, m_comboServerList);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_ctrlEditAccount);
	DDX_Control(pDX, IDC_LIST, m_ctrlServerList);					// 2006-05-02 by ispark
	DDX_Control(pDX, IDC_PROGRESS1, m_progressCtrl);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_szAccountName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_szPassword);
	DDV_MaxChars(pDX, m_szPassword, 14);
	DDX_Text(pDX, IDC_DOWNLOAD_FILENUM, m_staticNumFileCtrl);
	DDX_CBIndex(pDX, IDC_COMBO_WINDOW_DEGREE_LAUNCHER, m_nWindowDegree);
	DDX_Check(pDX, IDC_CHECK_WINDOWS_MODE, m_ctlbWindowMode);
	DDX_Control(pDX, IDGO, m_KbcGO);
	DDX_Control(pDX, IDJOIN, m_kbcBtnJoin);
	DDX_Control(pDX, IDC_BTN_HOMEPAGE, m_bmpBtnHomepage);

	DDX_Control(pDX, IDC_CHECK_V_SYNC, m_ctlChckVsync);
}

BEGIN_MESSAGE_MAP(CAtumLauncherDlg, CDialog)
	//{{AFX_MSG_MAP(CAtumLauncherDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDJOIN, OnJoin)
	ON_BN_CLICKED(IDSECRET, OnSecret)
	ON_BN_CLICKED(IDEND, OnEnd)
	ON_BN_CLICKED(IDDECA, OnDeca)
	ON_BN_CLICKED(IDBATTAL, OnBattal)
	ON_BN_CLICKED(IDSHARIN, OnSharin)
	ON_BN_CLICKED(IDPHILON, OnPhilon)
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDCAN, OnCan)
	ON_BN_CLICKED(IDMIN, OnMin)
	ON_EN_SETFOCUS(IDC_EDIT_ACCOUNT, OnSetfocusEditAccount)
	ON_EN_SETFOCUS(IDC_EDIT_PASSWORD, OnSetfocusEditPassword)
	ON_BN_CLICKED(IDC_BTN_VIEW_SCREEN_KEYBOARD, OnBtnViewScreenKeyboard)
	ON_BN_CLICKED(IDC_BTN_HOMEPAGE, OnBtnHomepage)
	ON_BN_CLICKED(IDGO, OnOk)
	ON_BN_CLICKED(IDC_CHECK_WINDOWS_MODE, OnCheckWindowsMode)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_PACKET_NOTIFY, OnSocketNotify)
	ON_MESSAGE(WM_ASYNC_EVENT, OnAsyncSocketMessage)
	ON_MESSAGE(WM_DOWNLOAD_GAMEFILES_DONE, OnDownLoadGamefilesDone)

	ON_MESSAGE(WM_UPDATEFILE_DOWNLOAD_ERROR, OnUpdateFileDownloadError)
	ON_MESSAGE(WM_UPDATEFILE_DOWNLOAD_INIT, OnUpdateFileDownloadInit)
	ON_MESSAGE(WM_UPDATEFILE_DOWNLOAD_PROGRESS, OnUpdateFileDownloadProgress)
	ON_MESSAGE(WM_UPDATEFILE_DOWNLOAD_OK, OnUpdateFileDownloadOK)
	ON_MESSAGE(WM_UPDATE_VTCGUARD_OK, OnUpdateVTCGuardOK)		// 2012-02-09 by hskim, ��Ʈ�� X-Trap -> VTC ����� ����
	ON_BN_CLICKED(IDC_CHECK_V_SYNC, &CAtumLauncherDlg::OnBnClickedCheckVSync)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAtumLauncherDlg message handlers


BOOL CAtumLauncherDlg::ReadNoticeFile()
{
	char	szLine[10000];
	CString strTemp;

	m_NoticeEdit = "";

	FILE		*fp;
#ifdef _ATUM_DEVELOP
	fp = fopen(m_szExecutePathReg + NOTICE_FILE_NAME, "r");
#else
	fp = fopen(NOTICE_FILE_NAME, "r");
#endif

	if (fp == NULL)
	{
		//szLine[0] = '\0';
		//strcpy(temp, m_NoticeEdit);
		//m_NoticeEdit.Format("%s%s",temp, szLine);
	}
	else
	{
		while(!feof(fp))
		{
			memset(szLine, 0x00, sizeof(szLine));
			if(fgets(szLine, 10000, fp)==NULL)
			{
				break;
			}

			szLine[strlen(szLine)-1] = 0;
			strTemp = m_NoticeEdit;
			m_NoticeEdit.Format("%s\r\n%s", strTemp, szLine);
		}
		fclose(fp);
	}

	// 2007-09-07 by cmkwon, ������� �ʴ� ���̹Ƿ� ��Ʈ���� ������
	//GetDlgItem(IDC_NOTICE)->SetWindowText(m_NoticeEdit);
	return TRUE;
}

#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
	#define EXE2_LAUNCHER_BG_SIZE_X					650
	#define EXE2_LAUNCHER_BG_SIZE_Y					70
#else
	#define EXE2_LAUNCHER_BG_SIZE_X					1030
#define EXE2_LAUNCHER_BG_SIZE_Y					524
#endif

	#define EXE2_BG_TITLE_BAR_SIZE_X				0	// Ÿ��Ʋ�� �̹��� Width
	#define EXE2_BG_TITLE_BAR_SIZE_Y				0						// Ÿ��Ʋ�� Height

	#define EXE2_BG_BACKGROUND_IMAGE_SIZE_X			EXE2_LAUNCHER_BG_SIZE_X									// ��� �̹��� Width
	#define EXE2_BG_BACKGROUND_IMAGE_SIZE_Y			(EXE2_LAUNCHER_BG_SIZE_Y - EXE2_BG_TITLE_BAR_SIZE_Y)	// ��� �̹��� Height

#define EXE2_BG_WEBCONTROL_POS_X				221		// �������� ��Ʈ�� ��ġ X
#define EXE2_BG_WEBCONTROL_POS_Y				118		// �������� ��Ʈ�� ��ġ Y
#define EXE2_BG_WEBCONTROL_WIDTH				517		// �������� ��Ʈ�� Width
#define EXE2_BG_WEBCONTROL_HEIGHT				337		// �������� ��Ʈ�� Height
	
#define EXE2_BG_RESOLUTION_COMBOBOX_POS_X		760		// ??? ?? Combo Box ?? X
#define EXE2_BG_RESOLUTION_COMBOBOX_POS_Y		425		// ??? ?? Combo Box ?? Y
#define EXE2_BG_RESOLUTION_COMBOBOX_WIDTH		240		// ??? ?? Combo Box Width
#define EXE2_BG_RESOLUTION_COMBOBOX_HEIGHT		16		// ??? ?? Combo Box Height

#if defined(S_LAUNCHER_USE_ID_PASSWORD_HSKIM)
	#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X		895		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ X
	#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y		401		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ Y

	#define EXE2_BG_ACCOUNTNAME_EDIT_POS_X			782		// AccountName Edit Box ��ġ X
	#define EXE2_BG_ACCOUNTNAME_EDIT_POS_Y			198		// AccountName Edit Box ��ġ Y
	#define EXE2_BG_ACCOUNTNAME_EDIT_WIDTH			200		// AccountName Edit Box Width
	#define EXE2_BG_ACCOUNTNAME_EDIT_HEIGHT			19		// AccountName Edit Box Height

	#define EXE2_BG_PASSWORD_EDIT_POS_X				782		// Password Edit Box ��ġ X
	#define EXE2_BG_PASSWORD_EDIT_POS_Y				254		// Password Edit Box ��ġ Y
	#define EXE2_BG_PASSWORD_EDIT_WIDTH				200		// Password Edit Box Width
	#define EXE2_BG_PASSWORD_EDIT_HEIGHT			19		// Password Edit Box Height

	#define EXE2_BG_GAMESTART_BTN_POS_X				748		// GameStart Button ��ġ X
	#define EXE2_BG_GAMESTART_BTN_POS_Y				330		// GameStart Button ��ġ Y
	#define EXE2_BG_GAMESTART_BTN_WIDTH				268		// GameStart Button Width
	#define EXE2_BG_GAMESTART_BTN_HEIGHT			55		// GameStart Button Height

#if defined(GAMEFORGE4D_ENG) || defined(GAMEFORGE4D_FRANCE) || defined(WIKIGAMES_ENG) || defined(DEVX)
	#define EXE2_BG_REMEMBERID_CHECKBOX_POS_X		782		// 2013-03-25 by jhseol, �������� ���� ID üũ��ư ��ġ ���� ���� ��ġ(689)���� -20 ��ŭ
#else
	#define EXE2_BG_REMEMBERID_CHECKBOX_POS_X		680		// Remember ID CheckBox ��ġ X
#endif
	#define EXE2_BG_REMEMBERID_CHECKBOX_POS_Y		285		// Remember ID CheckBox ��ġ Y
	#define EXE2_BG_REMEMBERID_CHECKBOX_WIDTH		15		// Remember ID CheckBox Width
	#define EXE2_BG_REMEMBERID_CHECKBOX_HEIGHT		15		// Remember ID CheckBox Height
#else
	#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X		690		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ X
	#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y		456		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ Y

		#define EXE2_BG_ACCOUNTNAME_EDIT_POS_X			666		// AccountName Edit Box ��ġ X
		#define EXE2_BG_ACCOUNTNAME_EDIT_POS_Y			518		// AccountName Edit Box ��ġ Y
		#define EXE2_BG_ACCOUNTNAME_EDIT_WIDTH			117		// AccountName Edit Box Width
		#define EXE2_BG_ACCOUNTNAME_EDIT_HEIGHT			15		// AccountName Edit Box Height

		#define EXE2_BG_PASSWORD_EDIT_POS_X				666		// Password Edit Box ��ġ X
		#define EXE2_BG_PASSWORD_EDIT_POS_Y				534		// Password Edit Box ��ġ Y
		#define EXE2_BG_PASSWORD_EDIT_WIDTH				117		// Password Edit Box Width
		#define EXE2_BG_PASSWORD_EDIT_HEIGHT			15		// Password Edit Box Height	

	#define EXE2_BG_GAMESTART_BTN_POS_X				544		// GameStart Button ��ġ X
	#define EXE2_BG_GAMESTART_BTN_POS_Y				307		// GameStart Button ��ġ Y
	#define EXE2_BG_GAMESTART_BTN_WIDTH				256		// GameStart Button Width
	#define EXE2_BG_GAMESTART_BTN_HEIGHT			143		// GameStart Button Height

	#define EXE2_BG_REMEMBERID_CHECKBOX_POS_X		666		// Remember ID CheckBox ��ġ X
	#define EXE2_BG_REMEMBERID_CHECKBOX_POS_Y		480		// Remember ID CheckBox ��ġ Y
	#define EXE2_BG_REMEMBERID_CHECKBOX_WIDTH		13		// Remember ID CheckBox Width
	#define EXE2_BG_REMEMBERID_CHECKBOX_HEIGHT		13		// Remember ID CheckBox Height
	#endif

#define EXE2_BG_WINDOWSMODE_CHECKBOX_WIDTH		15		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box Width
#define EXE2_BG_WINDOWSMODE_CHECKBOX_HEIGHT		15		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box Height

#define EXE2_BG_SERVERLIST_BOX_POS_X			782		// ServerList Box ��ġ X
#define EXE2_BG_SERVERLIST_BOX_POS_Y			128		// ServerList Box ��ġ Y
#define EXE2_BG_SERVERLIST_BOX_WIDTH			198		// ServerList Box Width
#define EXE2_BG_SERVERLIST_BOX_HEIGHT			27		// ServerList Box Height

#define EXE2_BG_SERVERLIST_ITEM_BG_WIDTH		198		// ServerList Item Background Width
#define EXE2_BG_SERVERLIST_ITEM_BG_HEIGHT		27		// ServerList Item Background Height

#define EXE2_BG_SERVERLIST_ITEM_ICON_POS_X		99996		// ServerList Item Icon ��ġ X
#define EXE2_BG_SERVERLIST_ITEM_ICON_POS_Y		99999		// ServerList Item Icon ��ġ Y
#define EXE2_BG_SERVERLIST_ITEM_ICON_WIDTH		16		// ServerList Item Icon Width
#define EXE2_BG_SERVERLIST_ITEM_ICON_HEIGHT		18		// ServerList Item Icon Height

#define EXE2_BG_MINIMIZED_BTN_POS_X				753		// Minimized Button ��ġ X
		#define EXE2_BG_MINIMIZED_BTN_POS_Y				10		// Minimized Button ��ġ Y
#define EXE2_BG_MINIMIZED_BTN_WIDTH				21		// Minimized Button Width
#define EXE2_BG_MINIMIZED_BTN_HEIGHT			18		// Minimized Button Height
		#define EXE2_BG_CANCEL_BTN_POS_X				783		// Cancel Button ��ġ X
		#define EXE2_BG_CANCEL_BTN_POS_Y				10		// Cancel Button ��ġ Y
#define EXE2_BG_CANCEL_BTN_WIDTH				21		// Cancel Button Width
#define EXE2_BG_CANCEL_BTN_HEIGHT				18		// Cancel Button Height

#if !defined(SERVICE_TYPE_JAPANESE_SERVER_1)
#define EXE2_BG_UPDATE_PROGRESS_BAR_POS_X		230		// Update Progress Bar ��ġ X
#define EXE2_BG_UPDATE_PROGRESS_BAR_POS_Y		490		// Update Progress Bar ��ġ Y = (EXE2_LAUNCHER_BG_SIZE_Y - 23)
#define EXE2_BG_UPDATE_PROGRESS_BAR_WIDTH		775		// Update Progress Bar Width = (EXE2_LAUNCHER_BG_SIZE_X - 2*EXE2_BG_UPDATE_PROGRESS_BAR_POS_X)
#define EXE2_BG_UPDATE_PROGRESS_BAR_HEIGHT		13		// Update Progress Bar Height

#define EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X		230		// Download file info static control ��ġ X
#define EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y		475		// Download file info static control ��ġ Y
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_WIDTH		200		// Download file info static control Width
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_HEIGHT		13		// Download file info static control Height
	#define EXE2_BG_DOWNLOAD_FILE_FONT_SIZE			12		// Download file info static control font Size
	#define EXE2_BG_DOWNLOAD_FILE_FONT_WEIGHT		FW_NORMAL	// Download file info static control font ����
#else
	#define EXE2_BG_UPDATE_PROGRESS_BAR_POS_X		42		// Update Progress Bar ��ġ X
	#define EXE2_BG_UPDATE_PROGRESS_BAR_POS_Y		36		// Update Progress Bar ��ġ Y = (EXE2_LAUNCHER_BG_SIZE_Y - 23)
	#define EXE2_BG_UPDATE_PROGRESS_BAR_WIDTH		574		// Update Progress Bar Width = (EXE2_LAUNCHER_BG_SIZE_X - 2*EXE2_BG_UPDATE_PROGRESS_BAR_POS_X)
	#define EXE2_BG_UPDATE_PROGRESS_BAR_HEIGHT		16		// Update Progress Bar Height

	#define EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X		63		// Download file info static control ��ġ X
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y		14		// Download file info static control ��ġ Y
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_WIDTH		140		// Download file info static control Width
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_HEIGHT		13		// Download file info static control Height
	#define EXE2_BG_DOWNLOAD_FILE_FONT_SIZE			12		// Download file info static control font Size
	#define EXE2_BG_DOWNLOAD_FILE_FONT_WEIGHT		FW_NORMAL	// Download file info static control font ����
#endif

	#define EXE2_BG_DOWNLOAD_FILE_FONT_COLOR		RGB(255, 255, 0)	// Download file info static control font Color

#if !defined(SERVICE_TYPE_JAPANESE_SERVER_1)
#define EXE2_BG_UPDATE_INFO_STATIC_POS_X		340		// Update info static control ��ġ X
#define EXE2_BG_UPDATE_INFO_STATIC_POS_Y		475		// Update info static control ��ġ Y
	#define EXE2_BG_UPDATE_INFO_STATIC_WIDTH		290		// Update info static control Width
	#define EXE2_BG_UPDATE_INFO_STATIC_HEIGHT		13		// Update info static control Height
	#define EXE2_BG_UPDATE_INFO_FONT_SIZE			12		// Update info static control font Size
	#define EXE2_BG_UPDATE_INFO_FONT_WEIGHT			FW_NORMAL	// Update info static control font ����
#else
	#define EXE2_BG_UPDATE_INFO_STATIC_POS_X		163		// Update info static control ��ġ X
	#define EXE2_BG_UPDATE_INFO_STATIC_POS_Y		14		// Update info static control ��ġ Y
	#define EXE2_BG_UPDATE_INFO_STATIC_WIDTH		422		// Update info static control Width
	#define EXE2_BG_UPDATE_INFO_STATIC_HEIGHT		13		// Update info static control Height
	#define EXE2_BG_UPDATE_INFO_FONT_SIZE			12		// Update info static control font Size
	#define EXE2_BG_UPDATE_INFO_FONT_WEIGHT			FW_NORMAL	// Update info static control font ����
#endif

	#define EXE2_BG_UPDATE_INFO_FONT_COLOR			RGB(255, 255, 0)	// Update info static control font Color

BOOL CAtumLauncherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// �۾� ǥ���ٿ� ���α׷��� ǥ��
	AfxGetApp()->m_pMainWnd->SetWindowText(STRMSG_WINDOW_TEXT);
	// �۾� ǥ���ٿ� ������ ǥ��
	ModifyStyle(0,WS_SYSMENU);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	///////////////////////////////////////////////////////////////////////////
	// TODO: Add extra initialization here

	CWinSocket::SocketInit();		// Initialize winsock 2.0

	this->MoveWindow2Center();	// 2007-09-07 by cmkwon, ��Ʈ�� ��ó �������̽� ���� - ȭ�� �߾����� ��ġ
	RECT rtBG;
	this->GetClientRect(&rtBG);

	// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - ���� �ػ� ����Ʈ �ʱ�ȭ
	this->InitSupportedWindowResolutionList();		
	
	///////////////////////////////////////////////////////////////////////////////
	// 2007-05-07 by cmkwon, �ػ� ������ �� ���� ���� �����ϱ� ����
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER);
	if(pComboBox)
	{
		this->InsertWindowDegreeList(pComboBox, m_ctlbWindowMode);

		int nIdx = this->FindWindowDegreeComboBoxIndex(pComboBox, (LPSTR)(LPCSTR)m_csWindowsResolutionReg);
		nIdx = max(0, nIdx);
		pComboBox->SetCurSel(nIdx);

	}
	
    m_fontServerGroupListBox.CreateFont(16, 0, 0, 0, SG_BOX_FONT_WEIGHT, 0, FALSE, FALSE, SG_BOX_FONT_CHARSET, OUT_DEFAULT_PRECIS,
							  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH , SG_BOX_FONT_FACENAME);    // "System" Font�� ��ǥ���� Fixed Font�Ӵ�.
    GetDlgItem(IDC_LIST)->SetFont(&m_fontServerGroupListBox);

	
	m_bitmapBtnCancel.AutoLoad(IDCAN, this);
	m_bitmapBtnMin.AutoLoad(IDMIN, this);
// 2008-01-08 by cmkwon, Yedang-Global ������Ʈ�� �߰�
//#if defined(_GLOBAL_ENG_SERVER)			// 2006-09-07 by cmkwon, ����(#ifdef _VTC_VIET_SERVER --> #ifndef _GLOBAL_ENG_SERVER)
//	m_KbcGO.SetBmpButtonImage(IDB_GOBTN, RGB(0,0,255));
//#elif defined(_KOREA_SERVER_2)		// 2006-10-02 by cmkwon
#if defined(S_LAUNCHER_USE_ID_PASSWORD_HSKIM)		// 2006-10-02 by cmkwon
	//m_KbcGO.SetBmpButtonImage(IDB_GO_VTC, RGB(0,0,255));
	m_KbcGO.SetBmpButtonImage(IDB_GOBTN, RGB(0,0,255));
#else
	m_KbcGO.SetBmpButtonImage(IDB_GO_S2, RGB(0,0,255));
#endif

	m_KbcGO.SetToolTipText("Game Start");
	m_kbcBtnJoin.SetBmpButtonImage(IDB_JOINBTN, RGB(0,0,255));
	m_kbcBtnJoin.SetToolTipText("Join");


	///////////////////////////////////////////////////////////////////////////////
	// ��Ʈ�� ��ġ �����ϱ� ----> Start

	// 2007-09-07 by cmkwon, WebBrowser control
	char strWebAddress[1024];
	util::strncpy(strWebAddress, LAUNCHER_WEB_URL, 1024);
#ifdef S_ACCESS_INTERNAL_SERVER_HSSON
	//strWebAddress		= TESTSERVER_LAUNCHER_WEB_URL;			// 2006-08-04 by cmkwon, �׼� Launcher ��������
	util::strncpy(strWebAddress, TESTSERVER_LAUNCHER_WEB_URL, 1024);
#endif


	RECT rt;
	rt.left		= EXE2_BG_WEBCONTROL_POS_X;
	rt.top		= EXE2_BG_WEBCONTROL_POS_Y;
	rt.right	= EXE2_BG_WEBCONTROL_POS_X + EXE2_BG_WEBCONTROL_WIDTH;
	rt.bottom	= EXE2_BG_WEBCONTROL_POS_Y + EXE2_BG_WEBCONTROL_HEIGHT;




	m_pHost		= new Host(m_hWnd,strWebAddress,NULL,NULL,NULL, &rt);





	// �ػ� ���� ComboBox
	GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->MoveWindow(EXE2_BG_RESOLUTION_COMBOBOX_POS_X, EXE2_BG_RESOLUTION_COMBOBOX_POS_Y, EXE2_BG_RESOLUTION_COMBOBOX_WIDTH, EXE2_BG_RESOLUTION_COMBOBOX_HEIGHT);

	// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ ũ�� ����
	GetDlgItem(IDC_CHECK_WINDOWS_MODE)->MoveWindow(EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X, EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y, EXE2_BG_WINDOWSMODE_CHECKBOX_WIDTH, EXE2_BG_WINDOWSMODE_CHECKBOX_HEIGHT);



	GetDlgItem(IDC_CHARACTER_NAME)->ShowWindow(SW_HIDE);



	// AccountName Edit Box, Password Edit Box
	GetDlgItem(IDC_EDIT_ACCOUNT)->MoveWindow(EXE2_BG_ACCOUNTNAME_EDIT_POS_X, EXE2_BG_ACCOUNTNAME_EDIT_POS_Y, EXE2_BG_ACCOUNTNAME_EDIT_WIDTH, EXE2_BG_ACCOUNTNAME_EDIT_HEIGHT);
	GetDlgItem(IDC_EDIT_PASSWORD)->MoveWindow(EXE2_BG_PASSWORD_EDIT_POS_X, EXE2_BG_PASSWORD_EDIT_POS_Y, EXE2_BG_PASSWORD_EDIT_WIDTH, EXE2_BG_PASSWORD_EDIT_HEIGHT);



#if defined(S_LAUNCHER_USE_ID_PASSWORD_HSKIM) || defined(_DEBUG)	// 2007-09-07 by cmkwon, �ѱ� ��Ÿ�Ӹ� Release�� �Է��� ����
	GetDlgItem(IDC_EDIT_ACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_SHOW);
#endif


	// ��������Ʈ List Box
	GetDlgItem(IDC_LIST)->MoveWindow(EXE2_BG_SERVERLIST_BOX_POS_X, EXE2_BG_SERVERLIST_BOX_POS_Y, EXE2_BG_SERVERLIST_BOX_WIDTH, EXE2_BG_SERVERLIST_BOX_HEIGHT);
	GetDlgItem(IDC_LIST)->ShowWindow(SW_SHOW);		
	m_ctrlServerList.SetItemHeight(30);
	m_ctrlServerList.SetItemBGImageSize(EXE2_BG_SERVERLIST_ITEM_BG_WIDTH, EXE2_BG_SERVERLIST_ITEM_BG_HEIGHT);
	m_ctrlServerList.SetItemIconImage(EXE2_BG_SERVERLIST_ITEM_ICON_POS_X, EXE2_BG_SERVERLIST_ITEM_ICON_POS_Y, EXE2_BG_SERVERLIST_ITEM_ICON_WIDTH, EXE2_BG_SERVERLIST_ITEM_ICON_HEIGHT);
	m_ServerList = (CListBoxEBX *)GetDlgItem(IDC_LIST);

	// Minimized Button, Cancel Button
	GetDlgItem(IDMIN)->MoveWindow(EXE2_BG_MINIMIZED_BTN_POS_X, EXE2_BG_MINIMIZED_BTN_POS_Y, EXE2_BG_MINIMIZED_BTN_WIDTH, EXE2_BG_MINIMIZED_BTN_HEIGHT);
	GetDlgItem(IDCAN)->MoveWindow(EXE2_BG_CANCEL_BTN_POS_X, EXE2_BG_CANCEL_BTN_POS_Y, EXE2_BG_CANCEL_BTN_WIDTH, EXE2_BG_CANCEL_BTN_HEIGHT);

	// Game Start Button
	GetDlgItem(IDGO)->MoveWindow(EXE2_BG_GAMESTART_BTN_POS_X, EXE2_BG_GAMESTART_BTN_POS_Y, EXE2_BG_GAMESTART_BTN_WIDTH, EXE2_BG_GAMESTART_BTN_HEIGHT);

	// 2007-09-07 by cmkwon, ������� �ʴ� ��ư��
	//// Join Button
	//GetDlgItem(IDJOIN)->MoveWindow(nPosX, nPosY, IMAGE_JOIN_BUTTON_X_SIZE, IMAGE_JOIN_BUTTON_Y_SIZE);

	// Update Progress Bar
	m_progressCtrl.MoveWindow(EXE2_BG_UPDATE_PROGRESS_BAR_POS_X, EXE2_BG_UPDATE_PROGRESS_BAR_POS_Y, EXE2_BG_UPDATE_PROGRESS_BAR_WIDTH, EXE2_BG_UPDATE_PROGRESS_BAR_HEIGHT);
	m_progressCtrl.SetGradientColors(RGB(178, 0, 0), RGB(255, 85, 0));


	// Download File Version Num
	GetDlgItem(IDC_DOWNLOAD_FILENUM)->MoveWindow(EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X, EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y, EXE2_BG_DOWNLOAD_FILE_STATIC_WIDTH, EXE2_BG_DOWNLOAD_FILE_STATIC_HEIGHT);
	long wndStyle = ::GetWindowLong(GetDlgItem(IDC_DOWNLOAD_FILENUM)->m_hWnd, GWL_STYLE);
    ::SetWindowLong(GetDlgItem(IDC_DOWNLOAD_FILENUM)->m_hWnd, GWL_STYLE, wndStyle | SS_CENTERIMAGE);	// ����� ������ �����߾�(SS_CENTERIMAGE)�Ӽ��� �߰�
	m_fontDownloadFileNum.CreateFont(EXE2_BG_DOWNLOAD_FILE_FONT_SIZE, 0, 0, 0, EXE2_BG_DOWNLOAD_FILE_FONT_WEIGHT, 0, FALSE, FALSE, SG_BOX_FONT_CHARSET, OUT_DEFAULT_PRECIS,
							  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH , SG_BOX_FONT_FACENAME);    // "System" Font�� ��ǥ���� Fixed Font�Ӵ�.
	GetDlgItem(IDC_DOWNLOAD_FILENUM)->SetFont(&m_fontDownloadFileNum);

	// Download File Info
	GetDlgItem(IDC_FILE_INFO)->MoveWindow(EXE2_BG_UPDATE_INFO_STATIC_POS_X, EXE2_BG_UPDATE_INFO_STATIC_POS_Y, EXE2_BG_UPDATE_INFO_STATIC_WIDTH, EXE2_BG_UPDATE_INFO_STATIC_HEIGHT);
	wndStyle = ::GetWindowLong(GetDlgItem(IDC_FILE_INFO)->m_hWnd, GWL_STYLE);
    ::SetWindowLong(GetDlgItem(IDC_FILE_INFO)->m_hWnd, GWL_STYLE, wndStyle | SS_CENTERIMAGE);	// ����� ������ �����߾�(SS_CENTERIMAGE)�Ӽ��� �߰�
	m_fontFileInfo.CreateFont(EXE2_BG_UPDATE_INFO_FONT_SIZE, 0, 0, 0, EXE2_BG_UPDATE_INFO_FONT_WEIGHT, 0, FALSE, FALSE, SG_BOX_FONT_CHARSET, OUT_DEFAULT_PRECIS,
							  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH , SG_BOX_FONT_FACENAME);    // "System" Font�� ��ǥ���� Fixed Font�Ӵ�.
	GetDlgItem(IDC_FILE_INFO)->SetFont(&m_fontFileInfo);



	m_ctlBtnRememberID.ShowWindow(SW_SHOW);
	m_ctlBtnRememberID.MoveWindow(EXE2_BG_REMEMBERID_CHECKBOX_POS_X, EXE2_BG_REMEMBERID_CHECKBOX_POS_Y, EXE2_BG_REMEMBERID_CHECKBOX_WIDTH, EXE2_BG_REMEMBERID_CHECKBOX_HEIGHT);

	if(FALSE == m_szAccountNameReg.IsEmpty())
	{
		m_ctlBtnRememberID.SetCheck(TRUE);
	}


	// 2015-12-16 Future, Vsync setting
	m_ctlChckVsync.ShowWindow(SW_SHOW);
	// VSync Checkbox position:
	m_ctlChckVsync.MoveWindow(EXE2_BG_REMEMBERID_CHECKBOX_POS_X + 112, EXE2_BG_REMEMBERID_CHECKBOX_POS_Y, EXE2_BG_REMEMBERID_CHECKBOX_WIDTH, EXE2_BG_REMEMBERID_CHECKBOX_HEIGHT);
	m_ctlChckVsync.SetCheck(m_bVSync);


	CDC *pDC = GetDC();
	int nXScreen = EXE2_LAUNCHER_BG_SIZE_X;
	int nYScreen = EXE2_LAUNCHER_BG_SIZE_Y;
	m_BackGround.CreateCompatibleBitmap(pDC, nXScreen, nYScreen);
		
	CDC		memDCBackGround;	
	memDCBackGround.CreateCompatibleDC(pDC);
	CBitmap	*pOldBitmapBackGround = memDCBackGround.SelectObject(&m_BackGround);
	memDCBackGround.PatBlt(0,0,nXScreen,nYScreen,BLACKNESS);						// ����� ���������� �ʱ�ȭ
	
	CDC tmMemDC;
	tmMemDC.CreateCompatibleDC(pDC);


	CBitmap tmBitmap;
	CBitmap *pTmOldBitmap;



	BitmapRgn(IDB_BG_VTC_MASK, RGB( 255,255,255 ),0, 0);

	// Ÿ��Ʋ�� �׸���(Title Bar)
	tmBitmap.LoadBitmap(IDB_TITLE);
	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
	memDCBackGround.BitBlt(0, 0, EXE2_BG_TITLE_BAR_SIZE_X, EXE2_BG_TITLE_BAR_SIZE_Y, &tmMemDC, 0, 0, SRCCOPY);
	tmMemDC.SelectObject(pTmOldBitmap);
	tmBitmap.DeleteObject();

	// ��� ȭ�� �׸���(Background)
	
	
	tmBitmap.LoadBitmap(IDB_BG_VTC);
	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
	memDCBackGround.BitBlt(0, 0,EXE2_BG_BACKGROUND_IMAGE_SIZE_X, EXE2_BG_BACKGROUND_IMAGE_SIZE_Y,&tmMemDC,0,0,SRCPAINT);			
	tmMemDC.SelectObject(pTmOldBitmap);
	tmBitmap.DeleteObject();

	memDCBackGround.SelectObject(pOldBitmapBackGround);


	DisableControls();
	SetPrivateIP();

	// timeout�� �߻��ϸ� ���� ������ ����
	SetTimer(TIMERID_CONNECT_PRESERVER, 200, NULL);
	SetTimer(TIMERID_SEND_ALIVE_PACKET, 30000, NULL);
	SetTimer(TIMERID_NETWORK_STATE_CHECK, 1000, NULL);		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ

	ShowWindow(SW_SHOW);
	this->GetPublicLocalIP(m_szLocalIP);		// 2006-05-07 by cmkwon
	return TRUE;  // return TRUE  unless you set the focus to a control

}

BOOL CAtumLauncherDlg::ConnectPreServer()
{
	char preServerIP[1024];		

	util::strncpy(preServerIP, m_szPreServerIPReg, 1024);		// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - 

	// Make socket instance & connect
	m_pUpdateWinsocket = new CUpdateWinSocket(GetSafeHwnd());

	int nPreServerPort = PRE_SERVER_PORT;		// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - ��Ʈ�� ���� �� �� �ְ� ����

	if (!m_pUpdateWinsocket->Connect(preServerIP, nPreServerPort))
	{
 		int err = GetLastError();
 		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0004);
		util::del(m_pUpdateWinsocket);
		EndDialog(-1);
		return FALSE;
	}
	m_PreSD = m_pUpdateWinsocket->GetSocketDescriptor();

	return TRUE;
}

void CAtumLauncherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if(SC_MAXIMIZE == nID)
	{// �ִ�ȭ�� ���´�.

		return;
	}
	
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

void CAtumLauncherDlg::OnPaint()
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
		CPaintDC PaintDC (this);
		CDC		dcMem;
		BITMAP	stBitmap;

		dcMem.CreateCompatibleDC(&PaintDC);
		CBitmap *OldBitmap = dcMem.SelectObject(&m_BackGround);

		m_BackGround.GetObject(sizeof(BITMAP), &stBitmap);
		PaintDC.BitBlt(0, 0, stBitmap.bmWidth, stBitmap.bmHeight, &dcMem, 0, 0, SRCCOPY);

		

			

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAtumLauncherDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


struct sort_MEX_SERVER_GROUP_INFO_FOR_LAUNCHER_By_Crowdedness
{
	bool operator()(MEX_SERVER_GROUP_INFO_FOR_LAUNCHER op1, MEX_SERVER_GROUP_INFO_FOR_LAUNCHER op2)
	{
		return op1.Crowdedness < op2.Crowdedness;				// �������� ����
	}
};


LONG CAtumLauncherDlg::OnSocketNotify(WPARAM wParam, LPARAM lParam)
{
	if(NULL == m_pUpdateWinsocket)
	{
		return 0L;
	}

	switch(LOWORD(wParam))
	{
	case CUpdateWinSocket::WS_ERROR:
		{
		}
		break;
	case CUpdateWinSocket::WS_CONNECTED:
		{
			if (HIWORD(wParam) == TRUE)
			{
				m_pUpdateWinsocket->WriteMessageType(T_PC_CONNECT_GET_SERVER_GROUP_LIST);

				INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_SINGLE_FILE_VERSION_CHECK, T_PC_CONNECT_SINGLE_FILE_VERSION_CHECK, msgSFVer, msgSFVerBuf);
				// delete file list version
				msgSFVer->DeleteFileListVersion[0] = m_CurrentDelFileListVersion.GetVersion()[0];
				msgSFVer->DeleteFileListVersion[1] = m_CurrentDelFileListVersion.GetVersion()[1];
				msgSFVer->DeleteFileListVersion[2] = m_CurrentDelFileListVersion.GetVersion()[2];
				msgSFVer->DeleteFileListVersion[3] = m_CurrentDelFileListVersion.GetVersion()[3];
				// notice version
				msgSFVer->NoticeVersion[0] = m_CurrentNoticeVersion.GetVersion()[0];
				msgSFVer->NoticeVersion[1] = m_CurrentNoticeVersion.GetVersion()[1];
				msgSFVer->NoticeVersion[2] = m_CurrentNoticeVersion.GetVersion()[2];
				msgSFVer->NoticeVersion[3] = m_CurrentNoticeVersion.GetVersion()[3];

				m_pUpdateWinsocket->Write((char*)msgSFVerBuf, MSG_SIZE(MSG_PC_CONNECT_SINGLE_FILE_VERSION_CHECK));
			}
			else
			{
//				AtumMessageBox("������ ����Ǿ� ���� �ʰų� ���� ���Դϴ�.\n\n�׽�Ʈ �ð��� �ָ� 24�ð�,\n\n���� ����10�ú��� ����24�ñ����Դϴ�.");
				AtumMessageBox(STRERR_S_ATUMLAUNCHER_0005);
				EndDialog(-1);
			}
		}
		break;
	case CUpdateWinSocket::WS_CLOSED:
		{
			util::del(m_pUpdateWinsocket);
#ifdef _DEBUG
			AtumMessageBox(STRERR_S_ATUMLAUNCHER_0006);
#endif

			OnCancel();
		}
		break;
	case CUpdateWinSocket::WS_RECEIVED:
		{
			char * pPacket = NULL;
			int len,nType;
			m_pUpdateWinsocket->Read(&pPacket, len);

			if(pPacket)
			{
				nType = 0;
				memcpy(&nType, pPacket, SIZE_FIELD_TYPE_HEADER);

				switch(nType)
				{
				case T_PC_CONNECT_SINGLE_FILE_VERSION_CHECK_OK:
					{
// 2006-05-03 by cmkwon, ���������� ��ó�� ��ȭ�鿡�� ó���Ѵ�.
// 						// Notice �ε�
// 						if (!ReadNoticeFile())
// 						{
// 							AtumMessageBox(STRERR_S_ATUMLAUNCHER_0007);
// 							EndDialog(-1);
// 							return FALSE;
// 						}
//						DbgOut("	2007-07-13 by cmkwon, T_PC_CONNECT_SINGLE_FILE_VERSION_CHECK_OK\r\n");	// 2007-07-13 by cmkwon, �׽�Ʈ 

						/////////////////////////////////////////////
						// Send Client Version
						INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_VERSION, T_PC_CONNECT_VERSION, msgVersion, msgVersionBuff);
						msgVersion->ClientVersion[0] = m_CurrentVersion.GetVersion()[0];
						msgVersion->ClientVersion[1] = m_CurrentVersion.GetVersion()[1];
						msgVersion->ClientVersion[2] = m_CurrentVersion.GetVersion()[2];
						msgVersion->ClientVersion[3] = m_CurrentVersion.GetVersion()[3];
						m_pUpdateWinsocket->Write(msgVersionBuff, MSG_SIZE(MSG_PC_CONNECT_VERSION));

						// �ϴ� ���α�
						SetProgressGroupText(STRMSG_S_ATUMLAUNCHER_0000);
					}
					break;
				case T_PC_CONNECT_SINGLE_FILE_UPDATE_INFO:
					{
						auto pMsgUpdate = reinterpret_cast<MSG_PC_CONNECT_SINGLE_FILE_UPDATE_INFO*>(pPacket + SIZE_FIELD_TYPE_HEADER);
						
						VersionInfo TmpDelVerion { pMsgUpdate->NewDeleteFileListVersion };
						
						if (TmpDelVerion != m_CurrentDelFileListVersion)
						{
							if (m_bUpdateClientFile) ProcessDeleteFileListByHttp(pMsgUpdate);
									
							m_CurrentDelFileListVersion = TmpDelVerion;
						}
						
						m_CurrentNoticeVersion.SetVersion(pMsgUpdate->NewNoticeVersion);
						
						reinterpret_cast<CAtumLauncherApp*>(AfxGetApp())->WriteProfile(*this);

						MessageData<T_PC_CONNECT_VERSION> msgVersion;

						msgVersion->ClientVersion[0] = m_CurrentVersion.GetVersion()[0];
						msgVersion->ClientVersion[1] = m_CurrentVersion.GetVersion()[1];
						msgVersion->ClientVersion[2] = m_CurrentVersion.GetVersion()[2];
						msgVersion->ClientVersion[3] = m_CurrentVersion.GetVersion()[3];

						m_pUpdateWinsocket->Write(msgVersion);

						SetProgressGroupText(STRMSG_S_ATUMLAUNCHER_0000);
					}
					break;

				case T_PC_CONNECT_VERSION_OK:

					m_bProcessingVersionUpdate = TRUE;
					EnableControls();

					NTStartNetworkCheck();

					break;

				case T_PC_CONNECT_REINSTALL_CLIENT:
					{
						m_bProcessingVersionUpdate = TRUE;
						MSG_PC_CONNECT_REINSTALL_CLIENT *pReinstall
							= (MSG_PC_CONNECT_REINSTALL_CLIENT*)(pPacket + SIZE_FIELD_TYPE_HEADER);
						VersionInfo currentVersion;
						currentVersion.SetVersion(pReinstall->LatestVersion[0]
													, pReinstall->LatestVersion[1]
													, pReinstall->LatestVersion[2]
													, pReinstall->LatestVersion[3]);

#ifdef _ATUM_DEVELOP
						if (!m_bUpdateClientFile)
						{

							/////////////////////////////////////////////
							// Send Client Version
							INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_VERSION, T_PC_CONNECT_VERSION, msgVersion, msgVersionBuff);
							msgVersion->ClientVersion[0] = pReinstall->LatestVersion[0];
							msgVersion->ClientVersion[1] = pReinstall->LatestVersion[1];
							msgVersion->ClientVersion[2] = pReinstall->LatestVersion[2];
							msgVersion->ClientVersion[3] = pReinstall->LatestVersion[3];
							m_pUpdateWinsocket->Write(msgVersionBuff, MSG_SIZE(MSG_PC_CONNECT_VERSION));
							EnableControls();
							NTStartNetworkCheck();		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
							SetProgressGroupText("update completed");
							break;
						}
#endif
						CString tmpMsg;
						tmpMsg.Format(STRMSG_S_050930, STRMSG_S_GAMEHOMEPAGE_DOMAIN);
						tmpMsg += currentVersion.GetVersionString();
						AtumMessageBox(tmpMsg);

						OnCancel();
					}
					break;
				case T_PC_CONNECT_UPDATE_INFO:
					{
						MSG_PC_CONNECT_UPDATE_INFO *pMsgUpdateInfo
							= (MSG_PC_CONNECT_UPDATE_INFO*)(pPacket + SIZE_FIELD_TYPE_HEADER);

#ifdef _ATUM_DEVELOP
						if (!m_bUpdateClientFile)
						{
							/////////////////////////////////////////////
							// Send Client Version
							INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_VERSION, T_PC_CONNECT_VERSION, msgVersion, msgVersionBuff);
							msgVersion->ClientVersion[0] = pMsgUpdateInfo->UpdateVersion[0];
							msgVersion->ClientVersion[1] = pMsgUpdateInfo->UpdateVersion[1];
							msgVersion->ClientVersion[2] = pMsgUpdateInfo->UpdateVersion[2];
							msgVersion->ClientVersion[3] = pMsgUpdateInfo->UpdateVersion[3];
							m_pUpdateWinsocket->Write(msgVersionBuff, MSG_SIZE(MSG_PC_CONNECT_VERSION));
							EnableControls();
							NTStartNetworkCheck();		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
							SetProgressGroupText(STRMSG_S_ATUMLAUNCHER_0000);
							break;
						}
#endif
												
						
						if(FALSE == DownloadUpdateFileByHttp(pMsgUpdateInfo))
						{
							AtumMessageBox(STRERR_S_ATUMLAUNCHER_0009);
							ShellExecute(NULL, "open", STRMSG_S_GAMEHOMEPAGE_DOMAIN, NULL, NULL, SW_SHOWNORMAL);
							exit(0);
						}
							
						m_msg_PC_CONNECT_UPDATE_INFO = *pMsgUpdateInfo;

					}
					break;
				case T_PC_CONNECT_LOGIN_OK:
					{
						MSG_PC_CONNECT_LOGIN_OK *pConnOK;
						pConnOK = (MSG_PC_CONNECT_LOGIN_OK*)(pPacket + SIZE_FIELD_TYPE_HEADER);


						char szEncodedString[SIZE_MAX_PASSWORD_MD5_STRING];
						BYTE byPass[SIZE_MAX_PASSWORD_MD5];
						MD5 MD5_instance;
						
						char szTmPassword[1024];			// 2006-05-22 by cmkwon, ����� �߰� ��Ʈ�� ����
						util::zero(szTmPassword, 1024);
						wsprintf(szTmPassword, "%s%s", MD5_PASSWORD_ADDITIONAL_STRING, m_szPassword);
						MD5_instance.MD5Encode(szTmPassword, byPass);
						MD5_instance.MD5Binary2String(byPass, szEncodedString);

						// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) - 2�ܰ� ������ �����Ѵ�.
						m_szAccountName	= pConnOK->AccountName;

						char cmdLine[1024];		util::zero(cmdLine, 1024);
						//_chdir(".\\down");
						CString szTmpWindowDegree;

						// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - ������
						int nCX, nCY, nDegree;
						if(FALSE == this->FindWindowResolutionByWindowDegree(&nCX, &nCY, &nDegree, (LPSTR)(LPCSTR)m_csWindowsResolutionReg))
						{
							nCX		= 1024;		nCY		= 768;		nDegree		= 2;	// 2007-12-28 by cmkwon, �⺻��
						}
						szTmpWindowDegree.Format("%d %d %d", nCX, nCY, nDegree);

						DBGOUT(" Resolution ==> %s\r\n", szTmpWindowDegree);

						///////////////////////////////////////////////////////////////////////////////
						// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
						char szAppPath[1024];		util::zero(szAppPath, 1024);
						char szCmdParam[1024];		util::zero(szCmdParam, 1024);
						if (IsWindowsVersionOrGreater(6, 0, 0))
						{
							util::strncpy(szAppPath, CLIENT_EXEUTE_FILE_NAME, 1024);
						}
						else
						{
							util::strncpy(szAppPath, CLIENT_EXEUTE_FILE_NAME_XP, 1024);
						}
						

						CString szAccountNameLow = g_szMGameID;
						szAccountNameLow.MakeLower();

 						sprintf(szCmdParam, "%s %d %s %d %s %s %d %s %d %d"
							, pConnOK->FieldServerIP, pConnOK->FieldServerPort, pConnOK->IMServerIP, pConnOK->IMServerPort, m_szAccountName
							, szEncodedString, m_nWindowModeReg, szTmpWindowDegree, pConnOK->OpeningMoviePlay,	// 2011-12-21 by hskim, EP4 [������ 1ȸ ���]
							m_bVSync );		// 2015-12-16 Future, Vsync setting
						sprintf(cmdLine, "%s %s", szAppPath, szCmdParam);


						ExecGame(cmdLine, szAppPath, szCmdParam);						

						OnCancel();
					}
					break;
				case T_PC_CONNECT_GET_SERVER_GROUP_LIST_OK:
					{
						MSG_PC_CONNECT_GET_SERVER_GROUP_LIST_OK *pServerListOK
							= (MSG_PC_CONNECT_GET_SERVER_GROUP_LIST_OK*)(pPacket+SIZE_FIELD_TYPE_HEADER);

						if (pServerListOK->NumOfServerGroup <= 0)
						{
							AtumMessageBox(STRERR_S_ATUMLAUNCHER_0010);
							OnCancel();
							return 0;
						}

						MEX_SERVER_GROUP_INFO_FOR_LAUNCHER *pArrMexServerGroup
							= ((MEX_SERVER_GROUP_INFO_FOR_LAUNCHER*)(pPacket + MSG_SIZE(MSG_PC_CONNECT_GET_SERVER_GROUP_LIST_OK)));


						BOOL	bSelectedServerGroupName = FALSE;
						int		nIndexMinCrowdednessServerGroup = -1;
						int		nMinCrowdedness = 100;
						int		nCrowdedIndex = -1;
						///////////////////////////////////////////////////////////////////////////////
						// �������� ����Ʈ�� �߰��Ѵ�
						for (int i = 0; i < pServerListOK->NumOfServerGroup; i++)
						{
							MEX_SERVER_GROUP_INFO_FOR_LAUNCHER *pMexServerGroup
								= &pArrMexServerGroup[i];

							if (strcmp(pMexServerGroup->ServerGroupName, "ARENA") == 0) continue;

							///////////////////////////////////////////////////////////////////////////////
							// ȥ�⵵ ������ ServerGroupName�� �߰��Ѵ�
							CString strTemp;
							COLORREF	fontColor;

							///////////////////////////////////////////////////////////////////////////////
							// ȥ�⵵ ������ �߰��� ServerGroupName�� List�� �߰��Ѵ�
							// 2006-05-02 by ispark, �޺��� ����
							if(0 >= pMexServerGroup->Crowdedness)
							{
								strTemp.Format(STRERR_S_ATUMLAUNCHER_0011, pMexServerGroup->ServerGroupName, STRING_SERVER_GROUP_NAME_DELIMIT);
								fontColor = RGB(180, 180, 180);
								nCrowdedIndex = -1; 
							}
							else
							{
								nCrowdedIndex = min(9, (int)(pMexServerGroup->Crowdedness)/10);
#if defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)
								// 2008-07-24 by cmkwon, WinnerOnline_Tha CCU�� 80% �̻��̸� 100%�� �����ֱ�(K0000369) - 
								nCrowdedIndex = (nCrowdedIndex < 7) ? nCrowdedIndex : 9;
#endif
								strTemp.Format("%-16s%s", pMexServerGroup->ServerGroupName, STRING_SERVER_GROUP_NAME_DELIMIT);
								fontColor = RGB(255, 255, 255);
							}

							///////////////////////////////////////////////////////////////////////////////
							// 2008-02-14 by cmkwon, ��ó���� �����׷� ���� ������ ���� ���࿡ ������ ������ ���� - m_vectServerGroupList �� �߰��Ѵ�.
							SSERVER_GROUP_FOR_LAUNCHER tmSerGroup;
							tmSerGroup.nIndex	= i;
							util::strncpy(tmSerGroup.szServerGroupName, pMexServerGroup->ServerGroupName, SIZE_MAX_SERVER_NAME);
							m_vectServerGroupList.push_back(tmSerGroup);
							
#ifdef SERVICE_TYPE_CHINESE_SERVER_1	// 2007-06-22 by cmkwon, �߱� ��Ʈ��ũ ���� �����ֱ� - �߱��� ȥ�⵵ �̹����� �׸��� �ʰ� ��Ʈ��ũ Ping �ӵ��� �����ش�
							m_ServerList->InsertItem(i, strTemp, pMexServerGroup->Crowdedness, DEF_COL, fontColor, nCrowdedIndex, this->NTGetPingAverageTime(), TRUE);
#else
							// 7/13/2006 by dgwoo
							m_ServerList->InsertItem(i, strTemp, pMexServerGroup->Crowdedness, DEF_COL, fontColor, nCrowdedIndex);
#endif
							///////////////////////////////////////////////////////////////////////////////
							// ������ ������ ServerGroupName�� ���Ѵ�
							if(FALSE == m_strServerGroupName.IsEmpty()
								&& 0 == strnicmp((LPSTR)(LPCSTR)m_strServerGroupName, pMexServerGroup->ServerGroupName, SIZE_MAX_SERVER_NAME)
								&& pMexServerGroup->Crowdedness > 0)
							{// Crowdedness�� 0�̸� ���� ���� ������

								// 7/13/2006 by dgwoo
								m_ServerList->SetCurSel(i);
								m_nOldSel					= i;		// 2007-06-21 by cmkwon, ������ ���� ���� ���� - ���õ� index�� �����Ѵ�.
								bSelectedServerGroupName = TRUE;
							}

							if(pMexServerGroup->Crowdedness > 0
								&& pMexServerGroup->Crowdedness < nMinCrowdedness)
							{
								nIndexMinCrowdednessServerGroup = i;
								nMinCrowdedness = pMexServerGroup->Crowdedness;
							}
						}
						
						if(FALSE == bSelectedServerGroupName)
						{
#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
							// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - ���������� ��ȿ���� ������ �׳� ����
							AtumMessageBox(STRERR_S_ATUMLAUNCHER_0012);
							OnCancel();
							return 0;
#endif
							if(nIndexMinCrowdednessServerGroup == -1)
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0012);
								OnCancel();
							}
							// 7/13/2006 by dgwoo
							m_ServerList->SetCurSel(nIndexMinCrowdednessServerGroup);
							m_nOldSel					= nIndexMinCrowdednessServerGroup;		// 2007-06-21 by cmkwon, ������ ���� ���� ���� - ���õ� index�� �����Ѵ�.
						}						
					}
					break;

				case T_PC_CONNECT_NETWORK_CHECK_OK:		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
					{
						MSG_PC_CONNECT_NETWORK_CHECK_OK *pRMsg = (MSG_PC_CONNECT_NETWORK_CHECK_OK*)(pPacket + SIZE_FIELD_TYPE_HEADER);
						this->NTOnReceivedNetworkCheckOK(pRMsg->nCheckCount);
						m_ServerList->UpdateNetworkState(this->NTGetPingAverageTime());		// 2007-06-22 by cmkwon, �߱� ��Ʈ��ũ ���� �����ֱ� -
						m_ServerList->Invalidate();											// 2007-06-22 by cmkwon, �߱� ��Ʈ��ũ ���� �����ֱ� -
					}
					break;

				case T_PC_CONNECT_LOGIN_BLOCKED:
					{
						MSG_PC_CONNECT_LOGIN_BLOCKED *pLoginBlocked
							= (MSG_PC_CONNECT_LOGIN_BLOCKED*)(pPacket+SIZE_FIELD_TYPE_HEADER);

						char szTemp[1024];
						wsprintf(szTemp, STRMSG_S_050506
							, pLoginBlocked->szAccountName, pLoginBlocked->szBlockedReasonForUser
							, pLoginBlocked->atimeStart.GetDateTimeString().GetBuffer()
							, pLoginBlocked->atimeEnd.GetDateTimeString().GetBuffer());
						AtumMessageBox(szTemp);
						OnCancel();
					}
					break;
				// 2016-01-09 Future, MAC Blocking
				case T_PC_CONNECT_MAC_BLOCKED:
					{
						AtumMessageBox(STRMSG_S_050507);
						OnCancel();
					}
					break;
				case T_ERROR:
					{
						MSG_ERROR *pRecvMsg;
						pRecvMsg = (MSG_ERROR*)(pPacket + SIZE_FIELD_TYPE_HEADER);

						char buf[1024];
						Err_t error = pRecvMsg->ErrorCode;

						DBGOUT(STRERR_S_ATUMLAUNCHER_0013, GetErrorString(pRecvMsg->ErrorCode), pRecvMsg->ErrorCode, "ST_PRE_SERVER", m_pUpdateWinsocket->m_szPeerIP);

						switch (error)
						{
						case ERR_COMMON_LOGIN_FAILED:
							{
								AtumMessageBox(STRMSG_060824_0000);
								GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
								((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetSel(0, -1);
							}
							break;
						case ERR_PROTOCOL_INVALID_PRESERVER_CLIENT_STATE:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0015);
								OnCancel();
							}
							break;
						case ERR_PROTOCOL_EMPTY_ACCOUNTNAME:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0016);
								GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
								((CEdit*)GetDlgItem(IDC_EDIT_ACCOUNT))->SetSel(0, -1);
							}
							break;
						case ERR_PROTOCOL_DUPLICATE_LOGIN:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0017);
								OnCancel();
							}
							break;
						case ERR_PROTOCOL_ALL_FIELD_SERVER_NOT_ALIVE:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0018);
								//OnCancel();
							}
							break;
						case ERR_PROTOCOL_IM_SERVER_NOT_ALIVE:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0019);
								//OnCancel();
							}
							break;
						case ERR_COMMON_SERVICE_TEMPORARILY_PAUSED:
							{
								static BOOL bMsgBox = FALSE;
								if(FALSE == bMsgBox)
								{
									bMsgBox = TRUE;
									AtumMessageBox(STRERR_S_ATUMLAUNCHER_0020);
									OnCancel();
								}
							}
							break;
						case ERR_PROTOCOL_LIMIT_GROUP_USER_COUNT:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0021);
								OnCancel();
							}
							break;
						case ERR_PROTOCOL_ACCOUNT_BLOCKED:
							{
								char szErrString[512];
								memset(szErrString, 0x00, 512);
								memcpy(szErrString, ((BYTE*)pRecvMsg) + sizeof(MSG_ERROR), pRecvMsg->StringLength);
								sprintf(buf, STRERR_S_ATUMLAUNCHER_0022, szErrString);
								AtumMessageBox(buf);
								OnCancel();
							}
							break;
						case ERR_COMMON_INVALID_CLIENT_VERSION:
							{
								AtumMessageBox(STRERR_061011_0000);		// 2006-10-11 by cmkwon, ����(STRERR_S_ATUMLAUNCHER_0023-->STRERR_061011_0000)
								OnCancel();
							}
							break;
						case ERR_DB_NO_SUCH_ACCOUNT:		// 2006-09-19 by cmkwon, ��ϵ��� ���� ������
							{
								AtumMessageBox(STRMSG_060824_0000);
							}
							break;
						case ERR_PERMISSION_DENIED:			// 2006-09-27 by cmkwon, ���� ������ �����ϴ�.
							{
								AtumMessageBox(STRMSG_060927_0000);		// 2006-09-27 by cmkwon, "���� ���� ���� ���Դϴ�. �ڼ��� ������ Ȩ�������� �����ϼ���."
								OnCancel();
							}
							break;
						case ERR_NO_SEARCH_CHARACTER:		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
						case ERR_DB_EXECUTION_FAILED:		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
							{
								AtumMessageBox(STRMSG_080430_0001);		// 2008-04-30 by cmkwon, "�����Ͻ� ������ �ű� ĳ���� ������ ���ѵ� ���� �Դϴ�."
							}
							break;
						// 2012-07-11 by hskim, ������ �˴ٿ�
						case ERR_PROTOCOL_SELECTIVE_SHUTDOWN_NOT_ALLOWED_TIME:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0037);
								OnCancel();								
							}
							break;
						// end 2012-07-11 by hskim, ������ �˴ٿ�

						default:
							{
								sprintf(buf, STRERR_S_ATUMLAUNCHER_0024, GetErrorString(pRecvMsg->ErrorCode), pRecvMsg->ErrorCode);
								AtumMessageBox(buf);
								OnCancel();
							}
							break;
						}
					}
				default:
					{
					}
				}

				util::del(pPacket);
			}
		}
		break;
	}

	return 0;
}

BOOL CAtumLauncherDlg::DownloadUpdateFile(MSG_PC_CONNECT_UPDATE_INFO *pMsgUpdateInfo)
{
//	if(m_pUpdateFTPManager){		return FALSE;}
//
//	VersionInfo OldVersion(pMsgUpdateInfo->OldVersion);
//	VersionInfo UpdateVersion(pMsgUpdateInfo->UpdateVersion);
//	char szDownLoadFileName[256];
//// 2005-12-23 by cmkwon
////	sprintf(szDownLoadFileName, "%s/%s_%s.zip",	pMsgUpdateInfo->FtpUpdateDir, OldVersion.GetVersionString(), UpdateVersion.GetVersionString());
//	sprintf(szDownLoadFileName, "%s/%s_%s.zip",	pMsgUpdateInfo->FtpUpdateDownloadDir, OldVersion.GetVersionString(), UpdateVersion.GetVersionString());
//
//	DbgOut("Updating game data file(%s) From %s:%d by FTP\r\n", szDownLoadFileName, pMsgUpdateInfo->FtpIP, pMsgUpdateInfo->FtpPort);
//
//	m_pUpdateFTPManager = new CFTPManager;
//	
//	BOOL bRet = m_pUpdateFTPManager->ConnectToServer(pMsgUpdateInfo->FtpIP, pMsgUpdateInfo->FtpPort,
//									pMsgUpdateInfo->FtpAccountName, pMsgUpdateInfo->FtpPassword);
//	if (!bRet)
//	{
//		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0025);		
//		return FALSE;
//	}
//
//	HINTERNET hFile;
//	int nFileSize = m_pUpdateFTPManager->GetFileSize(szDownLoadFileName, hFile);
//	if (nFileSize == -1)
//	{
//		DbgOut(STRERR_S_ATUMLAUNCHER_0026, szDownLoadFileName);
//// 2006-05-26 by cmkwon, FTP Server �ɼǿ� List �����ֱ� ������ �ȵǾ� ���� ���� �ִ�
//// 		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0027);
//// 		return FALSE;
//		nFileSize		= 1000*1024*1024;			// 2008-11-27 by cmkwon, �⺻ 1000MBytes�� ������. // 2006-05-26 by cmkwon, �⺻ 100MBytes�� ������
//	}
//
//	m_progressCtrl.SetRange32(0, nFileSize);
//	SetProgressGroupText((LPCSTR)(CString("Updating from ") + OldVersion.GetVersionString()
//							+ " to " + UpdateVersion.GetVersionString()));
//	
//	SetFTPUpdateState(UPDATE_STATE_DOWNLOADING);
//	bRet = m_pUpdateFTPManager->DownloadFile(szDownLoadFileName, NULL, NULL, GetSafeHwnd());
//	if (!bRet)
//	{
//		delete m_pUpdateFTPManager;
//		m_pUpdateFTPManager = NULL;
//		this->SetFTPUpdateState(UPDATE_STATE_INIT);
//		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0028);
//		return FALSE;
//	}

	return FALSE;
}

void CAtumLauncherDlg::ExtractUpdateFile(MSG_PC_CONNECT_UPDATE_INFO *pMsgUpdateInfo)
{
	VersionInfo OldVersion(pMsgUpdateInfo->OldVersion);
	VersionInfo UpdateVersion(pMsgUpdateInfo->UpdateVersion);
	char szUpdateFileName[256];
	sprintf(szUpdateFileName, "%s_%s.zip", OldVersion.GetVersionString(), UpdateVersion.GetVersionString());

	// extract zip file
	CZipArchive ZipOut;
	FILE* fp = NULL;
	errno_t no = fopen_s(&fp, szUpdateFileName, "rb");
	//if (ZipOut.FileExists(szUpdateFileName) != 1)
	if (no!=0)
	{
		fclose(fp);
		// error
		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0029);
		exit(0);
	}
	fclose(fp);

	ZipOut.Open(szUpdateFileName, CZipArchive::zipOpen);

	// 2010-04-28 by cmkwon, ��ó ��Ʈ�� ���� ����(K0002816) - 
	SetProgressGroupText((LPCSTR)(CString("Extracting ") + szUpdateFileName));
	m_progressCtrl.SetRange32(0, ZipOut.GetCount());
	for (int i = 0; i < ZipOut.GetCount(); i++)
	{
		//if (!ZipOut.IsFileDirectory(i))
		if (!(ZipOut.GetFileInfo(i))->IsDirectory())
		{
			CZipFileHeader zipFileHeader;
			ZipOut.GetFileInfo(zipFileHeader, i);
			CString targetFileName = zipFileHeader.GetFileName();
			DWORD fileAttr = GetFileAttributes(targetFileName);
			if (fileAttr & FILE_ATTRIBUTE_READONLY != 0)
			{
				fileAttr = fileAttr & ~FILE_ATTRIBUTE_READONLY;
				SetFileAttributes(targetFileName, fileAttr);
			}
		}

		ZipOut.ExtractFile(i, "./", true);
		m_progressCtrl.SetPos(i+1);
	}

	ZipOut.Close();

	DeleteFile(szUpdateFileName);

	return;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::DownloadUpdateFileByHttp(MSG_PC_CONNECT_UPDATE_INFO *pMsgUpdateInfo)
/// \brief		
/// \author		cmkwon
/// \date		2007-01-08 ~ 2007-01-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::DownloadUpdateFileByHttp(MSG_PC_CONNECT_UPDATE_INFO *pMsgUpdateInfo)
{
	if (m_pHttpManager != nullptr) return FALSE;
	
	VersionInfo OldVersion(pMsgUpdateInfo->OldVersion);
	VersionInfo UpdateVersion(pMsgUpdateInfo->UpdateVersion);
	char szDownLoadFileName[SIZE_MAX_FTP_FILE_PATH];
	char szDownLoadFileFullPath[SIZE_MAX_FTP_FILE_PATH];

	sprintf(szDownLoadFileName, "%s_%s.zip", OldVersion.GetVersionString(), UpdateVersion.GetVersionString());
	sprintf(szDownLoadFileFullPath, "%s/%s", pMsgUpdateInfo->FtpUpdateDownloadDir, szDownLoadFileName);

	//DbgOut("Updating game data file(%s) From %s:%d by Http\r\n", szDownLoadFileName, pMsgUpdateInfo->FtpIP, pMsgUpdateInfo->FtpPort);

	m_pHttpManager = new CHttpManager;

	SetFTPUpdateState(UPDATE_STATE_DOWNLOADING);
	Err_t errCode = m_pHttpManager->DownloadFileByHttp(pMsgUpdateInfo->FtpIP, pMsgUpdateInfo->FtpPort, szDownLoadFileFullPath, szDownLoadFileName, TRUE, this->GetSafeHwnd());
	if (ERR_NO_ERROR != errCode)
	{
		util::del(m_pHttpManager);
		this->SetFTPUpdateState(UPDATE_STATE_INIT);
		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0028);
		return FALSE;
	}

	SetProgressGroupText((LPCSTR)(CString("Updating from ") + OldVersion.GetVersionString()	+ " to " + UpdateVersion.GetVersionString()));
	
	return TRUE;
}

// WPARAM: Socket descriptor
LONG CAtumLauncherDlg::OnAsyncSocketMessage(WPARAM wParam, LPARAM lParam)
{
	if ((SOCKET)wParam == m_PreSD)
		m_pUpdateWinsocket->OnAsyncEvent(lParam);
/*	else if ((SOCKET)wParam == m_FieldSD)
		m_pFieldWinsocket->OnAsyncEvent(lParam);*/

	return 0;
}

LONG CAtumLauncherDlg::OnDownLoadGamefilesDone(WPARAM wParam, LPARAM lParam)
{
	if (m_bCancelFlag) return -1;

	CString cstrVersion = m_CurrentVersion.GetVersionString();
	SetFileNumText((char*)(LPCTSTR)("VER " + cstrVersion));

	///////////////////////////////////////////////////////////////////////////
	// �ٿ�ε� �Ϸ��� ���� ���� �� �ٽ� CONNECT_VERSION ����
	((CAtumLauncherApp*)AfxGetApp())->WriteProfile(*this);

	/////////////////////////////////////////////
	// Send Version
	INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_VERSION, T_PC_CONNECT_VERSION, msgVersion, msgVersionBuff);
	msgVersion->ClientVersion[0] = m_CurrentVersion.GetVersion()[0];
	msgVersion->ClientVersion[1] = m_CurrentVersion.GetVersion()[1];
	msgVersion->ClientVersion[2] = m_CurrentVersion.GetVersion()[2];
	msgVersion->ClientVersion[3] = m_CurrentVersion.GetVersion()[3];
	m_pUpdateWinsocket->Write(msgVersionBuff, MSG_SIZE(MSG_PC_CONNECT_VERSION));

	return 0;
}

void CAtumLauncherDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here

// 2009-11-19 by cmkwon, ���þ� AdminTool�� FrostLib �����ϱ� - 
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1) && defined(_USING_INNOVA_FROST_)
	///////////////////////////////////////////////////////////////////////////////
	// 2009-11-19 by cmkwon, ���þ� AdminTool�� FrostLib �����ϱ� - 
	frostFinalize();
#endif // END - #if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)

	util::del(m_pUpdateWinsocket);

	CWinSocket::SocketClean();
}

void CAtumLauncherDlg::OnOk()
{
	// TODO: Add your control notification handler code here

	if(m_SelectFlag)
	{
		UpdateData();
		// 7/13/2006 by dgwoo
		if (m_ServerList->GetCurSel() == LB_ERR
			|| m_ServerList->GetCount() < 1)
		{
			AtumMessageBox(STRMSG_S_ATUMLAUNCHER_0001);
			return;
		}

		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� -
		CString csWDegree;
		GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->GetWindowText(csWDegree);
		if(csWDegree.IsEmpty())
		{
			AtumMessageBox(STRMSG_071228_0001);
			return;
		}



/*	/// 2012-05-10 by jhseol, ���þ� - EP4 �ö���鼭 ��� ����. �ּ�ó��
		// 2008-12-17 by ckPark ���þ� ����
		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - üũ ��ư�� Ȯ�� �Ѵ�.		
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
		// ���þƴ� üũ�ڽ� ���¸� ��Ʈ�ѿ��� ���´�
		if(FALSE == m_ctrlCheckWindowMode.GetCheck())
#else
		if(FALSE == this->IsDlgButtonChecked(IDC_CHECK_WINDOWS_MODE))
#endif
		// end 2008-12-17 by ckPark ���þ� ����
*/

		if(FALSE == this->IsDlgButtonChecked(IDC_CHECK_WINDOWS_MODE))
		{
			m_nWindowModeReg		= GAME_MODE_FULLSCREEN;
		}
		else
		{
			m_nWindowModeReg		= GAME_MODE_WINDOW;
		}

		SendLogin(LOGIN_TYPE_DIRECT);
// 2007-03-06 by cmkwon, ������ �ҽ� ���ŷ� �ʿ� ����
//		//////////////////////////////////////////////////////////////////////
//		// Send Login
//#if defined(_ATUM_DEVELOP) || defined(_MASANG15_SERVER) || defined(_MASANG51_SERVER) || defined(_GLOBAL_ENG_SERVER) || defined(_VTC_VIET_SERVER) || defined(_KOREA_SERVER_2)
//		SendLogin(LOGIN_TYPE_DIRECT);
//#else
//		SendLogin(LOGIN_TYPE_MGAME);
//#endif// end_ATUM_DEVELOP

//		m_nServerGroupReg = m_nServer;
		m_szAccountName.MakeLower();
		m_szAccountNameReg = m_szAccountName;
		m_szPasswordReg = m_szPassword;
// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �ʿ� ����
//		m_nWindowDegreeReg = m_nWindowDegree+3;		// 2007-07-24 by cmkwon, ��ó���� 800*600 �ػ� ���� - ���� ������Ʈ������ ����ϱ� ���ؼ�




/*	/// 2012-05-10 by jhseol, ���þ� - EP4 �ö���鼭 ��� ����. �ּ�ó��
		// 2008-12-17 by ckPark ���þ� ����
		// ���þƴ� ��Ʈ���� ��Ʈ�ѿ��� ���� ���´�
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
		m_csWindowsResolutionReg	= reinterpret_cast<char*>(m_ctrlComboWindowDegree.GetItemData(m_ctrlComboWindowDegree.GetCurSel()));
#else
		m_csWindowsResolutionReg	= csWDegree;	// 2007-12-27 by cmkwon, �������� ��� ��� �߰� -
#endif
		// end 2008-12-17 by ckPark ���þ� ����
*/
		m_csWindowsResolutionReg	= csWDegree;	// 2007-12-27 by cmkwon, �������� ��� ��� �߰� -



		((CAtumLauncherApp*)AfxGetApp())->WriteProfile(*this);

		// ���� ���� ��ư ������ ������ �� ����
		DisableControls();
		SetTimer(TIMERID_ENABLE_CONTROL, 2000, NULL);
	}
	else
	{
		AfxMessageBox(STRMSG_S_ATUMLAUNCHER_0001);
	}
}

BOOL CAtumLauncherDlg::SendLogin(BYTE i_nLoginType)
{
	MessageData<T_PC_CONNECT_LOGIN> msgLogin;

	msgLogin->LoginType = i_nLoginType;
	if (i_nLoginType == LOGIN_TYPE_DIRECT)
	{
		util::strncpy(msgLogin->AccountName, m_szAccountName, SIZE_MAX_ORIGINAL_ACCOUNT_NAME);
	}
	else return FALSE;

	if (i_nLoginType == LOGIN_TYPE_DIRECT)
	{
		MD5 MD5_instance;
		char szTmPassword[1024];			// 2006-05-22 by cmkwon, ����� �߰� ��Ʈ�� ����
		util::zero(szTmPassword, 1024);
		wsprintf(szTmPassword, "%s%s", MD5_PASSWORD_ADDITIONAL_STRING, m_szPassword);
		MD5_instance.MD5Encode(szTmPassword, msgLogin->Password);
	}
	else return FALSE;
		
	if (m_ServerList->GetCrowdedness(m_ServerList->GetCurSel()) == 0)
	{
		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0030);
		return FALSE;
	}

	CString szSelectedServerName;

	if (!FindServerGroupName(&szSelectedServerName, m_ServerList->GetCurSel()))
	{
		AtumMessageBox("Invalid Server Group.");
		return FALSE;
	}
	

	m_strServerGroupName = szSelectedServerName;
	util::strncpy(msgLogin->FieldServerGroupName, szSelectedServerName, SIZE_MAX_SERVER_NAME);
	util::strncpy(msgLogin->PrivateIP, m_PrivateIP, SIZE_MAX_IPADDRESS);
	util::strncpy(msgLogin->WebLoginAuthKey, LPCSTR(m_szPassword), SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY);	


	// 2016-01-09 Future, MAC Blocking
	CMachineID::GetPrimaryAdapterMacAddressStr(msgLogin->MACAddress);

	return m_pUpdateWinsocket->Write(msgLogin);
}


int CAtumLauncherDlg::AtumMessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption/*=NULL*/, UINT nType/*=MB_OK*/)
{
	if (lpszCaption)
		
		return MessageBox(lpszText, lpszCaption, nType);
	
	return MessageBox(lpszText, STRMSG_WINDOW_TEXT, nType);	
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::ProcessDeleteFileListByHttp(MSG_PC_CONNECT_SINGLE_FILE_UPDATE_INFO *pUpdateInfo)
/// \brief		
/// \author		cmkwon
/// \date		2007-01-08 ~ 2007-01-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::ProcessDeleteFileListByHttp(MSG_PC_CONNECT_SINGLE_FILE_UPDATE_INFO *pUpdateInfo)
{
	constexpr auto szDelFileName = "tmDelete.txt";

	CHttpManager	httpMan;

	auto errCode = httpMan.DownloadFileByHttp(pUpdateInfo->FtpIP, pUpdateInfo->FtpPort, pUpdateInfo->DeleteFileListDownloadPath, szDelFileName);
	
	if (errCode != ERR_NO_ERROR)
	{

		::DeleteFile(szDelFileName);
		SetLastError(0);
		return false;
	}

	ifstream stream;

	stream.open(szDelFileName);

	if (!stream.is_open()) return false;

	char delFileLine[SIZE_MAX_FTP_FILE_PATH];
	
	auto bFileEndFlag = false;

	while (!bFileEndFlag)
	{
		stream.getline(delFileLine, SIZE_MAX_FTP_FILE_PATH);
		
		bFileEndFlag = stream.eof();

		if (delFileLine[0] == '\0') continue; // empty line

		auto secondlast = delFileLine + strlen(delFileLine) - 1;

		if (*secondlast == 0x0D) *secondlast = '\0'; // 0x0D (CR) : remove trailing \r

		if (delFileLine[0] == '#') continue; // this is a comment

		::DeleteFile(delFileLine);

		SetLastError(0); // in case there was no such file
	}
	
	stream.close();

	::DeleteFile(szDelFileName);

	return true;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumLauncherDlg::MoveWindow2Center(void)
/// \brief		// 2007-09-07 by cmkwon, ��Ʈ�� ��ó �������̽� ���� -
/// \author		cmkwon
/// \date		2007-09-07 ~ 2007-09-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumLauncherDlg::MoveWindow2Center(void)
{
	int nWidth	= EXE2_LAUNCHER_BG_SIZE_X + 6;
	int nHeight	= EXE2_LAUNCHER_BG_SIZE_Y + 6 ;

	LONG x,y;
	x=LONG((GetSystemMetrics(SM_CXSCREEN)-nWidth)/2); 
	y=LONG((GetSystemMetrics(SM_CYSCREEN)-nHeight)/2);
	
	MoveWindow(x, y, nWidth, nHeight, TRUE);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumLauncherDlg::PushCharFromScreenKeyboard(char i_cPushChar)
/// \brief		// 2007-09-11 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� -
/// \author		cmkwon
/// \date		2007-09-11 ~ 2007-09-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumLauncherDlg::PushCharFromScreenKeyboard(char i_cPushChar)
{
	if(NULL == m_pScreenKeyboardDlg)
	{
		return;
	}

	if(NULL == m_pInputEditFromScreenKeyboard)
	{
		m_pInputEditFromScreenKeyboard = GetDlgItem(IDC_EDIT_ACCOUNT);
	}

	CString strCurText, strResultText;
	m_pInputEditFromScreenKeyboard->GetWindowText(strCurText);
	strResultText.Format("%s%c", strCurText, i_cPushChar);
	m_pInputEditFromScreenKeyboard->SetWindowText(strResultText);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumLauncherDlg::DeleteCharFromScreenKeyboard(void)
/// \brief		// 2007-09-11 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� -
/// \author		cmkwon
/// \date		2007-09-11 ~ 2007-09-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumLauncherDlg::DeleteCharFromScreenKeyboard(void)
{
	if(NULL == m_pScreenKeyboardDlg)
	{
		return;
	}

	if(NULL == m_pInputEditFromScreenKeyboard)
	{
		m_pInputEditFromScreenKeyboard = GetDlgItem(IDC_EDIT_ACCOUNT);
	}

	CString strCurText;
	m_pInputEditFromScreenKeyboard->GetWindowText(strCurText);
	if(strCurText.IsEmpty())
	{
		return;
	}
	strCurText.Delete(strCurText.GetLength()-1);
	m_pInputEditFromScreenKeyboard->SetWindowText(strCurText);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumLauncherDlg::HideScreenKeyboardByScreenKeyboardWindow(void)
/// \brief		// 2007-09-18 by cmkwon, ȭ��Ű���� ���� - 
/// \author		cmkwon
/// \date		2007-09-18 ~ 2007-09-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumLauncherDlg::HideScreenKeyboardByScreenKeyboardWindow(void)
{
	m_bHideScreenKeyboardByScreenKeyboardWindow	= TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::FindWindowResolutionByWindowDegree(int *o_pnCX, int *o_pnCY, int *o_pnDegree, char *i_szWindowDegreeName)
/// \brief		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - CAtumLauncherDlg::FindWindowResolutionByWindowDegree() �߰�
/// \author		cmkwon
/// \date		2007-12-28 ~ 2007-12-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::FindWindowResolutionByWindowDegree(int *o_pnCX, int *o_pnCY, int *o_pnDegree, char *i_szWindowDegreeName)
{
	*o_pnCX		= 0;
	*o_pnCY		= 0;
	*o_pnDegree	= 0;

	for(int i=0; g_pWindowDegreeList[i].szWindowDegreeName != NULL; i++)
	{
		if(0 == strncmp(g_pWindowDegreeList[i].szWindowDegreeName, i_szWindowDegreeName, SIZE_MAX_WINDOW_DEGREE_NAME))
		{
			*o_pnCX		= g_pWindowDegreeList[i].nCX;
			*o_pnCY		= g_pWindowDegreeList[i].nCY;
			*o_pnDegree	= g_pWindowDegreeList[i].nDegree;
			return TRUE;
		}
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::InsertWindowDegreeList(CComboBox *i_pComboBox, BOOL i_bWindowsMode)
/// \brief		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - CAtumLauncherDlg::InsertWindowDegreeList() �߰�
/// \author		cmkwon
/// \date		2007-12-28 ~ 2007-12-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::InsertWindowDegreeList(CComboBox *i_pComboBox, BOOL i_bWindowsMode)
{
	i_pComboBox->ResetContent();	// 2007-12-28 by cmkwon, ��� ������ �ʱ�ȭ

	// 2013-07-30 by jhseol, ��Ƽ�ػ� ���� - ��ü �ػ� Ȯ��
#ifdef S_MULTI_RESOLUTION_JHSEOL	// - ��ü �ػ� Ȯ��
	int nCXScreen = GetSystemMetrics(SM_CXMAXTRACK);
	int nCYScreen = GetSystemMetrics(SM_CYMAXTRACK);
#else
	int nCXScreen = GetSystemMetrics(SM_CXSCREEN);
	int nCYScreen = GetSystemMetrics(SM_CYSCREEN);
#endif
	// end 2013-07-30 by jhseol, ��Ƽ�ػ� ���� - ��ü �ػ� Ȯ��


	int nInsertedCnts = 0;
	for(int i=0; g_pWindowDegreeList[i].szWindowDegreeName != NULL; i++)
	{
		// 2013-07-30 by jhseol, ��Ƽ�ػ� ���� - ��ü �ػ� �ȿ� ���ԵǴ� �ػ󵵸� ���
#ifdef S_MULTI_RESOLUTION_JHSEOL	// - ��ü �ػ� �ȿ� ���ԵǴ� �ػ󵵸� ���
		if( FALSE == i_bWindowsMode
			|| (nCXScreen >= g_pWindowDegreeList[i].nCX && nCYScreen >= g_pWindowDegreeList[i].nCY) )
		{
			i_pComboBox->AddString(g_pWindowDegreeList[i].szWindowDegreeName);
			nInsertedCnts++;
		}
#else
		if(FALSE == this->IsSupportedResolution(g_pWindowDegreeList[i].nCX, g_pWindowDegreeList[i].nCY))
		{// 2008-01-03 by cmkwon, �����ϴ� �ػ� ����Ʈ�� �����ֱ� - �������� �ʴ� �ػ󵵴� �������� �ȴ´�
			continue;
		}

		if( FALSE == i_bWindowsMode
			|| (nCXScreen >= g_pWindowDegreeList[i].nCX	&& nCYScreen >= g_pWindowDegreeList[i].nCY) )
		{
			i_pComboBox->AddString(g_pWindowDegreeList[i].szWindowDegreeName);

/*	/// 2012-05-10 by jhseol, ���þ� - EP4 �ö���鼭 ��� ����. �ּ�ó��
			// 2008-12-17 by ckPark ���þ� ����
			// ���þƴ� ��Ʈ���� ��Ʈ�ѿ��� ���� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
			i_pComboBox->SetItemData(i, (DWORD)(g_pWindowDegreeList[i].szWindowDegreeName));
#endif
			// end 2008-12-17 by ckPark ���þ� ����
*/
			nInsertedCnts++;
		}
#endif
		// end 2013-07-30 by jhseol, ��Ƽ�ػ� ���� - ��ü �ػ� �ȿ� ���ԵǴ� �ػ󵵸� ���
	}



/*	/// 2012-05-10 by jhseol, ���þ� - EP4 �ö���鼭 ��� ����. �ּ�ó��
	// 2008-12-17 by ckPark ���þ� ����
	// �޺��ڽ� ���Ž� �ٽ� �ѹ� �׸���
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	i_pComboBox->Invalidate(TRUE);
#endif
	// end 2008-12-17 by ckPark ���þ� ����
*/




	return nInsertedCnts;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::FindWindowDegreeComboBoxIndex(CComboBox *i_pComboBox, char *i_szWindowDegreeName)
/// \brief		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - CAtumLauncherDlg::FindWindowDegreeComboBoxIndex() �߰�
/// \author		cmkwon
/// \date		2007-12-28 ~ 2007-12-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::FindWindowDegreeComboBoxIndex(CComboBox *i_pComboBox, char *i_szWindowDegreeName)
{
	int nItemCnts = i_pComboBox->GetCount();
	for(int i=0; i < nItemCnts; i++)
	{
		CString csWDegree;

		
		
/*	/// 2012-05-10 by jhseol, ���þ� - EP4 �ö���鼭 ��� ����. �ּ�ó��
		// 2008-12-17 by ckPark ���þ� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
		csWDegree = (char*)(i_pComboBox->GetItemDataPtr(i));
#else
		i_pComboBox->GetLBText(i, csWDegree);
#endif
		// end 2008-12-17 by ckPark ���þ� ����
*/
		i_pComboBox->GetLBText(i, csWDegree);



		if(0 == csWDegree.Compare(i_szWindowDegreeName))
		{
			return i;
		}
	}

	return -1;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::InitSupportedWindowResolutionList(void)
/// \brief		// 2008-01-03 by cmkwon, �����ϴ� �ػ� ����Ʈ�� �����ֱ� - CAtumLauncherDlg::InitSupportedWindowResolutionList() �߰�
/// \author		cmkwon
/// \date		2008-01-03 ~ 2008-01-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::InitSupportedWindowResolutionList(void)
{
 	///////////////////////////////////////////////////////////////////////////////
 	// 2008-06-12 by cmkwon, �ӽ� üũ��, ���� �ػ� �α� ���Ϸ� ���� - �ʿ� ������� �ּ����� ó��
// 	BOOL bSaveFile	= TRUE;
// 	CSystemLogManager resultLog;
// 	if(FALSE == resultLog.InitLogManger(TRUE, "LauncherLog", "./"))
// 	{
// 		bSaveFile	= FALSE;
// 	}

	DEVMODE devMode;
	INT32 modeExist;
	for (int i=0; ;i++) 
	{
		modeExist = EnumDisplaySettings(NULL, i, &devMode);
		if (!modeExist) 
		{
			break;
		}

		
// 2008-06-12 by cmkwon, �ӽ� üũ��, ���� �ػ� �α� ���Ϸ� ����
// 		if(bSaveFile)
// 		{
// 			// 2008-05-23 by cmkwon, üũ��
// 			//DbgOut("Resolution Idx(%3d) %4d x %4d , BitsPerPel(%2d) Frequency(%3d)\r\n", i, devMode.dmPelsWidth, devMode.dmPelsHeight, devMode.dmBitsPerPel, devMode.dmDisplayFrequency);
// 			char szResult[2048];
// 			util::zero(szResult, 2048);
// 			sprintf(szResult, "Resolution Idx(%3d) %4d x %4d , BitsPerPel(%2d) Frequency(%3d)\r\n", i, devMode.dmPelsWidth, devMode.dmPelsHeight, devMode.dmBitsPerPel, devMode.dmDisplayFrequency);
// 			resultLog.WriteSystemLog(szResult);
// 		}

// 2008-10-31 by cmkwon, ��ó(Luncher)���� �ػ� üũ�� �ȼ��� üũ�� ����(�����Ʈ�� üũ���� ����) - üũ �ʿ� ����
//		// 2008-06-12 by cmkwon, Win98, Win98ME ���� �ػ� 1���� ������ �ʴ� ���� ����(K0000227) - win98, win98ME ������ dmDisplayFrequency �� 0���� ���ϵǰ� ����.
//		if( 32 != devMode.dmBitsPerPel
//			|| (0 != devMode.dmDisplayFrequency && 60 != devMode.dmDisplayFrequency) )
//		{
//			continue;
//		}

		m_vectSupportedResolutionList.push_back(devMode);
	}

	return m_vectSupportedResolutionList.size();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::IsSupportedResolution(int i_nWidth, int i_nHeight)
/// \brief		// 2008-01-03 by cmkwon, �����ϴ� �ػ� ����Ʈ�� �����ֱ� - CAtumLauncherDlg::IsSupportedResolution() �߰�
/// \author		cmkwon
/// \date		2008-01-03 ~ 2008-01-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::IsSupportedResolution(int i_nWidth, int i_nHeight)
{
	int nCnts = m_vectSupportedResolutionList.size();
	if (i_nWidth == 0 && i_nHeight == 0)
	{
		return TRUE;
	}

	for(int i=0; i < nCnts; i++)
	{
		DEVMODE *pDevMode = &(m_vectSupportedResolutionList[i]);
		if(pDevMode->dmPelsWidth == i_nWidth
			&& pDevMode->dmPelsHeight == i_nHeight)
		{
			return TRUE;
		}
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::FindServerGroupName(CString *o_pcsServerGroupName, int i_nFindIndex)
/// \brief		// 2008-02-14 by cmkwon, ��ó���� �����׷� ���� ������ ���� ���࿡ ������ ������ ���� - CAtumLauncherDlg::FindServerGroupName() �߰�
/// \author		cmkwon
/// \date		2008-02-14 ~ 2008-02-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::FindServerGroupName(CString *o_pcsServerGroupName, int i_nFindIndex)
{
	o_pcsServerGroupName->Empty();
	int i = 0;
	for(i=0; i < m_vectServerGroupList.size(); i++)
	{
		if(i_nFindIndex == m_vectServerGroupList[i].nIndex)
		{
			*o_pcsServerGroupName = m_vectServerGroupList[i].szServerGroupName;
			return TRUE;
		}
	}
	return FALSE;
}





/*
BOOL CAtumLauncherDlg::SetCurrentClientVersion()
{
	const int SIZE_BUFF = 512;
	char buff[SIZE_BUFF];
	char *token;
	char seps[] = " \t";

	ifstream fin;

	CString cstrVersionFile = CLIENT_DOWNLOAD_DIR;
	cstrVersionFile += CLIENT_VERSION_FILE_NAME;
	fin.open((LPCTSTR)cstrVersionFile);

	if (! fin.is_open())
	{
#ifdef _ATUM_DEVELOP
		m_CurrentVersion.SetVersion(0, 0, 0, 0);
		return TRUE;
#else // _ATUM_DEVELOP
		return FALSE;
#endif // _ATUM_DEVELOP
	}

	fin.getline(buff, SIZE_BUFF);

	token = strtok(buff, seps);

	m_CurrentVersion.SetVersion(token);

	fin.close();

	return TRUE;
}
*/


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::NTStartNetworkCheck(void)
/// \brief		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ 
/// \author		cmkwon
/// \date		2007-06-18 ~ 2007-06-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::NTStartNetworkCheck(void)
{
	if(NULL == m_pUpdateWinsocket
		|| FALSE == m_pUpdateWinsocket->IsConnected()
		|| -1 != m_nCurNetworkCheckCount)
	{
		return FALSE;
	}


	// 2007-06-18 by cmkwon, �ʱ�ȭ
	m_dwSumPacketTickGap		= 0;
	m_dwNetworkCheckSendTick	= timeGetTime();

	INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_NETWORK_CHECK, T_PC_CONNECT_NETWORK_CHECK, pNetCheck, SendBuf);
	pNetCheck->nCheckCount		= m_nCurNetworkCheckCount;	
	m_pUpdateWinsocket->Write(SendBuf, MSG_SIZE(MSG_PC_CONNECT_NETWORK_CHECK));
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::NTOnReceivedNetworkCheckOK(int i_nCheckCount)
/// \brief		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
/// \author		cmkwon
/// \date		2007-06-18 ~ 2007-06-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::NTOnReceivedNetworkCheckOK(int i_nCheckCount)
{
	if(NULL == m_pUpdateWinsocket
		|| FALSE == m_pUpdateWinsocket->IsConnected()
		|| m_nCurNetworkCheckCount != i_nCheckCount)
	{
		return NTGetPingAverageTime();
	}
	
	DWORD dwCurTick				= timeGetTime();

	m_nCurNetworkCheckCount++;
	m_dwSumPacketTickGap		+= dwCurTick - m_dwNetworkCheckSendTick;

	Sleep(500);		// 2007-06-19 by cmkwon, �ణ�� �ð����� �д�

	m_dwNetworkCheckSendTick	= timeGetTime();

	if(m_nMaxNetworkCheckCount <= m_nCurNetworkCheckCount)
	{
		return NTGetPingAverageTime();
	}
	INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_NETWORK_CHECK, T_PC_CONNECT_NETWORK_CHECK, pNetCheck, SendBuf);
	pNetCheck->nCheckCount		= m_nCurNetworkCheckCount;	
	m_pUpdateWinsocket->Write(SendBuf, MSG_SIZE(MSG_PC_CONNECT_NETWORK_CHECK));

	return NTGetPingAverageTime();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::NTGetPingAverageTime(void)
/// \brief		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
/// \author		cmkwon
/// \date		2007-06-19 ~ 2007-06-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::NTGetPingAverageTime(void)
{
	if(0 >= m_nCurNetworkCheckCount)
	{// 2007-06-19 by cmkwon, ���ۻ��°� �ƴϰų� ó�� ��Ŷ�� ���� ���� ���� �ϰ��

		return 0;		// 2007-06-21 by cmkwon, ��� Ping �ӵ��� �����ϵ��� ������ - 
	}

	DWORD dwAverageTick = m_dwSumPacketTickGap/m_nCurNetworkCheckCount;

// 2007-06-21 by cmkwon, ��� Ping �ӵ��� �����ϵ��� ������
//	const int nBestStateTick	= 100;
//	const int nWorstStateTick	= 300;
//	if(dwAverageTick <= nBestStateTick)
//	{
//		nRetState = 100;
//	}
//	else if(dwAverageTick >= nWorstStateTick)
//	{
//		nRetState = 1;
//	}
//	else
//	{
//		nRetState = 100 - ( 100 * (dwAverageTick-nBestStateTick) )/(nWorstStateTick - nBestStateTick);
//	}
//	

// 2007-07-13 by cmkwon, �ʿ� ����
//	DbgOut("	 AverageTickGap[%8d] <== Count(%d), SumTickGap(%8d)\r\n"
//		, dwAverageTick, m_nCurNetworkCheckCount, m_dwSumPacketTickGap);

	return dwAverageTick;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::NTCheckTimeOver(DWORD *o_pdwPingTime)
/// \brief		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
/// \author		cmkwon
/// \date		2007-06-19 ~ 2007-06-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::NTCheckTimeOver(DWORD *o_pdwPingTime)
{
	if(0 > m_nCurNetworkCheckCount
		|| m_nMaxNetworkCheckCount <= m_nCurNetworkCheckCount)
	{
		return FALSE;
	}

	DWORD dwCurTick				= timeGetTime();
	if(TICKGAP_NETWORK_STATE_WORST_PING_TICK > dwCurTick - m_dwNetworkCheckSendTick)
	{// 2007-06-19 by cmkwon, ó���� �ʿ� �����Ƿ� �׳� ���� ���¸� ����
		*o_pdwPingTime = NTGetPingAverageTime();
	}
	else
	{
		// 2007-06-19 by cmkwon, ���� ��Ŷ�� �ʱ�ȭ �ϰ� ���� ��Ŷ ����
		*o_pdwPingTime = NTOnReceivedNetworkCheckOK(m_nCurNetworkCheckCount);
	}

	return TRUE;
}


char* CAtumLauncherDlg::GetFileName(char *szFullPathName, char *szFileName)
{
	char *token;
	char seps[] = "/";
	int len = strlen(szFullPathName);

	strcpy(szFileName, szFullPathName);

	token = strtok(szFileName, seps);
	len -= strlen(token);

	while( len > 7 )
	{
		token = strtok(NULL, seps);
		len -= strlen(token);
	}

	util::strncpy(szFileName, token, SIZE_MAX_FTP_FILE_PATH);

	return szFileName;
}

// devide���ڸ� ���� ����Ʈ�� �ִ´�.
BOOL CAtumLauncherDlg::Tokenizer(CList <CString, CString&>& lsString, CString strMsg, TCHAR devide)
{
	if( strMsg.IsEmpty() ) return FALSE;
	int nStart = 0;
	int pos;
	if( strMsg[strMsg.GetLength()-1] != devide )
		strMsg += devide;
	pos = strMsg.Find( devide, nStart );
	if( pos == -1)
		lsString.AddTail( strMsg );
	while( (pos = strMsg.Find( devide, nStart )) != -1 )	{
		lsString.AddTail( strMsg.Mid( nStart, pos - nStart ) );
		nStart = pos+1;
	}
	return TRUE;
}

int CAtumLauncherDlg::CreateDirectory(CString strParent, CList<CString, CString&> &lsDir)
{
	POSITION pos = lsDir.GetHeadPosition();
	strParent += lsDir.GetNext(pos);
	if(pos)// �������� ���丮�� �ƴ� ������ ����
	{
		CFileFind finder;
		if(finder.FindFile(strParent))
		{

		    finder.FindNextFile();
			if(!finder.IsDirectory())
			{
				DeleteFile(strParent); // ���Ϸ� �����ϸ� �����.
				if(!::CreateDirectory(strParent,NULL))
					return -1;
			}
		} else
			if(!::CreateDirectory(strParent,NULL))
				return -1;

		lsDir.GetPrev(pos);
		lsDir.RemoveAt(pos);
		strParent += '/';
		if(CreateDirectory(strParent,lsDir)==-1)
			return -1;
	}
	return 0;

}

void CAtumLauncherDlg::SetProgressRange(int up)
{
	m_progressCtrl.SetRange32(0, up);
}

void CAtumLauncherDlg::SetProgressPos(int pos)
{
	m_progressCtrl.SetPos(pos);
}

void CAtumLauncherDlg::SetFileNumText(char* str)
{
	CWnd *pWndStatus = GetDlgItem(IDC_DOWNLOAD_FILENUM);
// 2007-09-11 by cmkwon, �Ʒ��� ���� ������
//	InvalidateRect(CRect(90,579,190,592),true);
	InvalidateRect(CRect(EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X,EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y,EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X + EXE2_BG_DOWNLOAD_FILE_STATIC_WIDTH,EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y+EXE2_BG_DOWNLOAD_FILE_STATIC_HEIGHT),true);
	
	pWndStatus->SetWindowText(str);
}

void CAtumLauncherDlg::SetProgressGroupText(const char* str)
{
	//ysw : ����
	CWnd *pWndStatus = GetDlgItem(IDC_FILE_INFO);
	// 7/10/2006 by dgwoo �۾��� �ܻ��� ���°��� �������� �κ�.

// 2007-09-11 by cmkwon, �Ʒ��� ���� ������
//	InvalidateRect(CRect(190,579,480, 592),true);
	InvalidateRect(CRect(EXE2_BG_UPDATE_INFO_STATIC_POS_X,EXE2_BG_UPDATE_INFO_STATIC_POS_Y,EXE2_BG_UPDATE_INFO_STATIC_POS_X+EXE2_BG_UPDATE_INFO_STATIC_WIDTH, EXE2_BG_UPDATE_INFO_STATIC_POS_Y+EXE2_BG_UPDATE_INFO_STATIC_HEIGHT),true);
	
	CPaintDC dc(this);
	CBitmap *oldbitmap;
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	oldbitmap = (CBitmap *)memDC.SelectObject(&m_BackGround);
	dc.BitBlt(EXE2_BG_UPDATE_INFO_STATIC_POS_X,EXE2_BG_UPDATE_INFO_STATIC_POS_Y,EXE2_BG_UPDATE_INFO_STATIC_WIDTH,EXE2_BG_UPDATE_INFO_STATIC_HEIGHT, &memDC,EXE2_BG_UPDATE_INFO_STATIC_POS_X,EXE2_BG_UPDATE_INFO_STATIC_POS_Y,SRCCOPY);
	memDC.SelectObject(oldbitmap);
	memDC.DeleteDC();
	
	WCHAR wcText[1024]; 
	util::zero(wcText, sizeof(wcText)); 
	// 2008-05-09 by cmkwon, CodePage ���� �߰� - 
	//MultiByteToWideChar(1258, 0, str, strlen(str)+1, wcText, sizeof(wcText)/sizeof(wcText[0])); 
	MultiByteToWideChar(CODE_PAGE, 0, str, strlen(str)+1, wcText, sizeof(wcText)/sizeof(wcText[0])); 
	::SetWindowTextW(pWndStatus->GetSafeHwnd(), wcText);
}


void CAtumLauncherDlg::OnCancel()
{
	// TODO: Add extra cleanup here
	m_bCancelFlag = TRUE;
	if (!m_bProcessingVersionUpdate)
	{
//		AtumMessageBox("Operation Canceled!");
	}
// start 2012-02-09 by hskim, ��Ʈ�� X-Trap -> VTC ����� ����
/*	if(m_pVTCGuard)
	{
		m_pVTCGuard->SetUpdateThreadCancelFlag(TRUE);
		Sleep(100);
		m_pVTCGuard->ThreadEnd(1000);
		util::del(m_pVTCGuard);
	}								*/						
// end 2012-02-09 by hskim, ��Ʈ�� X-Trap -> VTC ����� ����

	CDialog::OnCancel();
}

void CAtumLauncherDlg::DisableControls()
{
	m_bControlEnabled = FALSE;

	GetDlgItem(IDC_EDIT_ACCOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDGO)->EnableWindow(FALSE);
	m_KbcGO.SetButtonDisable();
	GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST)->EnableWindow(FALSE);

	GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(FALSE);	// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - ���� ����
	GetDlgItem(IDC_CHECK_WINDOWS_MODE)->EnableWindow(FALSE);			// 2008-01-17 by cmkwon, �������� ���� �����ϱ� - ���� ����

	m_ctlBtnRememberID.EnableWindow(FALSE);			// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - üũ�ڽ� ��ġ
	m_ctlChckVsync.EnableWindow(FALSE);

	//ysw : ����
//	GetDlgItem(IDC_DECA_SERVER)->EnableWindow(FALSE);
//	GetDlgItem(IDC_BATTALUS_SERVER)->EnableWindow(FALSE);
//	GetDlgItem(IDC_SHARRINE_SERVER)->EnableWindow(FALSE);
//	GetDlgItem(IDC_PHILON_SERVER)->EnableWindow(FALSE);


	SendDlgItemMessage(IDOK, BM_SETSTYLE, BS_PUSHBUTTON, (LONG)TRUE);
	SendDlgItemMessage(IDCANCEL, BM_SETSTYLE, BS_DEFPUSHBUTTON, (LONG)TRUE);
	GetDlgItem(IDCANCEL)->SetFocus();
}

void CAtumLauncherDlg::EnableControls()
{
//	DbgOut("	2007-07-13 by cmkwon, 111\r\n");	// 2007-07-13 by cmkwon, �׽�Ʈ 
	m_bControlEnabled = TRUE;

	int nLower, nUpper;
	m_progressCtrl.GetRange(nLower, nUpper);
	m_progressCtrl.SetPos(nUpper);

	GetDlgItem(IDC_EDIT_ACCOUNT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDGO)->EnableWindow(TRUE);
	m_KbcGO.SetButtonEnable();
// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - ���� ����
//	if (m_nWindowModeReg == GAME_MODE_WINDOW)
//	{
//		GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(FALSE);
//	}
//	else
//	{
//		GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(TRUE);
//	}
	GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(TRUE);	// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - ���� ����
	GetDlgItem(IDC_CHECK_WINDOWS_MODE)->EnableWindow(TRUE);				// 2008-01-17 by cmkwon, �������� ���� �����ϱ� - ���� ����
	GetDlgItem(IDC_LIST)->EnableWindow(TRUE);

	m_ctlBtnRememberID.EnableWindow();			// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - üũ�ڽ� ��ġ

	// 2015-12-16 Future, Vsync setting
	m_ctlChckVsync.EnableWindow();

	GetDlgItem(IDC_EDIT_ACCOUNT)->GetWindowText(m_szAccountNameReg);
	if (m_szAccountNameReg == "")
	{
		GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
	}
	else
	{
		GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetSel(0, -1);
	}
#ifdef _DEBUG
	//	- beta service������ ���� ���� �Ұ�����, 12.16.

//ysw : ����
//	GetDlgItem(IDC_DECA_SERVER)->EnableWindow(TRUE);
//	GetDlgItem(IDC_BATTALUS_SERVER)->EnableWindow(TRUE);
//	GetDlgItem(IDC_SHARRINE_SERVER)->EnableWindow(TRUE);
//	GetDlgItem(IDC_PHILON_SERVER)->EnableWindow(TRUE);
	//*/
#endif
	// reset default button
	SendDlgItemMessage(IDCANCEL, BM_SETSTYLE, BS_PUSHBUTTON, (LONG)TRUE);
	SendDlgItemMessage(IDOK, BM_SETSTYLE, BS_DEFPUSHBUTTON, (LONG)TRUE);
//	DbgOut("	2007-07-13 by cmkwon, 222\r\n");	// 2007-07-13 by cmkwon, �׽�Ʈ 
}

void CAtumLauncherDlg::SetPrivateIP()
{
	// �ڽ��� IP Address�� ���Ѵ�
	char	host[100];
	HOSTENT	*p;
	char	ip[SIZE_MAX_IPADDRESS];

	gethostname(host, 100);
	if(p = gethostbyname(host))
	{
		sprintf(ip, "%d.%d.%d.%d", (BYTE)p->h_addr_list[0][0], (BYTE)p->h_addr_list[0][1],(BYTE)p->h_addr_list[0][2], (BYTE)p->h_addr_list[0][3]);
		util::strncpy(m_PrivateIP, ip, SIZE_MAX_IPADDRESS);
	}
}

BOOL CAtumLauncherDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DestroyWindow();
}

void CAtumLauncherDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default


	if (nIDEvent == TIMERID_CONNECT_PRESERVER)
	{
		KillTimer(TIMERID_CONNECT_PRESERVER);

		BOOL ret = ConnectPreServer();

		if (ret)
		{
			// succeeded
			m_SelectFlag = TRUE;
//			m_nServerGroupReg = SERVER_DECA;
			m_nServer = SERVER_DECA;

//ysw : ����
			// Set default radio button
/*			int ServerGroup = IDC_DECA_SERVER;
			if ( m_nServerGroupReg == SERVER_DECA )
			{
				ServerGroup = IDC_DECA_SERVER;
			}
			else if ( m_nServerGroupReg == SERVER_BATTALUS )
			{
				ServerGroup = IDC_BATTALUS_SERVER;
			}
			else if ( m_nServerGroupReg == SERVER_SHARRINE )
			{
				ServerGroup = IDC_SHARRINE_SERVER;
			}
			else if ( m_nServerGroupReg == SERVER_PHILON )
			{
				ServerGroup = IDC_PHILON_SERVER;
			}
*/
		#ifdef _DEBUG
//			CButton* pBtn= (CButton* )GetDlgItem(ServerGroup);
//			pBtn->SetCheck( TRUE );
		#else
//			CButton* pBtn= (CButton* )GetDlgItem(IDC_BATTALUS_SERVER);
//			pBtn->SetCheck( TRUE );

		//ysw : ����
//			GetDlgItem(IDC_DECA_SERVER)->EnableWindow(FALSE);
//			GetDlgItem(IDC_BATTALUS_SERVER)->EnableWindow(FALSE);
//			GetDlgItem(IDC_SHARRINE_SERVER)->EnableWindow(FALSE);
//			GetDlgItem(IDC_PHILON_SERVER)->EnableWindow(FALSE);
		#endif

			CString txt = m_CurrentVersion.GetVersionString();
			SetFileNumText((char*)(LPCTSTR)("VER " + txt));

			// set account name
// 2005-08-22 by cmkwon, for jpn alpha test
// 2007-03-06 by cmkwon, for debug
//#if defined(_DEBUG) || (  !defined(_MASANG15_SERVER) && (!defined(_MASANG51_SERVER)) && (!defined(_GLOBAL_ENG_SERVER)) && (!defined(_VTC_VIET_SERVER)) && (!defined(_KOREA_SERVER_2))  )

// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - �Ʒ��� ���� ���� ��
// #if defined(_DEBUG)
// 			GetDlgItem(IDC_EDIT_ACCOUNT)->SetWindowText(m_szAccountNameReg);
// 			GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(m_szPasswordReg);
// 			((CEdit*)GetDlgItem(IDC_EDIT_ACCOUNT))->SetSel(0, -1);
// #endif

#if defined(_DEBUG)
			// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
			GetDlgItem(IDC_EDIT_ACCOUNT)->SetWindowText(m_szAccountNameReg);
			GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(m_szPasswordReg);


#elif defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1) || defined(SERVICE_TYPE_ARGENTINA_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)|| defined (SERVICE_TYPE_VIETNAMESE_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_1)
			// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - ����� AccountName �� �����Ѵ�.
			GetDlgItem(IDC_EDIT_ACCOUNT)->SetWindowText(m_szAccountNameReg);
#endif

#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
			// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - ���� �����ϱ�
			GetDlgItem(IDC_EDIT_ACCOUNT)->SetWindowText(m_szAccountNameReg);
#endif 
	//		m_szAccountNameReg = "��������\r\nTest��...\r\n������Ʈ ����\r\n���ָ� �߰�\r\n������ �߰�\r\n66\r\n77\r\n88\r\n99\r\n00\r\n00\r\n11\r\n22\r\n33\r\n44\r\n55\r\n";
	//		GetDlgItem(IDC_NOTICE)->SetWindowText(m_szAccountNameReg);


		}
		else
		{
			// failed
			EndDialog(-1);
			return;
		}
	}
	else if (nIDEvent == TIMERID_ENABLE_CONTROL)
	{
		KillTimer(nIDEvent);
		EnableControls();
	}
	else if(nIDEvent == TIMERID_SEND_ALIVE_PACKET)
	{
		if(m_pUpdateWinsocket
			&& m_pUpdateWinsocket->IsConnected())
		{
			m_pUpdateWinsocket->WriteMessageType(T_PC_CONNECT_ALIVE);
		}
	}
	else if(TIMERID_NETWORK_STATE_CHECK == nIDEvent)
	{// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ

		DWORD dwPingGapTick = 0;
		if(this->NTCheckTimeOver(&dwPingGapTick))
		{
			// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ - ȭ�鿡 ǥ��
			m_ServerList->UpdateNetworkState(this->NTGetPingAverageTime());		// 2007-06-22 by cmkwon, �߱� ��Ʈ��ũ ���� �����ֱ� -
			m_ServerList->Invalidate();											// 2007-06-22 by cmkwon, �߱� ��Ʈ��ũ ���� �����ֱ� -
		}
	}

	CDialog::OnTimer(nIDEvent);
}


//ysw : �߰�
void CAtumLauncherDlg::OnJoin()
{
	// TODO: Add your control notification handler code here
	CString strTmp;
	strTmp.Format("%s/%s", STRMSG_S_GAMEHOMEPAGE_DOMAIN, URL_REGISTER_PAGE);
	ShellExecute(NULL, "open", strTmp, NULL, NULL, SW_SHOWNORMAL);
}

void CAtumLauncherDlg::OnSecret()
{
	// TODO: Add your control notification handler code here
	WinExec("explorer.exe http://www.atumonline.com/7_members/login.asp ", SW_SHOW);
}

void CAtumLauncherDlg::OnEnd()
{
	// TODO: Add your control notification handler code here
	CDialog::DestroyWindow();
}

void CAtumLauncherDlg::OnDeca()
{
	// TODO: Add your control notification handler code here
	m_SelectFlag = TRUE;
	m_nServer = SERVER_DECA;
}

void CAtumLauncherDlg::OnBattal()
{
	// TODO: Add your control notification handler code here

}

void CAtumLauncherDlg::OnSharin()
{
	// TODO: Add your control notification handler code here

}

void CAtumLauncherDlg::OnPhilon()
{
	// TODO: Add your control notification handler code here

}

#define CUR_BAR_X		170
#define CUR_BAR_Y		41
#define CUR_BAR_WIDTH	258
#define CUR_BAR_HEIGHT	20

/*--------------------------------------------------------------------
	 DrawProgressBar
--------------------------------------------------------------------*/
int CAtumLauncherDlg::DrawProgressBar()
{
	CClientDC	dc(this);
	CDC			MemDC;
	CBitmap		* pOldBmp;
	CBrush		BlueBrush(RGB(0, 84, 166));
	CBrush		GrayBrush(RGB(109, 207, 246));

	CRect		ProRect;
	CBitmap		Percent;

	char		 Junk[10];
	TEXTMETRIC	 TextMetric;

	MemDC.CreateCompatibleDC(&dc);
	Percent.CreateCompatibleBitmap(&dc, CUR_BAR_WIDTH, CUR_BAR_HEIGHT);
	pOldBmp = (CBitmap *)MemDC.SelectObject(&Percent);

	ProRect.SetRect(0, 0, CUR_BAR_WIDTH, CUR_BAR_HEIGHT);
	MemDC.FillRect(&ProRect, &GrayBrush);
	ProRect.SetRect(0, 0, m_Cur_Rect , CUR_BAR_HEIGHT);
	MemDC.FillRect(&ProRect, &BlueBrush);

	MemDC.SetBkMode(TRANSPARENT);
	MemDC.SetTextColor(RGB(0, 0, 0));
	MemDC.GetTextMetrics(&TextMetric);

	wsprintf(Junk, "%d%%", m_Cur_Percent);
	MemDC.TextOut(CUR_BAR_WIDTH/2 - (TextMetric.tmAveCharWidth * lstrlen(Junk)/2),
				CUR_BAR_HEIGHT/2 - (TextMetric.tmHeight/2), (LPCSTR)Junk, lstrlen(Junk));

	dc.BitBlt(CUR_BAR_X, CUR_BAR_Y, CUR_BAR_WIDTH, CUR_BAR_HEIGHT, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(&pOldBmp);

	return	true;
}


/*----------------------------------------------------------------------------*
*			Set_Cur_Percent
*-----------------------------------------------------------------------------*/
void CAtumLauncherDlg::Set_Cur_Percent(DWORD CurSize)
{
	m_Cur_Percent = CurSize;
	if(m_Cur_Percent > 100) m_Cur_Percent = 100;

	m_Cur_Rect = (int)( (m_Cur_Percent*CUR_BAR_WIDTH)/100 );
}

void CAtumLauncherDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnLButtonDown(nFlags, point);

	// fake windows into thinking your clicking on the caption, does not
	// maximizeon double click
	
	// ���콺�� ��� ������ �̵�
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

//	if(m_FTPUpdateState == UPDATE_STATE_DOWNLOADING)
//	{
//		AtumMessageBox("���� �ֽ� ������Ʈ�� ���� �� �Դϴ�.\n\n������Ʈ �Ϸ� �� ���� ��ư�� Ŭ���� �ּ���.");
//	}
}


UINT CAtumLauncherDlg::OnNcHitTest(CPoint point)
{
     UINT nHitTest = CDialog::OnNcHitTest( point );
     // also fake windows out, but this maximizes the window
     // when you double click on it.
     return (nHitTest == HTCLIENT) ? HTCAPTION : nHitTest;
}


HBRUSH CAtumLauncherDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	switch(nCtlColor)
	{
	case CTLCOLOR_EDIT:
		{		
			if((GetDlgItem(IDC_EDIT_ACCOUNT)->m_hWnd == pWnd->m_hWnd)
				|| (GetDlgItem(IDC_EDIT_PASSWORD)->m_hWnd == pWnd->m_hWnd))
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetBkColor(RGB(0, 0, 0));
				pDC->SetTextColor(RGB(255, 255, 255));
				return m_StaticBrushBlack;
			}
		}
		break;
		
	case CTLCOLOR_STATIC:
		{
			if(GetDlgItem(IDC_FILE_INFO)->m_hWnd == pWnd->m_hWnd)
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(EXE2_BG_UPDATE_INFO_FONT_COLOR);		
				return (HBRUSH)GetStockObject(NULL_BRUSH);
			}
			else if(GetDlgItem(IDC_DOWNLOAD_FILENUM)->m_hWnd == pWnd->m_hWnd)
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(EXE2_BG_DOWNLOAD_FILE_FONT_COLOR);		
				return (HBRUSH)GetStockObject(NULL_BRUSH);
			}
			else if(GetDlgItem(IDC_CHARACTER_NAME)->m_hWnd == pWnd->m_hWnd )
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetBkColor(RGB(0, 0, 0));
				pDC->SetTextColor(RGB(255, 255, 255));		
				return m_StaticBrushGray;
			}
		}
		break;
	case CTLCOLOR_LISTBOX:
		{
			if(GetDlgItem(IDC_LIST)->m_hWnd == pWnd->m_hWnd )
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetBkColor(RGB(29, 29, 40));
				pDC->SetTextColor(RGB(189,194,198));
				return m_listBrush;
			}
		}
		break;
	default:
		{			
		}
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
//void CAtumLauncherDlg::ExecGame(char *cmdLine)
void CAtumLauncherDlg::ExecGame(char *cmdLine, char *i_szAppPath/*=NULL*/, char *i_szCmdParam/*=NULL*/)
{
#ifdef _ATUM_DEVELOP
	SetCurrentDirectory(m_szExecutePathReg);
#endif


#if defined(SERVICE_TYPE_VIETNAMESE_SERVER_1)
	m_pVTCGuard->Run(i_szAppPath, i_szCmdParam);

	return ;
#endif	// SERVICE_TYPE_VIETNAMESE_SERVER_1
// 2012-02-09 by hskim, ��Ʈ�� X-Trap -> VTC ����� ����

	/*
#if defined(SERVICE_TYPE_ENGLISH_SERVER_1)		// 2012-02-09 by hskim, ��Ʈ�� X-Trap -> VTC ����� ����
	///////////////////////////////////////////////////////////////////////////////
	// 2009-10-29 by cmkwon, ��Ʈ�� X-TRAP �ڵ�������Ʈ ��� ���� - CAtumLauncherDlg::ExecGame#,
	XTrap_L_Patch(XTRAP_KEY_STRING, NULL, 60);
#endif
	*/
// start 2012-03-21 by hskim, �ٽ��� ��� �߰� [�ڵ� ������Ʈ/�ɼ� �߰�/����͸� �ý���]
#ifdef S_HACK_SHIELD_AUTO_UPDATE_HSKIM
	// 2012-09-13 by jhseol, ĳ���� �ٽ��� ����
#ifdef S_HACK_SHIELD_REMOVE_JHSEOL
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "CANADA_HACK_SHIELD");
	if( NULL == hMutex )
	{
	DWORD dwRet = 0;
	char szFullFilePath[MAX_PATH]={ 0, };
	char szFolderGamePath[MAX_PATH]={ 0, };
	char szHackShieldPath[MAX_PATH]={ 0, };
	char szDir[_MAX_DIR] = { 0, };
	char szDrive[_MAX_DRIVE] = { 0, };
	AHNHS_EXT_ERRORINFO HsExtError = { 0, };

	ZeroMemory(&HsExtError,sizeof(HsExtError));

	strncpy(HsExtError.szServer, GAME_GUARD_MONITORING_SERVER_IP, MAX_PATH);
	strncpy(HsExtError.szUserId, m_szAccountName, MAX_PATH);
	strncpy(HsExtError.szGameVersion, m_CurrentVersion.GetVersionString(), SIZE_MAX_VERSION_STRING);

	::GetModuleFileName(NULL, szFullFilePath, MAX_PATH);

	_splitpath(szFullFilePath, szDrive, szDir, NULL, NULL);
	_makepath(szFolderGamePath, szDrive, szDir, NULL, NULL);

	sprintf(szHackShieldPath, "%s\\HShield", szFolderGamePath);

	dwRet = _AhnHS_HSUpdateEx(
		szHackShieldPath,
		1000 * 600,		// 600�� = 10 �� 
		HACKSHIELD_GAME_CODE,
		AHNHSUPDATE_CHKOPT_HOSTFILE | AHNHSUPDATE_CHKOPT_GAMECODE, 
		HsExtError,
		1000* 20);		// 20��

	if ( dwRet != ERROR_SUCCESS) 
	{ 
		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0035);

		return ;
	}
	}
#endif	// #ifdef S_HACK_SHIELD_REMOVE_JHSEOL
	// end 2012-09-13 by jhseol, ĳ���� �ٽ��� ����
#endif
// end 2012-03-21 by hskim, �ٽ��� ��� �߰� [�ڵ� ������Ʈ/�ɼ� �߰�/����͸� �ý���]

	UINT ret = WinExec(cmdLine, SW_SHOWNORMAL);
	//DbgOut("EXE 2 CommandLine : %s, RetCode(%d)\r\n", cmdLine, ret);		// 2007-05-16 by cmkwon
	if ( ret <= 31 )	// exec failed...
	{
		switch (ret)
		{
		case 0:						// The system is out of memory or resources.
			AtumMessageBox(STRERR_S_ATUMLAUNCHER_0031);
			break;
		case ERROR_BAD_FORMAT:		// The .exe file is invalid.
			AtumMessageBox(STRERR_S_ATUMLAUNCHER_0032);
			break;
		case ERROR_FILE_NOT_FOUND:	// The specified file was not found.
#ifdef _ATUM_DEVELOP
			AtumMessageBox(CString("File not Found!\nbin: ") + cmdLine
				+ "\npath: " + m_szExecutePathReg);
#else
			AtumMessageBox(STRERR_S_ATUMLAUNCHER_0033);
#endif
			break;
		case ERROR_PATH_NOT_FOUND:	// The specified path was not found.
			AtumMessageBox(STRERR_S_ATUMLAUNCHER_0034);
			break;
		default:
			break;
		}
	}
}

void CAtumLauncherDlg::OnSelchangeList()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE) ;
	int nSel = m_ctrlServerList.GetCurSel();
	if(m_ctrlServerList.GetServerCheck(nSel))
	{
		m_ctrlServerList.SetCurSel(nSel);
		m_nOldSel = nSel;
	}
	else
	{
		m_ctrlServerList.SetCurSel(m_nOldSel);
	}
}

void CAtumLauncherDlg::OnCan()
{
	// TODO: Add your control notification handler code here

	if (UPDATE_STATE_DOWNLOADING == m_FTPUpdateState || UPDATE_STATE_DOWNLOADED == m_FTPUpdateState)
	{

		if (m_pHttpManager)
		{
			m_pHttpManager->ThreadEnd(1000);
			util::del(m_pHttpManager);
			this->SetFTPUpdateState(UPDATE_STATE_INIT);
		}

		VersionInfo OldVersion(m_msg_PC_CONNECT_UPDATE_INFO.OldVersion);
		VersionInfo UpdateVersion(m_msg_PC_CONNECT_UPDATE_INFO.UpdateVersion);
		char szUpdateFileName[256];
		sprintf(szUpdateFileName, "%s_%s.zip", OldVersion.GetVersionString(), UpdateVersion.GetVersionString());
		DeleteFile(szUpdateFileName);
	}
	CDialog::OnCancel();
}

BOOL CAtumLauncherDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (m_bControlEnabled)
		{
			OnOk();
		}
		return TRUE;
	}

///////////////////////////////////////////////////////////////////////////////
// 2009-07-08 by cmkwon, ���þ� ��ó ���� ��û(���콺��Ŭ�� ����) - 	
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)
	if(WM_RBUTTONDOWN == pMsg->message)
	{
		return TRUE;
	}
#endif

	return CDialog::PreTranslateMessage(pMsg);
}



LONG CAtumLauncherDlg::OnUpdateFileDownloadError(WPARAM wParam, LPARAM lParam)
{
	if(UPDATE_STATE_DOWNLOADING != m_FTPUpdateState){		return FALSE;}

	char szErrString[1024];
	char szErrAddStr[1024];
	util::zero(szErrString, 1024);
	util::zero(szErrAddStr, 1024);
// 2007-01-05 by cmkwon, �Ʒ��� ���� ERR_XXX�� ������
//	switch(wParam)
//	{
//	case DOWNLOAD_ERR_FTP_CONNECT:
//		{
//			strcpy(szErrAddStr, STRERR_S_ATUMEXE_0006);
//		}
//		break;
//	case DOWNLOAD_ERR_FTP_OPENFILE:
//		{
//			strcpy(szErrAddStr, STR_DOWNLOAD_ERR_FTPCONNECT);
//		}
//		break;
//	case DOWNLOAD_ERR_CREATE_LOCAL_FILE:
//		{
//			strcpy(szErrAddStr, STR_DOWNLOAD_ERR_CREATE_LOCAL_FILE);
//		}
//		break;
//	case DOWNLOAD_ERR_READ_REMOTE_FILE:
//		{
//			strcpy(szErrAddStr, STR_DOWNLOAD_ERR_READ_REMOTE_FILE);
//		}
//		break;
//	default:
//		{
//			wsprintf(szErrAddStr, "Nomal download error(%d) !!", wParam);
//		}
//	}
	switch(wParam)
	{
	case ERR_CANNOT_CONNECT_AUTO_UPDATE_SERVER:
		{
			strcpy(szErrAddStr, STRERR_S_ATUMEXE_0006);
		}
		break;
	case ERR_LOCAL_FILE_CREATE_FAIL:
		{
			strcpy(szErrAddStr, STRCMD_CS_COMMON_DOWNLOAD_0001);
		}
		break;
	case ERR_UPDATE_FILE_NOT_FOUND:
		{
			strcpy(szErrAddStr, STRCMD_CS_COMMON_DOWNLOAD_0000);
		}
		break;
	case ERR_UPDATE_FILE_DOWNLOADING_FAIL:	
		{
			strcpy(szErrAddStr, STRCMD_CS_COMMON_DOWNLOAD_0002);
		}
		break;
	default:
		{
			wsprintf(szErrAddStr, "Nomal download error(%d) !!", wParam);
		}
	}

	wsprintf(szErrString, STRMSG_060526_0001
		, STRMSG_S_GAMEHOMEPAGE_DOMAIN, szErrAddStr);
	AtumMessageBox(szErrString);
	OnCancel();
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			LONG CAtumLauncherDlg::OnUpdateFileDownloadInit(WPARAM wParam, LPARAM lParam)
/// \brief		
/// \author		cmkwon
/// \date		2007-01-08 ~ 2007-01-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
LONG CAtumLauncherDlg::OnUpdateFileDownloadInit(WPARAM wParam, LPARAM lParam)
{
	m_progressCtrl.SetRange32(0, wParam);
	m_progressCtrl.SetPos(0);
	return TRUE;
}

LONG CAtumLauncherDlg::OnUpdateFileDownloadProgress(WPARAM wParam, LPARAM lParam)
{
	if(UPDATE_STATE_DOWNLOADING != m_FTPUpdateState){		return FALSE;}

	m_progressCtrl.SetPos(wParam);
	return TRUE;
}

// 2015-12-21 DevX
bool UpdateToDirectX9C()
{
	PROCESS_INFORMATION processInformation = { 0 };
	STARTUPINFO startupInfo = { 0 };
	startupInfo.cb = sizeof(startupInfo);

	// Create the process
	BOOL result = CreateProcess(NULL, ".\\Res-Sys\\DXSETUP.exe /silent", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);

	if (!result) return false;
	else
	{
		// Successfully created the process.  Wait for it to finish.
		WaitForSingleObject(processInformation.hProcess, INFINITE);

		// Get the exit code.
		//result = GetExitCodeProcess(processInformation.hProcess, &exitCode);

		// Close the handles.
		CloseHandle(processInformation.hProcess);
		CloseHandle(processInformation.hThread);

		//if (!result)
		//{
		//	// Could not get exit code.
		//	TRACE(_T("Executed command but couldn't get exit code.\nCommand=%s\n"), cmdLine);
		//	return FALSE;
		//}

		// We succeeded.
		return true;
	}
}

LONG CAtumLauncherDlg::OnUpdateFileDownloadOK(WPARAM wParam, LPARAM lParam)
{
	if(UPDATE_STATE_DOWNLOADING != m_FTPUpdateState){		return FALSE;}
	this->SetFTPUpdateState(UPDATE_STATE_DOWNLOADED);

	//if(m_pUpdateFTPManager)
	//{
	//	if (m_pUpdateFTPManager->m_threadDownload)
	//	{
	//		DWORD dwRet;
	//		dwRet = WaitForSingleObject(m_pUpdateFTPManager->m_hDownloadThread, 1000);
	//		if(WAIT_OBJECT_0 != dwRet)
	//		{
	//			// ������ WAIT_FAILED��
	//			int nError = GetLastError();
	//			SetLastError(0);
	//		}
	//		CloseHandle(m_pUpdateFTPManager->m_hDownloadThread);
	//		m_pUpdateFTPManager->m_hDownloadThread = NULL;

	//		Sleep(100);
	//	}

	//	delete m_pUpdateFTPManager;
	//	m_pUpdateFTPManager = NULL;
	//	this->SetFTPUpdateState(UPDATE_STATE_INIT);
	//}
	if(m_pHttpManager)
	{
		m_pHttpManager->ThreadEnd(1000);
		util::del(m_pHttpManager);		
		this->SetFTPUpdateState(UPDATE_STATE_INIT);
	}
	
	static USHORT oldver[SIZE_MAX_VERSION];
	static USHORT newver[SIZE_MAX_VERSION];

	memcpy(oldver, m_msg_PC_CONNECT_UPDATE_INFO.OldVersion, SIZE_MAX_VERSION * sizeof(USHORT));
	memcpy(newver, m_msg_PC_CONNECT_UPDATE_INFO.UpdateVersion, SIZE_MAX_VERSION * sizeof(USHORT));

	// update to dx9c here
	if (newver[0] == 4 && newver[1] == 5 && newver[2] == 1 && newver[3] == 1)
	{
		//AtumMessageBox("We will update DirectX for you, please wait.\n\nIf you cancel this update and the game does not run, you will have to manually install it yourself.\nDirectX Location : Nemerian\\Res-Sys\\DXSETUP.exe.");

		// extract update file
		ExtractUpdateFile(&m_msg_PC_CONNECT_UPDATE_INFO);

		auto func = [this]()
		{
			VersionInfo OldVer { oldver };
			VersionInfo UpdateVer { newver };

			SetProgressGroupText("Updating DirectX...");

			if (UpdateToDirectX9C())
			{
				SetProgressGroupText("Updated DirectX successfully!");

				m_CurrentVersion = UpdateVer;

				PostMessage(WM_DOWNLOAD_GAMEFILES_DONE);
			}
			else
			{
				SetProgressGroupText("Updating DirectX failed!");

				AtumMessageBox("Failed to update DirectX, please report this error to the server administrator.");
			}
		};

		thread t { func };

		t.detach();

		memset(&m_msg_PC_CONNECT_UPDATE_INFO, 0x00, sizeof(MSG_PC_CONNECT_UPDATE_INFO));

		return TRUE;
	}
	else
	{
		// extract update file
		ExtractUpdateFile(&m_msg_PC_CONNECT_UPDATE_INFO);

		// update completed
		VersionInfo OldVersion(m_msg_PC_CONNECT_UPDATE_INFO.OldVersion);
		VersionInfo UpdateVersion(m_msg_PC_CONNECT_UPDATE_INFO.UpdateVersion);

		char strBuffer[256];
		sprintf(strBuffer, STRMSG_S_ATUMLAUNCHER_0005, OldVersion.GetVersionString(), UpdateVersion.GetVersionString());
		SetProgressGroupText(strBuffer);

		// set current cliet version
		m_CurrentVersion = UpdateVersion;

		// On DownLoadGamefilesDone
		OnDownLoadGamefilesDone(NULL, NULL);

		memset(&m_msg_PC_CONNECT_UPDATE_INFO, 0x00, sizeof(MSG_PC_CONNECT_UPDATE_INFO));

		return TRUE;
	}
}
// start 2012-02-09 by hskim, ��Ʈ�� X-Trap -> VTC ����� ����
LONG CAtumLauncherDlg::OnUpdateVTCGuardOK(WPARAM wParam, LPARAM lParam)
{
	SetProgressGroupText(STRMSG_S_ATUMLAUNCHER_0015);

	m_bProcessingVersionUpdate = TRUE;
	EnableControls();
	
	return TRUE;
}
// end 2012-02-09 by hskim, ��Ʈ�� X-Trap -> VTC ����� ����

void CAtumLauncherDlg::OnMin() 
{
	// TODO: Add your control notification handler code here
	this->ShowWindow(SW_MINIMIZE);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumLauncherDlg::OnBtnHomepage() 
/// \brief		// 2007-09-27 by cmkwon, Homepage���� ��ư �߰�(��Ʈ�� VTC-Intecom ��û) - 
/// \author		cmkwon
/// \date		2007-09-27 ~ 2007-09-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumLauncherDlg::OnBtnHomepage() 
{
	// TODO: Add your control notification handler code here

	ShellExecute(NULL, "open", STRMSG_S_GAMEHOMEPAGE_DOMAIN, NULL, NULL, SW_SHOWNORMAL);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			char *CAtumLauncherDlg::GetPublicLocalIP(char *o_szLocalIP)
/// \brief		
/// \author		cmkwon
/// \date		2006-04-10 ~ 2006-04-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *CAtumLauncherDlg::GetPublicLocalIP(char *o_szLocalIP)
{
	GGetLocalIP(o_szLocalIP, IP_TYPE_PUBLIC);
	return o_szLocalIP;
}

void CAtumLauncherDlg::OnSetfocusEditAccount() 
{
	// TODO: Add your control notification handler code here
	if(NULL == m_pScreenKeyboardDlg)
	{
		return;
	}

	m_pInputEditFromScreenKeyboard = GetDlgItem(IDC_EDIT_ACCOUNT);	
}

void CAtumLauncherDlg::OnSetfocusEditPassword() 
{
	// TODO: Add your control notification handler code here
	
	if(NULL == m_pScreenKeyboardDlg)
	{
		return;
	}

	m_pInputEditFromScreenKeyboard = GetDlgItem(IDC_EDIT_PASSWORD);	

	///////////////////////////////////////////////////////////////////////////////
	// 2007-09-18 by cmkwon, ȭ��Ű���� ���� - ȭ��Ű���� �����쿡�� Hide ��ų��� ó���� ����
	if(FALSE == m_bHideScreenKeyboardByScreenKeyboardWindow)
	{
		// 2007-09-18 by cmkwon, ȭ��Ű���� ���� - �н����� �Է½ÿ��� Ȱ��ȭ �ȴ�.
		m_pScreenKeyboardDlg->ShowWindow(SW_SHOW);
	}
	m_bHideScreenKeyboardByScreenKeyboardWindow	= FALSE;
}

void CAtumLauncherDlg::OnBtnViewScreenKeyboard() 
{
	// TODO: Add your control notification handler code here

	if(NULL == m_pScreenKeyboardDlg)
	{
		return;
	}
	
	// 2007-09-11 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� - ȭ�� Ű���带 �����ش�
	m_pScreenKeyboardDlg->ShowWindow(SW_SHOW);
}

void CAtumLauncherDlg::OnCheckWindowsMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER);
	if(NULL == pComboBox)
	{
		return;
	}

	CString csBeforeWDegree;
	pComboBox->GetWindowText(csBeforeWDegree);

	
	
/*	/// 2012-05-10 by jhseol, ���þ� - EP4 �ö���鼭 ��� ����. �ּ�ó��
	// 2008-12-17 by ckPark ���þ� ����
	// // ���þƴ� üũ�ڽ�
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	this->InsertWindowDegreeList(pComboBox, m_ctrlCheckWindowMode.GetCheck());
#else
	this->InsertWindowDegreeList(pComboBox, m_ctlbWindowMode);
#endif
	// end 2008-12-17 by ckPark ���þ� ����
*/
	this->InsertWindowDegreeList(pComboBox, m_ctlbWindowMode);



	int nIdx = this->FindWindowDegreeComboBoxIndex(pComboBox, (LPSTR)(LPCSTR)csBeforeWDegree);
	nIdx = max(0, nIdx);
	pComboBox->SetCurSel(nIdx);
}

BOOL CAtumLauncherDlg::BitmapRgn( LPCTSTR resource, COLORREF TansColor ,int nx,int ny)
{
	HBITMAP			m_hBack;
	HINSTANCE hInstance = AfxGetInstanceHandle();
	
	HANDLE handle = ::LoadImage( hInstance, resource, IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS | LR_LOADFROMFILE );
   	
	if ( !handle ) return FALSE;
	
	m_hBack = (HBITMAP)handle;
	::SetWindowRgn( m_hWnd, BitmapToRegion( m_hBack, TansColor, TansColor, nx,ny) ,TRUE);
	
	return TRUE;
}

BOOL CAtumLauncherDlg::BitmapRgn( UINT resource, COLORREF TansColor,int nx,int ny )
{
	HBITMAP			m_hBack;
	HINSTANCE hInstance = AfxGetInstanceHandle();
	m_hBack = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(resource));
	::SetWindowRgn( m_hWnd, BitmapToRegion( m_hBack, TansColor, TansColor , nx,ny),TRUE);
	
	return TRUE;
}
HRGN CAtumLauncherDlg::BitmapToRegion(HBITMAP hBmp, COLORREF cTransparentColor/* = 0*/, COLORREF cTolerance/* = 0x101010*/,int nx,int ny)
{
	HRGN hRgn = NULL;

	if (hBmp)
	{
		// Create a memory DC inside which we will scan the bitmap content
		HDC hMemDC = CreateCompatibleDC(NULL);
		if (hMemDC)
		{
			// Get bitmap size
			BITMAP bm;
			GetObject(hBmp, sizeof(bm), &bm);

			// Create a 32 bits depth bitmap and select it into the memory DC 
			BITMAPINFOHEADER RGB32BITSBITMAPINFO = {	
					sizeof(BITMAPINFOHEADER),	// biSize 
					bm.bmWidth,					// biWidth; 
					bm.bmHeight,				// biHeight; 
					1,							// biPlanes; 
					32,							// biBitCount 
					BI_RGB,						// biCompression; 
					0,							// biSizeImage; 
					0,							// biXPelsPerMeter; 
					0,							// biYPelsPerMeter; 
					0,							// biClrUsed; 
					0							// biClrImportant; 
			};
			VOID * pbits32; 
			HBITMAP hbm32 = CreateDIBSection(hMemDC, (BITMAPINFO *)&RGB32BITSBITMAPINFO, DIB_RGB_COLORS, &pbits32, NULL, 0);
			if (hbm32)
			{
				HBITMAP holdBmp = (HBITMAP)SelectObject(hMemDC, hbm32);

				// Create a DC just to copy the bitmap into the memory DC
				HDC hDC = CreateCompatibleDC(hMemDC);
				if (hDC)
				{
					// Get how many bytes per row we have for the bitmap bits (rounded up to 32 bits)
					BITMAP bm32;
					GetObject(hbm32, sizeof(bm32), &bm32);
					while (bm32.bmWidthBytes % 4)
						bm32.bmWidthBytes++;

					// Copy the bitmap into the memory DC
					HBITMAP holdBmp = (HBITMAP)SelectObject(hDC, hBmp);
					BitBlt(hMemDC, nx, ny, bm.bmWidth, bm.bmHeight, hDC, 0, 0, SRCCOPY);

					// For better performances, we will use the ExtCreateRegion() function to create the
					// region. This function take a RGNDATA structure on entry. We will add rectangles by
					// amount of ALLOC_UNIT number in this structure.
					#define ALLOC_UNIT	100
					DWORD maxRects = ALLOC_UNIT;
					HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects));
					RGNDATA *pData = (RGNDATA *)GlobalLock(hData);
					pData->rdh.dwSize = sizeof(RGNDATAHEADER);
					pData->rdh.iType = RDH_RECTANGLES;
					pData->rdh.nCount = pData->rdh.nRgnSize = 0;
					SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);

					// Keep on hand highest and lowest values for the "transparent" pixels
					BYTE lr = GetRValue(cTransparentColor);
					BYTE lg = GetGValue(cTransparentColor);
					BYTE lb = GetBValue(cTransparentColor);
					BYTE hr = min(0xff, lr + GetRValue(cTolerance));
					BYTE hg = min(0xff, lg + GetGValue(cTolerance));
					BYTE hb = min(0xff, lb + GetBValue(cTolerance));

					// Scan each bitmap row from bottom to top (the bitmap is inverted vertically)
					BYTE *p32 = (BYTE *)bm32.bmBits + (bm32.bmHeight - 1) * bm32.bmWidthBytes;
					for (int y = 0; y < bm.bmHeight; y++)
					{
						// Scan each bitmap pixel from left to right
						for (int x = 0; x < bm.bmWidth; x++)
						{
							// Search for a continuous range of "non transparent pixels"
							int x0 = x;
							LONG *p = (LONG *)p32 + x;
							while (x < bm.bmWidth)
							{
								BYTE b = GetRValue(*p);
								if (b >= lr && b <= hr)
								{
									b = GetGValue(*p);
									if (b >= lg && b <= hg)
									{
										b = GetBValue(*p);
										if (b >= lb && b <= hb)
											// This pixel is "transparent"
											break;
									}
								}
								p++;
								x++;
							}

							if (x > x0)
							{
								// Add the pixels (x0, y) to (x, y+1) as a new rectangle in the region
								if (pData->rdh.nCount >= maxRects)
								{
									GlobalUnlock(hData);
									maxRects += ALLOC_UNIT;
									hData = GlobalReAlloc(hData, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), GMEM_MOVEABLE);
									pData = (RGNDATA *)GlobalLock(hData);
								}
								RECT *pr = (RECT *)&pData->Buffer;
								SetRect(&pr[pData->rdh.nCount], x0, y, x, y+1);
								if (x0 < pData->rdh.rcBound.left)
									pData->rdh.rcBound.left = x0;
								if (y < pData->rdh.rcBound.top)
									pData->rdh.rcBound.top = y;
								if (x > pData->rdh.rcBound.right)
									pData->rdh.rcBound.right = x;
								if (y+1 > pData->rdh.rcBound.bottom)
									pData->rdh.rcBound.bottom = y+1;
								pData->rdh.nCount++;

								// On Windows98, ExtCreateRegion() may fail if the number of rectangles is too
								// large (ie: > 4000). Therefore, we have to create the region by multiple steps.
								if (pData->rdh.nCount == 2000)
								{
									HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
									if (hRgn)
									{
										CombineRgn(hRgn, hRgn, h, RGN_OR);
										DeleteObject(h);
									}
									else
										hRgn = h;
									pData->rdh.nCount = 0;
									SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
								}
							}
						}

						// Go to next row (remember, the bitmap is inverted vertically)
						p32 -= bm32.bmWidthBytes;
					}

					// Create or extend the region with the remaining rectangles
					HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
					if (hRgn)
					{
						CombineRgn(hRgn, hRgn, h, RGN_OR);
						DeleteObject(h);
					}
					else
						hRgn = h;

					// Clean up
					GlobalFree(hData);
					SelectObject(hDC, holdBmp);
					DeleteDC(hDC);
				}

				DeleteObject(SelectObject(hMemDC, holdBmp));
			}

			DeleteDC(hMemDC);
		}	
	}

	return hRgn;
}

// 2015-12-16 Future, Vsync setting
void CAtumLauncherDlg::OnBnClickedCheckVSync()
{
	m_bVSync = m_ctlChckVsync.GetCheck();
}
