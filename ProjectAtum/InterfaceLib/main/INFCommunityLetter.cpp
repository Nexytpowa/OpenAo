// INFCommunityLetter.cpp: implementation of the CINFCommunityLetter class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "D3DHanFont.h"
#include "INFScrollBar.h"
#include "INFComboBox.h"
#include "INFGameMain.h"
#include "INFCommunity.h"
#include "GameDataLast.h"
#include "INFImageBtn.h"
#include "INFArenaScrollBar.h"
#include "AtumSound.h"
#include "INFEditBox.h"
#include "ShuttleChild.h"
#include "Chat.h"
#include "INFCurselEditBox.h"

#include "INFCommunityLetter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
//  ���� �б�
#define		LETTER_MODE_POS_X		32
#define		LETTER_MODE_POS_Y		25
#define		LETTER_MODE_WIDTH		118
#define		LETTER_MODE_HEIGHT		25
#define		MAX_LETTER_READ_NUMBER	7		// �ִ� 

#define		LETTER_READ_LIST_BK_X			22		// 
#define		LETTER_READ_LIST_BK_Y			60		// 

#define		LETTER_READ_INFO_BK_X			22		// 
#define		LETTER_READ_INFO_BK_Y			60		// 

#define		LETTER_READ_ITEM_X			53		// 
#define		LETTER_READ_ITEM_Y			128		// 
#define		LETTER_READ_ITEM_WIDTH		390		// 
#define		LETTER_READ_ITEM_HEIGHT		28		// 

///////////////////////// ���� ���� //////////////////////////
// ���� ����Ʈ �ڽ�
#define		LETTER_WRITE_USER_EDIT		0
#define		LETTER_WRITE_TITLE_EDIT		1
#define		LETTER_WRITE_INFO_EDIT		2

// ���������� ����
#define LETTER_SEND_USER_EDIT_X						180
#define LETTER_SEND_USER_EDIT_Y						81
#define LETTER_SEND_USER_EDIT_W						260
#define LETTER_SEND_USER_FONT_LINE_HEIGHT			15

// �������� ����
#define LETTER_USER_EDIT_X						180
#define LETTER_USER_EDIT_Y						101
#define LETTER_USER_EDIT_W						260
#define LETTER_USER_FONT_LINE_HEIGHT			15

// ����
#define LETTER_TITLE_EDIT_X						180
#define LETTER_TITLE_EDIT_Y						121
#define LETTER_TITLE_EDIT_W						260
#define LETTER_TITLE_FONT_LINE_HEIGHT			15

// ����
#define LETTER_INFO_MAX_SCROLL_LINE				11
#define LETTER_INFO_EDIT_X						84
#define LETTER_INFO_EDIT_Y						153
#define LETTER_INFO_EDIT_W						345
#define LETTER_INFO_FONT_LINE_HEIGHT			15
#define LETTER_INFO_FONT_MOUSE_HEIGHT			170

///////////////////////// ���� �б� â //////////////////////////
// �������� ����
#define LETTER_USER_READ_EDIT_X						180
#define LETTER_USER_READ_EDIT_Y						81
#define LETTER_USER_READ_EDIT_W						260
#define LETTER_USER_READ_FONT_LINE_HEIGHT			15

// ����
#define LETTER_TITLE_READ_EDIT_X						180
#define LETTER_TITLE_READ_EDIT_Y						101
#define LETTER_TITLE_READ_EDIT_W						260
#define LETTER_TITLE_READ_FONT_LINE_HEIGHT			15

// ����
#define LETTER_INFO_READ_MAX_SCROLL_LINE			11
#define LETTER_INFO_READ_EDIT_X						84
#define LETTER_INFO_READ_EDIT_Y						137
#define LETTER_INFO_READ_EDIT_W						345
#define LETTER_INFO_READ_FONT_LINE_HEIGHT			15
#define LETTER_INFO_READ_FONT_MOUSE_HEIGHT			170		 
#else 
#define		LETTER_MODE_POS_X		32
#define		LETTER_MODE_POS_Y		52
#define		LETTER_MODE_WIDTH		118
#define		LETTER_MODE_HEIGHT		25
#define		MAX_LETTER_READ_NUMBER	8		// �ִ� 

#define		LETTER_READ_LIST_BK_X			47		// 
#define		LETTER_READ_LIST_BK_Y			83		// 

#define		LETTER_READ_INFO_BK_X			54		// 
#define		LETTER_READ_INFO_BK_Y			73		// 

#define		LETTER_READ_ITEM_X			68		// 
#define		LETTER_READ_ITEM_Y			149		// 
#define		LETTER_READ_ITEM_WIDTH		390		// 
#define		LETTER_READ_ITEM_HEIGHT		27		// 

///////////////////////// ���� ���� //////////////////////////
// ���� ����Ʈ �ڽ�
#define		LETTER_WRITE_USER_EDIT		0
#define		LETTER_WRITE_TITLE_EDIT		1
#define		LETTER_WRITE_INFO_EDIT		2

// ���������� ����
#define LETTER_SEND_USER_EDIT_X						176
#define LETTER_SEND_USER_EDIT_Y						98
#define LETTER_SEND_USER_EDIT_W						260
#define LETTER_SEND_USER_FONT_LINE_HEIGHT			15

// �������� ����
#define LETTER_USER_EDIT_X						176
#define LETTER_USER_EDIT_Y						118
#define LETTER_USER_EDIT_W						260
#define LETTER_USER_FONT_LINE_HEIGHT			15

// ����
#define LETTER_TITLE_EDIT_X						176
#define LETTER_TITLE_EDIT_Y						138
#define LETTER_TITLE_EDIT_W						260
#define LETTER_TITLE_FONT_LINE_HEIGHT			15

// ����
#define LETTER_INFO_MAX_SCROLL_LINE			11
#define LETTER_INFO_EDIT_X						89
#define LETTER_INFO_EDIT_Y						164
#define LETTER_INFO_EDIT_W						345
#define LETTER_INFO_FONT_LINE_HEIGHT			15
#define LETTER_INFO_FONT_MOUSE_HEIGHT			170

///////////////////////// ���� �б� â //////////////////////////
// �������� ����
#define LETTER_USER_READ_EDIT_X						187
#define LETTER_USER_READ_EDIT_Y						110
#define LETTER_USER_READ_EDIT_W						260
#define LETTER_USER_READ_FONT_LINE_HEIGHT			15

// ����
#define LETTER_TITLE_READ_EDIT_X						187
#define LETTER_TITLE_READ_EDIT_Y						130
#define LETTER_TITLE_READ_EDIT_W						260
#define LETTER_TITLE_READ_FONT_LINE_HEIGHT			15

// ����
#define LETTER_INFO_READ_MAX_SCROLL_LINE			11
#define LETTER_INFO_READ_EDIT_X						90
#define LETTER_INFO_READ_EDIT_Y						156
#define LETTER_INFO_READ_EDIT_W						345
#define LETTER_INFO_READ_FONT_LINE_HEIGHT			15
#define LETTER_INFO_READ_FONT_MOUSE_HEIGHT			170
#endif

struct Letter_Sort: binary_function<structReadLetterItemInfo, structReadLetterItemInfo, bool>
{
	bool operator()(structReadLetterItemInfo pLetterInfo1, structReadLetterItemInfo pLetterInfo2)
	{
        if(pLetterInfo1.atimeMail > pLetterInfo2.atimeMail)
		{
			return TRUE;
		}		
		return FALSE;
    };
};


CINFCommunityLetter::CINFCommunityLetter(CAtumNode* pParent)
{
	m_pParent = pParent;

#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBack = NULL;
#endif
	int  nCnt = 0;
	for(nCnt = 0;nCnt < MAX_LETTER_MODE;nCnt++)
	{
		m_pLetterMode[nCnt] = NULL;
	}
	for(nCnt = 0;nCnt < MAX_LETTER_READ;nCnt++)
	{
		m_pLetterRead[nCnt] =NULL;
	}
	m_nLetterMode = LETTER_MODE_READ;
	m_nReadLetterMode = LETTER_READ_MODE_LIST;	

	m_pReadBtn = NULL ;			// �б�
	m_pReadDelBtn = NULL ;		// ����
	m_pImgSelect = NULL;
	m_pLetterReadListBk = NULL;
	m_pLetterReadBk = NULL;	// ���

	m_pScrollRead = NULL;
	m_pFontLetter = NULL;

	m_pSendBtn = NULL;			// ������
	m_pAllSendBtn= NULL;		// ��ü �߼�

	m_pEditWriteSendUser = NULL;
	m_pEditWriteReceiveUser = NULL;
	m_pEditWriteTitle = NULL;
	m_pEditWriteInfo = NULL;
	m_pScrollWrite			= NULL;

	m_pEditReadReceiveUser = NULL;		// �޴� ����
	m_pEditReadTitle= NULL;			// ����
	m_pEditReadInfo= NULL;			// ����
	m_pScrollReadInfo= NULL;			// ��ũ�� 

	m_pReadResponseBtn = NULL;			// �б� ����
	m_pReadListDelBtn= NULL;				// �б� ����
	m_pReadBackBtn= NULL;				// �б� �ڷ�

	m_nSelReadLetterPos = -1;
	m_nSelLetterWrite = -1;	

	m_uReadLetterUID = 0;
	m_bAllMail = FALSE;	

	m_bLetterFirstRq = FALSE;

	//Nexy 2024/12/27
	m_nTotalUnreadLetters = 0;
	m_nAdditionalUnreadLetters = 0;
}

CINFCommunityLetter::~CINFCommunityLetter()
{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	util::del(m_pBack);
#endif
	int  nCnt = 0;
	for(nCnt = 0;nCnt < MAX_LETTER_MODE;nCnt++)
	{
		util::del(m_pLetterMode[nCnt]);
	}
	for(nCnt = 0;nCnt < MAX_LETTER_READ;nCnt++)
	{
		util::del(m_pLetterRead[nCnt]);		
	}
	util::del(m_pReadBtn);	// ����
	util::del(m_pReadDelBtn);	
	util::del(m_pImgSelect);	
	util::del(m_pLetterReadListBk);	
	util::del(m_pLetterReadBk);		
	
	util::del(m_pSendBtn);			// ������
	util::del(m_pAllSendBtn);		// ��ü �߼�
	
	util::del(m_pScrollRead);
	util::del(m_pFontLetter);

	
	util::del(m_pEditWriteSendUser);
	util::del(m_pEditWriteReceiveUser);
	util::del(m_pEditWriteTitle);
	util::del(m_pEditWriteInfo);

	util::del(m_pScrollWrite);	
	
	util::del(m_pEditReadReceiveUser);		// �޴� ����
	util::del(m_pEditReadTitle);			// ����
	util::del(m_pEditReadInfo);			// ����
	util::del(m_pScrollReadInfo);			// ��ũ�� 

	util::del(m_pReadResponseBtn);			// �б� ����
	util::del(m_pReadListDelBtn);				// �б� ����
	util::del(m_pReadBackBtn);				// �б� �ڷ�
}

HRESULT CINFCommunityLetter::InitDeviceObjects()
{
	DataHeader *pDataHeader = NULL;
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	{
		pDataHeader = m_pGameData->Find("commubk4");	
		if(NULL == m_pBack)
		{
 			m_pBack = new CINFImageEx;
 		}
 		m_pBack->InitDeviceObjects( pDataHeader );
 		
 	}
#endif

	{
		int  nCnt = 0;
		char chImageBuff[128];
		for(nCnt = 0;nCnt < MAX_LETTER_MODE;nCnt++)
		{
			wsprintf(chImageBuff, "commu4_%d", nCnt+1);
			pDataHeader = m_pGameData->Find(chImageBuff);	
			if(NULL == m_pLetterMode[nCnt])
			{
				m_pLetterMode[nCnt] = new CINFImageEx;
			}
			m_pLetterMode[nCnt]->InitDeviceObjects( pDataHeader );
		}
	}

	///////////////////////////// ���� �б� /////////////////////////////
	{			
		// ���� ���� ����
		pDataHeader = m_pGameData->Find("c_lenr");	
		if(NULL == m_pLetterRead[LETTER_READ_NORES])
		{
			m_pLetterRead[LETTER_READ_NORES] = new CINFImageEx;
		}
		m_pLetterRead[LETTER_READ_NORES]->InitDeviceObjects( pDataHeader );

		// ���� ����
		pDataHeader = m_pGameData->Find("c_ler");	
		if(NULL == m_pLetterRead[LETTER_READ_RES])
		{
			m_pLetterRead[LETTER_READ_RES] = new CINFImageEx;
		}
		m_pLetterRead[LETTER_READ_RES]->InitDeviceObjects( pDataHeader );
	}
	
	
	// ���� �̹���
	{			
		pDataHeader = m_pGameData->Find("c_lesel");	
		if(NULL == m_pImgSelect)
		{
			m_pImgSelect = new CINFImageEx;
		}
		m_pImgSelect->InitDeviceObjects( pDataHeader );
	}
	
	{			
		pDataHeader = m_pGameData->Find("lr_list");	
		if(NULL == m_pLetterReadListBk)
		{
			m_pLetterReadListBk = new CINFImageEx;
		}
		m_pLetterReadListBk->InitDeviceObjects( pDataHeader );
	}
	
	{			
		pDataHeader = m_pGameData->Find("lr_bk");	
		if(NULL == m_pLetterReadBk)
		{
			m_pLetterReadBk = new CINFImageEx;
		}
		m_pLetterReadBk->InitDeviceObjects( pDataHeader );
	}
	

	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];				
		wsprintf(szUpBtn, "c_lebtn3");
		wsprintf(szDownBtn, "c_lebtn1");
		wsprintf(szSelBtn, "c_lebtn0");
		wsprintf(szDisBtn, "c_lebtn2");
		if(NULL == m_pReadBtn)
		{
			m_pReadBtn = new CINFImageBtn;
			// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
			//m_pReadBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);
			m_pReadBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP65");
			// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		}
		
	}
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];				
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����			
		wsprintf(szUpBtn, "cans03");
		wsprintf(szDownBtn, "cans01");
		wsprintf(szSelBtn, "cans00");
		wsprintf(szDisBtn, "cans02");															  
