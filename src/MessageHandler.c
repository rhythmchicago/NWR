/*
 * (C) Copyright 2022 Automated Design Corp. All Rights Reserved.
 * File Created: Monday, 7th March 2022 9:06:51 pm
 * Author: Thomas C. Bitsky Jr. (support@automateddesign.com)
 */

#include "MessageHandler.h"

#include <stdio.h>
#include <conio.h> // getch
#include <windows.h>

static ICoreWebView2WebMessageReceivedEventHandler* _handler = NULL;
static ULONG _refCount = 0;
static BOOL _isCreated = FALSE;


static ULONG MsgHandlerAddRef(/* IUnknown* */ ICoreWebView2WebMessageReceivedEventHandler* This)
{
    printf("%s:%d\n", __FILE__, __LINE__);

    printf("MsgHandlerAddRef Ref Count is currently %d\n", _refCount);

    _refCount += 1;

    return _refCount;
}



static ULONG MsgHandlerRelease(/* IUnknown* */ ICoreWebView2WebMessageReceivedEventHandler* This)
{
    printf("%s:%d\n", __FILE__, __LINE__);

    printf("MsgHandlerRelease Ref Count is currently %d\n", _refCount);

    if ( _refCount > 0 )
        _refCount -= 1;

    if (_refCount == 0)
    {
        if (_handler) 
        {
            free(_handler->lpVtbl);
            free(_handler);

            _handler->lpVtbl = 0;
            _handler = 0;
        }
    }

    printf("MsgHandlerRelease Ref Count is now  %d\n", _refCount);

    return _refCount;
}


static HRESULT MsgHandlerQueryInterface(
    /* IUnknown* This */ ICoreWebView2WebMessageReceivedEventHandler* This,
    const IID* riid,
    void** ppvObject
)
{
    printf("%s:%d\n", __FILE__, __LINE__);

    *ppvObject = This;
    MsgHandlerAddRef(This);
    return S_OK;
}

/**
 * @brief Callback from the WebView, which has sent a message.
 * 
 */
HRESULT MsgHandlerInvoke(
    /* IUnknown* This */ ICoreWebView2WebMessageReceivedEventHandler* This,
    /* HRESULT errorCode */ ICoreWebView2 *sender,
    ICoreWebView2WebMessageReceivedEventArgs* args
)
{
    printf("%s:%d\n", __FILE__, __LINE__);

    PWSTR message = NULL;

    printf("MsgHandlerInvoke message addr %d\n", &message);

    args->lpVtbl->TryGetWebMessageAsString(args, &message);


    printf("MsgHandlerInvoke message addr is now %d\n", &message);


    wprintf(message);

    sender->lpVtbl->PostWebMessageAsString(sender, message);

    CoTaskMemFree(message);

    return S_OK;
}







int MessageHandler_Create(ICoreWebView2WebMessageReceivedEventHandler** t)
{
    _handler
        = (ICoreWebView2WebMessageReceivedEventHandler*)malloc(sizeof(ICoreWebView2WebMessageReceivedEventHandler));

    if ( _handler == 0 ) 
    {
        printf(
            "%s:%d: %s (0x%x).\n",
            __FILE__,
            __LINE__,
            "Cannot allocate ICoreWebView2WebMessageReceivedEventHandler",
            GetLastError()
        );

        int ch = _getch();        
        return -10;
    }

    _handler->lpVtbl = (ICoreWebView2WebMessageReceivedEventHandlerVtbl*)malloc(sizeof(ICoreWebView2WebMessageReceivedEventHandlerVtbl));

    if ( _handler->lpVtbl == 0 )
    {
        printf(
            "%s:%d: %s (0x%x).\n",
            __FILE__,
            __LINE__,
            "Cannot allocate ICoreWebView2WebMessageReceivedEventHandlerVtbl",
            GetLastError()
        );

        int ch = _getch();        
        return -100;
    }

    _handler->lpVtbl->AddRef = MsgHandlerAddRef;
    _handler->lpVtbl->Release = MsgHandlerRelease;
    _handler->lpVtbl->QueryInterface = MsgHandlerQueryInterface;
    _handler->lpVtbl->Invoke = MsgHandlerInvoke;


    printf(
        "%s:%d: %s \n",
        __FILE__,
        __LINE__,
        "Successfully created handler\n"
    );

    *t = _handler;

    return 0;
}