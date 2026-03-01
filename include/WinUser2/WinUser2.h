#pragma once
#include <windows.h>

#define WM_FULLSCREEN           0x003A
#define WM_CLIENTSHUTDOWN       0x003B
#define WM_DDEMLEVENT           0x003C
#define WM_CALCSCROLL           0x003F
#define WM_UAHDESTROYWINDOW     0x0090	// handled by DefWindowProc
#define WM_UAHDRAWMENU          0x0091	// lParam is UAHMENU
#define WM_UAHDRAWMENUITEM      0x0092	// lParam is UAHDRAWMENUITEM
#define WM_UAHINITMENU          0x0093	// handled by DefWindowProc
#define WM_UAHMEASUREMENUITEM   0x0094	// lParam is UAHMEASUREMENUITEM
#define WM_UAHNCPAINTMENUPOPUP  0x0095	// handled by DefWindowProc
#define WM_UAHUPDATE            0x0096
#define WM_NCUAHDRAWCAPTION     0x00AE
#define WM_NCUAHDRAWFRAME       0x00AF
#define EM_MSGMAX               0x00DA
#define WM_SYSTIMER             0x0118
#define WM_GETISHELLBROWSER     (WM_USER+7)
#define WM_SYSMENU              (0x0313)
#define WM_TASKBARBUTTONCREATED (0xC22E)
#define WM_MSIMEQUERYPOSITION   (0xC05C)
#define WHERE_NOONE_CAN_SEE_ME ((int) -32000)

typedef enum tagNCHIT {
  NCHIT_CLIENT = 0x0000,
  NCHIT_LEFT = 0x0001,
  NCHIT_RIGHT = 0x0002,
  NCHIT_TOP = 0x0004,
  NCHIT_BOTTOM = 0x0008,
} NCHIT, * LPNCHIT;

typedef enum tagMOUSEAREA
{
  MA_NONE,
  MA_CLIENT,
  MA_NONCLIENT,
} MOUSEAREA, * LPMOUSEAREA;

typedef enum tagCAPTIONBUTTON {
  CB_NONE,
  CB_CAPTION,
  CB_ICONBUTTON,
  CB_LIGHTDARKBUTTON,
  CB_FEEDBACKBUTTON,
  CB_MINBUTTON,
  CB_MAXBUTTON,
  CB_CLOSEBUTTON
} CAPTIONBUTTON, * LPCAPTIONBUTTON;

BOOL SetWindowOwner(HWND hWnd, HWND hWndOwner);
BOOL SetProcessEcoQoS(DWORD dwProcessId);
BOOL SetThreadEcoQoS(DWORD dwThreadId);
BOOL InMenu(void);
HMENU LoadPopupMenu(HINSTANCE hInstance, LPCTSTR lpMenuName);
void ForceTimerMessagesToBeCreatedIfNecessary(LPMSG lpMsg);
BOOL PumpMessageQueue(HWND hwndPump);

EXTERN_C
BOOL FORCEINLINE
InitAllCommonControls(
    VOID
    );

EXTERN_C
BOOL FORCEINLINE
MyStrEquals(
    LPCTSTR lpszLeft,
    LPCTSTR lpszRight
    );

EXTERN_C
BOOL FORCEINLINE
IsWindowMaximized(
    HWND hwnd
    );

EXTERN_C
BOOL FORCEINLINE
GetCaptionRect(
    HWND   hWnd,
    LPRECT lprcCaption
    );

EXTERN_C
BOOL FORCEINLINE 
GetWindowBorders(
    HWND hwnd,
    LPSIZE lpsz
    );

EXTERN_C
LPCTSTR FORCEINLINE
DecipherMessage(
    UINT uMsg
    );

EXTERN_C
LPCTSTR FORCEINLINE
DecipherSysCommand(
    UINT cmd
    );

EXTERN_C BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam);

EXTERN_C
HWND FORCEINLINE APIPRIVATE
GetRealParent(
    HWND hWnd
    );



//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//  ============================ HWND Server Window Control ============================
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

#ifndef NOHWNDSERVER

#ifdef _WIN32

#define HWNDSERVER_CLASSW       L"HwndServerWindow32"          
#define HWNDSERVER_CLASSA       "HwndServerWindow32"


#ifdef UNICODE
#define HWNDSERVER_CLASS        HWNDSERVER_CLASSW
#else
#define HWNDSERVER_CLASS        HWNDSERVER_CLASSA
#endif

#else
#define HWNDSERVER_CLASS        "HwndServerWindow32"
#endif
/*
 * HWND server class
 */