#else
		wsprintf(szUpBtn, "lr_del3");
		wsprintf(szDownBtn, "lr_del1");
		wsprintf(szSelBtn, "lr_del0");
		wsprintf(szDisBtn, "lr_del2");
#endif
		if(NULL == m_pReadDelBtn)
		{
			m_pReadDelBtn = new CINFImageBtn;
			// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
			//m_pReadDelBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
			m_pReadDelBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP12");
			// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		}
	}	
	
	{
		char  szScBall[30];	
		if(NULL == m_pScrollRead)
		{
			m_pScrollRead = new CINFArenaScrollBar;
		}		
		wsprintf(szScBall,"c_scrlb");
		
		m_pScrollRead->InitDeviceObjects(MAX_LETTER_READ_NUMBER, szScBall);
	}
	{
		if(NULL == m_pFontLetter)
		{
			m_pFontLetter = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,1024,32);
		}
		m_pFontLetter->InitDeviceObjects(g_pD3dDev);
	}
	
	// �б� ����
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];				
		wsprintf(szUpBtn, "lr_rp3");
		wsprintf(szDownBtn, "lr_rp1");
		wsprintf(szSelBtn, "lr_rp0");
		wsprintf(szDisBtn, "lr_rp2");
		if(NULL == m_pReadResponseBtn)
		{
			m_pReadResponseBtn= new CINFImageBtn;
			// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
			//m_pReadResponseBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);	
			m_pReadResponseBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP54");
			// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����			
		}		
	}
	// �б� ����
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];				
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����		
		wsprintf(szUpBtn, "cans03");
		wsprintf(szDownBtn, "cans01");
		wsprintf(szSelBtn, "cans00");
		wsprintf(szDisBtn, "cans02");															  
#else					   
		wsprintf(szUpBtn, "lr_del3");
		wsprintf(szDownBtn, "lr_del1");
		wsprintf(szSelBtn, "lr_del0");
		wsprintf(szDisBtn, "lr_del2");
#endif
		if(NULL == m_pReadListDelBtn)
		{
			m_pReadListDelBtn= new CINFImageBtn;
			// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
			//m_pReadListDelBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
			m_pReadListDelBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP12");
			// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		}		
	}
	// �б� �ڷ�
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];				
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����			
		wsprintf(szUpBtn, "oks03");
		wsprintf(szDownBtn, "oks01");
		wsprintf(szSelBtn, "oks00");
		wsprintf(szDisBtn, "oks02");															  
#else						   
		wsprintf(szUpBtn, "lr_ok3");
		wsprintf(szDownBtn, "lr_ok1");
		wsprintf(szSelBtn, "lr_ok0");
		wsprintf(szDisBtn, "lr_ok2");
#endif
		if(NULL == m_pReadBackBtn)
		{
			m_pReadBackBtn= new CINFImageBtn;
			// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
			//m_pReadBackBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
			m_pReadBackBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP40");
			// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		}		
	}

	///////////////////////////// ���� ���� /////////////////////////////	
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];				
		wsprintf(szUpBtn, "c_sbtn3");
		wsprintf(szDownBtn, "c_sbtn1");
		wsprintf(szSelBtn, "c_sbtn0");
		wsprintf(szDisBtn, "c_sbtn2");
		if(NULL == m_pSendBtn)
		{
			m_pSendBtn = new CINFImageBtn;
			// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
			//m_pSendBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
			m_pSendBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP53");		
			// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		}
		
	}
	
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];				
		wsprintf(szUpBtn, "c_asbtn3");
		wsprintf(szDownBtn, "c_asbtn1");
		wsprintf(szSelBtn, "c_asbtn0");
		wsprintf(szDisBtn, "c_asbtn2");
		if(NULL == m_pAllSendBtn)
		{
			m_pAllSendBtn = new CINFImageBtn;
			// 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
			//m_pAllSendBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
			m_pAllSendBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn,"STRTOOLTIP55");		
			// end 2011. 1. 12 by jskim UI �̹��� ��ư ���� ����
		}
		
	}	
	////////////////////////// ���� �б� ////////////////////////////
	// �޴� ����
	{
		if(NULL == m_pEditReadReceiveUser)
		{
			m_pEditReadReceiveUser = new CINFEditBox;
		}
		POINT ptPos = {LETTER_USER_READ_EDIT_X, LETTER_USER_READ_EDIT_Y};
		m_pEditReadReceiveUser->InitDeviceObjects(9, ptPos, LETTER_USER_READ_EDIT_W, TRUE, LETTER_USER_READ_FONT_LINE_HEIGHT);				
		m_pEditReadReceiveUser->SetStringMaxBuff(SIZE_MAX_ARENA_FULL_NAME);
	}
	// ����
	{
		if(NULL == m_pEditReadTitle)
		{
			m_pEditReadTitle = new CINFEditBox;
		}
		POINT ptPos = {LETTER_TITLE_READ_EDIT_X, LETTER_TITLE_READ_EDIT_Y};
		m_pEditReadTitle->InitDeviceObjects(9, ptPos, LETTER_TITLE_READ_EDIT_W, TRUE, LETTER_TITLE_READ_FONT_LINE_HEIGHT);				
		m_pEditReadTitle->SetStringMaxBuff(SIZE_MAX_ARENA_FULL_NAME);
	}

	// ����
	{
		if(NULL == m_pEditReadInfo)
		{
			m_pEditReadInfo = new CINFEditBox;
		}
		POINT ptPos = {LETTER_INFO_READ_EDIT_X, LETTER_INFO_READ_EDIT_Y};
		m_pEditReadInfo->InitDeviceObjects(9, ptPos, LETTER_INFO_READ_EDIT_W, TRUE, LETTER_INFO_READ_FONT_LINE_HEIGHT, 
										FALSE, LETTER_INFO_READ_FONT_MOUSE_HEIGHT);				
		m_pEditReadInfo->SetStringMaxBuff(	SIZE_MAX_LETTER_CONTENT);
	}	

	// ��ũ��
	{
		char  szScBall[30];	
		// �� ����Ʈ.
		if(NULL == m_pScrollReadInfo)
		{
			m_pScrollReadInfo = new CINFArenaScrollBar;
		}		
		wsprintf(szScBall,"c_scrlb");
		m_pScrollReadInfo->InitDeviceObjects(LETTER_INFO_READ_MAX_SCROLL_LINE, szScBall);
	}

	////////////////////////// ���� ���� ////////////////////////////
	// ������ ����
	{
		if(NULL == m_pEditWriteSendUser)
		{
			m_pEditWriteSendUser = new CINFEditBox;
		}
		POINT ptPos = {LETTER_SEND_USER_EDIT_X, LETTER_SEND_USER_EDIT_Y};
		m_pEditWriteSendUser->InitDeviceObjects(9, ptPos, LETTER_SEND_USER_EDIT_W, TRUE, LETTER_SEND_USER_FONT_LINE_HEIGHT);				
		m_pEditWriteSendUser->SetStringMaxBuff(SIZE_MAX_ARENA_FULL_NAME);		
	}
	// �޴� ����
	{
		if(NULL == m_pEditWriteReceiveUser)
		{
			m_pEditWriteReceiveUser = new CINFEditBox;
		}
		POINT ptPos = {LETTER_USER_EDIT_X, LETTER_USER_EDIT_Y};
		m_pEditWriteReceiveUser->InitDeviceObjects(9, ptPos, LETTER_USER_EDIT_W, TRUE, LETTER_USER_FONT_LINE_HEIGHT);				
		m_pEditWriteReceiveUser->SetStringMaxBuff(SIZE_MAX_ARENA_FULL_NAME);
	}
	// ����
	{
		if(NULL == m_pEditWriteTitle)
		{
			m_pEditWriteTitle = new CINFEditBox;
		}
		POINT ptPos = {LETTER_TITLE_EDIT_X, LETTER_TITLE_EDIT_Y};
		m_pEditWriteTitle->InitDeviceObjects(9, ptPos, LETTER_TITLE_EDIT_W, TRUE, LETTER_TITLE_FONT_LINE_HEIGHT);				
		m_pEditWriteTitle->SetStringMaxBuff(SIZE_MAX_LETTER_TITLE);
	}

	// ����
	{
		if(NULL == m_pEditWriteInfo)
		{
			m_pEditWriteInfo = new CINFCurselEditBox;
		}
		POINT ptPos = {LETTER_INFO_EDIT_X, LETTER_INFO_EDIT_Y};
//		m_pEditWriteInfo->InitDeviceObjects(9, ptPos, LETTER_INFO_EDIT_W, TRUE, LETTER_INFO_FONT_LINE_HEIGHT, 
//										FALSE, LETTER_INFO_FONT_MOUSE_HEIGHT);				
		m_pEditWriteInfo->InitDeviceObjects(9, ptPos, LETTER_INFO_EDIT_W, TRUE, LETTER_INFO_FONT_LINE_HEIGHT, 
										FALSE, LETTER_INFO_FONT_MOUSE_HEIGHT);				
		m_pEditWriteInfo->SetStringMaxBuff(	SIZE_MAX_LETTER_CONTENT);
		m_pEditWriteInfo->SetOnePageItemCnt(LETTER_INFO_MAX_SCROLL_LINE);
	}	

	// ��ũ��
	{
		char  szScBall[30];	
		// �� ����Ʈ.
		if(NULL == m_pScrollWrite)
		{
			m_pScrollWrite = new CINFArenaScrollBar;
		}		
		wsprintf(szScBall,"c_scrlb");
		m_pScrollWrite->InitDeviceObjects(LETTER_INFO_MAX_SCROLL_LINE, szScBall);
	}

	//TestReadDb();

	return S_OK;
}

