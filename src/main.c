// #include <stdio.h>
// #include <stdlib.h>
// //#define WEBVIEW_HEADER
// //#include "webview.h"

// #include <windows.h>
// #include <WebView2.h>

// void myFunc(const char *seq, const char *req, void *arg) {
// 	printf("Params: %s\n", req);
// }

// #ifdef _MSC_VER
// int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,
//                    int nCmdShow) 
// {
// #else
// int main() 
// {
// #endif

// 	// webview_t w = webview_create(0, NULL);
// 	// webview_set_title(w, "Webview Example");
// 	// webview_set_size(w, 480, 320, WEBVIEW_HINT_NONE);
// 	// webview_bind(w, "myFunc", myFunc, NULL);
// 	// webview_navigate(w, "data:text/html, <button onclick='myFunc(\"Foo bar\")'>Click Me</button>");
// 	// webview_run(w);
// 	// webview_destroy(w);




//     return 0;
// }

#if 0
#include <windows.h>
#include <WebView2.h>



// C-Style Interface Example
// https://stackoverflow.com/questions/66820213/basic-win32-webview2-example-not-working-in-pure-c


ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler* _envHandler;
ICoreWebView2CreateCoreWebView2ControllerCompletedHandler* _completedHandler;

HWND _hWnd = NULL;
ICoreWebView2Controller* _webviewController = NULL;
ICoreWebView2* _webviewWindow = NULL;
BOOL _bEnvCreated = FALSE;



void GetDataPath(LPTSTR szOut, DWORD nSize)
{
	TCHAR szExePath[MAX_PATH];
	GetModuleFileName(NULL, szExePath, _countof(szExePath));

	LPTSTR szExeName = _tcsrchr(szExePath, TEXT('\\'));
	szExeName = szExeName ? szExeName + 1 : szExePath;

	TCHAR szAppData[MAX_PATH];
	GetEnvironmentVariable(TEXT("AppData"), szAppData, _countof(szAppData));

	_tcsncpy(szOut, szAppData, nSize);
	_tcsncat(szOut, TEXT("\\"), nSize);
	_tcsncat(szOut, szExeName, nSize);
}



static void ResizeBrowser(HWND hWnd)
{
#if 0
	if (!controller)
	{
		return;
	}
	RECT bounds;
	GetClientRect(hWnd, &bounds);
	controller->lpVtbl->put_Bounds(controller, bounds);
#endif
}



static HRESULT CreateEnvironmentCompleted(	HRESULT result, ICoreWebView2Environment* env)
{
    //CreateCoreWebView2Controller();

    return 0;

}


// static int _state = 0;


// static void fsm()
// {
//     switch(_state)
//     {
//         0 :
//     }
// }




LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		ResizeBrowser(hWnd);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
        PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	HICON icon = (HICON)(LoadImage(
		hInstance,
		IDI_APPLICATION,
		IMAGE_ICON,
		GetSystemMetrics(SM_CXICON),
		GetSystemMetrics(SM_CYICON),
		0
	));

	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("webview");
	wc.hIcon = icon;
	wc.hIconSm = icon;
	wc.lpfnWndProc = WndProc;
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindowEx(
		0,
		TEXT("webview"),
		TEXT("MinGW WebView2 Demo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1024,
		768,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	SetFocus(hWnd);

	// Get data path.

    

	TCHAR szDataPath[MAX_PATH];
	GetDataPath(szDataPath, _countof(szDataPath));

    CreateCoreWebView2EnvironmentWithOptions(NULL, NULL, NULL, CreateEnvironmentCompleted);

#if 0

	// Set up some event handlers.
	EventHandler handler = {};


	handler.EnvironmentCompleted = [&](HRESULT result, ICoreWebView2Environment* created_environment)
	{
		if (FAILED(result))
		{
			FatalError(TEXT("Failed to create environment?"));
		}
		created_environment->lpVtbl->CreateCoreWebView2Controller(created_environment, hWnd, &handler);
		return S_OK;
	};

	handler.ControllerCompleted = [&](HRESULT result, ICoreWebView2Controller* new_controller)
	{
		if (FAILED(result))
		{
			FatalError(TEXT("Failed to create controller?"));
		}
		controller = new_controller;
		controller->lpVtbl->AddRef(controller);
		controller->lpVtbl->get_CoreWebView2(controller, &webview2);
		webview2->lpVtbl->AddRef(webview2);
		webview2->lpVtbl->Navigate(webview2, L"https://en.m.wikipedia.org/wiki/Tyson_Tan");
		ResizeBrowser(hWnd);
		return S_OK;
	};

	HRESULT result = CreateCoreWebView2EnvironmentWithOptions(
		nullptr,
		TStrToWStr(szDataPath).c_str(),
		nullptr,
		&handler
	);
	if (FAILED(result))
	{
		FatalError(TEXT("Call to CreateCoreWebView2EnvironmentWithOptions failed!"));
	}
#endif

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_QUIT)
		{
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
#endif

#include <initguid.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
// #include <Shlobj_core.h>

#include <WebView2.h>

#define APPLICATION_NAME TEXT("WebView2")

#define error_printf printf

ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler* envHandler;
ICoreWebView2CreateCoreWebView2ControllerCompletedHandler* completedHandler;
HWND hWnd = NULL;
ICoreWebView2Controller* webviewController = NULL;
ICoreWebView2* webviewWindow = NULL;
BOOL bEnvCreated = FALSE;

ULONG HandlerRefCount = 0;
ULONG HandlerAddRef(IUnknown* This)
{
    return ++HandlerRefCount;
}
ULONG HandlerRelease(IUnknown* This)
{
    --HandlerRefCount;
    if (HandlerRefCount == 0)
    {
        if (completedHandler)
        {
            free(completedHandler->lpVtbl);
            free(completedHandler);
        }
        if (envHandler)
        {
            free(envHandler->lpVtbl);
            free(envHandler);
        }
    }
    return HandlerRefCount;
}
HRESULT HandlerQueryInterface(
    IUnknown* This,
    IID* riid,
    void** ppvObject
)
{
    *ppvObject = This;
    HandlerAddRef(This);
    return S_OK;
}
HRESULT HandlerInvoke(
    IUnknown* This,
    HRESULT errorCode,
    void* arg
)
{
    if (!bEnvCreated)
    {
        bEnvCreated = TRUE;
        char ch;
        completedHandler = malloc(sizeof(ICoreWebView2CreateCoreWebView2ControllerCompletedHandler));
        if (!completedHandler)
        {
            error_printf(
                "%s:%d: %s (0x%x).\n",
                __FILE__,
                __LINE__,
                "Cannot allocate ICoreWebView2CreateCoreWebView2ControllerCompletedHandler",
                GetLastError()
            );
            ch = _getch();
            return GetLastError();
        }
        completedHandler->lpVtbl = malloc(sizeof(ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl));
        if (!completedHandler->lpVtbl)
        {
            error_printf(
                "%s:%d: %s (0x%x).\n",
                __FILE__,
                __LINE__,
                "Cannot allocate ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl",
                GetLastError()
            );
            ch = _getch();
            return GetLastError();
        }
        completedHandler->lpVtbl->AddRef = HandlerAddRef;
        completedHandler->lpVtbl->Release = HandlerRelease;
        completedHandler->lpVtbl->QueryInterface = HandlerQueryInterface;
        completedHandler->lpVtbl->Invoke = HandlerInvoke;

        ICoreWebView2Environment* env = arg;
        env->lpVtbl->CreateCoreWebView2Controller(
            env,
            hWnd,
            completedHandler
        );

    }
    else
    {

        //printf("And here I am at 1.\n");
        ICoreWebView2Controller* controller = arg;

        if (controller != NULL) {
            webviewController = controller;
            webviewController->lpVtbl->get_CoreWebView2(
                webviewController,
                &webviewWindow
            );
            webviewController->lpVtbl->AddRef(webviewController); // <-- here, increase the reference count for the webviewController
        }


        //printf("And here I am at 2.\n");

        ICoreWebView2Settings* Settings;

        webviewWindow->lpVtbl->get_Settings(
            webviewWindow,
            &Settings
        );
        Settings->lpVtbl->put_IsScriptEnabled(
            Settings,
            TRUE
        );
        Settings->lpVtbl->put_AreDefaultScriptDialogsEnabled(
            Settings,
            TRUE
        );
        Settings->lpVtbl->put_IsWebMessageEnabled(
            Settings,
            TRUE
        );
        Settings->lpVtbl->put_AreDevToolsEnabled(
            Settings,
            FALSE
        );
        Settings->lpVtbl->put_AreDefaultContextMenusEnabled(
            Settings,
            TRUE
        );
        Settings->lpVtbl->put_IsStatusBarEnabled(
            Settings,
            TRUE
        );

        RECT bounds;
        GetClientRect(hWnd, &bounds);
        webviewController->lpVtbl->put_Bounds(
            webviewController,
            bounds
        );


        EventRegistrationToken token = {};

        ICoreWebView2WebMessageReceivedEventHandler* msgHandler = NULL;
        if ( MessageHandler_Create(&msgHandler) )
        {
            error_printf(
                "%s:%d: %s (0x%x).\n",
                __FILE__,
                __LINE__,
                "Failed to allocate web message handler",
                GetLastError()
            );
            int ch = _getch();
            return GetLastError();            
        }




        webviewWindow->lpVtbl->add_WebMessageReceived(
            webviewWindow,
            msgHandler,
            &token
        );


        // Post document URL to the host
        webviewWindow->lpVtbl->AddScriptToExecuteOnDocumentCreated(
            webviewWindow,
            L"window.chrome.webview.postMessage(window.document.URL);",
            NULL
        );





        //printf("Navigating...\n");
        webviewWindow->lpVtbl->Navigate(
            webviewWindow,
            L"file:///C:/Users/ThomasBitskyJr/source/repos/3254Swing/WebUx/build/index.html"
            //
            // L"https://google.com/"
        );
    }

    return S_OK;
}

LRESULT CALLBACK WindowProc(
    _In_ HWND   hWnd,
    _In_ UINT   uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{
    switch (uMsg)
    {
    /*case WM_NCCALCSIZE:
    {
        return 0;
    }*/
    case WM_DPICHANGED:
    {
        RECT* const newWindowSize = (RECT*)(lParam);
        SetWindowPos(
            hWnd,
            NULL,
            newWindowSize->left,
            newWindowSize->top,
            newWindowSize->right - newWindowSize->left,
            newWindowSize->bottom - newWindowSize->top,
            SWP_NOZORDER | SWP_NOACTIVATE);
        return TRUE;
    }
    case WM_SIZE:
    {
        if (webviewController != NULL) {
            RECT bounds;
            GetClientRect(hWnd, &bounds);
            webviewController->lpVtbl->put_Bounds(
                webviewController,
                bounds
            );
        };
        break;
    }
    default:
    {
        return DefWindowProc(
            hWnd,
            uMsg,
            wParam,
            lParam
        );
    }
    }
    return 0;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
    int ch;

    FILE* conout;
    AllocConsole();
    freopen_s(
        &conout,
        "CONOUT$",
        "w",
        stdout
    );

    HRESULT hr;

    if (!SetProcessDpiAwarenessContext(
        DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
    ))
    {
        error_printf(
            "%s:%d: %s (0x%x).\n",
            __FILE__,
            __LINE__,
            "SetProcessDpiAwarenessContext",
            GetLastError()
        );
        ch = _getch();
        return GetLastError();
    }

    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        error_printf(
            "%s:%d: %s (0x%x).\n",
            __FILE__,
            __LINE__,
            "CoInitialize",
            hr
        );
        ch = _getch();
        return hr;
    }

    WNDCLASS wndClass = { 0 };
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WindowProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = APPLICATION_NAME;

    hWnd = CreateWindowEx(
        0,
        (LPCWSTR)(
            MAKEINTATOM(
                RegisterClass(&wndClass)
            )
            ),
        APPLICATION_NAME,
        WS_OVERLAPPEDWINDOW,
        100, 100, 800, 800,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if (!hWnd)
    {
        error_printf(
            "%s:%d: %s (0x%x).\n",
            __FILE__,
            __LINE__,
            "CreateWindowEx",
            GetLastError()
        );
        ch = _getch();
        return GetLastError();
    }

    ShowWindow(hWnd, SW_SHOW);

    envHandler = malloc(sizeof(ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler));
    if (!envHandler)
    {
        error_printf(
            "%s:%d: %s (0x%x).\n",
            __FILE__,
            __LINE__,
            "Cannot allocate ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler",
            GetLastError()
        );
        ch = _getch();
        return GetLastError();
    }
    envHandler->lpVtbl = malloc(sizeof(ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl));
    if (!envHandler->lpVtbl)
    {
        error_printf(
            "%s:%d: %s (0x%x).\n",
            __FILE__,
            __LINE__,
            "Cannot allocate ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl",
            GetLastError()
        );
        ch = _getch();
        return GetLastError();
    }
    envHandler->lpVtbl->AddRef = HandlerAddRef;
    envHandler->lpVtbl->Release = HandlerRelease;
    envHandler->lpVtbl->QueryInterface = HandlerQueryInterface;
    envHandler->lpVtbl->Invoke = HandlerInvoke;
    
    UpdateWindow(hWnd);

    CreateCoreWebView2EnvironmentWithOptions(
        NULL,
        NULL,
        NULL,
        envHandler
    );

    MSG msg;
    BOOL bRet;
    while ((bRet = GetMessage(
        &msg,
        NULL,
        0,
        0)) != 0)
    {
        // An error occured
        if (bRet == -1)
        {
            break;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}