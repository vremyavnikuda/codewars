#include <windows.h>
#include <string>
#include <atlbase.h>
#include <oleacc.h>

int main() {
    // Set the path to the Firefox executable
    std::wstring firefoxPath = L"C:\\Program Files\\Mozilla Firefox\\firefox.exe";

    // Set the URL to open in Firefox
    std::wstring url = L"https://yandex.com/";

    // Open Firefox with the specified URL
    ShellExecute(NULL, L"open", firefoxPath.c_str(), url.c_str(), NULL, SW_SHOW);

    // Wait for Firefox to fully load
    Sleep(10000);

    // Use the .NET UI Automation framework to find and click the "Войти" button
    CComPtr<IUIAutomation> pAutomation;
    HRESULT hr = CoCreateInstance(CLSID_CUIAutomation, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pAutomation));

    if (SUCCEEDED(hr)) {
        CComPtr<IUIAutomationElement> pRootElement;
        hr = pAutomation->GetRootElement(&pRootElement);

        if (SUCCEEDED(hr)) {
            CComPtr<IUIAutomationElement> pFirefoxWindow;
            hr = pRootElement->FindFirst(TreeScope_Descendants, NULL, ProcessIdProperty, &firefoxPath[0], &pFirefoxWindow);

            if (SUCCEEDED(hr)) {
                CComPtr<IUIAutomationElementArray> pButtons;
                hr = pFirefoxWindow->FindAll(TreeScope_Descendants, NULL, NameProperty, L"Войти", &pButtons);

                if (SUCCEEDED(hr)) {
                    long buttonCount = 0;
                    hr = pButtons->get_Length(&buttonCount);

                    if (SUCCEEDED(hr)) {
                        for (long i = 0; i < buttonCount; i++) {
                            CComPtr<IUIAutomationElement> pButton;
                            hr = pButtons->GetElement(i, &pButton);

                            if (SUCCEEDED(hr)) {
                                CComPtr<IUIAutomationInvokePattern> pInvokePattern;
                                hr = pButton->GetCurrentPattern(UIA_InvokePatternId, IID_PPV_ARGS(&pInvokePattern));

                                if (SUCCEEDED(hr)) {
                                    pInvokePattern->Invoke();
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}