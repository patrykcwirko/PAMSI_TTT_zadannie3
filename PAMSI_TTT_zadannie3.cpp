// PAMSI_TTT_zadannie3.cpp : definiuje punkt wejścia dla aplikacji
//

#include <stdlib.h>
#include "stdafx.h"
#include <iostream>
#include <string>
#include "PAMSI_TTT_zadannie3.h"


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
void pobranieUstawien(HWND hDlg);
void initUstawien(HWND hDlg);

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
	case WM_ACTIVATE:
		{
		/*	if (ptrUstawienia->czyZaczynaKomputer())
			{
				ptrKolkoKrzyzyk->wykonajRuchKomp(OZnak);
			}*/
		}
		break;
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
		{
			if (ptrKolkoKrzyzyk->czyTerazRuchGracza())
			{
				Pozycja_Ptr kratka = ptrSiatka->wyliczKratke(lParam);
				if (kratka->x != NIEPOPRAWNA && kratka->y != NIEPOPRAWNA) {
					Wynik_Ptr wynik = std::make_shared<Wynik>(0, Pusta, kratka);
					bool usawionoKratke = ptrKolkoKrzyzyk->ustawKratke(wynik);
					if (usawionoKratke)
					{
						ptrKolkoKrzyzyk->wykonajRuchKomp(OZnak);
					}
					ptrSiatka->narysuj(&hWnd, ptrKolkoKrzyzyk);
				}
			}
			podajKtoWygral(hWnd, ptrKolkoKrzyzyk);
		}
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

void pobranieUstawien(HWND hDlg)
{
	HWND hIloscWRzedzie = GetDlgItem(hDlg, IDC_EDIT2);
	DWORD dlugoscTekstu = GetWindowTextLength(hIloscWRzedzie);
	wchar_t* lpszIloscWRzedzie = new wchar_t[dlugoscTekstu + 1];
	GetWindowText(hIloscWRzedzie, lpszIloscWRzedzie, dlugoscTekstu + 1);
	int rozmiarSiatki = wcstol(lpszIloscWRzedzie, 0, 10);
	delete lpszIloscWRzedzie;
	ptrUstawienia->ustawRozmiarSiatki(rozmiarSiatki);

	HWND hGlebokosc = GetDlgItem(hDlg, IDC_EDIT3);
	DWORD dlugoscTekstu2 = GetWindowTextLength(hGlebokosc);
	wchar_t* lpszGlebokosc = new wchar_t[dlugoscTekstu2 + 1];
	GetWindowText(hGlebokosc, lpszGlebokosc, dlugoscTekstu2 + 1);
	int glebokoscSzukania = wcstol(lpszGlebokosc, 0, 10);
	delete lpszGlebokosc;
	ptrUstawienia->ustawGlebokoscSzukania(glebokoscSzukania);

	//bool zaczynaKomputer = (IsDlgButtonChecked(hDlg, IDC_CHECK1) == BST_CHECKED);
	bool graLosowymi = (IsDlgButtonChecked(hDlg, IDC_CHECK2) == BST_CHECKED);
	//ptrUstawienia->ustawZaczynaKomputer(zaczynaKomputer);
	ptrUstawienia->ustawGraWartLosowymi(graLosowymi);
	Narzedzia::printLog(*(ptrUstawienia->info()));
}

void initUstawien(HWND hDlg)
{
	HWND hIloscTxt = GetDlgItem(hDlg, IDC_EDIT2);
	std::string iloscTxt = std::to_string(ptrUstawienia->pobierzRozmiarSiatki());
	std::wstring iloscWText;
	iloscWText.assign(iloscTxt.begin(), iloscTxt.end());
	SetWindowText(hIloscTxt, iloscWText.c_str());

	HWND hGlebokoscTxt = GetDlgItem(hDlg, IDC_EDIT3);
	std::string glebokoscTxt = std::to_string(ptrUstawienia->pobierzGlebokoscSzukania());
	std::wstring glebokoscWText;
	glebokoscWText.assign(glebokoscTxt.begin(), glebokoscTxt.end());
	SetWindowText(hGlebokoscTxt, glebokoscWText.c_str());

	//CheckDlgButton(hDlg, IDC_CHECK1, ptrUstawienia->czyZaczynaKomputer());
	CheckDlgButton(hDlg, IDC_CHECK2, ptrUstawienia->czyGraWartLosowymi());
}

//Procedura obsługi ustawień dla programu.
INT_PTR CALLBACK UstawieniaCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_ACTIVATE:
		initUstawien(hDlg);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK )
		{	
			//Przejąć wartości z ustawień
			USTAWIENIADIALOGRESULT * ldr = new USTAWIENIADIALOGRESULT; //TODO: check
			ZeroMemory(&ldr, sizeof(USTAWIENIADIALOGRESULT));
			pobranieUstawien(hDlg);
			ptrSiatka->ustawParametry(ptrUstawienia);
			ptrKolkoKrzyzyk->ustawParametry(ptrUstawienia);
			delete ldr;
			EndDialog(hDlg, LOWORD(wParam));
			HWND hParent = GetParent(hDlg);
			podajKtoWygral(hParent, ptrKolkoKrzyzyk);
			PostMessage(hParent, WM_PAINT, 0, 0);
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
			Narzedzia::printLog("Restart");
			ptrKolkoKrzyzyk->reset();
			if (ptrUstawienia->czyZaczynaKomputer())
			{
				ptrKolkoKrzyzyk->wykonajRuchKomp(OZnak);
			}
			EndDialog(hDlg, LOWORD(wParam));
			HWND hParent = GetParent(hDlg);
			podajKtoWygral(hParent, ptrKolkoKrzyzyk);
			PostMessage(hParent, WM_PAINT, 0, 0);
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
	std::wstring wygral = L"Remis";
	switch (ptrKolkoKrzyzyk->jakiStatus())
	{
	case GraczWygrywa:
		wygral = L"X wygral.";
		break;
	case KomputerWygrywa:
		wygral = L"O wygral.";
		break;
	case Remis:
		wygral = L"Remis.";
		break;
	default:
		wygral = L"Gramy";
		break;
	}
	SetWindowText(hWnd, (LPCWSTR)wygral.c_str());
}