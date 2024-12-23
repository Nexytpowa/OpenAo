// INFGameMain.h: interface for the CInterfaceGameMain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFGAMEMAIN_H__0FB2504C_BB3C_4763_9ADD_64687E4275A3__INCLUDED_)
#define AFX_INFGAMEMAIN_H__0FB2504C_BB3C_4763_9ADD_64687E4275A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"
#include "AtumApplication.h"
#include "INFMission.h"
#include "INFStrategicPointManager.h"
// 2007-07-04 by bhsohn ���۷����� �߰�
#include "INFImageBtn.h"

// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
#include "INFSpeakeMsg.h"

// 2008-02-27 by bhsohn �Ʒ��� �̵��� ä������ ���?
#include "ChatTab_t.h"

// 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����
#include "SkillInfo.h"
// end 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����

#include "INFImageEx.h"
#include "INFImageList.h"

//#include "INFQuickSlot.h"
//#include "INFParty.h"
//#include "INFMiniMap.h"
//#include "INFQuest.h"

#define LEFT_WINDOW_WEAPON	0			//��� ���ʿ� �Ѿ� ������ ���ö�..
#define LEFT_WINDOW_INVEN	1			//�κ�Ű (I key)�� �������� �κ�â�� �ߴ� ����.
#define LEFT_WINDOW_TRANS	2			//
#define LEFT_WINDOW_PARTY	3			//��Ƽâ..
#define LEFT_WINDOW_SHOP	4			//����.

#define RIGHT_WINDOW_WEAPON 0
#define RIGHT_WINDOW_INFO	1
#define RIGHT_WINDOW_OPTION 2

#define INF_WINDOW_MOVING_VEL	3000

#define UNITKIND_LEVEL_1_MASK		(USHORT)0x1111	// ���Ϸ�
#define UNITKIND_LEVEL_2_MASK		(USHORT)0x2222	// ����
#define UNITKIND_LEVEL_3_MASK		(USHORT)0x4444	// ���̽�
#define UNITKIND_LEVEL_4_MASK		(USHORT)0x8888	// ž��
#define IS_UNITKIND_LEVEL_1(x)		((x&UNITKIND_LEVEL_1_MASK) != 0)
#define IS_UNITKIND_LEVEL_2(x)		((x&UNITKIND_LEVEL_2_MASK) != 0)
#define IS_UNITKIND_LEVEL_3(x)		((x&UNITKIND_LEVEL_3_MASK) != 0)
#define IS_UNITKIND_LEVEL_4(x)		((x&UNITKIND_LEVEL_4_MASK) != 0)


#define GAMEMAIN_BUTTON_INVEN		0
#define GAMEMAIN_BUTTON_INFO		1
#define GAMEMAIN_BUTTON_COMMUNITY	2
#define GAMEMAIN_BUTTON_TRADE		3
#define GAMEMAIN_BUTTON_SYSTEM		4

#define GAMEMAIN_BUTTON_NUMBER		5

#define HELP_NUM					2
#define	GAMEMAIN_TIMESET_ZERO		0
#define	GAMEMAIN_TIME_VIEW_TOP		27


#define HELP_START_X				(g_pD3dApp->GetBackBufferDesc().Width/2)-220
#define HELP_START_Y				130
#define HELP_TEXT_CHECK_TIME		20

// 2007-03-02 by bhsohn ���� ���� �߰� ����
#define MAX_MULTI_SEL				3

// ������ ���� �ð� 
// 2007-09-19 by bhsohn ������ �ð� 1�ð����� ����
//#define	WAR_MONSTER_LIVETIME_HOUR					2
#define	WAR_MONSTER_LIVETIME_HOUR					1
// �� ����ִ� �ð� 
#define	MOTHERSHIP_LIVETIME_HOUR					2
#define	MOTHERSHIP_LIVETIME_SECOND					MOTHERSHIP_LIVETIME_HOUR*3600

// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
// ���� �ý��� ���� ����
#define		SECURITY_MODE_LOCK					0		// Lock
#define		SECURITY_MODE_SETUP_PASSWORD		1		// SETUP_PASSWORD
#define		SECURITY_MODE_SETUP_CHANGE_PASS		2		// 
#define		SECURITY_MODE_PASS_WND				3		// 
#define		MAX_SECURITY_MODE_WND				4		// SETUP_PASSWORD

// 2007-09-27 by bhsohn 2�� �н����� �߰� ��ȹ��
// Lock, UnLock, SecondeModeCanel
#define		SECURITY_MODE_PASS_LOCK					0		// Lock
#define		SECURITY_MODE_PASS_UNLOCK				1		// UnLock
#define		SECURITY_MODE_PASS_SENCOND_CANCEL		2		// Cacncel

// 2006-07-26 by ispark, ���� ������
typedef struct 
{
	BYTE					bySelectType;
	INVEN_DISPLAY_INFO	*	pSelectItem;
	CINFImageEx			*	pSelectIcon;
	POINT					ptIcon;
} stSelectItem;

// 2008-06-17 by dgwoo VoIP ���� ä�� ���� ����ü.
//struct stVOIPData
//{
//	BYTE					byVoiceType;					// ���� �������� ����ä��.(VOICE_NONE, VOICE_ONE, VOICE_PARTY, VOICE_GUILD)
//	BYTE					byVoiceInput;					// ���� �Է� ���.
//	DWORD					nVolum;							// ����.
//	stVOIPData()
//	{
//		byVoiceType		= 0;
//		byVoiceInput	= 0;
//		nVolum			= 100;
//	};
//};



