// INFGameMain.cpp: implementation of the CInterfaceGameMain class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFGameMain.h"
#include "QuestData.h"
#include "AtumApplication.h"

#include "GameDataLast.h"
#include "INFWindow.h"
#include "INFWeaponInfo.h"
// 2008-09-22 by bhsohn EP3 ĳ���� â
//#include "INFCharacterInfo.h"
#include "INFCharacterInfoExtend.h"
#include "RangeTime.h"
#include "INFInven.h"
// 2008-03-19 by bhsohn Ep3�ɼ�â
//#include "INFSystem.h"
#include "INFOptionSystem.h"

#include "INFTrade.h"
#include "INFGameMainChat.h"
#include "INFIcon.h"
//#include "INFShop.h"
#include "INFUnitNameInfo.h"
#include "INFItemInfo.h"
//#include "INFNotice.h"
#include "INFGameMainUnitInfoBar.h"
#include "INFGameMainQSlot.h"
#include "INFGameMainMinimap.h"
#include "INFCommunity.h"
#include "INF_QOL_info.h"
#include "INFUnitState.h"
#include "INFAttackDirection.h"
#include "INFGameHelpDesk.h"

#include "StoreData.h"
#include "EnemyData.h"
#include "MonsterData.h"
#include "INFCommunityParty.h"
#include "SceneData.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "D3DHanFont.h"
#include "Interface.h"
#include "AtumDatabase.h"
#include "Chat.h"
#include "INFCityBase.h"

// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
#include "IMSocketManager.h"
//#include "IMSocket.h"

#include "INFImage.h"
#include "Skill.h"
#include "AtumSound.h"
#include "ClientParty.h"
#include "INFQuest.h"
#include "INFSkill.h"
#include "INFGameCountDown.h"
#include "INFDamageView.h"
#include "INFOtherCharInfo.h"
#include "dxutil.h"
#include "INFGameMainFAQ.h"
#include "INFMenuList.h"
#include "INFCommunityGuild.h"
#include "INFTarget.h"
#include "INFMp3Player.h"
#include "TutorialSystem.h"
#include "INFMissionInfo.h"
// 2007-06-12 by bhsohn �̼� �������̽� ������
#include "INFMissionMain.h"
#include "FieldWinSocket.h"
#include "GlobalImage.h"
#include "INFCommunityVOIP.h"
#include "ItemInfo.h"
#include "Background.h"
#include "INFCityBoard.h"
#include "INFGameMainOutPost.h"

// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
#include "INFSecuMain.h"
#include "INFChangeCharactor.h"
#include "INFCouponWindow.h"
// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
#include "INFMotherShipManager.h"
#include "INFCityLeader.h"
#include "INFCommunityReject.h"

// 2008-10-16 by bhsohn �������� ����, ������ ����â
#include "INFCityOutPost.h"

#include "INFGameMainSysMsg.h"	// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�

#include "INFOpJoystick.h"		// 2008-11-13 by bhsohn ���̽�ƽ �۾�

#include "INFWorldRankWnd.h"	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
#include "INFItemMixWnd.h"		// 2013-02-20 by bhsohn �ΰ��� ����â ó��
#include "INFItemMenuList.h"	// 2013-02-26 by bhsohn �ΰ��� ���� �˻� ó��

#include "INFArmorCollectWnd.h"		// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���

#include "INFInfinity.h"		// 2010. 07. 27 by hsLee ���Ǵ�Ƽ 2�� ���� ��� �ó׸� ���� ��ŵ ó��.

// 2011. 10. 10 by jskim UI�ý��� ����
#include "INFImageEx.h"
#include "INFGroupImage.h"
#include "INFGroupManager.h"
// end 2011. 10. 10 by jskim UI�ý��� ����
// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
#include "INFToolTip.h"
// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����

#include <BonusKillSystem.h>			// 2015-06-16 by Future, Bonus Kill System Definitions

#define IMG_UNIT_LOCK_SCALE		((float)g_pD3dApp->GetBackBufferDesc().Width/1024.0f)
#define IMG_UNIT_LOCK_SIZE_X	118
#define IMG_UNIT_LOCK_SIZE_Y	36
#define IMG_UNIT_LOCK_START_X	(g_pD3dApp->GetBackBufferDesc().Width-IMG_UNIT_LOCK_SIZE_X*IMG_UNIT_LOCK_SCALE)/2
#define IMG_UNIT_LOCK_START_Y	3


#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
#define GAMEMAIN_BUTTON_START_X			(g_pD3dApp->GetBackBufferDesc().Width-275)
#define GAMEMAIN_BUTTON_START_Y			(g_pD3dApp->GetBackBufferDesc().Height-53)
#define GAMEMAIN_BK_START_X				(g_pD3dApp->GetBackBufferDesc().Width-335)
#define GAMEMAIN_BK_START_Y				(g_pD3dApp->GetBackBufferDesc().Height-53)
#define GAMEMAIN_BUTTON_SIZE_X			47//57
#define GAMEMAIN_BUTTON_SIZE_Y			18//18
#define GAMEMAIN_BUTTON_INTERVAL		55//60

#define GAME_BUTTON_CHECK_ON					0.5f

#define GAMEMAIN_FONT_LINE_HEIGHT				15							// �� ������ ����
#define GAMEMAIN_FONT_WIDTH_ENGLISH				6							// ���� ���� WIDTH

#define GAMEMAIN_MISSION_TIME_CHECK				5
// ���輳��
#define GAMEMAIN_ALTIMETER_X (g_pD3dApp->GetBackBufferDesc().Width-32)
#define GAMEMAIN_ALTIMETER_Y 188										// 2007-02-22 by dgwoo ��ġ ����.165	// 2012-03-29 by mspark, �̴ϸ�&�� ǥ�� ��ġ ���� - ���� 178���� 188�� ����

// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
#define GAMEMAIN_SERVER_TIME_X (g_pD3dApp->GetBackBufferDesc().Width-168)
#define GAMEMAIN_SERVER_TIME_Y 313
#define GAMEMAIN_SERVER_TIME_WIDTH (185)


// 2007-07-04 by bhsohn ���۷����� �߰�
#define FAQ_BTN_POS_X		(g_pD3dApp->GetBackBufferDesc().Width-330)
#define FAQ_BTN_POS_Y		(g_pD3dApp->GetBackBufferDesc().Height-53)
#define	FAQ_BLING_TIME		(1.0f)

#define COUPON_BTN_POS_X		(g_pD3dApp->GetBackBufferDesc().Width-75)
#define COUPON_BTN_POS_Y		(g_pD3dApp->GetBackBufferDesc().Height-190)
#define COUPON_WINDOW_POS_X		((g_pD3dApp->GetBackBufferDesc().Width - 307)/2)
#define COUPON_WINDOW_POS_Y		((g_pD3dApp->GetBackBufferDesc().Height - 183)/2)	   
#else
#define GAMEMAIN_BUTTON_START_X			(g_pD3dApp->GetBackBufferDesc().Width-251)
#define GAMEMAIN_BUTTON_START_Y			(g_pD3dApp->GetBackBufferDesc().Height-22)
#define GAMEMAIN_BUTTON_SIZE_X			47//57
#define GAMEMAIN_BUTTON_SIZE_Y			18//18
#define GAMEMAIN_BUTTON_INTERVAL		50//60

#define GAME_BUTTON_CHECK_ON					0.5f

#define GAMEMAIN_FONT_LINE_HEIGHT				15							// �� ������ ����
#define GAMEMAIN_FONT_WIDTH_ENGLISH				6							// ���� ���� WIDTH

#define GAMEMAIN_MISSION_TIME_CHECK				5
// ���輳��
#define GAMEMAIN_ALTIMETER_X (g_pD3dApp->GetBackBufferDesc().Width-32)
#define GAMEMAIN_ALTIMETER_Y 183										// 2007-02-22 by dgwoo ��ġ ����.165

// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
#define GAMEMAIN_SERVER_TIME_X (g_pD3dApp->GetBackBufferDesc().Width-168)
#define GAMEMAIN_SERVER_TIME_Y 313
#define GAMEMAIN_SERVER_TIME_WIDTH (185)


// 2007-07-04 by bhsohn ���۷����� �߰�
#define FAQ_BTN_POS_X		(g_pD3dApp->GetBackBufferDesc().Width-287)
#define FAQ_BTN_POS_Y		(g_pD3dApp->GetBackBufferDesc().Height-35)
#define	FAQ_BLING_TIME		(1.0f)

#define COUPON_BTN_POS_X		(g_pD3dApp->GetBackBufferDesc().Width-322)
#define COUPON_BTN_POS_Y		(g_pD3dApp->GetBackBufferDesc().Height-35)
#define COUPON_WINDOW_POS_X		((g_pD3dApp->GetBackBufferDesc().Width - 307)/2)
#define COUPON_WINDOW_POS_Y		((g_pD3dApp->GetBackBufferDesc().Height - 183)/2)
#endif

// 2009. 10. 14 by jskim ������ī ����
// Ʃ�丮�� ��ư �߰�
#define TUTORIAL_BUTTON_X		(g_pD3dApp->GetBackBufferDesc().Width - 73)		// 2012-03-29 by mspark, ���� 1~10���� �������� Ʃ�丮�� ��ư ��ġ ���� - ���� 64���� 73���� ����
#define TUTORIAL_BUTTON_Y		326												// 2012-03-29 by mspark, ���� 1~10���� �������� Ʃ�丮�� ��ư ��ġ ���� - ���� 315���� 326���� ����
//end 2009. 10. 14 by jskim ������ī ����
// 2007-07-20 by bhsohn Ʃ�丮�� ����
//#define	VCN_FIRST_QUEST_IDX		113		// ���������� ù��? ����Ʈ
//#define	ANI_FIRST_QUEST_IDX		501		// �˸��� ù��? ����Ʈ
#define	SELECT_FIRST_QUEST_IDX		112		// ���¼��� ����Ʈ


// 2006-03-07 by ispark, �� ���� ��ġ ����
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
#define FONTTOOLTIP_Y			17
#else
#define FONTTOOLTIP_Y			17//15
#endif

// 2007-09-05 by bhsohn ���� ������
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
	#define STRING_CULL ::StringCullingUserData_ToBlank
#else
	#define STRING_CULL ::StringCullingUserDataEx	
#endif

// 2008-10-20 by bhsohn VOIP ���� ����
#define		VOLUME_SET_MIN			1
#define		VOLUME_SET_MAX			100

// 2008-11-13 by bhsohn ���̽�ƽ �۾�
#define JOYSTICK_WND_POS_X		(g_pD3dApp->GetBackBufferDesc().Width/2-427)
#define JOYSTICK_WND_POS_Y		(g_pD3dApp->GetBackBufferDesc().Height/2-213)
// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#define TUTORIAL_BUTTON_Y_ADDCOUNT	34
//#define KILLCOUNT_MAX				300
// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2009-01-30 by bhsohn ���� ���� �Է� ��� ����
typedef struct
{	
	DWORD	dwKeyValue;
	int		nKey;	
} structNumTable;

structNumTable m_stucTable[] = 
{
	{0x000b0001, 0},
	{0x00020001, 1},
	{0x00030001, 2},
	{0x00040001, 3},
	{0x00050001, 4},
	
	{0x00060001, 5},
	{0x00070001, 6},
	{0x00080001, 7},
	{0x00090001, 8},
	{0x000a0001, 9},
	
	// Num�е�
	{0x00520001, 0},
	{0x004f0001, 1},
	{0x00500001, 2},
	{0x00510001, 3},
	{0x004b0001, 4},
	
	{0x004c0001, 5},
	{0x004d0001, 6},
	{0x00470001, 7},
	{0x00480001, 8},
	{0x00490001, 9}	
};
// end 2009-01-30 by bhsohn ���� ���� ���� �Է� ��� ����

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
CINFGameMain::CINFGameMain(CAtumNode* pParent, CGameData* pGameData)
#else
CINFGameMain::CINFGameMain(CAtumNode* pParent)
#endif
{
	FLOG( "CINFGameMain(CAtumNode* pParent)" );
	g_pGameMain = this;
	m_pGameData = NULL;
	m_pUnitInfoBar = NULL ;
	m_pInfWindow = NULL ;
//	m_pParty = NULL ;
	m_pCommunity = NULL ;
	m_pWeaponInfo = NULL ;

	m_pTrade  = NULL;
	m_pInven  = NULL;
	m_pSystem  = NULL;
	m_pCharacterInfo  = NULL;

	m_pChat = NULL;
	m_pQuickSlot = NULL;
	m_pMiniMap = NULL;
	m_pIcon = NULL;
//	m_pShop = NULL;
	m_pUnitNameInfo = NULL;
	m_pQuest = NULL;
	m_pMission = NULL;
	m_pItemInfo = NULL;
	// 2009-02-03 by bhsohn ���� ������ �� ����
	m_pEquipItemInfo = NULL;	// ���� ������ ������ ����
	m_bShowMyEqTooltip = FALSE;
	// end 2009-02-03 by bhsohn ���� ������ �� ����
//	m_pNotice = NULL;
	m_pUnitState = NULL;
	m_pAttackDirection = NULL;
	m_pInfSkill = NULL;
	m_pGameCountDown = NULL;
	m_pDamageView = NULL;
	m_pOtherCharInfo = NULL;
	m_pInfGameMainFaq =NULL;
	m_pMenuList = NULL;
	m_pMp3Player = NULL;
	
	// 2007-06-12 by bhsohn �̼� �������̽� ������
	//m_pMissionInfo = NULL;
	m_pMissionMain = NULL;
	
	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	m_pINFWorldRankWnd = NULL;
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
	
	// 2013-02-20 by bhsohn �ΰ��� ����â ó��
	m_pINFItemMixWnd = NULL;
	// END 2013-02-20 by bhsohn �ΰ��� ����â ó��

	// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
	m_pINFArmorCollectWnd = NULL;		
	// END 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���

	// 2007-08-28 by dgwoo ���������� class�߰�.
	m_pChangeCharactor = NULL;
	m_pCouponWindow = NULL;
	m_pOutPost = NULL;

	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	m_pINFSpeakeMsg = NULL;

	//m_pCommunityVOIP = NULL;
	m_pCityBoard = NULL;

	m_nLeftWindowState = LEFT_WEAPON_WINDOW_INIT ;
	m_bLeftWindowModeChage = FALSE;
	m_nLeftWindowInfo = LEFT_WINDOW_WEAPON;
	m_nLeftWeaponInfoPosX = 0;
	m_nLeftWindowPosY = DEAULT_WINDOW_POS_Y;
	m_nLeftWindowScaleSize = SIZE_WEAPON_Y;

	m_nRightWindowState = RIGHT_WEAPON_WINDOW_INIT ;
	m_bRightWindowModeChage = FALSE;
	m_nRightWindowInfo = RIGHT_WINDOW_WEAPON;
	m_nRightWeaponInfoPosX = g_pD3dApp->GetBackBufferDesc().Width - SIZE_ROLL_X;
	m_nRightWindowPosY = DEAULT_WINDOW_POS_Y;
	m_nRightWindowScaleSize = SIZE_WEAPON_Y;

	m_pParent = pParent;


	m_pFontToolTip = NULL;
	m_pFontTimeLimit	= NULL;
	m_pFontDrawMent = NULL;
	memset(m_strToolTip,0x00,sizeof(m_strToolTip));
	m_ptToolTip.x = 0;
	m_ptToolTip.y = 0;
	m_bShowHelp = FALSE;
	memset(m_pHelp, 0x00, sizeof(DWORD)*HELP_NUM);
//	m_pImgUnitLock = NULL;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	memset(m_pImgButton, 0x00, sizeof(DWORD)*GAMEMAIN_BUTTON_NUMBER);							  
#else 
	memset(m_pImgButton, 0x00, sizeof(DWORD)*GAMEMAIN_BUTTON_NUMBER*BUTTON_STATE_NUMBER);
	memset(m_nButtonState, 0x00, sizeof(int)*GAMEMAIN_BUTTON_NUMBER);
#endif
	m_pImgMission = NULL;

	m_pSelectIcon = NULL;
	int i;
	for(i=0; i<3; i++)
	{
		m_pImgTextPopUp[i] = NULL;
	}

	m_pImgTextBg = NULL;

	m_nIconPosX = 0;
	m_nIconPosY = 0;

	m_nLeftWindowY = DEAULT_WINDOW_POS_Y;
	m_nRightWindowY = DEAULT_WINDOW_POS_Y;
	m_bRestored = FALSE;

	m_pHelpDesk		= NULL;
	m_bHelpDeskFlag = FALSE;
	m_bQuestView	= FALSE;	

	m_bQuestLimitTimeView	= FALSE;
	// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
//	m_fTimeElapse			= 0.0f;
//	m_nTimeSecond			= GAMEMAIN_TIMESET_ZERO;
	m_fQuestTimeElapse		=GAMEMAIN_TIMESET_ZERO;

//	memset(m_strNPCName, 0x00, sizeof(m_strNPCName));
	
	m_bFAQProsFlag			= FALSE;
	m_bMenuListFlag			= FALSE;
	m_bMenuLock				= FALSE;
	m_bEnterBuilingCashShop = FALSE;
	m_bSendCashItemBuy		= FALSE;
	
	// 2005-03-03 by jschoi
	m_pRequestEnableBack		= NULL;
	m_pRequestEnableTriangle	= NULL;
	m_pAltiMeterGage			= NULL;
	m_pAltiMeterPin				= NULL;

	m_bChangeMousePoint			= FALSE;
	m_bQSlotIconFlag			= FALSE;
	m_nQSlotPosX				= 0;
	m_nQSlotPosY				= 0;
	m_bMp3PlayFlag				= TRUE;
	m_nTimeLimitMissionOldTime  = GAMEMAIN_TIMESET_ZERO;
	m_nLeftWindowInfo			= 0;				// ���� �ӽ� 1 �̸� �κ��丮
	m_bVOIPFlag = FALSE;

	for(i=0; i<SIZE_MAX_POS; i++)
	{
		m_nItemSourceNum[i] = 0;		
		m_pItemInfoWear[i] = NULL;
		m_pITEMG[i] = NULL;
	}
	m_bUseShopItem = FALSE;
	m_nArmorColor = 0;
	m_nLeaveBuildingIndex = 0;
	m_ptGageBack.x = 0;
	m_ptGageBack.y = 0;
	m_ptGagePin.x = 0;
	m_ptGagePin.y = 0;

	m_stSelectItem.pSelectItem = NULL;
	m_stSelectItem.pSelectIcon = NULL;
	m_stSelectItem.bySelectType = ITEM_NOT_POS;

	m_pImgStack					= NULL;
	for(i = 0; i < 2; i++)
	{
		m_bKnowON[i] = FALSE;
	}
	m_bKnowTwinkle = FALSE;
	m_fTimeElapseButtonCheck	= GAME_BUTTON_CHECK_ON;	
	
	// 2007-03-02 by bhsohn ���� ���� �߰� ����
	m_nMultiSelCnt = 0;	
	for(i = 0; i < MAX_MULTI_SEL;i++)
	{
		m_stMultiSelectItem[i].pSelectItem = NULL;
		m_stMultiSelectItem[i].pSelectIcon = NULL;
		m_stMultiSelectItem[i].bySelectType = ITEM_NOT_POS;
	}

	// 2007-07-04 by bhsohn ���۷����� �߰�
	m_pFaqBtn = NULL;	
	m_pCouponBtn = NULL;
	// 2009. 10. 14 by jskim ������ī ����
	m_pTut_SelBtn = NULL;
	//end 2009. 10. 14 by jskim ������ī ����
	// 2007-07-27 by bhsohn ���� �߰� �� ���� ���۷����Ϳ� ����
	m_bShowStatOpWnd = FALSE;

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	m_pINFSecuMain = NULL;

	// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	m_pMotherShipC = NULL;

	// 2015-05-01 by killburne
	m_pStrategicPointDisplay = NULL;

	m_bBuyMessage = FALSE;

	// 2008-10-14 by bhsohn VOIP����
//	m_bVOIPSpeaking = FALSE;

	// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
	m_pINFGameMainSysMsg = NULL;
	
	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	m_pINFOpJoystick = NULL;	
	// end 2008-11-13 by bhsohn ���̽�ƽ �۾�


//#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_GruopImagemanager = NULL;																	  
//#endif
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pGameData = pGameData;		 
#endif

	m_nAddPosY = 0;    // 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
}

CINFGameMain::~CINFGameMain()
{
	FLOG( "~CINFGameMain()" );
	g_pGameMain = NULL;

//#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	util::del(m_GruopImagemanager);															  
//#endif
	util::del(m_pUnitInfoBar) ;
	util::del(m_pInfWindow) ;
//	util::del(m_pParty);
	util::del(m_pCommunity);
	util::del(m_pWeaponInfo ) ;

	util::del(m_pTrade) ;
	util::del(m_pInven) ;
	util::del(m_pSystem) ;
	util::del(m_pCharacterInfo) ;

	util::del(m_pChat) ;
	util::del(m_pQuickSlot);
	util::del(m_pMiniMap);
	util::del(m_pIcon) ;
//	util::del(m_pShop) ;
	util::del(m_pUnitNameInfo);
	util::del(m_pQuest) ;
	util::del(m_pMission) ;
	util::del(m_pItemInfo) ;
	// 2009-02-03 by bhsohn ���� ������ �� ����
	util::del(m_pEquipItemInfo);	// ���� ������ ������ ����
	// end 2009-02-03 by bhsohn ���� ������ �� ����

//	util::del(m_pNotice) ;
	util::del(m_pUnitState) ;
	util::del(m_pAttackDirection) ;
	util::del(m_pGameCountDown) ;
	util::del(m_pDamageView) ;
	util::del(m_pOtherCharInfo) ;
	util::del(m_pInfGameMainFaq) ;
	util::del(m_pMenuList) ;

	util::del(m_pFontToolTip) ;
	util::del(m_pFontTimeLimit) ;
	util::del(m_pFontDrawMent) ;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pGameData = NULL;
#else
	util::del(m_pGameData) ;
#endif
	util::del(m_pInfSkill);
	util::del(m_pMp3Player);
	
	// 2007-06-12 by bhsohn �̼� �������̽� ������
	//util::del(m_pMissionInfo);
	util::del(m_pMissionMain);
	
	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	util::del(m_pINFWorldRankWnd);
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
	
	// 2013-02-20 by bhsohn �ΰ��� ����â ó��
	util::del(m_pINFItemMixWnd);
	// END 2013-02-20 by bhsohn �ΰ��� ����â ó��
	// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
	util::del(m_pINFArmorCollectWnd);		
	// END 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���

	// 2007-08-28 by dgwoo ���������� class�߰�.
	util::del(m_pOutPost);
	util::del(m_pChangeCharactor);
	util::del(m_pCouponWindow);

	// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
	util::del(m_pINFGameMainSysMsg);

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	util::del(m_pINFOpJoystick);	
	// end 2008-11-13 by bhsohn ���̽�ƽ �۾�

	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	util::del(m_pINFSpeakeMsg);	
	
	//util::del(m_pCommunityVOIP);

//	util::del(m_pImgUnitLock) ;
	int i;
	for(i=0;i<GAMEMAIN_BUTTON_NUMBER;i++)
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		util::del( m_pImgButton[i] );															  
#else 
		for(int j=0;j<BUTTON_STATE_NUMBER;j++)
		{
			util::del(m_pImgButton[i][j]);
		}
#endif
	}
	util::del(m_pImgMission);
	util::del(m_pHelpDesk);
	for(i=0; i<3; i++)
	{
		util::del(m_pImgTextPopUp[i]);
	}

	util::del( m_pImgTextBg );
	
	// 2005-03-03 by jschoi
	util::del(m_pRequestEnableBack);
	util::del(m_pRequestEnableTriangle);
	util::del(m_pAltiMeterGage);
	util::del(m_pAltiMeterPin);
	
	for(i=0;i<SIZE_MAX_POS;i++)
	{
		if(m_pItemInfoWear[i] != NULL)	{
		util::del( m_pItemInfoWear[i]);
		}
		if(m_pITEMG[i] != NULL)	{
			util::del( m_pITEMG[i]);
		}
	}

	util::del(m_pCityBoard);

	m_stSelectItem.pSelectItem = NULL;
	m_stSelectItem.pSelectIcon = NULL;
	m_stSelectItem.bySelectType = 0;

	// 2007-03-02 by bhsohn ���� ���� �߰� ����
	m_nMultiSelCnt = 0;	
	for(i = 0; i < MAX_MULTI_SEL;i++)
	{
		m_stMultiSelectItem[i].pSelectItem = NULL;
		m_stMultiSelectItem[i].pSelectIcon = NULL;
		m_stMultiSelectItem[i].bySelectType = 0;
	}
	// end 2007-03-02 by bhsohn ���� ���� �߰� ����

	util::del(m_pImgStack);

	// 2007-07-04 by bhsohn ���۷����� �߰�
	util::del(m_pFaqBtn);	 
	util::del(m_pCouponBtn);
	// end 2007-07-04 by bhsohn ���۷����� �߰�
	// 2009. 10. 14 by jskim ������ī ����
	util::del(m_pTut_SelBtn);
	//end 2009. 10. 14 by jskim ������ī ����

	// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	util::del(m_pMotherShipC);

	// 2015-05-01 by killburne
	util::del(m_pStrategicPointDisplay);

	// 2008. 12. 16 by ckPark ������ ��� ����
	m_listItemDelay.clear();
	// end 2008. 12. 16 by ckPark ������ ��� ����


	// 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����
	m_listSkillDelay.clear();
	// end 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����

	// 2009. 08. 21 by ckPark ĳ�������� �����ϱ⿡ ������ üũ
	memset( m_szCashGiftSendCharacterName, 0, sizeof( m_szCashGiftSendCharacterName ) );
	// end 2009. 08. 21 by ckPark ĳ�������� �����ϱ⿡ ������ üũ

	// 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
	ResetToolTipEx();
	// End. 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
}



HRESULT CINFGameMain::InitDeviceObjects()
{
	FLOG( "CINFGameMain::InitDeviceObjects()" );

	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
#else
	char strPath[256];
	g_pD3dApp->LoadPath( strPath, IDS_DIRECTORY_TEXTURE, "interface.tex");
	SetResourceFile(strPath);
#endif
//#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_GruopImagemanager = new CINFGroupManager( g_pD3dApp->m_pImageList, m_pGameData );
	m_GruopImagemanager->InitDeviceObjects();
//#endif
	
	m_pUnitInfoBar = new CINFGameMainUnitInfoBar(this) ;
	m_pUnitInfoBar->SetGameData(m_pGameData);
	m_pUnitInfoBar->InitDeviceObjects() ;

	m_pInfWindow = new CINFWindow(this) ;
	m_pInfWindow->SetGameData(m_pGameData);
	m_pInfWindow->InitDeviceObjects() ;

	m_pWeaponInfo = new CINFWeaponInfo(this) ;
	m_pWeaponInfo->SetGameData(m_pGameData);
	m_pWeaponInfo->InitDeviceObjects() ;

	m_pCommunity = new CINFCommunity(this);
	m_pCommunity->SetGameData(m_pGameData);
	m_pCommunity->InitDeviceObjects() ;

	// 2024/12/23 - Nexy : QOL info setup
	m_pQOLInfo = new CINFQOLinfo(this, m_pCommunity);
	m_pQOLInfo->SetGameData(m_pGameData);
	m_pQOLInfo->InitDeviceObjects();

	m_pTrade = new CINFTrade(this) ;
	m_pTrade->SetGameData(m_pGameData);
	m_pTrade->InitDeviceObjects() ;

	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	//m_pInven = new CINFInven(this) ;
	m_pInven = new CINFInvenExtend(this) ;
	
	m_pInven->SetGameData(m_pGameData);
	m_pInven->InitDeviceObjects() ;

	// 2008-03-19 by bhsohn Ep3�ɼ�â
	//m_pSystem = new CINFSystem(this) ;
	m_pSystem = new CINFOptionSystem(this) ;
	m_pSystem->SetGameData(m_pGameData);
	m_pSystem->InitDeviceObjects() ;
	// end 2008-03-19 by bhsohn Ep3�ɼ�â

	// 2008-09-22 by bhsohn EP3 ĳ���� â
	//m_pCharacterInfo = new CINFCharacterInfo(this) ;
	m_pCharacterInfo = new CINFCharacterInfoExtend(this) ;

	m_pCharacterInfo->SetGameData(m_pGameData);
	m_pCharacterInfo->InitDeviceObjects() ;

//	m_pShop = new CINFShop(this) ;
//	m_pShop->SetGameData(m_pGameData);
//	m_pShop->InitDeviceObjects() ;

	m_pMission = new CINFMission(this) ;
	m_pMission->SetGameData(m_pGameData);
	m_pMission->InitDeviceObjects() ;

	m_pUnitNameInfo = new CINFUnitNameInfo(this) ;
	m_pUnitNameInfo->SetGameData(m_pGameData);
	m_pUnitNameInfo->InitDeviceObjects() ;

	m_pIcon = new CINFIcon() ;
	m_pIcon->InitDeviceObjects() ;

	m_pFontToolTip = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,1024,32);		 //2008-12-19 dgwoo ���� ������ �ø�.
	m_pFontToolTip->InitDeviceObjects(g_pD3dDev);

	m_pFontTimeLimit = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,512,32);
	m_pFontTimeLimit->InitDeviceObjects(g_pD3dDev);
	
	m_pFontDrawMent = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,512,32);
	m_pFontDrawMent->InitDeviceObjects(g_pD3dDev);

	int nWidth, nHeight;
	nWidth = nHeight = -1;		
	if(g_pD3dApp->IsOptionEtc(OPTION_RADIO_INTERFACE_POS))
	{
		float fWidth = (float)g_pD3dApp->GetBackBufferDesc().Width;
		float fHeight = (float)g_pD3dApp->GetBackBufferDesc().Height;
		
		stcuctRateRect stRateRect = g_pD3dApp->GetOptionInterfacePOS();
		stcuctRateRect stChatRect = g_pD3dApp->GetChatInterfacePOS();
		if((stRateRect.fGameWidth == fWidth)
			&&(stRateRect.fGameHeight == fHeight))
		{
			nWidth	= stChatRect.fRateWidth;
			nHeight	= stChatRect.fRateHeight;
		}
		else
		{				
			float fRateWidth = (fWidth/stRateRect.fGameWidth);
			float fRateHeight = (fHeight/stRateRect.fGameHeight);
			if(fRateWidth == 0 )
			{					
				fRateWidth = 1;
			}
			if(fRateHeight == 0)
			{					
				fRateHeight = 1;
			}
			nWidth	= (int)(stChatRect.fRateWidth*fRateWidth);
			nHeight	= (int)(stChatRect.fRateHeight*fRateHeight);	
		}				
	}

	m_pChat = new CINFGameMainChat(this, nWidth, nHeight);
	// end 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����


	m_pChat->SetGameData(m_pGameData);
	m_pChat->InitDeviceObjects() ;

	m_pQuickSlot = new CINFGameMainQSlot(this) ;
	m_pQuickSlot->SetGameData(m_pGameData);
	m_pQuickSlot->InitDeviceObjects() ;

	m_pMiniMap = new CINFGameMainMiniMap(this) ;
	m_pMiniMap->SetGameData(m_pGameData);

	m_pMiniMap->InitDeviceObjects() ;

	m_pItemInfo = new CINFItemInfo(m_pParent);
	m_pItemInfo->SetGameData(m_pGameData);
	m_pItemInfo->InitDeviceObjects() ;
	// 2009-02-03 by bhsohn ���� ������ �� ����
	m_pEquipItemInfo = new CINFItemInfo(m_pParent);
	m_pEquipItemInfo->SetMyEquipItem(TRUE);
	m_pEquipItemInfo->SetGameData(m_pGameData);
	m_pEquipItemInfo->InitDeviceObjects() ;	
	// end 2009-02-03 by bhsohn ���� ������ �� ����

//	m_pNotice = new CINFNotice() ;
//	m_pNotice->InitDeviceObjects() ;

	m_pUnitState = new CINFUnitState(this) ;
	m_pUnitState->SetGameData(m_pGameData);
	m_pUnitState->InitDeviceObjects() ;

	m_pAttackDirection = new CINFAttackDirection(this) ;
	m_pAttackDirection->SetGameData(m_pGameData);
	m_pAttackDirection->InitDeviceObjects() ;

	DataHeader * pDataHeader = NULL;


#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pImgButton[GAMEMAIN_BUTTON_INVEN] =		new CINFImageBtn;
	m_pImgButton[GAMEMAIN_BUTTON_INFO] =		new CINFImageBtn;
	m_pImgButton[GAMEMAIN_BUTTON_COMMUNITY] =	new CINFImageBtn;
	m_pImgButton[GAMEMAIN_BUTTON_TRADE] =		new CINFImageBtn;
	m_pImgButton[GAMEMAIN_BUTTON_SYSTEM] =		new CINFImageBtn;

// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
// 	m_pImgButton[GAMEMAIN_BUTTON_INVEN]->InitDeviceObjects( "mnbtn03" , "mnbtn00", "mnbtn00", "mnbtn00");
// 	m_pImgButton[GAMEMAIN_BUTTON_INFO]->InitDeviceObjects( "mnbtn13" , "mnbtn10", "mnbtn10", "mnbtn10" );
// 	m_pImgButton[GAMEMAIN_BUTTON_COMMUNITY]->InitDeviceObjects( "mnbtn23" , "mnbtn20", "mnbtn20", "mnbtn20" );
// 	m_pImgButton[GAMEMAIN_BUTTON_TRADE]->InitDeviceObjects( "mnbtn33" , "mnbtn30", "mnbtn30", "mnbtn30" );
// 	m_pImgButton[GAMEMAIN_BUTTON_SYSTEM]->InitDeviceObjects( "mnbtn43" , "mnbtn40", "mnbtn40", "mnbtn40" );
	m_pImgButton[GAMEMAIN_BUTTON_INVEN]->InitDeviceObjects( "mnbtn03" , "mnbtn00", "mnbtn00", "mnbtn00","STRTOOLTIP102" );
	m_pImgButton[GAMEMAIN_BUTTON_INFO]->InitDeviceObjects( "mnbtn13" , "mnbtn10", "mnbtn10", "mnbtn10","STRTOOLTIP103" );
	m_pImgButton[GAMEMAIN_BUTTON_COMMUNITY]->InitDeviceObjects( "mnbtn23" , "mnbtn20", "mnbtn20", "mnbtn20","STRTOOLTIP104" );
	m_pImgButton[GAMEMAIN_BUTTON_TRADE]->InitDeviceObjects( "mnbtn33" , "mnbtn30", "mnbtn30", "mnbtn30","STRTOOLTIP105" );
	m_pImgButton[GAMEMAIN_BUTTON_SYSTEM]->InitDeviceObjects( "mnbtn43" , "mnbtn40", "mnbtn40", "mnbtn40","STRTOOLTIP106" );
// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
#endif

	int i;
	for(i=0;i<GAMEMAIN_BUTTON_NUMBER;i++)
	{

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pImgButton[i]->SetAnimation( SCALE_TYPE, OVER_TYPE, FALSE, 1.0f, 1.0f, 1.0f );
		m_pImgButton[i]->SetAnimation( SCALE_TYPE, CLICK_TYPE, FALSE, 0.0f, 1.0f, 1.0f );
		m_pImgButton[i]->SetAniScale(0.8f, 0.8f);	 
#else							
		for(int j=0;j<BUTTON_STATE_NUMBER;j++)
		{
			char buf[32];
			wsprintf(buf, "mnbtn%d%d", i,j);
			pDataHeader = m_pGameData->Find( buf );
			m_pImgButton[i][j] = new CINFImage;
			m_pImgButton[i][j]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
		}
#endif
	}
	// 2007-07-04 by bhsohn ���۷����� �߰�

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	{
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "op_faq3");
		wsprintf(szDownBtn, "op_faq0");
		wsprintf(szSelBtn, "op_faq0");
		wsprintf(szDisBtn, "op_faq0");
		if(NULL == m_pFaqBtn)
		{
			m_pFaqBtn = new CINFImageBtn;
		}
		// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		//m_pFaqBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);
		m_pFaqBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn, "STRTOOLTIP101");		
		// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		m_pFaqBtn->SetAnimation( SCALE_TYPE, OVER_TYPE, FALSE, 1.0f, 1.0f, 1.0f );
		m_pFaqBtn->SetAnimation( SCALE_TYPE, CLICK_TYPE, FALSE, 0.0f, 1.0f, 1.0f );
		m_pFaqBtn->SetAniScale(0.8f, 0.8f);
	}													   
#else	 
	{
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "op_faq3");
		wsprintf(szDownBtn, "op_faq1");
		wsprintf(szSelBtn, "op_faq0");
		wsprintf(szDisBtn, "op_faq2");
		if(NULL == m_pFaqBtn)
		{
			m_pFaqBtn = new CINFImageBtn;
		}
		m_pFaqBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}
#endif
			  
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pImgButtonBK = new CINFImageEx;
	pDataHeader = m_pGameData->Find( "mnbtnBG" );
	m_pImgButtonBK->InitDeviceObjects( pDataHeader );	
#endif
	// 2009. 10. 14 by jskim ������ī ����
	{
		char tulUpBtn[30], tulDownBtn[30], tulSelBtn[30], tulDisBtn[30];
		wsprintf(tulUpBtn, "Tut_sel3");
		wsprintf(tulDownBtn, "Tut_sel1");
		wsprintf(tulSelBtn, "Tut_sel0");
		wsprintf(tulDisBtn, "Tut_sel2");
		if(NULL == m_pTut_SelBtn)
		{
			m_pTut_SelBtn = new CINFImageBtn;
		}
		m_pTut_SelBtn->InitDeviceObjects(tulUpBtn, tulDownBtn, tulSelBtn, tulDisBtn);		
	}
	//end 2009. 10. 14 by jskim ������ī ����
	
	// end 2007-07-04 by bhsohn ���۷����� �߰�
	{
		if(NULL == m_pCouponBtn)
		{
			m_pCouponBtn = new CINFImageBtn;
		}
		m_pCouponBtn->InitDeviceObjects("couponB");
		m_pCouponBtn->EnableBtn(FALSE);
		m_pCouponBtn->ShowWindow(FALSE);
	}
	

	char buf[32];
	for(i=0; i<3; i++)
	{
		wsprintf(buf, "boxtip%d",i);
		pDataHeader = m_pGameData->Find( buf );
		m_pImgTextPopUp[i] = new CINFImageEx;
		m_pImgTextPopUp[i]->InitDeviceObjects( pDataHeader );
	}


	wsprintf(buf, "boxtip1");
	pDataHeader = m_pGameData->Find( buf );

	if ( pDataHeader )
	{
		m_pImgTextBg = new CINFImageEx;
		m_pImgTextBg->InitDeviceObjects( pDataHeader );
	}

	pDataHeader = m_pGameData->Find( "mnbtn70" );
	m_pImgMission = new CINFImageEx;
	m_pImgMission->InitDeviceObjects( pDataHeader );

	pDataHeader = m_pGameData->Find("mnbtn71");
	m_pImgStack = new CINFImageEx;
	m_pImgStack->InitDeviceObjects( pDataHeader );

	m_pQuest = new CINFQuest(this);
	m_pQuest->SetGameData(m_pGameData);
	m_pQuest->InitDeviceObjects();
	
	m_pInfSkill = new CINFSkill();
	m_pInfSkill->SetGameData(m_pGameData);
	m_pInfSkill->InitDeviceObjects();

	m_pGameCountDown = new CINFGameCountDown();

	m_pDamageView = new CINFDamageView();
	m_pDamageView->SetGameData( m_pGameData );
	m_pDamageView->InitDeviceObjects();

	m_pMp3Player = new CINFMp3Player();
	m_pMp3Player->SetGameData( m_pGameData );
	m_pMp3Player->InitDeviceObjects();
	m_pMp3Player->FindMp3File();

	
	// 2007-06-12 by bhsohn �̼� �������̽� ������
//	m_pMissionInfo = new CINFMissionInfo();
//	m_pMissionInfo->SetGameData( m_pGameData );
//	m_pMissionInfo->InitDeviceObjects();
	{
		m_pMissionMain = new CINFMissionMain();
		m_pMissionMain->SetGameData( m_pGameData );
		m_pMissionMain->InitDeviceObjects();
	}
	
	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	CWorldRankManager*	pWorldRankManager = g_pD3dApp->GetWorldRankManager();
	if(pWorldRankManager->GetUseWorldRanking())
	{
		if(NULL == m_pINFWorldRankWnd)
		{
			m_pINFWorldRankWnd = new CINFWorldRankWnd();		
			m_pINFWorldRankWnd->InitDeviceObjects();
		}
	}
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	// 2013-02-20 by bhsohn �ΰ��� ����â ó��
#if defined(C_INGAME_MIX_ITEM)
	{
		if(NULL == m_pINFItemMixWnd)
		{
			m_pINFItemMixWnd = new CINFItemMixWnd(this);
			m_pINFItemMixWnd->SetGameData(m_pGameData);
			m_pINFItemMixWnd->InitDeviceObjects();
		}
	}	
#endif
	// END 2013-02-20 by bhsohn �ΰ��� ����â ó��

	// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
#ifdef SC_COLLECTION_ARMOR_JHSEOL_BCKIM
	{
		if(NULL == m_pINFArmorCollectWnd)
		{
			m_pINFArmorCollectWnd = new CINFArmorCollectWnd(this);
			m_pINFArmorCollectWnd->SetGameData(m_pGameData);
			m_pINFArmorCollectWnd->InitDeviceObjects();
		}
	}
#endif
	// END 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���


	{// 2007-11-21 by dgwoo
		m_pChangeCharactor = new CINFChangeCharactor(this);
		m_pChangeCharactor->SetGameData(m_pGameData);
		m_pChangeCharactor->InitDeviceObjects();
	}
	{
		m_pCouponWindow = new CINFCouponWindow(this);
		m_pCouponWindow->SetGameData(m_pGameData);
		m_pCouponWindow->InitDeviceObjects();
	}
	// 2007-08-28 by dgwoo ���������� class�߰�.
	{
		m_pOutPost = new CINFGameMainOutPost();
		m_pOutPost->SetGameData(m_pGameData);
		m_pOutPost->InitDeviceObjects();
	}


	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	{
		m_pINFSpeakeMsg = new CINFSpeakeMsg;
		m_pINFSpeakeMsg->SetGameData( m_pGameData );
		m_pINFSpeakeMsg->InitDeviceObjects();		
	}
	// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	
	m_pOtherCharInfo = new CINFOtherCharInfo(this);
	m_pOtherCharInfo->SetGameData( m_pGameData );
	m_pOtherCharInfo->InitDeviceObjects();

	m_pInfGameMainFaq = new CINFGameMainFAQ();
	m_pInfGameMainFaq->SetGameData( m_pGameData );
	m_pInfGameMainFaq->InitDeviceObjects();
	
	m_pMenuList = new CINFMenuList();
	m_pMenuList->SetGameData( m_pGameData );
	m_pMenuList->InitDeviceObjects();
	
	// 2005-03-03 by jschoi
	m_pRequestEnableBack = new CINFImageEx;
	pDataHeader = FindResource("rq_enb");
	m_pRequestEnableBack->InitDeviceObjects( pDataHeader );

	m_pRequestEnableTriangle = new CINFImageEx;
	pDataHeader = FindResource("rq_ent");
	m_pRequestEnableTriangle->InitDeviceObjects( pDataHeader);

	m_pAltiMeterGage = new CINFImageEx;
	pDataHeader = FindResource("altig");
	m_pAltiMeterGage->InitDeviceObjects( pDataHeader );

	m_pAltiMeterPin = new CINFImageEx;
	pDataHeader = FindResource("altip");
	m_pAltiMeterPin->InitDeviceObjects(pDataHeader);
	
	// 2005-10-10 by ispark
	//m_pCommunityVOIP = new CINFCommunityVOIP();
	//m_pCommunityVOIP->SetGameData(m_pGameData);
	//m_pCommunityVOIP->InitDeviceObjects();

	// 2006-04-19 by ispark
	m_pCityBoard = new CINFCityBoard;
	if(g_pGround)
		m_pCityBoard->InitDeviceObjects(g_pGround->m_nMapNumber);	

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	InitSecurityPassMode();

	// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	{
		m_pMotherShipC		= new CINFMotherShipManager(m_pGameData);
		//m_pMotherShipC->SetGameData(m_pGameData);
		m_pMotherShipC->InitDeviceObjects();
	}
	// end 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	// 2015-05-01 by killburne
	{
		m_pStrategicPointDisplay = new CINFStrategicPointManager();
		m_pStrategicPointDisplay->SetGameData(m_pGameData);
		m_pStrategicPointDisplay->InitDeviceObjects();
	}
	{
		// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
		if(NULL == m_pINFGameMainSysMsg)
		{
			m_pINFGameMainSysMsg = new CINFGameMainSysMsg(this);
			m_pINFGameMainSysMsg->SetGameData(m_pGameData);
			m_pINFGameMainSysMsg->InitDeviceObjects();
		}
	}

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	{
		if(NULL == m_pINFOpJoystick)
		{
			m_pINFOpJoystick = new CINFOpJoystick(this);
			m_pINFOpJoystick->SetGameData(m_pGameData);
			m_pINFOpJoystick->InitDeviceObjects();
		}
	}
	// end 2008-11-13 by bhsohn ���̽�ƽ �۾�


	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��	
	{
		// �������̽� �����
		BOOL bShowInter = !g_pD3dApp->IsOptionEtc(OPTION_RADIO_INTERFACE_HIDE);

		g_pInterface->SetShowInterface(bShowInter);
	}
	// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

	ShowSysMsgWnd(TRUE);//2012-03-15 by jhahn ���� �ð� �����ֱ�

	return S_OK ;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void InitWarp()
/// \brief		���� ����� Ŭ�������� ������� �͵�.
/// \author		dgwoo
/// \date		2007-02-22 ~ 2007-02-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::InitWarp()
{
	m_pMiniMap->InitMapSet();
}

void CINFGameMain::InitHelpSystem(BOOL bShow)
{
	m_bHelpDeskFlag = bShow;
	if(bShow)
	{
		if(m_pHelpDesk)
		{
			m_pHelpDesk->InvalidateDeviceObjects();
			m_pHelpDesk->DeleteDeviceObjects();
			util::del(m_pHelpDesk);
		}
		m_pHelpDesk = new CINFGameHelpDesk(this);
		m_pHelpDesk->SetGameData(m_pGameData);
	DBGOUT("---------- Help InitDeviceObjects() ----------\n");
		m_pHelpDesk->InitDeviceObjects();
	DBGOUT("---------- Help RestoreDeviceObjects() ----------\n");
		m_pHelpDesk->RestoreDeviceObjects();
	DBGOUT("---------- Help StartHelpDesk() ----------\n");
		m_pHelpDesk->StartHelpDesk();

		// 2007-01-26 by bhsohn �ű����� �̼� �������̽�	
		// �ű� ���� ������ ����.		
		UpdateLV1NoviceUserHelper();		
	}
	else
	{
		if(m_pHelpDesk)
		{
			m_pHelpDesk->InvalidateDeviceObjects();
			m_pHelpDesk->DeleteDeviceObjects();
			util::del(m_pHelpDesk);
		}
	}
}
HRESULT CINFGameMain::RestoreDeviceObjects()
{
	FLOG( "CINFGameMain::RestoreDeviceObjects()" );
	if(!m_bRestored)
	{
		if(m_pUnitInfoBar )
			m_pUnitInfoBar->RestoreDeviceObjects() ;
		
		// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
		if(m_pINFGameMainSysMsg)
		{
			m_pINFGameMainSysMsg->RestoreDeviceObjects() ;
		}
		// end 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�

		// 2008-11-13 by bhsohn ���̽�ƽ �۾�
		if(m_pINFOpJoystick)
		{
			m_pINFOpJoystick->RestoreDeviceObjects() ;
		}
		// end 2008-11-13 by bhsohn ���̽�ƽ �۾�
	
		if(m_pInfWindow )
			m_pInfWindow->RestoreDeviceObjects() ;
		if(m_pWeaponInfo )
			m_pWeaponInfo->RestoreDeviceObjects() ;

		if(m_pCommunity)
			m_pCommunity->RestoreDeviceObjects() ;
		if (m_pQOLInfo)
			m_pQOLInfo->RestoreDeviceObjects() ;
		if(m_pTrade && !m_pTrade->m_bRestored )
			m_pTrade->RestoreDeviceObjects() ;
		if(m_pInven && !m_pInven->m_bRestored )
			m_pInven->RestoreDeviceObjects() ;
		if(m_pSystem && !m_pSystem->m_bRestored )
			m_pSystem->RestoreDeviceObjects() ;
		if(m_pCharacterInfo && !m_pCharacterInfo->m_bRestored )
			m_pCharacterInfo->RestoreDeviceObjects() ;
//		if(m_pShop && !m_pShop->m_bRestored )
//			m_pShop->RestoreDeviceObjects() ;

		if(m_pMission )
			m_pMission->RestoreDeviceObjects() ;
		if(m_pIcon )
			m_pIcon->RestoreDeviceObjects() ;
		if(m_pUnitNameInfo )
			m_pUnitNameInfo->RestoreDeviceObjects() ;
		if(m_pChat )
			m_pChat->RestoreDeviceObjects() ;
		if(m_pQuickSlot )
			m_pQuickSlot->RestoreDeviceObjects() ;
		if(m_pMiniMap )
			m_pMiniMap->RestoreDeviceObjects() ;
		if(m_pItemInfo )
			m_pItemInfo->RestoreDeviceObjects() ;
		// 2009-02-03 by bhsohn ���� ������ �� ����
		if(m_pEquipItemInfo)
		{			
			m_pEquipItemInfo->RestoreDeviceObjects();
		}
		// end 2009-02-03 by bhsohn ���� ������ �� ����
//		if(m_pNotice )
//			m_pNotice->RestoreDeviceObjects() ;
		if(m_pUnitState )
			m_pUnitState->RestoreDeviceObjects() ;
		if(m_pAttackDirection )
			m_pAttackDirection->RestoreDeviceObjects() ;
		if(m_pFontToolTip)
			m_pFontToolTip->RestoreDeviceObjects();
		if(m_pFontTimeLimit)
		    m_pFontTimeLimit->RestoreDeviceObjects();
		if(m_pFontDrawMent)
		    m_pFontDrawMent->RestoreDeviceObjects();
		if(m_bShowHelp)
		{
			for(int i=0;i<HELP_NUM;i++)
			{
				if(m_pHelp[i])
					m_pHelp[i]->RestoreDeviceObjects();
			}
		}
		if(m_pSelectIcon)
			m_pSelectIcon->RestoreDeviceObjects();
		for(int i=0; i<3; i++)
		{
			if(m_pImgTextPopUp[i])
				m_pImgTextPopUp[i]->RestoreDeviceObjects();
		}

		if ( m_pImgTextBg )
			m_pImgTextBg->RestoreDeviceObjects();


#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		if(m_pImgButtonBK)
			m_pImgButtonBK->RestoreDeviceObjects();												  
#endif

//		if(m_pImgUnitLock)
//			m_pImgUnitLock->RestoreDeviceObjects();
		for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++)
		{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
			m_pImgButton[i]->RestoreDeviceObjects();
			m_pImgButton[i]->SetBtnPosition(GAMEMAIN_BUTTON_START_X + GAMEMAIN_BUTTON_INTERVAL * i, GAMEMAIN_BUTTON_START_Y);
			m_pImgButton[i]->SetLineUp( CENTER_BOTTOM_LINEUP );									  
#else			
			for(int j=0;j<BUTTON_STATE_NUMBER;j++)
			{
				m_pImgButton[i][j]->RestoreDeviceObjects();
			}
#endif
		}

		// 2007-07-04 by bhsohn ���۷����� �߰�
		{				
			m_pFaqBtn->RestoreDeviceObjects();		
			m_pFaqBtn->SetBtnPosition(FAQ_BTN_POS_X, FAQ_BTN_POS_Y);

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
			m_pFaqBtn->SetLineUp( CENTER_BOTTOM_LINEUP );										  
#endif
		}
		// 2009. 10. 14 by jskim ������ī ����
		m_pTut_SelBtn->RestoreDeviceObjects();
		m_pTut_SelBtn->SetBtnPosition(TUTORIAL_BUTTON_X, TUTORIAL_BUTTON_Y);
		//end 2009. 10. 14 by jskim ������ī ����
		// end 2007-07-04 by bhsohn ���۷����� �߰�
		{
			m_pCouponBtn->RestoreDeviceObjects();
			m_pCouponBtn->SetBtnPosition(COUPON_BTN_POS_X,COUPON_BTN_POS_Y);
		}

		m_pImgMission->RestoreDeviceObjects();
		m_pImgStack->RestoreDeviceObjects();
		if(m_pInfSkill)
			m_pInfSkill->RestoreDeviceObjects();
		if(m_pDamageView)
			m_pDamageView->RestoreDeviceObjects();
		if(m_pOtherCharInfo)
			m_pOtherCharInfo->RestoreDeviceObjects();
		if(m_pInfGameMainFaq)
			m_pInfGameMainFaq->RestoreDeviceObjects();
		if(m_pMenuList)
			m_pMenuList->RestoreDeviceObjects();

		// 2005-03-03 by jschoi
		m_pRequestEnableBack->RestoreDeviceObjects();
		m_pRequestEnableTriangle->RestoreDeviceObjects();

		// 2006-04-11 by ispark
		if(m_pCityBoard)
			m_pCityBoard->RestoreDeviceObjects();

		// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
		m_pMotherShipC->RestoreDeviceObjects();

		// 2015-05-01 by killburne
		m_pStrategicPointDisplay->RestoreDeviceObjects();

		// 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
		ResetToolTipEx();
		// End. 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.

		m_bRestored = TRUE;
	}

	if(m_pHelpDesk )
		m_pHelpDesk->RestoreDeviceObjects();
	if(m_pQuest)
			m_pQuest->RestoreDeviceObjects();
	if(m_pMp3Player)
		m_pMp3Player->RestoreDeviceObjects();
	
	// 2007-06-12 by bhsohn �̼� �������̽� ������
//	if(m_pMissionInfo)
//		m_pMissionInfo->RestoreDeviceObjects();
	if(m_pMissionMain)
		m_pMissionMain->RestoreDeviceObjects();
	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	if(m_pINFWorldRankWnd)
	{	
		m_pINFWorldRankWnd->RestoreDeviceObjects();
	}
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
	
	// 2013-02-20 by bhsohn �ΰ��� ����â ó��
	if(m_pINFItemMixWnd)
	{		
		m_pINFItemMixWnd->RestoreDeviceObjects();
	}	
	// END 2013-02-20 by bhsohn �ΰ��� ����â ó��

	// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
	if(m_pINFArmorCollectWnd)
	{		
		m_pINFArmorCollectWnd->RestoreDeviceObjects();
	}	
	// END 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���

	// 2007-08-28 by dgwoo ���������� class�߰�.
	if(m_pChangeCharactor)
		m_pChangeCharactor->RestoreDeviceObjects();
	if(m_pCouponWindow)
		m_pCouponWindow->RestoreDeviceObjects();
	if(m_pOutPost)
		m_pOutPost->RestoreDeviceObjects();

	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	if(m_pINFSpeakeMsg)
	{
		m_pINFSpeakeMsg->RestoreDeviceObjects();		 
	}
	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	if(m_pINFSecuMain)
	{
		m_pINFSecuMain->RestoreDeviceObjects();		
	}
	// end 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����

	//if(m_pCommunityVOIP) m_pCommunityVOIP->RestoreDeviceObjects();

	m_pAltiMeterGage->RestoreDeviceObjects();
	m_pAltiMeterPin->RestoreDeviceObjects();
	
	m_ptGageBack = m_pAltiMeterGage->GetImgSize();
	m_ptGagePin = m_pAltiMeterPin->GetImgSize();
	
	return S_OK ;
}

HRESULT CINFGameMain::DeleteDeviceObjects()
{
	FLOG( "CINFGameMain::DeleteDeviceObjects()" );
	if(m_pUnitInfoBar ) {
		m_pUnitInfoBar->DeleteDeviceObjects() ;
		util::del(m_pUnitInfoBar ) ; }

	// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
	if(m_pINFGameMainSysMsg)
	{
		m_pINFGameMainSysMsg->DeleteDeviceObjects() ;
		util::del(m_pINFGameMainSysMsg) ;
	}
	// end 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	if(m_pINFOpJoystick)
	{
		m_pINFOpJoystick->DeleteDeviceObjects() ;
		util::del(m_pINFOpJoystick) ;
	}
	// end 2008-11-13 by bhsohn ���̽�ƽ �۾�

	if(m_pInfWindow ) {
		m_pInfWindow->DeleteDeviceObjects() ;
		util::del(m_pInfWindow ) ; }
//	if(m_pParty ) {
//		m_pParty->DeleteDeviceObjects() ;
//		util::del(m_pParty); }
	if(m_pCommunity ) {
		m_pCommunity->DeleteDeviceObjects() ;
		util::del(m_pCommunity); }

	if(m_pWeaponInfo ) {
		m_pWeaponInfo->DeleteDeviceObjects() ;
		util::del(m_pWeaponInfo ) ; }

	if(m_pTrade ) {
		m_pTrade->DeleteDeviceObjects() ;
		util::del(m_pTrade ) ; }

	if(m_pInven ) {
		m_pInven->DeleteDeviceObjects() ;
		util::del(m_pInven ) ; }

	if(m_pSystem ) {
		m_pSystem->DeleteDeviceObjects() ;
		util::del(m_pSystem ) ; }

	if(m_pCharacterInfo ) {
		m_pCharacterInfo->DeleteDeviceObjects() ;
		util::del(m_pCharacterInfo ) ; }

	if(m_pChat ) {
		m_pChat->DeleteDeviceObjects() ;
		util::del(m_pChat ) ; }

	if(m_pQuickSlot ) {
		m_pQuickSlot->DeleteDeviceObjects() ;
		util::del(m_pQuickSlot ) ; }

	if(m_pMiniMap ) {
		m_pMiniMap->DeleteDeviceObjects() ;
		util::del(m_pMiniMap ) ; }
	if(m_pItemInfo ) {
		m_pItemInfo->DeleteDeviceObjects() ;
		util::del(m_pItemInfo ) ; }
	// 2009-02-03 by bhsohn ���� ������ �� ����
	if(m_pEquipItemInfo)
	{			
		m_pEquipItemInfo->DeleteDeviceObjects() ;
		util::del(m_pEquipItemInfo) ;		
	}
	// end 2009-02-03 by bhsohn ���� ������ �� ����

//	if(m_pNotice ) {
//		m_pNotice->DeleteDeviceObjects() ;
//		util::del(m_pNotice ) ; }

	if(m_pUnitState ) {
		m_pUnitState->DeleteDeviceObjects() ;
		util::del(m_pUnitState ) ; }

	if(m_pAttackDirection ) {
		m_pAttackDirection->DeleteDeviceObjects() ;
		util::del(m_pAttackDirection ) ; }

//	if(m_pShop ) {
//		m_pShop->DeleteDeviceObjects() ;
//		util::del(m_pShop ) ; }
	if(m_pQuest )
		m_pQuest->DeleteDeviceObjects() ;
	util::del(m_pQuest ) ;
	if(m_pMission ) {
		m_pMission->DeleteDeviceObjects() ;
		util::del(m_pMission ) ; }

	if(m_pUnitNameInfo ) {
		m_pUnitNameInfo->DeleteDeviceObjects() ;
		util::del(m_pUnitNameInfo ) ; }

	if(m_pMp3Player) {
		m_pMp3Player->DeleteDeviceObjects();
		util::del(m_pMp3Player);	}

	// 2007-06-12 by bhsohn �̼� �������̽� ������
//	if(m_pMissionInfo) {
//		m_pMissionInfo->DeleteDeviceObjects();
//		util::del(m_pMissionInfo);}
	if(m_pMissionMain) {
		m_pMissionMain->DeleteDeviceObjects();
		util::del(m_pMissionMain);}	
	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	if(m_pINFWorldRankWnd)
	{	
		m_pINFWorldRankWnd->DeleteDeviceObjects();
		util::del(m_pINFWorldRankWnd);
	}
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
	// 2013-02-20 by bhsohn �ΰ��� ����â ó��
	if(m_pINFItemMixWnd)
	{			
		m_pINFItemMixWnd->DeleteDeviceObjects();
		util::del(m_pINFItemMixWnd);
	}	
	// END 2013-02-20 by bhsohn �ΰ��� ����â ó��
	// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
	if(m_pINFArmorCollectWnd)
	{		
		m_pINFArmorCollectWnd->DeleteDeviceObjects();
		util::del(m_pINFArmorCollectWnd);
	}	
	// END 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���

	if(m_pChangeCharactor)
	{
		m_pChangeCharactor->DeleteDeviceObjects();
		util::del(m_pChangeCharactor);
	}
	if(m_pCouponWindow)
	{
		m_pCouponWindow->DeleteDeviceObjects();
		util::del(m_pCouponWindow);
	}
	// 2007-08-28 by dgwoo ���������� class�߰�.
	if(m_pOutPost)
	{
		m_pOutPost->DeleteDeviceObjects();
		util::del(m_pOutPost);
	}


	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	if(m_pINFSpeakeMsg) {
		m_pINFSpeakeMsg->DeleteDeviceObjects();
		util::del(m_pINFSpeakeMsg);}	

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	if(m_pINFSecuMain)
	{
		m_pINFSecuMain->DeleteDeviceObjects();
		util::del(m_pINFSecuMain);
	}
	// end 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	

	if(m_pFontToolTip ) {
		m_pFontToolTip->DeleteDeviceObjects() ;
		util::del(m_pFontToolTip ) ; }

	if(m_pFontTimeLimit ) {
		m_pFontTimeLimit->DeleteDeviceObjects() ;
		util::del(m_pFontTimeLimit ) ; }
	
	if(m_pFontDrawMent ) {
		m_pFontDrawMent->DeleteDeviceObjects() ;
		util::del(m_pFontDrawMent ) ; }

	if(m_pIcon ) {
		m_pIcon->DeleteDeviceObjects() ;
		util::del(m_pIcon ) ; }
	if(m_bShowHelp)
	{
		for(int i=0;i<HELP_NUM;i++)
		{
			if(m_pHelp[i])
			{
				m_pHelp[i]->DeleteDeviceObjects();
				util::del(m_pHelp[i] );
			}
		}
	}
	if(m_pSelectIcon)
	{
		m_pSelectIcon->DeleteDeviceObjects();
		util::del(m_pSelectIcon);
	}
	for(int i=0; i<3; i++)
	{

		if ( m_pImgTextPopUp[i] )
			m_pImgTextPopUp[i]->DeleteDeviceObjects();

		util::del(m_pImgTextPopUp[i]);
	}

	if ( m_pImgTextBg )
		m_pImgTextBg->DeleteDeviceObjects();

	util::del( m_pImgTextBg );


#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	if( m_pImgButtonBK )
	{
		m_pImgButtonBK->DeleteDeviceObjects();
		util::del(m_pImgButtonBK);
	}																							  
#endif

//	if(m_pImgUnitLock ) {
//		m_pImgUnitLock->DeleteDeviceObjects() ;
//		util::del(m_pImgUnitLock ); }
	for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++)
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pImgButton[i]->DeleteDeviceObjects();
		util::del(m_pImgButton[i]);															  
#else			 
		for(int j=0;j<BUTTON_STATE_NUMBER;j++)
		{
			m_pImgButton[i][j]->DeleteDeviceObjects();
			util::del(m_pImgButton[i][j]); 
		}
#endif
	}

	// 2007-07-04 by bhsohn ���۷����� �߰�
	if(m_pFaqBtn)
	{
		m_pFaqBtn->DeleteDeviceObjects();	
		util::del(m_pFaqBtn);
	}
	// end 2007-07-04 by bhsohn ���۷����� �߰�
	// 2009. 10. 14 by jskim ������ī ����
	if(m_pTut_SelBtn)
	{
		m_pTut_SelBtn->DeleteDeviceObjects();
		util::del(m_pTut_SelBtn);
	}
	//end 2009. 10. 14 by jskim ������ī ����
	if(m_pCouponBtn)
	{
		m_pCouponBtn->DeleteDeviceObjects();
		util::del(m_pCouponBtn);
	}


	m_pImgMission->DeleteDeviceObjects();
	util::del(m_pImgMission); 
	m_pImgStack->DeleteDeviceObjects();
	util::del(m_pImgStack);

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pGameData = NULL;
#else
	util::del(m_pGameData) ;
#endif


	if(m_pHelpDesk) 
	{
		m_pHelpDesk->DeleteDeviceObjects() ;
		util::del(m_pHelpDesk) ; 
	}
	
	if(m_pInfSkill)
	{
		m_pInfSkill->DeleteDeviceObjects();
		util::del(m_pInfSkill);
	}
	if(m_pDamageView)
	{
		m_pDamageView->DeleteDeviceObjects();
		util::del(m_pDamageView);
	}
	if(m_pOtherCharInfo)
	{
		m_pOtherCharInfo->DeleteDeviceObjects();
		util::del(m_pOtherCharInfo);
	}
	if(m_pInfGameMainFaq)
	{
		m_pInfGameMainFaq->DeleteDeviceObjects();
		util::del(m_pInfGameMainFaq);
	}
	if(m_pMenuList)
	{
		m_pMenuList->DeleteDeviceObjects();
		util::del(m_pMenuList);
	}

	// 2005-03-03 by jschoi
	m_pRequestEnableBack->DeleteDeviceObjects();
	m_pRequestEnableTriangle->DeleteDeviceObjects();
	util::del(m_pRequestEnableBack);
	util::del(m_pRequestEnableTriangle);

	m_pAltiMeterGage->DeleteDeviceObjects();
	m_pAltiMeterPin->DeleteDeviceObjects();
	util::del(m_pAltiMeterGage);
	util::del(m_pAltiMeterPin);

	//if(m_pCommunityVOIP)
	//{
	//	m_pCommunityVOIP->DeleteDeviceObjects();
	//	util::del(m_pCommunityVOIP);
	//}

	// 2006-04-11 by ispark
	if(m_pCityBoard)
		m_pCityBoard->DeleteDeviceObjects();
	util::del(m_pCityBoard);

	// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	if(m_pMotherShipC)
	{
		m_pMotherShipC->DeleteDeviceObjects();
		util::del(m_pMotherShipC);
	}
	if (m_pStrategicPointDisplay)
	{
		m_pStrategicPointDisplay->DeleteDeviceObjects();
		util::del(m_pStrategicPointDisplay);
	}
	// end 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�

	// 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
	ResetToolTipEx();
	// End. 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.

	return S_OK ;
}


HRESULT CINFGameMain::InvalidateDeviceObjects()
{
	FLOG( "CINFGameMain::InvalidateDeviceObjects()" );
	if(m_bRestored)
	{
		if(m_pUnitInfoBar )
			m_pUnitInfoBar->InvalidateDeviceObjects() ;
		// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
		if(m_pINFGameMainSysMsg)
		{
			m_pINFGameMainSysMsg->InvalidateDeviceObjects() ;			
		}
		// end 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�

		// 2008-11-13 by bhsohn ���̽�ƽ �۾�
		if(m_pINFOpJoystick)
		{
			m_pINFOpJoystick->InvalidateDeviceObjects() ;			
		}
		// end 2008-11-13 by bhsohn ���̽�ƽ �۾�
	
		if(m_pInfWindow )
			m_pInfWindow->InvalidateDeviceObjects() ;
		if(m_pWeaponInfo )
			m_pWeaponInfo->InvalidateDeviceObjects() ;


//		if(m_pParty && m_pParty->m_bRestored )
//			m_pParty->InvalidateDeviceObjects() ;
		if(m_pCommunity )
			m_pCommunity->InvalidateDeviceObjects() ;
		if (m_pQOLInfo)
			m_pQOLInfo->InvalidateDeviceObjects() ;
		if(m_pTrade && m_pTrade->m_bRestored)
			m_pTrade->InvalidateDeviceObjects() ;
		if(m_pInven && m_pInven->m_bRestored )
			m_pInven->InvalidateDeviceObjects() ;
		if(m_pSystem && m_pSystem->m_bRestored )
			m_pSystem->InvalidateDeviceObjects() ;
		if(m_pCharacterInfo && m_pCharacterInfo->m_bRestored )
			m_pCharacterInfo->InvalidateDeviceObjects() ;
//		if(m_pShop && m_pShop->m_bRestored )
//			m_pShop->InvalidateDeviceObjects() ;

		if(m_pChat )
			m_pChat->InvalidateDeviceObjects() ;
		if(m_pQuickSlot )
			m_pQuickSlot->InvalidateDeviceObjects() ;
		if(m_pMiniMap )
			m_pMiniMap->InvalidateDeviceObjects() ;
		if(m_pUnitNameInfo )
			m_pUnitNameInfo->InvalidateDeviceObjects() ;
		if(m_pQuest )
			m_pQuest->InvalidateDeviceObjects() ;
		if(m_pMp3Player)
			m_pMp3Player->InvalidateDeviceObjects();
		
		// 2007-06-12 by bhsohn �̼� �������̽� ������
//		if(m_pMissionInfo)
//			m_pMissionInfo->InvalidateDeviceObjects();
		if(m_pMissionMain)
			m_pMissionMain->InvalidateDeviceObjects();
		// 2009-02-13 by bhsohn ���� ��ŷ �ý���
		if(m_pINFWorldRankWnd)
		{	
			m_pINFWorldRankWnd->InvalidateDeviceObjects();			
		}
		// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
		// 2013-02-20 by bhsohn �ΰ��� ����â ó��
		if(m_pINFItemMixWnd)
		{			
			m_pINFItemMixWnd->InvalidateDeviceObjects();						
		}	
		// END 2013-02-20 by bhsohn �ΰ��� ����â ó��
		// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
		if(m_pINFArmorCollectWnd)
		{		
			m_pINFArmorCollectWnd->InvalidateDeviceObjects();			
		}	
		// END 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���

		if(m_pChangeCharactor)
			m_pChangeCharactor->InvalidateDeviceObjects();
		if(m_pCouponWindow)
			m_pCouponWindow->InvalidateDeviceObjects();
		// 2007-08-28 by dgwoo ���������� class�߰�.
		if(m_pOutPost)
		{
			m_pOutPost->InvalidateDeviceObjects();
		}
		// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
		if(m_pINFSpeakeMsg) 
		{
			m_pINFSpeakeMsg->InvalidateDeviceObjects();
		}
		// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�

		// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
		if(m_pINFSecuMain)
		{
			m_pINFSecuMain->InvalidateDeviceObjects();
		}
		// end 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
		

		if(m_pMission )
			m_pMission->InvalidateDeviceObjects() ;
		if(m_pIcon )
			m_pIcon->InvalidateDeviceObjects() ;
		if(m_pFontTimeLimit )
			m_pFontTimeLimit->InvalidateDeviceObjects() ;
		if(m_pFontDrawMent )
			m_pFontDrawMent->InvalidateDeviceObjects() ;
		if(m_pFontToolTip )
			m_pFontToolTip->InvalidateDeviceObjects() ;
		if(m_pItemInfo && m_pItemInfo->m_bRestored )
			m_pItemInfo->InvalidateDeviceObjects() ;
		// 2009-02-03 by bhsohn ���� ������ �� ����
		if(m_pEquipItemInfo&& m_pEquipItemInfo->m_bRestored )
		{			
			m_pEquipItemInfo->InvalidateDeviceObjects();
		}
		// end 2009-02-03 by bhsohn ���� ������ �� ����

//		if(m_pNotice  )
//			m_pNotice->InvalidateDeviceObjects() ;
		if(m_pUnitState  )
			m_pUnitState->InvalidateDeviceObjects() ;
		if(m_pAttackDirection  )
			m_pAttackDirection->InvalidateDeviceObjects() ;

		if(m_bShowHelp)
		{
			for(int i=0;i<HELP_NUM;i++)
			{
				if(m_pHelp[i])
					m_pHelp[i]->InvalidateDeviceObjects();
			}
		}
		if(m_pSelectIcon)
			m_pSelectIcon->InvalidateDeviceObjects();
		for(int i=0; i<3; i++)
		{
			if (m_pImgTextPopUp[i] )
				m_pImgTextPopUp[i]->InvalidateDeviceObjects();
		}
		
		if ( m_pImgTextBg )
			m_pImgTextBg->InvalidateDeviceObjects();


#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		if( m_pImgButtonBK )
		{
			m_pImgButtonBK->InvalidateDeviceObjects();
		}											  
#endif

		for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++)
		{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
			m_pImgButton[i]->InvalidateDeviceObjects();
#else 
			for(int j=0;j<BUTTON_STATE_NUMBER;j++)
			{
				m_pImgButton[i][j]->InvalidateDeviceObjects();
			}
#endif																								  

		}

		// 2007-07-04 by bhsohn ���۷����� �߰�
		if(m_pFaqBtn)
		{
			m_pFaqBtn->InvalidateDeviceObjects();		
		}	
		// end 2007-07-04 by bhsohn ���۷����� �߰�
		// 2009. 10. 14 by jskim ������ī ����
		if(m_pTut_SelBtn)
		{
			m_pTut_SelBtn->InvalidateDeviceObjects();
		}
		//end 2009. 10. 14 by jskim ������ī ����
		if(m_pCouponBtn)
		{
			m_pCouponBtn->InvalidateDeviceObjects();
		}
		

		m_pImgMission->InvalidateDeviceObjects();
		m_pImgStack->InvalidateDeviceObjects();

		if(m_pHelpDesk )
		{
			m_pHelpDesk->InvalidateDeviceObjects();
		}
		
		if(m_pInfSkill)
			m_pInfSkill->InvalidateDeviceObjects();
		if(m_pDamageView)
			m_pDamageView->InvalidateDeviceObjects();
		if(m_pOtherCharInfo)
			m_pOtherCharInfo->InvalidateDeviceObjects();
		if(m_pInfGameMainFaq)
			m_pInfGameMainFaq->InvalidateDeviceObjects();
		if(m_pMenuList)
			m_pMenuList->InvalidateDeviceObjects();

		// 2005-03-03 by jschoi
		m_pRequestEnableBack->InvalidateDeviceObjects();
		m_pRequestEnableTriangle->InvalidateDeviceObjects();

		m_pAltiMeterGage->InvalidateDeviceObjects();
		m_pAltiMeterPin->InvalidateDeviceObjects();

		// 2006-04-19 by ispark
		if(m_pCityBoard)
			m_pCityBoard->InvalidateDeviceObjects();

		// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
		m_pMotherShipC->InvalidateDeviceObjects();

		// 2015-05-01 by killburne
		m_pStrategicPointDisplay->InvalidateDeviceObjects();

		// 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
		ResetToolTipEx();
		// End. 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.

		m_bRestored = FALSE;
	}
	return S_OK ;
}

BOOL CINFGameMain::ChangeLeftWindowMode()
{
	FLOG( "CINFGameMain::ChangeLeftWindowMode()" );
	switch(m_nLeftWindowState)
	{
	case LEFT_WEAPON_WINDOW_INIT:// ���� ���� �����ֱ�(�Ϸ�)
		{
			m_pWeaponInfo->m_nLeftWeaponInfoPosX = 0;
			m_nLeftWindowScaleSize = SIZE_WEAPON_Y;
			m_pInfWindow->m_bLeftWindow = FALSE ;
			m_bLeftWindowModeChage = FALSE;
			m_nLeftWindowState = LEFT_WEAPON_WINDOW_END;
			return FALSE;
		}
		break;
	case LEFT_WEAPON_WINDOW_HIDING:// ���� ���� ���̱�
		{
			m_pWeaponInfo->m_nLeftWeaponInfoPosX -= INF_WINDOW_MOVING_VEL*g_pD3dApp->GetElapsedTime();
			if(m_pWeaponInfo->m_nLeftWeaponInfoPosX<-100)
			{
				//������ �����ֱ�
				m_pInfWindow->m_bLeftWindow = TRUE ;
				m_pWeaponInfo->m_nLeftWeaponInfoPosX = -100 ;
				m_nLeftWindowState = LEFT_WINDOW_SHOWING ;
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_OPEN_MENU, g_pShuttleChild->m_vPos, FALSE);
			}
		}
		break;
	case LEFT_WINDOW_HIDING:// ������ â ���̱�
		{
			m_nLeftWindowScaleSize -= INF_WINDOW_MOVING_VEL*g_pD3dApp->GetElapsedTime() ;
			
			if(m_nLeftWindowScaleSize < SIZE_WEAPON_Y)
			{
				if(m_nLeftWindowInfo == LEFT_WINDOW_WEAPON)
				{
					// ���� â �ø���
					m_nLeftWindowState = LEFT_WEAPON_WINDOW_SHOWING;
					m_pInfWindow->m_bLeftWindow = FALSE ;
					m_nLeftWindowScaleSize = SIZE_WEAPON_Y ;
				}
				else
				{
					//������ �����ֱ�
					m_pInfWindow->m_bLeftWindow = TRUE ;
					m_pWeaponInfo->m_nLeftWeaponInfoPosX = -100 ;
					m_nLeftWindowState = LEFT_WINDOW_SHOWING ;
				}
			}
		}
		break;
	case LEFT_WEAPON_WINDOW_SHOWING:// ���� â �ø���
		{
			m_pWeaponInfo->m_nLeftWeaponInfoPosX += INF_WINDOW_MOVING_VEL*g_pD3dApp->GetElapsedTime();
			if(m_pWeaponInfo->m_nLeftWeaponInfoPosX>0)
			{
				// ����â �ø��� �Ϸ�� �̵�
				m_pWeaponInfo->m_nLeftWeaponInfoPosX = 0 ;
				//m_nLeftWindowState = LEFT_WINDOW_INIT ;
				m_nLeftWindowState = LEFT_WEAPON_WINDOW_INIT ;
			}
		}
		break;
	case LEFT_WINDOW_SHOWING:// ������ â �ø���
		{
			m_pInfWindow->m_bLeftWindow = TRUE ;
			m_nLeftWindowScaleSize += INF_WINDOW_MOVING_VEL*g_pD3dApp->GetElapsedTime() ;
			if(m_nLeftWindowScaleSize > SIZE_NORMAL_WINDOW_Y)
			{
				// ������ â �ø��� �Ϸ�� �̵�
				m_nLeftWindowScaleSize = SIZE_NORMAL_WINDOW_Y ;
				m_nLeftWindowState = LEFT_WINDOW_INIT ;
			}
		}
		break;
	case LEFT_WINDOW_INIT:// ������ â �ø���(�Ϸ�)
		{
			m_nLeftWindowScaleSize = SIZE_NORMAL_WINDOW_Y ;
			m_nLeftWindowState = LEFT_WINDOW_END ;
			return FALSE;
		}
		break;
	}
	return TRUE;
}


BOOL CINFGameMain::ChangeRightWindowMode()
{
	FLOG( "CINFGameMain::ChangeRightWindowMode()" );
	switch(m_nRightWindowState)
	{
	case RIGHT_WEAPON_WINDOW_INIT:// ���� ���� �����ֱ�(�Ϸ�)
		{
			m_pWeaponInfo->m_nRightWeaponInfoPosX = g_pD3dApp->GetBackBufferDesc().Width - SIZE_WEAPON_X;
			m_nRightWindowScaleSize = SIZE_WEAPON_Y;
			m_pInfWindow->m_bRightWindow = FALSE ;
			m_bRightWindowModeChage = FALSE;
			m_nRightWindowState = RIGHT_WEAPON_WINDOW_END;
			return FALSE;
		}
		break;
	case RIGHT_WEAPON_WINDOW_HIDING:// ���� ���� ���̱�
		{
			m_pWeaponInfo->m_nRightWeaponInfoPosX += INF_WINDOW_MOVING_VEL*g_pD3dApp->GetElapsedTime();
			if(m_pWeaponInfo->m_nRightWeaponInfoPosX > g_pD3dApp->GetBackBufferDesc().Width)
			{
				//������ �����ֱ�
				m_pInfWindow->m_bRightWindow = TRUE ;
				m_pWeaponInfo->m_nRightWeaponInfoPosX = g_pD3dApp->GetBackBufferDesc().Width ;
				m_nRightWindowState = RIGHT_WINDOW_SHOWING ;
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_OPEN_MENU, g_pShuttleChild->m_vPos, FALSE);
			}
		}
		break;
	case RIGHT_WINDOW_HIDING:// ������ â ���̱�
		{
/*			if(m_pSystem && m_pSystem->m_bRestored)
			{
				m_pSystem->InvalidateDeviceObjects();
			}
			if(m_pCharacterInfo && m_pCharacterInfo->m_bRestored)
			{
				m_pCharacterInfo->InvalidateDeviceObjects();
			}
*/			m_nRightWindowScaleSize -= INF_WINDOW_MOVING_VEL*g_pD3dApp->GetElapsedTime() ;
			if(m_nRightWindowScaleSize < SIZE_WEAPON_Y)
			{
				if(m_nRightWindowInfo == LEFT_WINDOW_WEAPON)
				{
					// ���� â �ø���
					m_nRightWindowState = RIGHT_WEAPON_WINDOW_SHOWING;
					m_pInfWindow->m_bRightWindow = FALSE ;
					m_nRightWindowScaleSize = SIZE_WEAPON_Y ;
				}
				else
				{
					//������ �����ֱ�
					m_pInfWindow->m_bRightWindow = TRUE ;
					m_pWeaponInfo->m_nRightWeaponInfoPosX = g_pD3dApp->GetBackBufferDesc().Width ;
					m_nRightWindowState = RIGHT_WINDOW_SHOWING ;
				}
			}
		}
		break;
	case RIGHT_WEAPON_WINDOW_SHOWING:// ���� â �ø���
		{
			m_pWeaponInfo->m_nRightWeaponInfoPosX -= INF_WINDOW_MOVING_VEL*g_pD3dApp->GetElapsedTime();
			if(m_pWeaponInfo->m_nRightWeaponInfoPosX < g_pD3dApp->GetBackBufferDesc().Width - SIZE_ROLL_X)
			{
				// ����â �ø��� �Ϸ�� �̵�
				m_pWeaponInfo->m_nRightWeaponInfoPosX = g_pD3dApp->GetBackBufferDesc().Width - SIZE_ROLL_X ;
				//m_nRightWindowState = RIGHT_WINDOW_INIT ;
				m_nRightWindowState = RIGHT_WEAPON_WINDOW_INIT ;
			}
		}
		break;
	case RIGHT_WINDOW_SHOWING:// ������ â �ø���
		{
			m_pInfWindow->m_bRightWindow = TRUE ;
			m_nRightWindowScaleSize += INF_WINDOW_MOVING_VEL*g_pD3dApp->GetElapsedTime() ;
			if(m_nRightWindowScaleSize > SIZE_NORMAL_WINDOW_Y)
			{
				// ������ â �ø��� �Ϸ�� �̵�
				m_nRightWindowScaleSize = SIZE_NORMAL_WINDOW_Y ;
				m_nRightWindowState = RIGHT_WINDOW_INIT ;
			}
		}
		break;
	case RIGHT_WINDOW_INIT:// ������ â �ø���(�Ϸ�)
		{
			m_nRightWindowScaleSize = SIZE_NORMAL_WINDOW_Y ;
			m_nRightWindowState = RIGHT_WINDOW_END ;
			return FALSE;
		}
		break;
	}
	return TRUE;
}

void CINFGameMain::Tick()
{
	FLOG( "CINFGameMain::Tick()" );

         // 2005-08-02 ispark
	if(m_pHelpDesk
		&& m_pHelpDesk->m_bRenderMissionItemInfo)
	{
		m_pHelpDesk->m_fHelpTextMission -= g_pD3dApp->GetElapsedTime();
		if(m_pHelpDesk->m_fHelpTextMission<0)
		{
			m_pHelpDesk->m_fHelpTextMission = 5.0f;
			m_pHelpDesk->m_bRenderMissionItemInfo = FALSE;
		}
	}

	TickDrawWindowInfo();

	// ����, ���� ����

#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	if(m_pMp3Player && m_bMp3PlayFlag == TRUE)
		m_pMp3Player->Tick();	
#endif
	if(m_pInfWindow)
		m_pInfWindow->Tick();
	if(m_pUnitInfoBar)
	{
		m_pUnitInfoBar->Tick();
	}
	if(m_pChat)
		m_pChat->Tick();
	if(m_pQuickSlot)
	{
		m_pQuickSlot->Tick();
	}
//	if(m_pNotice)
//		m_pNotice->Tick();
	if(m_pUnitState)
	{
		m_pUnitState->Tick();
	}
	if(m_pAttackDirection)
	{
		m_pAttackDirection->Tick();
	}
	// 2007-11-22 by dgwoo
	if(m_pChangeCharactor)
	{
		m_pChangeCharactor->Tick();
	}
	if(m_pCouponWindow)
		m_pCouponWindow->Tick();
	if(m_bHelpDeskFlag && g_pSOptionCharacter->sHelpDesk)	
		m_pHelpDesk->Tick();
	if(m_pGameCountDown)
		m_pGameCountDown->Tick();	
	if(m_pOtherCharInfo && m_pOtherCharInfo->m_bRenderInfo)
		m_pOtherCharInfo->Tick();
	if(m_pInfGameMainFaq && m_bFAQProsFlag)
		m_pInfGameMainFaq->Tick();
	//if(m_pCommunityVOIP && m_bVOIPFlag)
	//	m_pCommunityVOIP->Tick();
	if(m_pMenuList)
		m_pMenuList->Tick();


#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	for(int i=0; i< GAMEMAIN_BUTTON_NUMBER; i++)
	{
		if(m_pImgButton[i])
			m_pImgButton[i]->Tick();
	}

	if(m_pFaqBtn)
		m_pFaqBtn->Tick();
#endif
		
	switch(m_nLeftWindowInfo)
	{
	case LEFT_WINDOW_WEAPON:
		{
			m_pInven->Tick() ;
		}
		break;
	case LEFT_WINDOW_INVEN:
		{
			m_pInven->Tick() ;
		}
		break;
	case LEFT_WINDOW_TRANS:
		{
			m_pTrade->Tick() ;
			m_pInven->Tick() ;
		}
		break;
	case LEFT_WINDOW_PARTY:
		{
			m_pCommunity->Tick();
		}
		break;
	case LEFT_WINDOW_SHOP:
		{
//			m_pShop->Tick();
			m_pInven->Tick() ;
		}
		break;
	}
	// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
	if(m_pCommunity)
	{
		m_pCommunity->Tick();
	}

	if (m_pQOLInfo)
	{
		m_pQOLInfo->Tick();
	}

// 2007-10-22 by dgwoo ����� �ð��� �Ȱ��� ���׹߻� ���� �������� ��ġ ����.
//	// �ý��� Ÿ��
//	m_pSystem->Tick() ;
	
	// 2008-09-22 by bhsohn EP3 ĳ���� â
//	switch(m_nRightWindowInfo)
//	{
//	case RIGHT_WINDOW_WEAPON:
//		{
//			m_pWeaponInfo->Tick();
//		}
//		break;
//	case RIGHT_WINDOW_INFO:
//		{
//			m_pCharacterInfo->Tick() ;
//		}
//		break;
//	case RIGHT_WINDOW_OPTION:
//		{			
//		}
//		break;
//	}	
	if(m_pCharacterInfo->IsShowWnd())
	{
		m_pCharacterInfo->Tick() ;
	}
	// end 2008-09-22 by bhsohn EP3 ĳ���� â

	// �̼��� ��� ������ �����̱�
	m_fTimeElapseButtonCheck -= g_pD3dApp->GetElapsedTime();
	if(m_fTimeElapseButtonCheck < 0)
	{
		m_fTimeElapseButtonCheck = GAME_BUTTON_CHECK_ON;
	}

	if(m_bKnowON[LOW_LEVEL_STAT_HELP] || m_bKnowON[LOW_LEVEL_MISSION_HELP])
	{
		if(m_fTimeElapseButtonCheck == GAME_BUTTON_CHECK_ON)
		{
			m_bKnowTwinkle = !m_bKnowTwinkle;			
		}
	}

	// 2006-04-11 by ispark
	if(m_pCityBoard)
		m_pCityBoard->Tick(g_pD3dApp->GetElapsedTime());

	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	TickSpeakerMsg();

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	TickSecuritySystem();

	// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	m_pMotherShipC->Tick();

	// 2015-05-01 by killburne
	m_pStrategicPointDisplay->Tick();


	// 2009. 01. 23 by ckPark �������̽� ���� �� ��Ż/��ų ������� üũ

// 	// 2008. 12. 16 by ckPark ������ ��� ����
// 	TickItemDelay();	
// 	// end 2008. 12. 16 by ckPark ������ ��� ����
// 
// 
// 	// 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����
// 	TickSkillDealy();
// 	// end 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����

	// end 2009. 01. 23 by ckPark �������̽� ���� �� ��Ż/��ų ������� üũ

// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
#if S_BONUSEXPSYSTEM_RENEWAL || S_BONUS_KILL_SYSTEM_RENEWAL
	m_nAddPosY = 0;
	if(m_pUnitInfoBar->GetRestCount() > 0)// �޽� ����ġ ī��Ʈ�� �ִٸ�, Ʃ�丮�� ��ư�� ������
	{
		m_nAddPosY += TUTORIAL_BUTTON_Y_ADDCOUNT;
		m_pTut_SelBtn->SetBtnPosition(TUTORIAL_BUTTON_X, TUTORIAL_BUTTON_Y+m_nAddPosY);
	}
	if(m_pUnitInfoBar->GetKillCount() > 0)// ų ī��Ʈ�� �ִٸ�, Ʃ�丮�� ��ư�� ������
	{
		m_nAddPosY += TUTORIAL_BUTTON_Y_ADDCOUNT;
		m_pTut_SelBtn->SetBtnPosition(TUTORIAL_BUTTON_X, TUTORIAL_BUTTON_Y+m_nAddPosY);
	}
#endif // S_BONUSEXPSYSTEM_RENEWAL
// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

	UpdateServerTimeString();	// 2012-12-10 by jhjang �ð� ǥ�� ����
#ifdef SC_COLLECTION_ARMOR_JHSEOL_BCKIM
	TickArmorTimeCheck();		// 2013-05-09 by ssjung ���� ���� �Ⱓ���� ��� �޽��� ����
#endif
}

void CINFGameMain::RenderLeftRightWindow()
{
	switch(m_nLeftWindowInfo)
	{
	case LEFT_WINDOW_WEAPON:
		{
// 2008-05-29 by dgwoo ���� �������̽� ���� ��ȹ.
//			if(m_pWeaponInfo )
//				m_pWeaponInfo->RenderLeftWeapon() ;
		}
		break;
	case LEFT_WINDOW_INVEN:
		{
			if(m_pInven && !m_pInven->m_bRestored)
			{
				m_pInven->RestoreDeviceObjects();
			}
			if(!m_bLeftWindowModeChage && m_pInven)
			{
				m_pInven->Render() ;
			}

		}
		break;
	case LEFT_WINDOW_TRANS:
		{
			if(m_pTrade && !m_pTrade->m_bRestored)
			{
				m_pTrade->RestoreDeviceObjects();
			}
			if(m_pInven && !m_pInven->m_bRestored)
			{
				m_pInven->RestoreDeviceObjects();
			}

			if(!m_bLeftWindowModeChage && m_pInven && m_pTrade)
			{
				m_pTrade->Render() ;
				m_pInven->Render() ;
			}
		}
		break;
	case LEFT_WINDOW_PARTY:
		{
//			if(m_pParty && !m_pParty->m_bRestored)
//			{
//				m_pParty->RestoreDeviceObjects();
//			}
/*			if(m_pCommunity && !m_pCommunity->m_bRestored)
			{
				m_pCommunity->RestoreDeviceObjects();
			}
*/			if(!m_bLeftWindowModeChage && m_pCommunity)
			{
//				m_pParty->Render();
				m_pCommunity->Render();
			}
		}
		break;
	case LEFT_WINDOW_SHOP:
		{
//			if(m_pShop && !m_pShop->m_bRestored)
//			{
//				m_pShop->RestoreDeviceObjects();
//			}
//			if(m_pInven && !m_pInven->m_bRestored)
//			{
//				m_pInven->RestoreDeviceObjects();
//			}
//			if(!m_bLeftWindowModeChage && m_pShop)
//			{
//				m_pShop->Render();
//				m_pInven->Render() ;
//			}
		}
		break;
	}

	switch(m_nRightWindowInfo)
	{
	case RIGHT_WINDOW_WEAPON:
		{
// 2008-05-29 by dgwoo ���� �������̽� ���� ��ȹ.	
//			if(m_pWeaponInfo )
//				m_pWeaponInfo->RenderRightWeapon() ;
		}
		break;
	case RIGHT_WINDOW_INFO:
		{
			// 2008-09-22 by bhsohn EP3 ĳ���� â
//			if(m_pCharacterInfo && !m_pCharacterInfo->m_bRestored)
//			{
//				m_pCharacterInfo->RestoreDeviceObjects();
//			}
//
//			if(!m_bRightWindowModeChage && m_pCharacterInfo)
//			{
//				m_pCharacterInfo->Render() ;
//			}

		}
		break;
	case RIGHT_WINDOW_OPTION:
		{
			if(m_pSystem && !m_pSystem->m_bRestored)
			{
				m_pSystem->RestoreDeviceObjects();
			}

			if(!m_bRightWindowModeChage && m_pSystem)
			{
				m_pSystem->Render() ;
			}
		}
		break;
	}

	// 2008-03-19 by bhsohn Ep3�ɼ�â
	if(m_pSystem && m_pSystem->IsOptionShow())
	{
		if(!m_pSystem->m_bRestored)
		{
			m_pSystem->RestoreDeviceObjects();
		}
		m_pSystem->Render();
	}
	// end 2008-03-19 by bhsohn Ep3�ɼ�â


}

void CINFGameMain::Render()
{
	FLOG( "CINFGameMain::Render()" );

	if(g_pD3dApp->m_dwGameState == _GAME || g_pD3dApp->m_dwGameState == _SHOP )
	{
		if(m_pChat)	m_pChat->Render();		

		if(g_pShuttleChild->m_pClientParty->GetPartyInfo().PartyID != 0) 
			m_pCommunity->GetParty()->RenderPartyFrame();
		
		if(g_pD3dApp->m_dwGameState != _SHOP)
		{
		}
		
		if(m_pMission && m_pMission->m_bShow)	m_pMission->Render();
		if(m_pUnitState)
		{
			if(g_pD3dApp->m_pShuttleChild->m_bMouseLock)
			{
//				m_pUnitState->SetState( INF_US_LOCK_MASK );
			}
			else
			{
				m_pUnitState->OffState( INF_US_LOCK_MASK );
			}
		}

		if(m_pAttackDirection)	m_pAttackDirection->Render();
		if(m_pUnitState)		m_pUnitState->Render();
	}

	if(m_pOutPost)
	{
		m_pOutPost->Render();
	}
	// 2013-04-05 by bhsohn �ɸ��� ���� â ������ ���� ���� ó��
// 	if(m_pChangeCharactor)
// 	{
// 		m_pChangeCharactor->Render();
// 	}
	// END 2013-04-05 by bhsohn �ɸ��� ���� â ������ ���� ���� ó��
	if(m_pCouponWindow)
	{
		m_pCouponWindow->Render();
	}

	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	// 2008-04-23 by bhsohn ����Ŀ ������ ������ ���� ����
	//RenderSpeakerMsg();

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	RenderSecuritySystem();


	if(m_pGameCountDown)
	{
		m_pGameCountDown->Render();
	}
	// ���� ���̱�
	if(m_bHelpDeskFlag && g_pSOptionCharacter->sHelpDesk)
	{			
		m_pHelpDesk->Render();		
	}

	// ����Ʈ ������ ���� ǥ��
	if(m_pHelpDesk && m_pHelpDesk->m_bRenderMissionItemInfo)
	{
		m_pHelpDesk->DrawHelpWindow((g_pD3dApp->GetBackBufferDesc().Width /2)-((strlen(m_pHelpDesk->m_strMissionItem)*7)/2)+30, 120, 
			m_pHelpDesk->m_nHelpDeskWidth+(HELPDESK_WINDOW_TEXT_VIEW_GAP*2),
			m_pHelpDesk->m_nHelpDeskHeight+HELPDESK_WINDOW_TEXT_VIEW_GAP);
	}

	// ���� ������
	// 2006-01-05 by ispark, �������� ��Ÿ ���� �������� ���Ѵ�
	if(g_pD3dApp->m_dwGameState != _SHOP)
	{
	    ProcessAltiMeter(g_pGround->m_projectInfo.fWaterHeight, g_pScene->m_nMaxAtitudeHeight, g_pShuttleChild->m_vPos.y );
	}
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++)
	{
		m_pImgButton[i][m_nButtonState[i]]->Move(GAMEMAIN_BUTTON_START_X+GAMEMAIN_BUTTON_INTERVAL*i, GAMEMAIN_BUTTON_START_Y);
		m_pImgButton[i][m_nButtonState[i]]->Render();
	}
#endif
	// 2007-07-19 by dgwoo ������ ��ġ���� ����.
	RenderOnInfo();
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����;
	m_pImgButtonBK->Move(GAMEMAIN_BK_START_X, GAMEMAIN_BK_START_Y);
	m_pImgButtonBK->Render();

	for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++)
	{
		m_pImgButton[i]->Render();
	}
#endif
	// 2007-07-04 by bhsohn ���۷����� �߰�

	m_pFaqBtn->Render();
	m_pCouponBtn->Render();
	// 2009. 10. 14 by jskim ������ī ����
	const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
	if (myShuttleInfo.InfluenceType == 1 &&
		IS_CITY_MAP_INDEX(myShuttleInfo.MapChannelIndex.MapIndex) &&
		g_pShuttleChild->m_dwState == _LANDED) 
	{

		if (g_pD3dApp->m_dwGameState != _SHOP)
			
			m_pTut_SelBtn->Render();	
	}	

	if (m_pOtherCharInfo && m_pOtherCharInfo->m_bRenderInfo)

	    m_pOtherCharInfo->Render();
	
	// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	if (m_pMotherShipC) m_pMotherShipC->Render();
	
	if (m_pStrategicPointDisplay) m_pStrategicPointDisplay->Render();
	// end 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�

	// 2008-04-23 by bhsohn ����Ŀ ������ ������ ���� ����
	// ����Ŀ �������� ���� �������� �������ؾ��� ���� ���� ���δ�.
	RenderSpeakerMsg();

	// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
	RenderSysMsgWnd();	// ���� �ð�����
}

void CINFGameMain::RenderHelp()
{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����;
	if(m_pHelp[0])
	{
		m_pHelp[0]->Move(g_pD3dApp->GetBackBufferDesc().Width/2 - m_pHelp[0]->GetImgSize().x/2,g_pD3dApp->GetBackBufferDesc().Height/2 - m_pHelp[0]->GetImgSize().y/2);
		m_pHelp[0]->Render();
	}
#else
	if(m_pHelp[0])
	{
		m_pHelp[0]->Move(g_pD3dApp->GetBackBufferDesc().Width/2-359,g_pD3dApp->GetBackBufferDesc().Height/2-150);
		m_pHelp[0]->Render();
	}
	if(m_pHelp[1])
	{
		m_pHelp[1]->Move(g_pD3dApp->GetBackBufferDesc().Width/2,g_pD3dApp->GetBackBufferDesc().Height/2-150);
		m_pHelp[1]->Render();
	}
#endif
}
int CINFGameMain::WndProcLeftRightWindow(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	CheckMouseReverse(&pt);
	
		if(!m_bLeftWindowModeChage)
		{
			switch(m_nLeftWindowInfo)
			{
		case LEFT_WINDOW_INVEN:
			{
				if(m_pInven){					
						if(m_pInven->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
							return INF_MSGPROC_BREAK;
					}
				}
				break;
			case LEFT_WINDOW_TRANS:
				{
				if(m_pTrade){
						if(m_pTrade->WndProc(uMsg, wParam, lParam) ==  INF_MSGPROC_BREAK)
							return INF_MSGPROC_BREAK;
					}
				if(m_pInven){
						if(m_pInven->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
							return INF_MSGPROC_BREAK;
					}
				}
				break;
			case LEFT_WINDOW_PARTY:
				{
				if(m_pCommunity){
						if(m_pCommunity->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
							return INF_MSGPROC_BREAK;
					}
				}
				break;
			case LEFT_WINDOW_SHOP:
				{
				}
				break;
			}
		}
		if(!m_bRightWindowModeChage)
		{
			switch(m_nRightWindowInfo)
			{
			case RIGHT_WINDOW_INFO:
				{
					// 2008-09-22 by bhsohn EP3 ĳ���� â
//					if(m_pCharacterInfo)
//					{
//						if(m_pCharacterInfo->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
//							return INF_MSGPROC_BREAK;
//					}
					// end 2008-09-22 by bhsohn EP3 ĳ���� â
				}
				break;
			case RIGHT_WINDOW_OPTION:
				{
				if(m_pSystem){					
						if(m_pSystem->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
							return INF_MSGPROC_BREAK;
					}
				}
				break;
			}
		}

		// 2008-03-19 by bhsohn Ep3�ɼ�â
		if(m_pSystem)
		{					
			if(m_pSystem->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}
		// end 2008-03-19 by bhsohn Ep3�ɼ�â

	return INF_MSGPROC_NORMAL;
}

int CINFGameMain::WndProcKeyDown(WPARAM wParam, LPARAM lParam)
{
	// 2005-12-09 by ispark
	// Ű ��� ���� üũ 
	if(CheckKeyUseState(wParam, lParam, TRUE, FALSE) ||
		g_pD3dApp->m_bChatMode == TRUE ||
		g_pD3dApp->m_dwGameState == _SHOP || 
		m_nLeftWindowInfo == LEFT_WINDOW_TRANS ||
		g_pGameMain->m_pTrade->m_bTrading)
		return INF_MSGPROC_BREAK;

	// 2008-12-04 by bhsohn �������� �Ѿ� ������ ���� ó��
	if(g_pShuttleChild && g_pShuttleChild->IsWeapongShotting())
	{
		if(VK_F2 != wParam)
		{
			// �Ѿ� ��鼭 ��� ���� ������ �����ϴ�.
			return INF_MSGPROC_NORMAL;
		}
		
	}
	// end 2008-12-04 by bhsohn �������� �Ѿ� ������ ���� ó��
	// 2010. 05. 27 by jskim �ó׸� ���� ī�޶� ����
// 	if(g_pShuttleChild->m_ShowInterface)
// 	{
// 		switch(wParam)
// 		{
// 		case VK_ESCAPE:
// 			{
// 				g_pShuttleChild->DeletePattern();	
// 				break;
// 			}
// 		}			
// 		return INF_MSGPROC_BREAK;
// 	}
	//end 2010. 05. 27 by jskim �ó׸� ���� ī�޶� ����
	// ��� �����ϸ� � �������� �ؿ��� ����
	switch(wParam)
	{
	case VK_F1:
		{
//			if(((CInterface*)m_pParent)->m_bShowInterface == FALSE)
//				break;
			
			// 2005-04-07 by jschoi - Tutorial
			// 2005-08-09 by ispark - ����
//			if(g_pTutorial->IsTutorialMode() == TRUE)
//				break;

			ToggleHelpImage();
		}
		break;
	case VK_F2:
		{
			// 2005-04-07 by jschoi - Tutorial
			// 2005-08-09 by ispark - ����
//			if(g_pTutorial->IsTutorialMode() == TRUE)
//				break;

			// 2004-11-26 by jschoi - _GAME ���°� �ƴϰų� �����߿��� ������ ������ �� ����.
			if( g_pD3dApp->m_dwGameState != _GAME ||
				g_pShuttleChild->m_nCurrentPatternNumber == PATTERN_UNIT_WARP_OUT ||
				g_pShuttleChild->m_nCurrentPatternNumber == PATTERN_UNIT_WARP_IN 
				|| IS_CITY_MAP_INDEX(g_pD3dApp->GetMyShuttleMapChannelIndex().MapIndex)) // 2007-06-26 by bhsohn �������� ��� ���� �Ǵ� ���� ����
			{
				DBGOUT("Current Game State (%d) , and PatternType is (%d), So Can't join FormationFlight.\n",g_pD3dApp->m_dwGameState,g_pShuttleChild->m_nCurrentPatternNumber);
				break;
			}
			if( g_pShuttleChild->m_pClientParty->GetPartyInfo().bFormationFlyingType && 
				!g_pShuttleChild->m_pClientParty->GetPartyInfo().bFormationFlyingPositionType && 
				g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMEMBER &&
				g_pShuttleChild->m_dwState == _NORMAL &&
				g_pShuttleChild->m_bAttackMode != _SIEGE &&
				(FALSE == IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind) || g_pShuttleChild->m_bIsAir))
			{
				vector<PARTYENEMYINFO*>::iterator itParty = g_pShuttleChild->m_pClientParty->m_vecPartyEnemyInfo.begin();
				while(itParty != g_pShuttleChild->m_pClientParty->m_vecPartyEnemyInfo.end())
				{
					if(	(*itParty)->m_pEnemyData &&
						(*itParty)->m_bPartyType == _PARTYMASTER)
					{

//				CMapEnemyIterator itEnemy = g_pD3dApp->m_pScene->m_mapEnemyList.begin();
//				while(itEnemy != g_pD3dApp->m_pScene->m_mapEnemyList.end())
//				{
//					if(itEnemy->second->m_infoParty.bPartyType == _PARTYMASTER)
//					{
						if( D3DXVec3Length(&((*itParty)->m_pEnemyData->m_vPos - g_pShuttleChild->m_vPos)) < 300.0f &&
							(*itParty)->m_pEnemyData->m_dwState == _NORMAL)
						{
//							MSG_IC_PARTY_GET_FLIGHT_POSITION sMsg;
//							memset(&sMsg,0x00,sizeof(sMsg));
//							char buffer[SIZE_MAX_PACKET];
//							int nType = T_IC_PARTY_GET_FLIGHT_POSITION;
//							sMsg.CharacterUniqueNumber = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
//							memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//							memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//							g_pD3dApp->m_pIMSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
							g_pShuttleChild->m_pClientParty->ISendPartyGetFlightPosition();
							
//							g_pD3dApp->m_pShuttleChild->m_infoParty.bFormationFlyingPositionType = 5;
//							g_pD3dApp->m_pShuttleChild->m_bFormationFlight = TRUE;
							// 2005-10-24 by ispark
							// ������ ��û�� �� ��� ���� Ǭ��.
							g_pShuttleChild->m_bUnitStop = FALSE;
							g_pShuttleChild->m_nBooster = BOOSTER_TYPE_MIN;
							g_pShuttleChild->m_bPenaltyUnitStop = FALSE;
							g_pShuttleChild->m_bMouseLock = FALSE;
							g_pShuttleChild->m_bMouseMoveLock = FALSE;
							g_pD3dApp->m_bFixUnitDirMode = FALSE;
							g_pInterface->m_pGameMain->InitShowWindow();
							// 2010. 03. 30 by jskim ���� ���� �ٵ������ ���� ����	
							g_pShuttleChild->SendFieldSocketChangeBodyCondition( g_pShuttleChild->m_myShuttleInfo.ClientIndex, BODYCON_SET_OR_CLEAR_MASK );
							//end 2010. 03. 30 by jskim ���� ���� �ٵ������ ���� ����
							g_pShuttleChild->m_ptDirOld.x = 0;
							g_pShuttleChild->m_ptDirOld.y = 0;
						}
						else if((*itParty)->m_pEnemyData->m_dwState != _NORMAL)
						{
							char buf[256];
							wsprintf(buf,STRMSG_C_PARTY_0042);//"������� �������� �� �� ���� �����Դϴ�."
							g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_SYSTEM);
						}
						else
						{
							char buf[256];
							wsprintf(buf,STRMSG_C_PARTY_0043);//"��������κ��� �Ÿ��� �ʹ� �ָ� ������ �ֽ��ϴ�."
							g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_SYSTEM);
						}
						break;
					}
//					itEnemy++;
					itParty++;
				}
			}
			else if(!g_pShuttleChild->m_pClientParty->GetPartyInfo().bFormationFlyingType)
			{//
				char buf[256];
				wsprintf(buf,STRMSG_C_PARTY_0044);//"��� ���� ���� ������ �߸��Ǿ����ϴ�."
				g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_SYSTEM);
			}
			else if(g_pShuttleChild->m_pClientParty->GetPartyInfo().bFormationFlyingPositionType)
			{
				char buf[256];
				wsprintf(buf,STRMSG_C_PARTY_0045);//"��� ���� �������� �߸��Ǿ����ϴ�."
				g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_SYSTEM);
			}
			else if(g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType != _PARTYMEMBER)
			{
				char buf[256];
				wsprintf(buf,STRMSG_C_PARTY_0046);//"���� ������ �ƴմϴ�. Ȯ���� �ֽñ� �ٶ��ϴ�."
				g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_SYSTEM);
			}
			else
			{
				char buf[256];
				wsprintf(buf,STRMSG_C_PARTY_0047);//"��� ������ �� �� ���� �����Դϴ�."
				g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_SYSTEM);
			}
		}
		break;
	case VK_ESCAPE :
		{
			// 2005-04-07 by jschoi - Tutorial
			// 2005-08-04 by ispark - �������϶� �϶� Ű�� ���´�.
			// 2005-08-08 by ispark - �����ÿ��� ���
			// 2005-08-09 by ispark - ����
//			if(g_pTutorial->IsTutorialMode() == TRUE || 
//				(g_pD3dApp->m_bCharacter == FALSE && 
//				 g_pShuttleChild->m_bUnitStop == FALSE))
//				return INF_MSGPROC_BREAK;
			// 2007-04-02 by dgwoo ������ ����ϰ��� Ʃ�丮�� ��忡���� escŰ�� �۵��� ���´�.
			// 
			if(g_pShuttleChild->IsObserverMode() || g_pTutorial->IsTutorialMode())
				break;
			SetItemInfo(0,0,0,0);
			if( g_pD3dApp->m_dwGameState == _CITY && 
				g_pInterface->m_pCityBase->GetCurrentBuildingNPC() )
			{
				break;
			}
			
			// 2007-06-12 by bhsohn �̼� �������̽� ������
//			if(TRUE == m_pMissionInfo->GetMissionWindowState())
//			{
//				m_pMissionInfo->MissionProcFlag(FALSE);
//				break;
//			}
			if(IsShowTreeWnd())
			{
				ShowMissionTreeWnd(FALSE, TRUE);
				break;
			}				

			if(IsShowing())
			{
				if(m_pTrade->m_bTrading && m_nLeftWindowInfo == LEFT_WINDOW_TRANS)
				{
					m_pInfWindow->AddMsgBox(STRMSG_C_TRADE_0001, _Q_TRADE_CANCEL);//"�ŷ��� ����Ͻðڽ��ϱ�?"
				}
				else if(g_pD3dApp->m_dwGameState == _SHOP)
				{
					//LeftWindowShow(FALSE,LEFT_WINDOW_SHOP);
//					m_pShop->OnCancelButtonClicked();
				}
				else
				{
					LeftWindowShow(FALSE,m_nLeftWindowInfo);
				}
				RightWindowShow(FALSE,m_nRightWindowInfo);
				if(m_bShowHelp)
				{
					ToggleHelpImage();
				}
				// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
				if(m_pCharacterInfo && m_pCharacterInfo->IsShowWnd())
				{
					m_pCharacterInfo->ShowCharacterInfoWnd(FALSE, NULL);	
					//g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MENU, g_pShuttleChild->m_vPos, FALSE);	// 2013-01-03 by mspark, ���� �޴��� Ŭ���Ͽ��� ��� ���尡 ���ļ� �鸮�� ���� ���� - �ּ� ��
				}
				// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��
			}
			else if(m_bQuestView && g_pSOptionCharacter->sHelpDesk == TRUE )
			{
				m_bQuestView = FALSE;
			}
			else if(m_pOtherCharInfo->m_bRenderInfo)
			{
				m_pOtherCharInfo->m_bRenderInfo = FALSE;
			}
			else if(g_pGameMain->m_pChat->m_bMenuListUse == TRUE)
			{
				g_pGameMain->m_pChat->m_bMenuListUse = FALSE;
			}
			else if(m_bMenuListFlag == TRUE)
			{
				m_bMenuListFlag = FALSE;
			}
			// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
			else if(m_pINFSecuMain && m_pINFSecuMain->IsShowSecurityWnd())
			{
				m_pINFSecuMain->AllHideSecurityWnd();
			}
			// end 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
			// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
			else if(m_pCommunity && m_pCommunity->IsShowCommunityWindow())
			{
				// Ŀ�´�Ƽ â �ݱ�
				OnClickCommunity();				
			}
			// end 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
			// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
			else if(m_pInven && m_pInven->IsShowInven())
			{
				// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ���� 
				// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
				//if(g_INFCnt==0)
				if(g_pD3dApp->GetINFCnt() == 0)
				{
					g_pGameMain->m_bChangeMousePoint = FALSE;
				}				
				// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
				// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ���� 
				m_pInven->ShowInven(NULL, NULL, TRUE);	
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MENU, g_pShuttleChild->m_vPos, FALSE);
			}
			// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��
			// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
			else if(m_pCharacterInfo && m_pCharacterInfo->IsShowWnd())
			{
				m_pCharacterInfo->ShowCharacterInfoWnd(FALSE, NULL);	
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MENU, g_pShuttleChild->m_vPos, FALSE);
			}
			// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��
			else if(g_pInterface->m_pCityBase->GetCurrentBuildingNPC() == NULL)
			{
				// 2008-03-19 by bhsohn Ep3�ɼ�â
				//RightWindowShow(TRUE, RIGHT_WINDOW_OPTION);
				PopupSystemOptinWnd();
			}
			
			// 2009-02-03 by bhsohn ���� ������ �� ����
			//m_pItemInfo->ShowItemInfo(FALSE);
			ShowItemInfo(FALSE);
			// end 2009-02-03 by bhsohn ���� ������ �� ����

//			g_pD3dApp->m_pShuttleChild->m_bMouseLock = FALSE;	// 2005-10-07 by ispark ���� ESCŰ�� ���� ȸ�� �ȵŴ� ���� 
			m_pUnitState->OffState( INF_US_LOCK_MASK );
		}
		break;
	case VK_TAB :
		{
//					LeftWindowShow(TRUE, LEFT_WINDOW_INVEN);
		}
		break;
	case VK_F3:
		{
			// 2005-04-07 by jschoi - Tutorial
			// 2005-08-09 by ispark - ����
//			if(g_pTutorial->IsTutorialMode() == TRUE)
//				break;

			if(g_pD3dApp->m_dwGameState == _GAME)
			{
				// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
				// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
				//g_INFCnt++;
				g_pD3dApp->AddINFCnt();
				// end 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
				g_pGameMain->m_bChangeMousePoint = TRUE;								
				// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
				m_pInfWindow->AddMsgBox( STRMSG_C_PK_0004, _Q_BATTLE_NAME );//"1:1����� �� ������ �Է��Ͻÿ�."
				
			}
		}
		break;
	case VK_F5:
		{
			// 2005-04-07 by jschoi - Tutorial
			// 2005-08-04 by ispark - �������϶� �϶� Ű�� ���´�.
			// 2005-08-08 by ispark - �����ÿ��� ���
			// 2005-08-09 by ispark - ����
//			if(g_pTutorial->IsTutorialMode() == TRUE || 
//				(g_pD3dApp->m_bCharacter == FALSE && 
//				 g_pShuttleChild->m_bUnitStop == FALSE))
//				break;
			// 2007-03-27 by bhsohn ������ ���� �������̽� ����


			if(g_pShuttleChild->IsObserverMode())
			{
				break;
			}
			// end 2007-03-27 by bhsohn ������ ���� �������̽� ����

			if(((CInterface*)m_pParent)->m_bShowInterface == FALSE)
				break;
			if(m_nLeftWindowInfo == LEFT_WINDOW_INVEN)
			{
				SetItemInfo(0,0,0,0);
			}
			LeftWindowShow(TRUE, LEFT_WINDOW_INVEN);
		}
		break;
	case VK_F6:
		{
			// 2005-04-07 by jschoi - Tutorial
			// 2005-08-04 by ispark
			// 2005-08-08 by ispark - �����ÿ��� ���
			// 2005-08-09 by ispark - ����
//			if(g_pTutorial->IsTutorialMode() == TRUE || 
//				(g_pD3dApp->m_bCharacter == FALSE && 
//				 g_pShuttleChild->m_bUnitStop == FALSE))
//				break;
			// 2007-03-27 by bhsohn ������ ���� �������̽� ����
			if(g_pShuttleChild->IsObserverMode())
			{
				break;
			}
			// end 2007-03-27 by bhsohn ������ ���� �������̽� ����

			if(((CInterface*)m_pParent)->m_bShowInterface == FALSE)
				break;
			if(m_nLeftWindowInfo == RIGHT_WINDOW_INFO)
			{
				SetItemInfo(0,0,0,0);
			}
			RightWindowShow(TRUE, RIGHT_WINDOW_INFO);
		}
		break;
	case VK_F7:
		{
			// 2005-04-07 by jschoi - Tutorial
			// 2005-08-04 by ispark - �������϶� �϶� Ű�� ���´�.
			// 2005-08-08 by ispark - �����ÿ��� ���
			// 2005-08-09 by ispark - ����
//			if(g_pTutorial->IsTutorialMode() == TRUE || 
//				(g_pD3dApp->m_bCharacter == FALSE && 
//				 g_pShuttleChild->m_bUnitStop == FALSE))
//				break;
			// 2007-03-27 by bhsohn ������ ���� �������̽� ����
			if(g_pShuttleChild->IsObserverMode())
			{
				break;
			}
			// end 2007-03-27 by bhsohn ������ ���� �������̽� ����

			if(((CInterface*)m_pParent)->m_bShowInterface == FALSE)
				break;
			// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
			//LeftWindowShow(TRUE, LEFT_WINDOW_PARTY);
			OnClickCommunity();
			
		}
		break;
	case VK_F8:
		{
			// 2005-04-07 by jschoi - Tutorial
			// 2005-08-04 by ispark - �������϶� �϶� Ű�� ���´�.
			// 2005-08-08 by ispark - �����ÿ��� ���
			// 2005-08-09 by ispark - ����
//			if(g_pTutorial->IsTutorialMode() == TRUE || 
//				(g_pD3dApp->m_bCharacter == FALSE && 
//				 g_pShuttleChild->m_bUnitStop == FALSE))
//				break;
			// 2005-11-02 by ispark
			// ��ڴ� �ŷ��� �Ұ����ϴ�.
			if(g_pShuttleChild->m_dwPartType == _ADMIN)
			{
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_051102_0001, COLOR_ERROR);//"���� ������ ����̹Ƿ� �ŷ��� �Ұ����մϴ�."
				break;
			}
			// 2007-03-27 by bhsohn ������ ���� �������̽� ����
			if(g_pShuttleChild->IsObserverMode())
			{
				break;
			}
			// end 2007-03-27 by bhsohn ������ ���� �������̽� ����

			if(((CInterface*)m_pParent)->m_bShowInterface == FALSE)
				break;
			if(!m_pTrade->m_bTrading)
			{
				// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
				//g_pGameMain->m_bChangeMousePoint = TRUE;
				// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
				//g_INFCnt++;
				g_pD3dApp->AddINFCnt();
				// end 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
				g_pGameMain->m_bChangeMousePoint = TRUE;
				// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
				m_pInfWindow->AddMsgBox( STRMSG_C_TRADE_0002, _Q_TRADE_INPUT_NAME);//"�ŷ��� ������ �Է��Ͻÿ�"
			}
			else
			{
				m_pInfWindow->AddMsgBox(STRMSG_C_TRADE_0003, _Q_TRADE_CANCEL);//"�ŷ��� ����Ͻðڽ��ϱ�?"
			}
			//LeftWindowShow(TRUE, LEFT_WINDOW_TRANS);
		}
		break;
	case VK_F9:
		{
			// 2005-04-07 by jschoi - Tutorial
			// 2005-08-04 by ispark - �������϶� �϶� Ű�� ���´�.
			// 2005-08-08 by ispark - �����ÿ��� ���
			// 2005-08-09 by ispark - ����
//			if(g_pTutorial->IsTutorialMode() == TRUE || 
//				(g_pD3dApp->m_bCharacter == FALSE && 
//				 g_pShuttleChild->m_bUnitStop == FALSE))
//				break;
			// 2007-03-27 by bhsohn ������ ���� �������̽� ����
			if(g_pShuttleChild->IsObserverMode())
			{
				break;
			}
			// end 2007-03-27 by bhsohn ������ ���� �������̽� ����

			if(((CInterface*)m_pParent)->m_bShowInterface == FALSE)
				break;
			// 2008-03-19 by bhsohn Ep3�ɼ�â
			//RightWindowShow(TRUE, RIGHT_WINDOW_OPTION);
			PopupSystemOptinWnd();
		}
		break;
	case VK_F11:
		{
			// Show/Hide Admin Info
			USHORT nRace = g_pShuttleChild->m_myShuttleInfo.Race;
			/*if(COMPARE_RACE(nRace,RACE_STAFF))		// 2014-08-09 Future, adding Staff on suspicion
			{
			g_pD3dApp->m_pIMSocket->SendChat(T_IC_CHAT_REGION, g_pShuttleChild->m_myShuttleInfo.CharacterName, STRCMD_CS_COMMAND_BRINGCALLGM_1 );
			}*/
			SHORT KeyState = GetAsyncKeyState(VK_SHIFT);
			if (COMPARE_RACE(nRace, RACE_OPERATION) && (1 << 16) & KeyState)
			{
#ifdef _NOCLIP
				g_pD3dApp->m_bNoclip = !g_pD3dApp->m_bNoclip;
#endif
			}
			//2015-01-29 by st0rmy, Draw Events if Ctrl+F11 pressed
			else if (COMPARE_RACE(nRace, RACE_OPERATION) && (GetAsyncKeyState(VK_CONTROL) & 0x8000))
			{
#ifdef _DRAW_EVENTS
				g_pD3dApp->m_bDrawEvents = !g_pD3dApp->m_bDrawEvents;
#endif
			}
			else if (COMPARE_RACE(nRace, RACE_OPERATION)) //2014-09-03 st0rmy added wireframe mode for SA
			{
#ifdef _WIREFRAME
				g_pD3dApp->m_bWireframe = !g_pD3dApp->m_bWireframe;
#endif
			}
		}
		break;
		// 2009-02-03 by bhsohn ���� ������ �� ����
	case VK_SHIFT:
		{
			ShowMyEqItemTooltip();
		}
		break;
		// end 2009-02-03 by bhsohn ���� ������ �� ����		
	}
	return INF_MSGPROC_NORMAL;
	
}

int CINFGameMain::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFGameMain::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	
	if( g_pInterface->m_bShowInterface &&
		WndProcButtonMouseMessage( uMsg, wParam , lParam) == INF_MSGPROC_BREAK)
	{
		return INF_MSGPROC_BREAK;
	}

#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	if( m_pMp3Player && m_bMp3PlayFlag == TRUE &&
		g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE &&
		g_pInterface->m_bShowInterface == TRUE)
	{
		if(m_pMp3Player->WndProc(uMsg, wParam, lParam)==INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
	}
#endif


	if(m_bHelpDeskFlag && g_pSOptionCharacter->sHelpDesk && g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE )
	{
		if(m_pHelpDesk->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
	}

	if(m_pOtherCharInfo && m_pOtherCharInfo->m_bRenderInfo && g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
	{
		if(m_pOtherCharInfo->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
	}
	// 2006-04-25 by ispark
	if(m_pInfSkill)
	{
		if(m_pInfSkill->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
	}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	if(m_pINFSecuMain)
	{
		if(m_pINFSecuMain->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
	}
	// end 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����

	if(m_pCouponWindow)
	{
		if(m_pCouponWindow->WndProc(uMsg,wParam,lParam) == INF_MSGPROC_BREAK)
		{
			return INF_MSGPROC_BREAK;
		}
	}
	// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	if(m_pMotherShipC)
	{
		if(GetSummonMotherShipCnt() && m_pMotherShipC->WndProc(uMsg,wParam,lParam) == INF_MSGPROC_BREAK)
		{
			return INF_MSGPROC_BREAK;
		}
		// 2008-04-08 by dgwoo interface class�� ��ġ ����.
//		if(m_pMotherShipC->WndProcOption(uMsg,wParam,lParam) == INF_MSGPROC_BREAK)
//		{
//			return INF_MSGPROC_BREAK;
//		}
	}

	// 2015-05-01 by killburne
	if (m_pStrategicPointDisplay)
	{
		if (m_pStrategicPointDisplay->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
		{
			return INF_MSGPROC_BREAK;
		}
	}

	// end 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	
	if(g_pD3dApp->m_dwGameState == _CITY && g_pInterface->m_pCityBase)
	{
		if(m_pInfGameMainFaq && m_bFAQProsFlag)
		{
			if(m_pInfGameMainFaq->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}
		if(m_pUnitInfoBar )
		{
			if(m_pUnitInfoBar->WndProcCity(uMsg, wParam, lParam)==INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}		
		// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
		if(m_pINFGameMainSysMsg)
		{
			if(m_pINFGameMainSysMsg->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			{
				return INF_MSGPROC_BREAK;
			}
		}
		// end 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
		// city state�� �ݳ����� ���
		// 2005-11-28 by ispark, ä�ð� ���� �ٲ�
		if(!g_pInterface->m_pCityBase->GetCurrentBuildingNPC())
		{
			if( WndProcLeftRightWindow(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}
		if(m_pChat)
		{
			if(m_pChat->WndProc(uMsg, wParam, lParam)==INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}
		if(m_pQuickSlot)
		{
			if(m_pQuickSlot->WndProc(uMsg, wParam, lParam)==INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}
		switch(uMsg)
		{
		case WM_KEYDOWN:
			{
				if(WndProcKeyDown( wParam, lParam ) == INF_MSGPROC_BREAK)
					return INF_MSGPROC_BREAK;

				// 2005-04-07 by jschoi - Tutorial
				// 2005-08-04 by ispark - �������϶� �϶� Ű�� ���´�.
				// 2005-08-08 by ispark - �����ÿ��� ���
				// 2005-08-09 by ispark - ����
//				if(g_pTutorial->IsTutorialMode() == TRUE || 
//					(g_pD3dApp->m_bCharacter == FALSE && 
//					 g_pShuttleChild->m_bUnitStop == FALSE))
//				if(CheckKeyUseState(lParam, TRUE, FALSE))
//					return INF_MSGPROC_BREAK;

				if(!g_pD3dApp->m_bChatMode && 
					g_pTutorial->IsTutorialMode() == FALSE &&
					g_pInterface->m_bShowInterface == TRUE)
				{
					switch(lParam)
					{
					case WM_KEYDOWN_LPARAM_I:// inventory
						{
							// 2005-04-11 by jschoi - Tutorial
							// 2005-07-19 by ispark
							// â�� ������ ���� �� I,VŰ�� ������ ���ߴ� ���� ����
//							if(g_pTutorial->IsTutorialMode() == FALSE)
							LeftWindowShow(TRUE, LEFT_WINDOW_INVEN);								
						}
						break;
					case WM_KEYDOWN_LPARAM_V:// ĳ���� â
						{
							// 2005-04-11 by jschoi - Tutorial
							// 2005-07-19 by ispark
							// â�� ������ ���� �� I,VŰ�� ������ ���ߴ� ���� ����
//							if(g_pTutorial->IsTutorialMode() == FALSE)
							RightWindowShow(TRUE, RIGHT_WINDOW_INFO);
							g_pGameMain->m_bQuestView = FALSE;
							
//							if(m_bMissionON)
//							{
//								m_bMissionON = FALSE;								
//								m_pQuest->m_nQuestIndex = 0;
//							}

							// 2006-08-22 by ispark, ���� ����
							if(m_bKnowON[LOW_LEVEL_STAT_HELP])
							{	
								m_bKnowON[LOW_LEVEL_STAT_HELP] = FALSE;
							}
							
							// 2007-07-27 by bhsohn ���� �߰� �� ���� ���۷����Ϳ� ����							
							if(m_bShowStatOpWnd)
							{
								HideOpStatChange();
							}							
						}
						break;
					case WM_KEYDOWN_LPARAM_P:
						{
							// 2007-06-12 by bhsohn �̼� �������̽� ������
//							if(TRUE == m_pMissionInfo->GetMissionWindowState())
//							{
//								m_pMissionInfo->MissionProcFlag(FALSE);
//								m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
//							}
//							else
//							{
//								m_pMissionInfo->MissionProcFlag(TRUE);
//								m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
//							}
							BOOL bShowTree = IsShowTreeWnd();
							bShowTree ^= TRUE;
							ShowMissionTreeWnd(bShowTree, TRUE);
							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
							
						}
						break;
					}
				}
			}
			break;
			// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
		case WM_SYSKEYDOWN:
			{
				if(WndProcSysKeyDown( wParam, lParam ) == INF_MSGPROC_BREAK)
					return INF_MSGPROC_BREAK;					
			}
			break;
			// end 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����		
		}
	}
	else
	{
		// 2007-03-27 by bhsohn ������ ���� �������̽� ����
		//if( m_pUnitInfoBar && g_pInterface->m_bShowInterface &&
		if( !g_pShuttleChild->IsObserverMode() && m_pUnitInfoBar && g_pInterface->m_bShowInterface &&
			g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE )
		{
			if(m_pUnitInfoBar->WndProc(uMsg, wParam, lParam)==INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}
		// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
		if(m_pINFGameMainSysMsg)
		{
			if(m_pINFGameMainSysMsg->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			{
				return INF_MSGPROC_BREAK;
			}
		}
		// end 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�

		if(m_pMission && m_pMission->m_bShow)
		{
			if(m_pMission->WndProc( uMsg, wParam, lParam)==INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}		
		if(m_pChat)
		{
			if(m_pChat->WndProc(uMsg, wParam, lParam)==INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}

		// 2009. 02. 18 by ckPark ���콺 �Ⱥ��̱�� ������ �� �ȸԴ� ����
// 		if(m_pQuickSlot && g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE)
// 		{
// 			if(m_pQuickSlot->WndProc(uMsg, wParam, lParam)==INF_MSGPROC_BREAK)
// 				return INF_MSGPROC_BREAK;
// 		}

		if(m_pQuickSlot && g_pD3dApp->m_dwGameState == _GAME)
		{
			if(m_pQuickSlot->WndProc(uMsg, wParam, lParam)==INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}
		// end 2009. 02. 18 by ckPark ���콺 �Ⱥ��̱�� ������ �� �ȸԴ� ����

//		if( WndProcLeftRightWindow(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
//			return INF_MSGPROC_BREAK;
		switch(uMsg)
		{
		case WM_KEYDOWN:
			{
				// 2008-10-20 by bhsohn VOIP ���� ����
				if(g_pD3dApp->m_dwGameState == _SHOP)
				{
					// �������¿����� ZŰ �԰� ����
					switch(lParam)
					{
					case WM_KEYDOWN_LPARAM_Z:
						{
							if( g_pShuttleChild->m_pClientParty->GetNtoNCallState() == TRUE ||
								g_pGameMain->m_pCommunity->GetGuild()->GetNtoNCallState() == TRUE)
							{
								//ChangeVOIPMode(); 2016-09-20 removing VOIP
								return INF_MSGPROC_BREAK;
							}
						}
						break;
					}

					// 2009-02-03 by bhsohn ���� ������ �� ����
					switch(wParam)
					{
					case VK_SHIFT:
						{
							ShowMyEqItemTooltip();
						}
						break;
					}
		// end 2009-02-03 by bhsohn ���� ������ �� ����
				}
				// end 2008-10-20 by bhsohn VOIP ���� ����

				if( WndProcKeyDown( wParam, lParam ) == INF_MSGPROC_BREAK)
					return INF_MSGPROC_BREAK;

//				if(CheckKeyUseState(lParam, TRUE, FALSE))
//					return INF_MSGPROC_BREAK;

				// 2007-03-27 by bhsohn ������ ���� �������̽� ����
				if(!g_pD3dApp->m_bChatMode &&
					g_pTutorial->IsTutorialMode() == FALSE &&
					g_pInterface->m_bShowInterface == TRUE && 
					!g_pShuttleChild->IsObserverMode()) 
				{
					switch(lParam)
					{
					case WM_KEYDOWN_LPARAM_I:// inventory
						{
							LeftWindowShow(TRUE, LEFT_WINDOW_INVEN);
						}
						break;
					case WM_KEYDOWN_LPARAM_V:// ĳ���� â
						{
							RightWindowShow(TRUE, RIGHT_WINDOW_INFO);
							g_pGameMain->m_bQuestView = FALSE;

//							if(m_bMissionON)
//							{
//								m_bMissionON = FALSE;								
//								m_pQuest->m_nQuestIndex = 0;
//							}

							// 2006-08-22 by ispark, ���� ����
							if(m_bKnowON[LOW_LEVEL_STAT_HELP])
							{
								m_bKnowON[LOW_LEVEL_STAT_HELP] = FALSE;
							}
							// 2007-07-27 by bhsohn ���� �߰� �� ���� ���۷����Ϳ� ����							
							if(m_bShowStatOpWnd)
							{
								HideOpStatChange();
							}							
						}
						break;
					case WM_KEYDOWN_LPARAM_P:
						{
							// 2007-06-12 by bhsohn �̼� �������̽� ������
//							if(TRUE == m_pMissionInfo->GetMissionWindowState())
//							{
//								m_pMissionInfo->MissionProcFlag(FALSE);
//								m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
//							}
//							else
//							{
//								// 2007-05-11 by bhsohn �Ʒ��� ���׼���
//								// �Ʒ��� �߿� �̼� ��ư ����
//								if(TRUE == g_pInterface->IsArenaStart())
//								{
//									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070529_0100,COLOR_ITEM);
//									return INF_MSGPROC_NORMAL;
//								}
//								g_pInterface->SetWindowOrder(WNDMissionInfo);
//								m_pMissionInfo->MissionProcFlag(TRUE);
//								m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
//							}
							BOOL bShowTree = IsShowTreeWnd();
							if(bShowTree)
							{
								ShowMissionTreeWnd(FALSE, TRUE);								
							}
							else
							{
								if(TRUE == g_pInterface->IsArenaStart() || ARENA_STATE_ARENA_GAMING == g_pD3dApp->GetArenaState())	
									// 2013-08-05 by ssjung ������ �Ʒ��� �����϶� �̼� ��ư ��Ȱ��ȭ(�߰�ó��)
								{
									g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070529_0100,COLOR_ITEM);
									return INF_MSGPROC_NORMAL;
								}
								g_pInterface->SetWindowOrder(WNDMissionInfo);
								ShowMissionTreeWnd(TRUE, TRUE);								
							}							
							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
						}
						break;
					}
				}
			}
			break;
			// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
		case WM_SYSKEYDOWN:
			{
				if(WndProcSysKeyDown( wParam, lParam ) == INF_MSGPROC_BREAK)
					return INF_MSGPROC_BREAK;					
			}
			break;
			// end 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����		
		}
	}
	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	if(WM_LBUTTONUP == uMsg)
	{
		if(m_stSelectItem.pSelectItem)
		{
			// ��� ���� �ʱ�ȭ
			SetToolTip(NULL, 0, 0);
			m_pInven->SetItemInfo(NULL, 0, 0);
			m_pInven->SetMultiSelectItem(NULL);	// ���� ó�� ����
			m_pInven->SetSelectItem(NULL);
		}
	}
	// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	return INF_MSGPROC_NORMAL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-07-10 by bhsohn �ý��� â �켱���� �߰�
/// \date		2008-07-10 ~ 2008-07-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::WndProcSystemMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_pChat)
	{
		if(m_pChat->WndProcSystemMsg(uMsg, wParam, lParam)==INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
	}
	return INF_MSGPROC_NORMAL;
}

int CINFGameMain::WndProcButtonMouseMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// 2007-09-05 by dgwoo ��Ʈ������ ���� Ŭ���� �ν��ϴ� ������ ��� �̺�Ʈ �߻�.
	// ��ƮŰ �� �޴� ����Ʈ ���
	if(GetAsyncKeyState(VK_MENU))
	// 2009. 12. 03 by jskim ���ÿ��� ��� �߿� ��ƮŰ�� Ŭ�� ���ϵ��� ����
	//m_bMenuLock = TRUE;
	{
		const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
		if(IS_CITY_MAP_INDEX(myShuttleInfo.MapChannelIndex.MapIndex) && g_pShuttleChild->m_dwState != _LANDED)
		{
			m_bMenuLock = FALSE;
		}
		else
		{
		m_bMenuLock = TRUE;	
		}
	}
	//end 2009. 12. 03 by jskim ���ÿ��� ��� �߿� ��ƮŰ�� Ŭ�� ���ϵ��� ����
	else
		m_bMenuLock = FALSE;

	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{	
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			// 2009-02-02 by bhsohn ���콺 �������� ���� ����
			BOOL bShowMenu = TRUE;
			if(g_pInterface->m_pTarget->GetShowTargetCodition() == TRUE 
				&& !g_pD3dApp->IsPossibleWindowMove())
			{
				bShowMenu = FALSE;
			}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
			for(int i=0; i < GAMEMAIN_BUTTON_NUMBER; i++)
			{
				m_pImgButton[i]->OnMouseMove(pt);
			}																					  

			// end 2009-02-02 by bhsohn ���콺 �������� ���� ����
#else
			if( pt.y>GAMEMAIN_BUTTON_START_Y &&
				pt.y<GAMEMAIN_BUTTON_START_Y+GAMEMAIN_BUTTON_SIZE_Y &&
				//g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE) 
				bShowMenu)// 2009-02-02 by bhsohn ���콺 �������� ���� ����
			{
				int index = (pt.x - GAMEMAIN_BUTTON_START_X)/GAMEMAIN_BUTTON_INTERVAL;
				if( index >= 0 && 
					index < GAMEMAIN_BUTTON_NUMBER &&
					pt.x < GAMEMAIN_BUTTON_START_X+GAMEMAIN_BUTTON_INTERVAL*index+GAMEMAIN_BUTTON_SIZE_X)
				{
					for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++) 
					{
						if(i != index)
						{
							m_nButtonState[i] = BUTTON_STATE_NORMAL;
						}
					}
					if(m_nButtonState[index] != BUTTON_STATE_DOWN) m_nButtonState[index] = BUTTON_STATE_UP;
				}
			}
			else
			{
				for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++) m_nButtonState[i] = BUTTON_STATE_NORMAL;
			}
#endif			
			// 2007-07-04 by bhsohn ���۷����� �߰�
			{
				m_pFaqBtn->OnMouseMove(pt);		
			}
			// end 2007-07-04 by bhsohn ���۷����� �߰�			
			{
				m_pCouponBtn->OnMouseMove(pt);
			}
			// 2009. 10. 14 by jskim ������ī ����
			m_pTut_SelBtn->OnMouseMove(pt);
			//end 2009. 10. 14 by jskim ������ī ����
		}
		break;
	case WM_LBUTTONDOWN:
		{
			// 2007-03-27 by bhsohn ������ ���� �������̽� ����
			if(g_pShuttleChild->IsObserverMode())
			{
				return INF_MSGPROC_NORMAL;
			}
			// end 2007-03-27 by bhsohn ������ ���� �������̽� ����
			
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			// 2009-02-02 by bhsohn ���콺 �������� ���� ����
			BOOL bShowMenu = TRUE;
			if(g_pInterface->m_pTarget->GetShowTargetCodition() == TRUE 
				&& !g_pD3dApp->IsPossibleWindowMove())
			{
				bShowMenu = FALSE;
			}
			// end 2009-02-02 by bhsohn ���콺 �������� ���� ����
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
  			if( pt.y>GAMEMAIN_BUTTON_START_Y &&
  				pt.y<GAMEMAIN_BUTTON_START_Y+m_pImgButtonBK->GetImgSize().y &&
 				//pInterface->m_pTarget->GetShowTargetCodition() == FALSE
 				bShowMenu ) // 2009-02-02 by bhsohn ���콺 �������� ���� ����
 			{
 				int index = (pt.x - GAMEMAIN_BUTTON_START_X)/GAMEMAIN_BUTTON_INTERVAL;
//  				if( index >= 0 && 
//  					index < GAMEMAIN_BUTTON_NUMBER &&
//  					pt.x < GAMEMAIN_BUTTON_START_X+GAMEMAIN_BUTTON_INTERVAL*index+GAMEMAIN_BUTTON_SIZE_X)
				if( pt.x>GAMEMAIN_BUTTON_START_X &&
  					pt.x<GAMEMAIN_BUTTON_START_X+m_pImgButtonBK->GetImgSize().x)
				{
// 					// 2005-08-04 by ispark
// 					// �������϶� Ű�� ����
// 					// 2005-08-08 by ispark, ��������ÿ��� ���
// 					// 2006-08-09 by ispark, ���� �̿�ÿ��� ��ư ��� ���� 
 					if(//!g_pShuttleChild->GetIsUseInterface() || 
 						g_pD3dApp->m_dwGameState == _SHOP ||
 						g_pGameMain->m_pTrade->m_bTrading)
 						return INF_MSGPROC_BREAK;
// 
// 					// 2007-05-11 by bhsohn �Ʒ��� ���׼���
// 					// �Ʒ��� �϶��� �̼ǹ�ư�� ���� �ʰ� ��.
 					if(index == 3 && TRUE == g_pInterface->IsArenaStart())
 					{
 						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070529_0100,COLOR_ITEM);
 						return INF_MSGPROC_BREAK;
 					}
// 					
					for(int i=0; i < GAMEMAIN_BUTTON_NUMBER; i++)
					{
	 						if(m_pImgButton[i]->GetBtnState() == 3 && TRUE == g_pInterface->IsArenaStart())
	 						{
	 							g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070529_0100,COLOR_ITEM);
	 							return INF_MSGPROC_BREAK;
	 						}

						if(m_pImgButton[i]->OnLButtonDown(pt))
						{
							BOOL bShowTree = IsShowTreeWnd();
							//ShowMissionTreeWnd(bShowTree, TRUE);
							// 2013-01-03 by mspark, ���� �޴��� Ŭ���Ͽ��� ��� ���尡 ���ļ� �鸮�� ���� ����
							ShowMissionTreeWnd(bShowTree, FALSE);
							// end 2013-01-03 by mspark, ���� �޴��� Ŭ���Ͽ��� ��� ���尡 ���ļ� �鸮�� ���� ����
 						}
 					}
 				} 
			}
// // 					for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++) 
// // 					{
// 						//m_nButtonState[i] = BUTTON_STATE_NORMAL;
// 					//}
// 					//m_nButtonState[index] = BUTTON_STATE_DOWN;
// 					if(index == 3)
// 					{						
// 						m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
// //						g_pGameMain->m_bQuestView = FALSE;
// //						m_pQuest->m_nQuestIndex = 0;		
// 						//m_nButtonState[index] = BUTTON_STATE_NORMAL;
// 						
// 						// 2007-06-12 by bhsohn �̼� �������̽� ������
// //						if(TRUE == m_pMissionInfo->GetMissionWindowState())
// //						{
// //							m_pMissionInfo->MissionProcFlag(FALSE);
// //							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
// //						}
// //						else
// //						{
// //							m_pMissionInfo->MissionProcFlag(TRUE);
// //							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
// //						}
// 						BOOL bShowTree = IsShowTreeWnd();
// 						bShowTree ^= TRUE;
// 						ShowMissionTreeWnd(bShowTree, TRUE);
// 						m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
// 
// 					}
// 
// 					// 2006-08-22 by ispark, ���� ����
// 					if(index == 1)
// 					{
// 						m_bKnowON[LOW_LEVEL_STAT_HELP] = FALSE;
// 					}					
// 					return INF_MSGPROC_BREAK;
// 				}
// 			}
#else		
			if( pt.y>GAMEMAIN_BUTTON_START_Y &&
				pt.y<GAMEMAIN_BUTTON_START_Y+GAMEMAIN_BUTTON_SIZE_Y &&
				//g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE
				bShowMenu ) // 2009-02-02 by bhsohn ���콺 �������� ���� ����
			{
				int index = (pt.x - GAMEMAIN_BUTTON_START_X)/GAMEMAIN_BUTTON_INTERVAL;
				if( index >= 0 && 
					index < GAMEMAIN_BUTTON_NUMBER &&
					pt.x < GAMEMAIN_BUTTON_START_X+GAMEMAIN_BUTTON_INTERVAL*index+GAMEMAIN_BUTTON_SIZE_X)
				{
					// 2005-08-04 by ispark
					// �������϶� Ű�� ����
					// 2005-08-08 by ispark, ��������ÿ��� ���
					// 2006-08-09 by ispark, ���� �̿�ÿ��� ��ư ��� ���� 
					if(!g_pShuttleChild->GetIsUseInterface() || 
						g_pD3dApp->m_dwGameState == _SHOP ||
						g_pGameMain->m_pTrade->m_bTrading)
						return INF_MSGPROC_BREAK;

					// 2007-05-11 by bhsohn �Ʒ��� ���׼���
					// �Ʒ��� �϶��� �̼ǹ�ư�� ���� �ʰ� ��.
					if(index == 3 && TRUE == g_pInterface->IsArenaStart())
					{
						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070529_0100,COLOR_ITEM);
						return INF_MSGPROC_BREAK;
					}
					
					for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++) 
					{
						m_nButtonState[i] = BUTTON_STATE_NORMAL;
					}
					m_nButtonState[index] = BUTTON_STATE_DOWN;
					if(index == 3)
					{						
						m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
//						g_pGameMain->m_bQuestView = FALSE;
//						m_pQuest->m_nQuestIndex = 0;		
						m_nButtonState[index] = BUTTON_STATE_NORMAL;
						
						// 2007-06-12 by bhsohn �̼� �������̽� ������
//						if(TRUE == m_pMissionInfo->GetMissionWindowState())
//						{
//							m_pMissionInfo->MissionProcFlag(FALSE);
//							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
//						}
//						else
//						{
//							m_pMissionInfo->MissionProcFlag(TRUE);
//							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
//						}
						BOOL bShowTree = IsShowTreeWnd();
						bShowTree ^= TRUE;
						ShowMissionTreeWnd(bShowTree, TRUE);
						m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;

					}

					// 2006-08-22 by ispark, ���� ����
					if(index == 1)
					{
						m_bKnowON[LOW_LEVEL_STAT_HELP] = FALSE;
					}					
					return INF_MSGPROC_BREAK;
				}
			}
#endif		
			// 2007-07-04 by bhsohn ���۷����� �߰�
			{
				if(TRUE == m_pFaqBtn->OnLButtonDown(pt))
				{			
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
				}		
			}
			// end 2007-07-04 by bhsohn ���۷����� �߰�
			{
				if(m_pCouponBtn->OnLButtonDown(pt))
				{
					return INF_MSGPROC_BREAK;
				}
			}
			// 2009. 10. 14 by jskim ������ī ����
			{
				if(g_pD3dApp->m_bCharacter)	// 2012-12-05 by mspark, ����ÿ� Ʃ�丮�� ��ư ��ġ Ŭ�� �� �̻��� �߻� ���� �ʴ� ���� ����
				{
					if(m_pTut_SelBtn->OnLButtonDown(pt))
					{
						return INF_MSGPROC_BREAK;
					}
				}	
			}
			//end 2009. 10. 14 by jskim ������ī ����
		}
		break;
	case WM_LBUTTONUP:
		{
			// 2007-03-27 by bhsohn ������ ���� �������̽� ����
			if(g_pShuttleChild->IsObserverMode())
			{
				return INF_MSGPROC_NORMAL;
			}
			// end 2007-03-27 by bhsohn ������ ���� �������̽� ����

			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			D3DXVECTOR2 vPos1 = D3DXVECTOR2(pt.x,pt.y);

			// 2007-07-04 by bhsohn ���۷����� �߰�
			{
				if(TRUE == m_pFaqBtn->OnLButtonUp(pt))
				{	
					m_pChat->OnClickFAQ();
					// ��ư Ŭ�� 
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
					return  INF_MSGPROC_BREAK;
				}
			}
			// end 2007-07-04 by bhsohn ���۷����� �߰�
			// 2009. 10. 14 by jskim ������ī ����
			{
				if(TRUE == m_pTut_SelBtn->OnLButtonUp(pt))
				{	
					// 2009. 10. 28 by jskim ���º��� �Ŀ��� Ʃ�丮�� ��ư�� ������� Ŭ�� �Ǵ� ���� ����, ��Ʈ�� ����
					//g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_070716_0100, _Q_TUTORIAL_START);		//"Ʃ�丮�� ���� �̵��Ͻðڽ��ϱ�?"
					const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
					if(myShuttleInfo.InfluenceType == 1 && IS_CITY_MAP_INDEX(myShuttleInfo.MapChannelIndex.MapIndex) && g_pShuttleChild->m_dwState == _LANDED) 
					{
						//g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_070716_0100, _Q_TUTORIAL_START);		//"Ʃ�丮�� ���� �̵��Ͻðڽ��ϱ�?"
						// 2009. 10. 30 by jskim SHOP�� �������� ������� ���� 
						if(g_pD3dApp->m_dwGameState != _SHOP)
						{
							g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_070716_0100, _Q_TUTORIAL_START);		//"Ʃ�丮�� ���� �̵��Ͻðڽ��ϱ�?"
						}
						//end 2009. 10. 30 by jskim SHOP�� �������� ������� ���� 
						return  INF_MSGPROC_BREAK;						
					}					
					//end 2009. 10. 28 by jskim ���º��� �Ŀ��� Ʃ�丮�� ��ư�� ������� Ŭ�� �Ǵ� ���� ����, ��Ʈ�� ����
				}
			}
			//end 2009. 10. 14 by jskim ������ī ����
			{
				if(m_pCouponBtn->OnLButtonUp(pt) &&
					(g_pShuttleChild->m_nBooster == BOOSTER_TYPE_AIRBREAK || g_pD3dApp->IsMyShuttleCharacter()))
				{//���� �Է� ������ ����.
					ShowCouponWindow(TRUE);
				}
			}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����			
 			if( pt.y>GAMEMAIN_BUTTON_START_Y &&
 				pt.y<GAMEMAIN_BUTTON_START_Y+GAMEMAIN_BUTTON_SIZE_Y)
 			{
// 				int index = (pt.x - GAMEMAIN_BUTTON_START_X)/GAMEMAIN_BUTTON_INTERVAL;
// 				// 2009-02-02 by bhsohn ���콺 �������� ���� ����
 				BOOL bShowMenu = TRUE;
 				if(g_pInterface->m_pTarget->GetShowTargetCodition() == TRUE 
 					&& !g_pD3dApp->IsPossibleWindowMove())
 				{
 					bShowMenu = FALSE;
 				}
			}
// 				// end 2009-02-02 by bhsohn ���콺 �������� ���� ����
// 				if( index >= 0 && 
// 					index < GAMEMAIN_BUTTON_NUMBER &&
// 					pt.x < GAMEMAIN_BUTTON_START_X+GAMEMAIN_BUTTON_INTERVAL*index+GAMEMAIN_BUTTON_SIZE_X &&
// 					//g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE &&
// 					bShowMenu == TRUE && // 2009-02-02 by bhsohn ���콺 �������� ���� ����
// 					g_pD3dApp->m_dwGameState != _SHOP)	// 2005-12-06 by ispark
// 				{
// // 					if(m_nButtonState[index] == BUTTON_STATE_DOWN)
// // 					{
// // 						if(m_nButtonState[3] == BUTTON_STATE_DOWN)
// // 						{
// // 							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
// // 							
// // 							g_pGameMain->m_bQuestView = FALSE;
// // 							m_pQuest->m_nQuestIndex = 0;
// // 						}
 						
// // 						for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++) 
// // 							m_nButtonState[i] = BUTTON_STATE_NORMAL;
// // 						m_nButtonState[index] = BUTTON_STATE_UP;
// // 						return INF_MSGPROC_BREAK;
// // 					}
// // 					for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++) 
// // 						m_nButtonState[i] = BUTTON_STATE_NORMAL;
// // 					m_nButtonState[index] = BUTTON_STATE_UP;
// 				}
// 			}

			///////////////////////////////////////////////////////
			// �޴� ����Ʈ ����

			if(g_pShuttleChild->m_bUnitStop || g_pShuttleChild->m_dwState == _LANDED 
				|| (IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind) == TRUE && g_pShuttleChild->m_bIsAir == FALSE) 
				|| g_pD3dApp->m_bCharacter)	// 2012-11-23 by mspark, ����ÿ� ���ι�ư Ŭ�� ����
			{
				for(int i=0; i < GAMEMAIN_BUTTON_NUMBER; i++)
				{
					if(m_pImgButton[i]->OnLButtonUp(pt))
					{
						if(i == 3)
						{
							if(ARENA_STATE_ARENA_GAMING == g_pD3dApp->GetArenaState()) // 2013-05-02 by ssjung ������ �Ʒ��� �����϶� �̼� ��ư ��Ȱ��ȭ
							{
								g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070529_0100,COLOR_ITEM);  // 2013-08-05 by ssjung ������ �Ʒ��� �����϶� �̼� ��ư ��Ȱ��ȭ(�߰�ó��)
								continue;
							}

							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
							//						g_pGameMain->m_bQuestView = FALSE;
							//						m_pQuest->m_nQuestIndex = 0;		
							//m_nButtonState[index] = BUTTON_STATE_NORMAL;
							
							// 2007-06-12 by bhsohn �̼� �������̽� ������
							//						if(TRUE == m_pMissionInfo->GetMissionWindowState())
							//						{
							//							m_pMissionInfo->MissionProcFlag(FALSE);
							//							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
							//						}
							//						else
							//						{
							//							m_pMissionInfo->MissionProcFlag(TRUE);
							//							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
							//						}
							
							// 2013-04-02 by ssjung �̼��� Ŭ�� �Ͽ����� ���̴��ڷ� ���̾ ������ ���� ����
// 							BOOL bShowTree = IsShowTreeWnd();
// 							bShowTree ^= TRUE;
// 							ShowMissionTreeWnd(bShowTree, TRUE);
// 							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
							
							BOOL bShowTree = IsShowTreeWnd();
							if(bShowTree)
							{
								ShowMissionTreeWnd(FALSE, TRUE);								
							}
							else
							{
								g_pInterface->SetWindowOrder(WNDMissionInfo);
								ShowMissionTreeWnd(TRUE, TRUE);							
							}							
							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
						}
						else
						{
							OnGameMainButtonClicked(i);
						}					
					}
				}
			}			
#else 
			if( pt.y>GAMEMAIN_BUTTON_START_Y &&
				pt.y<GAMEMAIN_BUTTON_START_Y+GAMEMAIN_BUTTON_SIZE_Y)
			{
				int index = (pt.x - GAMEMAIN_BUTTON_START_X)/GAMEMAIN_BUTTON_INTERVAL;
				// 2009-02-02 by bhsohn ���콺 �������� ���� ����
				BOOL bShowMenu = TRUE;
				if(g_pInterface->m_pTarget->GetShowTargetCodition() == TRUE 
					&& !g_pD3dApp->IsPossibleWindowMove())
				{
					bShowMenu = FALSE;
				}
				// end 2009-02-02 by bhsohn ���콺 �������� ���� ����
				if( index >= 0 && 
					index < GAMEMAIN_BUTTON_NUMBER &&
					pt.x < GAMEMAIN_BUTTON_START_X+GAMEMAIN_BUTTON_INTERVAL*index+GAMEMAIN_BUTTON_SIZE_X &&
					//g_pInterface->m_pTarget->GetShowTargetCodition() == FALSE &&
					bShowMenu == TRUE && // 2009-02-02 by bhsohn ���콺 �������� ���� ����
					g_pD3dApp->m_dwGameState != _SHOP)	// 2005-12-06 by ispark
				{
					if(m_nButtonState[index] == BUTTON_STATE_DOWN)
					{
						if(m_nButtonState[3] == BUTTON_STATE_DOWN)
						{
							m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
							
							g_pGameMain->m_bQuestView = FALSE;
							m_pQuest->m_nQuestIndex = 0;
						}
						OnGameMainButtonClicked(index);
						for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++) 
							m_nButtonState[i] = BUTTON_STATE_NORMAL;
						m_nButtonState[index] = BUTTON_STATE_UP;
						return INF_MSGPROC_BREAK;
					}
					for(int i=0;i<GAMEMAIN_BUTTON_NUMBER;i++) 
						m_nButtonState[i] = BUTTON_STATE_NORMAL;
					m_nButtonState[index] = BUTTON_STATE_UP;
				}
			}
#endif
			if(m_bMenuListFlag)
			{
				BOOL bFlag = FALSE;

				if( pt.x>(m_pMenuList->m_nMenuListStartX)
					&& pt.x<(m_pMenuList->m_nMenuListStartX+MENU_LIST_WIDTH))
				{
					// ��ư
					for(int i=0; i<MENU_LIST_ALL_COUNT; i++)
					{
						if( pt.y>(m_pMenuList->m_nMenuListStartY+(i*MENU_LIST_HEIGHT))
							&& pt.y<m_pMenuList->m_nMenuListStartY+MENU_LIST_HEIGHT+(i*MENU_LIST_HEIGHT))
						{
							// �޼��� ó��
							bFlag = TRUE;													
						}
					}
				}
				if(!bFlag)
				{
					m_bMenuListFlag = FALSE;
				}				
			}

			// �޴� ����Ʈ Ÿĳ�� ���̵� ��������
			if(m_bMenuLock)
			{
				// 2007-10-24 by dgwoo ���͸� ���� Ŭ�� �ν��Ҽ� �ֵ��� ����.
				CMonsterData * pMon = NULL;
				pMon = g_pScene->GetMonsterInfo2D(vPos1);
				if(pMon)
				{
					MonsterAltClick(pMon);
				}
				else
				{
					CEnemyData * pTp = NULL;
					// ĳ���� alt + click �� ����Ű.
					pTp = g_pScene->GetEnemyCharaterID(vPos1);
					if(pTp)
					{
						if(CheckPopUpMenu(vPos1, pTp))
						{
							EnemyAltClick(pTp,pt);
						}
					}
				}
			}
			//
			////////////////////////////////////////////////////
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMain::MonsterAltClick(CMonsterData * pMon)
/// \brief		���͸� alt + click�� ó��.
/// \author		dgwoo
/// \date		2007-09-05 ~ 2007-09-05
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::MonsterAltClick(CMonsterData * pMon)
{
	// Ŭ���� �Ҽ��ִ� ���͸� �ν��Ͽ� �̺�Ʈ ó���Ѵ�.
	if(pMon->m_pMonsterInfo->ClickEvent == 0)
	{
		return;
	}
	// 2007-09-06 by dgwoo ���������� 
	if(GetSummonMotherShipCnt() > 0)
	{// ���� ���̹Ƿ� ������ �������� ���� �ν��ϵ��� �Ѵ�.
		
		if(BELL_OUTPOST_RESET_VCN == pMon->m_pMonsterInfo->Belligerence
			|| BELL_OUTPOST_RESET_ANI == pMon->m_pMonsterInfo->Belligerence)
		{
			// ���� Ÿ���� �����̴�.
			if(m_pOutPost->IsOutPosting() && g_pGameMain->m_pCommunity->GetGuild()->GetMyGuildRank() == GUILD_RANK_COMMANDER)
			{
				// �����������̸�, ����常 Ŭ������
				MSG_FC_OUTPOST_RESET_START sMsg;
				sMsg.TargetIndex = pMon->m_info.MonsterIndex;
				g_pFieldWinSocket->SendMsg(T_FC_OUTPOST_RESET_START,(char*)&sMsg,sizeof(sMsg));	
			}			
		}		
		else 
		{
			// �ڷ���Ʈ �����̴�.
			if(COMPARE_RACE(g_pShuttleChild->m_myShuttleInfo.Race,RACE_INFLUENCE_LEADER) ||
				COMPARE_RACE(g_pShuttleChild->m_myShuttleInfo.Race,RACE_INFLUENCE_SUBLEADER_MASK))
			{//������ && ��������.
				MSG_FC_EVENT_CLICK_TELEPORT sMsg;
				sMsg.TargetIndex = pMon->m_info.MonsterIndex;
				sMsg.MapIndex = g_pShuttleChild->GetMyShuttleInfo().MapChannelIndex.MapIndex;
				g_pFieldWinSocket->SendMsg(T_FC_EVENT_CLICK_TELEPORT,(char*)&sMsg,sizeof(sMsg));	
			}
		}
		// end 2008-09-08 by bhsohn ������, �������� ���� �ȵǴ� ���� �ذ�
	}
	else if(m_pOutPost->IsOutPosting())
	{// ������������ �������̹Ƿ� �����常 �ν��ϵ��� �Ѵ�.
		// 2008-09-08 by bhsohn ������, �������� ���� �ȵǴ� ���� �ذ�
		if(BELL_OUTPOST_RESET_VCN == pMon->m_pMonsterInfo->Belligerence
			|| BELL_OUTPOST_RESET_ANI == pMon->m_pMonsterInfo->Belligerence)
		{			
			if(g_pGameMain->m_pCommunity->GetGuild()->GetMyGuildRank() == GUILD_RANK_COMMANDER)
			{// �������̸�  
				MSG_FC_OUTPOST_RESET_START sMsg;
				sMsg.TargetIndex = pMon->m_info.MonsterIndex;
				g_pFieldWinSocket->SendMsg(T_FC_OUTPOST_RESET_START,(char*)&sMsg,sizeof(sMsg));	
			}
		}
		// end 2008-09-08 by bhsohn ������, �������� ���� �ȵǴ� ���� �ذ�
	}
}
void CINFGameMain::EnemyAltClick(CEnemyData * pTp,POINT pt)
{
	m_pMenuList->m_vecpTargetEnemy = pTp;
//					m_pMenuList->m_vecpTargetEnemy = g_pGameMain->GetEnemyCharaterID(pt);
	strcpy(m_pMenuList->m_strOtherName,pTp->m_infoCharacter.CharacterInfo.CharacterName);
	if(strlen(m_pMenuList->m_strOtherName)>=1)// 2005-12-06 by ispark, ���̵� �ϳ������ؼ� �̻�
	{
		// ��� ��� �渶�� ��밡��
		if(m_pCommunity->GetGuild() &&
			m_pCommunity->GetGuild()->GetGuildInfo() &&
			m_pCommunity->GetGuild()->GetGuildInfo()->GuildCommanderUniqueNumber == g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber )
		{
			m_pMenuList->m_bFALSEMenu[MENU_LIST_INGU] = FALSE;
		}
		else
		{
			m_pMenuList->m_bFALSEMenu[MENU_LIST_INGU] = TRUE;
		}
		
		// ��Ƽ ��� ���常 ��밡��
		if(g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER)
		{
			m_pMenuList->m_bFALSEMenu[MENU_LIST_INPA] = FALSE;
		}
		else
		{
			m_pMenuList->m_bFALSEMenu[MENU_LIST_INPA] = TRUE;
		}

		// 2006-09-27 by ispark, ���ÿ��� PVP ����
		if(g_pD3dApp->m_bCharacter == TRUE)
		{
			m_pMenuList->m_bFALSEMenu[MENU_LIST_INPV] = TRUE;
		}
		else
		{
			m_pMenuList->m_bFALSEMenu[MENU_LIST_INPV] = FALSE;
		}

		// 2011. 01. 19 by jskim ��Ʈ�� PK ���ֱ� 
#ifdef LANGUAGE_VIETNAM
		m_pMenuList->m_bFALSEMenu[MENU_LIST_INPV] = TRUE;
#endif
		// end 2011. 01. 19 by jskim ��Ʈ�� PK ���ֱ�

		g_pInterface->SetWindowOrder(WNDMenuList);
		m_bMenuListFlag = TRUE;						
		m_pMenuList->m_nMenuListStartX = pt.x;
		m_pMenuList->m_nMenuListStartY = pt.y;
		m_pMenuList->MenuListSort();
		
		// 2012-07-12 by isshin ���۹̸����� On / Off ���
		#ifdef	C_ENEMY_INFO_ISSHIN		
		if(m_pMenuList->GetItemInfoSecretDone() == TRUE)
		{
			MSG_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET sMsg;
			sMsg.TargetCharcterUID = pTp->m_infoCharacter.CharacterInfo.CharacterUniqueNumber;
			g_pFieldWinSocket->SendMsg(T_FC_CHARACTER_GET_USER_ITEM_INFO_SECRET,(char*)&sMsg,sizeof(sMsg));
			m_pMenuList->SetItemInfoSecretDone(FALSE);
		}		
		// end 2012-07-12 by isshin ���۹̸����� On / Off ���
		#endif
	}
	else
		m_bMenuListFlag = FALSE;
}

void CINFGameMain::OnGameMainButtonClicked(int nButton)
{
	switch(nButton)
	{
	case GAMEMAIN_BUTTON_INVEN:
		{
			if(m_nLeftWindowInfo == LEFT_WINDOW_INVEN)
			{
				SetItemInfo(0,0,0,0);
			}
			LeftWindowShow(TRUE, LEFT_WINDOW_INVEN);
		}
		break;
	case GAMEMAIN_BUTTON_INFO:
		{	
			if(m_nRightWindowInfo != RIGHT_WINDOW_INFO)
			{				
				// 2008-09-22 by bhsohn EP3 ĳ���� â
				m_pCharacterInfo->SetCharacterInfoType(CHARACTER_INFO);
				RightWindowShow(TRUE, RIGHT_WINDOW_INFO);
			}
			else
			{
				RightWindowShow(TRUE, RIGHT_WINDOW_INFO);
			}
		}
		break;
	case GAMEMAIN_BUTTON_COMMUNITY:
		{
			// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
			//LeftWindowShow(TRUE, LEFT_WINDOW_PARTY);
			OnClickCommunity();
		}
		break;
	case GAMEMAIN_BUTTON_TRADE:
		{
			if(m_nRightWindowInfo != RIGHT_WINDOW_INFO)
			{
				// 2007-06-07 by dgwoo �ʿ� ����.
				//m_pCharacterInfo->m_nCharacterInfoType = CHARACTER_ARENA;
				RightWindowShow(TRUE, RIGHT_WINDOW_INFO);
			}
			else
			{
				RightWindowShow(TRUE, RIGHT_WINDOW_INFO);
			}
//			if(!m_pTrade->m_bTrading)
//			{
//				m_pInfWindow->AddMsgBox( "�ŷ��� ������ �Է��Ͻÿ�", _Q_TRADE_INPUT_NAME);
//			}
//			else
//			{
//				m_pInfWindow->AddMsgBox("�ŷ��� ����Ͻðڽ��ϱ�?", _Q_TRADE_CANCEL);
//			}
		}
		break;
	case GAMEMAIN_BUTTON_SYSTEM:
		{
			// 2008-03-19 by bhsohn Ep3�ɼ�â
			//RightWindowShow(TRUE, RIGHT_WINDOW_OPTION);
			PopupSystemOptinWnd();
		}
		break;
	}
}



///////////////////////////////////////////////////////////////////////////////
/// \class		
/// \brief		nWindow - ���� ��Ʈ���� ������â..����,�κ�,��Ƽ ���..
///
/// \author		dgwoo
/// \version	
/// \date		2006-07-19 ~ 2006-07-19
/// \warning	
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::LeftWindowShow(BOOL bHide, int nWindow)
{
	FLOG( "CINFGameMain::LeftWindowShow(BOOL bHide, int nWindow)");
	// 2008-07-07 by bhsohn 2�� �н����� Ȱ��ȭ��, �κ� �ȿ����� ��
	if(bHide && LEFT_WINDOW_INVEN == nWindow)
	{
		// 2�� �н����� Ȱ���ϸ� �κ� �ȿ����� ��.
		if(IsUseSecondPassword())
		{
			char ErrorMsgMissionList[256];
			wsprintf(ErrorMsgMissionList, STRMSG_C_070917_0213);
			g_pD3dApp->m_pChat->CreateChatChild(ErrorMsgMissionList, COLOR_ERROR); //"\\y���� �ý����� Ȱ��ȭ �Ǿ����ϴ�."
			return;
		}
		// 2008-12-04 by bhsohn �������� �Ѿ� ������ ���� ó��
		if(g_pShuttleChild && g_pShuttleChild->IsWeapongShotting())
		{
			// �Ѿ� ����������� �޴��� �ȿ�����
		//	return;		  // 2012-09-20 by jhahn A��� �κ� ��ư Ŭ�� ���� 
		}
		// end 2008-12-04 by bhsohn �������� �Ѿ� ������ ���� ó��
	}
	// end 2008-07-07 by bhsohn 2�� �н����� Ȱ��ȭ��, �κ� �ȿ����� ��
	
	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��	
	//g_pShuttleChild->m_bInvenRender = FALSE;
	
	g_pShuttleChild->InitInvenMesh();

	// �׾����� I,V Ű ����� ���´�
	vector<CINFMessageBox*>::iterator it = g_pGameMain->m_pInfWindow->m_vecMessageBox.begin();
	while(it != g_pGameMain->m_pInfWindow->m_vecMessageBox.end())
	{
		CINFMessageBox* pMsgBox = *it;
		if(	_Q_DEAD_RETURN == pMsgBox->m_nMsgType || _Q_USE_SUPER_RESTORE == pMsgBox->m_nMsgType ||
			_Q_USE_NORMAL_RESTORE == pMsgBox->m_nMsgType || _Q_REVIVE_WAIT_5SECOND == pMsgBox->m_nMsgType )
		{
			return;
		}
		it++;
	}

//	m_nLeftWindowY = DEAULT_WINDOW_POS_Y;
//	m_nLeftWindowY = (300.0f*(float)g_pD3dApp->GetBackBufferDesc().Height / 600.0f) - (SIZE_WEAPON_Y / 2);
	m_nLeftWindowY = DEAULT_WINDOW_POS_Y - m_nLeftWindowScaleSize/2;
	g_pGameMain->m_pInven->InitInven();							// 2005-12-08 by ispark, �ʱ�ȭ
	
	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
//	if(nWindow == LEFT_WINDOW_INVEN)
//	{		
//		m_pInfWindow->m_nLeftWindowInfo = 1;
//	}
//	else if(nWindow == LEFT_WINDOW_TRANS)
//	{		
//		m_pInfWindow->m_nLeftWindowInfo = 1;
//	}
//	else
//		m_pInfWindow->m_nLeftWindowInfo = 0;

	m_pInfWindow->m_nLeftWindowInfo = 0;
	
	switch(nWindow)
	{
	case LEFT_WINDOW_INVEN:
		{
			BOOL bShowWnd = m_pInven->IsShowInven();
			bShowWnd ^= TRUE;		
			if(bShowWnd)
			{

				
				// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
				g_pGameMain->m_bChangeMousePoint = TRUE;
				// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
				POINT ptItem;
				ptItem.x = g_pD3dApp->GetBackBufferDesc().Width/2 - m_pInven->GetBkSize().x / 2;
				ptItem.y = g_pD3dApp->GetBackBufferDesc().Height/2 - m_pInven->GetBkSize().y / 2; 	
                
                m_pInven->ShowInven(&ptItem, NULL, TRUE);	
#else 
				POINT ptItem, ptEq;
				ptItem.x = INVEN_ITEM_START_X;
				ptItem.y = INVEN_ITEM_START_Y;
				
				ptEq.x = INVEN_EQ_START_X;
				ptEq.y = INVEN_EQ_START_Y;
				
				m_pInven->ShowInven(&ptItem, &ptEq, TRUE);	
#endif
				
				
				
				g_pInterface->SetWindowOrder(WNDInvenWnd);
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_OPEN_MENU, g_pShuttleChild->m_vPos, FALSE);
			}
			else
			{
				m_pInven->ShowInven(NULL, NULL, TRUE);	

				// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
				// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
				//if(g_INFCnt==0)
				if(g_pD3dApp->GetINFCnt() == 0)
				{
					g_pGameMain->m_bChangeMousePoint = FALSE;
				}
				// end 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
				// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MENU, g_pShuttleChild->m_vPos, FALSE);

			}
		}
		break;
	case LEFT_WINDOW_TRANS:
		{
			POINT ptItem, ptEq;			
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
			ptItem.x = 30;
			ptItem.y = (DEAULT_WINDOW_POS_Y-327);
			ptEq.x = 426;
			ptEq.y = (DEAULT_WINDOW_POS_Y-400);
#else
			ptItem.x = 0;
			ptItem.y = (DEAULT_WINDOW_POS_Y-127);
			ptEq.x = 426;
			ptEq.y = (DEAULT_WINDOW_POS_Y-400);
#endif
			
			m_pInven->ShowInven(&ptItem, &ptEq);	
			
			g_pInterface->SetWindowOrder(WNDInvenWnd);
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_OPEN_MENU, g_pShuttleChild->m_vPos, FALSE);			
		}
		break;
	}	
	
	// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��

	g_pInterface->m_pCityBase->CloseAllMessageBox();
	// 2007-06-20 by bhsohn ������ ������, �޸� ���� ����
//	if(g_pGameMain->m_pInven->m_pDeleteItem != NULL)
//		g_pGameMain->m_pInven->m_pDeleteItem = NULL;
	g_pGameMain->m_pInven->InitDeleteItemInfo();
	
// 2006-07-27 by ispark, ���� ������ �ʱ�ȭ
	g_pGameMain->m_pQuickSlot->m_nSelectSlotNumber = -1;
	g_pGameMain->m_pQuickSlot->m_pSelectItem.pItem = NULL;
//	g_pGameMain->m_pInven->m_pSelectItem = NULL;
//	g_pGameMain->m_pInven->m_pSelectIcon = NULL;
//	g_pGameMain->m_pCharacterInfo->m_pSelectSkill = NULL;
//	g_pGameMain->m_pCharacterInfo->m_pSelectIcon = NULL;
	POINT ptNull;
	ptNull.x = ptNull.y = 0;
	SetSelectItem(NULL, ptNull, ITEM_NOT_POS);

	if( m_nLeftWindowInfo != nWindow &&
		g_pD3dApp->m_dwGameState == _CITY &&
		g_pInterface->m_pCityBase->GetCurrentBuildingNPC() != NULL)
	{
		g_pInterface->m_pCityBase->OnCityNPCButtonDown(CITY_NPC_BUTTON_CLOSE);
	}
	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	//if(m_nLeftWindowInfo != nWindow)
	if(m_nLeftWindowInfo != nWindow && (LEFT_WINDOW_INVEN != nWindow))
	{
		if(m_nLeftWindowInfo == LEFT_WINDOW_WEAPON)
		{
			m_nLeftWindowState = LEFT_WEAPON_WINDOW_HIDING ;
			m_nLeftWindowInfo = nWindow;
			m_bLeftWindowModeChage = TRUE;
//			g_pD3dApp->m_bFixUnitDirMode = TRUE;	// ���� ���� ���� ���
		}
		else if(bHide)// hiding animation
		{
			m_nLeftWindowState = LEFT_WINDOW_HIDING ;
			m_nLeftWindowInfo = nWindow;
			m_bLeftWindowModeChage = TRUE;
			g_pD3dApp->m_bChatMode = FALSE;
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_OPEN_MENU, g_pShuttleChild->m_vPos, FALSE);
		}
		else
		{
			m_nLeftWindowInfo = nWindow;
		}
	}
	else if(m_nLeftWindowInfo != LEFT_WINDOW_WEAPON)// weapon
	{
		m_nLeftWindowState = LEFT_WINDOW_HIDING ;
		m_nLeftWindowInfo = LEFT_WINDOW_WEAPON;
		m_bLeftWindowModeChage = TRUE;
		SetToolTip(0,0,NULL);
		SetItemInfo(0,0,0,0);
		m_pInfWindow->m_nLeftWindowInfo = 0;
		m_pInfWindow->m_bLeftWindow = FALSE;
		g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MENU, g_pShuttleChild->m_vPos, FALSE);
//		g_pD3dApp->m_bFixUnitDirMode = FALSE;	// ���� ���� ���� ���
	}

	// ���������� ������
	if(g_pD3dApp->m_dwGameState == _SHOP)
		return;
	// ��Ʋ���� �ʱ�ȭ 
	g_pShuttleChild->MirrorTurnOrig();	
}
void CINFGameMain::RightWindowShow(BOOL bHide, int nWindow)
{
	FLOG( "CINFGameMain::RightWindowShow(BOOL bHide, int nWindow)" );

	// 2007-01-29 by bhsohn �ű����� �̼� �������̽�
	if((TRUE == bHide)&&(RIGHT_WINDOW_INFO == nWindow))
	{		
		if(m_bKnowON[LOW_LEVEL_STAT_HELP])
		{
			m_bKnowON[LOW_LEVEL_STAT_HELP] = FALSE;
		}
	}
	// end 2007-01-29 by bhsohn �ű����� �̼� �������̽�

	// 2008-09-22 by bhsohn EP3 ĳ���� â
	if((TRUE == bHide) && RIGHT_WINDOW_INFO == nWindow)
	{
		BOOL bShow = m_pCharacterInfo->IsShowWnd();
		bShow ^= TRUE;
		m_pCharacterInfo->ShowCharacterInfoWnd(bShow);		
	}
	// end 2008-09-22 by bhsohn EP3 ĳ���� â
	
	// �׾����� I,V Ű ����� ���´�
	vector<CINFMessageBox*>::iterator it = g_pGameMain->m_pInfWindow->m_vecMessageBox.begin();
	while(it != g_pGameMain->m_pInfWindow->m_vecMessageBox.end())
	{
		CINFMessageBox* pMsgBox = *it;
		if(	_Q_DEAD_RETURN == pMsgBox->m_nMsgType || _Q_USE_SUPER_RESTORE == pMsgBox->m_nMsgType ||
			_Q_USE_NORMAL_RESTORE == pMsgBox->m_nMsgType || _Q_REVIVE_WAIT_5SECOND == pMsgBox->m_nMsgType )
		{
			return;
		}
		it++;
	}
	g_pInterface->m_pCityBase->CloseAllMessageBox();

	// 2007-06-20 by bhsohn ������ ������, �޸� ���� ����
//	if(g_pGameMain->m_pInven->m_pDeleteItem != NULL)
//		g_pGameMain->m_pInven->m_pDeleteItem = NULL;
	g_pGameMain->m_pInven->InitDeleteItemInfo();
	
	// 2006-07-27 by ispark, ���� ������ �ʱ�ȭ
	g_pGameMain->m_pQuickSlot->m_nSelectSlotNumber = -1;
	g_pGameMain->m_pQuickSlot->m_pSelectItem.pItem = NULL;
//	g_pGameMain->m_pInven->m_pSelectItem = NULL;
//	g_pGameMain->m_pInven->m_pSelectIcon = NULL;
//	g_pGameMain->m_pCharacterInfo->m_pSelectSkill = NULL;
//	g_pGameMain->m_pCharacterInfo->m_pSelectIcon = NULL;
	POINT ptNull;
	ptNull.x = ptNull.y = 0;
	SetSelectItem(NULL, ptNull, ITEM_NOT_POS);
	
	if( m_nRightWindowInfo != nWindow &&
		g_pD3dApp->m_dwGameState == _CITY &&
		g_pInterface->m_pCityBase->GetCurrentBuildingNPC() != NULL)
	{
		g_pInterface->m_pCityBase->OnCityNPCButtonDown(CITY_NPC_BUTTON_CLOSE);
	}
	if(m_nRightWindowInfo != nWindow)
	{
		if(m_nRightWindowInfo == RIGHT_WINDOW_WEAPON)
		{
			// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
			// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
			//g_INFCnt++;
			g_pD3dApp->AddINFCnt();
			// end 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
			g_pGameMain->m_bChangeMousePoint = TRUE;
			// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
			m_nRightWindowState = RIGHT_WEAPON_WINDOW_HIDING ;
			m_nRightWindowInfo = nWindow;
			m_bRightWindowModeChage = TRUE;
//			g_pD3dApp->m_bFixUnitDirMode = TRUE;	// ���� ���� ���� ���
		}
		else if(bHide)
		{

			m_nRightWindowState = RIGHT_WINDOW_HIDING ;
			m_nRightWindowInfo = nWindow;
			m_bRightWindowModeChage = TRUE;
			g_pD3dApp->m_bChatMode = FALSE;
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MENU, g_pShuttleChild->m_vPos, FALSE);
		}
		else
		{
			m_nRightWindowInfo = nWindow;
		}
	}
	else if(m_nRightWindowInfo != RIGHT_WINDOW_WEAPON)
	{
		// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
		// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
		//g_INFCnt--;
		//if(g_INFCnt==0)
		if(g_pD3dApp->RemoveINFCnt() == 0)
		{
			g_pGameMain->m_bChangeMousePoint = FALSE;
		}		
		// end 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
		// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
		m_nRightWindowState = RIGHT_WINDOW_HIDING ;
		m_nRightWindowInfo = RIGHT_WINDOW_WEAPON;
		m_bRightWindowModeChage = TRUE;
		
		SetToolTip(0,0,NULL);
		SetItemInfo(0,0,0,0);
		
		g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MENU, g_pShuttleChild->m_vPos, FALSE);
	}
	
	// ���������� ������
	if(g_pD3dApp->m_dwGameState == _SHOP)
	{
		m_nLeftWindowInfo = LEFT_WINDOW_SHOP;
		m_nRightWindowState = RIGHT_WINDOW_HIDING ;
		m_bRightWindowModeChage = TRUE;
		SetToolTip(0,0,NULL);
		SetItemInfo(0,0,0,0);

		g_pGameMain->m_pInfWindow->m_nLeftWindowInfo = 0;
		return;
	}
	// ��Ʋ���� �ʱ�ȭ 
	g_pShuttleChild->MirrorTurnOrig();	
	// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
	g_pInterface->m_pToolTip->m_bToolTipState = FALSE;
	// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����

}
/*
void CINFGameMain::OnButtonClick(int nButton)
{
	FLOG( "CINFGameMain::OnButtonClick(int nButton)" );
	switch(nButton)
	{
	case 0:// info
		{
			RightWindowShow(TRUE, RIGHT_WINDOW_INFO);
		}
		break;
	case 1:// inven
		{
			LeftWindowShow(TRUE, LEFT_WINDOW_INVEN);

		}
		break;
	case 2:// party
		{
			LeftWindowShow(TRUE, LEFT_WINDOW_PARTY);
		}
		break;
	case 3:// trans
		{
			if(!m_pTrade->m_bTrading)
			{
				m_pInfWindow->AddMsgBox( "�ŷ��� ������ �Է��Ͻÿ�", _Q_TRADE_INPUT_NAME);
			}
			else
			{
				m_pInfWindow->AddMsgBox( "�ŷ��� ����Ͻðڽ��ϱ�?", _Q_TRADE_CANCEL);
			}
//			LeftWindowShow(TRUE, LEFT_WINDOW_TRANS);
		}
		break;
	case 4:// option
		{
			RightWindowShow(TRUE, RIGHT_WINDOW_OPTION);
		}
		break;
	}

}
*/


void CINFGameMain::SetToolTip(int x, int y, char* strToolTip)
{
	FLOG( "CINFGameMain::SetToolTip(int x, int y, char* strToolTip)" );
	if(strToolTip)
	{
		memset ( m_strToolTip , 0 , sizeof( m_strToolTip ) );

		// 2009. 05. 28 by ckPark ������Ʈ�� �޸� �Ѿ�� ���� üũ
		//strcpy(m_strToolTip, strToolTip);
		memset( m_strToolTip, 0, sizeof(m_strToolTip) );
		strncpy(m_strToolTip, strToolTip, 127);
		// end 2009. 05. 28 by ckPark ������Ʈ�� �޸� �Ѿ�� ���� üũ

		if(strlen(m_strToolTip)*6+x > g_pD3dApp->GetBackBufferDesc().Width)
		{
			x = g_pD3dApp->GetBackBufferDesc().Width - strlen(m_strToolTip)*6;
		}
	}
	else
	{
		m_strToolTip[0] = NULL;
	}
	m_ptToolTip.x = x;
	m_ptToolTip.y = y;
}


// 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
/****************************************************************
**
**	���� ���� ���� ����.
**
**	Create Info :	2010. 05. 03.	hsLee.
**
*****************************************************************/
void CINFGameMain :: SetToolTipEx ( int x , int y , char* pszToolTip , PRECT prcBound /*= NULL*/ )
{

	FLOG ( "CINFGameMain :: SetToolTipEx ( int x , int y , char* pszToolTip )" );

	if ( NULL == pszToolTip || pszToolTip[0] == 0 )
	{
		ResetToolTipEx();
	}
	else
	{
		if ( strcmp ( m_szSave_ToolTip , pszToolTip ) )
		{
			ResetToolTipEx();

			strncpy ( m_szSave_ToolTip , pszToolTip ,  min( strlen( pszToolTip ) , sizeof( m_szSave_ToolTip ) - 1 ) );

			//STRING_CULL( m_szSave_ToolTip , 1024 , &m_vecToolTip , m_pFontToolTip );
			StringCullingUserDataEx ( m_szSave_ToolTip , 1024 , &m_vecToolTip , m_pFontToolTip , TRUE );

			if ( m_vecToolTip.size() > 0 )
			{
				vector < string >::iterator it = m_vecToolTip.begin();

				for ( ; it != m_vecToolTip.end(); it++ )
				{
					m_iToolTipMaxWid = max ( m_iToolTipMaxWid , m_pFontToolTip->GetStringSize( (char*)it->c_str() ).cx );
				}
			}

			m_bRenderToolTipEx = TRUE;
		}
		else
		{
			m_bRenderToolTipEx = TRUE;
		}

		m_dwFrameToolTip[1] = m_dwFrameToolTip[0];

		if ( m_iToolTipMaxWid+x > g_pD3dApp->GetBackBufferDesc().Width )
			x = g_pD3dApp->GetBackBufferDesc().Width - m_iToolTipMaxWid;

		m_ptToolTipEx.x = x;
		m_ptToolTipEx.y	= y;

		if ( prcBound )
			m_rcToolTipEx = *prcBound;
	}

}


/******************************************************
**
**	���� ���� �ʱ�ȭ. ( ���� ���� �ɹ�. )
**
**	Create Info :	2010. 05. 03.	hsLee.
**
*******************************************************/
void CINFGameMain :: ResetToolTipEx ( void )
{

	m_vecToolTip.clear();

	memset ( m_szSave_ToolTip , 0x00 , sizeof( m_szSave_ToolTip ) );

	m_iToolTipMaxWid = 0;
	m_bRenderToolTipEx = FALSE;

	SetRectEmpty ( &m_rcToolTipEx );

}
// End. 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.


// 2013-04-11 by bhsohn �ΰ��� ����â ���� ���� ��þƮ �ý��� �˻�
//void CINFGameMain::SetItemInfo(LONGLONG nUniqueNumber, int nItemNum, int x, int y, int nItemCount/*=0*/, BOOL bShowMyEq/*=TRUE*/)
void CINFGameMain::SetItemInfo(LONGLONG nUniqueNumber, int nItemNum, int x, int y, int nItemCount/*=0*/, BOOL bShowMyEq/*=TRUE*/, 
							   int nLinkItem/*=0*/,  BOOL bArmorCollect /*FALSE*/, BOOL bInven /*FALSE*/) // 2013-06-10 by ssjung �Ƹ� �÷��� ���� ǥ��	
							   // 2013-06-26 by ssjung �κ��丮 �߰� ���� 
{
	FLOG( "CINFGameMain::SetItemInfo(LONGLONG nUniqueNumber, int nItemNum, int x, int y)" );
	if(nItemNum != 0)
	{
		ITEM *pITEM = g_pDatabase->GetServerItemInfo(nItemNum);
		if(pITEM == NULL)
		{
			// 2009-02-03 by bhsohn ���� ������ �� ����
			//m_pItemInfo->SetItemInfoNormal(NULL,0,0);			
			SetItemInfoNormal(NULL,0,0);			
			// end 2009-02-03 by bhsohn ���� ������ �� ����
			return;
		}

		if(nUniqueNumber != 0)
		{
			if(IS_SKILL_ITEM(pITEM->Kind) == FALSE)
			{
				CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( nUniqueNumber );
				if(pItemInfo)
				{
					// 2009-02-03 by bhsohn ���� ������ �� ����
					//m_pItemInfo->SetItemInfoUser( pItemInfo, x, y );
					SetItemInfoUser( pItemInfo, x, y, bShowMyEq,0,bInven); // 2013-04-11 by bhsohn �ΰ��� ����â ���� ���� ��þƮ �ý��� �˻�		 
					// 2013-06-26 by ssjung �κ��丮 �߰� ���� 
					// end 2009-02-03 by bhsohn ���� ������ �� ����
				}
			}
			else
			{
				// SKILL
//				ITEM* pSKILL = g_pShuttleChild->m_pSkill->FindItem( nItemNum );
//				if(pSKILL)
//				{
					// 2009-02-03 by bhsohn ���� ������ �� ����
					//m_pItemInfo->SetItemInfoNormal( pITEM, x, y, FALSE, nItemCount );
					SetItemInfoNormal( pITEM, x, y, FALSE, nItemCount, bShowMyEq,0, bArmorCollect);	// 2013-06-10 by ssjung �Ƹ� �÷��� ���� ǥ��
					// end 2009-02-03 by bhsohn ���� ������ �� ����
// 				}
			}
		}
		else
		{
//			if(pITEM)
//			{
				// 2009-02-03 by bhsohn ���� ������ �� ����
				//m_pItemInfo->SetItemInfoNormal( pITEM, x, y, TRUE, nItemCount );
				SetItemInfoNormal( pITEM, x, y, TRUE, nItemCount, bShowMyEq, nLinkItem,bArmorCollect);// 2013-06-10 by ssjung �Ƹ� �÷��� ���� ǥ��
				// end 2009-02-03 by bhsohn ���� ������ �� ����
//			}
		}
	}
	else
	{
		//m_pInfWindow->SetItemInfo(NULL,NULL,NULL,0,0);
		// 2009-02-03 by bhsohn ���� ������ �� ����
		//m_pItemInfo->SetItemInfoNormal(NULL,0,0);
		SetItemInfoNormal(NULL,0,0);
		// end 2009-02-03 by bhsohn ���� ������ �� ����
	}
}

// 2012-06-14 by isshin ���۹̸�����
void CINFGameMain::SetEnemyItemInfo(LONGLONG nUniqueNumber, int nItemNum, int x, int y, int nItemCount/*=0*/, BOOL bShowMyEq/*=TRUE*/)
{
	FLOG( "CINFGameMain::SetEnemyItemInfo(LONGLONG nUniqueNumber, int nItemNum, int x, int y)" );
	if(nItemNum != 0)
	{
		ITEM *pITEM = g_pDatabase->GetServerItemInfo(nItemNum);
		if(pITEM == NULL)
		{		
			SetItemInfoNormal(NULL,0,0);
			return;
		}
		
		if(nUniqueNumber != 0)
		{
			if(IS_SKILL_ITEM(pITEM->Kind) == FALSE)
			{
				CItemInfo* pItemInfo = g_pStoreData->FindItemInEnemyByUniqueNumber( nUniqueNumber );
				if(pItemInfo)
				{
					// 2013-06-21 by ssjung ���� ������������ �Ƹ��÷��� ������ ������ �ʵ��� ����
					pItemInfo->FixedTermShape.nStatLevel = 0;		
					pItemInfo->FixedTermShape.bActive = FALSE;
					// end 2013-06-21 by ssjung ���� ������������ �Ƹ��÷��� ������ ������ �ʵ��� ����

					SetItemInfoUser( pItemInfo, x, y, bShowMyEq);
				}
			}
			else
			{
				SetItemInfoNormal( pITEM, x, y, FALSE, nItemCount, bShowMyEq );				
			}
		}
		else
		{
			SetItemInfoNormal( pITEM, x, y, TRUE, nItemCount, bShowMyEq);			
		}
	}
	else
	{		
		SetItemInfoNormal(NULL,0,0);	
	}
}// end 2012-06-14 by isshin ���۹̸�����

// 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
void CINFGameMain::SetItemInfo1(CItemInfo* pItemInfo, int nItemNum, int x, int y, int nItemCount/*=0*/, BOOL bShowMyEq/*=TRUE*/)
{
	FLOG( "CINFGameMain::SetItemInfo(CItemInfo* pItemInfo, int nItemNum, int x, int y)" );
	if(nItemNum != 0)
	{
		ITEM *pITEM = g_pDatabase->GetServerItemInfo(nItemNum);
		if(pITEM == NULL)
		{
			SetItemInfoNormal(NULL,0,0);			
			return;
		}
		
		if(IS_SKILL_ITEM(pITEM->Kind) == FALSE)
		{
			if(pItemInfo)
			{
				SetItemInfoUser( pItemInfo, x, y, bShowMyEq);
			}
			else
			{
				SetItemInfoNormal( pITEM, x, y, FALSE, nItemCount, bShowMyEq );
			}
		}
		else
		{
			SetItemInfoNormal( pITEM, x, y, TRUE, nItemCount, bShowMyEq);
		}
	}
	else
	{
		SetItemInfoNormal(NULL,0,0);
	}
}
//end 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����

void CINFGameMain::ToggleHelpImage()
{
	FLOG( "CINFGameMain::ToggleHelpImage()" );
	m_bShowHelp = !m_bShowHelp;
	if(m_bShowHelp)
	{
		for(int i=0;i<HELP_NUM;i++)
		{
			util::del(m_pHelp[i]);
			char buf[64];
			wsprintf(buf, "help%02d", i);
			m_pHelp[i] = new CINFImageEx;
			DataHeader * pDataHeader = FindResource(buf);
			m_pHelp[i]->InitDeviceObjects( pDataHeader );
			m_pHelp[i]->RestoreDeviceObjects();
		}
	}
	else
	{
		for(int i=0;i<HELP_NUM;i++)
		{
			if(m_pHelp[i])
			{
				m_pHelp[i]->InvalidateDeviceObjects();
				m_pHelp[i]->DeleteDeviceObjects();
				util::del(m_pHelp[i]);
			}
		}

	}
}
void CINFGameMain::SetNotice(int index, int x, int y)
{
	if(m_pHelpDesk && m_pHelpDesk->m_nHelpDeskIndex != index)
	{
		m_pHelpDesk->SetHelpDeskBox( x, y, 400, index, TRUE, 10 );
		m_pHelpDesk->m_fHelpTextCheckTime = HELP_TEXT_CHECK_TIME;
	}
//	if(m_pNotice)
//	{
//		m_pNotice->SetNotice(strNotice);
//	}
}
void CINFGameMain::SetNotice(char* szString, int x, int y)
{
	if(m_pHelpDesk)
	{
		m_pHelpDesk->SetHelpDeskBox( x, y, 400, 0, FALSE, 10, szString );
		m_pHelpDesk->m_fHelpTextCheckTime = HELP_TEXT_CHECK_TIME;
	}
}

HRESULT CINFGameMain::SetResourceFile(char* szFileName)
{
	FLOG( "CINFGameMain::SetResourceFile(char* szFileName)" );
	util::del(m_pGameData);
	m_pGameData = new CGameData;
	m_pGameData->SetFile(szFileName, FALSE, NULL, 0);

	return S_OK;
}

DataHeader * CINFGameMain::FindResource(const char* szRcName)
{
	FLOG( "CINFGameMain::FindResource(char* szRcName)" );
	DataHeader* pHeader = NULL;
	if(m_pGameData)
	{
		pHeader = m_pGameData->Find(szRcName);
	}
	return pHeader;
}

// 2007-07-04 by bhsohn ���۷����� �߰�
DataHeader * CINFGameMain::FindResource_LoadOp(char* szRcName)
{	
	return g_pInterface->FindResource_LoadOp(szRcName);
}


void CINFGameMain::SetQuestLimitTime(int limitTime, int PlayTime, char* MissionName)
{	
	// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��	
	//m_nTimeSecond = limitTime * 60;	
	SetQuestTimeElapse(limitTime * 60);
// 2008-07-24 by dgwoo 8���� ����Ʈ���� Faqâ�� �ߴ� ���� ����.
//	wsprintf(m_strNPCName,"%s", MissionName);	

	if(PlayTime)
	{
		int resTime = (limitTime*60) - (g_pShuttleChild->m_myShuttleInfo.TotalPlayTime - PlayTime);
		// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��	
		//m_nTimeSecond = resTime;	
		SetQuestTimeElapse(resTime);
	}

	// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
	//m_nTimeLimitMissionOldTime = m_nTimeSecond;
	m_nTimeLimitMissionOldTime = (int)GetQuestTimeElapse();
	
	m_bQuestLimitTimeView = TRUE;	
}


CEnemyData * CINFGameMain::GetEnemyCharaterID(POINT pt)
{
	D3DXVECTOR2 vPos1 = D3DXVECTOR2(pt.x,pt.y);

	float fLength = 50.0f;
	map<INT,CEnemyData *>::iterator itEnemy = g_pD3dApp->m_pScene->m_mapEnemyList.begin();
	CEnemyData * pEnemy = NULL;
	while(itEnemy != g_pD3dApp->m_pScene->m_mapEnemyList.end())
	{
		if( itEnemy->second->m_nObjScreenW > 0)
		{
			D3DXVECTOR2 vPos2 = D3DXVECTOR2(itEnemy->second->m_nObjScreenX,itEnemy->second->m_nObjScreenY);
			float fLengthTemp = D3DXVec2Length(&(vPos1-vPos2));
			if(fLengthTemp < fLength)
			{
				fLength = fLengthTemp;
				pEnemy = itEnemy->second;
			}
		}
		itEnemy++;
	}

	return pEnemy;
}

void CINFGameMain::RenderPopUpWindowImage(int x, int y, int cx, int cy)
{
	//FLOG( "CINFGameMain::RenderPopUpWindowImage(int x, int y, int cx, int cy, int cstringLen)" );
	FLOG( "CINFGameMain::RenderPopUpWindowImage(int x, int y, int cx, int cy)" );

	m_pImgTextPopUp[0]->Move(x-7, y-2);
	m_pImgTextPopUp[0]->Render();

	m_pImgTextPopUp[1]->Move(x, y-2);
	m_pImgTextPopUp[1]->SetScale(cx, 1);
	m_pImgTextPopUp[1]->Render();

	m_pImgTextPopUp[2]->Move(x+cx, y-2);
	m_pImgTextPopUp[2]->Render();
}

/************************************************************
**
**	������ BG ���. ( Image, Round Box )
**
**	Create Info :	2010. 05. 03.	hsLee
**
*************************************************************/
void CINFGameMain :: RenderToolTipBg ( int ix , int iy , int iWid , int iHgt )
{

	if ( iWid <= 0 || iHgt <= 0 || NULL == m_pImgTextBg )
		return;

	FLOG( "CINFGameMain :: RenderToolTipBg ( int ix , int iy , int iWid , int iHgt )" );

	float fScly = .0f;
	float fOrgHgt = m_pImgTextBg->GetImgSize().y - 2;

	iWid += 7;
	
	if ( fOrgHgt <= .0f )
		return;

	fScly = (float)iHgt / fOrgHgt;

	if ( fScly <= 0.1f )
		return;

	float fPosx = (float)ix - 2.0f;
	float fPosy = (float)iy - 2.0f;

	m_pImgTextBg->Move ( fPosx , fPosy );
	m_pImgTextBg->SetScale ( (float)iWid , fScly );

	m_pImgTextBg->Render();

}

char *CINFGameMain::GetMapNameByIndex(int nMapIndex)
{
	return g_pDatabase->GetMapInfo(nMapIndex)->MapName;
}
void CINFGameMain::RenderRequestEnable(float fAniTime)
{
	DWORD dwColor = 0x00FFFFFF;
	DWORD dwAlpha;

	if(fAniTime < 0)
	{
		return;
	}
	else if(fAniTime <= REQUEST_ENABLE_TIME/2.0f)
	{
		dwAlpha = fAniTime*2.0f * 255;	
	}
	else
	{
		dwAlpha = (2.0f - fAniTime*2.0f) * 255;	
	}

	dwAlpha = dwAlpha << 24;
	dwColor |= dwAlpha;

	m_pRequestEnableBack->Move((g_pD3dApp->GetBackBufferDesc().Width - REQUEST_ENABLE_BOX_WIDTH)/2,
								(g_pD3dApp->GetBackBufferDesc().Height - REQUEST_ENABLE_BOX_HEIGHT)/2);
	m_pRequestEnableBack->Render();
	m_pRequestEnableTriangle->SetColor(dwColor);
	m_pRequestEnableTriangle->Move((g_pD3dApp->GetBackBufferDesc().Width - REQUEST_ENABLE_BOX_WIDTH)/2,
									(g_pD3dApp->GetBackBufferDesc().Height - REQUEST_ENABLE_BOX_HEIGHT)/2);
	m_pRequestEnableTriangle->Render();
}

void CINFGameMain::SetMentMessage(int x, int y, char *strMent)
{	
	// ��Ʈ ���� ������
	m_pFontDrawMent->DrawText(x,y,GUI_FONT_COLOR,strMent);
}
void CINFGameMain::SetGuildName(int x, int y, char *strGuild, DWORD dwFontColor)
{
	m_pFontDrawMent->DrawText(x, y, dwFontColor, strGuild);
}
// 2013-03-06 by bhsohn ���� ���� �ý���
int CINFGameMain::GetMentMessageSize(char *strMent)
{	
	// ��Ʈ ���� ������	
	return m_pFontDrawMent->GetStringSize(strMent).cx;
}
// END 2013-03-06 by bhsohn ���� ���� �ý���

void CINFGameMain::RenderQSlotIcon()
{
	CINFIcon* pIconInfo = m_pIcon;

	// 2005-11-28 by ispark, ���⼭ IconName�� SourceIndex�̴�.
	pIconInfo->SetIcon(m_pQuickSlot->m_pQSlotInfo[m_pQuickSlot->m_nCurrentTab][m_pQuickSlot->m_nSelectSlotNumber].IconName, 
						m_nQSlotPosX,
						m_nQSlotPosY, 1.0f);
	pIconInfo->Render();
}

DWORD CINFGameMain::GetCurrentColor(float fTime, DWORD dwType, float fTotal, float fDelay)
{	// fTime ��ü �ð�, dwType ����Ÿ��, fTotal ���̵� �ξƿ� Ÿ��, fDelay ���� �ð�
	DWORD dwColor = 0x00FFFFFF;
	DWORD dwAlpha;

	if(dwType == ALPHA_WAVE)
	{// ��������
		float fAlpha;
		fAlpha =  (fTime - (((int)(fTime/fTotal))*fTotal))/fTotal;
		if(fAlpha >= 0.5f)
		{
			dwAlpha = 255 * (2.0f - fAlpha*2.0f);
		}
		else
		{
			dwAlpha = 255 * (2.0f - (1.0f - fAlpha)*2.0f);
		}
	}
	else if(dwType == ALPHA_DELAY_WAVE)
	{
		float fAlpha;
		fTime = fTime - (((int)(fTime/fTotal))*fTotal);
		float fGap = (fTotal - fDelay)/2.0f;	// fGap + fDelay + fGap = fTotal
		
		if(fTime < fGap)
		{
			// 2006-07-18 by dgwoo ���� ��������.
			fAlpha =  fTime / fGap;
			dwAlpha = 255 * fAlpha;
		}
		else if(fTime >= fGap && fTime <= fGap + fDelay)
		{
			// 2006-07-18 by dgwoo ������ �۾� ����
			dwAlpha = 255;
		}
		else
		{
			// 2006-07-18 by dgwoo ���� �������.
			fAlpha =  (fTime - fDelay -fGap) / fGap;
			dwAlpha = 255 * (1.0f - fAlpha);			
		}

//		fAlpha =  (fTime - (((int)(fTime/fTotal))*fTotal))/fTotal;
//		if(fAlpha >= 0.5f)
//		{
//			dwAlpha = 255 * (2.0f - fAlpha*2.0f);
//		}
//		else
//		{
//			dwAlpha = 255 * (2.0f - (1.0f - fAlpha)*2.0f);
//		}		
	}
	else if(dwType == ALPHA_FADE_IN)
	{
		if(fTime < 0.0f)
		{
			dwAlpha = 0;
		}
		else if(fTime < fTotal)
		{
			dwAlpha = 255 * (fTime/fTotal);
		}
		else if(fTime > fTotal)
		{
			dwAlpha = 255;
		}
	}
	else if(dwType == ALPHA_FADE_OUT)
	{
		if(fTime < 0.0f)
		{
			dwAlpha = 255;
		}
		else if(fTime < fTotal)
		{
			dwAlpha = 255 * (1.0f - (fTime/fTotal));
		}
		else if(fTime > fTotal)
		{
			dwAlpha = 0;
		}
	}

	dwAlpha = dwAlpha << 24;
	dwColor |= dwAlpha;
	return dwColor;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		ispark
/// \date		2005-07-20 ~ 2005-07-20
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderToolTip()
{
	// 2006-03-06 by ispark, ���� ���� ��������
	if(m_strToolTip[0])
	{
		int sizeX = m_pFontToolTip->GetStringSize(m_strToolTip).cx;
		RenderPopUpWindowImage(m_ptToolTip.x+10, m_ptToolTip.y-15, sizeX, 1);
//		RenderPopUpWindowImage(m_ptToolTip.x+10, m_ptToolTip.y-15, strlen(m_strToolTip)*6.5, 1);
		m_pFontToolTip->DrawText(m_ptToolTip.x+10, m_ptToolTip.y-FONTTOOLTIP_Y, GUI_FONT_COLOR,m_strToolTip,0L);
	}
}


// 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
/**********************************************************************
**
**	���� ���. (���� ����.)
**
**	Create Info :	2010. 05. 03.	hsLee.
**
***********************************************************************/
void CINFGameMain :: RenderToolTipEx( void )
{

	if ( TRUE != m_bRenderToolTipEx )
	{
		if ( m_vecToolTip.size() > 0 && m_dwFrameToolTip[0] - m_dwFrameToolTip[1] > 30 )
			ResetToolTipEx();

		return;
	}

	if ( m_vecToolTip.size() > 0 )
	{
		RenderToolTipBg (m_ptToolTipEx.x+10 , m_ptToolTipEx.y-15 , m_iToolTipMaxWid , (int)(m_vecToolTip.size() * m_pFontToolTip->GetStringSize( (char*)m_vecToolTip[0].c_str() ).cy) );
		
		vector < string >::iterator it = m_vecToolTip.begin();

		int iCnt = 0;
		for ( ; it != m_vecToolTip.end(); it++ )
		{
			m_pFontToolTip->DrawText(m_ptToolTipEx.x+10, m_ptToolTipEx.y-FONTTOOLTIP_Y + m_pFontToolTip->GetStringSize( (char*)it->c_str() ).cy * iCnt , GUI_FONT_COLOR , (char*)it->c_str() , 0L );
			iCnt++;
		}
	}

	if ( !IsRectEmpty ( &m_rcToolTipEx ) )
	{
		POINT pt;
			GetCursorPos( &pt );
			ScreenToClient ( g_pD3dApp->GetHwnd() , &pt );

		if ( !PtInRect ( &m_rcToolTipEx , pt ) )
			m_bRenderToolTipEx = FALSE;
	}

	if ( m_dwFrameToolTip[0] - m_dwFrameToolTip[1] > 10 )
		m_bRenderToolTipEx = FALSE;

	m_dwFrameToolTip[0]++;


}
// End. 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.


///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFGameMain::InitShowWindow()
/// \brief		ȭ�鿡 ������ ������â �⺻���� �ٲٴ� �Լ�( �ʱ�ȭ , ������â �ʱ�ȭ.)
/// \author		ispark
/// \date		2005-08-05 ~ 2005-08-05
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::InitShowWindow()
{
	// ������ â
	RightWindowShow(FALSE,m_nRightWindowInfo);
//	RightWindowShow(FALSE, RIGHT_WINDOW_OPTION);

	// ���� â
	LeftWindowShow(FALSE,m_nLeftWindowInfo);
	
	// F1Ű ������̸� �����.
	if(m_bShowHelp == TRUE)
	{
		ToggleHelpImage();
	}

	//m_pMiniMap->SetZoomState(TRUE);
	m_bQuestView = FALSE;
	m_pOtherCharInfo->m_bRenderInfo = FALSE;
	g_pGameMain->m_pChat->m_bMenuListUse = FALSE;
	m_bMenuListFlag = FALSE;
	
	// 2009-02-03 by bhsohn ���� ������ �� ����
	//m_pItemInfo->ShowItemInfo(FALSE);
	ShowItemInfo(FALSE);
	// end 2009-02-03 by bhsohn ���� ������ �� ����

	g_pD3dApp->m_pShuttleChild->m_bMouseLock = FALSE;
	m_pUnitState->OffState( INF_US_LOCK_MASK );

	// 2008-01-17 by dgwoo �� �̵��� â �ʱ�ȭ.
	g_pGameMain->m_pCouponWindow->SetShow(FALSE);			// ����â �ʱ�ȭ.


	// 2007-06-12 by bhsohn �̼� �������̽� ������
//	if(g_pTutorial->GetTutorialEd() == FALSE)			// 2005-10-17 by ispark ��� Ʃ�丮���� ���� ���¶�� �̼�â�� ������ �ȉ´?
//		m_pMissionInfo->MissionProcFlag(FALSE);
	// ��� Ʃ�丮���� ���� ���¶�� �̼�â�� ������ �ȉ´?
	if(g_pTutorial->GetTutorialEd() == FALSE)			
		ShowMissionTreeWnd(FALSE, FALSE);

	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	BOOL bClick = FALSE;
	if(m_pInven->IsShowInven())
	{
		bClick = TRUE;
	}	

	// 2009. 09. 24 by jskim �ʵ� â�� ĳ�� ������
	//m_pInven->ShowInven(NULL, NULL, bClick); // �����ִٸ� �ݴ´�.
	//m_pCharacterInfo->ShowCharacterInfoWnd(FALSE, NULL);
	// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��	
	if(g_pInterface->m_pCityBase-> GetCurrentEnterBuildingIndex()!=FIELD_STORE_SHOP_BUILDING_INDEX)
	{
		m_pInven->ShowInven(NULL, NULL, bClick); // �����ִٸ� �ݴ´�.
		m_pCharacterInfo->ShowCharacterInfoWnd(FALSE, NULL);

		// 2013-03-18 by bhsohn ���丮 ���� �߰�
		// B�������� â�� ����
		OnClickItemMixWnd(FALSE, 0, 0);
		// END 2013-03-18 by bhsohn ���丮 ���� �߰�

		// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
		OnClickArmorCollectionWnd(FALSE, 0, 0);
		// END 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
	}	

	structInvenPosInfo tempInfo = m_pInven->GetInvenPosInfo();
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	tempInfo.ptItemIvenPos.x = g_pD3dApp->GetBackBufferDesc().Width/2 - m_pInven->GetBkSize().x / 2;
	tempInfo.ptItemIvenPos.y = g_pD3dApp->GetBackBufferDesc().Height/2 - m_pInven->GetBkSize().y / 2;
#else	  
	tempInfo.ptItemIvenPos.x = INVEN_ITEM_START_X;
	tempInfo.ptItemIvenPos.y = INVEN_ITEM_START_Y;
#endif
	tempInfo.ptEqIvenPos.x = INVEN_EQ_START_X;
	tempInfo.ptEqIvenPos.y = INVEN_EQ_START_Y;
	m_pInven->SetInvenPosInfo(&tempInfo);
	//end 2009. 09. 24 by jskim �ʵ� â�� ĳ�� ������


	// 2008-10-20 by bhsohn FAQ ��ü ���¿����� �Ⱥ��̰� ����
	m_bFAQProsFlag			= FALSE;
	// end 2008-10-20 by bhsohn FAQ ��ü ���¿����� �Ⱥ��̰� ����

	// 2008-11-06 by bhsohn ���콺 ���α� ��� ����
	g_pD3dApp->RefreshMouseMode();
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFGameMain::CheckKeyUseState(int nFlage, BOOL bAllUse, BOOL bOneUse)
/// \brief		Ű ��� üũ, �ι�° BOOL���� üũ ��� ���, ����° BOOL���� �������� ��� ��� 
/// \author		ispark
/// \date		2005-08-09 ~ 2005-08-09
/// \warning	
///
/// \param		
/// \return		BOOL
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::CheckKeyUseState(int nwParamFlage, int nlParamFlage, BOOL bUse, BOOL bOneUse)
{
	// Ű�� ���� �����
	// 2005-04-07 by jschoi - Tutorial
	// 2005-08-04 by ispark - �������϶� �϶� Ű�� ���´�.
	// 2005-08-08 by ispark - �����ÿ��� ���

	if(bUse == TRUE)
	{
		// wParamŰ
		switch(nwParamFlage) 
		{
		case VK_ESCAPE:

			if(g_pShuttleChild->WarpSkipInOutAirPort())
				return TRUE;

			// 2010. 05. 27 by jskim �ó׸� ���� ī�޶� ����
			if ( g_pShuttleChild->IsShowCinema() )
			{
				// 2010. 07. 27 by hsLee ���Ǵ�Ƽ 2�� ���� ��� �ó׸� ���� ��ŵ ó��.
				g_pInterface->m_pInfinity->SendPacket_SkipEndingCinema();

				//g_pShuttleChild->DeletePattern();
				return TRUE;
			}

			//end 2010. 05. 27 by jskim �ó׸� ���� ī�޶� ����
			if(	// 2007-07-10 by dgwoo Ʃ�丮�� ��忡���� escŰ�� �԰��Ѵ�.
				g_pTutorial->IsTutorialMode() == FALSE && 
				!g_pShuttleChild->GetIsUseInterface())
//				(g_pD3dApp->m_bCharacter == FALSE && 
//				 (g_pShuttleChild->m_bUnitStop == FALSE && g_pShuttleChild->m_bLandedMove == FALSE)))
				 return TRUE;
			
			// 2008-03-04 by bhsohn �������� ��������� ���ߴ� ����ó��
			// �����忡�� esc�� ���´�
			if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind)
				&&(g_pShuttleChild->m_bAttackMode == _SIEGE))
			{
				return TRUE;
			}

			break;

		case VK_F1:
			if(g_pTutorial->IsTutorialMode() == TRUE)
				return TRUE;
			break;

		case VK_F2:
			if(g_pTutorial->IsTutorialMode() == TRUE)
				return TRUE;
			break;

		case VK_F3:	// PVP
			if(g_pTutorial->IsTutorialMode() == TRUE)
				return TRUE;

			if(g_pD3dApp->m_bBazaar)			// 2006-07-25 by ispark, ����ʿ����� PVP ����� �ʱ�
			{
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_060802_0002,COLOR_ERROR);// "���� �ʿ����� ��� �� �� �����ϴ�."
				return TRUE;
			}
			break;

		case VK_F5:
			if(g_pTutorial->IsTutorialMode() == TRUE || 
				!g_pShuttleChild->GetIsUseInterface())
				 return TRUE;
			break;

		case VK_F6:
			if(g_pTutorial->IsTutorialMode() == TRUE || 
				!g_pShuttleChild->GetIsUseInterface())
				 return TRUE;
			break;

		case VK_F7:
			if(g_pTutorial->IsTutorialMode() == TRUE || 
				!g_pShuttleChild->GetIsUseInterface())
				 return TRUE;
			break;

		case VK_F8:	// �ŷ�
			if(g_pTutorial->IsTutorialMode() == TRUE || 
				!g_pShuttleChild->GetIsUseInterface())
				return TRUE;
			
			if(g_pD3dApp->m_bBazaar)			// 2006-07-25 by ispark, ����ʿ����� PVP ����� �ʱ�
			{
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_060802_0002,COLOR_ERROR);// "���� �ʿ����� ��� �� �� �����ϴ�."
				return TRUE;
			}
			break;

		case VK_F9:
			if(g_pTutorial->IsTutorialMode() == TRUE || 
				!g_pShuttleChild->GetIsUseInterface())
				 return TRUE;
			break;

		case VK_TAB:
			break;
		}
			
		// lParamŰ
		switch(nlParamFlage)
		{
		case WM_KEYDOWN_LPARAM_I:
		case WM_KEYDOWN_LPARAM_V:
			if(g_pTutorial->IsTutorialMode() == TRUE || 
				!g_pShuttleChild->GetIsUseInterface() ||
				 m_bVOIPFlag == TRUE)
				 return TRUE;
			break;
		case WM_KEYDOWN_LPARAM_P:
			if(g_pTutorial->IsTutorialMode() == TRUE || 
				!g_pShuttleChild->GetIsUseInterface() ||
				 m_bVOIPFlag == TRUE ||
				 g_pD3dApp->m_bBazaar)		// 2006-07-21 by ispark, ����ʿ����� �̼�â ����� �ʱ�
				 return TRUE;
			break;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		��ȿȭ ���� ���� �Լ�( ó�� ���μ����� �������κп� ��ġ )
///				�Ŀ� �����Ŀ� �ٽ� �ۼ�
/// \author		by ydkim
/// \date		2005-08-16 
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::InvalidWndRect(int x, int y, int nSizeW, int nSizeH)
{


}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�������� �������� ������ ����
///
/// \author		by ydkim
/// \date		2005-12-1
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::ChangeItemByShop(int nItemNum, int nUnitColor)
{
	ITEM *item = NULL;
	item = g_pDatabase->GetServerItemInfo(nItemNum);
	if(item == NULL)
		return;

	ITEM_GENERAL *pITEMG = NULL;
	CItemInfo *pItemInfo = NULL;
	// �Ƹ��� ��� �ٸ��� ǥ���Ѵ�.
//	if(ITEMKIND_DEFENSE == item->Kind)
//	{
//	}
#ifdef _REWORKED_COLORSHOP
	if (IS_PRIMARY_WEAPON(item->Kind) || IS_SECONDARY_WEAPON(item->Kind) || ITEMKIND_DEFENSE == item->Kind || ITEMKIND_COLOR_ITEM == item->Kind)
#else
	if(IS_PRIMARY_WEAPON(item->Kind) || IS_SECONDARY_WEAPON(item->Kind) || ITEMKIND_DEFENSE == item->Kind)
#endif
	{		
#ifdef _REWORKED_COLORSHOP
		if (item->ItemNum == COLOR_RESET_ITEMNUM)
			return;
#endif
		// �������� �������� �����غ��� ���� �κ�
		pITEMG							= new ITEM_GENERAL;
		pITEMG->Wear					= WEAR_ATTACHED;
		pITEMG->CurrentCount			= (IS_CHARGABLE_ITEM(item->Kind)?item->Charging:1);

		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		//pITEMG->ScarcityNumber			= 0;
		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

		pITEMG->NumOfEnchants			= 0;
		if (ITEMKIND_COLOR_ITEM == item->Kind)
		{
			//Simulate Armor
			pITEMG->ColorCode = item->SourceIndex;
			pITEMG->ShapeItemNum = item->SourceIndex;
			pITEMG->Kind = ITEMKIND_DEFENSE;
		}
		else
		{
			pITEMG->ColorCode = 0;
		}
		pITEMG->UsingTimeStamp			= ITEM_NOT_USING;
		pITEMG->UsingStartTime.Reset();		
		pITEMG->ItemInfo				= item;
		if (ITEMKIND_COLOR_ITEM != item->Kind)
			pITEMG->Kind					= item->Kind;
		pITEMG->ItemNum					= item->ItemNum;
		pITEMG->UniqueNumber			= 0;	
		pITEMG->ItemWindowIndex			= POS_ITEMWINDOW_OFFSET;
		
		pItemInfo = new CItemInfo((ITEM_GENERAL*)pITEMG);		
		g_pStoreData->UpdateWearItemData( pItemInfo, TRUE );

		if(ITEMKIND_DEFENSE == item->Kind)
		{
			g_pShuttleChild->SetInvenAmorColor(0);					// 2006-04-08 by ispark, ������ ������ �⺻ ����� ����
		}
	}
	else if(nUnitColor != -1)
	{
		// Į�� �������� Į���� �� Į�� �ٲܶ�.
		// 2006-02-17 by ispark
//		g_pD3dApp->SetUnitArmorColorNum(nUnitColor);
		g_pShuttleChild->SetInvenAmorColor(nUnitColor);
		return;
	}
	else
	{
		return;
	}
	
	//////////////////////////////////////////////////////////////////////////
	// ����� 1��, 2�� �Ƹ� ������ ���� ����
	// ���� ���밡�� �������� ����� ���⼭ ���� �� ���� (�����غ���)
	// ���� ��������� ���� ����
	if(IS_PRIMARY_WEAPON(pItemInfo->Kind) && m_pItemInfoWear[POS_PROWOUT])
	{	// 1�� ���� ����
		util::del( m_pItemInfoWear[POS_PROWOUT]);
		m_pItemInfoWear[POS_PROWOUT] = NULL;
		util::del( m_pITEMG[POS_PROWOUT]);
		m_pITEMG[POS_PROWOUT] = NULL;

		m_pITEMG[POS_PROWOUT] = pITEMG;
		m_pItemInfoWear[POS_PROWOUT] = pItemInfo;
	}
	else if(IS_SECONDARY_WEAPON(pItemInfo->Kind) && m_pItemInfoWear[POS_WINGOUT])
	{
		// 2�� ���� ����
		util::del( m_pItemInfoWear[POS_WINGOUT]);
		m_pItemInfoWear[POS_WINGOUT] = NULL;
		util::del( m_pITEMG[POS_WINGOUT]);
		m_pITEMG[POS_WINGOUT] = NULL;

		m_pITEMG[POS_WINGOUT] = pITEMG;
		m_pItemInfoWear[POS_WINGOUT] = pItemInfo;
	}
	else if(ITEMKIND_DEFENSE == pItemInfo->Kind)
	{
		// �Ƹ� ���� ����
		util::del( m_pItemInfoWear[POS_CENTER]);
		m_pItemInfoWear[POS_CENTER] = NULL;
		util::del( m_pITEMG[POS_CENTER]);
		m_pITEMG[POS_CENTER] = NULL;

		m_pITEMG[POS_CENTER] = pITEMG;
		m_pItemInfoWear[POS_CENTER] = pItemInfo;
	}
	//
	//////////////////////////////////////////////////////////////////////////	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���� �����ϰ� �ִ� ������ ���� ���
///				��� ��Ʈ(m_nItemSourceNum)
/// \author		by ydkim
/// \date		2005-12-1
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::BackUpWearItem()
{
	// ���� ���Խ� ������ ���� ���
	// FindItemInInventoryByItemNum( INT nItemNum );	
	CItemInfo* pTempItem = NULL;

	for(int i=0; i<SIZE_MAX_POS; i++)
	{
		pTempItem = g_pStoreData->FindItemInInventoryByWindowPos( i );
		if(pTempItem)
		{
			// 2006-08-24 by ispark, ����ũ �ѹ��� ����
//			m_nItemSourceNum[i]	= pTempItem->ItemNum;
			m_nItemSourceNum[i]	= pTempItem->UniqueNumber;

			if(i == POS_CENTER)
			{
				m_nArmorColor = max(1, pTempItem->ColorCode%100);				
//				g_pD3dApp->SetUnitArmorColorNum(m_nArmorColor);			// 2006-02-17 by ispark
			}
		}
	}

	m_bUseShopItem = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���� ��������� ���� 
///				����(m_pItemInfoWear, m_pITEMG)
/// \author		by ydkim
/// \date		2005-12-5
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::ResetWearItem(int nPos)
{
	if(nPos == -1)
{
	for(int i=0; i<SIZE_MAX_POS; i++)
	{
		util::del( m_pItemInfoWear[i]);
		m_pItemInfoWear[i] = NULL;
		util::del( m_pITEMG[i]);
		m_pITEMG[i] = NULL;
		m_nItemSourceNum[i] = 0;
		m_nArmorColor = 0;
		}
	}
	else
	{
		util::del( m_pItemInfoWear[nPos]);
		m_pItemInfoWear[nPos] = NULL;
		util::del( m_pITEMG[nPos]);
		m_pITEMG[nPos] = NULL;
		m_nItemSourceNum[nPos] = 0;
		m_nArmorColor = 0;
		
	}
}

void CINFGameMain::TickDrawWindowInfo()
{
	// 2005-04-29 by ydkim ������ �����ٰ��ΰ�?
//	if(TRUE == g_pTutorial->GetShowHelpDesk() && TRUE == IS_CITY_MAP_INDEX(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) )
	if(TRUE == g_pTutorial->GetShowHelpDesk())
	{		
		g_pGameMain->InitHelpSystem(TRUE);
		g_pTutorial->SetShowHelpDesk(FALSE);
	}
	
	m_nLeftWindowY = DEAULT_WINDOW_POS_Y - m_nLeftWindowScaleSize/2;
	if(m_nLeftWindowY < SIZE_ROLL_Y )
		m_nLeftWindowY = SIZE_ROLL_Y;
	if(m_pInfWindow->m_bLeftWindow)
	{
		m_nLeftWindowY = GetPositionInvenScreenMode();
	}
	else
	{
		if(m_nLeftWindowY > LEFT_WINDOW_MAX_Y-SIZE_WEAPON_Y)
			m_nLeftWindowY = LEFT_WINDOW_MAX_Y-SIZE_WEAPON_Y;
	}
	m_nRightWindowY = DEAULT_WINDOW_POS_Y - m_nRightWindowScaleSize/2;
	if(m_nRightWindowY < SIZE_ROLL_Y )
		m_nRightWindowY = SIZE_ROLL_Y;
	if(m_pInfWindow->m_bRightWindow)
	{
// 2007-12-22 by dgwoo â��� ���� (m_nLeftWindowY �� ���� Y���� ������ �Ѵ�.)
//		if(m_nRightWindowY > RIGHT_WINDOW_MAX_Y-SIZE_NORMAL_WINDOW_Y)
//			m_nRightWindowY = RIGHT_WINDOW_MAX_Y-SIZE_NORMAL_WINDOW_Y;
		m_nRightWindowY = GetPositionInvenScreenMode();
	}
	else
	{
		if(m_nRightWindowY > RIGHT_WINDOW_MAX_Y-SIZE_WEAPON_Y)
			m_nRightWindowY = RIGHT_WINDOW_MAX_Y-SIZE_WEAPON_Y;
	}
	
	if( g_pD3dApp->m_dwGameState == _CITY ||
		g_pD3dApp->m_dwGameState == _SHOP)
	{
		if(!g_pInterface->m_pCityBase->GetCurrentBuildingNPC())
		{
			if(m_bLeftWindowModeChage)
			{
				m_bLeftWindowModeChage = ChangeLeftWindowMode();
			}
			if(m_bRightWindowModeChage)
			{
				m_bRightWindowModeChage = ChangeRightWindowMode();
			}
		}
	}
	else
	{
		if(m_bLeftWindowModeChage)
		{
			m_bLeftWindowModeChage = ChangeLeftWindowMode();
		}
		if(m_bRightWindowModeChage)
		{
			m_bRightWindowModeChage = ChangeRightWindowMode();
		}
		if(m_pMiniMap)
			m_pMiniMap->Tick();
	}
}

void CINFGameMain::ProcessAltiMeter(float fMinHeight, float fMaxHeight, float fMyPosHeight)
{
	//////////////////////////////////////////////////////////////////////////
	// ydkim 05.12.13
	// ���� ������ �����̿��� ���� ������ �ְ� ���̷� �����Ѵ�
	// ���������� �������� �̹������� �����κ� ���κк��� �����Ѵ�
	// ���� �̹��� ��ü�� ������ �̹��� ���鵵 ���� ������ �ʿ��Ѵ�
	//////////////////////////////////////////////////////////////////////////

	float fGageGabBottom		= 23.0f;										// ������ �̹��� ���� (�Ʒ�)
	float fAltitudeApplyMin		= fMinHeight;									// �������� ���� 
	float fAltitudeApplyMax		= fMaxHeight+fAltitudeApplyMin;					// �ְ���� ����
	float fAltitudeApplyImgH	= m_ptGageBack.y - fGageGabBottom+9;			// �̹��� ����
	float fAltitudeApplyMyPos	= fMyPosHeight;									// ����ġ
	
	float Temp  = fAltitudeApplyMax/fMyPosHeight;
	if(Temp<=0) Temp = fAltitudeApplyMax;
	Temp = fAltitudeApplyImgH-(fAltitudeApplyImgH/Temp);

	RenderAltiMeter((int)GAMEMAIN_ALTIMETER_X, (int)GAMEMAIN_ALTIMETER_Y, (int)Temp);
}

void CINFGameMain::RenderAltiMeter(int x, int y, int nPos)
{
	m_pAltiMeterGage->Move(x, y);
	m_pAltiMeterGage->Render();

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pAltiMeterPin->Move(x - ( m_pAltiMeterPin->GetImgSize().x - m_pAltiMeterGage->GetImgSize().x ) /2, y+nPos);
#else			
	m_pAltiMeterPin->Move(x-5, y+nPos);
#endif
	m_pAltiMeterPin->Render();
}


void CINFGameMain::DrawSignBoardString()
{
	if(m_pCityBoard)
		m_pCityBoard->DrawSignBoardString();
}

void CINFGameMain::InitCityBoard(int nMapNumber)
{
	if(m_pCityBoard)
	{
		m_pCityBoard->InitDeviceObjects(nMapNumber);
		m_pCityBoard->RestoreDeviceObjects();
	}
}

void CINFGameMain::InitChangeInfluenceBoard()
{
	if(m_pCityBoard)
	{
		m_pCityBoard->DelAllString();
		InitCityBoard(g_pGround->m_nMapNumber);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CInterface::SetSelectItem(INVEN_DISPLAY_INFO *pDisplayInfo, POINT pt, BYTE byType)
/// \brief		���� ������
/// \author		ispark
/// \date		2006-07-26 ~ 2006-07-26
/// \warning	
///
/// \param		
/// \return		TRUE : �� ������ �� �ٸ� ������    FALSE : ���ų� ����
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetSelectItem(INVEN_DISPLAY_INFO *pDisplayInfo, POINT pt, BYTE byType)
{
	FLOG( "CINFInven::SetSelectItem(INVEN_DISPLAY_INFO* pDisplayInfo)" );
	
	if(pDisplayInfo && m_stSelectItem.pSelectItem)
	{
		return;
	}

	if(pDisplayInfo)
	{
		m_stSelectItem.pSelectIcon = m_pIcon->FindIcon(pDisplayInfo->IconName);
		m_stSelectItem.pSelectItem = pDisplayInfo;
		m_stSelectItem.bySelectType = byType;
		m_stSelectItem.ptIcon = pt;

		UpdateIconSelectItem(byType);

		// set tooltip
		// 2006-08-22 by dgwoo ���� ����.
//        POINT pt;
//        GetCursorPos( &pt );
//        ScreenToClient( g_pD3dApp->GetHwnd(), &pt );
//		CheckMouseReverse(&pt);
//		SetToolTip(pt.x, pt.y, pDisplayInfo->Name);
	}
	else
	{
		m_stSelectItem.pSelectItem = NULL;
		m_stSelectItem.pSelectIcon = NULL;
		m_stSelectItem.bySelectType = ITEM_NOT_POS;
		m_stSelectItem.ptIcon.x = 0;
		m_stSelectItem.ptIcon.y = 0;

		// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
		// 2006-07-27 by ispark, �κ��丮 ��ư �ʱ�ȭ
		//m_pInven->m_bSelectItem = 0;

		// 2007-03-02 by bhsohn ���� ���� �߰� ����
		ClearMultiSelectItem();
	}

	return;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void ClearMultiSelectItem()
/// \brief		���� ������
/// \author		// 2007-03-02 by bhsohn ���� ���� �߰� ����
/// \date		2007-03-05 ~ 2007-03-05
/// \warning	
///
/// \param		
/// \return		TRUE : �� ������ �� �ٸ� ������    FALSE : ���ų� ����
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::ClearMultiSelectItem()
{
	int i = 0;
	m_nMultiSelCnt = 0;	
	for(i = 0; i < MAX_MULTI_SEL;i++)
	{
		m_stMultiSelectItem[i].pSelectItem = NULL;
		m_stMultiSelectItem[i].pSelectIcon = NULL;
		m_stMultiSelectItem[i].bySelectType = ITEM_NOT_POS;
		m_stMultiSelectItem[i].ptIcon.x = 0;
		m_stMultiSelectItem[i].ptIcon.y = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMain::RenderSelectItem()
/// \brief		���õ� ������ ����
/// \author		ispark
/// \date		2006-07-26 ~ 2006-07-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderSelectItem()
{
	// 2007-03-02 by bhsohn ���� ���� �߰� ����
	if(m_nMultiSelCnt > 0) 
	{
		RenderMultiSelectItem();
		return;		
	}
	// end 2007-03-02 by bhsohn ���� ���� �߰� ����

	if(m_stSelectItem.pSelectIcon)
	{
        POINT ptCursor;
        GetCursorPos( &ptCursor );
        ScreenToClient( g_pD3dApp->GetHwnd(), &ptCursor );
		CheckMouseReverse(&ptCursor);		

		m_stSelectItem.pSelectIcon->Scaling(1.0f, 1.0f);
		m_stSelectItem.pSelectIcon->Move(ptCursor.x - m_stSelectItem.ptIcon.x, ptCursor.y - m_stSelectItem.ptIcon.y);
		m_stSelectItem.pSelectIcon->Render();
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMain::RenderMultiSelectItem()
/// \brief		���� ������ ������ 
/// \author		// 2007-03-02 by bhsohn ���� ���� �߰� ����
/// \date		2007-03-02 ~ 2007-03-02
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderMultiSelectItem()
{	
	POINT ptCursor;
    GetCursorPos( &ptCursor );
    ScreenToClient( g_pD3dApp->GetHwnd(), &ptCursor );
	CheckMouseReverse(&ptCursor);	
	int nCnt = 0;
	float fXStart, fYStart;
	float fX, fY;
	fX = fY = 0;
	fXStart = m_stMultiSelectItem[0].ptIcon.x;
	fYStart = m_stMultiSelectItem[0].ptIcon.x;
	for(nCnt = MAX_MULTI_SEL-1;nCnt >= 0 ;nCnt--)
	{
		if(NULL == m_stMultiSelectItem[nCnt].pSelectIcon)
		{
			continue;
		}
		fX = ptCursor.x - fXStart + nCnt*5;
		fY = ptCursor.y - fYStart + nCnt*5;
		m_stMultiSelectItem[nCnt].pSelectIcon->Scaling(1.0f, 1.0f);
		m_stMultiSelectItem[nCnt].pSelectIcon->Move(fX, fY);
		m_stMultiSelectItem[nCnt].pSelectIcon->Render();
	}	
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFGameMain::CheckPopUpMenu(D3DXVECTOR2 vPos, CEnemyData* pTp)
/// \brief		�˾� �޴� üũ
/// \author		ispark
/// \date		2006-08-01 ~ 2006-08-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::CheckPopUpMenu(D3DXVECTOR2 vPos, CEnemyData* pTp)
{
	// 2005-08-25 by ispark
	// �� ĳ���͸� ALT + LBUTTONDOWN ���� �˾�â ������ �ʰ� ��(ĳ���� -> ��� ����)
	// 2005-09-12 by ispark
	// ĳ���ͳ��� �޴��� �ϴ� ����
//					if((g_pD3dApp->m_bCharacter == TRUE || pTp->m_bEnemyCharacter == TRUE))
//						break;
	// 2005-11-03 by ispark
	// ���� �ٸ� ĳ���� ���³��� �ȵ�
	if((g_pD3dApp->m_bCharacter == FALSE && pTp->m_infoCharacter.CharacterInfo.CharacterMode0 == TRUE) ||
		(g_pD3dApp->m_bCharacter == TRUE && pTp->m_infoCharacter.CharacterInfo.CharacterMode0 == FALSE))
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_051208_0103, COLOR_ERROR);// "���� �ٸ� ĳ���� ���´� ������ �� �� �����ϴ�."
		return FALSE;
	}

	// 2006-01-07 by ispark, ���� ��
#ifdef FREEWAR_
	if (!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType, pTp->m_infoCharacter.CharacterInfo.InfluenceType, 1, g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
#else
	if(!IsInfluenceCharacter(g_pShuttleChild->m_myShuttleInfo.InfluenceType, pTp->m_infoCharacter.CharacterInfo.InfluenceType))
#endif
	{
// 2007-10-24 by dgwoo ������������ �ý��� Ŭ���� �ȵǴ°ɷ� �νĵǴ� ������ ��Ʈ�� ��.
//		// 2006-01-07 by ispark, ���� �ٸ� ���³��� ���� �ȵ�
//		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_051208_0102, COLOR_ERROR);// "���� �ٸ� ���³��� ������ �� �� �����ϴ�."
		return FALSE;
	}

	// 2006-08-01 by ispark, ���λ��� �̿����ΰ� ��
	if(pTp->m_byBazaarType > 0)
	{
		// ������ ���λ��� �̿��߸� �ȵ�
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_060801_0010, COLOR_ERROR);// "������ ���λ����� �̿��߿��� ������ �� �����ϴ�."
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMain::RenderOnInfo()
/// \brief		���Ȱ� �̼� ���� �˸�
/// \author		ispark
/// \date		2006-08-22 ~ 2006-08-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderOnInfo()
{
	if(m_bKnowON[LOW_LEVEL_MISSION_HELP] && m_bKnowTwinkle)
	{//�̼ǵ��� �� ��ư.
		m_pImgMission->Move(GAMEMAIN_BUTTON_START_X+GAMEMAIN_BUTTON_INTERVAL*3, GAMEMAIN_BUTTON_START_Y);
		m_pImgMission->Render();

		if(m_pHelpDesk->m_stLowLevelHelp[LOW_LEVEL_MISSION_HELP].bLowLevelHelp)
		{
			m_pHelpDesk->m_pLowLevelHelpflash->Move(GAMEMAIN_BUTTON_START_X - 1 + GAMEMAIN_BUTTON_INTERVAL*3, GAMEMAIN_BUTTON_START_Y - 11);
			m_pHelpDesk->m_pLowLevelHelpflash->Render();
		}
	}

	// 2006-08-21 by ispark
	if(m_bKnowON[LOW_LEVEL_STAT_HELP] && m_bKnowTwinkle)
	{//���ȵ��� �� ��ư.
		m_pImgStack->Move(GAMEMAIN_BUTTON_START_X+GAMEMAIN_BUTTON_INTERVAL*1, GAMEMAIN_BUTTON_START_Y);
		m_pImgStack->Render();

		if(m_pHelpDesk->m_stLowLevelHelp[LOW_LEVEL_STAT_HELP].bLowLevelHelp)
		{
			m_pHelpDesk->m_pLowLevelHelpflash->Move(GAMEMAIN_BUTTON_START_X - 1 + GAMEMAIN_BUTTON_INTERVAL*1, GAMEMAIN_BUTTON_START_Y - 11);
			m_pHelpDesk->m_pLowLevelHelpflash->Render();
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			StartNoviceUserHelper
/// \brief		�ű� ���� �������̽� ���� �ű� ó���� �Ѵ�. 
/// \author		bhsohn
/// \date		2007-01-26 ~ 2007-01-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::StartNoviceUserHelper()
{
	if(NULL == m_pHelpDesk)
	{
		return;
	}

	// 2007-06-12 by bhsohn �̼� �������̽� ������
//	m_bKnowON[LOW_LEVEL_MISSION_HELP] = TRUE;	
//	m_pHelpDesk->SetLowLevelStringbyType(LOW_LEVEL_MISSION_HELP);

	const CHARACTER* pShuttleInfo= g_pShuttleChild->GetShuttleInfo();		

	BOOL bBonusStat = FALSE;

	//g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.BonusStat
	if(pShuttleInfo->BonusStat > 0)
	{		
		// 2007-07-27 by bhsohn ���� �߰� �� ���� ���۷����Ϳ� ����
		ShowOpStatChange(pShuttleInfo->BonusStat);
//		m_bKnowON[LOW_LEVEL_STAT_HELP] = TRUE;
//		m_pHelpDesk->SetLowLevelStringbyType(LOW_LEVEL_STAT_HELP, pShuttleInfo->BonusStat);
	}			
}

void CINFGameMain::EndNoviceUserHelper()
{
    m_bKnowON[LOW_LEVEL_MISSION_HELP] = FALSE;
	m_bKnowON[LOW_LEVEL_STAT_HELP] = FALSE;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			IsNoviceUserMode()
/// \brief		�ʱ��� ��� ���� �Ǵ��Ѵ�.
/// \author		bhsohn
/// \date		2007-01-26 ~ 2007-01-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::IsNoviceUserMode()
{	
	BOOL bNoviceUser = FALSE;	
	if(NULL == g_pShuttleChild)
	{
		return bNoviceUser;
	}
	BYTE byInfluenceType = g_pShuttleChild->GetShuttleInfo()->InfluenceType;	

	// ���������� �Ϲݱ�(�߸�)�̸� �ű������� �ν�
	if(byInfluenceType & INFLUENCE_TYPE_NORMAL)
	{
		if((!IsMyLevelQuestComplete(g_pShuttleChild->GetShuttleInfo())))
		{
			bNoviceUser = TRUE;
			return bNoviceUser;
		}		
	}	
	return bNoviceUser;

}


///////////////////////////////////////////////////////////////////////////////
/// \fn			IsMyLevelQuestComplete()
/// \brief		�� ���� �´� ����Ʈ�� �Ϸ��߳�?
/// \author		bhsohn
/// \date		2007-01-26 ~ 2007-01-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::IsMyLevelQuestComplete(const CHARACTER* pShuttleInfo)
{
	BOOL bComplete = FALSE;

	// ��ü �̼��� �������� �κ�
	vector<int> vecQuestTemp;
	vecQuestTemp = g_pQuestData->GetRaceQuestIndex(INFLUENCE_TYPE_ALL_MASK);	

	vector<int>::iterator itQuest = vecQuestTemp.begin();
	while(itQuest != vecQuestTemp.end())
	{
		CQuest* pQuest = g_pQuestData->FindQuest(*itQuest);
		if(NULL == pQuest)
		{
			itQuest++;
			continue;
		}
		// �ּҷ��� ����Ʈ
		if(pShuttleInfo->Level == pQuest->ReqLevel.Min)
		{
			bComplete = g_pQuestData->IsQuestCompleted(*itQuest);			
		}		
		itQuest++;
	}

	return bComplete;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void UpdateNewUserHelper()
/// \brief		�ű����� �������̽� �κ� ����
/// \author		bhsohn
/// \date		2007-01-26 ~ 2007-01-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::UpdateNoviceUserHelper()
{
	if(IsNoviceUserMode())					
	{
		StartNoviceUserHelper();
	}
	else
	{
		EndNoviceUserHelper();
	}

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void UpdateLV1NoviceUserHelper()
/// \brief		����1�̸� ������ ����.
/// \author		bhsohn
/// \date		2007-01-26 ~ 2007-01-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::UpdateLV1NoviceUserHelper()
{		
	const CHARACTER* pShuttleInfo= g_pShuttleChild->GetShuttleInfo();		
	BYTE byInfluenceType = pShuttleInfo->InfluenceType;	

	// ���������� �Ϲݱ�(�߸�)�̸� �ű������� �ν�	
	if(byInfluenceType & INFLUENCE_TYPE_NORMAL)
	{
		StartNoviceUserHelper();
	}
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�κ����� ���� ������ ����
/// \author		bhsohn
/// \date		2007-02-21 ~ 2007-02-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetMultiSelectItem(INVEN_DISPLAY_INFO *pDisplayInfo, INVEN_DISPLAY_INFO	*pSelectItem, POINT ptIcon)
{
	g_pD3dApp->SetMultiSelectItem(pDisplayInfo, pSelectItem, ptIcon, ITEM_INVEN_POS);	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		â���� ���� ������ ó��
/// \author		bhsohn
/// \date		2007-02-21 ~ 2007-02-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetMultiSelectCityStoreItem(CItemInfo* pItemInfo, INVEN_DISPLAY_INFO	*pSelectItem, POINT ptIcon, INVEN_DISPLAY_INFO  *pDisSelectItem)
{			
	
	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	//g_pD3dApp->SetMultiSelectCityStoreItem(pItemInfo, pSelectItem, ptIcon, ITEM_STORE_POS);
	g_pD3dApp->SetMultiSelectCityStoreItem(pItemInfo, pSelectItem, ptIcon, ITEM_STORE_POS, pDisSelectItem);
	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
}

void CINFGameMain::UpdateIconSelectItem(BYTE byType)
{
	deque<stMultiSelectItem>* pVector = g_pD3dApp->GetMultiSelVector(byType);
	if(NULL == pVector)
	{
		return;
	}		
	ClearMultiSelectItem();
	int nCnt = 0;
	deque<stMultiSelectItem>::iterator it = pVector->begin();
	while(it != pVector->end())
	{			
		if(nCnt >= MAX_MULTI_SEL)
		{
			break;
		}
		
		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
		
		//AddMultiSelectItem(it->SourceIndex, it->bySelectType, it->ptIcon);
		AddMultiSelectItem( it->SourceIndex, it->bySelectType, it->ptIcon, it->szIconName );

		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

		it++;
	}
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CInterface::SetSelectItem(INVEN_DISPLAY_INFO *pDisplayInfo, POINT pt, BYTE byType)
/// \brief		���� ������
/// \author		// 2007-03-02 by bhsohn ���� ���� �߰� ����
/// \date		2007-03-05 ~ 2007-03-05
/// \warning	
///
/// \param		
/// \return		TRUE : �� ������ �� �ٸ� ������    FALSE : ���ų� ����
///////////////////////////////////////////////////////////////////////////////


// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
//void CINFGameMain::AddMultiSelectItem(int nSourceIndex, BYTE bySelectType, POINT ptIcon)
void CINFGameMain::AddMultiSelectItem( int nSourceIndex, BYTE bySelectType, POINT ptIcon, char* szIconName )
// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

{
	FLOG( "CINFInven::SetSelectItem(INVEN_DISPLAY_INFO* pDisplayInfo)" );

	// ������ ���� 
	if(m_nMultiSelCnt >= MAX_MULTI_SEL)
	{
		return;
	}	
	int nItemIdx = m_nMultiSelCnt;


	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

// 	char buf[64];
// 	wsprintf(buf, "%08d", nSourceIndex);
// 	CINFImage* pIcon = m_pIcon->FindIcon(buf);

	CINFImageEx* pIcon = m_pIcon->FindIcon( szIconName );
	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

	if(NULL == pIcon)
	{
		return;
	}
	m_stMultiSelectItem[nItemIdx].pSelectIcon	= pIcon;	
	m_stMultiSelectItem[nItemIdx].bySelectType	= bySelectType;
	m_stMultiSelectItem[nItemIdx].ptIcon		= ptIcon;
	m_nMultiSelCnt++;

	return;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		â������ ���� ���� 
/// \author		bhsohn
/// \date		2007-02-21 ~ 2007-02-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::GetCityStoreMultiSelectItem()
{
	return g_pD3dApp->GetCityStoreMultiSelectItem();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�κ����� â��� ������ �̵�
/// \author		// 2007-03-02 by bhsohn ���� ���� �߰� ����
/// \date		2007-02-21 ~ 2007-02-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::PopupMultiItemSelect()
{
	GUI_BUILDINGNPC* pNpc = g_pInterface->m_pCityBase->GetCurrentBuildingNPC();
	if(NULL == pNpc)
	{
		return;
	}
	// ���� ������ �˾� 
	
	char buf[MAX_PATH];	
	char szMoney[80];
	int nMultiPopupId = 0;	

	memset(buf, 0x00, MAX_PATH);	
	memset(szMoney, 0x00, 80);

	if(IS_ITEM_SHOP_TYPE(pNpc->buildingInfo.BuildingKind)
		|| IS_WARPOINT_SHOP_TYPE(pNpc->buildingInfo.BuildingKind))
	{	
		// ������
		g_pD3dApp->GetMultiItemSPI(_Q_SHOP_MULTI_SELL_ITEM, szMoney);		
		nMultiPopupId = _Q_SHOP_MULTI_SELL_ITEM;
		wsprintf( buf, STRMSG_C_070212_0202, szMoney);
	}
	else if(IS_STORE_SHOP_TYPE(pNpc->buildingInfo.BuildingKind))
	{	
		// â��
		g_pD3dApp->GetMultiItemSPI(_Q_STORE_MULTI_PUT_ITEM, szMoney);		// �� �ؽ�Ʈ�� ���´�. 
		nMultiPopupId = _Q_STORE_MULTI_PUT_ITEM ;
		wsprintf( buf, STRMSG_C_070212_0201, szMoney);
	}
	else
	{
		return;
	}
	

	if(m_pInfWindow->IsExistMsgBox(_Q_SHOP_SELL_ITEM))
	{
		m_pInfWindow->DeleteMsgBox(_Q_SHOP_SELL_ITEM);
	}
	else if(m_pInfWindow->IsExistMsgBox(_Q_SHOP_SELL_ENERGY))
	{
		m_pInfWindow->DeleteMsgBox(_Q_SHOP_SELL_ENERGY);
	}	
	else if(m_pInfWindow->IsExistMsgBox(_Q_SHOP_MULTI_SELL_ITEM ))
	{
		m_pInfWindow->DeleteMsgBox(_Q_SHOP_MULTI_SELL_ITEM );
	}								
	else if(m_pInfWindow->IsExistMsgBox(_Q_STORE_MULTI_PUT_ITEM ))
	{
		m_pInfWindow->DeleteMsgBox(_Q_STORE_MULTI_PUT_ITEM );
	}								
	else if(m_pInfWindow->IsExistMsgBox(_Q_STORE_MULTI_GET_ITEM ))
	{
		m_pInfWindow->DeleteMsgBox(_Q_STORE_MULTI_GET_ITEM );
	}
	
	m_pInfWindow->AddMsgBox(buf, nMultiPopupId, NULL);	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		â���� �κ��� ������ �̵�
/// \author		// 2007-03-02 by bhsohn ���� ���� �߰� ����
/// \date		2007-02-21 ~ 2007-02-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::PopupStoreMultiItemSelect()
{	
	if(m_pInfWindow->IsExistMsgBox(_Q_SHOP_SELL_ITEM))
	{
		m_pInfWindow->DeleteMsgBox(_Q_SHOP_SELL_ITEM);
	}
	else if(m_pInfWindow->IsExistMsgBox(_Q_SHOP_SELL_ENERGY))
	{
		m_pInfWindow->DeleteMsgBox(_Q_SHOP_SELL_ENERGY);
	}	
	else if(m_pInfWindow->IsExistMsgBox(_Q_SHOP_MULTI_SELL_ITEM ))
	{
		m_pInfWindow->DeleteMsgBox(_Q_SHOP_MULTI_SELL_ITEM );
	}								
	else if(m_pInfWindow->IsExistMsgBox(_Q_STORE_MULTI_PUT_ITEM ))
	{
		m_pInfWindow->DeleteMsgBox(_Q_STORE_MULTI_PUT_ITEM );
	}								
	else if(m_pInfWindow->IsExistMsgBox(_Q_STORE_MULTI_GET_ITEM ))
	{
		m_pInfWindow->DeleteMsgBox(_Q_STORE_MULTI_GET_ITEM );
	}
	
	m_pInfWindow->AddMsgBox(STRMSG_C_070212_0205, _Q_STORE_MULTI_GET_ITEM, NULL);	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���� ��ų�� ������̳�
/// \author		// 2007-03-22 by bhsohn ������ ũ�� ���� ����
/// \date		2007-03-22 ~ 2007-03-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::IsDoingSkill(int nSourceIndex)
{
	if(NULL == m_pInfSkill)
	{
		return FALSE;
	}
	return m_pInfSkill->IsDoingSkill(nSourceIndex);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���� ��ų�� ������̳�
/// \author		// 2007-03-27 by bhsohn ������ ���� �������̽� ����
/// \date		2007-03-27 ~ 2007-03-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::Render_AltiMeter()
{
	// ������ ǥ��
	ProcessAltiMeter(g_pGround->m_projectInfo.fWaterHeight, 
		g_pScene->m_nMaxAtitudeHeight, 
		g_pShuttleChild->m_vPos.y );
	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�̼� ��Ʈ�� ������
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderMission()
{
	if(NULL == m_pMissionMain)
	{
		return;
	}	
	m_pMissionMain->Render();	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�̼� ��Ʈ�� �޽��� ó��
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::WndProcMiss(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(NULL == m_pMissionMain)
	{
		return INF_MSGPROC_NORMAL;
	}	
	// 2007-11-01 by bhsohn ���� �̿��߿� ��� ��ư ����
	else if(g_pD3dApp->m_dwGameState == _SHOP)
	{
		return INF_MSGPROC_NORMAL;
	}
	// end 2007-11-01 by bhsohn ���� �̿��߿� ��� ��ư ����
	return m_pMissionMain->WndProc(uMsg, wParam, lParam);

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
ITEM * CINFGameMain::GetServerItemInfo(int nItemNum)
{
	return g_pDatabase->GetServerItemInfo(nItemNum);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
CINFImageEx* CINFGameMain::FindIcon(char* strName)
{
	return m_pIcon->FindIcon(strName);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetWindowOrder(int nWndIndex)
{
	g_pInterface->SetWindowOrder(nWndIndex);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::CreateChatChild(TCHAR *str,int type, int chatType/* = CHAT_TAB_SYSTEM*/, char* szWisperToCharacterName, char *szWisperFromCharacterName)
{	
	g_pD3dApp->m_pChat->CreateChatChild(str,
											type, 
											chatType, 
											szWisperToCharacterName, 
											szWisperFromCharacterName); 
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
MEX_MONSTER_INFO * CINFGameMain::CheckMonsterInfo(int nMonType)
{
	return g_pDatabase->CheckMonsterInfo(nMonType);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
MAP_INFO * CINFGameMain::GetMapInfo(MapIndex_t nMapIndex)
{
	return g_pDatabase->GetMapInfo(nMapIndex);
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderMissionINGInfo()
{
	if(NULL == m_pMissionMain)
	{
		return ;
	}	
	m_pMissionMain->RenderMissionINGInfo();	
}
void CINFGameMain::SetMissionEnterShop(BOOL bEnterShopState)
{
	if(NULL == m_pMissionMain)
	{
		return ;
	}	
	m_pMissionMain->SetMissionEnterShop(bEnterShopState);

}
void CINFGameMain::MissionStart(DWORD dMissionIndex)
{
	if(NULL == m_pMissionMain)
	{
		return ;
	}	
	m_pMissionMain->MissionStart(dMissionIndex);
}


BOOL CINFGameMain::IsBazaar()
{
	// 2007-12-27 by bhsohn ���� ���ۿ� ���� �κ� ����
	if(NULL == g_pGround)
	{
		return FALSE;		
	}
	// end 2007-12-27 by bhsohn ���� ���ۿ� ���� �κ� ����
	return g_pGround->m_bBazaar;
}

void CINFGameMain::TickMissonMain()
{
	if(NULL == m_pMissionMain)
	{
		return ;
	}	
	m_pMissionMain->Tick();
}
// ������ ó�� ������ ����
void CINFGameMain::FirstUserShowMissionTreeWnd()
{	
	// 2007-07-20 by bhsohn 10���� Ʃ�丮���� ��ü�� �� �ؾ��Ѵ�.
	g_pInterface->ShowOpUserHelper(TRUE, OPERATOR_USER_HELPER_FREESKA, NULL);	
}

void CINFGameMain::ShowMissionTreeWnd(BOOL bFlag, BOOL bSoundPlay)
{
	// ����ʿ����� �̼�â ���� ���Ѵ�.
	if(g_pGameMain->IsBazaar())
	{
		return ;
	}
	if(bFlag && g_pTutorial)
	{
		g_pTutorial->SetTutorialEd(FALSE);		
	}
	m_pMissionMain->ShowTreeWnd(bFlag, bSoundPlay);
}

BOOL CINFGameMain::IsShowTreeWnd()
{
	if(NULL == m_pMissionMain)
	{
		return FALSE;
	}	
	return m_pMissionMain->IsShowTreeWnd();
}

void CINFGameMain::SetMissionPosMissionSearchStart(BOOL nstate)
{
	if(NULL == m_pMissionMain)
	{
		return ;
	}	
	m_pMissionMain->SetPosMissionSearchStart(nstate);
}
void CINFGameMain::SetMissionPosMissionInfo(CQuest* pQuest)
{
	if(NULL == m_pMissionMain)
	{
		return ;
	}	
	m_pMissionMain->SetPosMissionInfo(pQuest);	
}

void CINFGameMain::SetMissionPosMissionComplete(BOOL bFlag)
{
	if(NULL == m_pMissionMain)
	{
		return ;
	}	
	m_pMissionMain->SetPosMissionComplete(bFlag);
}

BOOL CINFGameMain::GetInfluenceMission()
{
	if(NULL == m_pMissionMain)
	{
		return FALSE;
	}	
	return m_pMissionMain->GetInfluenceMission();	
}
void CINFGameMain::SetInfluenceMission(BOOL nFlag, float fANIPercent, float fVANPercent)
{
	if(NULL == m_pMissionMain)
	{
		return ;
	}	
	m_pMissionMain->SetInfluenceMission(nFlag, fANIPercent, fVANPercent);
}

void CINFGameMain::RefreshMission(BOOL bClick)
{
	if(NULL == m_pMissionMain)
	{
		return ;
	}	
	INT nQuestIdx = 0;
	CQuest* pProgressMission = g_pQuestData->GetProgressMission();
	if(pProgressMission)
	{
		nQuestIdx = pProgressMission->QuestIndex;
	}
	m_pMissionMain->RefreshMission(bClick, nQuestIdx);

}
void CINFGameMain::SelectNextMission(INT nQuestIndex)
{
	if(NULL == m_pMissionMain)
	{
		return ;
	}	
	m_pMissionMain->SelectNextMission(nQuestIndex);

}

void CINFGameMain::GoWarpMapChange(int nQuestMapIdx)
{
	// 2007-07-04 by bhsohn ���۷����� �߰�
	g_pInterface->ShowOpUserHelper(FALSE, 0, NULL);
		
	const auto& myShuttle = GetMyShuttleInfo();

	// 2007.09.19 by bhsohn ���� ���� ��� ó��
	if(IS_OUTPOST_CITY_MAP_INDEX(myShuttle.MapChannelIndex.MapIndex))
	{
		m_pMissionMain->SetMissionMapQuestIdx(nQuestMapIdx);
		BOOL bGoMissionMap = g_pShuttleChild->SendGoMissionMap();				
		
		if(FALSE == bGoMissionMap)
		{
			// �̼Ǹ� �� ������ ��� �ߵ�
			CObjectChild * pCurrentObjEvent = g_pScene->FindEventObjectByTypeAndPosition(EVENT_TYPE_CHARACTERMODE_WARP, g_pCharacterChild->m_vPos, 10240.0f);
			if(pCurrentObjEvent)
			{
				g_pShuttleChild->SendFieldSocketRequestEventObjectWarpIn(pCurrentObjEvent);
			}
			// 2008-04-22 by bhsohn �������� ��� �ȵǴ� ���� �ذ�
			else
			{
				// EVENT_TYPE_CHARACTERMODE_WARP �� ��ã���� EVENT_TYPE_CHARACTERMODE_DIRECTLY_WARP �� ã�´�.
				pCurrentObjEvent = g_pScene->FindEventObjectByTypeAndPosition(EVENT_TYPE_CHARACTERMODE_DIRECTLY_WARP, g_pCharacterChild->m_vPos, 10240.0f);
				if(pCurrentObjEvent)
				{
					g_pShuttleChild->SendFieldSocketRequestEventObjectWarpIn(pCurrentObjEvent);
				}				
			}
			// end 2008-04-22 by bhsohn �������� ��� �ȵǴ� ���� �ذ�
		}
	}
	else
	{
		// �̼Ǹ��� 0�̸� �׳� ���
		// �̼Ǹ����� �̵�
		g_pD3dApp->StartFadeEffect(TRUE,3,D3DCOLOR_ARGB(0,0,0,0));
		g_pCharacterChild->FineObjectTakeOff();	
		m_pMissionMain->SetMissionMapQuestIdx(nQuestMapIdx);
	}
	// end 2007.09.19 by bhsohn ���� ���� ��� ó��

	// 2008-06-17 by bhsohn ��� ���� ó��
	if(g_pShuttleChild 
		&& g_pShuttleChild->m_pClientParty 
		&& g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER 
		&& g_pShuttleChild->m_pClientParty->IsFormationFlight())
	{
		g_pShuttleChild->m_pClientParty->TempPartyFormation(FLIGHT_FORM_NONE);
	}

}

void CINFGameMain::AddMsgBox(char* strMsg, int nType, DWORD dwData1, DWORD dwData2, int nLiveTime,UID64_t UniqueNumber, char* strName)
{
	m_pInfWindow->AddMsgBox(strMsg, nType, dwData1, dwData2, nLiveTime,UniqueNumber, strName);
}

// ĳ������
const CHARACTER& CINFGameMain::GetMyShuttleInfo() const
{
	return g_pShuttleChild->GetMyShuttleInfo();
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// �������� �˾� ������ Show
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::UpdateMissionPopWnd(BYTE byUpLevel, int nSuccessQuestIdx)
{
	int nPossibleQuestIdx = 0;
	if(FALSE == m_pMissionMain->IsLevelSecnQuest(byUpLevel, nSuccessQuestIdx, &nPossibleQuestIdx))
	{
		return;
	}	

	// 2007-07-23 by bhsohn ���۷����� �߰��۾�
	BOOL bShowFirstOperation = FALSE;
	if(g_pD3dApp->IsMyShuttleCharacter() == TRUE)
	{
		// ���۷����͸� ����.
		// 2007-07-20 by bhsohn Ʃ�丮�� ����
		const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
		// ����������
		if((COMPARE_INFLUENCE(myShuttleInfo.InfluenceType, INFLUENCE_TYPE_VCN))
			&&(SELECT_FIRST_QUEST_IDX == nSuccessQuestIdx))
		{		
			bShowFirstOperation = TRUE;
			g_pInterface->ShowOpFirstInfluenceQuest(INFLUENCE_TYPE_VCN);			
		}
		else if((COMPARE_INFLUENCE(myShuttleInfo.InfluenceType, INFLUENCE_TYPE_ANI))
			&&(SELECT_FIRST_QUEST_IDX == nSuccessQuestIdx))
		{			
			bShowFirstOperation = TRUE;
			g_pInterface->ShowOpFirstInfluenceQuest(INFLUENCE_TYPE_ANI);			
		}
	}		
	if(FALSE == bShowFirstOperation )
	{
		m_pMissionMain->ShowMissionPopWnd(TRUE, nPossibleQuestIdx);			
		m_pMissionMain->SetFirstPossibleQuestIdx(0);
	}
	else 
	{
		m_pMissionMain->SetFirstPossibleQuestIdx(nPossibleQuestIdx);
		
	}
}

// ó�� ���� ���� ������ ���۷��̼� �ݱ� ��ư Ŭ��
void CINFGameMain::OnClickFirstUserCloseBtn()
{
	if(m_pMissionMain->GetFirstPossibleQuestIdx() != 0)
	{
		m_pMissionMain->ShowMissionPopWnd(TRUE, m_pMissionMain->GetFirstPossibleQuestIdx());	
	}

}
int CINFGameMain::GetMissionMapQuestIdx()
{
	if(NULL == m_pMissionMain)
	{
		return 0;
	}
	return m_pMissionMain->GetMissionMapQuestIdx();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// �������� �˾� ������ Show
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-06-12 ~ 2007-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetImageInfo(int nImageIndex, BOOL bMissionImg)
{
	g_pGImage->SetImageInfo(nImageIndex, bMissionImg);
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		FAQ��ư ������
/// \author		// 2007-07-04 by bhsohn ���۷����� �߰�
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetFaqBtnBlingBling(BOOL bSet)
{	
	m_pFaqBtn->SetBtnBlingBling(bSet, FAQ_BLING_TIME);

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�긮�� �� Ŭ��
/// \author		// 2007-06-12 by bhsohn �̼� �������̽� ������
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::OnClickBriefingRoom()
{
	BOOL bShowTree = IsShowTreeWnd();
	bShowTree ^= TRUE;
	ShowMissionTreeWnd(bShowTree, TRUE);
	g_pInterface->SetWindowOrder(WNDMissionInfo);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		Ʃ�丮�� 
/// \author		// 2007-07-04 by bhsohn ���۷����� �߰�
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::NextTutirialState()
{
	g_pTutorial->NextState();
}
void CINFGameMain::ChangeChapterReady()
{
	g_pTutorial->ChangeChapterReady();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		Ʃ�丮�� 
/// \author		// 2007-07-04 by bhsohn ���۷����� �߰�
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::InitTutorialLesson()
{
	g_pTutorial->ChangeLesson(L0);

}

BOOL CINFGameMain::IsTutorialMode()
{
	return g_pTutorial->IsTutorialMode();
}

void CINFGameMain::ShowOpBossMonsterSummon(BYTE byBelligerence, int nHour, int nMinute)
{	
	g_pInterface->ShowOpBossMonsterSummon(byBelligerence, nHour, nMinute);

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-07-27 by bhsohn ���� �߰� �� ���� ���۷����Ϳ� ����
/// \date		2007-07-27 ~ 2007-07-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFGameMain::ShowOpStatChange(int nStat)
{
	if(!IS_NORMAL_INFLUENCE_TYPE(g_pGameMain->GetMyShuttleInfo().InfluenceType))
	{
		return;
	}
	char chHelpString[1024];
	memset(chHelpString, 0x00, 1024);
	wsprintf(chHelpString, STRMSG_C_060823_0000, nStat);
	g_pInterface->ShowOpWndTxt(chHelpString);

	m_bShowStatOpWnd = TRUE;
	
}
VOID CINFGameMain::HideOpStatChange()
{
	m_bShowStatOpWnd = FALSE;
	g_pInterface->ShowOpWnd(FALSE);

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-08-02 by bhsohn ���ڸʿ��� ��ݹ�ư ǥ������.
/// \date		2007-08-02 ~ 2007-08-02
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFGameMain::RefreshMissionUI()
{
	if(NULL == m_pMissionMain)
	{
		return;
	}
	m_pMissionMain->RefreshMissionUI();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
/// \date		2007-08-07 ~ 2007-08-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFGameMain::RenderSpeakerMsg()
{
	if(NULL == m_pINFSpeakeMsg)
	{
		return;
	}
	m_pINFSpeakeMsg->Render();

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
/// \date		2007-08-07 ~ 2007-08-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFGameMain::TickSpeakerMsg()
{
	if(NULL == m_pINFSpeakeMsg)
	{
		return;
	}
	m_pINFSpeakeMsg->Tick();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
/// \date		2007-08-07 ~ 2007-08-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::AddSpeakerMsgString(char* pTxt, BOOL bGm, BOOL bGmColor)
{
	if(NULL == m_pINFSpeakeMsg)
	{
		return;
	}
	m_pINFSpeakeMsg->AddSpeakerMsgString(pTxt, bGm,bGmColor);

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
/// \date		2007-08-07 ~ 2007-08-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::DeleteNotGmMsg()
{
	if(NULL == m_pINFSpeakeMsg)
	{
		return;
	}
	m_pINFSpeakeMsg->DeleteNotGmMsg();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-09-05 by bhsohn ���� ������
/// \date		2007-09-05 ~ 2007-09-05
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::StringCulling(char *pLineString, int nCullStringNum, vector<string> *vecStorage, CD3DHanFont* pHanFont)
{
	STRING_CULL(pLineString, nCullStringNum, vecStorage, pHanFont);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::InitSecurityPassMode()
{	
	if(FALSE == g_pD3dApp->IsUseSecondaryPasswordSystem())
	{
		return;
	}
	if(NULL == m_pINFSecuMain)
	{
		m_pINFSecuMain = new CINFSecuMain;		
		m_pINFSecuMain->SetGameData( m_pGameData );
		m_pINFSecuMain->InitDeviceObjects();		
	}
	// 2008-07-07 by bhsohn 2�� �н����� Ȱ��ȭ��, �κ� �ȿ����� ��
	g_pD3dApp->SetSecondPassLock(g_pD3dApp->IsSetSecondaryPassword());	// �α׿����ϰ� ó�� ���� ������ �������̴�.

	// ������ �ȵǾ������� Lock���·� ������ ����.
//	if(FALSE == g_pD3dApp->IsSetSecondaryPassword())
//	{			
//		m_pINFSecuMain->ShowSecurityWnd(SECURITY_MODE_LOCK, TRUE);
//	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFGameMain::RenderSecuritySystem()
{
	if(NULL == m_pINFSecuMain)
	{
		return;
	}
	m_pINFSecuMain->Render();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFGameMain::TickSecuritySystem()
{
	if(NULL == m_pINFSecuMain)
	{
		return;
	}
	m_pINFSecuMain->Tick();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::OnClickF10Btn()
{
	if((FALSE == g_pD3dApp->IsUseSecondaryPasswordSystem()) 
		||(NULL == m_pINFSecuMain))
	{
		return;
	}
	// 2008-08-25 by bhsohn �Ʒ��� �̿��, 2�� �н����� ���� �ذ�
	else if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
	{
		return;
	}
	// end 2008-08-25 by bhsohn �Ʒ��� �̿��, 2�� �н����� ���� �ذ�
	
	// 2007-09-27 by bhsohn 2�� �н����� �߰� ��ȹ��
	if(GetAsyncKeyState(VK_CONTROL))
	{
		if(m_pINFSecuMain->IsShowWnd(SECURITY_MODE_LOCK))
		{
			return;
		}
		if(TRUE == g_pD3dApp->IsSetSecondaryPassword())
		{
			//"���� �ý����� �����Ͻðڽ��ϱ�?"
			m_pInfWindow->AddMsgBox(STRMSG_C_070928_0201, _Q_SECOND_PASS_CANCEL_MSG);
		}
	}
	else
	{
		if(m_pInfWindow->IsExistMsgBox(_Q_SECOND_PASS_CANCEL_MSG))
		{
			return;
		}
		BOOL bShowLock = m_pINFSecuMain->IsShowWnd(SECURITY_MODE_LOCK);
		bShowLock ^= TRUE;
		if(bShowLock)
		{
			if(m_pINFSecuMain->IsShowWnd(SECURITY_MODE_PASS_WND))
			{
				return;
			}
			m_pINFSecuMain->ShowSecurityWnd(SECURITY_MODE_LOCK, bShowLock);
		}
		else
		{
			m_pINFSecuMain->AllHideSecurityWnd();		
		}
	}	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::WndProcSysKeyDown(WPARAM wParam, LPARAM lParam)
{
	if(CheckSysKeyUseState(wParam, lParam, TRUE, FALSE) ||
		g_pD3dApp->m_bChatMode == TRUE ||
		g_pD3dApp->m_dwGameState == _SHOP || 
		m_nLeftWindowInfo == LEFT_WINDOW_TRANS ||
		g_pGameMain->m_pTrade->m_bTrading)
	{
		return INF_MSGPROC_BREAK;
	}

	switch(wParam)
	{
	case VK_F10:
		{			
			if(g_pShuttleChild->IsObserverMode())
			{
				break;
			}	
			if(((CInterface*)m_pParent)->m_bShowInterface == FALSE)
				break;
			OnClickF10Btn();
		}
	}
	return INF_MSGPROC_NORMAL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::CheckSysKeyUseState(int nwParamFlage, int nlParamFlage, BOOL bUse, BOOL bOneUse)
{
	if(bUse == FALSE)
	{
		return FALSE;
	}
	switch(nlParamFlage) 
	{
	case VK_F10:
		if(g_pTutorial->IsTutorialMode() == TRUE || 
			!g_pShuttleChild->GetIsUseInterface())
		{
			return TRUE;
		}
		break;
	}
	return FALSE;	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�н����� ����
/// \author		// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFGameMain::FieldSecondLockOk(BOOL bIsUnlockFlag, BOOL bSuccess)
{
	// 2008-07-07 by bhsohn 2�� �н����� Ȱ��ȭ��, �κ� �ȿ����� ��
	BYTE bLockFlag = FALSE;
	if(bSuccess)
	{
		bLockFlag = !bIsUnlockFlag;		
	}
	else
	{
		bLockFlag = TRUE;
	}
	g_pD3dApp->SetSecondPassLock(bLockFlag);
	// end 2008-07-07 by bhsohn 2�� �н����� Ȱ��ȭ��, �κ� �ȿ����� ��

	if((FALSE == g_pD3dApp->IsUseSecondaryPasswordSystem()) 
		||(NULL == m_pINFSecuMain))
	{
		// UnLock
		g_pD3dApp->EnterLock(TRUE);
		return;
	}
	
	m_pINFSecuMain->FieldSecondLockOk(bIsUnlockFlag, bSuccess);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			VOID CAtumApplication::FieldSocketSecondPasswordUpdateOk(BOOL bSuccess)
/// \brief		2�� �н� ���� ������Ʈ
/// \author		// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////	
VOID CINFGameMain::FieldSocketSecondPasswordUpdateOk(BOOL bSuccess, BOOL bFirstUseSecondPassword)
{
	if((FALSE == g_pD3dApp->IsUseSecondaryPasswordSystem()) 
		||(NULL == m_pINFSecuMain))
	{
		// UnLock
		g_pD3dApp->EnterLock(TRUE);
		return;
	}
	m_pINFSecuMain->FieldSocketSecondPasswordUpdateOk(bSuccess, bFirstUseSecondPassword);
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			int GetPassChangeMode()
/// \brief		2�� �н� ���� ������Ʈ
/// \author		// 2007-09-27 by bhsohn 2�� �н����� �߰� ��ȹ��
/// \date		2007-09-27 ~ 2007-09-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////	
int CINFGameMain::GetPassChangeMode()
{
	if((FALSE == g_pD3dApp->IsUseSecondaryPasswordSystem()) 
		||(NULL == m_pINFSecuMain))
	{		
		return -1;
	}
	return m_pINFSecuMain->GetPassChangeMode();
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFGameMain::ShowSecondPassword()
{
	if((FALSE == g_pD3dApp->IsUseSecondaryPasswordSystem()) 
		||(NULL == m_pINFSecuMain))
	{		
		return ;
	}
	m_pINFSecuMain->ShowSecurityWnd(SECURITY_MODE_PASS_WND, TRUE, SECURITY_MODE_PASS_SENCOND_CANCEL);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�ִ� �Ѿ� ���� ���´�. �����̾� ������ 2���� �Ѿ˼� (��Ʈ���� ����)
/// \author		// 2007-10-15 by bhsohn �Ѿ� ������ �߰� ó��
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::GetMaxBulletItem(int nBullet)
{
	int nMaxCharge = nBullet;
#ifndef LANGUAGE_VIETNAM
	// ��Ʈ���� 2�� �ý��� ��� ����.
	if(g_pD3dApp->IsPrimiumUser())
	{
		nMaxCharge = (2*nBullet);
	}
#endif
	return nMaxCharge;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�ŷ� �� �׾�����, Ű �ȸԴ� ����ó��
/// \author		// 2007-10-16 by bhsohn �ŷ� �� �׾�����, Ű �ȸԴ� ����ó��
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetTradeInfo(BOOL bTrade)
{
	if(NULL == m_pTrade)
	{
		return;
	}
	m_pTrade->SetTradeInfo(bTrade);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMain::ShowCouponWindow(BOOL i_bShow)
/// \brief		����â�� ���̰� ����.
/// \author		dgwoo
/// \date		2008-01-15 ~ 2008-01-15
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::ShowCouponWindow(BOOL i_bShow)
{
	POINT pt;
	pt.x = COUPON_WINDOW_POS_X;
	pt.y = COUPON_WINDOW_POS_Y;
	m_pCouponWindow->SetShow(i_bShow);
	m_pCouponWindow->SetWindowPoint(pt);
	
}
void CINFGameMain::SetCouponActive(MSG_FC_EVENT_COUPON_EVENT_INFO* pMsg)
{
	m_pCouponWindow->SetActive(pMsg);
	m_pCouponBtn->EnableBtn(TRUE);
	m_pCouponBtn->ShowWindow(TRUE);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainChat::GetAllChatList(ChatLine_t pArrChatLine[CHAT_BUFFER_NUMBER])
/// \brief		ä����ü ������ ���´�.
/// \author		// 2008-02-27 by bhsohn �Ʒ��� �̵��� ä������ ���?
/// \date		2008-02-27 ~ 2008-02-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::GetAllChatList(ChatLine_t pArrChatLine[CHAT_BUFFER_NUMBER])
{
	if(m_pChat)
	{
		m_pChat->GetAllChatList(pArrChatLine);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�ɼ�â ����
/// \author		// 2008-03-19 by bhsohn Ep3�ɼ�â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::PopupSystemOptinWnd()
{
	// 2008-04-08 by bhsohn �ñ�� ����
	if(NULL == m_pSystem)
	{
		return;
	}
	// end 2008-04-08 by bhsohn �ñ�� ����
	BOOL bShow = m_pSystem->IsOptionShow();
	bShow ^= TRUE;
	m_pSystem->ShowOptionWnd(bShow);

	if(bShow)
	{
		// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ���� 
		//g_INFCnt++;
		g_pGameMain->m_bChangeMousePoint = TRUE;
		// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ����
		g_pInterface->SetWindowOrder(WNDLeftRightWindow);
		g_pD3dApp->m_pSound->PlayD3DSound(SOUND_OPEN_MENU, g_pShuttleChild->m_vPos, FALSE);			
	}
	else
	{
#ifndef NEMERIAN
		// 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ���� 
		if(g_pGameMain->m_pUnitState->m_dwState==0)
		{
#endif
			//g_INFCnt--;
			// 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
			//if(g_INFCnt==0)
			if(g_pD3dApp->GetINFCnt() == 0)
			{
				g_pGameMain->m_bChangeMousePoint = FALSE;
			}
			// end 2012-12-17 by jhjang ������ ���콺 Ŀ���� ����� �������� �ʴ� ���� ����
#ifndef NEMERIAN
	}
#endif

		// end 2009. 08. 19 by jsKim ���� �� �޴� ������ ��� Ŀ���� ������ �ʴ� ���� 
		g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MENU, g_pShuttleChild->m_vPos, FALSE);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-03-27 by bhsohn �̼Ǽ���â�� ���ִ� ���¿����� ������ �ȿ����� ����
/// \date		2008-03-27 ~ 2008-03-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::CloseCurrentEnterBuilding()
{
	if(g_pInterface->m_pCityBase->GetCurrentBuildingNPC() != NULL)
	{
		g_pInterface->m_pCityBase->OnCityNPCButtonDown(CITY_NPC_BUTTON_CLOSE);
	}
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-03-27 by bhsohn �̼Ǽ���â�� ���ִ� ���¿����� ������ �ȿ����� ����
/// \date		2008-03-27 ~ 2008-03-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetForceCloseShop(BOOL bForceClose)
{
	g_pInterface->m_pCityBase->SetForceCloseShop(bForceClose);		
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::DestroyMotherShipInfo(BYTE byBelligerence)
{
	m_pMotherShipC->DestroyMotherShipInfo(byBelligerence);
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SummonMotherShipInfo(BYTE byBelligerence, 
										ATUM_DATE_TIME  *pSummonMonsterTime, 
										INT	 nContributionPoint, 
										INT SummonMonsterUnitkind)
{
	m_pMotherShipC->SummonMotherShipInfo(byBelligerence, pSummonMonsterTime, nContributionPoint, SummonMonsterUnitkind);
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::GetSummonMotherShipCnt()
{
	if(NULL == m_pMotherShipC)
	{
		return 0;
	}
	return m_pMotherShipC->GetSummonMotherShipCnt();
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::GetMotherShipInfl(UINT i_nMotherShipInf)
{
	return m_pMotherShipC->GetMotherShipInfl(i_nMotherShipInf);	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::SetWarPointMapInfo(SMSWARINFO_DISPLAY * pWarInfo)
{
	return m_pMotherShipC->SetWarPointMapInfo(pWarInfo);
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetStrategicPointInfo(SSTRATEGYPOINT_DISPLAY_INFO* pStrInfo)
{
	m_pStrategicPointDisplay->SetStrategicPoint(pStrInfo);
}

void CINFGameMain::DeleteStrategicPointInfo(MapIndex_t mapIndex)
{
	m_pStrategicPointDisplay->RemoveStrategicPoint(mapIndex);
}

void CINFGameMain::ResetStrategicPointDisplay()
{
	m_pStrategicPointDisplay->ResetAllStrategicPoints();
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetMSWarInfoDisplayOption(MSG_FC_INFO_MSWARINFO_DISPLAY_OPTION_OK* pMsg)
{
	m_pMotherShipC->SetMSWarInfoDisplayOption(pMsg);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
/// \date		2008-04-07 ~ 2008-04-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CINFGameMain::GetQuestTimeElapse()
{
	return m_fQuestTimeElapse;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
/// \date		2008-04-07 ~ 2008-04-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetQuestTimeElapse(float fGetQuestTimeElapse)
{
	m_fQuestTimeElapse = fGetQuestTimeElapse;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-22 by bhsohn ��/������ �������� ������ ǥ�� �ϰ� ����
/// \date		2008-04-22 ~ 2008-04-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::UpdatePlayingMotherShipInfo()
{
	if(NULL == m_pMotherShipC)
	{
		return;
	}
	GUI_BUILDINGNPC* pBuilding = g_pInterface->m_pCityBase->GetCurrentBuildingNPC();
	if(NULL == pBuilding)
	{
		return;
	}
	int nBuildingKind = pBuilding->buildingInfo.BuildingKind;
	if((BUILDINGKIND_CITYLEADER_LEADER != nBuildingKind)
		&&(BUILDINGKIND_CITYLEADER_OUTPOST != nBuildingKind))	// 2008-10-16 by bhsohn �������� ����, ������ ����â
	{
		return;
	}
	CMapCityShopIterator it = g_pInterface->m_pCityBase->m_mapCityShop.find(nBuildingKind);
	if(it == g_pInterface->m_pCityBase->m_mapCityShop.end() || NULL == it->second)
	{
		return;
	}
	
	// 2008-10-16 by bhsohn �������� ����, ������ ����â
	//CINFCityLeader * pCityLeader = ((CINFCityLeader*)it->second);
	int nCnt =0;

	BYTE byBelligerence=0;
	BYTE AttInfluence=0;
	ATUM_DATE_TIME timeSummon, timeSummonEnd;
	INT  nContributionPoint=0;
	INT  SummonMonsterUnitkind=0;

	char buf[256];
	memset(buf, 0x00, 256);	
	
	memset(&timeSummon, 0x00, sizeof(ATUM_DATE_TIME));
	memset(&timeSummonEnd, 0x00, sizeof(ATUM_DATE_TIME));
	

	for(nCnt =0;nCnt < m_pMotherShipC->GetSummonMotherShipCnt();nCnt++)
	{
		m_pMotherShipC->GetMotherShipInfo(nCnt, 
											&byBelligerence, 
											&timeSummon, 
											&nContributionPoint, 
											&SummonMonsterUnitkind);

		// ���� �̸� 
		memset(buf, 0x00, 256);
		MEX_MONSTER_INFO* pMonsterInfo = g_pDatabase->CheckMonsterInfo(SummonMonsterUnitkind);
		if(pMonsterInfo)
		{		
			util::strncpy(buf,pMonsterInfo->MonsterName,SIZE_MAX_MONSTER_NAME);			
		}

		// ���� ����
		AttInfluence = INFLUENCE_TYPE_VCN;
		if(byBelligerence == BELL_INFLUENCE_VCN)
		{
			// �ʼ��°� �ݴ밡 ���� �����̴�.
			AttInfluence = INFLUENCE_TYPE_ANI;
		}		

		// 2008-10-16 by bhsohn �������� ����, ������ ����â
		if(BUILDINGKIND_CITYLEADER_LEADER == nBuildingKind)
		{
			CINFCityLeader * pCityLeader = ((CINFCityLeader*)it->second);
			pCityLeader->AddWarInfoMothership(AttInfluence,	// ���ݼ���
								0,		// �¸�����(0:������)
								buf,				// ���̸�
								nContributionPoint,				// ��������Ʈ
								timeSummon,	// ���۽ð�
								timeSummonEnd);	//����ð�	
		}
		else if(BUILDINGKIND_CITYLEADER_OUTPOST == nBuildingKind)
		{
			CINFCityOutPost * pCityLeader = ((CINFCityOutPost*)it->second);
			pCityLeader->AddWarInfoMothership(AttInfluence,	// ���ݼ���
								0,		// �¸�����(0:������)
								buf,				// ���̸�
								nContributionPoint,				// ��������Ʈ
								timeSummon,	// ���۽ð�
								timeSummonEnd);	//����ð�	
			
		}
		// end 2008-10-16 by bhsohn �������� ����, ������ ����â
	}
}

void CINFGameMain::SetMotherShipTeleportTime(MSG_FC_EVENT_CLICK_TELEPORT_OK *pMsg)
{
	m_pMotherShipC->SetMotherShipSearchTeleportTime(pMsg);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::OnClickCommunity()
{
	BOOL bShow = m_pCommunity->IsShowCommunityWindow();
	bShow ^= TRUE;
	m_pCommunity->ShowCommunityWindow(bShow);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderCommunity()
{
	if(!m_pCommunity)
	{
		return;
	}
	m_pCommunity->Render();

	if (m_pQOLInfo)
		m_pQOLInfo->Render();
	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::WndProcCommunityWnd(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(!m_pCommunity)
	{
		return INF_MSGPROC_NORMAL;
	}	
	return m_pCommunity->WndProc(uMsg, wParam, lParam);	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
/// \date		2008-04-04 ~ 2008-04-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::TextReduce(CD3DHanFont *pFont, int nCutPixelX, char* buf)
{
	int nBufSize = pFont->GetStringSize(buf).cx;
	if(nBufSize < nCutPixelX)
	{
		return;
	}
	char szDstBuff[256];
	char chDummy[8];
	memset(szDstBuff, 0x00, 256);
	memset(chDummy, 0x00, 8);
	sprintf(chDummy, "..");
	
	int nCnt =0;
	int nCheckPoint=  strlen(buf);

	for(nCnt =0;nCnt < strlen(buf); nCnt++)
	{
		if(nCheckPoint <= 0)
		{
			// ó����ġ
			break;
		}
		char	*pNextStr = CharPrev(buf, &buf[nCheckPoint]);		
		if(NULL == pNextStr)
		{
			break;
		}
		int	nStringLen = pNextStr - (buf);		
		nCheckPoint = nStringLen;

		strncpy(szDstBuff, buf, nStringLen);		
		szDstBuff[nStringLen] = NULL;
		strcat(szDstBuff, chDummy);		// �ڿ� ".."�� ���δ�.

		nBufSize = pFont->GetStringSize(szDstBuff).cx;

		if(nBufSize < nCutPixelX)
		{
			strncpy(buf, szDstBuff, strlen(szDstBuff));		
			buf[strlen(szDstBuff)] = NULL;			
			break;
		}
	}
}
// 2016-07-19 panoskj disabled this
//void CINFGameMain::SetVoiceVolum(DWORD i_nVolum)
//{
//	//// ���� 1~100
//	if(i_nVolum > VOLUME_SET_MAX)
//	{
//		i_nVolum = VOLUME_SET_MAX;
//	}
//	else if(i_nVolum < VOLUME_SET_MIN)
//	{
//		i_nVolum = VOLUME_SET_MIN;
//	}
//
//	if(GetVoiceType() == VOICE_NONE)
//		return;
//	if(GetVoiceVolum() == i_nVolum)
//	{
//		return;
//	}
//	//--------------------------------------------------------------------------//
//	DBGOUT("SetVoiceVolum(1~100 : %d)\n",i_nVolum);
//	COPYDATASTRUCT	copyData;
//	DWORD			nVolum = i_nVolum;
//	memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
//	AVCallType	nCallType = _NtoNCall;
//	if(GetVoiceType() == VOICE_ONE)
//	{
//		nCallType = _1to1Call;
//	}
//	AV_MSG_WM_COPYDATA voIP(nCallType, AV_MT_SET_SPK_VOLUME, nVolum);
//	copyData.dwData = (DWORD)voIP;
//	copyData.lpData = NULL;
//	copyData.cbData = 0;
//	::SendMessage(g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient, WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(), (LPARAM)&copyData);
//	//--------------------------------------------------------------------------//
//
//	// 2008-10-20 by bhsohn VOIP ���� ����
//	m_stVOIP.nVolum = i_nVolum;
//	
//}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-10-14 by bhsohn VOIP����
/// \date		2008-10-15 ~ 2008-10-15
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
//void CINFGameMain::InitSetVoiceVolum(DWORD i_nVolum)
//{
//	m_stVOIP.nVolum = i_nVolum;
//	//// ���� 1~100
//	if(m_stVOIP.nVolum > VOLUME_SET_MAX)
//	{
//		m_stVOIP.nVolum = VOLUME_SET_MAX;
//	}
//	else if(m_stVOIP.nVolum < VOLUME_SET_MIN)
//	{
//		m_stVOIP.nVolum = VOLUME_SET_MIN;
//	}
//
//	if(m_pChat)
//	{
//		m_pChat->UpdateVoiceVolumScroll();		
//	}
//	
//}

//void CINFGameMain::SetVoiceType(BYTE i_byType)
//{
//	if(m_stVOIP.byVoiceType == i_byType)
//		return;
//	m_stVOIP.byVoiceType = i_byType;
//	EN_CHECK_TYPE tempType;
//	MSG_IC_VOIP_SET sMsg;
//	switch(i_byType)
//	{
//	case VOICE_ONE:
//		{
//			tempType = CHECK_TYPE_VOIP_1to1;
//		}
//		break;
//	case VOICE_PARTY:
//		{
//			tempType = CHECK_TYPE_VOIP_PARTY;
//		}
//		break;
//	case VOICE_GUILD:
//		{
//			tempType = CHECK_TYPE_VOIP_GUILD;
//		}
//		break;
//	default:
//		{
//			tempType = CHECK_TYPE_VOIP_NONE;
//		}
//		break;
//	}
//	DBGOUT("SetVoiceType(%d)\n",i_byType);
//	sMsg.VoipType = tempType;
//	g_pIMSocket->SendMsg(T_IC_VOIP_SET,(char*)&sMsg,sizeof(MSG_IC_VOIP_SET));
//}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-07-07 by bhsohn 2�� �н����� Ȱ��ȭ��, �κ� �ȿ����� ��
/// \date		2008-07-07 ~ 2008-07-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::IsUseSecondPassword()
{
	if((FALSE == g_pD3dApp->IsUseSecondaryPasswordSystem()) 
		||(NULL == m_pINFSecuMain))
	{
		// 2�� �н� ���� �ý����� ������.
		return FALSE;
	}
	// 2008-08-25 by bhsohn �Ʒ��� �̿��, 2�� �н����� ���� �ذ�
	else if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
	{
		return FALSE;	// �Ʒ��� ������ 2�� �н����� ������.
	}
	// end 2008-08-25 by bhsohn �Ʒ��� �̿��, 2�� �н����� ���� �ذ�
	else if(g_pD3dApp->IsSecondPassLock())
	{
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-07-14 by bhsohn EP3 ���� ó��
/// \date		2008-07-14 ~ 2008-07-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::IsRejectUser(char* pRejectName)
{
	if(!m_pCommunity || NULL == m_pCommunity->GetReject())				// 2013-06-10 by ssjung ĳ���� �ͼ��� ���� ���� �ڵ� ÷��
		return FALSE;
	
	vector<Reject_t>::iterator itReject = m_pCommunity->GetReject()->m_vecReject.begin();
	while(itReject != m_pCommunity->GetReject()->m_vecReject.end())
	{
		if(0 == stricmp(pRejectName, itReject->szRejectName))
		{
			return TRUE;
		}
		itReject++;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
/// \date		2008-09-08 ~ 2008-09-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderMirror(POINT *pMirrorPos/*=NULL*/)
{
	if(NULL == m_pInven)
	{
		return;
	}
	m_pInven->RenderMirror(pMirrorPos);
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�κ��� ������ ���� �Ǵ�
/// \author		// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
/// \date		2008-09-08 ~ 2008-09-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::IsEquipInvenShow()
{
	if(NULL == m_pInven)
	{
		return FALSE;
	}
	return m_pInven->IsEquipInvenShow();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�κ��� ������ ���� �Ǵ�
/// \author		// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
/// \date		2008-09-08 ~ 2008-09-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
D3DXMATRIX	CINFGameMain::GetInvenMatInven()
{
	if(NULL == m_pInven)
	{
		D3DXMATRIX MatInven;
		D3DXMatrixIdentity(&MatInven);
		return MatInven;
	}
	return m_pInven->GetInvenMatInven();

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�κ�â ������
/// \author		// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
/// \date		2008-09-08 ~ 2008-09-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderInvenWnd()
{
	if(m_pInven && !m_pInven->m_bRestored)
	{
		m_pInven->RestoreDeviceObjects();
	}
	if(m_pInven)
	{
		m_pInven->Render() ;
	}
	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�κ�â �޽���â
/// \author		// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
/// \date		2008-09-08 ~ 2008-09-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::WndProcInvenWnd(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_pInven && m_pInven->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
	{
		return INF_MSGPROC_BREAK;
	}
	return INF_MSGPROC_NORMAL;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�κ�â �޽���â
/// \author		// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
/// \date		2008-09-08 ~ 2008-09-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
// 2013-03-18 by bhsohn ���丮 ���� �߰�
POINT CINFGameMain::ShowShopInven(int nBuildingKind, BOOL bShowInven/*=FALSE*/)
{	
	POINT ptItem, ptEq;
	ptItem.x = ptItem.y = ptEq.x = ptEq.y = 0;
	
	if(IS_SKILL_SHOP_TYPE(nBuildingKind)
		|| IS_CASH_SHOP_TYPE(nBuildingKind)
		|| (BUILDINGKIND_REFINERY == nBuildingKind)
		|| (IS_OUTPOST_SHOP_TYPE(nBuildingKind))
		|| (IS_WARP_SHOP_TYPE(nBuildingKind))
		|| (IS_MISSION_SHOP_TYPE(nBuildingKind))
		|| (BUILDINGKIND_INFLBUFF_SHOP == nBuildingKind ) // 2013-05-07 by bhsohn ��������Ʈ ������ �ý���
		|| (BUILDINGKIND_ARENA == nBuildingKind))		
	{
		m_pInven->ShowInven(NULL, NULL, FALSE, TRUE);			
	}
	// 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
	else if((BUILDINGKIND_LUCKY_OPTION_MACHINE == nBuildingKind) && !bShowInven)
	{
		m_pInven->ShowInven(NULL, NULL, FALSE, TRUE);
	}
	//end 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
	// 2009-03-04 by bhsohn ��Ű �ӽ� ������
	else if((BUILDINGKIND_LUCKY== nBuildingKind) && !bShowInven)
	{
		m_pInven->ShowInven(NULL, NULL, FALSE, TRUE);
	}
	// end 2009-03-04 by bhsohn ��Ű �ӽ� ������
	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	else if( ( BUILDINGKIND_INFINITY == nBuildingKind ) && !bShowInven )
	{
		// ���Ǵ�Ƽ npc�� �κ��� �������� �ʴ´�
		m_pInven->ShowInven(NULL, NULL, FALSE, TRUE);
	}
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	// 2010-08-31 by shcho&&jskim, ���� �ý��� ����
	else if( ( BUILDINGKIND_DISSOLUTION == nBuildingKind ) && !bShowInven )
	{
		m_pInven->ShowInven(NULL, NULL, FALSE, TRUE);
	}
	// end 2010-08-31 by shcho&&jskim, ���� �ý��� ����
	else
	{
		// ���� ����
		ptItem.x = INVEN_ITEM_SHOP_START_X;
		ptItem.y = INVEN_ITEM_SHOP_START_Y;
		ptEq.x = INVEN_EQ_SHOP_START_X;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		ptEq.y = INVEN_ITEM_SHOP_START_Y;														  
#else 
		ptEq.y = INVEN_EQ_SHOP_START_Y;
#endif
		if(g_pD3dApp->GetHeight() < RESOLUTION_FULL_H_768)
		{
			ptEq.x = (INVEN_ITEM_SHOP_START_X-294);
			ptEq.y = INVEN_ITEM_SHOP_START_Y;			
		}

		// 2013-03-18 by bhsohn ���丮 ���� �߰�
#ifdef C_INGAME_MIX_ITEM
		if( BUILDINGKIND_FACTORY == nBuildingKind )
		{
			ptItem.x -= 115;
			ptEq.x -= 115;
		}
#endif
		// END 2013-03-18 by bhsohn ���丮 ���� �߰�

		if(ptEq.x < 0)
		{
			ptEq.x = 0;
		}
		if(ptEq.y < 0)
		{
			ptEq.y = 0;
		}

		m_pInven->ShowInven(&ptItem, &ptEq, FALSE, TRUE);
#ifndef C_EPSODE4_UI_CHANGE_JSKIM	
		// 2008-11-24 by dgwoo ��Ű �ӽ�
		if(BUILDINGKIND_LUCKY == nBuildingKind)
		{
			m_pInven->ShowInvenAndMirror(TRUE);
		}
		// 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
		else if(BUILDINGKIND_LUCKY_OPTION_MACHINE== nBuildingKind)
		{
			m_pInven->ShowInvenAndMirror(TRUE);
		}
		//end 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
		// 2010-08-31 by shcho&&jskim, ���� �ý��� ����
				        // 2011. 10. 10 by jskim UI�ý��� ����
		else if(BUILDINGKIND_DISSOLUTION == nBuildingKind)
		{
			m_pInven->ShowInvenAndMirror(TRUE);
		}
#endif
		// end 2010-08-31 by shcho&&jskim, ���� �ý��� ����
		
	}	
	return ptItem;// 2013-03-18 by bhsohn ���丮 ���� �߰�
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�ɸ���â ������
/// \author		// 2008-09-22 by bhsohn EP3 ĳ���� â
/// \date		2008-09-23 ~ 2008-09-23
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderCharacterWnd()
{
	if(m_pCharacterInfo && !m_pCharacterInfo->m_bRestored)
	{
		m_pCharacterInfo->RestoreDeviceObjects();
	}
	
	if(!m_bRightWindowModeChage && m_pCharacterInfo)
	{
		m_pCharacterInfo->Render() ;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL StringCullingUserData_ToBlank( char* strTalk, int nCullPixel, vector<string> *vecStorage, CD3DHanFont* pHanFont)
/// \brief		Enteró���� ���� �ø��Լ� ("\\n �̶�� ��Ʈ���� �����Ƿ� �� ó���ؾ���)
/// \author		// 2008-10-13 by bhsohn ���� �б� Return �ȵǴ� ���� ó��
/// \date		2008-07-24 ~ 2008-07-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::StringCullingUserData_ToNormal( char* strTalk, int nCullPixel, vector<string> *vecDstString, CD3DHanFont* pFont, BOOL bChRt /*= FALSE*/)
{
	int nCheckPoint=  0;
	char* pCheckPoint = NULL;
	char chCullingBuff[2048], chCullingTmpBuff[2048];	
	char chColorSave = 0;
	BOOL bBreak = FALSE;	
	BOOL bFindBlank = FALSE;	
	int nBlankPos = 0;	
	BOOL bFindCrtn = FALSE;		// \\n �� ã�� ���� ����
	char chCharRtn[8] = "\\n";
	
	int nCullingPos=0;
	int nLastStartPos = 0;	

	int nCullingLen =0;
	int nLastCullingLen = 0;	

	int nOldCheckPoint = 0;

	ZERO_MEMORY(chCullingBuff);
	ZERO_MEMORY(chCullingTmpBuff);
	
	//for(int nStrPos = 0;nStrPos <= strlen(strTalk); nStrPos++)
	while(TRUE)
	{
		char	*pNextStr = CharNext(&strTalk[nCheckPoint]);
		if(NULL == pNextStr)
		{
			break;
		}
		nOldCheckPoint = nCheckPoint;
		int	nNextLen = pNextStr - (strTalk + nCheckPoint);

		bFindBlank = FALSE;
		
		nCheckPoint += nNextLen;		

		nCullingLen = pNextStr - (strTalk + nLastStartPos);
		strncpy(chCullingBuff, &strTalk[nLastStartPos], nCullingLen);

		bFindCrtn = FALSE;		// \\n �� ã�� ���� ���� �ʱ�ȭ

		if(NULL == pNextStr[0] || (NULL == pNextStr))
		{
			bFindBlank = TRUE;			
			bBreak = TRUE;			
		}		
		else if(nCullingLen >= 2)
		{
			if(('\\' == chCullingBuff[nCullingLen-2]) && ('n' == chCullingBuff[nCullingLen-1]))
			{
				bFindCrtn = TRUE;		// \\n �� ã�� ���� ����			
			}			
		}

		int nBufSize = pFont->GetStringSize(chCullingBuff).cx;
		if(nBufSize >= nCullPixel || bFindCrtn)
		{			
			// ���� �߰�
			int nStringSize = strlen(chCullingBuff);
			memset(chCullingBuff, 0x00, nStringSize+1);
			if(nLastCullingLen)
			{
				// �ٽ� �޸𸮸� �ٽ� �����ؿ´�.
				strncpy(chCullingBuff, &strTalk[nLastStartPos], nLastCullingLen);				
				nCheckPoint = nCullingPos;
				// �ø� ����
				nLastStartPos = nCullingPos;						
			}
			else
			{	
				nLastCullingLen = pNextStr - (strTalk + nLastStartPos);

				// ������ ����.
				strncpy(chCullingBuff, &strTalk[nLastStartPos], nLastCullingLen);				
				
				nLastStartPos = nCheckPoint;				
				nCheckPoint = nCheckPoint;
			}		

			chColorSave = StringCullingAddVector_ToNormal(chColorSave, chCullingBuff, vecDstString);
			ZERO_MEMORY(chCullingBuff);				
			
			if(bBreak)
			{
				// ������ ��ã�� �ִ� �ȼ����� �Ѿ���.
				nCullingLen = pNextStr - (strTalk + nLastStartPos);
				if(nCullingLen)
				{
					strncpy(chCullingBuff, &strTalk[nLastStartPos], nCullingLen);			
					chColorSave = StringCullingAddVector_ToNormal(chColorSave, chCullingBuff, vecDstString);
					ZERO_MEMORY(chCullingBuff);	
				}
				
			}
			bFindBlank = FALSE;			
			
			nLastCullingLen = 0;
			nCullingPos = 0;
		}		
		else if(bBreak)
		{
			// ������ ��ã�� �ִ� �ȼ����� �Ѿ���.
			nCullingLen = pNextStr - (strTalk + nLastStartPos);
			if(nCullingLen)
			{
				strncpy(chCullingBuff, &strTalk[nLastStartPos], nCullingLen);			
				chColorSave = StringCullingAddVector_ToNormal(chColorSave, chCullingBuff, vecDstString);			
			}
		}
		else if(bFindBlank)
		{	
			nLastCullingLen = nCullingLen;
			nCullingPos = nCheckPoint;
		}		

		if(bBreak)
		{
			break;
		}

	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL StringCullingUserData_ToBlank( char* strTalk, int nCullPixel, vector<string> *vecStorage, CD3DHanFont* pHanFont)
/// \brief		Enteró���� ���� �ø��Լ� ("\\n �̶�� ��Ʈ���� �����Ƿ� �� ó���ؾ���)
/// \author		// 2008-10-13 by bhsohn ���� �б� Return �ȵǴ� ���� ó��
/// \date		2008-07-24 ~ 2008-07-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char CINFGameMain::StringCullingAddVector_ToNormal(char chColorSave, char* pString, vector<string> *vecDstString)
{
	char chCullingTmpBuff[2048];
	// 2008-07-24 by bhsohn �ø� ���� ���� ����
	char chFindColor = GetFindColorOnTxt(pString);				

	ZERO_MEMORY(chCullingTmpBuff);
	// 2008-07-24 by bhsohn �ø� ���� ���� ����
	//if(0 == chFindColor && chColorSave )
	if(chColorSave )
	{
		// Į���� ������ ������ Į�� �־���
		strncpy(chCullingTmpBuff, pString, 2048);
		sprintf(pString, "\\%c%s", chColorSave, chCullingTmpBuff);
		chFindColor = GetFindColorOnTxt(pString);				
		chColorSave = chFindColor;
	}
	else if('n' == chFindColor)
	{
		chColorSave = 0;	// \\n �� ���� �ƴϴ�.
	}
	else if(0 != chFindColor )
	{
		// �����÷� ����
		chColorSave = chFindColor;
	}

	// �ø��� ���ϴ� �ȼ����� ū�� üũ�Ѵ�.
	vecDstString->push_back(pString);

	return chColorSave;	
}
						  
///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL StringCullingUserData_ToBlank( char* strTalk, int nCullPixel, vector<string> *vecStorage, CD3DHanFont* pHanFont)
/// \brief		Enteró���� ���� �ø��Լ� ("\\n �̶�� ��Ʈ���� �����Ƿ� �� ó���ؾ���)
/// \author		// 2008-10-13 by bhsohn ���� �б� Return �ȵǴ� ���� ó��
/// \date		2008-07-24 ~ 2008-07-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char CINFGameMain::DelCharacterRetrn(char* o_pTxt)
{
	int nCnt = 0;
	int nRtnPos = -1;
	int nStringLen = strlen(o_pTxt);
	BOOL bCharcterRtn = FALSE;
	
	for(nCnt = 0;nCnt < nStringLen;nCnt++)
	{
		if('\\' == o_pTxt[nCnt])
		{
			bCharcterRtn = TRUE;
		}
		else if(bCharcterRtn)
		{
			bCharcterRtn = FALSE;
			if('n' == o_pTxt[nCnt])
			{
				nRtnPos = nCnt;
			}
		}		
	}
	if(nRtnPos >= 1)
	{
		o_pTxt[nRtnPos-1] = NULL;
		o_pTxt[nRtnPos] = NULL;
	}
	
	// 2008-10-29 by bhsohn ����Ʈ �ڽ� ���� ����
	int nIdx = strlen(o_pTxt)-1;	// ������ ��Ʈ����
	if(nIdx < 0)
    {
		nIdx = 0;
    }
	return o_pTxt[nIdx];
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-10-15 by bhsohn ���ҽ� �޸� ��ȣ ��� �߰�
/// \date		2008-10-15 ~ 2008-10-15
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::CreateChatChild_OperationMode(TCHAR *str,int type, int chatType/* = CHAT_TAB_SYSTEM*/, char* szWisperToCharacterName, char *szWisperFromCharacterName)
{
	// �����ڰ� �ƴϸ� ���� ���ƶ�
	const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
	if (!COMPARE_RACE(myShuttleInfo.Race, RACE_OPERATION | RACE_GAMEMASTER | RACE_MONITOR))
	{
		return FALSE;
	}
	if(g_pD3dApp && g_pD3dApp->m_pChat)
	{
		g_pD3dApp->m_pChat->CreateChatChild(str,type, chatType, szWisperToCharacterName, szWisperFromCharacterName);
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-10-14 by bhsohn VOIP����
/// \date		2008-10-15 ~ 2008-10-15
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
// 2016-07-19 panoskj disabled this
//void CINFGameMain::ChangeVOIPMode()
//{
//	BOOL bGetVOIPSpeaking = GetVOIPSpeaking();
//	bGetVOIPSpeaking^= TRUE;	
//
//	if(bGetVOIPSpeaking)
//	{
//		COPYDATASTRUCT	copyData;
//		memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
//		AV_MSG_WM_COPYDATA voIP(_NtoNCall, AV_MT_TALK, 0);
//		copyData.dwData = (DWORD)voIP;
//		copyData.lpData = NULL;
//		copyData.cbData = 0;
//		::SendMessage(g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient, 
//			WM_COPYDATA, 
//			(WPARAM)g_pD3dApp->GetHwnd(), 
//			(LPARAM)&copyData);
//	}
//	else
//	{
//		ReleaseVOIPMode();		
//	}	
//}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		VOIP����
/// \author		// 2008-10-14 by bhsohn VOIP����
/// \date		2008-10-15 ~ 2008-10-15
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
// 2016-07-19 panoskj disabled this
//void CINFGameMain::ReleaseVOIPMode()
//{
//	BOOL bGetVOIPSpeaking = GetVOIPSpeaking();
//	if(!bGetVOIPSpeaking)
//	{
//		return;
//	}
//	COPYDATASTRUCT	copyData;
//	memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));
//	AV_MSG_WM_COPYDATA voIP(_NtoNCall, AV_MT_TALK_CANCEL, 0);
//	copyData.dwData = (DWORD)voIP;
//	copyData.lpData = NULL;
//	copyData.cbData = 0;
//	::SendMessage(g_pD3dApp->m_VOIPState.m_hWndAtumVoIPClient, WM_COPYDATA, (WPARAM)g_pD3dApp->GetHwnd(), (LPARAM)&copyData);
//}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-10-14 by bhsohn VOIP����
/// \date		2008-10-15 ~ 2008-10-15
/// \warning	
///
/// \param		
/// \return		
/////////////////////////////////////////////////////////////////////////////////
//void CINFGameMain::SetVOIPSpeaking(BOOL i_bVOIPSpeaking)
//{
//	m_bVOIPSpeaking = i_bVOIPSpeaking;
//}
/////////////////////////////////////////////////////////////////////////////////
///// \fn			
///// \brief		
///// \author		// 2008-10-14 by bhsohn VOIP����
///// \date		2008-10-15 ~ 2008-10-15
///// \warning	
/////
///// \param		
///// \return		
/////////////////////////////////////////////////////////////////////////////////
//BOOL CINFGameMain::GetVOIPSpeaking()
//{
//	return m_bVOIPSpeaking;
//}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
/// \date		2008-11-3 ~ 2008-11-3
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::OnClickServerTime()
{
	if(NULL == m_pINFGameMainSysMsg)
	{
		return;
	}

	BOOL bShow = m_pINFGameMainSysMsg->IsShowWnd();
	bShow ^= TRUE;
	ShowSysMsgWnd(bShow);

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
/// \date		2008-11-3 ~ 2008-11-3
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::ShowSysMsgWnd(BOOL bShowWnd)
{
	if(NULL == m_pINFGameMainSysMsg)
	{
		return;
	}
	POINT ptPos = m_pINFGameMainSysMsg->GetWndPos();
	if(0 >= ptPos.x && 0 >= ptPos.y)
	{
		ptPos.x = GAMEMAIN_SERVER_TIME_X;
		ptPos.y = GAMEMAIN_SERVER_TIME_Y;
	}	

	int nCapWidth = GAMEMAIN_SERVER_TIME_WIDTH;

	if(bShowWnd)
	{
		ATUM_DATE_TIME curServerTime = GetServerDateTime();

		string szStrBuf;
		curServerTime.GetLocalString_YYYYMMDD(curServerTime.Year,
			curServerTime.Month, 
			curServerTime.Day, 
			szStrBuf);	
		int nHour = curServerTime.Hour;
		int nMinute = curServerTime.Minute;

		char chTimeString[MAX_PATH];
		char chAmPm[32];
		// 2008. 11. 21 ���� �ð� �����ֱ�, �ڽ� ����
		char chTime[256];
		memset(chTimeString, 0x00, MAX_PATH);

		wsprintf(chAmPm, STRMSG_C_081103_0200);	//"AM"
		if(nHour > 12)
		{
			nHour -= 12;
			wsprintf(chAmPm, STRMSG_C_081103_0201);	//"PM"
		}

		// 2008. 11. 21 ���� �ð� �����ֱ�, �ڽ� ����
		wsprintf(chTimeString, "%s", (char*)szStrBuf.c_str());
		wsprintf(chTime, "%s %02d:%02d", chAmPm, nHour, nMinute);
// 		wsprintf(chTimeString, "%s %s %02d:%02d", 
// 			(char*)szStrBuf.c_str(), 
// 			chAmPm,
// 			nHour, 
// 			nMinute);
		
		
		m_pINFGameMainSysMsg->InitString();		
		m_pINFGameMainSysMsg->SetString(STRMSG_C_081103_0202);
		m_pINFGameMainSysMsg->SetString(chTimeString);
		// 2008. 11. 21 by ckPark ���� �ð� �����ֱ�, �ڽ� ����
		m_pINFGameMainSysMsg->SetString(chTime);

	}
	
	m_pINFGameMainSysMsg->ShowWnd(bShowWnd, &ptPos, nCapWidth);
}
// 2012-03-16 by jhahn FŰ�� ���ܵ� �ð谡 ���̰� ����
void CINFGameMain::RenderSysTimer()
{
	RenderSysMsgWnd();

}
//end 2012-03-16 by jhahn FŰ�� ���ܵ� �ð谡 ���̰� ����
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
/// \date		2008-11-3 ~ 2008-11-3
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderSysMsgWnd()
{
	if(NULL == m_pINFGameMainSysMsg )
	{
		return;
	}
	else if(!m_pINFGameMainSysMsg->IsShowWnd() )
	{
		return;
	}

	// 2012-12-10 by jhjang �ð� ǥ�� ����
// 	ATUM_DATE_TIME curServerTime = GetServerDateTime();
// 
// 	string szStrBuf;
// 	curServerTime.GetLocalString_YYYYMMDD(curServerTime.Year,
// 		curServerTime.Month, 
// 		curServerTime.Day, 
// 		szStrBuf,
// 		GetLanguageType());	
// 	int nHour = curServerTime.Hour;
// 	int nMinute = curServerTime.Minute;
// 	
// 	char chTimeString[MAX_PATH];
// 	char chAmPm[32];
// 	// 2008. 11. 21 by ckPark ���� �ð� �����ֱ�, �ڽ� ����
// 	char chTime[256];
// 
// 	memset(chTimeString, 0x00, MAX_PATH);
// 	
// 	// 2009. 05. 28 by ckPark ���� �ð� AM PM ���� ����
// // 	wsprintf(chAmPm, STRMSG_C_081103_0200);	//"AM"
// // 	if(nHour > 12)
// // 	{
// // 		nHour -= 12;
// // 		wsprintf(chAmPm, STRMSG_C_081103_0201);	//"PM"
// // 	}
// 
// 	if( 0 <= nHour && nHour <= 11)
// 		wsprintf(chAmPm, STRMSG_C_081103_0200);	// AM
// 	else
// 		wsprintf(chAmPm, STRMSG_C_081103_0201); // PM
// 	// end 2009. 05. 28 by ckPark ���� �ð� AM PM ���� ����
// 	
// 	// 2008. 11. 21 by ckPark ���� �ð� �����ֱ�, �ڽ� ����
// 	wsprintf(chTimeString, "%s", (char*)szStrBuf.c_str());
// 	wsprintf(chTime, "%s %02d:%02d", chAmPm, nHour, nMinute);
// 
// 	m_pINFGameMainSysMsg->UpdateString(1, chTimeString);
// 	m_pINFGameMainSysMsg->UpdateString(2, chTime);
// // 	wsprintf(chTimeString, "%s %s %02d:%02d", 
// // 		(char*)szStrBuf.c_str(), 
// // 		chAmPm,
// // 		nHour, 
// // 		nMinute);
// // 	m_pINFGameMainSysMsg->UpdateString(1, chTimeString);
	// end 2012-12-10 by jhjang �ð� ǥ�� ����

	m_pINFGameMainSysMsg->Render();

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-11-13 by bhsohn EP3-2 ���� ���� ���� �Ǹ� �ȵǴ� ���� ����
/// \date		2008-11-13 ~ 2008-11-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::ClearSetIconInfo()
{
	POINT ptNull;
	ptNull.x = ptNull.y = 0;
	SetSelectItem(NULL, ptNull, ITEM_NOT_POS);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-11-13 by bhsohn ���̽�ƽ �۾�
/// \date		2008-11-13 ~ 2008-11-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::ShowOpJoystick(BOOL bShow)
{
	if(NULL == m_pINFOpJoystick)
	{
		return;
	}
	if(bShow)
	{
		POINT ptPos;

		ptPos.x = JOYSTICK_WND_POS_X;
		ptPos.y = JOYSTICK_WND_POS_Y;

		// �ֿ켱 ������
		g_pInterface->SetWindowOrder(WNDOpJoystick);// ���̽�ƽ �ɼ�
		m_pINFOpJoystick->ShowWnd(TRUE, &ptPos);
	}
	else
	{
		m_pINFOpJoystick->ShowWnd(FALSE, NULL);
	}
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-11-13 by bhsohn ���̽�ƽ �۾�
/// \date		2008-11-13 ~ 2008-11-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::IsShowOpJoystick()
{
	if(NULL == m_pINFOpJoystick)
	{
		return FALSE;
	}
	return m_pINFOpJoystick->IsShowWnd();

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-11-13 by bhsohn ���̽�ƽ �۾�
/// \date		2008-11-13 ~ 2008-11-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::WndProcOpJoystickWnd(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(!m_pINFOpJoystick)
	{
		return INF_MSGPROC_NORMAL;
	}	
	return m_pINFOpJoystick->WndProc(uMsg, wParam, lParam);	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-11-13 by bhsohn ���̽�ƽ �۾�
/// \date		2008-11-13 ~ 2008-11-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderOpJoystickWnd()
{
	if(!m_pINFOpJoystick)
	{
		return;
	}	
	m_pINFOpJoystick->Render();

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		�ٸ� �̸����� ���̽�ƽ ���� ����
/// \author		// 2008-11-13 by bhsohn ���̽�ƽ �۾�
/// \date		2008-11-13 ~ 2008-11-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SaveAsJoysticSetupInfo(char* pSaveAsFilename)
{
	if(!m_pINFOpJoystick)
	{
		return;
	}
	m_pINFOpJoystick->SaveAsJoysticSetupInfo(pSaveAsFilename);

}



// 2008. 12. 16 by ckPark ������ ��� ����
///////////////////////////////////////////////////////////////////////////////
/// \fn		: CINFGameMain::PushDelayItem
/// \brief	: ����� ���� �������� ť�� �ִ´�
///			  �������� ���̰ų� �̹� ������ ��������� ���
///			  FALSE ����
/// \author	: ckPark
/// \date	: 16:12:2008   14:59
/// \warning: 
/// \param	: const CItemInfo * pItemInfo
/// \return	: void
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMain::PushDelayItem(CItemInfo* pItemInfo)
{
	// ������ ������ �߸����?���
	if(!pItemInfo)
		return FALSE;
	
	// ����Ʈ�� ���� ��ȸ�ϸ�
	std::list<ITEM_DELAY>::iterator end = m_listItemDelay.end();
	for(std::list<ITEM_DELAY>::iterator it = m_listItemDelay.begin(); it != end; ++it)
	{
		// �̹� ���� ����ũ�ѹ��� ����Ʈ�� ���� ���
		if( (*it).nItemUniqueNumber == pItemInfo->UniqueNumber )
		{
			// �̹� ������Դϴ�
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_081216_0303, COLOR_ITEM);
			return FALSE;
		}
	}
	
	const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
	// ���� ���� ���� ���
	if(IS_CITY_MAP_INDEX(myShuttleInfo.MapChannelIndex.MapIndex))
	{
		// ����Ʈ�� Ǫ������ �ʰ� �ٷ� ������
		g_pGameMain->m_pInven->SendUseItem( static_cast<CItemInfo*>(pItemInfo) );
	}
	else
	{
		// ���� ���� �ƴ� ���
		ITEM_DELAY	item_delay;
		item_delay.nItemUniqueNumber	= pItemInfo->UniqueNumber;
		item_delay.nItemUseTime			= timeGetTime();
		item_delay.nItemDelayTime		= pItemInfo->GetItemInfo()->AttackTime;
		
		// ����Ʈ�� Ǫ��
		m_listItemDelay.push_back(item_delay);
	}

	// xx�������� �ߵ� ���Դϴ�
	char szBuff[256];
	sprintf(szBuff, STRMSG_C_081216_0301, pItemInfo->GetItemInfo()->ItemName);
	g_pD3dApp->m_pChat->CreateChatChild(szBuff, COLOR_ITEM);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn		: CINFGameMain::ReleaseDelayItem
/// \brief	: �����̾����� ����Ʈ�� Ŭ�����Ѵ�( ex> �׾��� ��)
/// \author	: ckPark
/// \date	: 16:12:2008   16:34
/// \warning: 
/// \param	: void
/// \return	: void
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::ReleaseDelayItem(void)
{
	m_listItemDelay.clear();
}
///////////////////////////////////////////////////////////////////////////////
/// \fn		: CINFGameMain::TickItemDelay(void)
/// \brief	: �����̾����� ����Ʈ�� Ŭ�����Ѵ�( ex> �׾��� ��)
/// \author	: ckPark
/// \date	: 16:12:2008   16:34
/// \warning: 
/// \param	: void
/// \return	: void
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::TickItemDelay(void)
{
	if(m_listItemDelay.empty())
	{
		return;
	}
	// ���� �ð�
	DWORD	dwCurTime = timeGetTime();
	
	std::list<ITEM_DELAY>::iterator end		= m_listItemDelay.end();
	std::list<ITEM_DELAY>::iterator it		= m_listItemDelay.begin();
	while(it != end)
	{
		// ����ð��� ������ �����̽ð� + ����� �ð� ���� ���� ��� ���� ����������
		if(dwCurTime < (*it).nItemDelayTime + (*it).nItemUseTime)
			++it;
		else
		{
			// ����ð��� ������ �����̽ð� + ����� �ð� ���� Ŭ ��� �������� ���� ����Ѵ�
			// ����ũ �ѹ��� �κ����� �������� ã�´�
			CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( (*it).nItemUniqueNumber );
			// �κ����� ã���� ��츸
			if(pItemInfo)
			{
				// ������ ��� ��Ŷ ����
				g_pGameMain->m_pInven->SendUseItem( static_cast<CItemInfo*>( pItemInfo ) );
				
				// xx�������� ����մϴ�.
				char szBuff[256];
				sprintf(szBuff, STRMSG_C_081216_0302, pItemInfo->GetItemInfo()->ItemName);
				g_pD3dApp->m_pChat->CreateChatChild(szBuff, COLOR_ITEM);
			}
			
			// ������ �ð��� ���� �������� ������ ��Ŷ�� ������ �Ⱥ����� �����Ѵ�
			it = m_listItemDelay.erase(it);
		}
	}
}
// end 2008. 12. 16 by ckPark ������ ��� ����







// 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����
BOOL CINFGameMain::PushDelaySkill(CSkillInfo* pSkillInfo, UID32_t nTargetUniqueNumber)
{
	if(!pSkillInfo)
		return FALSE;

	std::list<SKILL_DELAY>::iterator end = m_listSkillDelay.end();
	for(std::list<SKILL_DELAY>::iterator it = m_listSkillDelay.begin(); it != end; ++it)
	{
		if( (*it).pSkillInfo == pSkillInfo )
		{
			// �̹� ������Դϴ�
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_081216_0303, COLOR_ITEM);
			return FALSE;
		}
	}

	SKILL_DELAY		skill_delay;

	skill_delay.pSkillInfo				= pSkillInfo;
	skill_delay.nSkillUseTime			= timeGetTime();
	skill_delay.nSkillDelayTime			= pSkillInfo->ItemInfo->AttackTime;
	skill_delay.nTargetUniqueNumber		= nTargetUniqueNumber;

	m_listSkillDelay.push_back(skill_delay);

	return TRUE;
}

void CINFGameMain::ReleaseDelaySkill(void)
{
	m_listSkillDelay.clear();
}

void CINFGameMain::TickSkillDealy(void)
{
	if( m_listSkillDelay.empty( ) )
		return;

	DWORD dwCurTime = timeGetTime();

	std::list<SKILL_DELAY>::iterator end	= m_listSkillDelay.end();
	std::list<SKILL_DELAY>::iterator it		= m_listSkillDelay.begin();

	while(it != end)
	{
		if(dwCurTime < (*it).nSkillDelayTime + (*it).nSkillUseTime )
			++it;
		else
		{
			// 2009. 04. 06 by ckPark �ݿ�������ν� �ٸ� Ÿ���� ��ų ������ ����
			g_pShuttleChild->m_pSkill->SetCharacterUID( (*it).nTargetUniqueNumber );
			g_pGameMain->m_pCharacterInfo->SendUseSkill( (*it).pSkillInfo );
			//g_pD3dApp->m_pShuttleChild->m_pSkill->SendConfirmSkillUse( (*it).pSkillInfo, (*it).nTargetUniqueNumber );
			// end 2009. 04. 06 by ckPark �ݿ�������ν� �ٸ� Ÿ���� ��ų ������ ����
			it = m_listSkillDelay.erase( it );
			break;
		}
	}
}
// end 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����


// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
CINFImageEx*	CINFGameMain::FindBigIcon( int nItemnum )
{
	return m_pItemInfo->FindBigIcon( nItemnum );
}
// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


// 2010. 02. 11 by ckPark �ߵ��� ����������
void	CINFGameMain::PushInvokeWearItem( UID64_t nItemUID )
{
	CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( nItemUID );
	// ������ ������ ���ų� ��Ÿ���� 0������ ���� ����Ʈ���� �����Ѵ�
	if( !pItemInfo || pItemInfo->GetCoolElapsedTime() <= 0 )
	{
		PopInvokeWearItem( nItemUID );
		return;
	}

	std::list<INVOKEITEM_COOLTIME>::iterator it = m_listInvokeItemCoolTime.begin();
	while( it != m_listInvokeItemCoolTime.end() )
	{
		// �̹� �����ϴ� ��Ÿ�� ����Ʈ�� ���ؼ��� ���� ���Ÿ� �Ѵ�
		if( nItemUID == (*it).nItemUID )
		{
			(*it).nItemUID				= nItemUID;
			(*it).nPrevTickTime			= timeGetTime();
			(*it).bSendEndCoolTime		= FALSE;
			return;
		}

		++it;
	}

	// ��Ÿ�� ����Ʈ�� �߰�
	INVOKEITEM_COOLTIME item;
	item.nItemUID				= nItemUID;
	item.nPrevTickTime			= timeGetTime();
	item.bSendEndCoolTime		= FALSE;
	m_listInvokeItemCoolTime.push_back( item );
}

void	CINFGameMain::PopInvokeWearItem( UID64_t nItemUID )
{
	// ��Ÿ�� ����Ʈ�� ����
	std::list<INVOKEITEM_COOLTIME>::iterator it = m_listInvokeItemCoolTime.begin();
	while( it != m_listInvokeItemCoolTime.end() )
	{
		if( nItemUID == (*it).nItemUID )
		{
			it = m_listInvokeItemCoolTime.erase( it );
			return;
		}

		++it;
	}
}

void	CINFGameMain::TickInvokeWearItem( void )
{
	std::list<INVOKEITEM_COOLTIME>::iterator it = m_listInvokeItemCoolTime.begin();
	while( it != m_listInvokeItemCoolTime.end() )
	{
		CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( (*it).nItemUID );
		if( pItemInfo
			&& (*it).nItemUID == pItemInfo->UniqueNumber
			&& pItemInfo->Wear == WEAR_ATTACHED
			&& (pItemInfo->ItemInfo->InvokingDestParamID || pItemInfo->ItemInfo->InvokingDestParamIDByUse) )
		{
			INT nElapsedTime		= pItemInfo->GetCoolElapsedTime();
			DWORD nCurTime			= timeGetTime();
			nElapsedTime			+= (nCurTime - (*it).nPrevTickTime);
			pItemInfo->SetCoolElapsedTime( nElapsedTime );
			(*it).nPrevTickTime		= nCurTime;

			// ���� ��Ÿ���� �������ٸ� ������ ����
			// ���� 2�� ������ �ʴ´�
			if( !((*it).bSendEndCoolTime) && (nElapsedTime > pItemInfo->ItemInfo->ReAttacktime ) )
			{
				MSG_FC_ITEM_END_COOLINGTIME_ITEM msg;
				msg.ItemUID	= pItemInfo->UniqueNumber;
				g_pFieldWinSocket->SendMsg( T_FC_ITEM_END_COOLINGTIME_ITEM, (char*)(&msg), sizeof( MSG_FC_ITEM_END_COOLINGTIME_ITEM ) );

				(*it).bSendEndCoolTime	= TRUE;
			}
		}

		++it;
	}
}

void	CINFGameMain::SetItemCoolStart( UID64_t nItemUID )
{
	CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( nItemUID );
	if( pItemInfo )
	{
		if( pItemInfo->ItemInfo->ReAttacktime == 0 )
			return;
		
		// ��Ÿ���� 1(0.001��)�� ���������� ��Ÿ���� �����Ѵ�
		// 0�� ��Ÿ���� �ƿ����ٴ� ��....
		pItemInfo->SetCoolElapsedTime( 1 );

		// ������ �������̸� ��Ÿ�Ӹ���Ʈ�� �߰��Ѵ�
		if( pItemInfo && pItemInfo->Wear == WEAR_ATTACHED )
			PushInvokeWearItem( nItemUID );
	}
}

void	CINFGameMain::SetItemCoolEnd( UID64_t nItemUID )
{
	CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( nItemUID );
	// ��Ÿ���� 0���� ���������� ��Ÿ�� ����
	// 0�� ��Ÿ���� �ƿ����ٴ� ��....
	if( pItemInfo )
		pItemInfo->SetCoolElapsedTime( 0 );

	// ��Ÿ�� ����Ʈ�� ����
	PopInvokeWearItem( nItemUID );
}

void	CINFGameMain::RefreshInvokeItemTickTime( UID64_t nItemUID )
{
	std::list<INVOKEITEM_COOLTIME>::iterator it = m_listInvokeItemCoolTime.begin();
	// �� ������ ��Ÿ�� ��� �ð��� ����
	while( it != m_listInvokeItemCoolTime.end() )
	{
		if( (*it).nItemUID == nItemUID )
		{
			(*it).nPrevTickTime	= timeGetTime();
			return;
		}

		++it;
	}
}
// end 2010. 02. 11 by ckPark �ߵ��� ����������


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-01-30 by bhsohn ���� ���� �Է� ��� ����
/// \date		2009-01-30 ~ 2009-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::GetKeyDownToNumber(LPARAM i_lParam)
{
	int nLen = sizeof(m_stucTable)/sizeof(structNumTable);
	int nCnt =0;
	int nRtn = -1;
	for(nCnt =0;nCnt<nLen;nCnt++)
	{
		if(i_lParam == m_stucTable[nCnt].dwKeyValue)
		{
			nRtn = m_stucTable[nCnt].nKey;
			break;
		}
		
	}
	return nRtn;
	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2012-12-10 by jhjang �Ʒ��� ��ȣ ������ �����ϰ� �Է� ���� 
/// \date		2012-12-10 ~ 2012-12-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char CINFGameMain::GetKeyDownToNumberAndAlphabet(WPARAM wParam)
{
	if((0x30 <= wParam && wParam <= 0x39) ||	//Ű ���� ������ 0~9�����϶�
		(0x41 <= wParam && wParam <= 0x5A) ||	//Ű ���� A~Z�϶�
		(0x61 <= wParam && wParam <= 0x7A))		//Ű ���� a~z�϶�
	{
		return wParam;
	}
	return -1;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-03 by bhsohn ���� ������ �� ����
/// \date		2009-02-03 ~ 2009-02-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetItemInfoUser( CItemInfo* pItemInfo, int x, int y, BOOL bShowMyEq/*=TRUE*/, int nLinkItem/*=0*/, BOOL bInven /*FALSE*/)  // 2013-06-26 by ssjung �κ��丮 �߰� ���� 
{	
	// �Ϲ� ����
	m_pItemInfo->SetItemInfoUser( pItemInfo, x, y ,0,bInven);	   // 2013-06-26 by ssjung �κ��丮 �߰� ���� 

	m_bShowMyEqTooltip = bShowMyEq; // �� ��� ���̴��� ����
	if(NULL == pItemInfo)
	{
		m_pEquipItemInfo->SetItemInfoUser( pItemInfo, x, y);
	}
	else if(GetAsyncKeyState(VK_SHIFT) && bShowMyEq)
	{			
		ITEM* pITEM = pItemInfo->GetItemInfo();
		CItemInfo* pMyEqITEM = GetItem_To_MyEqITEM(pITEM);
		if(NULL == pMyEqITEM)
		{
			// �ʱ�ȭ
			m_pEquipItemInfo->SetItemInfoUser( NULL, 0, 0);
			RefreshItemTooltipPos();
			return;
		}
		
		if(pMyEqITEM)
		{
			int nPosX = m_pItemInfo->GetMaxLength();
			if(nPosX > 0)
			{
				nPosX += 12;	// 12��ŭ �� ����
			}
			nPosX += x;	
			int nPosY = y;	
			m_pEquipItemInfo->SetItemInfoUser( pMyEqITEM, nPosX, nPosY);						
		}
	}
	else
	{
		// �ʱ�ȭ
		m_pEquipItemInfo->SetItemInfoUser( NULL, 0, 0);
	}
	RefreshItemTooltipPos();
	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-03 by bhsohn ���� ������ �� ����
/// \date		2009-02-03 ~ 2009-02-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::ShowItemInfo(BOOL bShow)
{
	m_pItemInfo->ShowItemInfo(bShow);
	m_pEquipItemInfo->ShowItemInfo(bShow);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-03 by bhsohn ���� ������ �� ����
/// \date		2009-02-03 ~ 2009-02-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::SetItemInfoNormal( ITEM* pITEM, int x, int y, BOOL bShop, int nItemCount /*= 0*/, BOOL bShowMyEq/*=TRUE*/, int nLinkItem/*=0*/, BOOL ArmorCollect /*FALSE*/)// 2013-06-10 by ssjung �Ƹ� �÷��� ���� ǥ��
{	
	// 2013-04-11 by bhsohn �ΰ��� ����â ���� ���� ��þƮ �ý��� �˻�
//	m_pItemInfo->SetItemInfoNormal( pITEM, x, y, bShop, nItemCount );
	m_pItemInfo->SetItemInfoNormal( pITEM, x, y, bShop, nItemCount, nLinkItem,ArmorCollect);// 2013-06-10 by ssjung �Ƹ� �÷��� ���� ǥ��
	// END 2013-04-11 by bhsohn �ΰ��� ����â ���� ���� ��þƮ �ý��� �˻�

	m_bShowMyEqTooltip = bShowMyEq; // �� ��� ���̴��� ����

	if(NULL == pITEM)
	{
		m_pEquipItemInfo->SetItemInfoNormal( pITEM, x, y, bShop, nItemCount );
	}
	else if(GetAsyncKeyState(VK_SHIFT) && bShowMyEq)
	{
		CItemInfo* pMyEqITEM = GetItem_To_MyEqITEM(pITEM);
		if(NULL == pMyEqITEM)
		{
			m_pEquipItemInfo->SetItemInfoNormal( NULL, 0, 0, 0, 0);
			RefreshItemTooltipPos();
			return;
		}

		int nPosX = m_pItemInfo->GetMaxLength();
		if(nPosX > 0)
		{
			nPosX += 12;	// 12��ŭ �� ����
		}
		nPosX += x;	
		int nPosY = y;		
		
		m_pEquipItemInfo->SetItemInfoNormal( pMyEqITEM->GetItemInfo(), nPosX, nPosY, bShop, nItemCount );
	}
	else
	{
		m_pEquipItemInfo->SetItemInfoNormal( NULL, 0, 0, 0, 0);
	}
	RefreshItemTooltipPos();
	

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-03 by bhsohn ���� ������ �� ����
/// \date		2009-02-03 ~ 2009-02-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::ShowMyEqItemTooltip()
{
	if(NULL == m_pItemInfo)
	{
		return;
	}
	CItemInfo*	pItemInfo = m_pItemInfo->GetRefItemInfo();	
	if(NULL == pItemInfo)
	{
		return;
	}

	ITEM* pITEM = pItemInfo->GetItemInfo();
	CItemInfo* pMyEqITEM = GetItem_To_MyEqITEM(pITEM);
	if((NULL == pMyEqITEM)
		||(!m_bShowMyEqTooltip))
	{
		// �ʱ�ȭ
		m_pEquipItemInfo->SetItemInfoUser( NULL, 0, 0);
		RefreshItemTooltipPos();
		return;
	}
	
	POINT ptPos = m_pItemInfo->GetItemInfoPos();
	if(pMyEqITEM)
	{
		int nPosX = m_pItemInfo->GetMaxLength();
		if(nPosX > 0)
		{
			nPosX += 12;	// 12��ŭ �� ����
		}
		nPosX += ptPos.x;	
		int nPosY = ptPos.y;	
		m_pEquipItemInfo->SetItemInfoUser( pMyEqITEM, nPosX, nPosY);		
	}
	RefreshItemTooltipPos();

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-03 by bhsohn ���� ������ �� ����
/// \date		2009-02-03 ~ 2009-02-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderItemInfo()
{
	if(m_pItemInfo)
	{
		m_pItemInfo->Render();
	}
	if(m_pEquipItemInfo)
	{
		m_pEquipItemInfo->Render();
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-03 by bhsohn ���� ������ �� ����
/// \date		2009-02-03 ~ 2009-02-03
/// \warning	
///
/// \param		
/// \return		
/////////////////////////////////////////////////////////////////////////////// 
CItemInfo* CINFGameMain::GetItem_To_MyEqITEM(ITEM* i_pItem)
{
	if(NULL == i_pItem)
	{
		return NULL;
	}

	int nWindowPos = 0;
	
	if(IS_PRIMARY_WEAPON(i_pItem->Kind))
	{
		// 1�� ����(���� ����)	--> ���� 1��
		nWindowPos = POS_PROWOUT;
	}
	else if(IS_SECONDARY_WEAPON(i_pItem->Kind))
	{		
		// 2�� ����(���� ����)	--> ���� 1��
		nWindowPos = POS_WINGOUT;

	}
	else if(ITEMKIND_DEFENSE == i_pItem->Kind)
	{
		// �Ƹ�(�߾� ���)	--> ���� 4��
		nWindowPos = POS_CENTER;
	}
	else if(ITEMKIND_SUPPORT == i_pItem->Kind)
	{
		// ����(�Ĺ� ���)	--> ���� 3��
		nWindowPos = POS_REAR;

	}
	else if(ITEMKIND_RADAR == i_pItem->Kind)
	{
		// ���̴�(���� ���)	--> ���� 2��
		nWindowPos = POS_PROW;
	}
	else if(ITEMKIND_COMPUTER == i_pItem->Kind)
	{		
		// ��ǻ��(�߾� ����)	--> ���� 2��
		nWindowPos = POS_PROWIN;
	}
	else if(ITEMKIND_ACCESSORY_UNLIMITED == i_pItem->Kind)
	{
		// ������ �Ǽ��縮 - ������(�Ĺ� ����-������ũ|�����̳ʰ迭) --> ���� 3��
		nWindowPos = POS_ACCESSORY_UNLIMITED;
	}
	else if(ITEMKIND_ACCESSORY_TIMELIMIT == i_pItem->Kind)
	{
		// �ð����� �Ǽ��縮(�Ĺ� ����)	--> ���� 4��
		nWindowPos = POS_ACCESSORY_TIME_LIMIT;
	}
	else
	{
		return NULL;
	}

	// �κ����� ã�´�.
	CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByWindowPos(nWindowPos);
	if(NULL == pItemInfo)
	{
		return NULL;
	}
	return pItemInfo;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-03 by bhsohn ���� ������ �� ����
/// \date		2009-02-03 ~ 2009-02-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RefreshItemTooltipPos()
{
	if(!m_pEquipItemInfo || !m_pEquipItemInfo->IsShowItemInfo())
	{
		return;
	}
	// ũ�� ���� ó��
	
	{
		SIZE szItemInfo = m_pItemInfo->GetItemInfoTooltipSize();
		SIZE szMyEqItemInfo = m_pEquipItemInfo->GetItemInfoTooltipSize();
		if(szItemInfo.cx > szMyEqItemInfo.cx)
		{
			szMyEqItemInfo.cx = szItemInfo.cx;
		}
		else if(szItemInfo.cx < szMyEqItemInfo.cx)
		{
			szItemInfo.cx = szMyEqItemInfo.cx;
		}

		if(szItemInfo.cy > szMyEqItemInfo.cy)
		{
			szMyEqItemInfo.cy = szItemInfo.cy;
		}
		else if(szItemInfo.cy < szMyEqItemInfo.cy)
		{
			szItemInfo.cy = szMyEqItemInfo.cy;
		}
		m_pItemInfo->SetItemInfoTooltipSize(szItemInfo);
		m_pEquipItemInfo->SetItemInfoTooltipSize(szMyEqItemInfo);
	}

	// ��ġ ����
	{
		POINT ptItemInfo = m_pItemInfo->GetItemInfoPos();
		SIZE szItemInfo = m_pItemInfo->GetItemInfoTooltipSize();
		
		POINT ptMyEqPos = m_pEquipItemInfo->GetItemInfoPos();				
		SIZE szMyEqItemInfo = m_pEquipItemInfo->GetItemInfoTooltipSize();

		if((ptItemInfo.x + szItemInfo.cx) > ptMyEqPos.x)
		{
			ptMyEqPos.x = ptItemInfo.x - szMyEqItemInfo.cx;
		}
		
		if((ptItemInfo.y + szItemInfo.cy) > g_pD3dApp->GetBackBufferDesc().Height)
		{
			ptItemInfo.y = g_pD3dApp->GetBackBufferDesc().Height - szItemInfo.cy;
		}
		if((ptMyEqPos.y + szMyEqItemInfo.cy) > g_pD3dApp->GetBackBufferDesc().Height)
		{
			ptMyEqPos.y = g_pD3dApp->GetBackBufferDesc().Height - szMyEqItemInfo.cy;
		}

		m_pItemInfo->SetItemInfoPos(ptItemInfo);
		m_pEquipItemInfo->SetItemInfoPos(ptMyEqPos);
	}

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-13 by bhsohn ���� ��ŷ �ý���
/// \date		2009-02-16 ~ 2009-02-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::OnClickWorldRankBoard()
{
	if(NULL == m_pINFWorldRankWnd)
	{
		return;
	}
	BOOL bShow = m_pINFWorldRankWnd->IsShowWnd();
	bShow = TRUE;	
	m_pINFWorldRankWnd->ShowWnd(bShow);		

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-13 by bhsohn ���� ��ŷ �ý���
/// \date		2009-02-16 ~ 2009-02-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFGameMain::WndProcWorldRank(UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	if(NULL == m_pINFWorldRankWnd)
	{
		return INF_MSGPROC_NORMAL;
	}
	return m_pINFWorldRankWnd->WndProc(uMsg, wParam, lParam);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-13 by bhsohn ���� ��ŷ �ý���
/// \date		2009-02-16 ~ 2009-02-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RenderWorldRank()
{
	if(NULL == m_pINFWorldRankWnd)
	{
		return;
	}
	m_pINFWorldRankWnd->Render();
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-13 by bhsohn ���� ��ŷ �ý���
/// \date		2009-02-16 ~ 2009-02-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::RqWorldRankInfo()
{
	if(NULL == m_pINFWorldRankWnd)
	{
		return;
	}
	m_pINFWorldRankWnd->RqWorldRankInfo();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2013-02-20 by bhsohn �ΰ��� ����â ó��
/// \date		2013-02-20 ~ 2013-02-20
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::OnClickItemMixWnd(BOOL bShow, INT nShowItemNum, UID64_t uItemUniNum)
{
	if(NULL == m_pINFItemMixWnd)
	{
		return;
	}		
	POINT ptInvenItem = {0,0};
	POINT ptMixWndPos = {0,0};

	if(bShow)
	{		
		int nCap = 15;
		ptInvenItem.x = g_pD3dApp->GetBackBufferDesc().Width/2 - (m_pInven->GetBkSize().x + m_pINFItemMixWnd->GetBkSize().x)/2;
		ptInvenItem.x -= nCap; // 15�ȼ����� �����
		ptInvenItem.y = g_pD3dApp->GetBackBufferDesc().Height/2 - m_pInven->GetBkSize().y / 2; 	
		m_pInven->SetBkPos(ptInvenItem);	

		ptMixWndPos.x = ptInvenItem.x+m_pInven->GetBkSize().x;
		ptMixWndPos.x += nCap;
		ptMixWndPos.y = g_pD3dApp->GetBackBufferDesc().Height/2 - m_pInven->GetBkSize().y / 2; 	
	}		

	m_pINFItemMixWnd->ShowWnd(bShow, nShowItemNum, uItemUniNum, &ptMixWndPos);
	
}

int CINFGameMain::WndProcItemMixWnd(UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	if(NULL == m_pINFItemMixWnd)
	{
		return INF_MSGPROC_NORMAL;
	}
	return m_pINFItemMixWnd->WndProc(uMsg, wParam, lParam);
}

void CINFGameMain::RenderItemMixWnd()
{
	if(NULL == m_pINFItemMixWnd)
	{
		return;
	}
	m_pINFItemMixWnd->Render();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2013-05-28 by bhsohn �Ƹ� �÷��� �ý���
/// \date		2013-05-28 ~ 2013-05-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMain::OnClickArmorCollectionWnd(BOOL bShow, INT nShowItemNum, UID64_t uItemUniNum)
{
	if(NULL == m_pINFArmorCollectWnd)
	{
		return;
	}		
	POINT ptInvenItem = {0,0};
	POINT ptMixWndPos = {0,0};
	
	if(bShow)
	{		
		if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING)
		{
			m_pINFArmorCollectWnd->ShowWnd(FALSE, 0, 0, NULL);
			return;
		}

		const int ARROR_COLLECT_WIDTH	= 762;
		const int ARROR_COLLECT_HEIGHT	= 645;

		m_pInven->ShowInven(NULL, NULL, FALSE, TRUE);			
		
		ptMixWndPos.x = g_pD3dApp->GetBackBufferDesc().Width/2 - ARROR_COLLECT_WIDTH/2;
		ptMixWndPos.y = g_pD3dApp->GetBackBufferDesc().Height/2 - ARROR_COLLECT_HEIGHT/2 - 20;
	}		
	
	m_pINFArmorCollectWnd->ShowWnd(bShow, nShowItemNum, uItemUniNum, &ptMixWndPos);
	
}

int CINFGameMain::WndProcArmorCollectionWnd(UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	if(NULL == m_pINFArmorCollectWnd)
	{
		return INF_MSGPROC_NORMAL;
	}
	return m_pINFArmorCollectWnd->WndProc(uMsg, wParam, lParam);
}

void CINFGameMain::RenderArmorCollectionWnd()
{
	if(NULL == m_pINFArmorCollectWnd)
	{
		return;
	}
	m_pINFArmorCollectWnd->Render();
}

// 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������
void CINFGameMain::SetKillCount(INT nCount) // ų ī��Ʈ ����
{
	if(NULL == m_pUnitInfoBar) return;
	m_pUnitInfoBar->SetKillCount(nCount);

#if S_BONUS_KILL_SYSTEM_RENEWAL
	if (nCount == KILLCOUNT_MAX(g_pShuttleChild->m_myShuttleInfo.UnitKind))
#else
	if (nCount == 30)
#endif // S_BONUS_KILL_SYSTEM_RENEWAL
	{
		g_pD3dApp->SetPlayEffect(RC_EFF_KILL_COUNT_MAX,0);
	}
}
void CINFGameMain::SetRestCount(INT nCount) // �޽� ����ġ ����
{
	if(NULL == m_pUnitInfoBar) return;
	m_pUnitInfoBar->SetRestCount(nCount);
}
void CINFGameMain::SetBonusExpRate(INT nPartyRate,INT nFriendRate,INT nGuildRate) // ����ġ ���ʽ� ���� ����
{
	if(NULL == m_pUnitInfoBar) return;
	m_pUnitInfoBar->SetBonusExpRate(nPartyRate,nFriendRate,nGuildRate);
}
// end 2012-10-12 by jhjang ���� �ƿ� ����ġ ���ʽ� �ý��� ������

// 2012-12-10 by jhjang �ð� ǥ�� ����
void CINFGameMain::UpdateServerTimeString()
{
	ATUM_DATE_TIME curServerTime = GetServerDateTime();
	
	int nHour = curServerTime.Hour;
	int nMinute = curServerTime.Minute;
	
	if(curServerTime.Year != m_OldServerTime.Year
		|| curServerTime.Month != m_OldServerTime.Month
		|| curServerTime.Day != m_OldServerTime.Day)
	{
		string szStrBuf;
		curServerTime.GetLocalString_YYYYMMDD(curServerTime.Year,
			curServerTime.Month, 
			curServerTime.Day, 
			szStrBuf);	
		char chDateString[MAX_PATH];
		memset(chDateString, 0x00, MAX_PATH);
		wsprintf(chDateString, "%s", (char*)szStrBuf.c_str());

		m_pINFGameMainSysMsg->UpdateString(1, chDateString);
	}

	if(curServerTime.Hour != m_OldServerTime.Hour
		|| curServerTime.Minute != m_OldServerTime.Minute)
	{
		char chAmPm[32];
		// 2008. 11. 21 by ckPark ���� �ð� �����ֱ�, �ڽ� ����
		char chTimeString[MAX_PATH];
		if( 0 <= nHour && nHour <= 11)
			wsprintf(chAmPm, STRMSG_C_081103_0200);	// AM
		else
			wsprintf(chAmPm, STRMSG_C_081103_0201); // PM
		// end 2009. 05. 28 by ckPark ���� �ð� AM PM ���� ����
		
		// 2008. 11. 21 by ckPark ���� �ð� �����ֱ�, �ڽ� ����
		wsprintf(chTimeString, "%s %02d:%02d", chAmPm, nHour, nMinute);
		m_pINFGameMainSysMsg->UpdateString(2, chTimeString);
		// 2009. 05. 28 by ckPark ���� �ð� AM PM ���� ����
	}
	m_OldServerTime = curServerTime;
}
// end 2012-12-10 by jhjang �ð� ǥ�� ����


// 2013-05-09 by ssjung ���� ���� �Ⱓ���� ��� �޽��� ����
#ifdef SC_COLLECTION_ARMOR_JHSEOL_BCKIM
void CINFGameMain::TickArmorTimeCheck()
{	
	CItemInfo* pItemInfo = NULL;			
	if(!m_pInven || !m_pInven->m_pWearDisplayInfo[POS_CENTER])
	{
		return;
	}
	
	int nUniqueNumber = m_pInven->m_pWearDisplayInfo[POS_CENTER]->pItem->UniqueNumber;
	if(nUniqueNumber != 0)
	{
		pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( nUniqueNumber );
	}
	
	if(!pItemInfo || !pItemInfo->FixedTermShape.bActive || !pItemInfo->FixedTermShape.nStatLevel || SHAPE_STAT_FIXED_TIME_LIMITE_LEVEL <= pItemInfo->FixedTermShape.nStatLevel)
//	if(!pItemInfo || pItemInfo->FixedTermShape.bIsEnd || !pItemInfo->FixedTermShape.nStatLevel || 10 <= pItemInfo->FixedTermShape.nStatLevel)
	{
		return;
	}		
	
	{
		ATUM_DATE_TIME curServerTime = GetServerDateTime();
		int nRemainSecond = ( pItemInfo->FixedTermShape.EndDate.GetTimeInSeconds() - curServerTime.GetTimeInSeconds() );
		
		int m_nDay	= (nRemainSecond ) / 86400;
		int m_nHour	= (nRemainSecond ) % 86400 / 3600;
		int m_nMin	= (nRemainSecond ) % 86400 % 3600 / 60;
		int m_nSec	= (nRemainSecond ) % 86400 % 3600 % 60 / 1;
		
		int nStrarttime = ( pItemInfo->FixedTermShape.EndDate.GetTimeInSeconds() - pItemInfo->FixedTermShape.StartDate.GetTimeInSeconds() );
		
		if ((0 == m_nDay ) && (0 == m_nHour) && m_nMin )
		{
			if(5 == m_nMin || 3 == m_nMin || 1 == m_nMin)
			{
				if(!pItemInfo->GetLimitTimeFlag())
				{
					g_pD3dApp->LookChangeLimitTimeMSG();
					pItemInfo->SetLimitTimeFlag(TRUE);
				}
			}				
			else
			{
				pItemInfo->SetLimitTimeFlag(FALSE);	
			}
		}
	}
}
// end 2013-05-09 by ssjung ���� ���� �Ⱓ���� ��� �޽��� ����
														 
// 2013-06-12 by ssjung �Ƹ� �÷��� ���� ǥ��
INT CINFGameMain::GetArmorCollectType()
{
	return m_pINFArmorCollectWnd->GetSelUnitCollectType();
}						  
// end 2013-06-12 by ssjung �Ƹ� �÷��� ���� ǥ��
#endif

// 2015-09-25 Future, inactivity kick
#ifdef C_DISCONNECT_INACTIVE_PLAYERS
void CINFGameMain::InitInactivityKick(int nTimeTillKick)
{
	// Check if inactivity kick was initated already
	if (m_bShowingInactivityDCWarning || !m_pInfWindow)
		return;

	// Setup the message
	char inactivityMsg[128];
	sprintf_s(inactivityMsg, sizeof(inactivityMsg), STRMSG_C_INACTIVITY_0001
		, ((DISCONNECT_INACTIVE_PLAYERS_AFTER_SECONDS - DISCONNECT_INACTIVE_PLAYERS_WARNING_TIME) / 60) + 1);

	// Add the inactivity kick window
	m_pInfWindow->AddTimeMsgBox(inactivityMsg, _Q_AUTO_KICK, DISCONNECT_INACTIVE_PLAYERS_WARNING_TIME, STRMSG_C_INACTIVITY_0002);

	// Play some button sound
	g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0, 0, 0), FALSE);

	// Set inactivity warning showing
	m_bShowingInactivityDCWarning = true;
}

void CINFGameMain::CancelInactivityKick()
{
	// Check if inactivity kick was initated already
	if (!m_bShowingInactivityDCWarning || !m_pInfWindow)
		return;

	// Remove the message
	m_pInfWindow->DeleteMsgBox(_Q_AUTO_KICK);

	// Set inactivity warning showing
	m_bShowingInactivityDCWarning = false;
}

#endif // C_DISCONNECT_INACTIVE_PLAYERS

BOOL CINFGameMain::ShowOnScreenDisplay()
{
	if (IS_CITY_MAP_INDEX(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
	{
		return FALSE;
	}
	if (COMPARE_BODYCON_BIT(g_pShuttleChild->m_pCharacterInfo->m_nCurrentBodyCondition, BODYCON_LANDED_MASK | BODYCON_LANDING_MASK))
	{
		return FALSE;
	}
	if (g_pD3dApp->m_dwGameState == _GAME || g_pD3dApp->m_dwGameState == _CITY || g_pD3dApp->m_dwGameState == _SHOP)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//2016-01-04 by St0rmy, Fix City Fly bug
bool CINFGameMain::IsShowRanking()
{
	return m_pINFWorldRankWnd->IsShowWnd();
}