HRESULT CINFCommunityLetter::RestoreDeviceObjects()
{
	// ��� 
	POINT ptBkPos = ((CINFCommunity*)m_pParent)->GetCommunityBkPos();

#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	if(m_pBack)
	{
		m_pBack->RestoreDeviceObjects();
	}
#endif
	int nCnt = 0;
	int nPosX, nPosY;
	nPosX = nPosY =0;
	for(nCnt = 0;nCnt < MAX_LETTER_MODE;nCnt++)
	{		
		if(m_pLetterMode[nCnt])
		{
			m_pLetterMode[nCnt]->RestoreDeviceObjects();
		}
	}
	for(nCnt = 0;nCnt < MAX_LETTER_READ;nCnt++)
	{		
		if(m_pLetterRead[nCnt])
		{
			m_pLetterRead[nCnt]->RestoreDeviceObjects();
		}
	}

	if(m_pImgSelect)
	{
		m_pImgSelect->RestoreDeviceObjects();
	}
	if(m_pLetterReadListBk)
	{
		m_pLetterReadListBk->RestoreDeviceObjects();
	}
	if(m_pLetterReadBk)
	{
		m_pLetterReadBk->RestoreDeviceObjects();
	}
	if(m_pReadBtn)
	{
		m_pReadBtn->RestoreDeviceObjects();				
		nPosX = ptBkPos.x + 308;
		nPosY = ptBkPos.y + 97;		
		m_pReadBtn->SetBtnPosition(nPosX, nPosY);	
	}
	if(m_pReadDelBtn)
	{
		m_pReadDelBtn->RestoreDeviceObjects();		
		
		nPosX = ptBkPos.x + 378;
		nPosY = ptBkPos.y + 97;		
		m_pReadDelBtn->SetBtnPosition(nPosX, nPosY);	
	}	
	if(m_pAllSendBtn)
	{
		m_pAllSendBtn->RestoreDeviceObjects();		
		
		nPosX = ptBkPos.x + 282;
		nPosY = ptBkPos.y + 346;		
		m_pAllSendBtn->SetBtnPosition(nPosX, nPosY);	
	}
	if(m_pSendBtn)
	{
		m_pSendBtn->RestoreDeviceObjects();				
		nPosX = ptBkPos.x + 381;
		nPosY = ptBkPos.y + 346;		
		m_pSendBtn->SetBtnPosition(nPosX, nPosY);	
	}

	// �б� ����
	if(m_pReadResponseBtn)
	{
		m_pReadResponseBtn->RestoreDeviceObjects();				
		nPosX = ptBkPos.x + 243;
		nPosY = ptBkPos.y + 88;		
		m_pReadResponseBtn->SetBtnPosition(nPosX, nPosY);	
	}
	// �б� ����
	if(m_pReadListDelBtn)
	{
		m_pReadListDelBtn->RestoreDeviceObjects();				
		nPosX = ptBkPos.x + 310;
		nPosY = ptBkPos.y + 88;		
		m_pReadListDelBtn->SetBtnPosition(nPosX, nPosY);	
	}
	// �б� �ڷ�
	if(m_pReadBackBtn)
	{
		m_pReadBackBtn->RestoreDeviceObjects();				
		nPosX = ptBkPos.x + 377;
		nPosY = ptBkPos.y + 88;		
		m_pReadBackBtn->SetBtnPosition(nPosX, nPosY);	
	}


	{
		// ��ũ��
		m_pScrollRead->RestoreDeviceObjects();
		
		RECT rcMouseWhell, rcMousePos;
		POINT ptScrollPos = ptBkPos;

#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		ptScrollPos.x += 469;
		ptScrollPos.y += 175;																	  
#else					
		ptScrollPos.x += 454;
		ptScrollPos.y += 152;
#endif

		m_pScrollRead->SetPosition(ptScrollPos.x ,ptScrollPos.y,11,170);
		rcMouseWhell.left		= ptScrollPos.x - 468;
		rcMouseWhell.top		= ptScrollPos.y - 30;
		rcMouseWhell.right		= ptScrollPos.x + 30;
		rcMouseWhell.bottom		= ptScrollPos.y + 230;
		m_pScrollRead->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= ptScrollPos.x - 11;
		rcMousePos.top			= ptScrollPos.y ;
		rcMousePos.right		= rcMousePos.left + 32;
		rcMousePos.bottom		= rcMousePos.top + 200;
		m_pScrollRead->SetMouseBallRect(rcMousePos);
	}
	if(m_pFontLetter)
	{
		m_pFontLetter->RestoreDeviceObjects();
	}
	/////////////////////////////// ���� �б�///////////////////////////////////////////
	if(m_pEditReadReceiveUser)
	{
		m_pEditReadReceiveUser->RestoreDeviceObjects();
		nPosX = ptBkPos.x + LETTER_USER_READ_EDIT_X;
		nPosY = ptBkPos.y + LETTER_USER_READ_EDIT_Y;		
		m_pEditReadReceiveUser->SetPos(nPosX, nPosY);
	}
	if(m_pEditReadTitle)
	{
		m_pEditReadTitle->RestoreDeviceObjects();
		nPosX = ptBkPos.x + LETTER_TITLE_READ_EDIT_X;
		nPosY = ptBkPos.y + LETTER_TITLE_READ_EDIT_Y;		
		m_pEditReadTitle->SetPos(nPosX, nPosY);
	}
	if(m_pEditReadInfo)
	{
		m_pEditReadInfo->RestoreDeviceObjects();
		nPosX = ptBkPos.x + LETTER_INFO_READ_EDIT_X;
		nPosY = ptBkPos.y + LETTER_INFO_READ_EDIT_Y;		
		m_pEditReadInfo->SetPos(nPosX, nPosY);
	}
	{
		m_pScrollReadInfo->RestoreDeviceObjects();
		
		RECT rcMouseWhell, rcMousePos;
		POINT ptScrollPos = ptBkPos;

		ptScrollPos.x += 454;
		ptScrollPos.y += 164;

		m_pScrollReadInfo->SetPosition(ptScrollPos.x ,ptScrollPos.y,11,135);
		rcMouseWhell.left		= ptScrollPos.x - 468;
		rcMouseWhell.top		= ptScrollPos.y - 30;
		rcMouseWhell.right		= ptScrollPos.x + 30;
		rcMouseWhell.bottom		= ptScrollPos.y + 230;
		m_pScrollReadInfo->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= ptScrollPos.x - 11;
		rcMousePos.top			= ptScrollPos.y ;
		rcMousePos.right		= rcMousePos.left + 32;
		rcMousePos.bottom		= rcMousePos.top + 200;
		m_pScrollReadInfo->SetMouseBallRect(rcMousePos);
	}

	/////////////////////////////// ���� ����///////////////////////////////////////////
	if(m_pEditWriteSendUser)
	{
		m_pEditWriteSendUser->RestoreDeviceObjects();
		nPosX = ptBkPos.x + LETTER_SEND_USER_EDIT_X;
		nPosY = ptBkPos.y + LETTER_SEND_USER_EDIT_Y;		
		m_pEditWriteSendUser->SetPos(nPosX, nPosY);

		const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();		
		m_pEditWriteSendUser->SetString(myShuttleInfo.CharacterName, strlen(myShuttleInfo.CharacterName)+1);
	}

	if(m_pEditWriteReceiveUser)
	{
		m_pEditWriteReceiveUser->RestoreDeviceObjects();
		nPosX = ptBkPos.x + LETTER_USER_EDIT_X;
		nPosY = ptBkPos.y + LETTER_USER_EDIT_Y;		
		m_pEditWriteReceiveUser->SetPos(nPosX, nPosY);
	}
	if(m_pEditWriteTitle)
	{
		m_pEditWriteTitle->RestoreDeviceObjects();
		nPosX = ptBkPos.x + LETTER_TITLE_EDIT_X;
		nPosY = ptBkPos.y + LETTER_TITLE_EDIT_Y;		
		m_pEditWriteTitle->SetPos(nPosX, nPosY);
	}
	if(m_pEditWriteInfo)
	{
		m_pEditWriteInfo->RestoreDeviceObjects();
		nPosX = ptBkPos.x + LETTER_INFO_EDIT_X;
		nPosY = ptBkPos.y + LETTER_INFO_EDIT_Y;		
		m_pEditWriteInfo->SetPos(nPosX, nPosY);
	}
	{
		m_pScrollWrite->RestoreDeviceObjects();
		
		RECT rcMouseWhell, rcMousePos;
		POINT ptScrollPos = ptBkPos;

		ptScrollPos.x += 454;
		ptScrollPos.y += 164;

		m_pScrollWrite->SetPosition(ptScrollPos.x ,ptScrollPos.y,11,135);
		rcMouseWhell.left		= ptScrollPos.x - 468;
		rcMouseWhell.top		= ptScrollPos.y - 30;
		rcMouseWhell.right		= ptScrollPos.x + 30;
		rcMouseWhell.bottom		= ptScrollPos.y + 230;
		m_pScrollWrite->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= ptScrollPos.x - 11;
		rcMousePos.top			= ptScrollPos.y ;
		rcMousePos.right		= rcMousePos.left + 32;
		rcMousePos.bottom		= rcMousePos.top + 200;
		m_pScrollWrite->SetMouseBallRect(rcMousePos);
	}
	
	return S_OK;
}

HRESULT CINFCommunityLetter::InvalidateDeviceObjects()
{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	if(m_pBack)
	{
		m_pBack->InvalidateDeviceObjects();
	}
#endif
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_LETTER_MODE;nCnt++)
	{		
		if(m_pLetterMode[nCnt])
		{
			m_pLetterMode[nCnt]->InvalidateDeviceObjects();
		}
	}
	for(nCnt = 0;nCnt < MAX_LETTER_READ;nCnt++)
	{		
		if(m_pLetterRead[nCnt])
		{
			m_pLetterRead[nCnt]->InvalidateDeviceObjects();
		}
	}
	if(m_pImgSelect)
	{
		m_pImgSelect->InvalidateDeviceObjects();
	}
	if(m_pLetterReadListBk)
	{
		m_pLetterReadListBk->InvalidateDeviceObjects();
	}
	if(m_pLetterReadBk)
	{
		m_pLetterReadBk->InvalidateDeviceObjects();
	}
		
	if(m_pReadBtn)
	{		
		m_pReadBtn->InvalidateDeviceObjects();
	}
	if(m_pReadDelBtn)
	{		
		m_pReadDelBtn->InvalidateDeviceObjects();
	}
	
	if(m_pSendBtn)
	{
		m_pSendBtn->InvalidateDeviceObjects();
	}	
		
	// �б� ����
	if(m_pReadResponseBtn)
	{
		m_pReadResponseBtn->InvalidateDeviceObjects();
	}
	// �б� ����
	if(m_pReadListDelBtn)
	{
		m_pReadListDelBtn->InvalidateDeviceObjects();
	}
	// �б� �ڷ�
	if(m_pReadBackBtn)
	{
		m_pReadBackBtn->InvalidateDeviceObjects();
	}

	if(m_pAllSendBtn)
	{
		m_pAllSendBtn->InvalidateDeviceObjects();		
	}

	if(m_pScrollRead)
	{
		m_pScrollRead->InvalidateDeviceObjects();
	}
	if(m_pFontLetter)
	{
		m_pFontLetter->InvalidateDeviceObjects();
	}
	/////////////////////////////// ���� �б�///////////////////////////////////////////
	if(m_pEditReadReceiveUser)
	{
		m_pEditReadReceiveUser->InvalidateDeviceObjects();
	}
	if(m_pEditReadTitle)
	{
		m_pEditReadTitle->InvalidateDeviceObjects();
	}
	if(m_pEditReadInfo)
	{
		m_pEditReadInfo->InvalidateDeviceObjects();
	}

	if(m_pScrollReadInfo)
	{
		m_pScrollReadInfo->InvalidateDeviceObjects();
	}
	/////////////////////////////// ���� ����///////////////////////////////////////////
	if(m_pEditWriteSendUser)
	{
		m_pEditWriteSendUser->InvalidateDeviceObjects();
	}
	if(m_pEditWriteReceiveUser)
	{
		m_pEditWriteReceiveUser->InvalidateDeviceObjects();
	}
	if(m_pEditWriteTitle)
	{
		m_pEditWriteTitle->InvalidateDeviceObjects();
	}
	if(m_pEditWriteInfo)
	{
		m_pEditWriteInfo->InvalidateDeviceObjects();
	}

	if(m_pScrollWrite)
	{
		m_pScrollWrite->InvalidateDeviceObjects();
	}

	return S_OK;
}

HRESULT CINFCommunityLetter::DeleteDeviceObjects()
{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	if(m_pBack)
	{
		m_pBack->DeleteDeviceObjects();
		util::del(m_pBack);
	}
#endif
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_LETTER_MODE;nCnt++)
	{		
		if(m_pLetterMode[nCnt])
		{
			m_pLetterMode[nCnt]->DeleteDeviceObjects();
			util::del(m_pLetterMode[nCnt]);
		}
	}
	for(nCnt = 0;nCnt < MAX_LETTER_READ;nCnt++)
	{		
		if(m_pLetterRead[nCnt])
		{
			m_pLetterRead[nCnt]->DeleteDeviceObjects();
			util::del(m_pLetterRead[nCnt]);			
		}
	}
	if(m_pImgSelect)
	{
		m_pImgSelect->DeleteDeviceObjects();
		util::del(m_pImgSelect);
	}
	if(m_pLetterReadListBk)
	{
		m_pLetterReadListBk->DeleteDeviceObjects();
		util::del(m_pLetterReadListBk);
	}
	if(m_pLetterReadBk)
	{
		m_pLetterReadBk->DeleteDeviceObjects();
		util::del(m_pLetterReadBk);
	}
	if(m_pReadBtn)
	{		
		m_pReadBtn->DeleteDeviceObjects();
		util::del(m_pReadBtn);
	}
	if(m_pReadDelBtn)
	{		
		m_pReadDelBtn->DeleteDeviceObjects();
		util::del(m_pReadDelBtn);
	}
	if(m_pSendBtn)
	{		
		m_pSendBtn->DeleteDeviceObjects();
		util::del(m_pSendBtn);
	}

	if(m_pReadResponseBtn)
	{		
		m_pReadResponseBtn->DeleteDeviceObjects();
		util::del(m_pReadResponseBtn);
	}

	if(m_pReadListDelBtn)
	{		
		m_pReadListDelBtn->DeleteDeviceObjects();
		util::del(m_pReadListDelBtn);
	}

	if(m_pReadBackBtn)
	{		
		m_pReadBackBtn->DeleteDeviceObjects();
		util::del(m_pReadBackBtn);
	}

	
	if(m_pAllSendBtn)
	{
		m_pAllSendBtn->DeleteDeviceObjects();
		util::del(m_pAllSendBtn);		
	}
	
	if(m_pScrollRead)
	{
		m_pScrollRead->DeleteDeviceObjects();
		util::del(m_pScrollRead);
	}

	if(m_pFontLetter)
	{		
		m_pFontLetter->DeleteDeviceObjects();
		util::del(m_pFontLetter);
	}
	/////////////////////////////// �����б�///////////////////////////////////////////
	if(m_pEditReadReceiveUser)
	{
		m_pEditReadReceiveUser->DeleteDeviceObjects();
		util::del(m_pEditReadReceiveUser);		
	}
	if(m_pEditReadTitle)
	{
		m_pEditReadTitle->DeleteDeviceObjects();
		util::del(m_pEditReadTitle);		
	}
	if(m_pEditReadInfo)
	{
		m_pEditReadInfo->DeleteDeviceObjects();
		util::del(m_pEditReadInfo);				
	}
	if(m_pScrollReadInfo)
	{
		m_pScrollReadInfo->DeleteDeviceObjects();
		util::del(m_pScrollReadInfo);
	}
	/////////////////////////////// ���� ����///////////////////////////////////////////
	if(m_pEditWriteSendUser)
	{
		m_pEditWriteSendUser->DeleteDeviceObjects();
		util::del(m_pEditWriteSendUser);		
	}

	if(m_pEditWriteReceiveUser)
	{
		m_pEditWriteReceiveUser->DeleteDeviceObjects();
		util::del(m_pEditWriteReceiveUser);		
	}
	if(m_pEditWriteTitle)
	{
		m_pEditWriteTitle->DeleteDeviceObjects();
		util::del(m_pEditWriteTitle);		
	}
	if(m_pEditWriteInfo)
	{
		m_pEditWriteInfo->DeleteDeviceObjects();
		util::del(m_pEditWriteInfo);				
	}
	if(m_pScrollWrite)
	{
		m_pScrollWrite->DeleteDeviceObjects();
		util::del(m_pScrollWrite);
	}
	
	return S_OK;
}

