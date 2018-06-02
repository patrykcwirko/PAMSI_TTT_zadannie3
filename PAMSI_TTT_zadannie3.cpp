// PAMSI_TTT_zadannie3.cpp : definiuje punkt wejścia dla aplikacji
//

#include <stdlib.h>
#include "stdafx.h"
#include <iostream>
#include <string>
#include "PAMSI_TTT_zadannie3.h"
#include "Ustawienia.h"
#include "Siatka.h"
#include "Narzedzia.h"
#include "KolkoKrzyzyk.h"

#define MAX_LOADSTRING 100


// Zmienne globalne:
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego

// Przekaż dalej deklaracje funkcji dołączonych w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AboutCallback(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    UstawieniaCallback(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    RestartCallback(HWND, UINT, WPARAM, LPARAM);
void podajKtoWygral(HWND hWnd, KolkoKrzyzyk_Ptr ptrKolkoKrzyzyk);

// Zmienne dla Kółko i krzyżyk>>>>>>
Ustawienia_Ptr ptrUstawienia = std::make_shared<Ustawienia>();
Siatka_Ptr ptrSiatka = std::make_shared<Siatka>(Siatka(ptrUstawienia));
KolkoKrzyzyk_Ptr ptrKolkoKrzyzyk = std::make_shared<KolkoKrzyzyk>(KolkoKrzyzyk(ptrUstawienia));

//<<<<<<Zmienne dla Kółko i krzyżyk



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: DONE W tym miejscu umieść kod.
	Narzedzia::RedirectIOToConsole();
	Narzedzia::printLog("START");

    // Zainicjuj ciągi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PAMSITTTZADANNIE3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjacje aplikacji:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAMSITTTZADANNIE3));

    MSG msg;

    // Główna pętla wiadomości:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  CEL: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAMSITTTZADANNIE3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PAMSITTTZADANNIE3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   CEL: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Przechowuj dojście wystąpienia w zmiennej globalnej

   RECT MRECT;
   GetWindowRect(GetDesktopWindow(), &MRECT);
   int CX = (MRECT.right / 2) - (TDLUGOSC / 2);
   int CY = (MRECT.bottom / 2) - (TWYSOKOSC / 2);
 /*  HWND Window = CreateWindow("TicTacToe", "TicTacToe", WS_CAPTION | WS_SYSMENU | WS_OVERLAPPED,
							CX, CY, TWidth, THeight, HWND_DESKTOP, NULL, hThisInst, NULL);*/
/*
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);*/

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CX, CY, TDLUGOSC, TWYSOKOSC, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  CEL: Przetwarza wiadomości dla okna głównego.
//
//  WM_COMMAND — przetwarzaj menu aplikacji
//  WM_PAINT — pomaluj okno główne
//  WM_DESTROY — opublikuj komunikat o rezygnacji i wróć
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizuj zaznaczenia menu:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutCallback);
                break;
			case IDM_USTAWIENIA:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_USTAWIENIA), hWnd, UstawieniaCallback);
				break;
			case ID_PLIK_NOWAGRA:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_RESTART), hWnd, RestartCallback);
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: DONE tutaj dodaj kod rysowania używający elementu hdc...
			ptrSiatka->narysuj(&hWnd, ptrKolkoKrzyzyk);
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:

		ptrSiatka->zaznaczKlikniecie(ptrKolkoKrzyzyk, lParam);
		podajKtoWygral(hWnd, ptrKolkoKrzyzyk);
		ptrSiatka->narysuj(&hWnd, ptrKolkoKrzyzyk);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//Procedura obsługi wiadomości dla okna informacji o programie.
INT_PTR CALLBACK AboutCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int ustawieniaPobranieIlosciWRzedzie(HWND hDlg)
{
	HWND hIloscWRzedzie = GetDlgItem(hDlg, IDC_EDIT2);
	DWORD dlugoscTekstu = GetWindowTextLength(hIloscWRzedzie);
	wchar_t* lpszIloscWRzedzie = new wchar_t[dlugoscTekstu + 1];
	GetWindowText(hIloscWRzedzie, lpszIloscWRzedzie, dlugoscTekstu + 1);
	int iloscWRzedzie = wcstol(lpszIloscWRzedzie, 0, 10);
	delete lpszIloscWRzedzie;
	std::cout << "ilosc w Rzedzie: " << iloscWRzedzie << std::endl;
	return iloscWRzedzie;
}

//Procedura obsługi ustawień dla programu.
INT_PTR CALLBACK UstawieniaCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK )
		{	
			//Przejąć wartości z ustawień
			USTAWIENIADIALOGRESULT * ldr = new USTAWIENIADIALOGRESULT;
			ZeroMemory(&ldr, sizeof(USTAWIENIADIALOGRESULT));
			int iloscWRzedzie = ustawieniaPobranieIlosciWRzedzie(hDlg);
			ptrSiatka->ustawWielkosc(iloscWRzedzie);
			ptrKolkoKrzyzyk->ustawWielkosc(iloscWRzedzie);
			delete ldr;
			EndDialog(hDlg, LOWORD(wParam));
			HWND hParent = GetParent(hDlg);
			PostMessage(hParent, WM_PAINT, 0, 0);
			Narzedzia::printLog("Ustawienie wielkosci na: " + std::to_string(iloscWRzedzie) );
			return (INT_PTR)TRUE;
		}
		if ( LOWORD(wParam) == IDCANCEL )
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RestartCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			ptrKolkoKrzyzyk->init();
			EndDialog(hDlg, LOWORD(wParam));
			HWND hParent = GetParent(hDlg);
			PostMessage(hParent, WM_PAINT, 0, 0);
			Narzedzia::printLog("Restart");
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void podajKtoWygral(HWND hWnd ,KolkoKrzyzyk_Ptr ptrKolkoKrzyzyk)
{
	std::string wygral = "Remis";
	switch (ptrKolkoKrzyzyk->status())
	{
	case G1Wygrywa:
		wygral = "X wygral.";
		break;
	case G2Wygrywa:
		wygral = "O wygral.";
		break;
	default:
		wygral = "Remis";
		break;
	}
	SetWindowText(hWnd, (LPCWSTR)wygral.c_str());
}