// 2008. 12. 16 by ckPark ������ ��� ����
///////////////////////////////////////////////////////////////////////////////
// \class 	: ITEM_DELAY
// \brief	: ������ ���� ���� �ð���, ������ ������ ���� ����Ʈ�� ��Ƶ� ����ü
//			  ���� �ð��� nItemDelayTime + nItemUseTime���� Ŭ ��� ������ ������ �ȴ�
// \author	: ckPark
// \version : 
// \date	: 16:12:2008   14:32
// \warning	: nItemUniqueNumber�� ITEM_BASE�� UniqueNumber ���
//			  nItemUseTime�� ��������� �ð��� ���
//			  nItemDelayTime�� ITEM�� AttackTime ���
struct ITEM_DELAY
{
	UINT64	nItemUniqueNumber;		// ������ ���� �ѹ�
	DWORD	nItemUseTime;			// ������ ����� �ð� (1/1000�� ����)
	USHORT	nItemDelayTime;			// ������ ������ Ÿ��
};
// end 2008. 12. 16 by ckPark ������ ��� ����




// 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����
///////////////////////////////////////////////////////////////////////////////
// \class 	: SKILL_DELAY
// \brief	: ��ų ���� ���� �ð���, ������ ������ ���� ����Ʈ�� ��Ƶ� ����ü
//			  ���� �ð��� nSkillUseTime + nSkillDelayTime���� Ŭ ��� ������ ������ �ȴ�
// \author	: ckPark
// \version : 
// \date	: 26:12:2008   12:58
// \warning	: nTargetUniqueNumber Ÿ�� ����ũ �ѹ�
//			  nSkillUseTime�� ��ų ���� �ð�
//			  nSkillDelayTime�� ITEM�� AttackTime ���
///////////////////////////////////////////////////////////////////////////////
struct SKILL_DELAY
{
	CSkillInfo*	pSkillInfo;
	UID32_t		nTargetUniqueNumber;
	DWORD		nSkillUseTime;
	USHORT		nSkillDelayTime;
};
// end 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����


// 2010. 02. 11 by ckPark �ߵ��� ����������
struct INVOKEITEM_COOLTIME
{
	UID64_t		nItemUID;			// ������ UID
	DWORD		nPrevTickTime;		// �� ������ ��Ÿ�� ��� �ð�
	BOOL		bSendEndCoolTime;	// ������ ��Ÿ�� ���Ḧ ���´°�?

	INVOKEITEM_COOLTIME() : nItemUID( 0 ), nPrevTickTime( 0 ), bSendEndCoolTime( FALSE ) 
	{

	}
};
// end 2010. 02. 11 by ckPark �ߵ��� ����������


class CGameData;
class CINFAttackDirection;
class CINFUnitState;
class CINFGameMainQSlot;
class CINFGameMainUnitInfoBar;
class CINFGameMainMiniMap;
class CINFGameMainOutPost;
class CINFCommunity;
class CINFQOLinfo;
class CINFWindow;
class CINFWeaponInfo;
class CINFTrade;

// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
//class CINFInven;
class CINFInvenExtend;

// 2008-03-19 by bhsohn Ep3�ɼ�â
//class CINFSystem;
class CINFOptionSystem;
// end 2008-03-19 by bhsohn Ep3�ɼ�â

// 2008-09-22 by bhsohn EP3 ĳ���� â
//class CINFCharacterInfo;
class CINFCharacterInfoExtend;

class CINFGameMainChat;
class CINFIcon;
class CINFShop;
class CINFItemInfo;
//class CINFNotice;
class CINFUnitNameInfo;
class CINFImage;
class CD3DHanFont;
class DataHeader;
class CINFGameHelpDesk;
class CINFQuest;
class CINFSkill;
class CINFGameCountDown;
class CINFDamageView;
class CINFOtherCharInfo;
class CINFGameMainFAQ;
class CINFMenuList;
class CINFMp3Player;
class CINFMissionInfo;
// 2007-06-12 by bhsohn �̼� �������̽� ������
class CINFMissionMain;

//class CINFCommunityVOIP;
class CINFCityBoard;

// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
class CINFSecuMain;
class CINFChangeCharactor;					// 2007-11-21 by dgwoo ĳ���� ���� ī��
class CINFCouponWindow;						// 2008-01-15 by dgwoo ���� �ý��� �߰�.
class CINFMotherShipManager;				// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
class CINFStrategicPointManager;			// 2015-05-01 by killburne
class CINFGameMainSysMsg;					// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
class CINFOpJoystick;						// 2008-11-13 by bhsohn ���̽�ƽ �۾�
class CINFWorldRankWnd;						// 2009-02-13 by bhsohn ���� ��ŷ �ý���
class CINFItemMixWnd;						// 2013-02-20 by bhsohn �ΰ��� ����â ó��
class CINFItemMenuList;						// 2013-02-26 by bhsohn �ΰ��� ���� �˻� ó��
class CINFArmorCollectWnd;					// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���

class CINFImageList;
class CINFGroupManager;
class CINFGroupImage;

