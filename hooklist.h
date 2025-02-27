HOOK_DEFINE(int, GetObjectW,  (__in HANDLE h, __in int c, __out_bcount_opt(c) LPVOID pv), (h, c, pv))
HOOK_DEFINE(int, GetObjectA,  (__in HANDLE h, __in int c, __out_bcount_opt(c) LPVOID pv), (h, c, pv))
HOOK_DEFINE(int, GetTextFaceAliasW, (HDC hdc, int nLen, LPWSTR lpAliasW), (hdc, nLen, lpAliasW))
HOOK_DEFINE(BOOL, DeleteObject, ( HGDIOBJ hObject),(hObject))
HOOK_DEFINE(int, GetTextFaceW, ( __in HDC hdc, __in int c, __out_ecount_part_opt(c, return)  LPWSTR lpName), (hdc, c, lpName))
HOOK_DEFINE(int, GetTextFaceA, ( __in HDC hdc, __in int c, __out_ecount_part_opt(c, return)  LPSTR lpName), (hdc, c, lpName))
// dc->window detection helper
HOOK_DEFINE(HDC, CreateCompatibleDC, (_In_opt_ HDC hdc), (hdc))
HOOK_DEFINE(BOOL, DeleteDC, (_In_ HDC hdc), (hdc))
/*
* BeginBufferedPaint calls CreateCompatibleDC internally
HOOK_DEFINE(HPAINTBUFFER, BeginBufferedPaint, (
			HDC hdcTarget,
			const RECT * prcTarget,
			BP_BUFFERFORMAT dwFormat,
			BP_PAINTPARAMS * pPaintParams,
			HDC * phdc
	), (hdcTarget, prcTarget, dwFormat, pPaintParams, phdc))
HOOK_DEFINE(HRESULT, EndBufferedPaint, (
			HPAINTBUFFER hBufferedPaint,
			BOOL fUpdateTarget
		), (hBufferedPaint, fUpdateTarget))
*/
HOOK_DEFINE(DWORD, GetGlyphOutlineW, (    __in HDC hdc, \
			__in UINT uChar, \
			__in UINT fuFormat, \
			__out LPGLYPHMETRICS lpgm, \
			__in DWORD cjBuffer, \
			__out_bcount_opt(cjBuffer) LPVOID pvBuffer, \
			__in CONST MAT2 *lpmat2 \
			), (hdc, uChar, fuFormat, lpgm, cjBuffer, pvBuffer, lpmat2))
HOOK_DEFINE(DWORD, GetGlyphOutlineA, (__in HDC hdc, \
			__in UINT uChar, \
			__in UINT fuFormat, \
			__out LPGLYPHMETRICS lpgm, \
			__in DWORD cjBuffer, \
			__out_bcount_opt(cjBuffer) LPVOID pvBuffer, \
			__in CONST MAT2 *lpmat2), \
			(hdc, uChar, fuFormat, lpgm, cjBuffer, pvBuffer, lpmat2))


// DrawTextA,W
// DrawTextExA,W
// TabbedTextOutA,W
// TextOutA,W
// ExtTextOutA
// は内部で ExtTextOutWを呼んでるから ExtTextOutW だけ実装すればOK。←XPの場合
// Windows 2000 でも動くようにその他のAPIもフックを掛けておく。

HOOK_MANUALLY(HFONT, CreateFontIndirectW, (CONST LOGFONTW *lplf), (lplf))
HOOK_MANUALLY(HFONT, CreateFontIndirectExW, (CONST ENUMLOGFONTEXDV *penumlfex), (penumlfex))

// HOOK_DEFINE(BOOL, GetCharWidthW, (HDC hdc, UINT iFirstChar, UINT iLastChar, LPINT lpBuffer))
// HOOK_DEFINE(BOOL, GetCharWidth32W, (HDC hdc, UINT iFirstChar, UINT iLastChar, LPINT lpBuffer))


