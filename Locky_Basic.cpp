/*
Locky Terminal Basic

Copyright (C) 2023 Special-Niewbie Softwares

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation version 3.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "framework.h"
#include "Locky_Basic.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <UxTheme.h>
#include <commdlg.h>
#include <time.h>
#include <richedit.h>
#include <shellapi.h>

#define MAX_LOADSTRING 100
#define ID_USERNAME_EDIT 1
#define ID_USERNAME_LABEL 2
#define ID_USERNAME_OK_BUTTON 3
#define ID_PASSWORD_LENGTH_EDIT 4
#define ID_PASSWORD_LENGTH_LABEL 5
#define ID_PASSWORD_LENGTH_OK_BUTTON 6
#define ID_PASSWORD_LABEL 7
#define ID_PASSWORD_TEXT 8
#define MAX_PASSWORD_LENGTH 121
#define ID_SAVE_PASSWORD_YES_BUTTON 9
#define ID_SAVE_PASSWORD_NO_BUTTON 10
#define ID_EXIT_YES_BUTTON 11
#define ID_EXIT_NO_BUTTON 12
#define IDD_DIALOG1 13
#define ID_LOWERCASE_CHECKBOX 14
#define ID_UPPERCASE_CHECKBOX 15
#define ID_NUMBERS_CHECKBOX 16
#define ID_SYMBOLS_CHECKBOX 17
#define ID_SELECT_LENGTH_LABEL 18
#define ID_PASSWORD_LENGTH_TRACKBAR 19
#define ID_BACK_BUTTON 20
#define ID_BACK_BUTTON2 21

// Global variables:
HINSTANCE hInst;                    // current instance
WCHAR szTitle[MAX_LOADSTRING];      // Title bar text
WCHAR szWindowClass[MAX_LOADSTRING];// main window class name
WCHAR username[MAX_LOADSTRING];
WCHAR password[MAX_PASSWORD_LENGTH];

HMENU hLanguageMenu;
HWND hThankYou;
HWND hUsernameEdit = NULL;
HWND hUsernameLabel;
HWND hUsernameLabel2;
HWND hUsernameOkButton;
HWND hUsernameText;
HWND hSelectLengthLabel;
HWND hLowercaseCheckbox = NULL;
HWND hUppercaseCheckbox = NULL;
HWND hNumbersCheckbox = NULL;
HWND hSymbolsCheckbox = NULL;
HWND hTrackbar;
HWND hPasswordLengthTrackbar;
HWND hShowPassword;
HWND hPasswordLengthEdit = NULL;
HWND hPasswordLengthLabel;
HWND hPasswordLengthOkButton;
HWND hPasswordLabel;
HWND hPasswordText;
HWND hPasswordLabelQ;
HWND hSavePasswordYesButton;
HWND hSavePasswordNoButton;
HWND hExitYesButton;
HWND hExitNoButton;
HWND hDlg;
HWND hShowUsername;
HWND hBackButton;
HWND hBackButton2;

int currentTrackbarPosition = 0;
int lunghezza_password_iniziale = 8;

// Language variables:
wchar_t g_ThankYou[700] = L" I truly appreciate you using my products and if you find them useful for your privacy needs or daily usage, a small donation as a friendly gesture would \r\n       greatly help me to continue improving and providing valuable softwares / privacy tools for the future. I am grateful for your belief in my mission \r\n\t\t\t\t\t                   and for choosing to support me. \r\n \r\n - For more info on how to donate through PayPal or Ko-fi, visit my GitHub projects or click the 'Donate' button above. \r\n - To discover more projects, visit my GitHub profile at : \r\n \r\n\t\t\t\t\t         ***    https://github.com/Special-Niewbie    ***";
wchar_t g_usernameLabelText[256] = L"Enter your username:";
wchar_t g_passwordLengthLabelText[MAX_LOADSTRING] = L"Enter the length of the password (min 4, max 120):";
wchar_t g_enterUsernameText [MAX_LOADSTRING] = L"Please enter a username!";
wchar_t g_errorText[MAX_LOADSTRING] = L"Errore";

wchar_t g_hSelectLengthLabel[MAX_LOADSTRING] =  L"Select the CheckBoxes below to include in the Password:";
wchar_t g_hLowercaseCheckbox[MAX_LOADSTRING] =  L" -  Lowercase Letters";
wchar_t g_hUppercaseCheckbox[MAX_LOADSTRING] = L" -  UPPERCASE Letters";
wchar_t g_hNumbersCheckbox[MAX_LOADSTRING] = L" -  Numbers (0 - 9)";
wchar_t g_hSymbolsCheckbox[MAX_LOADSTRING] = L" -  Special Symbols";
wchar_t g_hPasswordLengthTrackbar[MAX_LOADSTRING] = L"Track-Bar to choose the length Password with the mouse:";

wchar_t g_errorIfLenght[MAX_LOADSTRING] = L"Password length must be a Number!";
wchar_t g_errorIfLenght4_120[MAX_LOADSTRING] = L"Password length must be between 4 and 120!";
wchar_t g_errorIfSelectCar[MAX_LOADSTRING] = L"You must to select at least one Font";

wchar_t g_hUsernameLabel2[MAX_LOADSTRING] = L" Username: ";
wchar_t g_hPasswordLabel[MAX_LOADSTRING] = L" Password: ";

wchar_t g_hSavePasswordYesButton[MAX_LOADSTRING] = L"Yes";
wchar_t g_hSavePasswordNoButton[MAX_LOADSTRING] = L"No";
wchar_t g_hPasswordLabelQ[MAX_LOADSTRING] = L" Do you want to save the Username and Password in a file? (yes/no):";

wchar_t g_lpstrTitle[MAX_LOADSTRING] = L"Save the file with Username and Password";
wchar_t g_FileWrittenUser[MAX_LOADSTRING] = L"Username: \n\n";
wchar_t g_FileWrittenPass[MAX_LOADSTRING] = L"\n\nPassword: \n\n";
wchar_t g_FileSaved[MAX_LOADSTRING] = L"Congratulations file successfully saved!";
wchar_t g_FileSavedComplete[MAX_LOADSTRING] = L"Save completed";

wchar_t g_RestartQ[MAX_LOADSTRING] = L"Do you want to continue and generate new Username / Password?";
wchar_t g_Closing[MAX_LOADSTRING] = L"Closing";

// Declarations with function prototypes included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PASSWORDGENERATORGUI2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PASSWORDGENERATORGUI2));

    MSG msg;
    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEXW));

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PASSWORDGENERATORGUI2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PASSWORDGENERATORGUI2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves the instance handle and creates the main window
//
//   COMMENTS:
//
//        In this function, the instance handle is saved in a global variable, and
//        the main window of the program is created and displayed.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Stores the instance handle in the global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   hLanguageMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDC_PASSWORDGENERATORGUI2));
   DrawMenuBar(hWnd);
   SetMenu(hWnd, hLanguageMenu);
   CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ENGLISH, MF_CHECKED);
   CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ITALIAN, MF_UNCHECKED);
   CheckMenuItem(hLanguageMenu, ID_LANGUAGE_SPANISH, MF_UNCHECKED);
   CheckMenuItem(hLanguageMenu, ID_LANGUAGE_JAPANESE, MF_UNCHECKED);
   CheckMenuItem(hLanguageMenu, ID_LANGUAGE_CHINESE, MF_UNCHECKED);
   CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ARABIC, MF_UNCHECKED);
   CheckMenuItem(hLanguageMenu, ID_LANGUAGE_RUSSIAN, MF_UNCHECKED);
   CheckMenuItem(hLanguageMenu, ID_LANGUAGE_HINDI, MF_UNCHECKED);
   MoveWindow(hWnd, 180, 120, 1280, 720, TRUE);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND - process application menu
//  WM_PAINT   - Draw the main window
//  WM_DESTROY - post a quit message and return
//
void ShowPasswordLengthScreen() {
    ShowWindow(hPasswordLengthLabel, SW_SHOW);
    ShowWindow(hPasswordLengthEdit, SW_SHOW);
    ShowWindow(hPasswordLengthOkButton, SW_SHOW);
}
void ShowPasswordScreen(WCHAR* username, WCHAR* password) {

    // Set the text of the labels with the username and generated password
    SetWindowText(hUsernameLabel, username);
    SetWindowText(hPasswordLabel, password);
}
void OnPasswordLengthTrackbarChange(HWND hDlg)
{
    int trackbarPosition = (int)SendMessage(hTrackbar, TBM_GETPOS, 0, 0);
    WCHAR trackbarPositionString[5];
    _itow_s(trackbarPosition, trackbarPositionString, 10);
    SetWindowText(hPasswordLengthEdit, trackbarPositionString);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZE:
    {
        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        int width = clientRect.right - clientRect.left;
        int height = clientRect.bottom - clientRect.top;
        int x = width - 120 - 20;
        int y = height - 40 - 20;
        int x2 = width - 230 - 40;
        int y2 = height - 40 - 20;
        int x3 = 20;
        int y3 = height - 101 - 20;
        int x4 = 20;
        int y4 = height - 31 - 20;

        // Resize the hUsernameOkButton button
        MoveWindow(hUsernameOkButton, x, y, 120, 40, TRUE);
        // Resize the hPasswordLengthOkButton button
        MoveWindow(hPasswordLengthOkButton, x, y, 120, 40, TRUE);
        // Resize the hSavePasswordYesButton button
        MoveWindow(hSavePasswordYesButton, x2, y2, 120, 40, TRUE);
        // Resize the hSavePasswordNoButton button
        MoveWindow(hSavePasswordNoButton, x, y, 120, 40, TRUE);
        // Resize the hPasswordLabelQ button
        MoveWindow(hPasswordLabelQ, x3, y3, 480, 20, TRUE);
        // Resize the hBackButton button
        MoveWindow(hBackButton, x4, y4, 100, 30, TRUE);
        MoveWindow(hBackButton2, x4, y4, 100, 30, TRUE);

    }
    break;
    case WM_HSCROLL:
    {
        int trackbarPosition = (int)SendMessage(hTrackbar, TBM_GETPOS, 0, 0);
        currentTrackbarPosition = trackbarPosition;
        OnPasswordLengthTrackbarChange(hWnd);
    }
    break;
    case WM_CREATE:
    {

        MoveWindow(hWnd, 0, 0, 1280, 720, TRUE);
        const wchar_t* inputString = g_usernameLabelText;
        size_t inputStringLength = wcslen(inputString);
        
        // Create the window for entering the username
        hThankYou = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", g_ThankYou, WS_CHILD | WS_VISIBLE | ES_MULTILINE, 120, 20, 1000, 140, hWnd, (HMENU)0, NULL, NULL);
        hUsernameLabel = CreateWindowEx(0, L"STATIC", g_usernameLabelText, WS_CHILD | WS_VISIBLE, 20, 200, 220, 20, hWnd, (HMENU)ID_USERNAME_LABEL, NULL, NULL);
        hUsernameEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE, 240, 200, 800, 20, hWnd, (HMENU)ID_USERNAME_EDIT, NULL, NULL);
        hUsernameOkButton = CreateWindowEx(0, L"BUTTON", L"OK", WS_CHILD | WS_VISIBLE, 1120, 600, 120, 40, hWnd, (HMENU)ID_USERNAME_OK_BUTTON, NULL, NULL);

        SendMessage(hThankYou, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
    }
    break;
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* pInfo = (MINMAXINFO*)lParam;
        pInfo->ptMinTrackSize.x = 900; // Set the desired minimum width to 900
        pInfo->ptMinTrackSize.y = 500; // Set the desired minimum height to 500
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int usernameLength = GetWindowTextLength(hUsernameEdit);
        if (usernameLength > MAX_LOADSTRING - 1) {
            usernameLength = MAX_LOADSTRING - 1;
        }

        // Handle menu selections:
        switch (wmId)
        {
        case ID_DONATION:
        {
            const wchar_t* donationURL = L"https://www.paypal.com/paypalme/CrisDonate";
            ShellExecute(hWnd, L"open", donationURL, NULL, NULL, SW_SHOWNORMAL);
        }
        break;
        case ID_LANGUAGE_ENGLISH:
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ENGLISH, MF_CHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ITALIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_SPANISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_JAPANESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_CHINESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ARABIC, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_RUSSIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_HINDI, MF_UNCHECKED);
            //First Menu Language section
            wcscpy_s(g_ThankYou, 700, L" I truly appreciate you using my products and if you find them useful for your privacy needs or daily usage, a small donation as a friendly gesture would \r\n       greatly help me to continue improving and providing valuable softwares / privacy tools for the future. I am grateful for your belief in my mission \r\n\t\t\t\t\t                   and for choosing to support me. \r\n \r\n - To Donate through PayPal and receive a `Special Gift` you can simply click the 'Donate' button on the top Menu. \r\n - For more info visit my GitHub profile at : \r\n \r\n\t\t\t\t\t         ***    https://github.com/Special-Niewbie    ***");
            wcscpy_s(g_usernameLabelText, 256, L"Enter your username:");
            wcscpy_s(g_passwordLengthLabelText, MAX_LOADSTRING, L"Enter the length of the password (min 4, max 120):");
            wcscpy_s(g_enterUsernameText, MAX_LOADSTRING, L"Please enter a username!");
            wcscpy_s(g_errorText, MAX_LOADSTRING, L"Error");
            //Second Menu Language section
            wcscpy_s(g_hSelectLengthLabel, MAX_LOADSTRING, L"Select the CheckBoxes below to include in the Password:");
            wcscpy_s(g_hLowercaseCheckbox, MAX_LOADSTRING, L" -  Lowercase Letters");
            wcscpy_s(g_hUppercaseCheckbox, MAX_LOADSTRING, L" -  UPPERCASE Letters");
            wcscpy_s(g_hNumbersCheckbox, MAX_LOADSTRING, L" -  Numbers (0 - 9)");
            wcscpy_s(g_hSymbolsCheckbox, MAX_LOADSTRING, L" -  Special Symbols");
            wcscpy_s(g_hPasswordLengthTrackbar, MAX_LOADSTRING, L"Track-Bar to choose the length Password with the mouse:");
            //Third Menu Language section
            wcscpy_s(g_errorIfLenght, MAX_LOADSTRING, L"Password length must be a Number!");
            wcscpy_s(g_errorIfLenght4_120, MAX_LOADSTRING, L"Password length must be between 4 and 120!");
            wcscpy_s(g_errorIfSelectCar, MAX_LOADSTRING, L"You must select at least one Font");
            //Fourth Menu Language section
            wcscpy_s(g_hUsernameLabel2, MAX_LOADSTRING, L" Username: ");
            wcscpy_s(g_hPasswordLabel, MAX_LOADSTRING, L" Password: ");
            wcscpy_s(g_hSavePasswordYesButton, MAX_LOADSTRING, L"Yes");
            wcscpy_s(g_hSavePasswordNoButton, MAX_LOADSTRING, L"No");
            wcscpy_s(g_hPasswordLabelQ,MAX_LOADSTRING, L" Do you want to save the Username and Password in a file? (yes/no):");
            //Fifth Menu Language section
            wcscpy_s(g_lpstrTitle, MAX_LOADSTRING, L"Save the file with Username and Password");
            wcscpy_s(g_FileWrittenUser, MAX_LOADSTRING, L"Username: \n\n");
            wcscpy_s(g_FileWrittenPass, MAX_LOADSTRING, L"\n\nPassword: \n\n");
            wcscpy_s(g_FileSaved, MAX_LOADSTRING, L"Congratulations file successfully saved!");
            wcscpy_s(g_FileSavedComplete, MAX_LOADSTRING, L"Save completed");

            wcscpy_s(g_RestartQ, MAX_LOADSTRING, L"Do you want to continue and generate new Username / Password?");
            wcscpy_s(g_Closing, MAX_LOADSTRING, L"Closing");
            
            // Set all labels and buttons - First section
            SetWindowText(hThankYou, g_ThankYou);
            SetWindowText(hUsernameLabel, g_usernameLabelText);
            SetWindowText(hPasswordLengthLabel, g_passwordLengthLabelText);

            // Set all labels and buttons - Second section
            SetWindowText(hSelectLengthLabel, g_hSelectLengthLabel);
            SetWindowText(hLowercaseCheckbox, g_hLowercaseCheckbox);
            SetWindowText(hUppercaseCheckbox, g_hUppercaseCheckbox);
            SetWindowText(hNumbersCheckbox, g_hNumbersCheckbox);
            SetWindowText(hSymbolsCheckbox, g_hSymbolsCheckbox);
            SetWindowText(hPasswordLengthTrackbar, g_hPasswordLengthTrackbar);

            // Set all labels and buttons - Third section
            SetWindowText(hUsernameLabel2, g_hUsernameLabel2);
            SetWindowText(hPasswordLabel, g_hPasswordLabel);
            SetWindowText(hSavePasswordYesButton, g_hSavePasswordYesButton);
            SetWindowText(hSavePasswordNoButton, g_hSavePasswordNoButton);
            SetWindowText(hPasswordLabelQ, g_hPasswordLabelQ);
            break;
        case ID_LANGUAGE_ITALIAN:
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ENGLISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ITALIAN, MF_CHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_SPANISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_JAPANESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_CHINESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ARABIC, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_RUSSIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_HINDI, MF_UNCHECKED);
            //First Menu Language section
            wcscpy_s(g_ThankYou, 800, L"  Apprezzo davvero l'utilizzo dei miei prodotti e se li trovi utili per le tue esigenze di privacy o per l'uso quotidiano, una piccola donazione come gesto\r\n\tamichevole mi aiuterebbe enormemente a continuare a migliorare e fornire software / strumenti per la privacy di valore per il futuro. \r\n\t\t\tSono grato per la tua fiducia nella mia missione e per aver scelto di supportarmi. \r\n \r\n - Per ulteriori info su come effettuare una donazione tramite PayPal o Ko-fi, visita i miei progetti su GitHub o clicca il pulsante 'Donazione' sopra. \r\n - Per scoprire altri progetti, visita il mio profilo GitHub su: \r\n \r\n\t\t\t\t\t         ***    https://github.com/Special-Niewbie    ***");
            wcscpy_s(g_usernameLabelText, 256, L"Inserisci il tuo nome utente:");
            wcscpy_s(g_passwordLengthLabelText, MAX_LOADSTRING, L"Inserisci la lunghezza della password (min 4, max 120):");
            wcscpy_s(g_enterUsernameText, MAX_LOADSTRING, L"Inserisci un nome utente!");
            wcscpy_s(g_errorText, MAX_LOADSTRING, L"Errore");
            //Second Menu Language section
            wcscpy_s(g_hSelectLengthLabel, MAX_LOADSTRING, L"Seleziona i CheckBox qui sotto da includere nella Password:");
            wcscpy_s(g_hLowercaseCheckbox, MAX_LOADSTRING, L" -  Lettere minuscole");
            wcscpy_s(g_hUppercaseCheckbox, MAX_LOADSTRING, L" -  Lettere MAIUSCOLE");
            wcscpy_s(g_hNumbersCheckbox, MAX_LOADSTRING, L" -  Numeri (0 - 9)");
            wcscpy_s(g_hSymbolsCheckbox, MAX_LOADSTRING, L" -  Simboli Speciali");
            wcscpy_s(g_hPasswordLengthTrackbar, MAX_LOADSTRING, L"Barra per scegliere la lunghezza della Password con il mouse:");
            //Third Menu Language section
            wcscpy_s(g_errorIfLenght, MAX_LOADSTRING, L"La lunghezza della password deve essere un Numero!");
            wcscpy_s(g_errorIfLenght4_120, MAX_LOADSTRING, L"La lunghezza della password deve essere compresa tra 4 e 120!");
            wcscpy_s(g_errorIfSelectCar, MAX_LOADSTRING, L"Devi selezionare almeno un tipo di carattere");
            //Fourth Menu Language section
            wcscpy_s(g_hUsernameLabel2, MAX_LOADSTRING, L" Nome Utente: ");
            wcscpy_s(g_hPasswordLabel, MAX_LOADSTRING, L" Password: ");
            wcscpy_s(g_hSavePasswordYesButton, MAX_LOADSTRING, L"Si");
            wcscpy_s(g_hSavePasswordNoButton, MAX_LOADSTRING, L"No");
            wcscpy_s(g_hPasswordLabelQ, MAX_LOADSTRING, L" Vuoi salvare il Nome Utente e Password in un file? (si/no):");
            //Fifth Menu Language section
            wcscpy_s(g_lpstrTitle, MAX_LOADSTRING, L"Salva il file con Nome Utente e Password");
            wcscpy_s(g_FileWrittenUser, MAX_LOADSTRING, L"Nome Utente: \n\n");
            wcscpy_s(g_FileWrittenPass, MAX_LOADSTRING, L"\n\nPassword: \n\n");
            wcscpy_s(g_FileSaved, MAX_LOADSTRING, L"Congratulazioni file salvato con successo!");
            wcscpy_s(g_FileSavedComplete, MAX_LOADSTRING, L"Salvataggio completato");

            wcscpy_s(g_RestartQ, MAX_LOADSTRING, L"Vuoi continuare e generare dei nuovi Username / Password ?");
            wcscpy_s(g_Closing, MAX_LOADSTRING, L"Chiusura del Software");
                       
            //Set all labels and buttons - First section
            SetWindowText(hThankYou, g_ThankYou);
            SetWindowText(hUsernameLabel, g_usernameLabelText);
            SetWindowText(hPasswordLengthLabel, g_passwordLengthLabelText);

            //Set all labels and buttons - Second section
            SetWindowText(hSelectLengthLabel, g_hSelectLengthLabel);
            SetWindowText(hLowercaseCheckbox, g_hLowercaseCheckbox);
            SetWindowText(hUppercaseCheckbox, g_hUppercaseCheckbox);
            SetWindowText(hNumbersCheckbox, g_hNumbersCheckbox);
            SetWindowText(hSymbolsCheckbox, g_hSymbolsCheckbox);
            SetWindowText(hPasswordLengthTrackbar, g_hPasswordLengthTrackbar);

            //Set all labels and buttons - Third section
            SetWindowText(hUsernameLabel2, g_hUsernameLabel2);
            SetWindowText(hPasswordLabel, g_hPasswordLabel);
            SetWindowText(hSavePasswordYesButton, g_hSavePasswordYesButton);
            SetWindowText(hSavePasswordNoButton, g_hSavePasswordNoButton);
            SetWindowText(hPasswordLabelQ, g_hPasswordLabelQ);
            break;
        case ID_LANGUAGE_SPANISH:
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ENGLISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ITALIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_SPANISH, MF_CHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_JAPANESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_CHINESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ARABIC, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_RUSSIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_HINDI, MF_UNCHECKED);
            //First Menu Language section
            wcscpy_s(g_ThankYou, 800, L"   Aprecio sinceramente que utilices mis productos y si los encuentras útiles para tus necesidades de privacidad o uso diario, una pequeña donación\r\n  como gesto amigable me ayudaría enormemente a seguir mejorando y proporcionando herramientas de software / privacidad valiosas para el futuro.\r\n\t\t\t\tEstoy agradecido por tu confianza en mi misión y por elegir apoyarme. \r\n \r\n - Para obtener más info sobre cómo hacer una donación a través de PayPal o Ko-fi, visita mis proyectos en GitHub o haz clic en el botón 'Donar' arriba. \r\n - Para descubrir más proyectos, visita mi perfil de GitHub en: \r\n \r\n\t\t\t\t\t         ***    https://github.com/Special-Niewbie    ***");
            wcscpy_s(g_usernameLabelText, 256, L"Ingrese su nombre de usuario:");
            wcscpy_s(g_passwordLengthLabelText, MAX_LOADSTRING, L"Introduzca la longitud de la Password (mín. 4, máx. 120):");
            wcscpy_s(g_enterUsernameText, MAX_LOADSTRING, L"¡Por favor, ingrese un nombre de usuario!");
            wcscpy_s(g_errorText, MAX_LOADSTRING, L"Error");
            //Second Menu Language section
            wcscpy_s(g_hSelectLengthLabel, MAX_LOADSTRING, L"Seleccione las casillas de verificación a continuación para incluir en la Password:");
            wcscpy_s(g_hLowercaseCheckbox, MAX_LOADSTRING, L" -  Letras minusculas");
            wcscpy_s(g_hUppercaseCheckbox, MAX_LOADSTRING, L" -  Letras Mayúsculas");
            wcscpy_s(g_hNumbersCheckbox, MAX_LOADSTRING, L" -  Números (0 - 9)");
            wcscpy_s(g_hSymbolsCheckbox, MAX_LOADSTRING, L" -  Símbolos Especiales");
            wcscpy_s(g_hPasswordLengthTrackbar, MAX_LOADSTRING, L"Barra para elegir la longitud de la Password con el ratón:");
            //Third Menu Language section
            wcscpy_s(g_errorIfLenght, MAX_LOADSTRING, L"¡La longitud de la password debe ser un número!");
            wcscpy_s(g_errorIfLenght4_120, MAX_LOADSTRING, L"¡La longitud de la password debe estar entre 4 y 120!");
            wcscpy_s(g_errorIfSelectCar, MAX_LOADSTRING, L"Debe seleccionar al menos una fuente");
            //Fourth Menu Language section
            wcscpy_s(g_hUsernameLabel2, MAX_LOADSTRING, L" Nombre de Usuario: ");
            wcscpy_s(g_hPasswordLabel, MAX_LOADSTRING, L" Password: ");
            wcscpy_s(g_hSavePasswordYesButton, MAX_LOADSTRING, L"Sí");
            wcscpy_s(g_hSavePasswordNoButton, MAX_LOADSTRING, L"No");
            wcscpy_s(g_hPasswordLabelQ, MAX_LOADSTRING, L" ¿Desea guardar el nombre de usuario y la password en un archivo? (Sí No):");
            //Fifth Menu Language section
            wcscpy_s(g_lpstrTitle, MAX_LOADSTRING, L"Guarde el archivo con nombre de usuario y Password");
            wcscpy_s(g_FileWrittenUser, MAX_LOADSTRING, L"Nombre de Usuario: \n\n");
            wcscpy_s(g_FileWrittenPass, MAX_LOADSTRING, L"\n\nPassword: \n\n");
            wcscpy_s(g_FileSaved, MAX_LOADSTRING, L"¡Felicitaciones, el archivo se guardó con éxito!");
            wcscpy_s(g_FileSavedComplete, MAX_LOADSTRING, L"Guardado completado");

            wcscpy_s(g_RestartQ, MAX_LOADSTRING, L"¿Desea continuar y generar un nuevo nombre de Usuario / Password?");
            wcscpy_s(g_Closing, MAX_LOADSTRING, L"Terminación del Software");

            //Set all labels and buttons - First section
            SetWindowText(hThankYou, g_ThankYou);
            SetWindowText(hUsernameLabel, g_usernameLabelText);
            SetWindowText(hPasswordLengthLabel, g_passwordLengthLabelText);

            //Set all labels and buttons - Second section
            SetWindowText(hSelectLengthLabel, g_hSelectLengthLabel);
            SetWindowText(hLowercaseCheckbox, g_hLowercaseCheckbox);
            SetWindowText(hUppercaseCheckbox, g_hUppercaseCheckbox);
            SetWindowText(hNumbersCheckbox, g_hNumbersCheckbox);
            SetWindowText(hSymbolsCheckbox, g_hSymbolsCheckbox);
            SetWindowText(hPasswordLengthTrackbar, g_hPasswordLengthTrackbar);

            //Set all labels and buttons - Third section
            SetWindowText(hUsernameLabel2, g_hUsernameLabel2);
            SetWindowText(hPasswordLabel, g_hPasswordLabel);
            SetWindowText(hSavePasswordYesButton, g_hSavePasswordYesButton);
            SetWindowText(hSavePasswordNoButton, g_hSavePasswordNoButton);
            SetWindowText(hPasswordLabelQ, g_hPasswordLabelQ);
            break;
        case ID_LANGUAGE_JAPANESE:
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ENGLISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ITALIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_SPANISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_JAPANESE, MF_CHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_CHINESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ARABIC, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_RUSSIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_HINDI, MF_UNCHECKED);
            //First Menu Language section
            wcscpy_s(g_ThankYou, 700, L"私の製品をご利用いただき、本当に感謝しています。プライバシーのニーズや日常の使用に役立つと思われる場合、友好的なジェスチャーとして\r\n の少額の寄付は、将来の改善や価値あるソフトウェア/プライバシーツールの提供に大いに役立ちます。私のミッションへの信念とサポートを選ん\r\n\t\t\t\t\t\tでいただき、心から感謝しています。 \r\n \r\n - PayPalやKo-fiを介して寄付を行う方法の詳細については、GitHubのプロジェクトをご覧いただくか、上記の「寄付」ボタンをクリックしてください。 \r\n - さらに多くのプロジェクトを見つけるには、GitHubプロフィールをご覧ください: \r\n \r\n\t\t\t\t\t         ***    https://github.com/Special-Niewbie    ***");
            wcscpy_s(g_usernameLabelText, 256, L"ユーザ名を入力してください：");
            wcscpy_s(g_passwordLengthLabelText, MAX_LOADSTRING, L"パスワードの長さを入力してください (最小 4、最大 120):");
            wcscpy_s(g_enterUsernameText, MAX_LOADSTRING, L"ユーザー名を入力して下さい！");
            wcscpy_s(g_errorText, MAX_LOADSTRING, L"エラー");
            //Second Menu Language section
            wcscpy_s(g_hSelectLengthLabel, MAX_LOADSTRING, L"以下のチェックボックスを選択して、パスワードに含めます。");
            wcscpy_s(g_hLowercaseCheckbox, MAX_LOADSTRING, L" -  小文字");
            wcscpy_s(g_hUppercaseCheckbox, MAX_LOADSTRING, L" -  大文字");
            wcscpy_s(g_hNumbersCheckbox, MAX_LOADSTRING, L" -  数字 (0 - 9)");
            wcscpy_s(g_hSymbolsCheckbox, MAX_LOADSTRING, L" -  特殊記号");
            wcscpy_s(g_hPasswordLengthTrackbar, MAX_LOADSTRING, L"マウスでパスワードの長さを選択するためのトラック バー:");
            //Third Menu Language section
            wcscpy_s(g_errorIfLenght, MAX_LOADSTRING, L"パスワードの長さは数値でなければなりません!");
            wcscpy_s(g_errorIfLenght4_120, MAX_LOADSTRING, L"パスワードの長さは 4 から 120 の間でなければなりません!");
            wcscpy_s(g_errorIfSelectCar, MAX_LOADSTRING, L"少なくとも 1 つのフォントを選択する必要があります");
            //Fourth Menu Language section
            wcscpy_s(g_hUsernameLabel2, MAX_LOADSTRING, L" ユーザー名: ");
            wcscpy_s(g_hPasswordLabel, MAX_LOADSTRING, L" パスワード： ");
            wcscpy_s(g_hSavePasswordYesButton, MAX_LOADSTRING, L"Yes");
            wcscpy_s(g_hSavePasswordNoButton, MAX_LOADSTRING, L"No");
            wcscpy_s(g_hPasswordLabelQ, MAX_LOADSTRING, L" ユーザー名とパスワードをファイルに保存しますか? （はい・いいえ）：");
            //Fifth Menu Language section
            wcscpy_s(g_lpstrTitle, MAX_LOADSTRING, L"ユーザー名とパスワードでファイルを保存します");
            wcscpy_s(g_FileWrittenUser, MAX_LOADSTRING, L"ユーザー名: \n\n");
            wcscpy_s(g_FileWrittenPass, MAX_LOADSTRING, L"\n\nパスワード： \n\n");
            wcscpy_s(g_FileSaved, MAX_LOADSTRING, L"おめでとうファイルが正常に保存されました!");
            wcscpy_s(g_FileSavedComplete, MAX_LOADSTRING, L"保存完了");

            wcscpy_s(g_RestartQ, MAX_LOADSTRING, L"続行して新しいユーザー名/パスワードを生成しますか?");
            wcscpy_s(g_Closing, MAX_LOADSTRING, L"閉鎖");

            //Set all labels and buttons - First section
            SetWindowText(hThankYou, g_ThankYou);
            SetWindowText(hUsernameLabel, g_usernameLabelText);
            SetWindowText(hPasswordLengthLabel, g_passwordLengthLabelText);

            //Set all labels and buttons - Second section
            SetWindowText(hSelectLengthLabel, g_hSelectLengthLabel);
            SetWindowText(hLowercaseCheckbox, g_hLowercaseCheckbox);
            SetWindowText(hUppercaseCheckbox, g_hUppercaseCheckbox);
            SetWindowText(hNumbersCheckbox, g_hNumbersCheckbox);
            SetWindowText(hSymbolsCheckbox, g_hSymbolsCheckbox);
            SetWindowText(hPasswordLengthTrackbar, g_hPasswordLengthTrackbar);

            //Set all labels and buttons - Third section
            SetWindowText(hUsernameLabel2, g_hUsernameLabel2);
            SetWindowText(hPasswordLabel, g_hPasswordLabel);
            SetWindowText(hSavePasswordYesButton, g_hSavePasswordYesButton);
            SetWindowText(hSavePasswordNoButton, g_hSavePasswordNoButton);
            SetWindowText(hPasswordLabelQ, g_hPasswordLabelQ);
            break;
        case ID_LANGUAGE_CHINESE:
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ENGLISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ITALIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_SPANISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_JAPANESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_CHINESE, MF_CHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ARABIC, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_RUSSIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_HINDI, MF_UNCHECKED);
            //First Menu Language section
            wcscpy_s(g_ThankYou, 700, L"非常感谢您使用我的产品。如果您发现它们对于您的隐私需求或日常使用非常有用，作为友好的表示，您可以进行少量捐赠，这\r\n    将极大地帮助我继续改进并提供有价值的软件/隐私工具以应对未来的挑战。我非常感激您对我的使命的信任并选择支持我。 \r\n \r\n - 有关如何通过PayPal或Ko-fi进行捐赠的更多信息，请访问我的GitHub项目或点击上方的“捐赠”按钮。 \r\n - 要发现更多项目，请访问我的GitHub个人资料页面： \r\n \r\n\t\t\t\t\t         ***    https://github.com/Special-Niewbie    ***");
            wcscpy_s(g_usernameLabelText, MAX_LOADSTRING, L"輸入你的用戶名：");
            wcscpy_s(g_passwordLengthLabelText, MAX_LOADSTRING, L"輸入密碼長度（最小 4，最大 120）：");
            wcscpy_s(g_enterUsernameText, MAX_LOADSTRING, L"請填入一個用戶名！");
            wcscpy_s(g_errorText, MAX_LOADSTRING, L"錯誤");
            //Second Menu Language section
            wcscpy_s(g_hSelectLengthLabel, MAX_LOADSTRING, L"選擇下面的複選框以包含在密碼中：");
            wcscpy_s(g_hLowercaseCheckbox, MAX_LOADSTRING, L" -  小寫字母");
            wcscpy_s(g_hUppercaseCheckbox, MAX_LOADSTRING, L" -  大寫字母");
            wcscpy_s(g_hNumbersCheckbox, MAX_LOADSTRING, L" -  數字 (0 - 9)");
            wcscpy_s(g_hSymbolsCheckbox, MAX_LOADSTRING, L" -  特殊符號");
            wcscpy_s(g_hPasswordLengthTrackbar, MAX_LOADSTRING, L"Track-Bar 用鼠標選擇密碼長度：");
            //Third Menu Language section
            wcscpy_s(g_errorIfLenght, MAX_LOADSTRING, L"密碼長度必須是數字！");
            wcscpy_s(g_errorIfLenght4_120, MAX_LOADSTRING, L"密碼長度必須在 4 到 120 之間！");
            wcscpy_s(g_errorIfSelectCar, MAX_LOADSTRING, L"您必須至少選擇一種字體");
            //Fourth Menu Language section
            wcscpy_s(g_hUsernameLabel2, MAX_LOADSTRING, L" 用戶名： ");
            wcscpy_s(g_hPasswordLabel, MAX_LOADSTRING, L" 密碼： ");
            wcscpy_s(g_hSavePasswordYesButton, MAX_LOADSTRING, L"是的");
            wcscpy_s(g_hSavePasswordNoButton, MAX_LOADSTRING, L"不");
            wcscpy_s(g_hPasswordLabelQ, MAX_LOADSTRING, L" 您想將用戶名和密碼保存在文件中嗎？ （是/否）：");
            //Fifth Menu Language section
            wcscpy_s(g_lpstrTitle, MAX_LOADSTRING, L"使用用戶名和密碼保存文件");
            wcscpy_s(g_FileWrittenUser, MAX_LOADSTRING, L"用戶名： \n\n");
            wcscpy_s(g_FileWrittenPass, MAX_LOADSTRING, L"\n\n密碼： \n\n");
            wcscpy_s(g_FileSaved, MAX_LOADSTRING, L"恭喜文件保存成功！");
            wcscpy_s(g_FileSavedComplete, MAX_LOADSTRING, L"保存完成");

            wcscpy_s(g_RestartQ, MAX_LOADSTRING, L"您要繼續並生成新的用戶名/密碼嗎？");
            wcscpy_s(g_Closing, MAX_LOADSTRING, L"關閉");

            //Set all labels and buttons - First section
            SetWindowText(hThankYou, g_ThankYou);
            SetWindowText(hUsernameLabel, g_usernameLabelText);
            SetWindowText(hPasswordLengthLabel, g_passwordLengthLabelText);

            //Set all labels and buttons - Second section
            SetWindowText(hSelectLengthLabel, g_hSelectLengthLabel);
            SetWindowText(hLowercaseCheckbox, g_hLowercaseCheckbox);
            SetWindowText(hUppercaseCheckbox, g_hUppercaseCheckbox);
            SetWindowText(hNumbersCheckbox, g_hNumbersCheckbox);
            SetWindowText(hSymbolsCheckbox, g_hSymbolsCheckbox);
            SetWindowText(hPasswordLengthTrackbar, g_hPasswordLengthTrackbar);

            //Set all labels and buttons - Third section
            SetWindowText(hUsernameLabel2, g_hUsernameLabel2);
            SetWindowText(hPasswordLabel, g_hPasswordLabel);
            SetWindowText(hSavePasswordYesButton, g_hSavePasswordYesButton);
            SetWindowText(hSavePasswordNoButton, g_hSavePasswordNoButton);
            SetWindowText(hPasswordLabelQ, g_hPasswordLabelQ);
            break;
        case ID_LANGUAGE_ARABIC:
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ENGLISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ITALIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_SPANISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_JAPANESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_CHINESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ARABIC, MF_CHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_RUSSIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_HINDI, MF_UNCHECKED);
            //First Menu Language section
            wcscpy_s(g_ThankYou, 700, L" أقدر حقا استخدامك لمنتجاتي، وإذا وجدتها مفيدة لاحتياجاتك في الخصوصية أو الاستخدام اليومي، فإن التبرع بمبلغ صغير كنوع من اللطف سيساعدني كثيرًا في مواصلة التحسين وتوفير أدوات برمجية / خصوصية قيمة للمستقبل. أنا ممتن لثقتك في مهمتي واختيارك لدعمي. \r\n \r\n - لمزيد من المعلومات حول كيفية التبرع عبر PayPal أو Ko-fi، قم بزيارة مشاريعي على GitHub أو انقر فوق زر 'تبرع' أعلاه. \r\n - لاكتشاف المزيد من المشاريع، قم بزيارة ملفي الشخصي على GitHub عبر الرابط التالي: \r\n \r\n\t\t\t\t\t         ***    https://github.com/Special-Niewbie    ***");
            wcscpy_s(g_usernameLabelText, 256, L"أدخل اسم المستخدم الخاص بك:");
            wcscpy_s(g_passwordLengthLabelText, MAX_LOADSTRING, L"أدخل طول كلمة المرور (الحد الأدنى 4 ، الحد الأقصى 120):");
            wcscpy_s(g_enterUsernameText, MAX_LOADSTRING, L"الرجاء ادخال اسم المستخدم!");
            wcscpy_s(g_errorText, MAX_LOADSTRING, L"Error");
            //Second Menu Language section
            wcscpy_s(g_hSelectLengthLabel, MAX_LOADSTRING, L"حدد خانات الاختيار أدناه لتضمينها في كلمة المرور:");
            wcscpy_s(g_hLowercaseCheckbox, MAX_LOADSTRING, L" -  أحرف صغيرة");
            wcscpy_s(g_hUppercaseCheckbox, MAX_LOADSTRING, L" -  الأحرف الكبيرة");
            wcscpy_s(g_hNumbersCheckbox, MAX_LOADSTRING, L" -  (أرقام (0 - 9");
            wcscpy_s(g_hSymbolsCheckbox, MAX_LOADSTRING, L" -  الرموز الخاصة");
            wcscpy_s(g_hPasswordLengthTrackbar, MAX_LOADSTRING, L"شريط المسار لاختيار طول كلمة المرور بالماوس:");
            //Third Menu Language section
            wcscpy_s(g_errorIfLenght, MAX_LOADSTRING, L"يجب أن يكون طول كلمة المرور رقمًا!");
            wcscpy_s(g_errorIfLenght4_120, MAX_LOADSTRING, L"يجب أن يكون طول كلمة المرور بين 4 و 120!");
            wcscpy_s(g_errorIfSelectCar, MAX_LOADSTRING, L"يجب تحديد خط واحد على الأقل");
            //Fourth Menu Language section
            wcscpy_s(g_hUsernameLabel2, MAX_LOADSTRING, L" اسم المستخدم: ");
            wcscpy_s(g_hPasswordLabel, MAX_LOADSTRING, L" كلمة المرور: ");
            wcscpy_s(g_hSavePasswordYesButton, MAX_LOADSTRING, L"نعم");
            wcscpy_s(g_hSavePasswordNoButton, MAX_LOADSTRING, L"رقم");
            wcscpy_s(g_hPasswordLabelQ, MAX_LOADSTRING, L" هل تريد حفظ اسم المستخدم وكلمة المرور في ملف؟ (نعم / لا):");
            //Fifth Menu Language section
            wcscpy_s(g_lpstrTitle, MAX_LOADSTRING, L"احفظ الملف باسم المستخدم وكلمة المرور");
            wcscpy_s(g_FileWrittenUser, MAX_LOADSTRING, L"اسم المستخدم: \n\n");
            wcscpy_s(g_FileWrittenPass, MAX_LOADSTRING, L"\n\nكلمة المرور: \n\n");
            wcscpy_s(g_FileSaved, MAX_LOADSTRING, L"تم حفظ ملف التهاني بنجاح!");
            wcscpy_s(g_FileSavedComplete, MAX_LOADSTRING, L"تم الحفظ");

            wcscpy_s(g_RestartQ, MAX_LOADSTRING, L"هل تريد المتابعة وإنشاء اسم مستخدم / كلمة مرور جديدة؟");
            wcscpy_s(g_Closing, MAX_LOADSTRING, L"إغلاق");

            //Set all labels and buttons - First section
            SetWindowText(hThankYou, g_ThankYou);
            SetWindowText(hUsernameLabel, g_usernameLabelText);
            SetWindowText(hPasswordLengthLabel, g_passwordLengthLabelText);

            //Set all labels and buttons - Second section
            SetWindowText(hSelectLengthLabel, g_hSelectLengthLabel);
            SetWindowText(hLowercaseCheckbox, g_hLowercaseCheckbox);
            SetWindowText(hUppercaseCheckbox, g_hUppercaseCheckbox);
            SetWindowText(hNumbersCheckbox, g_hNumbersCheckbox);
            SetWindowText(hSymbolsCheckbox, g_hSymbolsCheckbox);
            SetWindowText(hPasswordLengthTrackbar, g_hPasswordLengthTrackbar);

            //Set all labels and buttons - Third section
            SetWindowText(hUsernameLabel2, g_hUsernameLabel2);
            SetWindowText(hPasswordLabel, g_hPasswordLabel);
            SetWindowText(hSavePasswordYesButton, g_hSavePasswordYesButton);
            SetWindowText(hSavePasswordNoButton, g_hSavePasswordNoButton);
            SetWindowText(hPasswordLabelQ, g_hPasswordLabelQ);
            break;
        case ID_LANGUAGE_RUSSIAN:
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ENGLISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ITALIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_SPANISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_JAPANESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_CHINESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ARABIC, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_RUSSIAN, MF_CHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_HINDI, MF_UNCHECKED);
            //First Menu Language section
            wcscpy_s(g_ThankYou, 900, L"          Я искренне благодарен за использование моих продуктов, и если они оказались полезными для ваших потребностей в\r\n         конфиденциальности или повседневного использования, небольшое пожертвование в качестве дружественного жеста\r\n   существенно поможет мне в дальнейшем совершенствовании и предоставлении ценных программных средств / инструментов\r\n\t\tконфиденциальности. Я благодарен за ваше доверие к моей миссии и выбор в поддержке меня. \r\n \r\n - Для получения дополнительной информации о том, как сделать пожертвование через PayPal или Ko-fi, посетите мои проекты на\r\n   GitHub или нажмите кнопку 'Пожертвовать' выше. \r\n - Чтобы открыть для себя больше проектов, посетите мой профиль на GitHub по ссылке: \r\n \r\n\t\t\t\t\t         ***    https://github.com/Special-Niewbie    ***");
            wcscpy_s(g_usernameLabelText, 256, L"Введите имя пользователя:");
            wcscpy_s(g_passwordLengthLabelText, MAX_LOADSTRING, L"Введите длину пароля (мин. 4, макс. 120):");
            wcscpy_s(g_enterUsernameText, MAX_LOADSTRING, L"Пожалуйста введите имя пользователя!");
            wcscpy_s(g_errorText, MAX_LOADSTRING, L"Ошибка");
            //Second Menu Language section
            wcscpy_s(g_hSelectLengthLabel, MAX_LOADSTRING, L"Установите флажки ниже, чтобы включить их в пароль:");
            wcscpy_s(g_hLowercaseCheckbox, MAX_LOADSTRING, L" -  Строчные буквы");
            wcscpy_s(g_hUppercaseCheckbox, MAX_LOADSTRING, L" -  Заглавные буквы");
            wcscpy_s(g_hNumbersCheckbox, MAX_LOADSTRING, L" -  Числа (0 - 9)");
            wcscpy_s(g_hSymbolsCheckbox, MAX_LOADSTRING, L" -  Специальные Символы");
            wcscpy_s(g_hPasswordLengthTrackbar, MAX_LOADSTRING, L"Track-Bar для выбора длины пароля с помощью мыши:");
            //Third Menu Language section
            wcscpy_s(g_errorIfLenght, MAX_LOADSTRING, L"Длина пароля должна быть числом!");
            wcscpy_s(g_errorIfLenght4_120, MAX_LOADSTRING, L"Длина пароля должна быть от 4 до 120!");
            wcscpy_s(g_errorIfSelectCar, MAX_LOADSTRING, L"Вы должны выбрать хотя бы один шрифт");
            //Fourth Menu Language section
            wcscpy_s(g_hUsernameLabel2, MAX_LOADSTRING, L" Имя пользователя: ");
            wcscpy_s(g_hPasswordLabel, MAX_LOADSTRING, L" Пароль: ");
            wcscpy_s(g_hSavePasswordYesButton, MAX_LOADSTRING, L"Да");
            wcscpy_s(g_hSavePasswordNoButton, MAX_LOADSTRING, L"Нет");
            wcscpy_s(g_hPasswordLabelQ, MAX_LOADSTRING, L" Вы хотите сохранить имя пользователя и пароль в файле? (да нет):");
            //Fifth Menu Language section
            wcscpy_s(g_lpstrTitle, MAX_LOADSTRING, L"Сохраните файл с именем пользователя и паролем");
            wcscpy_s(g_FileWrittenUser, MAX_LOADSTRING, L"Имя пользователя: \n\n");
            wcscpy_s(g_FileWrittenPass, MAX_LOADSTRING, L"\n\nПароль: \n\n");
            wcscpy_s(g_FileSaved, MAX_LOADSTRING, L"Поздравляем, файл успешно сохранен!");
            wcscpy_s(g_FileSavedComplete, MAX_LOADSTRING, L"Сохранить завершено");

            wcscpy_s(g_RestartQ, MAX_LOADSTRING, L"Вы хотите продолжить и сгенерировать новое имя пользователя/пароль?");
            wcscpy_s(g_Closing, MAX_LOADSTRING, L"Закрытие");

            //Set all labels and buttons - First section
            SetWindowText(hThankYou, g_ThankYou);
            SetWindowText(hUsernameLabel, g_usernameLabelText);
            SetWindowText(hPasswordLengthLabel, g_passwordLengthLabelText);

            //Set all labels and buttons - Second section
            SetWindowText(hSelectLengthLabel, g_hSelectLengthLabel);
            SetWindowText(hLowercaseCheckbox, g_hLowercaseCheckbox);
            SetWindowText(hUppercaseCheckbox, g_hUppercaseCheckbox);
            SetWindowText(hNumbersCheckbox, g_hNumbersCheckbox);
            SetWindowText(hSymbolsCheckbox, g_hSymbolsCheckbox);
            SetWindowText(hPasswordLengthTrackbar, g_hPasswordLengthTrackbar);

            //Set all labels and buttons - Third section
            SetWindowText(hUsernameLabel2, g_hUsernameLabel2);
            SetWindowText(hPasswordLabel, g_hPasswordLabel);
            SetWindowText(hSavePasswordYesButton, g_hSavePasswordYesButton);
            SetWindowText(hSavePasswordNoButton, g_hSavePasswordNoButton);
            SetWindowText(hPasswordLabelQ, g_hPasswordLabelQ);
            break;
        case ID_LANGUAGE_HINDI:
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ENGLISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ITALIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_SPANISH, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_JAPANESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_CHINESE, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_ARABIC, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_RUSSIAN, MF_UNCHECKED);
            CheckMenuItem(hLanguageMenu, ID_LANGUAGE_HINDI, MF_CHECKED);
            //First Menu Language section
            wcscpy_s(g_ThankYou, 750, L" मैं आपके मेरे उत्पादों का उपयोग करने की सचमुच आभारी हूँ और यदि आप इन्हें अपनी गोपनीयता आवश्यकताओं या दैनिक उपयोग के लिए उपयोगी पाते हैं, तो एक छोटे दान के रूप में मित्रता के रूप में आपकी मदद करेगा \r\n       मुझे और आपको भविष्य के लिए महत्वपूर्ण सॉफ़्टवेयर / गोपनीयता उपकरणों की सुविधा और सुनिश्चित करने के लिए। मैं अपनी मिशन में आपके विश्वास और मेरे समर्थन के लिए आभारी हूँ। \r\n \r\n - अधिक जानकारी के लिए कैसे PayPal या Ko-fi के माध्यम से डोनेट करें, मेरे GitHub परियोजनाओं का दौरा करें या ऊपर के 'डोनेट' बटन पर क्लिक करें। \r\n - अधिक परियोजनाओं की खोज करने के लिए, मेरा GitHub प्रोफ़ाइल देखें: \r\n \r\n\t\t\t\t\t         ***    https://github.com/Special-Niewbie    ***");
            wcscpy_s(g_usernameLabelText, 256, L"अपने उपयोगकर्ता नाम दर्ज करें  :");
            wcscpy_s(g_passwordLengthLabelText, MAX_LOADSTRING, L"पासवर्ड की लंबाई दर्ज करें (न्यूनतम 4, अधिकतम 120):");
            wcscpy_s(g_enterUsernameText, MAX_LOADSTRING, L"कृपया उपयोगकर्तानाम डालें!");
            wcscpy_s(g_errorText, MAX_LOADSTRING, L"गलती");
            //Second Menu Language section
            wcscpy_s(g_hSelectLengthLabel, MAX_LOADSTRING, L"पासवर्ड में शामिल करने के लिए नीचे दिए गए चेकबॉक्स चुनें:");
            wcscpy_s(g_hLowercaseCheckbox, MAX_LOADSTRING, L" -  छोटे अक्षर");
            wcscpy_s(g_hUppercaseCheckbox, MAX_LOADSTRING, L" -  बड़ी वर्तनी के अक्षर");
            wcscpy_s(g_hNumbersCheckbox, MAX_LOADSTRING, L" -  नंबर (0 - 9)");
            wcscpy_s(g_hSymbolsCheckbox, MAX_LOADSTRING, L" -  विशेष प्रतीक");
            wcscpy_s(g_hPasswordLengthTrackbar, MAX_LOADSTRING, L"ट्रैक-बार माउस के साथ लंबाई पासवर्ड चुनने के लिए:");
            //Third Menu Language section
            wcscpy_s(g_errorIfLenght, MAX_LOADSTRING, L"पासवर्ड की लंबाई एक संख्या होनी चाहिए!");
            wcscpy_s(g_errorIfLenght4_120, MAX_LOADSTRING, L"पासवर्ड की लंबाई 4 और 120 के बीच होनी चाहिए!");
            wcscpy_s(g_errorIfSelectCar, MAX_LOADSTRING, L"आपको कम से कम एक फ़ॉन्ट चुनना होगा");
            //Fourth Menu Language section
            wcscpy_s(g_hUsernameLabel2, MAX_LOADSTRING, L" उपयोगकर्ता नाम: ");
            wcscpy_s(g_hPasswordLabel, MAX_LOADSTRING, L" पासवर्ड: ");
            wcscpy_s(g_hSavePasswordYesButton, MAX_LOADSTRING, L"हाँ");
            wcscpy_s(g_hSavePasswordNoButton, MAX_LOADSTRING, L"नहीं");
            wcscpy_s(g_hPasswordLabelQ, MAX_LOADSTRING, L" क्या आप यूजरनेम और पासवर्ड को फाइल में सेव करना चाहते हैं? (हाँ नही):");
            //Fifth Menu Language section
            wcscpy_s(g_lpstrTitle, MAX_LOADSTRING, L"फ़ाइल को उपयोगकर्ता नाम और पासवर्ड से सहेजें");
            wcscpy_s(g_FileWrittenUser, MAX_LOADSTRING, L"उपयोगकर्ता नाम: \n\n");
            wcscpy_s(g_FileWrittenPass, MAX_LOADSTRING, L"\n\nपासवर्ड: \n\n");
            wcscpy_s(g_FileSaved, MAX_LOADSTRING, L"बधाई फ़ाइल सफलतापूर्वक सहेजी गई!");
            wcscpy_s(g_FileSavedComplete, MAX_LOADSTRING, L"सेव पूरा हुआ");

            wcscpy_s(g_RestartQ, MAX_LOADSTRING, L"क्या आप जारी रखना चाहते हैं और नया उपयोगकर्ता नाम/पासवर्ड बनाना चाहते हैं?");
            wcscpy_s(g_Closing, MAX_LOADSTRING, L"समापन");

            //Set all labels and buttons - First section
            SetWindowText(hThankYou, g_ThankYou);
            SetWindowText(hUsernameLabel, g_usernameLabelText);
            SetWindowText(hPasswordLengthLabel, g_passwordLengthLabelText);

            //Set all labels and buttons - Second section
            SetWindowText(hSelectLengthLabel, g_hSelectLengthLabel);
            SetWindowText(hLowercaseCheckbox, g_hLowercaseCheckbox);
            SetWindowText(hUppercaseCheckbox, g_hUppercaseCheckbox);
            SetWindowText(hNumbersCheckbox, g_hNumbersCheckbox);
            SetWindowText(hSymbolsCheckbox, g_hSymbolsCheckbox);
            SetWindowText(hPasswordLengthTrackbar, g_hPasswordLengthTrackbar);

            //Set all labels and buttons - Third section
            SetWindowText(hUsernameLabel2, g_hUsernameLabel2);
            SetWindowText(hPasswordLabel, g_hPasswordLabel);
            SetWindowText(hSavePasswordYesButton, g_hSavePasswordYesButton);
            SetWindowText(hSavePasswordNoButton, g_hSavePasswordNoButton);
            SetWindowText(hPasswordLabelQ, g_hPasswordLabelQ);
            break;
        case ID_USERNAME_OK_BUTTON:
        {
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;
            int x = width - 120 - 20;
            int y = height - 40 - 20;
            int x2 = width - 230 - 40;
            int y2 = height - 40 - 20;
            int x3 = 20;
            int y3 = height - 101 - 20;
            int x4 = 20;
            int y4 = height - 31 - 20;
           

            WCHAR username[MAX_LOADSTRING];
            GetWindowText(hUsernameEdit, username, MAX_LOADSTRING);
            if (wcscmp(username, L"") == 0 || wcslen(username) == 0)
            {
               MessageBox(NULL, g_usernameLabelText, g_errorText, MB_ICONWARNING | MB_OK);
               return 0;
            }

            // Hide the elements of the first screen
            ShowWindow(hThankYou, SW_HIDE);
            ShowWindow(hUsernameLabel, SW_HIDE);
            ShowWindow(hUsernameOkButton, SW_HIDE);
            ShowWindow(hUsernameEdit, SW_HIDE);
            ShowPasswordLengthScreen();
            //Checkbox
            hSelectLengthLabel = CreateWindowEx(0, L"STATIC", g_hSelectLengthLabel, WS_CHILD | WS_VISIBLE, 20, 20, 480, 30, hWnd, (HMENU)ID_SELECT_LENGTH_LABEL, NULL, NULL);
            hLowercaseCheckbox = CreateWindowEx(0, L"BUTTON", g_hLowercaseCheckbox, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 50, 180, 20, hWnd, (HMENU)ID_LOWERCASE_CHECKBOX, NULL, NULL);
            SendMessage(hLowercaseCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            hUppercaseCheckbox = CreateWindowEx(0, L"BUTTON", g_hUppercaseCheckbox, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 70, 180, 20, hWnd, (HMENU)ID_UPPERCASE_CHECKBOX, NULL, NULL);
            SendMessage(hUppercaseCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            hNumbersCheckbox = CreateWindowEx(0, L"BUTTON", g_hNumbersCheckbox, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 90, 180, 20, hWnd, (HMENU)ID_NUMBERS_CHECKBOX, NULL, NULL);
            SendMessage(hNumbersCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            hSymbolsCheckbox = CreateWindowEx(0, L"BUTTON", g_hSymbolsCheckbox, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 110, 180, 20, hWnd, (HMENU)ID_SYMBOLS_CHECKBOX, NULL, NULL);
            SendMessage(hSymbolsCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            //// Enter the length of the password (min 4, max 120):
            hPasswordLengthLabel = CreateWindowEx(0, L"STATIC", g_passwordLengthLabelText, WS_CHILD | WS_VISIBLE, 20, 160, 380, 20, hWnd, (HMENU)ID_PASSWORD_LENGTH_LABEL, NULL, NULL);
            hPasswordLengthEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE, 400, 160, 50, 20, hWnd, (HMENU)ID_PASSWORD_LENGTH_EDIT, NULL, NULL);
            hPasswordLengthTrackbar = CreateWindowEx(0, L"STATIC", g_hPasswordLengthTrackbar, WS_CHILD | WS_VISIBLE, 460, 260, 420, 20, hWnd, (HMENU)ID_PASSWORD_LENGTH_TRACKBAR, NULL, NULL);
            hTrackbar = CreateWindowEx(0, TRACKBAR_CLASS, L"", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE, 360, 300, 600, 30, hWnd, (HMENU)WM_HSCROLL, hInst, NULL);
            hPasswordLengthOkButton = CreateWindowEx(0, L"BUTTON", L"OK", WS_CHILD | WS_VISIBLE, 1124, 601, 120, 40, hWnd, (HMENU)ID_PASSWORD_LENGTH_OK_BUTTON, NULL, NULL);
            hBackButton = CreateWindowEx(0, L"BUTTON", L" <---- ", WS_CHILD | WS_VISIBLE, 20, 610, 100, 30, hWnd, (HMENU)ID_BACK_BUTTON, hInst, NULL);

            InvalidateRect(hWnd, NULL, TRUE);
            // Resize the hUsernameOkButton button
            MoveWindow(hUsernameOkButton, x, y, 120, 40, TRUE);
            // Resize the hPasswordLengthOkButton button
            MoveWindow(hPasswordLengthOkButton, x, y, 120, 40, TRUE);
            // Resize the hPasswordLabelQ button
            MoveWindow(hPasswordLabelQ, x3, y3, 480, 20, TRUE);
            // Resize the hBackButton button
            MoveWindow(hBackButton, x4, y4, 100, 30, TRUE);
            MoveWindow(hBackButton2, x4, y4, 100, 30, TRUE);

            // Initialize the scroll bar
            SendMessage(hTrackbar, TBM_SETRANGE, TRUE, MAKELPARAM(4, 120));
            SendMessage(hTrackbar, TBM_SETPOS, TRUE, lunghezza_password_iniziale);
            SendMessage(hTrackbar, TBM_SETTICFREQ, 4, 0);
            break;
        }
        case ID_LOWERCASE_CHECKBOX:
            if (BST_CHECKED == SendMessage(hLowercaseCheckbox, BM_GETCHECK, 0, 0))
                SendMessage(hLowercaseCheckbox, BM_SETCHECK, BST_UNCHECKED, 0);
            else
                SendMessage(hLowercaseCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            break;
        case ID_UPPERCASE_CHECKBOX:
            if (BST_CHECKED == SendMessage(hUppercaseCheckbox, BM_GETCHECK, 0, 0))
                SendMessage(hUppercaseCheckbox, BM_SETCHECK, BST_UNCHECKED, 0);
            else
                SendMessage(hUppercaseCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            break;
        case ID_NUMBERS_CHECKBOX:
            if (BST_CHECKED == SendMessage(hNumbersCheckbox, BM_GETCHECK, 0, 0))
                SendMessage(hNumbersCheckbox, BM_SETCHECK, BST_UNCHECKED, 0);
            else
                SendMessage(hNumbersCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            break;
        case ID_SYMBOLS_CHECKBOX:
            if (BST_CHECKED == SendMessage(hSymbolsCheckbox, BM_GETCHECK, 0, 0))
                SendMessage(hSymbolsCheckbox, BM_SETCHECK, BST_UNCHECKED, 0);
            else
                SendMessage(hSymbolsCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            break;
        // Check if the button pressed is the "Back" button
        case ID_BACK_BUTTON:
        {
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;
            int x = width - 120 - 20;
            int y = height - 40 - 20;
            int x2 = width - 230 - 40;
            int y2 = height - 40 - 20;
            int x3 = 20;
            int y3 = height - 101 - 20;
            int x4 = 20;
            int y4 = height - 31 - 20;

            // Hide the elements of the second screen
            DestroyWindow(hSelectLengthLabel);
            DestroyWindow(hLowercaseCheckbox);
            DestroyWindow(hUppercaseCheckbox);
            DestroyWindow(hNumbersCheckbox);
            DestroyWindow(hSymbolsCheckbox);
            DestroyWindow(hPasswordLengthLabel);
            DestroyWindow(hPasswordLengthEdit);
            DestroyWindow(hPasswordLengthOkButton);
            DestroyWindow(hPasswordLengthTrackbar);
            DestroyWindow(hTrackbar);
            DestroyWindow(hBackButton);
            DestroyWindow(hBackButton2);

            // Show the elements of the first screen
            ShowWindow(hThankYou, SW_SHOW);
            ShowWindow(hUsernameLabel, SW_SHOW);
            ShowWindow(hUsernameEdit, SW_SHOW);
            ShowWindow(hUsernameOkButton, SW_SHOW);
            
            InvalidateRect(hWnd, NULL, TRUE);
            // Resize the hUsernameOkButton button
            MoveWindow(hUsernameOkButton, x, y, 120, 40, TRUE);
            // Resize the hPasswordLengthOkButton button
            MoveWindow(hPasswordLengthOkButton, x, y, 120, 40, TRUE);
            // Resize the hPasswordLabelQ button
            MoveWindow(hPasswordLabelQ, x3, y3, 480, 20, TRUE);
            // Resize the hBackButton button
            MoveWindow(hBackButton, x4, y4, 100, 30, TRUE);
            MoveWindow(hBackButton2, x4, y4, 100, 30, TRUE);

        }
        break;
        case ID_PASSWORD_LENGTH_OK_BUTTON:
        {
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;
            int x = width - 120 - 20;
            int y = height - 40 - 20;
            int x2 = width - 230 - 40;
            int y2 = height - 40 - 20;
            int x3 = 20;
            int y3 = height - 101 - 20;
            int x4 = 20;
            int y4 = height - 31 - 20;


            WCHAR buffer[100];
            GetWindowText(hUsernameEdit, username, MAX_LOADSTRING);
            wchar_t *end = 0;
            // Retrieve the password length entered by the user
            GetWindowText(hPasswordLengthEdit, buffer, 100);
            size_t password_length = _wcstoui64(buffer, &end, 10); // Convert the password length to a secure integer
            wchar_t allCharacters[200];
            const wchar_t lowercaseCharacters[] = L"abcdefghijklmnopqrstuvwxyz";
            const wchar_t uppercaseCharacters[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            const wchar_t numberCharacters[] = L"0123456789";
            const wchar_t symbolsCharacters[] = L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
            allCharacters[0] = L'\0';

            if (BST_CHECKED == SendMessage(hLowercaseCheckbox, BM_GETCHECK, 0, 0))
            {
                // Include lowercase letters in the password
                wcscat_s(allCharacters, lowercaseCharacters);
            }
            if (BST_CHECKED == SendMessage(hUppercaseCheckbox, BM_GETCHECK, 0, 0))
            {
                // Include uppercase letters in the password
                wcscat_s(allCharacters, uppercaseCharacters);
            }
            if (BST_CHECKED == SendMessage(hNumbersCheckbox, BM_GETCHECK, 0, 0))
            {
                // Include numbers in the password
                wcscat_s(allCharacters, numberCharacters);
            }
            if (BST_CHECKED == SendMessage(hSymbolsCheckbox, BM_GETCHECK, 0, 0))
            {
                // Include special symbols in the password
                wcscat_s(allCharacters, symbolsCharacters);
            }
            if (buffer == end || *end != L'\0') {
                // Error: Invalid input
                MessageBox(NULL, g_errorIfLenght, g_errorText, MB_ICONERROR | MB_OK);
            }
            if (password_length <= 3 || password_length >= 121) {
                MessageBox(NULL, g_errorIfLenght4_120, g_errorText, MB_ICONERROR | MB_OK);
            }
            else {
                // Generate the random password
                time_t time_raw_format;
                time(&time_raw_format);
                srand((unsigned int)time(NULL));

                const int possibleCharactersLength = (int)wcslen(allCharacters);
                if (possibleCharactersLength == 0) {
                    MessageBox(NULL, g_errorIfSelectCar, g_errorText, MB_ICONERROR | MB_OK);
                    break;
                }
                for (int i = 0; i < password_length; i++) {
                int randomIndex = rand() % possibleCharactersLength;
                password[i] = allCharacters[randomIndex];
                }
                password[password_length] = L'\0';

                // Create the labels to display the username and password
                hUsernameLabel2 = CreateWindowEx(0, L"STATIC", g_hUsernameLabel2, WS_CHILD | WS_VISIBLE, 20, 20, 180, 20, hWnd, (HMENU)ID_USERNAME_LABEL, NULL, NULL);
                hShowUsername = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", username, WS_CHILD | WS_VISIBLE | ES_READONLY | ES_AUTOHSCROLL, 220, 20, 1000, 20, hWnd, (HMENU)0, NULL, NULL);
                hPasswordLabel = CreateWindowEx(0, L"STATIC",  g_hPasswordLabel, WS_CHILD | WS_VISIBLE, 20, 60, 180, 20, hWnd, (HMENU)ID_PASSWORD_LABEL, NULL, NULL);
                hShowPassword = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", password, WS_CHILD | WS_VISIBLE | ES_READONLY | ES_AUTOHSCROLL, 220, 60, 1000, 20, hWnd, (HMENU)0, NULL, NULL);

                hPasswordLabelQ = CreateWindowEx(0, L"STATIC", g_hPasswordLabelQ, WS_CHILD | WS_VISIBLE, 20, 540, 500, 20, hWnd, (HMENU)ID_PASSWORD_LABEL, NULL, NULL);
                
                // Hide the OK buttons for the username and password length
                ShowWindow(hPasswordLengthOkButton, SW_HIDE);
                ShowWindow(hPasswordLengthLabel, SW_HIDE);
                ShowWindow(hPasswordLengthEdit, SW_HIDE);
                ShowWindow(hSelectLengthLabel, SW_HIDE);
                ShowWindow(hLowercaseCheckbox, SW_HIDE);
                ShowWindow(hUppercaseCheckbox, SW_HIDE);
                ShowWindow(hNumbersCheckbox, SW_HIDE);
                ShowWindow(hSymbolsCheckbox, SW_HIDE);
                ShowWindow(hTrackbar, SW_HIDE);
                ShowWindow(hPasswordLengthTrackbar, SW_HIDE);
                ShowWindow(hBackButton, SW_HIDE);
                ShowWindow(hBackButton2, SW_HIDE);
                // Disable editing of the username and password length
                EnableWindow(hShowUsername, TRUE);
                EnableWindow(hShowPassword, TRUE);
                
                // Create the buttons to save or not save the password
                hBackButton2 = CreateWindowEx(0, L"BUTTON", L" <---- ", WS_CHILD | WS_VISIBLE, 20, 610, 100, 30, hWnd, (HMENU)ID_BACK_BUTTON2, hInst, NULL);
                hSavePasswordYesButton = CreateWindowEx(0, L"BUTTON", g_hSavePasswordYesButton, WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 990, 600, 120, 40, hWnd, (HMENU)ID_SAVE_PASSWORD_YES_BUTTON, NULL, NULL);
                hSavePasswordNoButton = CreateWindowEx(0, L"BUTTON", g_hSavePasswordNoButton, WS_CHILD | WS_VISIBLE, 1120, 600, 120, 40, hWnd, (HMENU)ID_SAVE_PASSWORD_NO_BUTTON, NULL, NULL);
                
                InvalidateRect(hWnd, NULL, TRUE);

                // Resize the hPasswordLengthOkButton button
                MoveWindow(hPasswordLengthOkButton, x, y, 120, 40, TRUE);
                // Resize the hPasswordLabelQ button
                MoveWindow(hPasswordLabelQ, x3, y3, 480, 20, TRUE);
                // Resize the hSavePasswordYesButton button
                MoveWindow(hSavePasswordYesButton, x2, y2, 120, 40, TRUE);
                // Resize the hSavePasswordNoButton button
                MoveWindow(hSavePasswordNoButton, x, y, 120, 40, TRUE);
                // Resize the hBackButton button
                MoveWindow(hBackButton, x4, y4, 100, 30, TRUE);
                MoveWindow(hBackButton2, x4, y4, 100, 30, TRUE);


            }
            break;
        }
        case ID_BACK_BUTTON2:
        {
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;
            int x = width - 120 - 20;
            int y = height - 40 - 20;
            int x2 = width - 230 - 40;
            int y2 = height - 40 - 20;
            int x3 = 20;
            int y3 = height - 101 - 20;
            int x4 = 20;
            int y4 = height - 31 - 20;

            // Hide the elements of the second screen
            ShowWindow(hSelectLengthLabel, SW_SHOW);
            ShowWindow(hLowercaseCheckbox, SW_SHOW);
            ShowWindow(hUppercaseCheckbox, SW_SHOW);
            ShowWindow(hNumbersCheckbox, SW_SHOW);
            ShowWindow(hSymbolsCheckbox, SW_SHOW);
            ShowWindow(hPasswordLengthLabel, SW_SHOW);
            ShowWindow(hPasswordLengthEdit, SW_SHOW);
            ShowWindow(hPasswordLengthOkButton, SW_SHOW);
            ShowWindow(hBackButton, SW_SHOW);
            ShowWindow(hPasswordLengthTrackbar, SW_SHOW);
            ShowWindow(hTrackbar, SW_SHOW);

            // Show the elements of the first screen
            DestroyWindow(hPasswordLabelQ);
            DestroyWindow(hPasswordLabel);
            DestroyWindow(hUsernameLabel2);
            DestroyWindow(hShowUsername);
            DestroyWindow(hShowPassword);
            DestroyWindow(hSavePasswordYesButton);
            DestroyWindow(hSavePasswordNoButton);
            DestroyWindow(hBackButton2);

            InvalidateRect(hWnd, NULL, TRUE);
            // Resize the hUsernameOkButton button
            MoveWindow(hUsernameOkButton, x, y, 120, 40, TRUE);
            // Resize the hPasswordLengthOkButton button
            MoveWindow(hPasswordLengthOkButton, x, y, 120, 40, TRUE);
            // Resize the hPasswordLabelQ button
            MoveWindow(hPasswordLabelQ, x3, y3, 480, 20, TRUE);
            // Resize the hBackButton button
            MoveWindow(hBackButton, x4, y4, 100, 30, TRUE);
            MoveWindow(hBackButton2, x4, y4, 100, 30, TRUE);

        }
        break;
        case ID_SAVE_PASSWORD_YES_BUTTON:
        {

            WCHAR fileName[MAX_LOADSTRING] = L"MyFile.txt";
            WCHAR filter[] = L"Text Files (.txt)\0.txt\0All Files (.)\0*.*\0";
            OPENFILENAME ofn;
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFilter = filter;
            ofn.lpstrFile = fileName;
            ofn.nMaxFile = MAX_LOADSTRING;
            ofn.lpstrTitle = g_lpstrTitle;
            ofn.lpstrDefExt = L"txt";
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
            fileName[ofn.nFileOffset] = L'\0';
            if (GetSaveFileName(&ofn))
            {
                // Open the file in write mode
                HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hFile != INVALID_HANDLE_VALUE)
                {
                    DWORD passwordLength = _countof(password);
                    DWORD dwBytesWritten;
                    // Write the username and password to the file
                    WriteFile(hFile, g_FileWrittenUser, wcslen(g_FileWrittenUser) * sizeof(WCHAR), &dwBytesWritten, NULL);
                    WriteFile(hFile, username, wcslen(username) * sizeof(WCHAR), &dwBytesWritten, NULL);
                    WriteFile(hFile, L"\r\n", sizeof(L"\r\n") - sizeof(WCHAR), &dwBytesWritten, NULL);
                    WriteFile(hFile, g_FileWrittenPass, wcslen(g_FileWrittenPass) * sizeof(WCHAR), &dwBytesWritten, NULL);
                    WriteFile(hFile, password, wcslen(password) * sizeof(WCHAR), &dwBytesWritten, NULL);

                    CloseHandle(hFile);
                    MessageBox(hWnd, g_FileSaved, g_FileSavedComplete, MB_OK | MB_ICONINFORMATION);
                }
            }
            break;
        }
        case ID_SAVE_PASSWORD_NO_BUTTON:
        {
            // Open a dialog window to ask the user if they want to close the program or generate a new username and password
            INT_PTR result = MessageBox(hWnd, g_RestartQ, g_Closing, MB_YESNOCANCEL |MB_ICONQUESTION);
            if (result == IDNO) {
                ExitProcess(0);
            }
            else if (result == IDYES) {
                // Specify the executable file name of your program
                wchar_t currentFilePath[MAX_PATH];
                GetModuleFileName(NULL, currentFilePath, MAX_PATH);
                // Create a structure for the CreateProcess parameters
                STARTUPINFO si;
                PROCESS_INFORMATION pi;
                ZeroMemory(&si, sizeof(si));
                si.cb = sizeof(si);
                ZeroMemory(&pi, sizeof(pi));
                // Start the new process
                if(!CreateProcess(currentFilePath,   // Executable file name
                  NULL,      // Command line arguments
                  NULL,      // Process security attributes
                  NULL,      // Thread security attributes
                  FALSE,     // Inherit handles
                  0,         // Creation flags
                  NULL,      // Environment
                  NULL,      // Working directory
                  &si,       // STARTUPINFO
                  &pi))      // PROCESS_INFORMATION 
                {
                    MessageBox(hWnd, L"Impossibile avviare il programma", L"Errore", MB_OK | MB_ICONERROR);
                }
                else {
                    // Close process handles
                    CloseHandle(pi.hProcess);
                    CloseHandle(pi.hThread);
                    // Terminate the current process
                    ExitProcess(0);
                }
            }
            else if (result == IDCANCEL) {
                // Do nothing
            }
            break;
        }
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
            // TODO: Add drawing code here that uses HDC...
            EndPaint(hWnd, &ps);
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

// Message handler for the About window.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
