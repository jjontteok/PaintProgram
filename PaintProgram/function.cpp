#include "function.h"

//static int figureStyle = -1;
//static int defaultEllipse = 1, defaultRect = 1, defaultRoundRect = 1;
//static int penStyle = 0; //PS_SOLID;
//static int hatchStyle = HS_FILL; //채워져있는 상태
//static int textStyle = 0;
//static int eraserStyle = 0;

void __Line(HDC hdc, int x1, int y1, int x2, int y2, int thickness, int penStyle, COLORREF crPen) {
    HPEN oldPen, newPen;
    newPen = CreatePen(penStyle, thickness, crPen);
    oldPen = (HPEN)SelectObject(hdc, newPen);
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    SelectObject(hdc, oldPen);
    DeleteObject(newPen);
}

void __Rectangle(HDC hdc, int x1, int y1, int x2, int y2, int thickness, int penStyle, int brushStyle, COLORREF crPen, COLORREF crBrush) {
    HPEN oldPen, newPen;
    HBRUSH oldBrush, newBrush;

    newPen = CreatePen(penStyle, thickness, crPen);
    oldPen = (HPEN)SelectObject(hdc, newPen);

    if (brushStyle == HS_FILL && defaultRect != 0)
        newBrush = CreateSolidBrush(crBrush);
    else if (defaultRect == 0)
        newBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    else
        newBrush = CreateHatchBrush(brushStyle, crBrush);
    oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

    Rectangle(hdc, x1, y1, x2, y2);

    SelectObject(hdc, oldPen);
    DeleteObject(newPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(newBrush);
}

void __Ellipse(HDC hdc, int x1, int y1, int x2, int y2, int thickness, int penStyle, int brushStyle, COLORREF crPen, COLORREF crBrush) {
    HPEN oldPen, newPen;
    HBRUSH oldBrush, newBrush;

    newPen = CreatePen(penStyle, thickness, crPen);
    oldPen = (HPEN)SelectObject(hdc, newPen);

    if (brushStyle == HS_FILL && defaultEllipse != 0)
        newBrush = CreateSolidBrush(crBrush);
    else if (defaultEllipse == 0 && sizeChange < 2)
        newBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    else
        newBrush = CreateHatchBrush(brushStyle, crBrush);

    oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

    Ellipse(hdc, x1, y1, x2, y2);

    SelectObject(hdc, oldPen);
    DeleteObject(newPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(newBrush);
}

void __RoundRect(HDC hdc, int x1, int y1, int x2, int y2, int thickness, int penStyle, int brushStyle, COLORREF crPen, COLORREF crBrush) {
    HPEN oldPen, newPen;
    HBRUSH oldBrush, newBrush;

    newPen = CreatePen(penStyle, thickness, crPen);
    oldPen = (HPEN)SelectObject(hdc, newPen);

    if (brushStyle == HS_FILL && defaultRoundRect != 0)
        newBrush = CreateSolidBrush(crBrush);
    else if (defaultRoundRect == 0)
        newBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    else
        newBrush = CreateHatchBrush(brushStyle, crBrush);
    oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

    RoundRect(hdc, x1, y1, x2, y2, 15, 15);

    SelectObject(hdc, oldPen);
    DeleteObject(newPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(newBrush);
}

void __Text(HDC hdc, int x, int y, int textStyle, COLORREF crText, COLORREF crBK, const char* str, int stringLen) {
    switch (textStyle) {
    case TRANSPARENT:
        SetBkMode(hdc, TRANSPARENT);
        break;
    case OPAQUE:
        SetBkMode(hdc, OPAQUE);
        SetBkColor(hdc, crBK);
        break;
    case DEFAULT_TEXT:
        SetBkMode(hdc, OPAQUE);
        SetBkColor(hdc, RGB(255, 255, 255));
        break;
    }
    SetTextColor(hdc, crText);
    TextOut(hdc, x, y, str, stringLen);
}
void SelectFigure(HDC hdc, int x1, int y1, int x2, int y2) {
    switch (figureStyle) {
    case 1:
        __Line(hdc, x1, y1, x2, y2, penWidth, penStyle, RGB(redPen, greenPen, bluePen));
        break;
    case 2:
        if (defaultEllipse == 0)
            __Ellipse(hdc, x1, y1, x2, y2, penWidth, penStyle, hatchStyle, RGB(redPen, greenPen, bluePen), NULL_BRUSH);
        else
            __Ellipse(hdc, x1, y1, x2, y2, penWidth, penStyle, hatchStyle, RGB(redPen, greenPen, bluePen), RGB(redBrush, greenBrush, blueBrush));
        break;
    case 3:
        if (defaultRect == 0)
            __Rectangle(hdc, x1, y1, x2, y2, penWidth, penStyle, hatchStyle, RGB(redPen, greenPen, bluePen), NULL_BRUSH);
        else
            __Rectangle(hdc, x1, y1, x2, y2, penWidth, penStyle, hatchStyle, RGB(redPen, greenPen, bluePen), RGB(redBrush, greenBrush, blueBrush));
        break;
    case 4:
        if (defaultRoundRect == 0)
            __RoundRect(hdc, x1, y1, x2, y2, penWidth, penStyle, hatchStyle, RGB(redPen, greenPen, bluePen), NULL_BRUSH);
        else
            __RoundRect(hdc, x1, y1, x2, y2, penWidth, penStyle, hatchStyle, RGB(redPen, greenPen, bluePen), RGB(redBrush, greenBrush, blueBrush));
        break;
    }
}

void __DrawText(HDC hdc, int x, int y, const char* str, int strLen) {
    switch (textStyle) {
    case TRANSPARENT:
        __Text(hdc, x, y, TRANSPARENT, RGB(redPen, greenPen, bluePen), RGB(255, 255, 255), str, strLen);
        break;
    case OPAQUE:
        __Text(hdc, x, y, OPAQUE, RGB(redPen, greenPen, bluePen), RGB(redBrush, greenBrush, blueBrush), str, strLen);
        break;
    case DEFAULT_TEXT:
        __Text(hdc, x, y, DEFAULT_TEXT, RGB(redPen, greenPen, bluePen), RGB(255, 255, 255), str, strLen);
        break;
    }
}

void DrawFigure(HWND hWnd, int x1, int y1, int x2, int y2, BOOL bFill)
{
    int nStockBrush = NULL_BRUSH;

    HDC hdc = GetDC(hWnd);
    if (bFill)
        nStockBrush = BLACK_BRUSH;
    else
        SetROP2(hdc, R2_NOT);
    SelectObject(hdc, GetStockObject(nStockBrush));
    RestrictPaint(&y1, &y2, g_nHeight - 555, g_nHeight - 200, g_nHeight - 550, g_nHeight - 205);
    SelectFigure(hdc, x1, y1, x2, y2);
    ReleaseDC(hWnd, hdc);
}

void RestrictPaint(int* a1, int* a2, int restrictPoint1, int restrictPoint2, int setPoint1, int setPoint2) {
    if ((int)(short)*a1 <= restrictPoint1)
        *a1 = setPoint1;
    if ((int)(short)*a2 <= restrictPoint1)
        *a2 = setPoint1;
    if ((int)(short)*a1 >= restrictPoint2)
        *a1 = setPoint2;
    if ((int)(short)*a2 >= restrictPoint2)
        *a2 = setPoint2;
}

int RestrictCursor(int getCursor, int restrictCursor1, int restrictCursor2, int setCursor1, int setCursor2) {
    if (getCursor <= restrictCursor1)
        return setCursor1;
    else if (getCursor >= restrictCursor2)
        return setCursor2;
    else
        return getCursor;
}
void MenuFigure(HWND hWnd, HDC hdc, int cursorX, int cursorY) {

    __Line(hdc, 10, g_nHeight - 175, 30, g_nHeight - 165, 1, PS_SOLID, RGB(0, 0, 0));
    __Line(hdc, 30, g_nHeight - 165, 30, g_nHeight - 135, 1, PS_SOLID, RGB(0, 0, 0));
    __Line(hdc, 30, g_nHeight - 135, 50, g_nHeight - 135, 1, PS_SOLID, RGB(0, 0, 0));                                       //1열 1행
    __Line(hdc, 65, g_nHeight - 175, 105, g_nHeight - 135, 1, PS_SOLID, RGB(0, 0, 0));                                      //1열 2행
    __Ellipse(hdc, 120, g_nHeight - 175, 160, g_nHeight - 135, 1, PS_SOLID, HS_FILL, RGB(0, 0, 0), RGB(255, 255, 255));
    __Rectangle(hdc, 175, g_nHeight - 175, 215, g_nHeight - 135, 1, PS_SOLID, HS_FILL, RGB(0, 0, 0), RGB(255, 255, 255));
    __RoundRect(hdc, 230, g_nHeight - 175, 270, g_nHeight - 135, 1, PS_SOLID, HS_FILL, RGB(0, 0, 0), RGB(255, 255, 255));
    TextOut(hdc, 285, g_nHeight - 175, "기본 텍스트", (int)strlen("기본 텍스트"));
    TextOut(hdc, 285, g_nHeight - 135, "투명 텍스트", (int)strlen("투명 텍스트"));
    TextOut(hdc, 285, g_nHeight - 95, "불투명 텍스트", (int)strlen("불투명 텍스트"));

    for (int i = 10, j = 1; i <= 230; i += 55) {
        if (i == 120)
            __Line(hdc, i, g_nHeight - 120, i + 40, g_nHeight - 80, 1, PS_SOLID, RGB(0, 0, 0));
        else
            __Line(hdc, i, g_nHeight - 120, i + 40, g_nHeight - 80, 1, j++, RGB(0, 0, 0));
    }

    for (int i = 10, j = 0; i <= 340; i += 55) {
        __Ellipse(hdc, i, g_nHeight - 65, i + 40, g_nHeight - 25, 1, PS_SOLID, j++, RGB(0, 0, 0), RGB(0, 0, 0));
    }


    if (cursorY >= g_nHeight - 175 && cursorY <= g_nHeight - 135) { //첫 번째 줄
        if (cursorX >= 10 && cursorX <= 50)
            figureStyle = 0;
        else if (cursorX >= 65 && cursorX <= 105)
            figureStyle = 1;
        else if (cursorX >= 120 && cursorX <= 160) {
            figureStyle = 2;
            defaultEllipse = 0;
        }
        else if (cursorX >= 175 && cursorX <= 215) {
            figureStyle = 3;
            defaultRect = 0;
        }
        else if (cursorX >= 230 && cursorX <= 270) {
            figureStyle = 4;
            defaultRoundRect = 0;
        }
        eraserStyle = 0;
    }
    else if (cursorY >= g_nHeight - 120 && cursorY <= g_nHeight - 80) { //두 번째 줄
        if (cursorX >= 10 && cursorX <= 50)
            penStyle = PS_DASH;
        else if (cursorX >= 65 && cursorX <= 105)
            penStyle = PS_DOT;
        if (cursorX >= 120 && cursorX <= 160)
            penStyle = PS_SOLID;
        if (cursorX >= 175 && cursorX <= 215)
            penStyle = PS_DASHDOT;
        if (cursorX >= 230 && cursorX <= 270)
            penStyle = PS_DASHDOTDOT;
        eraserStyle = 0;
    }
    else if (cursorY >= g_nHeight - 65 && cursorY <= g_nHeight - 25) {  //세 번째 줄
        if (cursorX >= 10 && cursorX <= 50)
            hatchStyle = HS_HORIZONTAL;
        else if (cursorX >= 65 && cursorX <= 105)
            hatchStyle = HS_VERTICAL;
        else if (cursorX >= 120 && cursorX <= 160)
            hatchStyle = HS_BDIAGONAL;
        else if (cursorX >= 175 && cursorX <= 215)
            hatchStyle = HS_FDIAGONAL;
        else if (cursorX >= 230 && cursorX <= 270)
            hatchStyle = HS_CROSS;
        else if (cursorX >= 285 && cursorX <= 325)
            hatchStyle = HS_DIAGCROSS;
        else if (cursorX >= 340 && cursorX <= 380)
            hatchStyle = HS_FILL;
        if (cursorX >= 10 && cursorX <= 380)
            defaultEllipse = 1, defaultRect = 1, defaultRoundRect = 1;
        eraserStyle = 0;
    }

    if (cursorX >= 285 && cursorX <= 380 && cursorY >= g_nHeight - 175 && cursorY <= g_nHeight - 75) {
        figureStyle = 5;
        eraserStyle = 0;
        if (cursorY >= g_nHeight - 175 && cursorY <= g_nHeight - 155)
            textStyle = 0;
        else if (cursorY >= g_nHeight - 135 && cursorY <= g_nHeight - 115)
            textStyle = 1;
        else if (cursorY >= g_nHeight - 95 && cursorY <= g_nHeight - 75)
            textStyle = 2;
    }

    if (cursorY >= g_nHeight - 70 && cursorY <= g_nHeight - 10) {
        if (cursorX >= 1000 && cursorX <= 1060) {
            eraserStyle = 1;
            figureStyle = -1;
        }
        else if (cursorX >= 1080 && cursorX <= 1140) {
            eraserStyle = 2;
        }
    }

    TextOut(hdc, 775, g_nHeight - 194, "펜 RGB", (int)strlen("펜 RGB"));
    TextOut(hdc, 775, g_nHeight - 80, "펜 굵기", (int)strlen("팬 굵기"));
    TextOut(hdc, 1020, g_nHeight - 194, "브러쉬 RGB", (int)strlen("브러쉬 RGB"));

    __Rectangle(hdc, 1000, g_nHeight - 70, 1060, g_nHeight - 10, 1, PS_SOLID, HS_FILL, RGB(0, 0, 0), RGB(255, 255, 255)); //지우개
    __Rectangle(hdc, 1080, g_nHeight - 70, 1140, g_nHeight - 10, 1, PS_SOLID, HS_FILL, RGB(0, 0, 0), RGB(255, 255, 255)); //전체 지우기
    TextOut(hdc, 1005, g_nHeight - 45, "지우개", (int)strlen("지우개"));
    TextOut(hdc, 1090, g_nHeight - 60, "전체", (int)strlen("전체"));
    TextOut(hdc, 1085, g_nHeight - 35, "지우기", (int)strlen("지우기"));

    //뭘 그릴지 선택한 거를 보여주는 코드
    sizeChange = 1;
    if (figureStyle == 0) {
        __Line(hdc, 500, g_nHeight - 175, 600, g_nHeight - 75, penWidth, penStyle, RGB(redPen, greenPen, bluePen));
        __Line(hdc, 600, g_nHeight - 75, 600, g_nHeight - 25, penWidth, penStyle, RGB(redPen, greenPen, bluePen));
        __Line(hdc, 600, g_nHeight - 25, 650, g_nHeight - 25, penWidth, penStyle, RGB(redPen, greenPen, bluePen));
    }
    else if (figureStyle == 5)
        switch (textStyle) {
        case TRANSPARENT:
            __Text(hdc, 500, g_nHeight - 175, TRANSPARENT, RGB(redPen, greenPen, bluePen), RGB(255, 255, 255), "투명 텍스트", (int)strlen("투명 텍스트"));
            break;
        case OPAQUE:
            __Text(hdc, 500, g_nHeight - 175, OPAQUE, RGB(redPen, greenPen, bluePen), RGB(redBrush, greenBrush, blueBrush), "불투명 텍스트", (int)strlen("불투명 텍스트"));
            break;
        case DEFAULT_TEXT:
            __Text(hdc, 500, g_nHeight - 175, DEFAULT_TEXT, RGB(redPen, greenPen, bluePen), RGB(255, 255, 255), "기본 텍스트", (int)strlen("기본 텍스트"));
            break;
        }
    else
        SelectFigure(hdc, 500, g_nHeight - 175, 650, g_nHeight - 25);
}