#include "stdafx.h"
#include "INFGameMain.h"
#include "INF_QOL_info.h"
#include "INFCommunity.h"
#include "INFCommunityLetter.h"
#include "D3DHanFont.h"
#include "AtumApplication.h"
#include "dxutil.h"


CINFQOLinfo::CINFQOLinfo(CINFGameMain* pParent) : 
	m_pParent{ pParent }
{	
	m_pFontCircle = 0;
	m_pFontMailInfo = 0;

	m_iLastUnreadCount = 0;
	m_lastUpdate = 0.f;
	m_iMailInfoSize = 0;
	memset(m_szMailInfo, 0, sizeof(m_szMailInfo));

	if (g_pGameMain && g_pGameMain->m_pCommunity)
		m_pCommunity = g_pGameMain->m_pCommunity;
}

CINFQOLinfo::~CINFQOLinfo()
{
	util::del(m_pFontMailInfo);
	util::del(m_pFontCircle);
}

HRESULT CINFQOLinfo::SetupUnicodeFont()
{
	D3DXFONT_DESC fontDesc = {
		45,                        // Height
		0,                         // Width
		400,                       // Weight (boldness)
		0,                         // MipLevels
		false,                     // Italic
		DEFAULT_CHARSET,           // Charset
		OUT_TT_PRECIS,             // Output precision
		CLIP_DEFAULT_PRECIS,       // Clipping precision
		DEFAULT_PITCH | FF_DONTCARE, // Pitch and family
		"Arial"                   // Font face name
	};
	return D3DXCreateFontIndirect(g_pD3dDev, &fontDesc, &m_pFontCircle);
}

HRESULT CINFQOLinfo::InitDeviceObjects()
{
	m_pFontMailInfo = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), INFQOL_FONT_SIZE, D3DFONT_ZENABLE | D3DFONT_BOLD, TRUE, 256, 32);
	m_pFontMailInfo->InitDeviceObjects(g_pD3dDev);

	if ( FAILED(SetupUnicodeFont()) )
		m_pFontCircle = nullptr;

	return S_OK;
}

HRESULT CINFQOLinfo::InvalidateDeviceObjects()
{
	if (m_pFontMailInfo)
		m_pFontMailInfo->InvalidateDeviceObjects();
	if (m_pFontCircle)
		m_pFontCircle->OnLostDevice();

	return S_OK;
}

HRESULT CINFQOLinfo::RestoreDeviceObjects()
{
	if(m_pFontMailInfo)
		m_pFontMailInfo->RestoreDeviceObjects();
	if (m_pFontCircle)
		m_pFontCircle->OnResetDevice();

	return S_OK;
}

void CINFQOLinfo::Render()
{
	CINFImageBtn* hudCommButton = m_pParent->m_pImgButton[GAMEMAIN_BUTTON_COMMUNITY];
	if (!hudCommButton)
		return;

	POINT pos = hudCommButton->GetBtnPosition();
	POINT size = hudCommButton->GetImgSize();
	 
	if (m_pFontMailInfo && m_pFontCircle && m_iLastUnreadCount > 0)
	{
		RECT circleDrawPos = { pos.x + size.x/2 - 10, pos.y + size.y/2, 
								pos.x + size.x/2 + 15, pos.y + size.y/2 + 25 };

		//Draw background circle
		m_pFontCircle->DrawTextW(
			nullptr,
			L"●",
			-1,
			&circleDrawPos,
			DT_RIGHT | DT_BOTTOM,
			D3DCOLOR_ARGB(255, 225, 25, 25) // Red color
		);
		//


		//Draw mail count
		float colorMultiplier = 1.f;
		if (m_iLastUnreadCount > INFQOL_MAX_NOTIFICATION_COUNT || timeGetTime() - m_lastUpdate < INFQOL_NEW_MAIL_BLINK_DELAY) // Nexy 2024-12-27 : fixed the 5s delay that was actually 5ms previously
			colorMultiplier = cosf(D3DXToRadian(timeGetTime() * INFQOL_BLINK_SPEED));

		int warningGradient = (int)(INFQOL_MAX_WARNING_GRADIENT * colorMultiplier) % 256;
		

		m_pFontMailInfo->DrawText(pos.x + size.x - INFQOL_FONT_SIZE * (m_iMailInfoSize > 1 ? m_iMailInfoSize+2 : 3.5), //Nexy 2024-12-27 : Keeping single digits centered
			pos.y + INFQOL_FONT_SIZE*3,
			RGB(warningGradient, warningGradient, INFQOL_MAX_WARNING_GRADIENT),
			m_szMailInfo, 0L);
		//
	}
}

//2024/12/23 - Nexy - Updating unread letter count string only on change
void CINFQOLinfo::Tick()
{
	if (m_pCommunity && m_pCommunity->GetLetter())
	{
		int unreadCount = m_pCommunity->GetLetter()->GetUnreadLetterCount();
		if (unreadCount != m_iLastUnreadCount)
		{
			if (m_iLastUnreadCount > INFQOL_MAX_NOTIFICATION_COUNT)
				sprintf_s(m_szMailInfo, "+99");
			else
				sprintf_s(m_szMailInfo, "%d", unreadCount);

			m_iMailInfoSize = strlen(m_szMailInfo); //Caching string size
			m_lastUpdate = timeGetTime();
			m_iLastUnreadCount = unreadCount;
		}
	}

	//todo: Add QOL for gear info button (bonus stats)
}