HOOK_DEFINE(BOOL, TextOutA, (HDC hdc, int nXStart, int nYStart, LPCSTR  lpString, int cbString), (hdc, nXStart, nYStart, lpString, cbString))
HOOK_DEFINE(BOOL, TextOutW, (HDC hdc, int nXStart, int nYStart, LPCWSTR lpString, int cbString), (hdc, nXStart, nYStart, lpString, cbString))

HOOK_DEFINE(BOOL, ExtTextOutA, (HDC hdc, int nXStart, int nYStart, UINT fuOptions, CONST RECT *lprc, LPCSTR  lpString, UINT cbString, CONST INT *lpDx), 
	(hdc, nXStart, nYStart, fuOptions, lprc, lpString, cbString, lpDx))

HOOK_DEFINE(BOOL, ExtTextOutW, (HDC hdc, int nXStart, int nYStart, UINT fuOptions, CONST RECT *lprc, LPCWSTR lpString, UINT cbString, CONST INT *lpDx), 
	(hdc, nXStart, nYStart, fuOptions, lprc, lpString, cbString, lpDx))

HOOK_DEFINE(BOOL, RemoveFontResourceExW, (__in LPCWSTR name, __in DWORD fl, __reserved PVOID pdv), (name, fl, pdv))
//HOOK_DEFINE(BOOL, RemoveFontResourceW, (__in LPCWSTR lpFileName))
HOOK_DEFINE(HGDIOBJ, GetStockObject, (__in int i), (i))
HOOK_DEFINE(BOOL, BeginPath, (HDC hdc), (hdc))
HOOK_DEFINE(BOOL, EndPath, (HDC hdc), (hdc))
HOOK_DEFINE(BOOL, AbortPath, (HDC hdc), (hdc));
HOOK_DEFINE(DWORD, GetFontData, (_In_ HDC     hdc,
	_In_ DWORD   dwTable,
	_In_ DWORD   dwOffset,
	_Out_writes_bytes_to_opt_(cjBuffer, return) PVOID pvBuffer,
	_In_ DWORD   cjBuffer
	), (hdc, dwTable, dwOffset, pvBuffer, cjBuffer));

HOOK_MANUALLY(HRESULT, BitmapRenderTarget_DrawGlyphRun, (
	IDWriteBitmapRenderTarget* This,
	FLOAT baselineOriginX,
	FLOAT baselineOriginY,
	DWRITE_MEASURING_MODE measuringMode,
	DWRITE_GLYPH_RUN const* glyphRun,
	IDWriteRenderingParams* renderingParams,
	COLORREF textColor,
	RECT* blackBoxRect),
	(This, baselineOriginX, baselineOriginY, measuringMode, glyphRun, renderingParams, textColor, blackBoxRect))

/*
HOOK_MANUALLY(void, SetTextAntialiasMode, (
			   ID2D1RenderTarget* self,
			   D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode))

HOOK_MANUALLY(void, SetTextRenderingParams, (
			   ID2D1RenderTarget* self,
			   __in_opt IDWriteRenderingParams *textRenderingParams ))*/

HOOK_MANUALLY(HRESULT, DWriteCreateFactory,  (
			  __in DWRITE_FACTORY_TYPE factoryType,
			  __in REFIID iid,
			  __out IUnknown **factory), (factoryType, iid, factory))

HOOK_MANUALLY(HRESULT, D2D1CreateDevice, (
			  IDXGIDevice* dxgiDevice,
			  CONST D2D1_CREATION_PROPERTIES* creationProperties,
			  ID2D1Device** d2dDevice), (dxgiDevice, creationProperties, d2dDevice))

HOOK_MANUALLY(HRESULT, D2D1CreateDeviceContext, (
			  IDXGISurface* dxgiSurface,
			  CONST D2D1_CREATION_PROPERTIES* creationProperties,
			  ID2D1DeviceContext** d2dDeviceContext), (dxgiSurface, creationProperties, d2dDeviceContext))

HOOK_MANUALLY(HRESULT, D2D1CreateFactory, (
				D2D1_FACTORY_TYPE factoryType,
				REFIID riid,
				const D2D1_FACTORY_OPTIONS* pFactoryOptions,
				void** ppIFactory), (factoryType, riid, pFactoryOptions, ppIFactory))

