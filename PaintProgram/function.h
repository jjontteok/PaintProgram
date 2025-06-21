#ifndef  FUNCTION_H
#define FUNCTION_H

#include <windows.h>

#define HS_FILL 6
#define DEFAULT_TEXT 0
#define ID_SCRRED 100
#define ID_SCRGREEN 101
#define ID_SCRBLUE 102
#define ID_SPENWIDTH 103

extern HINSTANCE g_hInst;
extern HWND hRedPen, hGreenPen, hBluePen, hPenWidth;
extern HWND hRedBrush, hGreenBrush, hBlueBrush;
extern int redPen, greenPen, bluePen, redBrush, greenBrush, blueBrush;
extern int penWidth;
extern int g_nWidth, g_nHeight;
extern int figureStyle;
extern int defaultEllipse, defaultRect, defaultRoundRect;
extern int penStyle; //PS_SOLID;
extern int hatchStyle; //채워져있는 상태
extern int textStyle;
extern int eraserStyle;
extern int sizeChange;

void DrawFigure(HWND hWnd, int x1, int y1, int x2, int y2, BOOL bFill);
void __Line(HDC hdc, int x1, int y1, int x2, int y2, int thickness, int penStyle, COLORREF crPen);
void __Rectangle(HDC, int x1, int y1, int x2, int y2, int thickness, int penStyle, int brushStyle, COLORREF crPen, COLORREF crBrush);
void __Ellipse(HDC hdc, int x1, int y1, int x2, int y2, int thickness, int penStyle, int brushStyle, COLORREF crPen, COLORREF crBrush);
void __RoundRect(HDC hdc, int x1, int y1, int x2, int y2, int thickness, int penStyle, int brushStyle, COLORREF crPen, COLORREF crBrush);
void __Text(HDC hdc, int x, int y, int textStyle, COLORREF crText, COLORREF crBK, const char* str, int stringLen);
void MenuFigure(HWND hWnd, HDC hdc, int cursorX, int cursorY);
void SelectFigure(HDC hdc, int x1, int y1, int x2, int y2);
void __DrawText(HDC hdc, int x, int y, const char* str, int strLen);
void RestrictPaint(int* a1, int* a2, int restrictPoint1, int restrictPoint2, int setPoint1, int setPoint2);
int RestrictCursor(int getCursor, int restrictCursor1, int restrictCursor2, int setCursor1, int setCursor2);
#endif 