#define WC_WINDOWSERVER         (HWNDSERVER_CLASS)

//---------------------------------------------------------------------------------------
// Immersive Window Control Styles
//---------------------------------------------------------------------------------------
// begin_r_commctrl
// end_r_commctrl

#define WM_SERVERCREATEWINDOW (WM_USER + 0x1337)
#define WM_SERVERDESTROYWINDOW (WM_USER + 0x1338)

typedef struct tagCREATEWINDOWPARAMS
{
  DWORD     dwExStyle;
  LPCWSTR   lpClassName;
  LPCWSTR   lpWindowName;
  DWORD     dwStyle;
  int       X;
  int       Y;
  int       nWidth;
  int       nHeight;
  HWND      hWndParent;
  HMENU     hMenu;
  HINSTANCE hInstance;
  LPVOID    lpParam;
} CREATEWINDOWPARAMS, * LPCREATEWINDOWPARAMS;

HWND WINAPI CreateWindowServer(void);
HWND WINAPI ServerCreateWindow(HWND hwndServer, LPCREATEWINDOWPARAMS lpcwp);
LRESULT WINAPI CALLBACK DefServerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // NOHWNDSERVER

// Affects the colors the uxtheme.lib chooses to color controls. 
typedef enum tagPREFERREDAPPMODE {
  PAM_DEFAULT,
  PAM_ALLOWDARK,
  PAM_FORCEDARK,
  PAM_FORCELIGHT,
  PAM_LAST
} PREFERREDAPPMODE;

typedef VOID(WINAPI* PFNREFRESHIMMERSIVECOLORPOLICYSTATE)(VOID);
typedef PREFERREDAPPMODE(WINAPI* PFNSETPREFERREDAPPMODE)(PREFERREDAPPMODE eAppMode);

EXTERN_C PFNSETPREFERREDAPPMODE SetPreferredAppMode;
EXTERN_C PFNREFRESHIMMERSIVECOLORPOLICYSTATE RefreshImmersiveColorPolicyState;

EXTERN_C
BOOL PFORCEINLINE WINAPI
InitializeSysThunks(
    VOID
    );

EXTERN_C
BOOL PFORCEINLINE WINAPI
GetWindowCenteredPoint(
    LPPOINT      lppt,
    const LPSIZE lpsz
    );

EXTERN_C
BOOL PFORCEINLINE WINAPI
MonitorWorkRectFromWindow(
    HWND   hwnd,
    LPRECT rcWork
    );

EXTERN_C
HRESULT PFORCEINLINE WINAPI
EnableBlurBehind(
    HWND hWnd
    );

EXTERN_C
BOOL CFORCEINLINE WINAPI
ShowSystemMenu(
    HWND hwnd,
    int x,
    int y);

EXTERN_C void
EnableDarkMode(
    HWND hWnd
    );

EXTERN_C void
EnableLightMode(
    HWND hWnd
    );

EXTERN_C
BOOL FORCEINLINE WINAPI
SetWindowData(
    HWND hWnd,
    int nIndex,
    LPVOID pData
    );

EXTERN_C
NCHIT PFORCEINLINE WINAPI
NCHitTest(
    HWND hwnd,
    POINT pt
    );

EXTERN_C
BOOL PFORCEINLINE APIPRIVATE
GetCaptionButtonRect(
    HWND   hWnd,
    LPRECT lprcCaption,
    CAPTIONBUTTON  eCaptionButton
    );

EXTERN_C
BOOL PFORCEINLINE APIPRIVATE
GetCaptionButtonRectFast(
    LPRECT lprcCaption,
    int nWidth,
    CAPTIONBUTTON eCaptionButton
    );

EXTERN_C
BOOL WINAPI
IsWindowClosing(
    HWND hwnd
    );

HWND ShowTooltip(const char* szTip, int x, int y);
VOID DestroyTooltip(HWND hwnd);

BOOL IsRestoredEx(HWND hwnd);
BOOL WorkspaceToScreen(LPRECT lprcWorkspace);

typedef struct _DWM_WINDOW_ATTRIBUTES
{
    BOOL fNcRenderingEnabled;
    RECT rcCaptionButtonBounds;
    RECT rcExtendedFrameBounds;
    BOOL fCloaked;
    
} DWM_WINDOW_ATTRIBUTES, * PDWM_WINDOW_ATTRIBUTES;

BOOL DwmGetWindowAttributes(
    HWND hwnd,
    PDWM_WINDOW_ATTRIBUTES pAttr
    );

EXTERN_C
LRESULT PFORCEINLINE
DwmDefWindowProcEx(
    HWND   hWnd,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam
    );