HOOK_MANUALLY(HRESULT, GetGdiInterop, (
			  IDWriteFactory* This,
			  IDWriteGdiInterop** gdiInterop
			  ), (This, gdiInterop))

HOOK_MANUALLY(HRESULT, CreateGlyphRunAnalysis, (
			  IDWriteFactory* This,
			  DWRITE_GLYPH_RUN const* glyphRun,
			  FLOAT pixelsPerDip,
			  DWRITE_MATRIX const* transform,
			  DWRITE_RENDERING_MODE renderingMode,
			  DWRITE_MEASURING_MODE measuringMode,
			  FLOAT baselineOriginX,
			  FLOAT baselineOriginY,
			  IDWriteGlyphRunAnalysis** glyphRunAnalysis
			  ), (This, glyphRun, pixelsPerDip, transform, renderingMode, measuringMode, baselineOriginX, baselineOriginY, glyphRunAnalysis))
	
HOOK_MANUALLY(HRESULT, CreateGlyphRunAnalysis2, (
			  IDWriteFactory2* This,
			  DWRITE_GLYPH_RUN const* glyphRun,
			  DWRITE_MATRIX const* transform,
			  DWRITE_RENDERING_MODE renderingMode,
			  DWRITE_MEASURING_MODE measuringMode,
			  DWRITE_GRID_FIT_MODE gridFitMode,
			  DWRITE_TEXT_ANTIALIAS_MODE antialiasMode,
			  FLOAT baselineOriginX,
			  FLOAT baselineOriginY,
			  IDWriteGlyphRunAnalysis** glyphRunAnalysis
			  ), (This, glyphRun, transform, renderingMode, measuringMode, gridFitMode, antialiasMode, baselineOriginX, baselineOriginY, glyphRunAnalysis))

HOOK_MANUALLY(HRESULT, CreateGlyphRunAnalysis3, (
			  IDWriteFactory3* This,
			  DWRITE_GLYPH_RUN const* glyphRun,
			  DWRITE_MATRIX const* transform,
			  DWRITE_RENDERING_MODE1 renderingMode,
			  DWRITE_MEASURING_MODE measuringMode,
			  DWRITE_GRID_FIT_MODE gridFitMode,
			  DWRITE_TEXT_ANTIALIAS_MODE antialiasMode,
			  FLOAT baselineOriginX,
			  FLOAT baselineOriginY,
			  IDWriteGlyphRunAnalysis** glyphRunAnalysis
			  ), (This, glyphRun, transform, renderingMode, measuringMode, gridFitMode, antialiasMode, baselineOriginX, baselineOriginY, glyphRunAnalysis))

HOOK_MANUALLY(HRESULT, GetAlphaBlendParams, (
			  IDWriteGlyphRunAnalysis* This,
			  IDWriteRenderingParams* renderingParams,
			  FLOAT* blendGamma,
			  FLOAT* blendEnhancedContrast,
			  FLOAT* blendClearTypeLevel
			  ), (This, renderingParams, blendGamma, blendEnhancedContrast, blendClearTypeLevel))
			  
HOOK_MANUALLY(HRESULT, CreateDeviceContext, (
			  ID2D1Device* This,
			  D2D1_DEVICE_CONTEXT_OPTIONS options,
			  ID2D1DeviceContext** deviceContext
			  ), (This, options, deviceContext))

HOOK_MANUALLY(HRESULT, CreateDeviceContext2, (
			  ID2D1Device1* This,
			  D2D1_DEVICE_CONTEXT_OPTIONS options,
			  ID2D1DeviceContext1** deviceContext
			  ), (This, options, deviceContext))

HOOK_MANUALLY(HRESULT, CreateDeviceContext3, (
			  ID2D1Device2* This,
			  D2D1_DEVICE_CONTEXT_OPTIONS options,
			  ID2D1DeviceContext2** deviceContext
			  ), (This, options, deviceContext))