void CINFCommunityLetter::Tick()
{
	switch(m_nLetterMode)
	{
	case LETTER_MODE_READ:
		{			
		}
		break;
	case LETTER_MODE_WRITE:
		{			
		}
		break;		
	}

}

void CINFCommunityLetter::Render(POINT ptPos)
{
#ifndef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBack->Move(ptPos.x, ptPos.y);
	m_pBack->Render();
#endif
	// �������
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		m_pLetterMode[m_nLetterMode]->Move(ptPos.x, ptPos.y+LETTER_MODE_POS_Y);
#else	   
		m_pLetterMode[m_nLetterMode]->Move(ptPos.x+LETTER_MODE_POS_X, ptPos.y+LETTER_MODE_POS_Y);
#endif
		m_pLetterMode[m_nLetterMode]->Render();
	}
	switch(m_nLetterMode)
	{
	case LETTER_MODE_READ:
		{
			RenderLetterRead(ptPos);			
		}
		break;
	case LETTER_MODE_WRITE:
		{			
			RenderLetterWrite(ptPos);
		}
		break;		
	}
}

void CINFCommunityLetter::RenderLetterRead(POINT ptBkPos)
{
	switch(m_nReadLetterMode)
	{
	case LETTER_READ_MODE_LIST:
		{
			// ����Ʈ ���
			m_pLetterReadListBk->Move(ptBkPos.x+LETTER_READ_LIST_BK_X, ptBkPos.y+LETTER_READ_LIST_BK_Y);
			m_pLetterReadListBk->Render();

			// ��ư
			m_pReadBtn->Render();	
			m_pReadDelBtn->Render();

			// ��ũ��
			m_pScrollRead->Render();

			RenderReadLetter(ptBkPos);
		}
		break;
	case LETTER_READ_MODE_INFO:
		{
			/////////////////////////////// ���� ///////////////////////////////////////////
			// ���� �б� ���
			m_pLetterReadBk->Move(ptBkPos.x+LETTER_READ_INFO_BK_X, ptBkPos.y+LETTER_READ_INFO_BK_Y);
			m_pLetterReadBk->Render();

			// �޴� ���
			m_pEditReadReceiveUser->Tick();
			m_pEditReadReceiveUser->Render();
			// ����
			m_pEditReadTitle->Tick();
			m_pEditReadTitle->Render();
			// ����
			m_pEditReadInfo->Tick();
			m_pEditReadInfo->Render(m_pScrollReadInfo->GetScrollStep(), LETTER_INFO_READ_MAX_SCROLL_LINE);
			
			m_pScrollReadInfo->Render();

			m_pReadResponseBtn->Render();			// �б� ����
			m_pReadListDelBtn->Render();			// �б� ����
			m_pReadBackBtn->Render();				// �б� �ڷ�
		}
		break;
	}	
}

void CINFCommunityLetter::RenderLetterWrite(POINT ptBkPos)
{
	m_pSendBtn->Render();			// ������
	const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();		
	// ������ �� �������� Ȥ�� �����ڴ� ä�� �������� ���ܵȴ�.
	if(COMPARE_RACE(myShuttleInfo.Race, RACE_INFLUENCE_LEADER)
		||COMPARE_RACE(myShuttleInfo.Race, RACE_INFLUENCE_SUBLEADER_1)
		||COMPARE_RACE(myShuttleInfo.Race, RACE_INFLUENCE_SUBLEADER_2)
		|| COMPARE_RACE(myShuttleInfo.Race, RACE_OPERATION | RACE_GAMEMASTER | RACE_MONITOR))
	{
	m_pAllSendBtn->Render();		// ��ü �߼�
	}

	/////////////////////////////// ���� ����///////////////////////////////////////////
	m_pEditWriteSendUser->Tick();
	m_pEditWriteSendUser->Render();
	// �޴� ���
	m_pEditWriteReceiveUser->Tick();
	m_pEditWriteReceiveUser->Render();
	// ����
	m_pEditWriteTitle->Tick();
	m_pEditWriteTitle->Render();
	// ����
	m_pEditWriteInfo->Tick();
	m_pEditWriteInfo->Render(m_pScrollWrite->GetScrollStep(), LETTER_INFO_MAX_SCROLL_LINE);

	m_pScrollWrite->Render();
}

