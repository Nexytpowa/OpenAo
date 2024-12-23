// INFCommunity.h: interface for the CINFCommunity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_INF_QOL_INFO)
#define _INF_QOL_INFO

#if _MSC_VER > 1000
#pragma once
#endif

#include "INFBase.h"

#define INFQOL_FONT_SIZE 8
#define INFQOL_WARNING_COLOR_START 180
#define INFQOL_MAX_NOTIFICATION_COUNT 99

class CAtumNode;
class CINFImage;
class CINFImageBtn;
class CINFImageEx;											


class CINFQOLinfo : public CINFBase
{
public:
	CINFQOLinfo(CINFGameMain* pParent, CINFCommunity* pCommunity);
	virtual ~CINFQOLinfo();

	// DX9 Resources management
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();

	void Render();
	virtual void Tick();

	//Util functions
	void SetupUnicodeFont();

	CD3DHanFont*	m_pFontMailInfo;
	ID3DXFont*		m_pFontCircle; // DX9 Font instead of D3DHanFont to allow unicode characters to be drawn

protected:
	CINFGameMain*	m_pParent;
	CINFCommunity*	m_pCommunity;

	BOOL			m_bRestored;

	int				m_iLastUnreadCount;
	DWORD			m_lastUpdate; // last time the unread mails count changed
	char			m_szMailInfo[12];
};


#endif