HOOK_MANUALLY(HRESULT, CreateDeviceContext4, (
			  ID2D1Device3* This,
			  D2D1_DEVICE_CONTEXT_OPTIONS options,
			  ID2D1DeviceContext3** deviceContext
			  ), (This, options, deviceContext))

HOOK_MANUALLY(HRESULT, CreateDeviceContext5, (
			  ID2D1Device4* This,
			  D2D1_DEVICE_CONTEXT_OPTIONS options,
			  ID2D1DeviceContext4** deviceContext
			  ), (This, options, deviceContext))

HOOK_MANUALLY(HRESULT, CreateDeviceContext6, (
			  ID2D1Device5* This,
			  D2D1_DEVICE_CONTEXT_OPTIONS options,
			  ID2D1DeviceContext5** deviceContext
			  ), (This, options, deviceContext))

HOOK_MANUALLY(HRESULT, CreateDeviceContext7, (
			  ID2D1Device6* This,
			  D2D1_DEVICE_CONTEXT_OPTIONS options,
			  ID2D1DeviceContext6** deviceContext
			  ), (This, options, deviceContext))

HOOK_MANUALLY(HRESULT, CreateTextFormat, (
			   IDWriteFactory* self,
			   __in_z WCHAR const* fontFamilyName,
			   __maybenull IDWriteFontCollection* fontCollection,
			   DWRITE_FONT_WEIGHT fontWeight,
			   DWRITE_FONT_STYLE fontStyle,
			   DWRITE_FONT_STRETCH fontStretch,
			   FLOAT fontSize,
			   __in_z WCHAR const* localeName,
			   __out IDWriteTextFormat** textFormat), 
				 (self, fontFamilyName, fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, textFormat))

HOOK_MANUALLY(HRESULT, CreateFontFace, (
			  IDWriteFont* self,
			  __out IDWriteFontFace** fontFace
			  ), (self, fontFace))

HOOK_MANUALLY(HRESULT, DWriteFontFaceReference_CreateFontFace, (
			  IDWriteFontFaceReference* self,
			  __out IDWriteFontFace3** fontFace
			  ), (self, fontFace))

HOOK_MANUALLY(HRESULT, DWriteFontFaceReference_CreateFontFaceWithSimulations, (
			  IDWriteFontFaceReference* self,
			  DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags,
			  __out IDWriteFontFace3** fontFace
			  ), (self, fontFaceSimulationFlags, fontFace))

HOOK_MANUALLY(HRESULT, CreateBitmapRenderTarget, (
			  IDWriteGdiInterop* This,
			  HDC hdc,
			  UINT32 width,
			  UINT32 height,
			  IDWriteBitmapRenderTarget** renderTarget
			  ), (This, hdc, width, height, renderTarget))

HOOK_MANUALLY(HRESULT, CreateCompatibleRenderTarget, (
			  ID2D1RenderTarget* This,
			  CONST D2D1_SIZE_F* desiredSize,
			  CONST D2D1_SIZE_U* desiredPixelSize,
			  CONST D2D1_PIXEL_FORMAT* desiredFormat,
			  D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options,
			  ID2D1BitmapRenderTarget** bitmapRenderTarget
			  ), (This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget))

HOOK_MANUALLY(void, D2D1RenderTarget_SetTextAntialiasMode, (
			  ID2D1RenderTarget* This,
			  D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode), (This, textAntialiasMode));

HOOK_MANUALLY(void, D2D1DeviceContext_SetTextAntialiasMode, (
			  ID2D1DeviceContext* This,
			  D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode), (This, textAntialiasMode));

HOOK_MANUALLY(void, D2D1RenderTarget_SetTextRenderingParams, (
				  ID2D1RenderTarget* This,
				  _In_opt_ IDWriteRenderingParams* textRenderingParams), (This, textRenderingParams));

