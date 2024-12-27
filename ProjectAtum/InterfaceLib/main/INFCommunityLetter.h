// INFCommunityLetter.h: interface for the CINFCommunityLetter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCOMMUNITYLETTER_H__DFF38A04_9D63_44D9_B403_CF87C3A3D868__INCLUDED_)
#define AFX_INFCOMMUNITYLETTER_H__DFF38A04_9D63_44D9_B403_CF87C3A3D868__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

class CINFImage;
class CINFImageBtn;
class CINFArenaScrollBar;
class CINFEditBox;
class CINFCurselEditBox;
class CINFGroupImage;

// ���� ���
#define		LETTER_MODE_READ		0	// ���� �б�
#define		LETTER_MODE_WRITE		1	// ���� ����
#define		MAX_LETTER_MODE			2

// ���� �б�
#define		LETTER_READ_MODE_LIST	0	// ���� ����Ʈ
#define		LETTER_READ_MODE_INFO	1	// ���� ����

// ���� �о����� ����
#define		LETTER_READ_NORES		0	// ���� ���� ����
#define		LETTER_READ_RES			1	// ���� ����
#define		MAX_LETTER_READ			2



class CINFCommunityLetter  : public CINFBase  
{
public:
	CINFCommunityLetter(CAtumNode* pParent);
	virtual ~CINFCommunityLetter();	

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual void Tick();
	void Render(POINT ptPos);
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);


	int WndProcLetterRead(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int WndProcLetterWrite(UINT uMsg, WPARAM wParam, LPARAM lParam);

	// ���� �б� ����
	void AddReadLetter(BOOL bAllMail, BOOL bReadMail, UID64_t   LetterUID, char* pSendUser, char* pLetterTitle, ATUM_DATE_TIME	atimeMail);
	void RqDelReadLetter(BOOL bAllMail, UID64_t   LetterUID);
	void DelReadLetter();
	void SetLetterInfo(BOOL bAllMail, UID64_t LetterUID, char* Content); // ���� ����	
	void RefreshLetterInfo();
	void RqLetterTitle(BOOL bLetterFirstRq);								// ���� ����Ʈ��û
	void RqAllLetterTitle();		// ��ü ���� ��û 

	void CheckNotReadMail();		// �������� ���� üũ
	void FieldSocketChatLetterDelOk();

	void ChangeLetterMode(int nLetterMode, int nSubLetterMode, char* pUser, 
											BOOL bAllMail, UID64_t uReadLetterUID);

	void UpdateBtnPos();

	int CountUnreadLetters();
	void AddUnreadLetterCount();
	const int GetUnreadLetterCount();

private:
	// 
	int OnLButtonDown(POINT pt);

	void InitLetterMode();

	// ���� �б�
	void RenderLetterRead(POINT ptBkPos);	
	int OnLButtonDown_ReadList(POINT pt);
	int OnLButtonDown_ReadInfo(POINT pt);
	int OnLButtonUp_Read(POINT pt);
	void RenderReadLetter(POINT ptBkPos);
	int GetReadLetterCurselPos(POINT pt);
	void OnClickReadLetter(int nSelReadLetterPos);		// ������ Ŭ��	
	void TestReadDb();
	
	void RqLetterRead(BOOL bAllMail, UID64_t uReadLetterUID);								// ���� ���� ��û	
	BOOL GetLetterItemInfo(BOOL bAllMail, UID64_t LetterUID, structReadLetterItemInfo* pItem);	// ���� ���� ����

	// ���� ����
	void OnClickLetterSend(BOOL bAllMail);
	void RenderLetterWrite(POINT ptBkPos);
	void OnClickWriteEditBox(int nSelLetterWrite, CINFEditBox*	pSelEdit);	


private:
#ifdef C_EPSODE4_UI_CHANGE_JSKIM					        // 2011. 10. 10 by jskim UI�ý��� ����
	CINFGroupImage*	 m_pBack;		// ���														  
#else 
	CINFImageEx*	m_pBack;		// ���
#endif
	
	// �б�/����
	int				m_nLetterMode;
	CINFImageEx*	m_pLetterMode[MAX_LETTER_MODE];		
	
	// ����
	int						m_nSelReadLetterPos;
	CINFImageEx*			m_pImgSelect;

	// �б� ���� ��ư
	int				m_nReadLetterMode;
	CINFImageBtn*				m_pReadBtn;			// �б�
	CINFImageBtn*				m_pReadDelBtn;		// ����	
	CINFArenaScrollBar*			m_pScrollRead;			// ��ũ��
	vector<structReadLetterItemInfo>		m_vecReadLetter;
	CINFImageEx*				m_pLetterRead[MAX_LETTER_READ];
	
	CINFImageEx*				m_pLetterReadListBk;		
	CINFImageEx*				m_pLetterReadBk;

	// �б�
	UID64_t						m_uReadLetterUID;
	BOOL						m_bAllMail;					// ��ü���Ͽ���

	CINFEditBox*				m_pEditReadReceiveUser;		// �޴� ����
	CINFEditBox*				m_pEditReadTitle;			// ����
	CINFEditBox*				m_pEditReadInfo;			// ����
	CINFArenaScrollBar*			m_pScrollReadInfo;			// ��ũ�� 

	CINFImageBtn*				m_pReadResponseBtn;			// �б� ����
	CINFImageBtn*				m_pReadListDelBtn;				// �б� ����
	CINFImageBtn*				m_pReadBackBtn;				// �б� �ڷ�

	// ���� ���� ��Ʈ
	CINFImageBtn*				m_pSendBtn;			// ������
	CINFImageBtn*				m_pAllSendBtn;		// ��ü �߼�

	// ����
	CINFEditBox*				m_pEditWriteSendUser;		// ������ ����
	CINFEditBox*				m_pEditWriteReceiveUser;		// �޴� ����
	CINFEditBox*				m_pEditWriteTitle;			// ����
	// 2008-06-24 by bhsohn �������� ����Ű �԰� ����
	CINFCurselEditBox*				m_pEditWriteInfo;			// ����
	CINFArenaScrollBar*			m_pScrollWrite;			// ��ũ�� 

	int							m_nSelLetterWrite;
	

	// ���� ��Ʈ 
	CD3DHanFont*				m_pFontLetter;

	BOOL						m_bLetterFirstRq;			// ó�� ��û�� �����̳�?

	int							m_nTotalUnreadLetters;
	int							m_nAdditionalUnreadLetters; //2024/12/23 - Nexy : Added a counter for newly received mails
};

#endif // !defined(AFX_INFCOMMUNITYLETTER_H__DFF38A04_9D63_44D9_B403_CF87C3A3D868__INCLUDED_)
