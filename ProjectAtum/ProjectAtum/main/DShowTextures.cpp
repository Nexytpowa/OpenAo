//-----------------------------------------------------------------------------
// File: DShowTextures.cpp
//
// Desc: DirectShow sample code - adds support for DirectShow videos playing 
//       on a DirectX 9.0 texture surface. Turns the D3D texture tutorial into 
//       a recreation of the VideoTex sample from previous versions of DirectX.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

#include "Textures.h"
#include "DShowTextures.h"


//-----------------------------------------------------------------------------
// Global DirectShow pointers
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9      g_pTextureMoviePlayer;
D3DFORMAT               g_TextureFormat; // Texture format

TCHAR g_achCopy[]     = TEXT("Bitwise copy of the sample");
TCHAR g_achOffscr[]   = TEXT("Using offscreen surfaces and StretchCopy()");
TCHAR g_achDynTextr[] = TEXT("Using Dynamic Textures");
TCHAR* g_pachRenderMethod = NULL;





    

//-----------------------------------------------------------------------------
// CTextureRenderer constructor
//-----------------------------------------------------------------------------
CTextureRenderer::CTextureRenderer(LPUNKNOWN pUnk, HRESULT* phr) :
	CBaseVideoRenderer { __uuidof(CLSID_TextureRenderer), NAME("Texture Renderer"), pUnk, phr },
	m_bUseDynamicTextures { FALSE }, m_lVidWidth { 0 }, m_lVidHeight { 0 }, m_lVidPitch { 0 }
{
    // Store and AddRef the texture for our use.
    ASSERT(phr);
    if (phr) *phr = S_OK;
}





//-----------------------------------------------------------------------------
// CheckMediaType: This method forces the graph to give us an R8G8B8 video
// type, making our copy to texture memory trivial.
//-----------------------------------------------------------------------------
HRESULT CTextureRenderer::CheckMediaType(const CMediaType *pmt)
{
    HRESULT   hr = E_FAIL;
    VIDEOINFO *pvi=0;
    
    CheckPointer(pmt,E_POINTER);

    // Reject the connection if this is not a video type
    if( *pmt->FormatType() != FORMAT_VideoInfo ) {
        return E_INVALIDARG;
    }
    
    // Only accept RGB24 video
    pvi = (VIDEOINFO *)pmt->Format();

    if(IsEqualGUID( *pmt->Type(),    MEDIATYPE_Video)  &&
       IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_RGB24))
    {
        hr = S_OK;
    }
    
    return hr;
}