HOOK_MANUALLY(void, D2D1DeviceContext_SetTextRenderingParams, (
				  ID2D1DeviceContext* This,
				  _In_opt_ IDWriteRenderingParams* textRenderingParams), (This, textRenderingParams));

			  /*
HOOK_MANUALLY(GpStatus, GdipDrawString, (
			  GpGraphics               *graphics,
			  GDIPCONST WCHAR          *string,
			  INT                       length,
			  GDIPCONST GpFont         *font,
			  GDIPCONST RectF          *layoutRect,
			  GDIPCONST GpStringFormat *stringFormat,
			  GDIPCONST GpBrush        *brush
			  ))*/

HOOK_MANUALLY(HRESULT, CreateWicBitmapRenderTarget, (
	ID2D1Factory* This,
	IWICBitmap* target,
	const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties,
	ID2D1RenderTarget** renderTarget), (This, target, renderTargetProperties, renderTarget));

HOOK_MANUALLY(HRESULT, CreateHwndRenderTarget, (
	ID2D1Factory* This,
	const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties,
	const D2D1_HWND_RENDER_TARGET_PROPERTIES* hwndRenderTargetProperties,
	ID2D1HwndRenderTarget** hwndRenderTarget), (This, renderTargetProperties, hwndRenderTargetProperties, hwndRenderTarget));

HOOK_MANUALLY(HRESULT, CreateDxgiSurfaceRenderTarget, (
	ID2D1Factory* This,
	IDXGISurface* dxgiSurface,
	const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties,
	ID2D1RenderTarget** renderTarget), (This, dxgiSurface, renderTargetProperties, renderTarget));

HOOK_MANUALLY(HRESULT, CreateDCRenderTarget, (
	ID2D1Factory* This,
	const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties,
	ID2D1DCRenderTarget** dcRenderTarget), (This, renderTargetProperties, dcRenderTarget));

HOOK_MANUALLY(HRESULT, CreateDevice1, (
	ID2D1Factory1* This,
	IDXGIDevice* dxgiDevice,
	ID2D1Device** d2dDevice), (This, dxgiDevice, d2dDevice));

HOOK_MANUALLY(HRESULT, CreateDevice2, (
	ID2D1Factory2* This,
	IDXGIDevice* dxgiDevice,
	ID2D1Device1** d2dDevice1
	), (This, dxgiDevice, d2dDevice1));

HOOK_MANUALLY(HRESULT, CreateDevice3, (
	ID2D1Factory3* This,
	IDXGIDevice* dxgiDevice,
	ID2D1Device2** d2dDevice2
	), (This, dxgiDevice, d2dDevice2));

HOOK_MANUALLY(HRESULT, CreateDevice4, (
	ID2D1Factory4* This,
	IDXGIDevice* dxgiDevice,
	ID2D1Device3** d2dDevice3
	), (This, dxgiDevice, d2dDevice3));

HOOK_MANUALLY(HRESULT, CreateDevice5, (
	ID2D1Factory5* This,
	IDXGIDevice* dxgiDevice,
	ID2D1Device4** d2dDevice4
	), (This, dxgiDevice, d2dDevice4));

HOOK_MANUALLY(HRESULT, CreateDevice6, (
	ID2D1Factory6* This,
	IDXGIDevice* dxgiDevice,
	ID2D1Device5** d2dDevice5
	), (This, dxgiDevice, d2dDevice5));

HOOK_MANUALLY(HRESULT, CreateDevice7, (
	ID2D1Factory7* This,
	IDXGIDevice* dxgiDevice,
	ID2D1Device6** d2dDevice6
	), (This, dxgiDevice, d2dDevice6));

HOOK_MANUALLY(BOOL, MySetProcessMitigationPolicy, (
	_In_ PROCESS_MITIGATION_POLICY MitigationPolicy,
	_In_ PVOID                     lpBuffer,
	_In_ SIZE_T                    dwLength
	), (MitigationPolicy, lpBuffer, dwLength));

HOOK_MANUALLY(void, D2D1RenderTarget_DrawGlyphRun1, (
	ID2D1DeviceContext *This,
	D2D1_POINT_2F baselineOrigin,
	CONST DWRITE_GLYPH_RUN *glyphRun,
	CONST DWRITE_GLYPH_RUN_DESCRIPTION *glyphRunDescription,
	ID2D1Brush *foregroundBrush,
	DWRITE_MEASURING_MODE measuringMode), (This, baselineOrigin, glyphRun, glyphRunDescription, foregroundBrush, measuringMode));