int CINFCommunityLetter::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(m_nLetterMode)
	{
	case LETTER_MODE_READ:
		{
			if(INF_MSGPROC_BREAK == WndProcLetterRead(uMsg, wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case LETTER_MODE_WRITE:
		{
			if(INF_MSGPROC_BREAK == WndProcLetterWrite(uMsg, wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;		
	}

	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(INF_MSGPROC_BREAK == OnLButtonDown(pt))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	}
	

	return INF_MSGPROC_NORMAL;	

}



int CINFCommunityLetter::OnLButtonDown(POINT pt)
{
	// ��� 
	POINT ptBkPos = ((CINFCommunity*)m_pParent)->GetCommunityBkPos();
	int nCnt = 0;

	// ��Ŭ�� 
	{
		int nStartTabX = ptBkPos.x + LETTER_MODE_POS_X;
		int nStartTabY = ptBkPos.y + LETTER_MODE_POS_Y;
		int	nWidth = LETTER_MODE_WIDTH;
		int nHeight = LETTER_MODE_HEIGHT;
		
		for(nCnt = 0;nCnt < MAX_LETTER_MODE;nCnt++)
		{
			nStartTabX = ptBkPos.x + LETTER_MODE_POS_X + (nWidth*nCnt);
			if((pt.y >= nStartTabY )
				&&(pt.y <= (nStartTabY + nHeight))
				&&(pt.x >= nStartTabX)
				&&(pt.x <= nStartTabX+nWidth))
				
			{
				ChangeLetterMode(nCnt, 0, NULL, FALSE, 0);				
				return INF_MSGPROC_BREAK;
			}
		}
	}
	

	// ��� ��	
	if((pt.y >= ptBkPos.y )
				&&(pt.y <= (ptBkPos.y + 404))
				&&(pt.x >= ptBkPos.x)
				&&(pt.x <= (ptBkPos.x+518)))
	{
		return INF_MSGPROC_BREAK;
	}


	return INF_MSGPROC_NORMAL;
}

void CINFCommunityLetter::ChangeLetterMode(int nLetterMode, int nSubLetterMode, char* pUser, 
											BOOL bAllMail, UID64_t uReadLetterUID)
{
	m_nLetterMode = nLetterMode;
	InitLetterMode();
	switch(m_nLetterMode)
	{
	case LETTER_MODE_READ:
		{
			m_nReadLetterMode = nSubLetterMode;
			switch(m_nReadLetterMode)
			{
			case LETTER_READ_MODE_LIST:
				{
					RqLetterTitle(FALSE);					
				}
				break;			
			case LETTER_READ_MODE_INFO:
				{
					m_uReadLetterUID = uReadLetterUID;	
					m_bAllMail = bAllMail;
					RqLetterRead(bAllMail, m_uReadLetterUID);
				}
				break;	
			}
		}
		break;
	case LETTER_MODE_WRITE:
		{
			if(pUser)
			{
				m_pEditWriteReceiveUser->SetString(pUser, strlen(pUser)+1);
				m_pEditWriteReceiveUser->BackupTxtString();	// ��Ʈ���� �����޴´�.

				OnClickWriteEditBox(LETTER_WRITE_USER_EDIT, m_pEditWriteReceiveUser);// �������� ����Ʈ Enable
			}
		}
		break;
	}	
}

void CINFCommunityLetter::InitLetterMode()
{
	m_pEditWriteReceiveUser->EnableEdit(FALSE, FALSE);		// �޴� ����
	m_pEditWriteTitle->EnableEdit(FALSE, FALSE);			// ����
	m_pEditWriteInfo->EnableEdit(FALSE, FALSE);			// ����
}

int CINFCommunityLetter::WndProcLetterRead(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			switch(m_nReadLetterMode)
			{
			case LETTER_READ_MODE_LIST:
				{
					if(INF_MSGPROC_BREAK == OnLButtonDown_ReadList(pt))
					{
						return INF_MSGPROC_BREAK;
					}					
				}
				break;
			case LETTER_READ_MODE_INFO:
				{		
					{
						if(TRUE == m_pReadResponseBtn->OnLButtonDown(pt))
						{
							// ��ư���� ���콺�� �ִ�.
							return  INF_MSGPROC_BREAK;
						}		
					}
					{
						if(TRUE == m_pReadListDelBtn->OnLButtonDown(pt))
						{
							// ��ư���� ���콺�� �ִ�.
							return  INF_MSGPROC_BREAK;
						}		
					}
					{
						if(TRUE == m_pReadBackBtn->OnLButtonDown(pt))
						{
							// ��ư���� ���콺�� �ִ�.
							return  INF_MSGPROC_BREAK;
						}		
					}
					{
						// 2010. 02. 11 by jskim ���� ���� ���� �� ��ũ�� �ȵǴ� ���� ����
// 						BOOL bClick = m_pScrollWrite->IsMouseBallPos(pt);
// 						if(bClick)
// 						{
// 							m_pScrollWrite->SetMouseMoveMode(TRUE);
						BOOL bClick = m_pScrollReadInfo->IsMouseBallPos(pt);
						
						if(bClick)
						{
							m_pScrollReadInfo->SetMouseMoveMode(TRUE);
						//end 2010. 02. 11 by jskim ���� ���� ���� �� ��ũ�� �ȵǴ� ���� ����
							return INF_MSGPROC_BREAK;
						}
					}

				}
				break;
			}
			
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			switch(m_nReadLetterMode)
			{
			case LETTER_READ_MODE_LIST:
				{
					m_pReadBtn->OnMouseMove(pt);
					m_pReadDelBtn->OnMouseMove(pt);
					{
						if(m_pScrollRead->GetMouseMoveMode())
						{
							if(FALSE == m_pScrollRead->IsMouseScrollPos(pt))
							{
								m_pScrollRead->SetMouseMoveMode(FALSE);
							}
							else
							{
								m_pScrollRead->SetScrollPos(pt);
								return INF_MSGPROC_BREAK;
							}
						}
					}
				}
				break;
			case LETTER_READ_MODE_INFO:
				{
					m_pReadResponseBtn->OnMouseMove(pt);
					m_pReadListDelBtn->OnMouseMove(pt);
					m_pReadBackBtn->OnMouseMove(pt);
					{
						// 2010. 02. 11 by jskim ���� ���� ���� �� ��ũ�� �ȵǴ� ���� ����
// 						if(m_pScrollWrite->GetMouseMoveMode())
// 						{
// 							if(FALSE == m_pScrollWrite->IsMouseScrollPos(pt))
// 							{
// 								m_pScrollWrite->SetMouseMoveMode(FALSE);
// 							}
// 							else
// 							{
// 								m_pScrollWrite->SetScrollPos(pt);
// 								return INF_MSGPROC_BREAK;
// 							}
// 						}
						if(m_pScrollReadInfo->GetMouseMoveMode())
						{
							if(FALSE == m_pScrollReadInfo->IsMouseScrollPos(pt))
							{
								m_pScrollReadInfo->SetMouseMoveMode(FALSE);
							}
							else
							{
								m_pScrollReadInfo->SetScrollPos(pt);
								return INF_MSGPROC_BREAK;
							}
						}
						//end 2010. 02. 11 by jskim ���� ���� ���� �� ��ũ�� �ȵǴ� ���� ����
					}

				}
				break;
			}
			
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			switch(m_nReadLetterMode)
			{
			case LETTER_READ_MODE_LIST:
				{
					if(INF_MSGPROC_BREAK == OnLButtonUp_Read(pt))
					{
						return INF_MSGPROC_BREAK;
					}					
				}
				break;
			case LETTER_READ_MODE_INFO:
				{
					{
						if(TRUE == m_pReadResponseBtn->OnLButtonUp(pt))
						{	
							char chUser[SIZE_MAX_ARENA_FULL_NAME];
							memset(chUser, 0x00, SIZE_MAX_ARENA_FULL_NAME);
							
							m_pEditReadReceiveUser->GetString(chUser, SIZE_MAX_ARENA_FULL_NAME);
							ChangeLetterMode(LETTER_MODE_WRITE, 0, chUser, FALSE, 0);
							
							
							g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
							return  INF_MSGPROC_BREAK;
						}
					}
					{
						if(TRUE == m_pReadListDelBtn->OnLButtonUp(pt))
						{				
							RqDelReadLetter(m_bAllMail, m_uReadLetterUID);
							//ChangeLetterMode(LETTER_MODE_READ, LETTER_READ_MODE_LIST, NULL, FALSE,0);
							g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
							return  INF_MSGPROC_BREAK;
						}
					}
					{
						if(TRUE == m_pReadBackBtn->OnLButtonUp(pt))
						{				
							ChangeLetterMode(LETTER_MODE_READ, LETTER_READ_MODE_LIST, NULL, FALSE,0);
							g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
							return  INF_MSGPROC_BREAK;
						}
					}
					// ��ũ��
					{
						// 2010. 02. 11 by jskim ���� ���� ���� �� ��ũ�� �ȵǴ� ���� ����
// 						BOOL bClick = m_pScrollWrite->GetMouseMoveMode();
// 						if(bClick)
// 						{
// 							m_pScrollWrite->SetMouseMoveMode(FALSE);
// 							return INF_MSGPROC_BREAK;
// 						}
						BOOL bClick = m_pScrollReadInfo->GetMouseMoveMode();
						if(bClick)
						{
							m_pScrollReadInfo->SetMouseMoveMode(FALSE);
							return INF_MSGPROC_BREAK;
						}				
						//end 2010. 02. 11 by jskim ���� ���� ���� �� ��ũ�� �ȵǴ� ���� ����
					}
				}
				break;
			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			switch(m_nReadLetterMode)
			{
			case LETTER_READ_MODE_LIST:
				{
					BOOL bClick = m_pScrollRead->IsMouseWhellPos(pt);
					if(bClick)		
					{			
						m_pScrollRead->OnMouseWheel(wParam, lParam);	
						return INF_MSGPROC_BREAK;
					}
					
				}
				break;
			case LETTER_READ_MODE_INFO:
				{
					// 2010. 02. 11 by jskim ���� ���� ���� �� ��ũ�� �ȵǴ� ���� ����
// 					BOOL bClick = m_pScrollWrite->IsMouseWhellPos(pt);
// 					if(bClick)		
// 					{			
// 						m_pScrollWrite->OnMouseWheel(wParam, lParam);	
// 						return INF_MSGPROC_BREAK;
// 					}
					BOOL bClick = m_pScrollReadInfo->IsMouseWhellPos(pt);
					if(bClick)		
					{			
						m_pScrollReadInfo->OnMouseWheel(wParam, lParam);	
						return INF_MSGPROC_BREAK;
					}
					//end 2010. 02. 11 by jskim ���� ���� ���� �� ��ũ�� �ȵǴ� ���� ����
				}
				break;
			}			
		}
		break;	
	case WM_LBUTTONDBLCLK:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			switch(m_nReadLetterMode)
			{
			case LETTER_READ_MODE_LIST:
				{
					int nSelReadLetterPos = GetReadLetterCurselPos(pt);		
					
					if(nSelReadLetterPos>=0)
					{				
						if(m_nSelReadLetterPos == nSelReadLetterPos)
						{
							OnClickReadLetter(nSelReadLetterPos);
							return INF_MSGPROC_BREAK;
						}
					}
				}
				break;
			}
					
		}
		break;
	}
	return INF_MSGPROC_NORMAL;	
}

int CINFCommunityLetter::OnLButtonDown_ReadList(POINT pt)
{
	int nCnt = 0;
	
	{
		if(TRUE == m_pReadBtn->OnLButtonDown(pt))
		{
			// ��ư���� ���콺�� �ִ�.
			return  INF_MSGPROC_BREAK;
		}		
	}
	
	{
		if(TRUE == m_pReadDelBtn->OnLButtonDown(pt))
		{
			// ��ư���� ���콺�� �ִ�.
			return  INF_MSGPROC_BREAK;
		}		
	}
	{
		BOOL bClick = m_pScrollRead->IsMouseBallPos(pt);
		if(bClick)
		{
			m_pScrollRead->SetMouseMoveMode(TRUE);
			return INF_MSGPROC_BREAK;
		}
	}	
	
	m_nSelReadLetterPos = GetReadLetterCurselPos(pt);
	return INF_MSGPROC_NORMAL;
}

int CINFCommunityLetter::OnLButtonDown_ReadInfo(POINT pt)
{
	return INF_MSGPROC_NORMAL;
}


int CINFCommunityLetter::OnLButtonUp_Read(POINT pt)
{
	{
		if(TRUE == m_pReadBtn->OnLButtonUp(pt))
		{				
			if(m_nSelReadLetterPos >= 0)
			{
				OnClickReadLetter(m_nSelReadLetterPos);
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
				return  INF_MSGPROC_BREAK;
			}
			
		}
	}
	
	{
		if(TRUE == m_pReadDelBtn->OnLButtonUp(pt))
		{	
			if(m_nSelReadLetterPos >= 0 && m_nSelReadLetterPos < (int)m_vecReadLetter.size())
			{
				structReadLetterItemInfo sMsg= m_vecReadLetter[m_nSelReadLetterPos];
				RqDelReadLetter(sMsg.bAllMail, sMsg.LetterUID);
				
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
				return  INF_MSGPROC_BREAK;
			}			
		}
	}
	{
		BOOL bClick = m_pScrollRead->GetMouseMoveMode();
		if(bClick)
		{
			m_pScrollRead->SetMouseMoveMode(FALSE);
			return INF_MSGPROC_BREAK;
		}				
	}
	return INF_MSGPROC_NORMAL;	
}

int CINFCommunityLetter::WndProcLetterWrite(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// ������
			m_pSendBtn->OnMouseMove(pt);
			m_pAllSendBtn->OnMouseMove(pt);

			if(m_pScrollWrite->GetMouseMoveMode())
			{
				if(FALSE == m_pScrollWrite->IsMouseScrollPos(pt))
				{
					m_pScrollWrite->SetMouseMoveMode(FALSE);
				}
				else
				{
					m_pScrollWrite->SetScrollPos(pt);
					return INF_MSGPROC_BREAK;
				}
			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			BOOL bClick = m_pScrollWrite->IsMouseWhellPos(pt);
			if(bClick)		
			{			
				m_pScrollWrite->OnMouseWheel(wParam, lParam);	
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			BOOL bClick = m_pScrollWrite->GetMouseMoveMode();
			if(bClick)
			{
				m_pScrollWrite->SetMouseMoveMode(FALSE);
				return INF_MSGPROC_BREAK;
			}

			{
				// ���� ������
				if(TRUE == m_pSendBtn->OnLButtonUp(pt))
				{					
					// ���� ������ Ŭ��
					OnClickLetterSend(FALSE);
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
					return  INF_MSGPROC_BREAK;
				}
			}
			
			{
				// ���� ������
				if(TRUE == m_pAllSendBtn->OnLButtonUp(pt))
				{					
					// ���� ������ Ŭ��
					OnClickLetterSend(TRUE);
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
					return  INF_MSGPROC_BREAK;
				}
			}

		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// �޴� ����
			if(TRUE == m_pEditWriteReceiveUser->OnLButtonDown(pt))
			{
				OnClickWriteEditBox(LETTER_WRITE_USER_EDIT, m_pEditWriteReceiveUser);
				return INF_MSGPROC_BREAK;
			}
			// ����
			if(TRUE == m_pEditWriteTitle->OnLButtonDown(pt))
			{
				OnClickWriteEditBox(LETTER_WRITE_TITLE_EDIT, m_pEditWriteTitle);
				return INF_MSGPROC_BREAK;
			}
			// ����
			if(TRUE == m_pEditWriteInfo->OnLButtonDown(pt))
			{
				OnClickWriteEditBox(LETTER_WRITE_INFO_EDIT, NULL);
				return INF_MSGPROC_BREAK;
			}
			{
				BOOL bClick = m_pScrollWrite->IsMouseBallPos(pt);
				if(bClick)
				{
					m_pScrollWrite->SetMouseMoveMode(TRUE);
					return INF_MSGPROC_BREAK;
				}
			}
			{
				//  ����������
				if(TRUE == m_pSendBtn->OnLButtonDown(pt))
				{
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
				}		
			}
			
			{
				//  ����������
				if(TRUE == m_pAllSendBtn->OnLButtonDown(pt))
				{
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
				}		
			}
		}
		break;
	case WM_IME_STARTCOMPOSITION:
//	case WM_IME_NOTIFY:
	case WM_IME_COMPOSITION:
	case WM_INPUTLANGCHANGE:	
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_SETCONTEXT:	
	case WM_CHAR:
	case WM_KEYDOWN:
	// 2010. 04. 12 by ckPark �������� ���� ����Ʈ �ڽ� ��� ����
	case WM_KEYUP:
	// end 2010. 04. 12 by ckPark �������� ���� ����Ʈ �ڽ� ��� ����
		{			
			switch(m_nSelLetterWrite)
			{
			case LETTER_WRITE_USER_EDIT:	// �޴� ����
				{
					if(m_pEditWriteReceiveUser->WndProc(uMsg, wParam, lParam, NULL, TRUE))
					{
						return INF_MSGPROC_BREAK;
					}
				}
				break;	
			case LETTER_WRITE_TITLE_EDIT:	// ����
				{
					if(m_pEditWriteTitle->WndProc(uMsg, wParam, lParam, NULL, TRUE))
					{
						return INF_MSGPROC_BREAK;
					}
				}
				break;
			case LETTER_WRITE_INFO_EDIT:	// ����
				{
					int nLienCnt = -1;
					int nArrowScroll = 0;
					BOOL bRtn = FALSE;
					BOOL bStrCat =FALSE;
					bRtn = m_pEditWriteInfo->WndProc(uMsg, wParam, lParam, m_pScrollWrite->GetScrollStep(), 
										&nLienCnt, &nArrowScroll, &bStrCat);
					
					if(nLienCnt < 0)
					{
						// �ƹ� ó���� ���ߴ�.
						return INF_MSGPROC_NORMAL;
					}			
					int nMaxStep = 0;			
					int nScrollStep = 0;
					switch(uMsg)
					{
					case WM_KEYDOWN:
						{
							switch(wParam)
							{
							case VK_LEFT:	// �������� �̵�
							case VK_UP:
							case VK_RIGHT:
							case VK_DOWN:
							// 2010. 04. 12 by ckPark �������� ���� ����Ʈ �ڽ� ��� ����
							case VK_BACK:
							// end 2010. 04. 12 by ckPark �������� ���� ����Ʈ �ڽ� ��� ����
								{
									// ����Ű�� ������ ��ũ�� ��ġ ���� 
									if(nLienCnt > LETTER_INFO_MAX_SCROLL_LINE 
										&& nArrowScroll !=0)
									{
										nMaxStep = m_pScrollWrite->GetMaxStepCnt();
										nScrollStep = m_pScrollWrite->GetScrollStep() + nArrowScroll;
										nScrollStep = max(0, nScrollStep);						
										nScrollStep = min(nMaxStep, nScrollStep);						
										m_pScrollWrite->SetScrollStep(nScrollStep);
									}
									
									return INF_MSGPROC_NORMAL;
								}
								break;
							case VK_RETURN:
								{
									return INF_MSGPROC_BREAK;
								}
								break;
							}
						}
						break;
					}
					
					nMaxStep = max(nLienCnt, LETTER_INFO_MAX_SCROLL_LINE);
					nScrollStep = nMaxStep - LETTER_INFO_MAX_SCROLL_LINE;
					if(nScrollStep < 0)
					{
						nScrollStep = 0;
					}						
					if(m_pEditWriteInfo->IsLastPos())
					{
						// ���� ������ �����̳�?					
						
						// �ִ� �������� �����ְ�
						m_pScrollWrite->SetMaxItem(nMaxStep);					
						// ��Ʈ���� �ڿ� ���̴� ����� �ƴϴ�.
						// ��ũ�� ��ġ�� ���� �Ʒ�
						m_pScrollWrite->SetScrollStep(nScrollStep);								
					}					
					else
					{
						m_pScrollWrite->SetOnlyMaxItem(nMaxStep);
						m_pEditWriteInfo->RefreshEndCurselPos();	// ��������ġ ����
					}
					
					if(bRtn)
					{
						return INF_MSGPROC_BREAK;
					}					
					
				}
				break;
			}			
		}
		break;	
	}
	return INF_MSGPROC_NORMAL;	
}

void CINFCommunityLetter::OnClickWriteEditBox(int nSelLetterWrite, CINFEditBox*	pSelEdit)
{
	m_nSelLetterWrite = nSelLetterWrite;

	if(m_pEditWriteReceiveUser->IsEditMode())
	{
		m_pEditWriteReceiveUser->BackupTxtString();
	}
	if(m_pEditWriteTitle->IsEditMode())
	{
		m_pEditWriteTitle->BackupTxtString();
	}
	if(m_pEditWriteInfo->IsEditMode())
	{
		m_pEditWriteInfo->BackupTxtString();
	}
	m_pEditWriteReceiveUser->EnableEdit(FALSE, FALSE);		// �޴� ����
	m_pEditWriteTitle->EnableEdit(FALSE, FALSE);				// ����
	m_pEditWriteInfo->EnableEdit(FALSE, FALSE);				// ����

	// ������ �������̽��� ��
	if(pSelEdit)
	{
		pSelEdit->EnableEdit(TRUE, TRUE);
	}
	else if(LETTER_WRITE_INFO_EDIT == m_nSelLetterWrite)
	{
		m_pEditWriteInfo->EnableEdit(TRUE, TRUE);
	}

}

void CINFCommunityLetter::TestReadDb()
{
	structReadLetterItemInfo sMsg;
	memset(&sMsg, 0x00, sizeof(sMsg));
	int nCnt = 0;
	for(nCnt = 0;nCnt< 20;nCnt++)
	{
		wsprintf(sMsg.chSendUser, "User%d", nCnt);
		wsprintf(sMsg.chLetterTitle, "Title%d", nCnt);
		sMsg.bReadMail = (nCnt%2);		
		//wsprintf(sMsg.chLetterInfo, "�뷡 �����ߴ�. �뷡������.[%d] ",nCnt);
		sMsg.LetterUID = nCnt;

		AddReadLetter(FALSE, sMsg.bReadMail, sMsg.LetterUID, sMsg.chSendUser, sMsg.chLetterTitle, sMsg.atimeMail);
	}
}

void CINFCommunityLetter::AddReadLetter(BOOL bAllMail, BOOL bReadMail, UID64_t   LetterUID, char* pSendUser, char* pLetterTitle, ATUM_DATE_TIME	atimeMail)
{
	structReadLetterItemInfo sMsg;
	memset(&sMsg, 0x00, sizeof(sMsg));

	sMsg.LetterUID = LetterUID;	
	util::strncpy(sMsg.chSendUser, pSendUser, SIZE_MAX_ARENA_FULL_NAME);
	util::strncpy(sMsg.chLetterTitle, pLetterTitle, SIZE_MAX_ARENA_FULL_NAME);	// ����
	
	sMsg.atimeMail = atimeMail;
	sMsg.bReadMail = bReadMail;	
	sMsg.bAllMail  = bAllMail;

	m_vecReadLetter.push_back(sMsg);
	m_pScrollRead->SetMaxItem((int)m_vecReadLetter.size());

	sort(m_vecReadLetter.begin(), m_vecReadLetter.end(), Letter_Sort());	

	// 2024/23/12 - Nexy : Recount unread letters and reset additional letter count when browsing
	CountUnreadLetters();
}
void CINFCommunityLetter::RqDelReadLetter(BOOL bAllMail, UID64_t   LetterUID)
{
	// ���� ���� ��û
	MessageType_t msgType = T_FC_CHAT_LETTER_DELETE;
	vector<MessageType_t> vecUnLockMsg;
	vecUnLockMsg.clear();	

	if(!bAllMail)
	{		
		msgType = T_FC_CHAT_LETTER_DELETE;
		vecUnLockMsg.push_back(T_FC_CHAT_LETTER_DELETE);		
		vecUnLockMsg.push_back(T_FC_CHAT_LETTER_DELETE_OK);				

		MSG_FC_CHAT_LETTER_DELETE sMsg;
		memset(&sMsg, 0x00, sizeof(MSG_FC_CHAT_LETTER_DELETE));
		sMsg.LetterUID = LetterUID;
		g_pFieldWinSocket->SendMsg(msgType, (char*)&sMsg, sizeof(sMsg));
	}
	else
	{
		msgType = T_FC_CHAT_ALLLETTER_DELETE;
		vecUnLockMsg.push_back(T_FC_CHAT_ALLLETTER_DELETE);		
		vecUnLockMsg.push_back(T_FC_CHAT_ALLLETTER_DELETE_OK);		
		
		MSG_FC_CHAT_ALLLETTER_DELETE sMsg;
		memset(&sMsg, 0x00, sizeof(MSG_FC_CHAT_ALLLETTER_DELETE));
		sMsg.LetterUID = LetterUID;
		g_pFieldWinSocket->SendMsg(msgType, (char*)&sMsg, sizeof(sMsg));

	}
	// �ϳ��� ��Ī �Ǿ ���� Ǯ����. 
	g_pD3dApp->EnterMultiLock(TRUE, msgType, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);
	
}

void CINFCommunityLetter::DelReadLetter()
{
	// ���� ������ �����Ǿ���.���� ��û�� ����
	/*
	vector<structReadLetterItemInfo>::iterator it = m_vecReadLetter.begin();
	while(it != m_vecReadLetter.end())
	{
		structReadLetterItemInfo stTmp = (*it);
		if((stTmp.bAllMail == m_bDelAllMail)
			&& (stTmp.LetterUID == m_uDelLetterUID))
		{
			it = m_vecReadLetter.erase(it);
			continue;
		}
		it++;
	}

	// ��ũ�� ����Ʈ ����
	m_pScrollRead->SetMaxItem(m_vecReadLetter.size());
	if(m_nSelReadLetterPos >= m_vecReadLetter.size())
	{
		// ������ ������ ����
		m_nSelReadLetterPos =-1;
	}
	*/

}

void CINFCommunityLetter::RenderReadLetter(POINT ptBkPos)
{
	int nCnt = 0;
	int nLine = 0;
	int nStartX, nStartY;
	nStartX = nStartY = 0;
	int nRenderLine = m_nSelReadLetterPos - m_pScrollRead->GetScrollStep();	// ������ ������
	vector<structReadLetterItemInfo>::iterator it = m_vecReadLetter.begin();

	for(nCnt=0; nCnt < m_pScrollRead->GetScrollStep();nCnt++)
	{
		if(it != m_vecReadLetter.end())
		{			
			it++;
		}
	}		
	char chBuff[512];
	memset(chBuff, 0x00, 512);

	while(it != m_vecReadLetter.end())
	{
		if(nLine >= MAX_LETTER_READ_NUMBER)
		{
			break;
		}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
		structReadLetterItemInfo stTmp = (*it);
		nStartX = ptBkPos.x + LETTER_READ_ITEM_X+ 6;
		nStartY = ptBkPos.y + LETTER_READ_ITEM_Y + (LETTER_READ_ITEM_HEIGHT*nLine) + 4;
		m_pLetterRead[stTmp.bReadMail]->Move(nStartX, nStartY);
		m_pLetterRead[stTmp.bReadMail]->Render();

		
		// �������
		nStartX = ptBkPos.x + LETTER_READ_ITEM_X;
		nStartY = ptBkPos.y + LETTER_READ_ITEM_Y + (LETTER_READ_ITEM_HEIGHT*nLine);
		nStartX += 55;

		strncpy(chBuff, stTmp.chSendUser, strlen(stTmp.chSendUser)+1);
		g_pGameMain->TextReduce(m_pFontLetter, 90, chBuff);
		m_pFontLetter->DrawText( nStartX, nStartY + 5, 
										 GUI_FONT_COLOR,
										 chBuff, 0L );		
		// ����
		nStartX += 105;
		strncpy(chBuff, stTmp.chLetterTitle, strlen(stTmp.chLetterTitle)+1);
		g_pGameMain->TextReduce(m_pFontLetter, 130, chBuff);
		m_pFontLetter->DrawText( nStartX, nStartY + 5, 
										 GUI_FONT_COLOR,
										 chBuff, 0L );		

		// �ð� 
		nStartX += 140;
		string szStrBuf;
		stTmp.atimeMail.GetLocalString_YYYYMMDD(stTmp.atimeMail.Year, 
													stTmp.atimeMail.Month, 
													stTmp.atimeMail.Day, 
													szStrBuf);	
		m_pFontLetter->DrawText( nStartX, nStartY + 5, 
										 GUI_FONT_COLOR,
										 (char*)szStrBuf.c_str(), 0L );	
#else
		structReadLetterItemInfo stTmp = (*it);
		nStartX = ptBkPos.x + LETTER_READ_ITEM_X+ 1;
		nStartY = ptBkPos.y + LETTER_READ_ITEM_Y + (LETTER_READ_ITEM_HEIGHT*nLine) - 2;
		m_pLetterRead[stTmp.bReadMail]->Move(nStartX, nStartY);
		m_pLetterRead[stTmp.bReadMail]->Render();

		
		// �������
		nStartX = ptBkPos.x + LETTER_READ_ITEM_X;
		nStartY = ptBkPos.y + LETTER_READ_ITEM_Y + (LETTER_READ_ITEM_HEIGHT*nLine);
		nStartX += 30;

		strncpy(chBuff, stTmp.chSendUser, strlen(stTmp.chSendUser)+1);
		g_pGameMain->TextReduce(m_pFontLetter, 90, chBuff);
		m_pFontLetter->DrawText( nStartX, nStartY, 
										 GUI_FONT_COLOR,
										 chBuff, 0L );		
		// ����
		nStartX += 105;
		strncpy(chBuff, stTmp.chLetterTitle, strlen(stTmp.chLetterTitle)+1);
		g_pGameMain->TextReduce(m_pFontLetter, 130, chBuff);
		m_pFontLetter->DrawText( nStartX, nStartY, 
										 GUI_FONT_COLOR,
										 chBuff, 0L );		

		// �ð� 
		nStartX += 150;
		string szStrBuf;
		stTmp.atimeMail.GetLocalString_YYYYMMDD(stTmp.atimeMail.Year, 
													stTmp.atimeMail.Month, 
													stTmp.atimeMail.Day, 
													szStrBuf,
													GetLanguageType());	
		m_pFontLetter->DrawText( nStartX, nStartY, 
										 GUI_FONT_COLOR,
										 (char*)szStrBuf.c_str(), 0L );		

#endif	

		nLine++;
		it++;
	}	
	
	if(nRenderLine >= 0 && nRenderLine < MAX_LETTER_READ_NUMBER)
	{
		int nSelPosX = ptBkPos.x + LETTER_READ_ITEM_X -4 ;		
		int nSelPosY = ptBkPos.y + LETTER_READ_ITEM_Y + (LETTER_READ_ITEM_HEIGHT*nRenderLine)- 4;
		m_pImgSelect->Move(nSelPosX, nSelPosY);
		m_pImgSelect->Render();
	}
}

int CINFCommunityLetter::GetReadLetterCurselPos(POINT pt)
{
	POINT ptBkPos = ((CINFCommunity*)m_pParent)->GetCommunityBkPos();

	int nLine = 0;
	int nStartX = (ptBkPos.x + LETTER_MODE_POS_X);
	int nStartY = (ptBkPos.y + LETTER_READ_ITEM_Y);
	int nCurSel = -1;
	if((pt.x >= nStartX)
		&& (pt.x <= (nStartX + LETTER_READ_ITEM_WIDTH)))
	{
		for(nLine =0;nLine <MAX_LETTER_READ_NUMBER;nLine++)
		{
			nStartY = (ptBkPos.y + LETTER_READ_ITEM_Y)+(nLine*LETTER_READ_ITEM_HEIGHT);
			if((pt.y >= nStartY)
				&& (pt.y <= (nStartY + LETTER_READ_ITEM_HEIGHT)))
			{
				nCurSel = nLine;
			}			
		}
	}
	
	int nSelCurPos = -1;
	if(nCurSel>=0)
	{
		nSelCurPos = nCurSel+m_pScrollRead->GetScrollStep();
		if(nSelCurPos >= (int)m_vecReadLetter.size())
		{
			nSelCurPos =-1;
		}
	}
	else
	{
		nSelCurPos = -1;
	}
	return nSelCurPos;
}

void CINFCommunityLetter::OnClickReadLetter(int nSelReadLetterPos)
{
	vector<structReadLetterItemInfo>::iterator it = m_vecReadLetter.begin();

	int nMailIdx = 0;
	while(it != m_vecReadLetter.end())
	{
		structReadLetterItemInfo stTmp = (*it);

		if(nMailIdx == nSelReadLetterPos)
		{				
			ChangeLetterMode(LETTER_MODE_READ, LETTER_READ_MODE_INFO, NULL, stTmp.bAllMail, stTmp.LetterUID);
			return;

			break;
		}
		nMailIdx ++;
		it++;		
	}
}


void CINFCommunityLetter::RqLetterTitle(BOOL bLetterFirstRq)
{	
	m_bLetterFirstRq = bLetterFirstRq;	// ó������ ���� ������ ��û�߳�?

	// ���� ���� ����Ʈ�� �ʱ�ȭ ���ش�.
	m_nSelReadLetterPos =-1; // �����׸����
	m_vecReadLetter.clear();
	m_pScrollRead->SetMaxItem((int)m_vecReadLetter.size());
	{
		vector<MessageType_t> vecUnLockMsg;
		vecUnLockMsg.clear();
		vecUnLockMsg.push_back(T_FC_CHAT_LETTER_REQUEST_TITLE);		
		vecUnLockMsg.push_back(T_FC_CHAT_LETTER_REQUEST_TITLE_OK_DONE);		
		// �ϳ��� ��Ī �Ǿ ���� Ǯ����. 
		g_pD3dApp->EnterMultiLock(TRUE, T_FC_CHAT_LETTER_REQUEST_TITLE, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);
	}

	g_pFieldWinSocket->SendMsg(T_FC_CHAT_LETTER_REQUEST_TITLE, NULL, NULL);	
}

void CINFCommunityLetter::RqAllLetterTitle()
{
	{
		vector<MessageType_t> vecUnLockMsg;
		vecUnLockMsg.clear();
		vecUnLockMsg.push_back(T_FC_CHAT_ALLLETTER_REQUEST_TITLE);		
		vecUnLockMsg.push_back(T_FC_CHAT_ALLLETTER_REQUEST_TITLE_OK_DONE);		
		// �ϳ��� ��Ī �Ǿ ���� Ǯ����. 
		g_pD3dApp->EnterMultiLock(TRUE, T_FC_CHAT_ALLLETTER_REQUEST_TITLE, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);
	}
	g_pFieldWinSocket->SendMsg(T_FC_CHAT_ALLLETTER_REQUEST_TITLE, NULL, NULL);	

}
void CINFCommunityLetter::RqLetterRead(BOOL bAllMail, UID64_t uReadLetterUID)
{
	structReadLetterItemInfo  struItem;
	memset(&struItem, 0x00, sizeof(structReadLetterItemInfo ));

	if(!GetLetterItemInfo(bAllMail, uReadLetterUID, &struItem))
	{
		return;
	}
	

	// ������ ������ ������ ��û�Ѵ�.
	vector<MessageType_t> vecUnLockMsg;
	vecUnLockMsg.clear();

	MessageType_t msgType = T_FC_CHAT_LETTER_READ;
	if(!struItem.bAllMail)
	{
		msgType = T_FC_CHAT_LETTER_READ;		
		vecUnLockMsg.push_back(T_FC_CHAT_LETTER_READ);		
		vecUnLockMsg.push_back(T_FC_CHAT_LETTER_READ_OK);				

		MSG_FC_CHAT_LETTER_READ sMsg;
		memset(&sMsg, 0x00, sizeof(sMsg));		
		sMsg.LetterUID = struItem.LetterUID;
		sMsg.CheckRead = struItem.bReadMail;				
		g_pFieldWinSocket->SendMsg(msgType, (char*)&sMsg, sizeof(sMsg));	

		
	}	
	else
	{
		msgType = T_FC_CHAT_ALLLETTER_READ;		
		vecUnLockMsg.push_back(T_FC_CHAT_ALLLETTER_READ);		
		vecUnLockMsg.push_back(T_FC_CHAT_ALLLETTER_READ_OK);				

		MSG_FC_CHAT_ALLLETTER_READ sMsg;
		memset(&sMsg, 0x00, sizeof(sMsg));		
		sMsg.LetterUID = struItem.LetterUID;
		sMsg.CheckRead = struItem.bReadMail;				
		g_pFieldWinSocket->SendMsg(msgType, (char*)&sMsg, sizeof(sMsg));	

	}
	// �ϳ��� ��Ī �Ǿ ���� Ǯ����. 
	g_pD3dApp->EnterMultiLock(TRUE, msgType, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);	
}


void CINFCommunityLetter::SetLetterInfo(BOOL bAllMail, UID64_t LetterUID, char* Content)
{
	structReadLetterItemInfo  struItem;
	memset(&struItem, 0x00, sizeof(structReadLetterItemInfo ));

	if(!GetLetterItemInfo(bAllMail, LetterUID, &struItem))
	{
		return;
	}	
	m_pEditReadReceiveUser->SetString(struItem.chSendUser, SIZE_MAX_ARENA_FULL_NAME);	// ���� ����	
	m_pEditReadTitle->SetString(struItem.chLetterTitle, SIZE_MAX_ARENA_FULL_NAME);		// ����
	
	
	if(Content)
	{
		// 2008-10-13 by bhsohn ���� �б� Return �ȵǴ� ���� ó��
		//int nLienCnt = m_pEditReadInfo->SetString(Content, 	SIZE_MAX_LETTER_CONTENT);
		int nLienCnt = m_pEditReadInfo->SetString(Content, 	SIZE_MAX_LETTER_CONTENT, TRUE);
		int nMaxStep = max(nLienCnt, LETTER_INFO_READ_MAX_SCROLL_LINE);			
		
		// �ִ� �������� �����ְ�
		m_pScrollReadInfo->SetMaxItem(nMaxStep);
	}	

	//Nexy 2024-12-27 : Decrement unread letter count if the mail wasn't read
	if(!struItem.bReadMail)
		m_nAdditionalUnreadLetters--;
}


BOOL CINFCommunityLetter::GetLetterItemInfo(BOOL bAllMail, UID64_t LetterUID, structReadLetterItemInfo* pItem)
{
	vector<structReadLetterItemInfo>::iterator it = m_vecReadLetter.begin();		
	while(it != m_vecReadLetter.end())
	{
		structReadLetterItemInfo stTmp = (*it);
		if((stTmp.bAllMail==bAllMail)
			&&(stTmp.LetterUID == LetterUID))
		{			
			(*pItem) = stTmp;
			return TRUE;
		}
		it++;
	}
	return FALSE;

}

void CINFCommunityLetter::OnClickLetterSend(BOOL bAllMail)
{

	if(!bAllMail)
	{		
		// ���� ������ Ŭ��
		MSG_FC_CHAT_LETTER_SEND sMsg; 
		memset(&sMsg, 0x00, sizeof(MSG_FC_CHAT_LETTER_SEND));
		
		sMsg.SendCharacterUID = g_pShuttleChild->GetShuttleInfo()->CharacterUniqueNumber;
		m_pEditWriteReceiveUser->GetString(sMsg.RecvCharacterName, SIZE_MAX_CHARACTER_NAME-1);		// �޴� ����
		m_pEditWriteTitle->GetString(sMsg.Title, SIZE_MAX_LETTER_TITLE-1);		// ����
		m_pEditWriteInfo->GetString(sMsg.Content, SIZE_MAX_LETTER_CONTENT-1);		// ����

		if(strlen(sMsg.Title) <= 0)
		{
			char buf[256];
			wsprintf(buf, STRMSG_C_080513_0201);//"\\y������ �Է��ϼ���."
			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_ERROR);
			return;
		}

		if(strlen(sMsg.RecvCharacterName) <= 0)
		{
			char buf[256];
			wsprintf(buf, STRMSG_C_080513_0202);//"\\y�޴� ����� �Է��ϼ���."
			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_ERROR);
			return;
		}
		if(strlen(sMsg.Content) <= 0)
		{
			char buf[256];
			wsprintf(buf, STRMSG_C_080513_0203);//"\\y���� ������ �Է��ϼ���."
			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_ERROR);
			return;
		}
		
		vector<MessageType_t> vecUnLockMsg;
		vecUnLockMsg.clear();
		vecUnLockMsg.push_back(T_FC_CHAT_LETTER_SEND);		
		vecUnLockMsg.push_back(T_FC_CHAT_LETTER_SEND_OK);		
		// �ϳ��� ��Ī �Ǿ ���� Ǯ����. 
		g_pD3dApp->EnterMultiLock(TRUE, T_FC_CHAT_LETTER_SEND, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);

		g_pFieldWinSocket->SendMsg(T_FC_CHAT_LETTER_SEND, (char*)&sMsg, sizeof(sMsg));	
	}
	else
	{		
		// ���� ������ Ŭ��
		MSG_FC_CHAT_ALLLETTER_SEND sMsg; 
		memset(&sMsg, 0x00, sizeof(MSG_FC_CHAT_ALLLETTER_SEND));
		
		sMsg.SendCharacterUID = g_pShuttleChild->GetShuttleInfo()->CharacterUniqueNumber;
		m_pEditWriteReceiveUser->GetString(sMsg.RecvCharacterName, SIZE_MAX_CHARACTER_NAME-1);		// �޴� ����
		m_pEditWriteTitle->GetString(sMsg.Title, SIZE_MAX_LETTER_TITLE-1);		// ����
		m_pEditWriteInfo->GetString(sMsg.Content, SIZE_MAX_LETTER_CONTENT-1);		// ����

		if(strlen(sMsg.Title) <= 0)
		{
			char buf[256];
			wsprintf(buf, STRMSG_C_080513_0201);//"\\y������ �Է��ϼ���."
			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_ERROR);
			return;
		}

