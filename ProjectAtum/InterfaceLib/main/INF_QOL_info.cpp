#include "stdafx.h"
#include "INFGameMain.h"
#include "INF_QOL_info.h"
#include "INFCommunity.h"
#include "INFCommunityLetter.h"
#include "D3DHanFont.h"
#include "AtumApplication.h"
#include "dxutil.h"


CINFQOLinfo::CINFQOLinfo(CINFGameMain* pParent, CINFCommunity* pCommunity)
{
	m_pParent = pParent;
	m_pCommunity = pCommunity;

	m_bRestored = FALSE;

	m_iLastUnreadCount = 0;
	m_pFontMailInfo = 0;
	m_lastUpdate = 0.f;
	memset(m_szMailInfo, 0, sizeof(m_szMailInfo));

	CINFImage* test;
	//test->
}

CINFQOLinfo::~CINFQOLinfo()
{
	util::del(m_pFontMailInfo);
}

void CINFQOLinfo::SetupUnicodeFont()
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
	D3DXCreateFontIndirect(g_pD3dDev, &fontDesc, &m_pFontCircle);
}

HRESULT CINFQOLinfo::InitDeviceObjects()
{
	m_pFontMailInfo = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), INFQOL_FONT_SIZE, D3DFONT_ZENABLE | D3DFONT_BOLD, TRUE, 256, 32);
	m_pFontMailInfo->InitDeviceObjects(g_pD3dDev);

	SetupUnicodeFont();

	return S_OK;
}

HRESULT CINFQOLinfo::InvalidateDeviceObjects()
{
	if (!m_bRestored)
		return S_OK;

	m_pFontMailInfo->InvalidateDeviceObjects();
	if (m_pFontCircle)
		m_pFontCircle->OnLostDevice();

	m_bRestored = FALSE;
	return S_OK;
}

HRESULT CINFQOLinfo::RestoreDeviceObjects()
{
	if (m_bRestored)
		return S_OK;

	m_pFontMailInfo->RestoreDeviceObjects();
	if (m_pFontCircle)
		m_pFontCircle->OnResetDevice();

	m_bRestored = TRUE;
	return S_OK;
}

void CINFQOLinfo::Render()
{
	CINFImageBtn* HUDCommButton = m_pParent->m_pImgButton[GAMEMAIN_BUTTON_COMMUNITY];
	if (!HUDCommButton)
		return;

	POINT pos = HUDCommButton->GetBtnPosition();
	POINT size = HUDCommButton->GetImgSize();
	 
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
		if (m_iLastUnreadCount > INFQOL_MAX_NOTIFICATION_COUNT || timeGetTime() - m_lastUpdate < 5)
			colorMultiplier = cos(D3DXToRadian(timeGetTime() * 0.15));

		char warningGradient = 220 * colorMultiplier;

		m_pFontMailInfo->DrawText(pos.x + size.x - INFQOL_FONT_SIZE*(strlen(m_szMailInfo)+2),
			pos.y + INFQOL_FONT_SIZE*3,
			RGB(warningGradient, warningGradient, 220),
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
			m_iLastUnreadCount = unreadCount;
			if (m_iLastUnreadCount > INFQOL_MAX_NOTIFICATION_COUNT)
				sprintf_s(m_szMailInfo, "+99");
			else
				sprintf_s(m_szMailInfo, "%d", unreadCount);

			m_lastUpdate = timeGetTime();
		}
	}

	//todo: Add QOL for gear info button (bonus stats)
}