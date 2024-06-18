#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
// CONSTATN DATA
static const char WName[] = "Pong";
// DATA TYPE
typedef struct { unsigned long left, top, right, bottom; } RCT;
// WINDOW FUNCTION PROTOTYPE
static WNDPROC WndProc(HWND hWnd, UINT mess, WPARAM w, LPARAM l);
// GRAPHICS FUNCTION PROTOTYPE
extern void __fastcall ClearScreen(DWORD* Buf, DWORD Col, unsigned int BufSize);
extern void __fastcall DrawRectFunc(unsigned int XSx, unsigned int YSy, DWORD* Buf, DWORD Col);
extern void __fastcall DrawCircleFunc(unsigned int XY, unsigned int Rad, DWORD* Buf, DWORD Col);
extern void __fastcall DrawLHCircleFunc(unsigned int XY, unsigned int Rad, DWORD* Bud, DWORD Col);
extern void __fastcall DrawRHCircleFunc(unsigned int XY, unsigned int Rad, DWORD* Bud, DWORD Col);
// GRAPHICS API
#define ToRGB(r, g, b) (r << 16) | (g << 8) | b
#define DrawRect(X, Y, Sx, Sy, Buf, Col) DrawRectFunc((Sx << 16) | (X), (Sy << 16) | (Y), Buf, Col)
#define DrawCircle(X, Y, Rad, Buf, Col) DrawCircleFunc((X << 16) | Y, Rad, Buf, Col)
#define DrawLHCircle(X, Y, Rad, Buf, Col) DrawLHCircleFunc((X << 16) | Y, Rad, Buf, Col)
#define DrawRHCircle(X, Y, Rad, Buf, Col) DrawRHCircleFunc((X << 16) | Y, Rad, Buf, Col)
// WINDOW DATA
static WNDCLASSA WClass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, "PongGme"};
static MSG mess;
extern RCT WRect = { 0, 0, 0, 0 };
static HBITMAP Bm;
static HDC Dc;
static HDC MDc;
static HFONT Font;
// PIX BUFFER DATA
static BITMAPINFO Bmi = { { 40, 0, 0, 1, 32, 0, 0, 0, 0, 0, 0 }, 0 };
static DWORD* PixBuf;
// GAME DATA
#define CentWidth 0.01f
#define CentHei 0.11f
#define CentProb 0.03f
static float FPS;
static unsigned int CStr;
static unsigned short CWidth;
static unsigned short CHei;
static unsigned short CProb;
// MENU DATA
#define P1GAME 1
#define P2GAME 2
#define StdMenuCol 1
static unsigned char ModCol = StdMenuCol;
static unsigned char Pos = 0;
static unsigned char LClc = 0;
// MENU LABELS
static char Playrs[] = {'1', 'P', ' ', ' ', ' ', ' ', ' ', '2', 'P'};
// BALL DARA
#define BallSdtSpdX 0.4f
#define BallSdtSpdY 0.36f
#define BallRad 0.007f
static float BSpdX;
static float BSpdY;
static float BSpd;
static float Bx;
static float By;
static unsigned short Br;
// PLATFORM DATA
#define FPlX 0.02f
#define FPlSx 0.005f
#define FPlSy 0.11f
#define FSpdp 0.28f
static unsigned short PSx;
static unsigned short PSy;
static float PSpd;
// FIRST PLATFOTM DATA
static unsigned short Px;
static float Py;
static unsigned char scor1;
// SECOND PLATFORM DATA
static unsigned short P2x;
static float P2y;
static unsigned char scor2;
// MAIN PROCEDURE
static int WinMain() {
// INIT WINDOW
	WRect.bottom = GetSystemMetrics(SM_CYSCREEN) >> 1;
	WRect.bottom += WRect.bottom >> 1;
	Bmi.bmiHeader.biHeight = WRect.bottom;
	Bmi.bmiHeader.biWidth = WRect.right = WRect.bottom << 1;
	WClass.hCursor = LoadCursorA(0, IDC_ARROW);
	Font = CreateFontA(52, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
// PIXEL BUFFER INIT
	Bmi.bmiHeader.biSizeImage = (WRect.right * WRect.bottom + 4);
	PixBuf = malloc((Bmi.bmiHeader.biSizeImage << 2));
// CREATE & SHOW WINDOW
	RegisterClassA(&WClass);
	ShowWindow(MDc = CreateWindowExA(0, WClass.lpszClassName, WName, (WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX), 0, 0, WRect.right, WRect.bottom, 0, 0, 0, 0), SW_SHOWNORMAL);
	MDc = GetDC(MDc);
// GAME INIT
	CWidth = WRect.right * CentWidth;
	CHei = WRect.bottom * CentHei;
	CProb = WRect.bottom * CentProb;
	Bx = WRect.right >> 1;
	By = WRect.bottom >> 1;
	Br = WRect.right * BallRad;
	BSpdX = WRect.right * BallSdtSpdX;
	BSpdY = WRect.right * BallSdtSpdY;
	BSpd = sqrt(BSpdX * BSpdX + BSpdY * BSpdY);
	PSx = WRect.right * FPlSx;
	PSy = WRect.right * FPlSy;
	Px = WRect.right * FPlX;
	Py = (WRect.bottom >> 1) - (PSy >> 1);
	PSpd = WRect.right * FSpdp;
	P2x = WRect.right - WRect.right * (FPlX + FPlSx);
	P2y = (WRect.bottom >> 1) - (PSy >> 1);
// CYCLE
	CYC: {
		if (PeekMessageA(&mess, 0, 0, 0, PM_REMOVE)) DispatchMessageA(&mess);
	} goto CYC;
	return 0;
}
// MAIN WINDOW PROCEDURE
static WNDPROC WndProc(HWND hWnd, UINT mess, WPARAM w, LPARAM l) {
	switch (mess) {
// WINDOW DESTROY EVENT
		case (WM_DESTROY): 
			ExitProcess(0); 
			return 0;
// MOUSE CLICK EVENT
		case (WM_LBUTTONDOWN):
			switch (Pos) {
				case(0):
					if ((l & 0x0000FFFF) > (WRect.right >> 1) - 100 && (l & 0x0000FFFF) < (WRect.right >> 1) && (l >> 16) < 70) LClc = 1;
					else if ((l & 0x0000FFFF) < (WRect.right >> 1) + 100 && (l & 0x0000FFFF) > (WRect.right >> 1) && (l >> 16) < 70) LClc = 2;
					break;
			}
			return 0;
// MOUSE UP EVENT
		case (WM_LBUTTONUP):
			switch (Pos) {
				case(0):
					if ((l & 0x0000FFFF) > (WRect.right >> 1) - 100 && (l & 0x0000FFFF) < (WRect.right >> 1) && (l >> 16) < 70 && LClc == 1) {
						Pos = P1GAME;
						ModCol = 0;
						Playrs[0] = '0';
						Playrs[1] = '0';
						Playrs[8] = '0';
						Playrs[7] = '0';
					} else if ((l & 0x0000FFFF) < (WRect.right >> 1) + 100 && (l & 0x0000FFFF) > (WRect.right >> 1) && (l >> 16) < 70 && LClc == 2) {
						Pos = P2GAME;
						ModCol = 0;
						Playrs[0] = '0';
						Playrs[1] = '0';
						Playrs[8] = '0';
						Playrs[7] = '0';
					}
					break;
			}
			return 0;
// WINDOW RESIZE EVENT
		case (WM_SIZE):
			GetClientRect(hWnd, &WRect);
			Bmi.bmiHeader.biSizeImage = ((Bmi.bmiHeader.biWidth = WRect.right) * (Bmi.bmiHeader.biHeight = WRect.bottom) + 4);
			free(PixBuf);
			PixBuf = malloc((Bmi.bmiHeader.biSizeImage << 2));
			return 0;
// DRAW EVENT
		case (WM_PAINT):
			CStr = clock();
			Dc = CreateCompatibleDC(MDc);
			Bm = CreateCompatibleBitmap(MDc, WRect.right, WRect.bottom);
			SelectObject(Dc, Bm);
			ClearScreen(PixBuf, ToRGB((100 >> ModCol), (255 >> ModCol), (100 >> ModCol)), Bmi.bmiHeader.biSizeImage);
// DRAW GAME
			unsigned int i = 0;
			for (; i < WRect.bottom / (CHei + CProb); ++i) DrawRect(((WRect.right >> 1) - (CWidth >> 1)), (i * (CHei + CProb)), CWidth, CHei, PixBuf, ToRGB((unsigned int)(255 >> ModCol), (unsigned int)(255 >> ModCol), (unsigned int)(255 >> ModCol)));
			DrawRect(((WRect.right >> 1) - (CWidth >> 1)), i * (CHei + CProb), CWidth, (WRect.bottom - i * (CHei + CProb)), PixBuf, ToRGB((unsigned int)(255 >> ModCol), (unsigned int)(255 >> ModCol), (unsigned int)(255 >> ModCol)));
// GAME LOGIC
			DrawCircle((unsigned int)Bx, (unsigned int)By, Br, PixBuf, ToRGB((220 >> ModCol), (220 >> ModCol), (220 >> ModCol)));
			if (Pos == P1GAME || Pos == P2GAME) {
				Bx = min(max(Br, (Bx + (BSpdX / FPS))), WRect.right - Br);
				By = min(max(Br, (By + (BSpdY / FPS))), WRect.bottom - Br);
				if (By <= Br || By >= WRect.bottom - Br) BSpdY = -BSpdY;
				if (Bx <= Br) {
					BSpdX = -BSpdX;
					++scor1;
					Playrs[0] = scor1 / 10 + 48;
					Playrs[1] = scor1 % 10 + 48;
					Bx = WRect.right >> 1;
					By = WRect.bottom >> 1;
				} else if (Bx >= WRect.right - Br) {
					BSpdX = -BSpdX;
					++scor2;
					Playrs[7] = scor2 / 10 + 48;
					Playrs[8] = scor2 % 10 + 48;
					Bx = WRect.right >> 1;
					By = WRect.bottom >> 1;
				} else if (Bx + Br >= Px && Bx - Br <= Px + PSx && By + Br >= Py && By - Br <= Py + PSy) {
					BSpdY = WRect.right * max(min(((By - (Py + (PSy >> 1))) / (float)PSy), 0.5f), -0.5f);
					BSpdX = sqrt(BSpd * BSpd - BSpdY * BSpdY);
				} else if (Bx + Br >= P2x && Bx - Br <= P2x + PSx && By + Br >= P2y && By - Br <= P2y + PSy) {
					BSpdY = WRect.right * max(min(((By - (P2y + (PSy >> 1))) / (float)PSy), 0.5f), -0.5f);
					BSpdX = -sqrt(BSpd * BSpd - BSpdY * BSpdY);
				}
				if (GetKeyState(0x57) & 0x8000) Py = min((Py + (PSpd / FPS)), WRect.bottom - PSy);
				else if (GetKeyState(0x53) & 0x8000) Py = max((Py - (PSpd / FPS)), 0);
				if (Pos == P2GAME) {
					if (GetKeyState(VK_UP) & 0x8000) P2y = min((P2y + (PSpd / FPS)), WRect.bottom - PSy);
					if (GetKeyState(VK_DOWN) & 0x8000) P2y = max((P2y - (PSpd / FPS)), 0);
				} else {
					if (P2y + (PSy >> 1) + 3 < By) P2y = min((P2y + PSpd / FPS), WRect.bottom - PSy);
					else if (P2y + (PSy >> 1) - 3 > By) P2y = max((P2y - PSpd / FPS), 0);
				}
			}
			DrawRect(Px, (unsigned int)Py, PSx, PSy, PixBuf, ToRGB((255 >> ModCol), (255 >> ModCol), (255 >> ModCol)));
			DrawRect(P2x, (unsigned int)P2y, PSx, PSy, PixBuf, ToRGB((255 >> ModCol), (255 >> ModCol), (255 >> ModCol)));
// DRAW INTERFACE
			DrawLHCircle((WRect.right >> 1) - 70, WRect.bottom - 35, 35, PixBuf, ToRGB(0, 0, 0));
			DrawRHCircle((WRect.right >> 1) + 70, WRect.bottom - 35, 35, PixBuf, ToRGB(0, 0, 0));
			DrawRect(((WRect.right >> 1) - 70), (WRect.bottom - 70), 140, 70, PixBuf, ToRGB(0, 0, 0));
			SetDIBitsToDevice(Dc, 0, 0, WRect.right, WRect.bottom, 0, 0, 0, WRect.bottom, PixBuf, &Bmi, BI_RGB);
			SetTextColor(Dc, RGB(255, 255, 255));
			SetBkColor(Dc, RGB(0, 0, 0));
			SelectObject(Dc, Font);
			TextOutA(Dc, (WRect.right >> 1) - 8 * (sizeof(Playrs)), 8, Playrs, sizeof(Playrs));
			BitBlt(MDc, 0, 0, WRect.right, WRect.bottom, Dc, 0, 0, SRCCOPY);
			DeleteDC(Dc);
			DeleteObject(Bm);
// GAME LOGIC
			FPS = 1000.f / (float)(clock() - CStr);
			return 0;
// OTHER EVENTS
		default: return DefWindowProcA(hWnd, mess, w, l);
	}
}