//		if(strlen(sMsg.RecvCharacterName) <= 0)
//		{
//			char buf[256];
//			wsprintf(buf, STRMSG_C_080513_0202);//"\\y�޴� ����� �Է��ϼ���."
//			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_ERROR);
//			return;
//		}
		if(strlen(sMsg.Content) <= 0)
		{
			char buf[256];
			wsprintf(buf, STRMSG_C_080513_0203);//"\\y���� ������ �Է��ϼ���."
			g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_ERROR);
			return;
		}

		vector<MessageType_t> vecUnLockMsg;
		vecUnLockMsg.clear();
		vecUnLockMsg.push_back(T_FC_CHAT_ALLLETTER_SEND);		
		vecUnLockMsg.push_back(T_FC_CHAT_ALLLETTER_SEND_OK);		
		// �ϳ��� ��Ī �Ǿ ���� Ǯ����. 
		g_pD3dApp->EnterMultiLock(TRUE, T_FC_CHAT_ALLLETTER_SEND, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);
		
		g_pFieldWinSocket->SendMsg(T_FC_CHAT_ALLLETTER_SEND, (char*)&sMsg, sizeof(sMsg));	
	}
	char chBlank[16];
	memset(chBlank, 0x00, 16);
	
	m_pEditWriteReceiveUser->SetString(chBlank, 16);		// �޴� ����
	m_pEditWriteReceiveUser->BackupTxtString();

	m_pEditWriteTitle->SetString(chBlank, 16);		// ����
	m_pEditWriteTitle->BackupTxtString();

	m_pEditWriteInfo->SetString(chBlank, 16, 0, TRUE);		// ����
	m_pEditWriteInfo->BackupTxtString();
}

