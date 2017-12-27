// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved


#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers

#include "MainWindow.h"

#include <GDIPlus.h>
#include <UXTheme.h>

using namespace Gdiplus;

// Entry point to the application

int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
    )
{
    HRESULT hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        if (SUCCEEDED(BufferedPaintInit()))
        {
            ULONG_PTR gdiplusToken;
            GdiplusStartupInput gdiplusStartupInput;
            
            if (GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) == Ok)
            {
                {
                    CMainWindow mainWindow;
                    hr = mainWindow.Initialize(hInstance);
                    if (SUCCEEDED(hr))
                    {
                        MSG msg;
                        while (GetMessage(&msg, NULL, 0, 0) > 0)
                        {
                            TranslateMessage(&msg);
                            DispatchMessage(&msg);
                        }
                    }
                }
                
                GdiplusShutdown(gdiplusToken);
            }
            
            BufferedPaintUnInit();
        }

        CoUninitialize();
    }

    return 0;
}
