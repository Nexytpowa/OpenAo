// CINF_QOL_info.h: interface for the CINFQOLinfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_INF_QOL_INFO)
#define _INF_QOL_INFO

#if _MSC_VER > 1000
#pragma once
#endif

#include "INFBase.h"

constexpr int INFQOL_FONT_SIZE = 8;
constexpr int INFQOL_WARNING_COLOR_START = 180;
constexpr int INFQOL_MAX_NOTIFICATION_COUNT = 99;
constexpr int INFQOL_MAX_WARNING_GRADIENT = 220;

constexpr int INFQOL_NEW_MAIL_BLINK_DELAY = 5000; // time in ms
constexpr float INFQOL_BLINK_SPEED = 0.15f;



class CINFQOLinfo : public CINFBase
{
public:
	CINFQOLinfo(CINFGameMain* pParent);
	virtual ~CINFQOLinfo();

	// DX9 Resources management
	virtual HRESULT InitDeviceObjects() override;
	virtual HRESULT InvalidateDeviceObjects() override;
	virtual HRESULT RestoreDeviceObjects() override;

	void Render();
	virtual void Tick();

	//Util functions
	HRESULT SetupUnicodeFont();

protected:
	CD3DHanFont* m_pFontMailInfo;
	ID3DXFont* m_pFontCircle; // DX9 Font instead of D3DHanFont to allow unicode characters to be drawn

	CINFGameMain*	m_pParent;
	CINFCommunity*	m_pCommunity;

	int				m_iLastUnreadCount;
	DWORD			m_lastUpdate; // last time the unread mails count changed
	char			m_szMailInfo[12];
	char			m_iMailInfoSize; //szMailInfo string length

	//BOOL			m_bRestored;
};


#endif