void CINFCommunityLetter::RefreshLetterInfo()
{
	const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
	BOOL bShowBtn = FALSE;
	// ������ �� �������� Ȥ�� �����ڴ� ��ư�� ���δ�.
	if(COMPARE_RACE(myShuttleInfo.Race, RACE_INFLUENCE_LEADER))
	{
		bShowBtn = TRUE;
	}
	else if(COMPARE_RACE(myShuttleInfo.Race, RACE_INFLUENCE_SUBLEADER_1))
	{
		bShowBtn = TRUE;
	}
	else if(COMPARE_RACE(myShuttleInfo.Race, RACE_INFLUENCE_SUBLEADER_2))
	{
		bShowBtn = TRUE;
	}
	else if (COMPARE_RACE(myShuttleInfo.Race, RACE_OPERATION | RACE_GAMEMASTER | RACE_MONITOR))
	{
		bShowBtn = TRUE;
	}
	// ��ü ������ ��ư ������ ���� �Ǵ�
	m_pAllSendBtn->ShowWindow(bShowBtn);
	
	ChangeLetterMode(LETTER_MODE_READ, LETTER_READ_MODE_LIST, NULL, FALSE,0);
}

void CINFCommunityLetter::CheckNotReadMail()
{
	if(!m_bLetterFirstRq)
	{
		// ó�� ��û�ϴ� ������ �ƴϴ�.
		return;
	}
	char chBuf[256];
	memset(chBuf, 0x00, 256);

	vector<structReadLetterItemInfo>::iterator it = m_vecReadLetter.begin();		
	while(it != m_vecReadLetter.end())
	{
		structReadLetterItemInfo stTmp = (*it);
		if(!stTmp.bReadMail)
		{
			wsprintf(chBuf, STRMSG_C_080513_0206, stTmp.chSendUser);
			g_pD3dApp->m_pChat->CreateChatChild(chBuf,COLOR_SYSTEM);
		}
		
		it++;
	}
}

void CINFCommunityLetter::FieldSocketChatLetterDelOk()
{
	ChangeLetterMode(LETTER_MODE_READ, LETTER_READ_MODE_LIST, NULL, FALSE,0);
}