//-----------------------------------------------------------------------------
// SetMediaType: Graph connection has been made. 
//-----------------------------------------------------------------------------
HRESULT CTextureRenderer::SetMediaType(const CMediaType *pmt)
{
    HRESULT hr;

    UINT uintWidth = 2;
    UINT uintHeight = 2;

    // Retrive the size of this media type
    D3DCAPS9 caps;
    VIDEOINFO *pviBmp;                      // Bitmap info header
    pviBmp = (VIDEOINFO *)pmt->Format();

    m_lVidWidth  = pviBmp->bmiHeader.biWidth;
    m_lVidHeight = abs(pviBmp->bmiHeader.biHeight);
    m_lVidPitch  = (m_lVidWidth * 3 + 3) & ~(3); // We are forcing RGB24

    // here let's check if we can use dynamic textures
    ZeroMemory( &caps, sizeof(D3DCAPS9));
    hr = g_pD3dDev->GetDeviceCaps( &caps );
    if( caps.Caps2 & D3DCAPS2_DYNAMICTEXTURES )
    {
        m_bUseDynamicTextures = TRUE;
    }

    if( caps.TextureCaps & D3DPTEXTURECAPS_POW2 )
    {
        while( (LONG)uintWidth < m_lVidWidth )
        {
            uintWidth = uintWidth << 1;
        }
        while( (LONG)uintHeight < m_lVidHeight )
        {
            uintHeight = uintHeight << 1;
        }
        
    }
    else
    {
        uintWidth = m_lVidWidth;
        uintHeight = m_lVidHeight;
    }

    // Create the texture that maps to this media type
    hr = E_UNEXPECTED;
	g_pTextureMoviePlayer = NULL;
    if( m_bUseDynamicTextures )
    {
        hr = g_pD3dDev->CreateTexture(uintWidth, uintHeight, 1, D3DUSAGE_DYNAMIC, 
                                         D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,
                                         &g_pTextureMoviePlayer, NULL);
        g_pachRenderMethod = g_achDynTextr;
        if( FAILED(hr))
        {
            m_bUseDynamicTextures = FALSE;
        }
    }
    if( FALSE == m_bUseDynamicTextures )
    {
        hr = g_pD3dDev->CreateTexture(uintWidth, uintHeight, 1, 0, 
                                         D3DFMT_X8R8G8B8,D3DPOOL_MANAGED,
                                         &g_pTextureMoviePlayer, NULL);
        g_pachRenderMethod = g_achCopy;
    }
    if( FAILED(hr))
    {

        return hr;
    }

    // CreateTexture can silently change the parameters on us
    D3DSURFACE_DESC ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));

    if ( FAILED( hr = g_pTextureMoviePlayer->GetLevelDesc( 0, &ddsd ) ) ) {
        return hr;
    }


    CComPtr<IDirect3DSurface9> pSurf; 

    if (SUCCEEDED(hr = g_pTextureMoviePlayer->GetSurfaceLevel(0, &pSurf)))
        pSurf->GetDesc(&ddsd);

    // Save format info
    g_TextureFormat = ddsd.Format;

    if (g_TextureFormat != D3DFMT_X8R8G8B8 &&
        g_TextureFormat != D3DFMT_A1R5G5B5) 
	{
        return VFW_E_TYPE_NOT_ACCEPTED;
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// DoRenderSample: A sample has been delivered. Copy it to the texture.
//-----------------------------------------------------------------------------
HRESULT CTextureRenderer::DoRenderSample( IMediaSample * pSample )
{
    BYTE  *pBmpBuffer, *pTxtBuffer; // Bitmap buffer, texture buffer
    LONG  lTxtPitch;                // Pitch of bitmap, texture

    BYTE  * pbS = NULL;
    DWORD * pdwS = NULL;
    DWORD * pdwD = NULL;
    UINT row, col, dwordWidth;
    
    CheckPointer(pSample,E_POINTER);
    CheckPointer(g_pTextureMoviePlayer,E_UNEXPECTED);

    // Get the video bitmap buffer
    pSample->GetPointer( &pBmpBuffer );

    // Lock the Texture
    D3DLOCKED_RECT d3dlr;
    if( m_bUseDynamicTextures )
    {
        if( FAILED(g_pTextureMoviePlayer->LockRect(0, &d3dlr, 0, D3DLOCK_DISCARD)))
            return E_FAIL;
    }
    else
    {
        if (FAILED(g_pTextureMoviePlayer->LockRect(0, &d3dlr, 0, 0)))
            return E_FAIL;
    }
    // Get the texture buffer & pitch
    pTxtBuffer = static_cast<byte *>(d3dlr.pBits);
    lTxtPitch = d3dlr.Pitch;
    
    
    // Copy the bits    

    if (g_TextureFormat == D3DFMT_X8R8G8B8) 
    {
        // Instead of copying data bytewise, we use DWORD alignment here.
        // We also unroll loop by copying 4 pixels at once.
        //
        // original BYTE array is [b0][g0][r0][b1][g1][r1][b2][g2][r2][b3][g3][r3]
        //
        // aligned DWORD array is     [b1 r0 g0 b0][g2 b2 r1 g1][r3 g3 b3 r2]
        //
        // We want to transform it to [ff r0 g0 b0][ff r1 g1 b1][ff r2 g2 b2][ff r3 b3 g3]
        // below, bitwise operations do exactly this.

        dwordWidth = m_lVidWidth / 4; // aligned width of the row, in DWORDS
                                      // (pixel by 3 bytes over sizeof(DWORD))

        for( row = 0; row< (UINT)m_lVidHeight; row++)
        {
            pdwS = ( DWORD*)pBmpBuffer;
            pdwD = ( DWORD*)pTxtBuffer;

            for( col = 0; col < dwordWidth; col ++ )
            {
                pdwD[0] =  pdwS[0] | 0xFF000000;
                pdwD[1] = ((pdwS[1]<<8)  | 0xFF000000) | (pdwS[0]>>24);
                pdwD[2] = ((pdwS[2]<<16) | 0xFF000000) | (pdwS[1]>>16);
                pdwD[3] = 0xFF000000 | (pdwS[2]>>8);
                pdwD +=4;
                pdwS +=3;
            }

            // we might have remaining (misaligned) bytes here
            pbS = (BYTE*) pdwS;
            for( col = 0; col < (UINT)m_lVidWidth % 4; col++)
            {
                *pdwD = 0xFF000000     |
                        (pbS[2] << 16) |
                        (pbS[1] <<  8) |
                        (pbS[0]);
                pdwD++;
                pbS += 3;           
            }

            pBmpBuffer  += m_lVidPitch;
            pTxtBuffer += lTxtPitch;
        }// for rows
    }

    if (g_TextureFormat == D3DFMT_A1R5G5B5) 
    {
        for(int y = 0; y < m_lVidHeight; y++ ) 
        {
            BYTE *pBmpBufferOld = pBmpBuffer;
            BYTE *pTxtBufferOld = pTxtBuffer;   

            for (int x = 0; x < m_lVidWidth; x++) 
            {
                *(WORD *)pTxtBuffer = (WORD)
                    (0x8000 +
                    ((pBmpBuffer[2] & 0xF8) << 7) +
                    ((pBmpBuffer[1] & 0xF8) << 2) +
                    (pBmpBuffer[0] >> 3));

                pTxtBuffer += 2;
                pBmpBuffer += 3;
            }

            pBmpBuffer = pBmpBufferOld + m_lVidPitch;
            pTxtBuffer = pTxtBufferOld + lTxtPitch;
        }
    }

    // Unlock the Texture
    if (!g_pTextureMoviePlayer || FAILED(g_pTextureMoviePlayer->UnlockRect(0)))
	{
		return E_FAIL;
	}
    
    return S_OK;
}









