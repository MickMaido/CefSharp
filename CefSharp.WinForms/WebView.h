#pragma once

#include "BrowserSettings.h"
#include "ClientAdapter.h"
#include "ScriptCore.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;

namespace CefSharp
{
namespace WinForms
{
    public ref class WebView sealed : public Control, IWebBrowser
    {
    private:
        BrowserSettings^ _settings;

        MCefRefPtr<ClientAdapter> _clientAdapter;
        BrowserCore^ _browserCore;
        MCefRefPtr<ScriptCore> _scriptCore;

        void Initialize(String^ address, BrowserSettings^ settings);
        bool TryGetCefBrowser(CefRefPtr<CefBrowser>& browser);

    protected:
        virtual void OnHandleCreated(EventArgs^ e) override;
        virtual void OnSizeChanged(EventArgs^ e) override;
        virtual void OnGotFocus(EventArgs^ e) override;


    public:
        virtual event PropertyChangedEventHandler^ PropertyChanged
        {
            void add(PropertyChangedEventHandler^ handler)
            {
                _browserCore->PropertyChanged += handler;
            }

            void remove(PropertyChangedEventHandler^ handler)
            {
                _browserCore->PropertyChanged -= handler;
            }
        }

        virtual event ConsoleMessageEventHandler^ ConsoleMessage;

		virtual event KeyEventHandler^ BrowserKeyEvent;

        WebView()
        {
            Initialize(String::Empty, gcnew BrowserSettings);
        }

        WebView(String^ address, BrowserSettings^ settings)
        {
            Initialize(address, settings);
        }

        ~WebView()
        {
            CefRefPtr<CefBrowser> browser;
            if (TryGetCefBrowser(browser))
            {
                browser->CloseBrowser();
            }
        }

        virtual property bool IsBrowserInitialized
        {
            bool get() { return _browserCore->IsBrowserInitialized; }
        }

        virtual property bool IsLoading
        {
            bool get() { return _browserCore->IsLoading; }
        }

        virtual property bool CanGoBack
        { 
            bool get() { return _browserCore->CanGoBack; } 
        }

        virtual property bool CanGoForward
        { 
            bool get() { return _browserCore->CanGoForward; } 
        }

        virtual property int ContentsWidth
        {
            int get() { return _browserCore->ContentsWidth; }
            void set(int contentsWidth) { _browserCore->ContentsWidth = contentsWidth; }
        }

        virtual property int ContentsHeight
        {
            int get() { return _browserCore->ContentsHeight; }
            void set(int contentsHeight) { _browserCore->ContentsHeight = contentsHeight; }
        }

        virtual property String^ Address
        {
            String^ get() { return _browserCore->Address; }
            void set(String^ address) { _browserCore->Address = address; }
        }

        virtual property String^ Title
        {
            String^ get() { return _browserCore->Title; }
            void set(String^ title) { _browserCore->Title = title; }
        }

        virtual property Object^ BoundObject
        {
            Object^ get() { return _browserCore->BoundObject; }
            void set(Object^ object) { _browserCore->BoundObject = object; }
        }

        virtual property String^ TooltipText
        {
            String^ get() { return _browserCore->TooltipText; }
            void set(String^ text) { _browserCore->TooltipText = text; }
        }

        virtual property IBeforePopup^ BeforePopupHandler
        {
            IBeforePopup^ get() { return _browserCore->BeforePopupHandler; }
            void set(IBeforePopup^ handler) { _browserCore->BeforePopupHandler = handler; }
        }

        virtual property IBeforeResourceLoad^ BeforeResourceLoadHandler
        {
            IBeforeResourceLoad^ get() { return _browserCore->BeforeResourceLoadHandler; }
            void set(IBeforeResourceLoad^ handler) { _browserCore->BeforeResourceLoadHandler = handler; }
        }

        virtual property IBeforeMenu^ BeforeMenuHandler
        {
            IBeforeMenu^ get() { return _browserCore->BeforeMenuHandler; }
            void set(IBeforeMenu^ handler) { _browserCore->BeforeMenuHandler = handler; }
        }

        virtual property IAfterResponse^ AfterResponseHandler
        {
            IAfterResponse^ get() { return _browserCore->AfterResponseHandler; }
            void set(IAfterResponse^ handler) { _browserCore->AfterResponseHandler = handler; }
        }

        virtual void OnInitialized();

        virtual void Load(String^ url);
        virtual void Stop();
        virtual void Back();
        virtual void Forward();
        virtual void Reload();
        virtual void Reload(bool ignoreCache);
        virtual void ClearHistory();
        virtual void ShowDevTools();
        virtual void CloseDevTools();

        virtual void Undo();
        virtual void Redo();
        virtual void Cut();
        virtual void Copy();
        virtual void Paste();
        virtual void Delete();
        virtual void SelectAll();
        virtual void Print();

        void ExecuteScript(String^ script);
        Object^ EvaluateScript(String^ script);
        Object^ EvaluateScript(String^ script, TimeSpan timeout);

        virtual void SetNavState(bool isLoading, bool canGoBack, bool canGoForward);

        virtual void OnFrameLoadStart();
        virtual void OnFrameLoadEnd();
        virtual void OnTakeFocus(bool next);
        virtual void OnConsoleMessage(String^ message, String^ source, int line);
		virtual void OnKeyEvent(int type, int code, int modifiers, bool isSystemKey);
    };
}}