void CINFCommunityLetter::UpdateBtnPos()
{
	// ��� 
	POINT ptBkPos = ((CINFCommunity*)m_pParent)->GetCommunityBkPos();
	
	int nCnt = 0;
	int nPosX, nPosY;
	nPosX = nPosY =0;
	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	if(m_pReadBtn)
	{		
		nPosX = ptBkPos.x + 380;
		nPosY = ptBkPos.y + 66;		
		m_pReadBtn->SetBtnPosition(nPosX, nPosY);	
	}
	if(m_pReadDelBtn)
	{		
		nPosX = ptBkPos.x + 429;
		nPosY = ptBkPos.y + 66;		
		m_pReadDelBtn->SetBtnPosition(nPosX, nPosY);	
	}	
	if(m_pAllSendBtn)
	{		
		nPosX = ptBkPos.x + 360;
		nPosY = ptBkPos.y + 335;		
		m_pAllSendBtn->SetBtnPosition(nPosX, nPosY);	
	}
	if(m_pSendBtn)
	{		
		nPosX = ptBkPos.x + 410;
		nPosY = ptBkPos.y + 335;		
		m_pSendBtn->SetBtnPosition(nPosX, nPosY);	
	}

	// �б� ����
	if(m_pReadResponseBtn)
	{		
		nPosX = ptBkPos.x + 350;
		nPosY = ptBkPos.y + 335;		
		m_pReadResponseBtn->SetBtnPosition(nPosX, nPosY);	
	}
	// �б� ����
	if(m_pReadListDelBtn)
	{		
		nPosX = ptBkPos.x + 399;
		nPosY = ptBkPos.y + 335;		
		m_pReadListDelBtn->SetBtnPosition(nPosX, nPosY);	
	}
	// �б� �ڷ�
	if(m_pReadBackBtn)
	{		
		nPosX = ptBkPos.x + 446;
		nPosY = ptBkPos.y + 335;		
		m_pReadBackBtn->SetBtnPosition(nPosX, nPosY);	
	}


	{
		// ��ũ��		
		
		RECT rcMouseWhell, rcMousePos;
		POINT ptScrollPos = ptBkPos;

		ptScrollPos.x += 468;
		ptScrollPos.y += 129;

		m_pScrollRead->SetPosition(ptScrollPos.x ,ptScrollPos.y,11,170);
		rcMouseWhell.left		= ptScrollPos.x - 468;
		rcMouseWhell.top		= ptScrollPos.y - 30;
		rcMouseWhell.right		= ptScrollPos.x + 30;
		rcMouseWhell.bottom		= ptScrollPos.y + 230;
		m_pScrollRead->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= ptScrollPos.x - 11;
		rcMousePos.top			= ptScrollPos.y ;
		rcMousePos.right		= rcMousePos.left + 32;
		rcMousePos.bottom		= rcMousePos.top + 200;
		m_pScrollRead->SetMouseBallRect(rcMousePos);
	}
	 
	/////////////////////////////// ���� �б�///////////////////////////////////////////
	if(m_pEditReadReceiveUser)
	{
		nPosX = ptBkPos.x + LETTER_USER_READ_EDIT_X;
		nPosY = ptBkPos.y + LETTER_USER_READ_EDIT_Y;		
		m_pEditReadReceiveUser->SetPos(nPosX, nPosY);
	}
	if(m_pEditReadTitle)
	{		
		nPosX = ptBkPos.x + LETTER_TITLE_READ_EDIT_X;
		nPosY = ptBkPos.y + LETTER_TITLE_READ_EDIT_Y;		
		m_pEditReadTitle->SetPos(nPosX, nPosY);
	}
	if(m_pEditReadInfo)
	{		
		nPosX = ptBkPos.x + LETTER_INFO_READ_EDIT_X;
		nPosY = ptBkPos.y + LETTER_INFO_READ_EDIT_Y;		
		m_pEditReadInfo->SetPos(nPosX, nPosY);
	}
	{		
		
		RECT rcMouseWhell, rcMousePos;
		POINT ptScrollPos = ptBkPos;

		ptScrollPos.x += 452;
		ptScrollPos.y += 128;

		m_pScrollReadInfo->SetPosition(ptScrollPos.x ,ptScrollPos.y,11,163);
		rcMouseWhell.left		= ptScrollPos.x - 468;
		rcMouseWhell.top		= ptScrollPos.y - 30;
		rcMouseWhell.right		= ptScrollPos.x + 30;
		rcMouseWhell.bottom		= ptScrollPos.y + 230;
		m_pScrollReadInfo->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= ptScrollPos.x - 11;
		rcMousePos.top			= ptScrollPos.y ;
		rcMousePos.right		= rcMousePos.left + 32;
		rcMousePos.bottom		= rcMousePos.top + 200;
		m_pScrollReadInfo->SetMouseBallRect(rcMousePos);
	}

	/////////////////////////////// ���� ����///////////////////////////////////////////
	if(m_pEditWriteSendUser)
	{		
		nPosX = ptBkPos.x + LETTER_SEND_USER_EDIT_X;
		nPosY = ptBkPos.y + LETTER_SEND_USER_EDIT_Y;		
		m_pEditWriteSendUser->SetPos(nPosX, nPosY);

		const auto& myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
		m_pEditWriteSendUser->SetString(myShuttleInfo.CharacterName, strlen(myShuttleInfo.CharacterName)+1);
	}

	if(m_pEditWriteReceiveUser)
	{		
		nPosX = ptBkPos.x + LETTER_USER_EDIT_X;
		nPosY = ptBkPos.y + LETTER_USER_EDIT_Y;		
		m_pEditWriteReceiveUser->SetPos(nPosX, nPosY);
	}
	if(m_pEditWriteTitle)
	{		
		nPosX = ptBkPos.x + LETTER_TITLE_EDIT_X;
		nPosY = ptBkPos.y + LETTER_TITLE_EDIT_Y;		
		m_pEditWriteTitle->SetPos(nPosX, nPosY);
	}
	if(m_pEditWriteInfo)
	{		
		nPosX = ptBkPos.x + LETTER_INFO_EDIT_X;
		nPosY = ptBkPos.y + LETTER_INFO_EDIT_Y;		
		m_pEditWriteInfo->SetPos(nPosX, nPosY);
	}
	{		
		RECT rcMouseWhell, rcMousePos;
		POINT ptScrollPos = ptBkPos;

		ptScrollPos.x += 455;
		ptScrollPos.y += 149;

		m_pScrollWrite->SetPosition(ptScrollPos.x ,ptScrollPos.y,11,157);
		rcMouseWhell.left		= ptScrollPos.x - 468;
		rcMouseWhell.top		= ptScrollPos.y - 30;
		rcMouseWhell.right		= ptScrollPos.x + 30;
		rcMouseWhell.bottom		= ptScrollPos.y + 230;
		m_pScrollWrite->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= ptScrollPos.x - 11;
		rcMousePos.top			= ptScrollPos.y ;
		rcMousePos.right		= rcMousePos.left + 32;
		rcMousePos.bottom		= rcMousePos.top + 200;
		m_pScrollWrite->SetMouseBallRect(rcMousePos);
	}
#else
	if(m_pReadBtn)
	{		
		nPosX = ptBkPos.x + 308;
		nPosY = ptBkPos.y + 97;		
		m_pReadBtn->SetBtnPosition(nPosX, nPosY);	
	}
	if(m_pReadDelBtn)
	{		
		nPosX = ptBkPos.x + 378;
		nPosY = ptBkPos.y + 97;		
		m_pReadDelBtn->SetBtnPosition(nPosX, nPosY);	
	}	
	if(m_pAllSendBtn)
	{		
		nPosX = ptBkPos.x + 282;
		nPosY = ptBkPos.y + 346;		
		m_pAllSendBtn->SetBtnPosition(nPosX, nPosY);	
	}
	if(m_pSendBtn)
	{		
		nPosX = ptBkPos.x + 381;
		nPosY = ptBkPos.y + 346;		
		m_pSendBtn->SetBtnPosition(nPosX, nPosY);	
	}

	// �б� ����
	if(m_pReadResponseBtn)
	{		
		nPosX = ptBkPos.x + 243;
		nPosY = ptBkPos.y + 88;		
		m_pReadResponseBtn->SetBtnPosition(nPosX, nPosY);	
	}
	// �б� ����
	if(m_pReadListDelBtn)
	{		
		nPosX = ptBkPos.x + 310;
		nPosY = ptBkPos.y + 88;		
		m_pReadListDelBtn->SetBtnPosition(nPosX, nPosY);	
	}
	// �б� �ڷ�
	if(m_pReadBackBtn)
	{		
		nPosX = ptBkPos.x + 377;
		nPosY = ptBkPos.y + 88;		
		m_pReadBackBtn->SetBtnPosition(nPosX, nPosY);	
	}


	{
		// ��ũ��		
		
		RECT rcMouseWhell, rcMousePos;
		POINT ptScrollPos = ptBkPos;

		ptScrollPos.x += 454;
		ptScrollPos.y += 152;

		m_pScrollRead->SetPosition(ptScrollPos.x ,ptScrollPos.y,11,170);
		rcMouseWhell.left		= ptScrollPos.x - 468;
		rcMouseWhell.top		= ptScrollPos.y - 30;
		rcMouseWhell.right		= ptScrollPos.x + 30;
		rcMouseWhell.bottom		= ptScrollPos.y + 230;
		m_pScrollRead->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= ptScrollPos.x - 11;
		rcMousePos.top			= ptScrollPos.y ;
		rcMousePos.right		= rcMousePos.left + 32;
		rcMousePos.bottom		= rcMousePos.top + 200;
		m_pScrollRead->SetMouseBallRect(rcMousePos);
	}
	
	/////////////////////////////// ���� �б�///////////////////////////////////////////
	if(m_pEditReadReceiveUser)
	{
		nPosX = ptBkPos.x + LETTER_USER_READ_EDIT_X;
		nPosY = ptBkPos.y + LETTER_USER_READ_EDIT_Y;		
		m_pEditReadReceiveUser->SetPos(nPosX, nPosY);
	}
	if(m_pEditReadTitle)
	{		
		nPosX = ptBkPos.x + LETTER_TITLE_READ_EDIT_X;
		nPosY = ptBkPos.y + LETTER_TITLE_READ_EDIT_Y;		
		m_pEditReadTitle->SetPos(nPosX, nPosY);
	}
	if(m_pEditReadInfo)
	{		
		nPosX = ptBkPos.x + LETTER_INFO_READ_EDIT_X;
		nPosY = ptBkPos.y + LETTER_INFO_READ_EDIT_Y;		
		m_pEditReadInfo->SetPos(nPosX, nPosY);
	}
	{		
		
		RECT rcMouseWhell, rcMousePos;
		POINT ptScrollPos = ptBkPos;

		ptScrollPos.x += 454;
		ptScrollPos.y += 164;

		m_pScrollReadInfo->SetPosition(ptScrollPos.x ,ptScrollPos.y,11,135);
		rcMouseWhell.left		= ptScrollPos.x - 468;
		rcMouseWhell.top		= ptScrollPos.y - 30;
		rcMouseWhell.right		= ptScrollPos.x + 30;
		rcMouseWhell.bottom		= ptScrollPos.y + 230;
		m_pScrollReadInfo->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= ptScrollPos.x - 11;
		rcMousePos.top			= ptScrollPos.y ;
		rcMousePos.right		= rcMousePos.left + 32;
		rcMousePos.bottom		= rcMousePos.top + 200;
		m_pScrollReadInfo->SetMouseBallRect(rcMousePos);
	}

	/////////////////////////////// ���� ����///////////////////////////////////////////
	if(m_pEditWriteSendUser)
	{		
		nPosX = ptBkPos.x + LETTER_SEND_USER_EDIT_X;
		nPosY = ptBkPos.y + LETTER_SEND_USER_EDIT_Y;		
		m_pEditWriteSendUser->SetPos(nPosX, nPosY);

		CHARACTER myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();		
		m_pEditWriteSendUser->SetString(myShuttleInfo.CharacterName, strlen(myShuttleInfo.CharacterName)+1);
	}

	if(m_pEditWriteReceiveUser)
	{		
		nPosX = ptBkPos.x + LETTER_USER_EDIT_X;
		nPosY = ptBkPos.y + LETTER_USER_EDIT_Y;		
		m_pEditWriteReceiveUser->SetPos(nPosX, nPosY);
	}
	if(m_pEditWriteTitle)
	{		
		nPosX = ptBkPos.x + LETTER_TITLE_EDIT_X;
		nPosY = ptBkPos.y + LETTER_TITLE_EDIT_Y;		
		m_pEditWriteTitle->SetPos(nPosX, nPosY);
	}
	if(m_pEditWriteInfo)
	{		
		nPosX = ptBkPos.x + LETTER_INFO_EDIT_X;
		nPosY = ptBkPos.y + LETTER_INFO_EDIT_Y;		
		m_pEditWriteInfo->SetPos(nPosX, nPosY);
	}
	{		
		RECT rcMouseWhell, rcMousePos;
		POINT ptScrollPos = ptBkPos;

		ptScrollPos.x += 454;
		ptScrollPos.y += 164;

		m_pScrollWrite->SetPosition(ptScrollPos.x ,ptScrollPos.y,11,135);
		rcMouseWhell.left		= ptScrollPos.x - 468;
		rcMouseWhell.top		= ptScrollPos.y - 30;
		rcMouseWhell.right		= ptScrollPos.x + 30;
		rcMouseWhell.bottom		= ptScrollPos.y + 230;
		m_pScrollWrite->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= ptScrollPos.x - 11;
		rcMousePos.top			= ptScrollPos.y ;
		rcMousePos.right		= rcMousePos.left + 32;
		rcMousePos.bottom		= rcMousePos.top + 200;
		m_pScrollWrite->SetMouseBallRect(rcMousePos);
	}
#endif
}

int CINFCommunityLetter::CountUnreadLetters()
{
	int count = 0;
	for (auto& letter : m_vecReadLetter)
	{
		if (!letter.bReadMail)
			count++;
	}
	m_nTotalUnreadLetters = count;
	m_nAdditionalUnreadLetters = 0;
	return count;
}

void CINFCommunityLetter::AddUnreadLetterCount()
{
	m_nAdditionalUnreadLetters++;
}

const int CINFCommunityLetter::GetUnreadLetterCount()
{
	return m_nTotalUnreadLetters + m_nAdditionalUnreadLetters;
}