class CINFGameMain : public CAtumNode
{
public:
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	CINFGameMain(CAtumNode* pParent, CGameData* pGameData);
#else
	CINFGameMain(CAtumNode* pParent);
#endif
	virtual ~CINFGameMain();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	void InitWarp();
	void Render();
	void RenderLeftRightWindow();
	void RenderHelp();
	virtual void Tick();
	int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int WndProcLeftRightWindow(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int	WndProcKeyDown(WPARAM wParam, LPARAM lParam);

	// 2008-07-10 by bhsohn �ý��� â �켱���� �߰�
	int WndProcSystemMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	int WndProcSysKeyDown(WPARAM wParam, LPARAM lParam);
	BOOL CheckSysKeyUseState(int nwParamFlage, int nlParamFlage, BOOL bUse, BOOL bOneUse);
	VOID FieldSecondLockOk(BOOL bIsUnlockFlag, BOOL bSuccess);
	VOID FieldSocketSecondPasswordUpdateOk(BOOL bSuccess, BOOL bFirstUseSecondPassword);

//	void OnButtonClick(int nButton);
	int WndProcButtonMouseMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	void OnGameMainButtonClicked(int nButton);

	HRESULT	SetResourceFile(char* szFileName) ;
	DataHeader* FindResource(const char* szRcName);

	BOOL ChangeLeftWindowMode();//return : m_nLeftWindowModeChage
	BOOL ChangeRightWindowMode();//return : m_nRightWindowModeChage
	void RightWindowShow(BOOL bHide, int nWindow);
	void LeftWindowShow(BOOL bHide, int nWindow);

	void SetToolTip(int x, int y, char* pszToolTip);

	// 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
	void SetToolTipEx ( int x , int y , char* strToolTip , PRECT prcBound = NULL );
	void ResetToolTipEx ( void );
	// End. 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.

	// 2013-04-11 by bhsohn �ΰ��� ����â ���� ���� ��þƮ �ý��� �˻�
//	void SetItemInfo(LONGLONG nUniqueNumber, int nItemNum, int x, int y, int nItemCount = 0, BOOL bShowMyEq=TRUE);	
//	void SetItemInfo(LONGLONG nUniqueNumber, int nItemNum, int x, int y, int nItemCount = 0, BOOL bShowMyEq=TRUE, int nLinkItem=0 , BOOL ArmorCollect = FALSE);	// 2013-06-10 by ssjung �Ƹ� �÷��� ���� ǥ��
	void SetItemInfo(LONGLONG nUniqueNumber, int nItemNum, int x, int y, int nItemCount = 0, BOOL bShowMyEq=TRUE, int nLinkItem=0 , BOOL ArmorCollect = FALSE, BOOL bInven = FALSE);
	// 2013-06-26 by ssjung �κ��丮 �߰� ���� 
	// END 2013-04-11 by bhsohn �ΰ��� ����â ���� ���� ��þƮ �ý��� �˻�

	void SetEnemyItemInfo(LONGLONG nUniqueNumber, int nItemNum, int x, int y, int nItemCount = 0, BOOL bShowMyEq=TRUE);// 2012-06-14 by isshin ���۹̸�����
	// end 2009-02-03 by bhsohn ���� ������ �� ����
	// 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
	void SetItemInfo1(CItemInfo* pItemInfo, int nItemNum, int x, int y, int nItemCount = 0, BOOL bShowMyEq=TRUE);	
	//end 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
	void ToggleHelpImage();
//	BOOL LoadEnvironment() ;
//	BOOL SaveEnvironment();

	void SetNotice(int index, int x=HELP_START_X, int y=HELP_START_Y);
	void SetNotice(char* szString, int x=HELP_START_X, int y=HELP_START_Y);
	void SetQuestLimitTime(int limitTime, int PlayTime, char* MissionName);

	bool IsShowing() const { return	!(m_nLeftWindowInfo == LEFT_WINDOW_WEAPON && 
								m_nRightWindowInfo == RIGHT_WINDOW_WEAPON &&
								m_bShowHelp == FALSE &&
								!m_pMission->m_bShow); }
	void InitHelpSystem(BOOL bShow);
	void SetMentMessage(int x, int y, char *strMent);
	void SetGuildName(int x, int y, char *strGuild, DWORD dwFontColor);
	// 2013-03-06 by bhsohn ���� ���� �ý���
	int GetMentMessageSize(char *strMent);
	// END 2013-03-06 by bhsohn ���� ���� �ý���
	void RenderQSlotIcon();

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// ��Ÿ �߰� �Լ� 
	CEnemyData	*	GetEnemyCharaterID(POINT pt);																// ���� ����� ĳ���� ���� ��������
	void			RenderPopUpWindowImage(int x, int y, int cx, int cy);										// ���ڿ� Ʋ����� �ֱ�
	void			RenderToolTipBg ( int ix , int iy , int iWid , int iHgt );
	char		*	GetMapNameByIndex(int nMapIndex);
	void			InvalidWndRect(int x, int y, int nSizeW, int nSizeH);
	void			ChangeItemByShop(int nItemNum, int nUnitColor=-1);											// ������ �����غ���
	void			BackUpWearItem();																			// ���� ������ ���
	void			ResetWearItem(int nPos=-1);																			// ���� ������ ����
	void			ProcessAltiMeter(float fMinHeight, float fMaxHeight,  float fMyPosHeight);					// ���� ���
	void			RenderAltiMeter(int x, int y, int nPos);
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////

	// 2005-03-03 by jschoi
	void RenderRequestEnable(float fAniTime);
	DWORD GetCurrentColor(float fTime, DWORD dwType, float fTotal = 1.0f, float fDelay = 0.0f);

	// 2005-07-20 by ispark
	void RenderToolTip();

	// 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
	void RenderToolTipEx( void );
	// End. 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.

	// 2005-08-05 by ispark
	void InitShowWindow();
	BOOL CheckKeyUseState(int nwParamFlage, int nlParamFlage, BOOL bUse, BOOL bOneUse);
	void TickDrawWindowInfo();

	void DrawSignBoardString();
	void InitCityBoard(int nMapNumber);
	void InitChangeInfluenceBoard();

	// 2006-07-26 by ispark, ���� ������ ������
	void SetSelectItem(INVEN_DISPLAY_INFO* pDisplayInfo, POINT pt, BYTE byType);
	void RenderSelectItem();

	// 2006-08-01 by ispark
	BOOL CheckPopUpMenu(D3DXVECTOR2 vPos, CEnemyData* pTp);

	// 2006-08-22 by ispark, ���� �� �̼� �߰� ���� �˸� ������
	void RenderOnInfo();
	
	void UpdateNoviceUserHelper();				// 2007-01-26 by bhsohn �ű����� �̼� �������̽�
	void UpdateLV1NoviceUserHelper();			// 2007-01-26 by bhsohn �ű����� �̼� �������̽�

	// 2007-02-12 by bhsohn Item ���� ���� ó��
	void SetMultiSelectItem(INVEN_DISPLAY_INFO *pDisplayInfo, INVEN_DISPLAY_INFO	*pSelectItem, POINT ptIcon);
	void SetMultiSelectCityStoreItem(CItemInfo* pItemInfo, INVEN_DISPLAY_INFO	*pSelectItem, POINT ptIcon, INVEN_DISPLAY_INFO  *pDisSelectItem);
	int	 GetCityStoreMultiSelectItem();

	// 2007-03-02 by bhsohn ���� ���� �߰� ����
	void PopupMultiItemSelect();
	void PopupStoreMultiItemSelect();
	void RenderMultiSelectItem();

	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	//void AddMultiSelectItem(int nSourceIndex, BYTE bySelectType, POINT ptIcon);
	void AddMultiSelectItem( int nSourceIndex, BYTE bySelectType, POINT ptIcon, char* szIconName );
	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


	void ClearMultiSelectItem();	
	void UpdateIconSelectItem(BYTE byType);

	// 2007-03-22 by bhsohn ������ ũ�� ���� ����
	BOOL IsDoingSkill(int nSourceIndex);

	// 2007-03-27 by bhsohn ������ ���� �������̽� ����
	void Render_AltiMeter();

	// 2007-06-12 by bhsohn �̼� �������̽� ������
	void RenderMission();
	void RenderMissionINGInfo();
	int WndProcMiss(UINT uMsg, WPARAM wParam, LPARAM lParam);
	ITEM * GetServerItemInfo(int nItemNum);
	CINFImageEx* FindIcon(char* strName);
	void SetWindowOrder(int nWndIndex);
	void CreateChatChild(TCHAR *str,int type, int chatType=CHAT_TAB_SYSTEM, char* szWisperToCharacterName=NULL, char *szWisperFromCharacterName=NULL);
	// ���� ������ ����.
	MEX_MONSTER_INFO * CheckMonsterInfo(int nMonType);
	MAP_INFO * GetMapInfo(MapIndex_t nMapIndex);
	void SetMissionEnterShop(BOOL bEnterShopState);	
	void MissionStart(DWORD dMissionIndex);
	BOOL IsBazaar();
	void TickMissonMain();	
	void ShowMissionTreeWnd(BOOL bFlag, BOOL bSoundPlay);
	void FirstUserShowMissionTreeWnd();
	BOOL IsShowTreeWnd();
	
	void SetMissionPosMissionSearchStart(BOOL nstate);
	void SetMissionPosMissionInfo(CQuest* pQuest);
	void SetMissionPosMissionComplete(BOOL bFlag);

	// ���¼��� �̼� 
	BOOL GetInfluenceMission();
	void SetInfluenceMission(BOOL nFlag, float fANIPercent, float fVANPercent);

	// �̼� ���� �ʱ�ȭ 
	void RefreshMission(BOOL bClick);
	void GoWarpMapChange(int nMapIndex);

	// ĳ������
	const CHARACTER& GetMyShuttleInfo() const;

	// ���� �̼� ����
	void SelectNextMission(INT nQuestIndex);
	void AddMsgBox(char* strMsg, int nType, DWORD dwData1=0, DWORD dwData2=0, int nLiveTime=0,UID64_t UniqueNumber=0, char* strName=NULL);
	// �˾� ������ Show
	void UpdateMissionPopWnd(BYTE byUpLevel, int nSuccessQuestIdx);
	// ������ �̼Ǹ� 
	int GetMissionMapQuestIdx();
	void SetImageInfo(int nImageIndex, BOOL bMissionImg);
	
	// 2007-07-04 by bhsohn ���۷����� �߰�
	DataHeader * FindResource_LoadOp(char* szRcName);

	// 2007-07-04 by bhsohn ���۷����� �߰�
	void SetFaqBtnBlingBling(BOOL bSet);
	void NextTutirialState();
	void ChangeChapterReady();
	void InitTutorialLesson();
	BOOL IsTutorialMode();
	void ShowOpBossMonsterSummon(BYTE byBelligerence, int nHour, int nMinute);
	// ó�� ���� ���� ������ ���۷��̼� �ݱ� ��ư Ŭ��
	void OnClickFirstUserCloseBtn();
	

	// 2007-06-12 by bhsohn �̼� �������̽� ������
	void OnClickBriefingRoom();

	// 2007-07-27 by bhsohn ���� �߰� �� ���� ���۷����Ϳ� ����
	VOID	ShowOpStatChange(int nStat);
	VOID	HideOpStatChange();

	// 2007-08-02 by bhsohn ���ڸʿ��� ��ݹ�ư ǥ������.
	VOID	RefreshMissionUI();

	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	void AddSpeakerMsgString(char* pTxt, BOOL bGm, BOOL bGmColor);	
	void DeleteNotGmMsg();
	// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�

	// 2007-09-05 by dgwoo ���(����) alt + click
	void EnemyAltClick(CEnemyData * pTp,POINT pt);
	void MonsterAltClick(CMonsterData * pMon);

	// 2007-09-05 by bhsohn ���� ������
	void StringCulling(char *pLineString, int nCullStringNum, vector<string> *vecStorage, CD3DHanFont* pHanFont);

	// 2007-09-27 by bhsohn 2�� �н����� �߰� ��ȹ��
	VOID ShowSecondPassword();
	int GetPassChangeMode();

	// 2007-10-05 by bhsohn FŰ�� ���ܵ� ����Ŀ ��Ʈ�� ���̰� ����
	VOID		RenderSpeakerMsg();
	VOID			TickSpeakerMsg();

	// 2007-10-15 by bhsohn �Ѿ� ������ �߰� ó��
	int GetMaxBulletItem(int nMaxBullet);

	// 2007-10-16 by bhsohn �ŷ� �� �׾�����, Ű �ȸԴ� ����ó��
	void SetTradeInfo(BOOL bTrade);
	void ShowCouponWindow(BOOL i_bShow);

	void SetCouponActive(MSG_FC_EVENT_COUPON_EVENT_INFO* pMsg);

	// 2008-02-27 by bhsohn �Ʒ��� �̵��� ä������ ���?
	void GetAllChatList(ChatLine_t pArrChatLine[CHAT_BUFFER_NUMBER]);

	// 2008-03-27 by bhsohn �̼Ǽ���â�� ���ִ� ���¿����� ������ �ȿ����� ����
	void CloseCurrentEnterBuilding();
	void SetForceCloseShop(BOOL bForceClose);	

	// 2008-03-19 by bhsohn Ep3�ɼ�â
	void PopupSystemOptinWnd();
  
	// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	// ���� ���� 
	void DestroyMotherShipInfo(BYTE byBelligerence);
	void SummonMotherShipInfo(BYTE byBelligerence, 
										ATUM_DATE_TIME  *pSummonMonsterTime, 
										INT	 nContributionPoint, 
										INT SummonMonsterUnitkind);
	int GetSummonMotherShipCnt();
	BOOL GetMotherShipInfl(UINT i_nMotherShipInf);
	BOOL SetWarPointMapInfo(SMSWARINFO_DISPLAY * pWarInfo);
	void SetStrategicPointInfo(SSTRATEGYPOINT_DISPLAY_INFO* pStrInfo);
	void DeleteStrategicPointInfo(MapIndex_t mapIndex);
	void ResetStrategicPointDisplay();
	void SetMSWarInfoDisplayOption(MSG_FC_INFO_MSWARINFO_DISPLAY_OPTION_OK* pMsg);
	CINFMotherShipManager* GetINFMotherShipManager() {return m_pMotherShipC;}
	void SetMotherShipTeleportTime(MSG_FC_EVENT_CLICK_TELEPORT_OK *pMsg);

	// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
	float	GetQuestTimeElapse();
	void	SetQuestTimeElapse(float fGetQuestTimeElapse);	

	// 2008-04-22 by bhsohn ��/������ �������� ������ ǥ�� �ϰ� ����
	void UpdatePlayingMotherShipInfo();
	// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
	void OnClickCommunity();	// Ŀ�´�Ƽ â Ŭ��
	void RenderCommunity();
	int WndProcCommunityWnd(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void TextReduce(CD3DHanFont *pFont, int nCutPixelX, char* buf);
	// 2008-06-17 by dgwoo ����ä�� ���� �Լ�.
	//DWORD GetVoiceVolum()			{	return m_stVOIP.nVolum;				}
	//BYTE GetVoiceType()				{   return m_stVOIP.byVoiceType;		}			//VOICE_NONE, VOICE_ONE, VOICE_PARTY, VOICE_GUILD)
	//BYTE GetVoiceInputType()		{	return m_stVOIP.byVoiceInput;		}		
	//void SetVoiceVolum(DWORD i_nVolum);
	//void SetVoiceType(BYTE i_byType);

	// 2008-10-20 by bhsohn VOIP ���� ����
	void InitSetVoiceVolum(DWORD i_nVolum);


	// 2008-07-07 by bhsohn 2�� �н����� Ȱ��ȭ��, �κ� �ȿ����� ��
	BOOL IsUseSecondPassword();

	// 2008-07-14 by bhsohn EP3 ���� ó��
	BOOL IsRejectUser(char* pRejectName);

	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	void RenderMirror(POINT *pMirrorPos=NULL);
	BOOL IsEquipInvenShow();
	D3DXMATRIX	GetInvenMatInven();
	void RenderInvenWnd();	// �κ�â ������
	int WndProcInvenWnd(UINT uMsg, WPARAM wParam, LPARAM lParam);	// �κ�â ������ �޽���
	// 2009-03-04 by bhsohn ��Ű �ӽ� ������
	//void ShowShopInven(int nBuildingKind);
	POINT ShowShopInven(int nBuildingKind, BOOL bShowInven=FALSE); // 2013-03-18 by bhsohn ���丮 ���� �߰�
	// end 2009-03-04 by bhsohn ��Ű �ӽ� ������

	// 2008-09-22 by bhsohn EP3 ĳ���� â
	void RenderCharacterWnd();

	// 2008-10-13 by bhsohn ���� �б� Return �ȵǴ� ���� ó��
	//�۾��� ¥��
	BOOL StringCullingUserData_ToNormal( char* strTalk, int nCullPixel, vector<string> *vecDstString, CD3DHanFont* pFont, BOOL bChRt = FALSE);
	char StringCullingAddVector_ToNormal(char chColorSave, char* pString, vector<string> *vecDstString);
	char DelCharacterRetrn(char* o_pTxt);
	// end 2008-10-13 by bhsohn ���� �б� Return �ȵǴ� ���� ó��

	// 2008-10-15 by bhsohn ���ҽ� �޸� ��ȣ ��� �߰�
	BOOL CreateChatChild_OperationMode(TCHAR *str,int type, int chatType=CHAT_TAB_SYSTEM, char* szWisperToCharacterName=NULL, char *szWisperFromCharacterName=NULL);
	// end 2008-10-15 by bhsohn ���ҽ� �޸� ��ȣ ��� �߰�

	// 2008-10-14 by bhsohn VOIP����
	//void ChangeVOIPMode();
	//void ReleaseVOIPMode();
	//void SetVOIPSpeaking(BOOL i_bVOIPSpeaking);
	//BOOL GetVOIPSpeaking();

	// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
	void OnClickServerTime();	

	// 2008-11-13 by bhsohn EP3-2 ���� ���� ���� �Ǹ� �ȵǴ� ���� ����
	void ClearSetIconInfo();

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	BOOL IsShowOpJoystick();
	void ShowOpJoystick(BOOL bShow);
	int WndProcOpJoystickWnd(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void RenderOpJoystickWnd();
	void SaveAsJoysticSetupInfo(char* pSaveAsFilename);

	// 2009-01-30 by bhsohn ���� ���� �Է� ��� ����
	int		GetKeyDownToNumber(LPARAM i_lParam);
	// end 2009-01-30 by bhsohn ���� ���� ���� �Է� ��� ����
	
	// 2012-12-10 by jhjang �Ʒ��� ��ȣ ������ �����ϰ� �Է� ���� 
	char GetKeyDownToNumberAndAlphabet(WPARAM wParam);
	// end 2012-12-10 by jhjang �Ʒ��� ��ȣ ������ �����ϰ� �Է� ���� 

	
	// 2009-02-03 by bhsohn ���� ������ �� ����
	// 2013-04-11 by bhsohn �ΰ��� ����â ���� ���� ��þƮ �ý��� �˻�
//	void SetItemInfoUser( CItemInfo* pItemInfo, int x, int y, BOOL bShowMyEq=TRUE);
	void SetItemInfoUser( CItemInfo* pItemInfo, int x, int y, BOOL bShowMyEq=TRUE, int nLinkItem=0, BOOL bInven  = FALSE);	   // 2013-06-26 by ssjung �κ��丮 �߰� ���� 
	// END 2013-04-11 by bhsohn �ΰ��� ����â ���� ���� ��þƮ �ý��� �˻�
	void ShowItemInfo(BOOL bShow);
	void SetItemInfoNormal( ITEM* pITEM, int x, int y, BOOL bShop=TRUE, int nItemCount = 0, BOOL bShowMyEq=TRUE, int nLinkItem=0,  BOOL ArmorCollect = FALSE);
	void RenderItemInfo();
	CItemInfo*	GetItem_To_MyEqITEM(ITEM* i_pItem);	// ���� ������ ������ �� ��� �˾ƿ�
	void ShowMyEqItemTooltip();	// �� ��� ������
	void RefreshItemTooltipPos();	
	// end 2009-02-03 by bhsohn ���� ������ �� ����

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	void OnClickWorldRankBoard();
	void RenderWorldRank();
	int WndProcWorldRank(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void RqWorldRankInfo();		// ���� ��ŷ ���� ��û
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	// 2013-02-20 by bhsohn �ΰ��� ����â ó��
	// ������ ����â
	void OnClickItemMixWnd(BOOL bShow, INT nShowItemNum, UID64_t uItemUniNum);
	int WndProcItemMixWnd(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void RenderItemMixWnd();		
	// END 2013-02-20 by bhsohn �ΰ��� ����â ó��

	// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
	// �Ƹ� �÷��� �ý���â
	void	OnClickArmorCollectionWnd(BOOL bShow, INT nShowItemNum, UID64_t uItemUniNum);
	int		WndProcArmorCollectionWnd(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void	RenderArmorCollectionWnd();		
	// END 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���

	// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	void SetKillCount(INT nCount);
	void SetRestCount(INT nCount);
	void SetBonusExpRate(INT nPartyExpRate,INT nFriendExpRate,INT nGuildExpRate);
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	void UpdateServerTimeString();	// 2012-12-10 by jhjang �ð� ǥ�� ����

	BOOL ShowOnScreenDisplay();
	
	// 2015-09-25 Future, inactivity kick
#ifdef C_DISCONNECT_INACTIVE_PLAYERS
	void InitInactivityKick(int nTimeTillKick);
	void CancelInactivityKick();
	bool	m_bShowingInactivityDCWarning;
#endif // C_DISCONNECT_INACTIVE_PLAYERS

public:
	//��, �� ������ ��ġ ����� �����
	int		m_nLeftWindowY;
	int		m_nRightWindowY;

	//////////////////////////////////////////////////////////////////////////	
	// �������� ������ ���� ���� ����
	CItemInfo*					m_pItemInfoWear[SIZE_MAX_POS];					// �����غ��� ������ ����
	ITEM_GENERAL*				m_pITEMG[SIZE_MAX_POS];							// �����غ��� ������ ����
	int							m_nItemSourceNum[SIZE_MAX_POS];					// ������ �����ϰ� �ִ� ������ ����
	BOOL						m_bUseShopItem;	
	int							m_nArmorColor;									// ������ �Ƹ� Į��
	int							m_nLeaveBuildingIndex;							// ��������� ����
	//
	//////////////////////////////////////////////////////////////////////////	

public:
	CGameData				*	m_pGameData ;

	CINFAttackDirection		*	m_pAttackDirection;
	CINFUnitState			*	m_pUnitState;
	CINFGameMainQSlot		*	m_pQuickSlot;
	CINFGameMainUnitInfoBar	*	m_pUnitInfoBar;
	CINFGameMainMiniMap		*	m_pMiniMap;
	CINFCommunity			*	m_pCommunity;
	CINFWindow				*	m_pInfWindow;
	CINFWeaponInfo			*	m_pWeaponInfo ;
	CINFTrade				*	m_pTrade;

	CINFQOLinfo				* m_pQOLInfo; // 2024/12/23 Nexy : Added QOL improvements to the main UI
	
	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	//CINFInven				*	m_pInven ;
	CINFInvenExtend				*	m_pInven ;
	
	// 2008-03-19 by bhsohn Ep3�ɼ�â
	//CINFSystem				*	m_pSystem ;
	CINFOptionSystem		*	m_pSystem ;
	
	// 2008-09-22 by bhsohn EP3 ĳ���� â
	//CINFCharacterInfo		*	m_pCharacterInfo ;
	CINFCharacterInfoExtend	*	m_pCharacterInfo ;

	CINFGameMainChat		*	m_pChat;
	CINFIcon				*	m_pIcon;
	CINFMission				*	m_pMission;	
	// 2009-02-03 by bhsohn ���� ������ �� ����
	//CINFItemInfo			*	m_pItemInfo;	
	// end 2009-02-03 by bhsohn ���� ������ �� ����
	CINFUnitNameInfo		*	m_pUnitNameInfo;
	CINFSkill				*	m_pInfSkill;
	CINFGameCountDown		*	m_pGameCountDown;
	CINFDamageView			*	m_pDamageView;
	CINFOtherCharInfo		*	m_pOtherCharInfo;
	CINFGameMainFAQ			*	m_pInfGameMainFaq;
	CINFMenuList			*	m_pMenuList;
	CINFCouponWindow		*	m_pCouponWindow;

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	CINFImageBtn			*	m_pImgButton[GAMEMAIN_BUTTON_NUMBER];
	CINFImageEx				*	m_pImgButtonBK;
#else 
	CINFImage				*	m_pImgButton[GAMEMAIN_BUTTON_NUMBER][BUTTON_STATE_NUMBER];
#endif
	CINFImageEx				*	m_pImgMission;
	CINFImageEx				*	m_pHelp[HELP_NUM];	
	CINFImageEx				*	m_pSelectIcon;
	CINFImageEx				*	m_pImgTextPopUp[3];	
	CINFImageEx				*	m_pImgTextBg;
	CINFGameHelpDesk		*	m_pHelpDesk;	
	CINFQuest				*	m_pQuest;
	CINFMp3Player			*	m_pMp3Player;
	// 2007-08-28 by dgwoo ���������� class�߰�.
	CINFGameMainOutPost		*	m_pOutPost;
	
	// 2007-06-12 by bhsohn �̼� �������̽� ������
	//CINFMissionInfo			*	m_pMissionInfo;
	CINFMissionMain			*	m_pMissionMain;	
	CINFChangeCharactor		*	m_pChangeCharactor;				// 2007-11-21 by dgwoo ĳ���� ���� ī��

	//CINFCommunityVOIP		*	m_pCommunityVOIP;
	CINFCityBoard			*	m_pCityBoard;			
	CINFImageEx				*	m_pImgStack;

	int		m_nIconPosX;
	int		m_nIconPosY;
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	int		m_nButtonState[GAMEMAIN_BUTTON_NUMBER];
#endif
	int		m_nLeftWindowState;	
	int		m_nLeftWindowInfo;
	int		m_nLeftWeaponInfoPosX;
	int		m_nLeftWindowPosY;
	int		m_nLeftWindowScaleSize;
	int		m_nRightWindowState;	
	int		m_nRightWindowInfo;
	int		m_nRightWeaponInfoPosX;
	int		m_nRightWindowPosY;
	int		m_nRightWindowScaleSize;
	
	BOOL	m_bHelpDeskFlag;
	BOOL	m_bLeftWindowModeChage;				//����â�� ��ȭ���ִ� ������ ����. ��
	BOOL	m_bRightWindowModeChage;
	BOOL	m_bMp3PlayFlag;

	CD3DHanFont		*	m_pFontToolTip;
	CD3DHanFont		*	m_pFontTimeLimit;
	CD3DHanFont		*	m_pFontDrawMent;

	// 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
	char				m_szSave_ToolTip[1024];

	vector < string >	m_vecToolTip;

	INT					m_iToolTipMaxWid;
	BOOL				m_bRenderToolTipEx;
	POINT				m_ptToolTipEx;
	RECT				m_rcToolTipEx;

	DWORD				m_dwFrameToolTip[2];
	// End. 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.

	

	char				m_strToolTip[128];
	POINT				m_ptToolTip;
	BOOL				m_bShowHelp;
	BOOL				m_bRestored;
	BOOL				m_bQuestView;	
	

	BOOL				m_bQuestLimitTimeView;
	// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
//	float				m_fTimeElapse;	
//	int					m_nTimeSecond;
//	char				m_strNPCName[32];

	// ������ �̼ǹ�ư �����̱�
//	BOOL				m_bMissionON;
//	BOOL				m_bMissionTwinkle;
// 	float				m_fTimeElapseMission;

	// FAQ ����
	BOOL				m_bFAQProsFlag;
	// �޴� ����Ʈ
	BOOL				m_bMenuListFlag;
	BOOL				m_bMenuLock;
	BOOL				m_bEnterBuilingCashShop;
	BOOL				m_bSendCashItemBuy;

	BOOL				m_bBuyMessage;

	// 2005-03-03 by jschoi - RequestEnable
	CINFImageEx*		m_pRequestEnableBack;
	CINFImageEx*		m_pRequestEnableTriangle;

	// �� ������ ����
	CINFImageEx*	m_pAltiMeterGage;
	CINFImageEx*	m_pAltiMeterPin;
	POINT			m_ptGageBack;
	POINT			m_ptGagePin;

	// �ŷ� 1:1���� ���콺 ����Ʈ ����
	BOOL			m_bChangeMousePoint;
	// ���� ������
	BOOL			m_bQSlotIconFlag;
	int				m_nQSlotPosX;
	int				m_nQSlotPosY;

	// �̼� ����
	int				m_nTimeLimitMissionOldTime;
	// VOIP
	BOOL			m_bVOIPFlag;

	// 2006-08-23 by ispark, ��ư �����̴� �ҽ� ����
	BOOL			m_bKnowON[HELP_SPECIAL_COUNT];
	BOOL			m_bKnowTwinkle;
	float			m_fTimeElapseButtonCheck;

	stSelectItem	m_stSelectItem;			// 2006-07-26 by ispark, ���� ������

	// 2007-03-02 by bhsohn ���� ���� �߰� ����
	stSelectItem	m_stMultiSelectItem[MAX_MULTI_SEL];	
	int				m_nMultiSelCnt;	
	// 2008-01-15 by dgwoo ���� �ý��� �߰�.
	CINFImageBtn*			m_pCouponBtn;
	// 2009. 10. 14 by jskim ������ī ����	
	CINFImageBtn*			m_pTut_SelBtn;
	//end 2009. 10. 14 by jskim ������ī ����	
//#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	CINFGroupManager*		m_GruopImagemanager;
//#endif
private:
	// 2007-07-04 by bhsohn ���۷����� �߰�
	CINFImageBtn*			m_pFaqBtn;

	// 2007-07-27 by bhsohn ���� �߰� �� ���� ���۷����Ϳ� ����
	BOOL					m_bShowStatOpWnd;

	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	CINFSpeakeMsg*			m_pINFSpeakeMsg;
	// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	CINFSecuMain*			m_pINFSecuMain;
	// end 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����

	// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	CINFMotherShipManager*		m_pMotherShipC;

	// 2015-05-01 by killburne
	CINFStrategicPointManager*	m_pStrategicPointDisplay;

	// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
	float						m_fQuestTimeElapse;		

	// 2008-06-17 by dgwoo ���� ä��.
	//stVOIPData					m_stVOIP;

	// 2008-10-14 by bhsohn VOIP����
	//BOOL						m_bVOIPSpeaking;

	// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
	CINFGameMainSysMsg*			m_pINFGameMainSysMsg;

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	CINFOpJoystick*				m_pINFOpJoystick;

	// 2009-02-03 by bhsohn ���� ������ �� ����
	CINFItemInfo			*	m_pItemInfo;		// ������ ����
	CINFItemInfo			*	m_pEquipItemInfo;	// ���� ������ ������ ����	
	BOOL						m_bShowMyEqTooltip;
	// end 2009-02-03 by bhsohn ���� ������ �� ����

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	CINFWorldRankWnd*			m_pINFWorldRankWnd;
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	// 2013-02-20 by bhsohn �ΰ��� ����â ó��
	CINFItemMixWnd*				m_pINFItemMixWnd;
	// END 2013-02-20 by bhsohn �ΰ��� ����â ó��
	
	// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
	CINFArmorCollectWnd*		m_pINFArmorCollectWnd;
	// END 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���

    // 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
	int				m_nAddPosY;
	// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

	ATUM_DATE_TIME m_OldServerTime; 	// 2012-12-10 by jhjang �ð� ǥ�� ����

	

protected:	
	BOOL			IsNoviceUserMode();		// 2007-01-26 by bhsohn �ű����� �̼� �������̽�
	void			StartNoviceUserHelper();		
	void			EndNoviceUserHelper();		// 2007-01-26 by bhsohn �ű����� �̼� �������̽�
	BOOL			IsMyLevelQuestComplete(const CHARACTER* pShuttleInfo);// 2007-01-26 by bhsohn �ű����� �̼� �������̽�


	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	//VOID			RenderSpeakerMsg();
	//VOID			TickSpeakerMsg();
	// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	void			InitSecurityPassMode();
	VOID			RenderSecuritySystem();
	VOID			TickSecuritySystem();
	void			OnClickF10Btn();

	// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�	
	void			ShowSysMsgWnd(BOOL bShowWnd);
	void			RenderSysMsgWnd();
#ifdef SC_COLLECTION_ARMOR_JHSEOL_BCKIM
	void TickArmorTimeCheck();		  // 2013-05-09 by ssjung ���� ���� �Ⱓ���� ��� �޽��� ����
#endif
	// 2008. 12. 16 by ckPark ������ ��� ����
	// ���� ó���� �������� �־�� ����Ʈ
	std::list<ITEM_DELAY>	m_listItemDelay;

public:
	// ����ó���� ������ �߰�
	BOOL PushDelayItem(CItemInfo* pItemInfo);
	// ����ó���� �����۸���Ʈ �ʱ�ȭ
	void ReleaseDelayItem(void);
	void TickItemDelay(void);
	// end 2008. 12. 16 by ckPark ������ ��� ����

	// 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����
	// 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����
	CINFItemInfo* GetINFItemInfo() { return m_pItemInfo; }
	//end 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����

	void			RenderSysTimer();						// 2012-03-16 by jhahn FŰ�� ���ܵ� �ð谡 ���̰� ����
protected:
	std::list<SKILL_DELAY>	m_listSkillDelay;

public:
	BOOL PushDelaySkill(CSkillInfo* pSkillInfo, UID32_t nTargetUniqueNumber);
	void ReleaseDelaySkill(void);
	void TickSkillDealy(void);
	// end 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����


	// 2009. 08. 21 by ckPark ĳ�������� �����ϱ⿡ ������ üũ
protected:
	char	m_szCashGiftSendCharacterName[256];

public:
	inline	void	SetCashGiftSendCharacterName( const char* szCharacterName ) { strcpy( m_szCashGiftSendCharacterName, szCharacterName ); }
	inline	void	GetCashGiftSendCharacterName( char* szCharacterName ) { strcpy( szCharacterName, m_szCashGiftSendCharacterName ); }
	// end 2009. 08. 21 by ckPark ĳ�������� �����ϱ⿡ ������ üũ


	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	CINFImageEx*	FindBigIcon( int nItemnum );
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


	// 2010. 02. 11 by ckPark �ߵ��� ����������
protected:
	// ��Ÿ�� ����Ʈ
	std::list<INVOKEITEM_COOLTIME>	m_listInvokeItemCoolTime;

public:
	// ��Ÿ�� ������ ����Ʈ�� �߰�
	void	PushInvokeWearItem( UID64_t nItemUID );
	// ��Ÿ�� ������ ����Ʈ���� ����
	void	PopInvokeWearItem( UID64_t nItemUID );
	// ��Ÿ�� ƽ
	void	TickInvokeWearItem( void );
	// ��Ÿ�� ����
	void	SetItemCoolStart( UID64_t nItemUID );
	// ��Ÿ�� ��
	void	SetItemCoolEnd( UID64_t nItemUID );
	// ��Ÿ�� ���ð� ����
	void	RefreshInvokeItemTickTime( UID64_t nItemUID );
	// end 2010. 02. 11 by ckPark �ߵ��� ����������

	//2016-01-04 by St0rmy, Fix City Fly bug
	bool IsShowRanking();

#ifdef SC_COLLECTION_ARMOR_JHSEOL_BCKIM
	INT GetArmorCollectType();	// 2013-06-12 by ssjung �Ƹ� �÷��� ���� ǥ��
#endif
};

#define POS_LEFT_WINDOW_Y	(((CINFGameMain*)m_pParent)->m_nLeftWindowPosY - ((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/2)
#define POS_RIGHT_WINDOW_Y	(((CINFGameMain*)m_pParent)->m_nRightWindowPosY - ((CINFGameMain*)m_pParent)->m_nRightWindowScaleSize/2)
#define POS_RIGHT_WINDOW_X		(g_pD3dApp->GetBackBufferDesc().Width - SIZE_NORMAL_WINDOW_X)


#endif // !defined(AFX_INFGameMain_H__0FB2504C_BB3C_4763_9ADD_64687E4275A3__INCLUDED_)