HOOK_MANUALLY(void, D2D1RenderTarget1_DrawGlyphRun1, (
	ID2D1DeviceContext *This,
	D2D1_POINT_2F baselineOrigin,
	CONST DWRITE_GLYPH_RUN *glyphRun,
	CONST DWRITE_GLYPH_RUN_DESCRIPTION *glyphRunDescription,
	ID2D1Brush *foregroundBrush,
	DWRITE_MEASURING_MODE measuringMode), (This, baselineOrigin, glyphRun, glyphRunDescription, foregroundBrush, measuringMode));

HOOK_MANUALLY(void, D2D1DeviceContext_DrawGlyphRun1, (
	ID2D1DeviceContext *This,
	D2D1_POINT_2F baselineOrigin,
	CONST DWRITE_GLYPH_RUN *glyphRun,
	CONST DWRITE_GLYPH_RUN_DESCRIPTION *glyphRunDescription,
	ID2D1Brush *foregroundBrush,
	DWRITE_MEASURING_MODE measuringMode), (This, baselineOrigin, glyphRun, glyphRunDescription, foregroundBrush, measuringMode));

HOOK_MANUALLY(void, D2D1RenderTarget_DrawGlyphRun, (
	ID2D1RenderTarget* This,
	D2D1_POINT_2F baselineOrigin,
	CONST DWRITE_GLYPH_RUN *glyphRun,
	ID2D1Brush *foregroundBrush,
	DWRITE_MEASURING_MODE measuringMode
	), (This, baselineOrigin, glyphRun, foregroundBrush, measuringMode));

HOOK_MANUALLY(void, D2D1RenderTarget1_DrawGlyphRun, (
	ID2D1RenderTarget* This,
	D2D1_POINT_2F baselineOrigin,
	CONST DWRITE_GLYPH_RUN *glyphRun,
	ID2D1Brush *foregroundBrush,
	DWRITE_MEASURING_MODE measuringMode
	), (This, baselineOrigin, glyphRun, foregroundBrush, measuringMode));

HOOK_MANUALLY(void, D2D1DeviceContext_DrawGlyphRun, (
	ID2D1DeviceContext* This,
	D2D1_POINT_2F baselineOrigin,
	CONST DWRITE_GLYPH_RUN *glyphRun,
	ID2D1Brush *foregroundBrush,
	DWRITE_MEASURING_MODE measuringMode
	), (This, baselineOrigin, glyphRun, foregroundBrush, measuringMode));

HOOK_MANUALLY(void, D2D1RenderTarget_DrawText, (
	ID2D1RenderTarget* This,
	CONST WCHAR *string,
	UINT32 stringLength,
	IDWriteTextFormat *textFormat,
	CONST D2D1_RECT_F *layoutRect,
	ID2D1Brush *defaultForegroundBrush,
	D2D1_DRAW_TEXT_OPTIONS options,
	DWRITE_MEASURING_MODE measuringMode), 
	(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode));

HOOK_MANUALLY(void, D2D1DeviceContext_DrawText, (
	ID2D1DeviceContext* This,
	CONST WCHAR *string,
	UINT32 stringLength,
	IDWriteTextFormat *textFormat,
	CONST D2D1_RECT_F *layoutRect,
	ID2D1Brush *defaultForegroundBrush,
	D2D1_DRAW_TEXT_OPTIONS options,
	DWRITE_MEASURING_MODE measuringMode),
	(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode));

HOOK_MANUALLY(void, D2D1RenderTarget_DrawTextLayout, (
	ID2D1RenderTarget* This,
	D2D1_POINT_2F origin,
	IDWriteTextLayout *textLayout,
	ID2D1Brush *defaultForegroundBrush,
	D2D1_DRAW_TEXT_OPTIONS options
	),
	(This, origin, textLayout, defaultForegroundBrush, options));


//EOF
