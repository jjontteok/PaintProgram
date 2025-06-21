#include <windows.h>
#include "function.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//// WinMain 함수 : 윈도즈 프로그램의 최초 진입점 ( Entry Point )
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR	  lpCmdLine,
    int		  nCmdShow)
{
    char	  szAppName[] = "예제";
    HWND	  hWnd;
    MSG      msg;
    WNDCLASS wndclass;

    g_hInst = hInstance;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = g_hInst;
    wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    //// 윈도 클래스 등록
    RegisterClass(&wndclass);

    //// 윈도 생성
    hWnd = CreateWindow(szAppName,
        szAppName,
        WS_OVERLAPPEDWINDOW,
        100, 100, 1200, 600,
        NULL, NULL, hInstance, NULL);

    if (!hWnd) return FALSE;

    //// 생성된 윈도를 화면에 표시
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    //// 메시지 루프
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rt;
    int tempPos=0;
    static BOOL bDrawing = FALSE;
    static BOOL bScrollbarCreated = FALSE;
    static int  x1, y1, x2, y2;
    static char str[256];
    static int strLen = 0;

    switch (message)
    {
        //메뉴 보여주기
    case WM_SIZE:
        hdc = GetDC(hWnd);
        g_nHeight = HIWORD(lParam);
        g_nWidth = LOWORD(lParam);

        __Line(hdc, 0, g_nHeight - 200, g_nWidth, g_nHeight - 200, 1, PS_SOLID, RGB(0, 0, 0));
        MenuFigure(hWnd, hdc, x1, y1);

        if (!bScrollbarCreated) {
            hRedPen = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 700, g_nHeight - 175, 200, 20, hWnd, (HMENU)ID_SCRRED, g_hInst, NULL);
            hGreenPen = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 700, g_nHeight - 145, 200, 20, hWnd, (HMENU)ID_SCRGREEN, g_hInst, NULL);
            hBluePen = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 700, g_nHeight - 115, 200, 20, hWnd, (HMENU)ID_SCRBLUE, g_hInst, NULL);

            hPenWidth = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 700, g_nHeight - 60, 200, 20, hWnd, (HMENU)ID_SPENWIDTH, g_hInst, NULL); //펜 굵기 스크롤바

            hRedBrush = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 950, g_nHeight - 175, 200, 20, hWnd, (HMENU)ID_SCRRED, g_hInst, NULL);
            hGreenBrush = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 950, g_nHeight - 145, 200, 20, hWnd, (HMENU)ID_SCRGREEN, g_hInst, NULL);
            hBlueBrush = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 950, g_nHeight - 115, 200, 20, hWnd, (HMENU)ID_SCRBLUE, g_hInst, NULL);

            SetScrollRange(hRedPen, SB_CTL, 0, 255, TRUE);
            SetScrollPos(hRedPen, SB_CTL, 0, TRUE);
            SetScrollRange(hGreenPen, SB_CTL, 0, 255, TRUE);
            SetScrollPos(hGreenPen, SB_CTL, 0, TRUE);
            SetScrollRange(hBluePen, SB_CTL, 0, 255, TRUE);
            SetScrollPos(hBluePen, SB_CTL, 0, TRUE);

            SetScrollRange(hPenWidth, SB_CTL, 0, 30, TRUE);
            SetScrollPos(hPenWidth, SB_CTL, 0, TRUE);

            SetScrollRange(hRedBrush, SB_CTL, 0, 255, TRUE);
            SetScrollPos(hRedBrush, SB_CTL, 0, TRUE);
            SetScrollRange(hGreenBrush, SB_CTL, 0, 255, TRUE);
            SetScrollPos(hGreenBrush, SB_CTL, 0, TRUE);
            SetScrollRange(hBlueBrush, SB_CTL, 0, 255, TRUE);
            SetScrollPos(hBlueBrush, SB_CTL, 0, TRUE);

            bScrollbarCreated = TRUE;
        }
        else {
            MoveWindow(hRedPen, 700, g_nHeight - 175, 200, 20, TRUE);
            MoveWindow(hGreenPen, 700, g_nHeight - 145, 200, 20, TRUE);
            MoveWindow(hBluePen, 700, g_nHeight - 115, 200, 20, TRUE);
            MoveWindow(hPenWidth, 700, g_nHeight - 60, 200, 20, TRUE);
            MoveWindow(hRedBrush, 950, g_nHeight - 175, 200, 20, TRUE);
            MoveWindow(hGreenBrush, 950, g_nHeight - 145, 200, 20, TRUE);
            MoveWindow(hBlueBrush, 950, g_nHeight - 115, 200, 20, TRUE);
        }
        sizeChange++;
        ReleaseDC(hWnd, hdc);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        
        __Line(hdc, 0, g_nHeight - 200, g_nWidth, g_nHeight - 200, 1, PS_SOLID, RGB(0, 0, 0));
        MenuFigure(hWnd, hdc, x1, y1);
        RestrictPaint(&y1, &y2, g_nHeight - 555, g_nHeight - 200, g_nHeight - 550, g_nHeight - 205);

        if (figureStyle == 5) {
            __DrawText(hdc, x1, y1, str, strLen);
            SetRect(&rt, 0, g_nHeight - 200, g_nWidth, g_nHeight-194);
            InvalidateRect(hWnd, &rt, FALSE);
        }
        if (eraserStyle == 2) {
            SetRect(&rt, 0, 0, g_nWidth, g_nHeight - 199);
            InvalidateRect(hWnd, &rt, TRUE);
            eraserStyle = 0;
        }
        EndPaint(hWnd, &ps);
        return 0;

    case WM_LBUTTONDOWN:
        SetRect(&rt, 0, g_nHeight - 200, g_nWidth, g_nHeight);
        InvalidateRect(hWnd, &rt, FALSE);
        x1 = x2 = LOWORD(lParam);
        y1 = y2 = HIWORD(lParam);
        
        SetCursor(LoadCursor(NULL, IDC_CROSS));
        //// 커서가 영역밖을 벗어나도 지속적 마우스 메시지를 받을 수 있다
        SetCapture(hWnd);    

        //클릭할 때마다 문자열이 초기화됨
        strLen = 0;
        str[0] = '\0';

        bDrawing = TRUE;
        break;

    case WM_MOUSEMOVE:
        if (bDrawing)
        {
            hdc = GetDC(hWnd);
            int cursorX = (int)(short)LOWORD(lParam);
            int cursorY = (int)(short)HIWORD(lParam);
            
            if (eraserStyle == 1) {
                RestrictPaint(&x1, &x2, 0, g_nWidth, 0, g_nWidth - 1);
                RestrictPaint(&y1, &y2, 0, g_nHeight - 200, 0, g_nHeight - 201);

                x2 = RestrictCursor(cursorX, 0, g_nWidth, 0, g_nWidth - 1);
                y2 = RestrictCursor(cursorY, 0, g_nHeight - 200, 0, g_nHeight - 201);
                __Line(hdc, x1, y1, x2, y2, penWidth, penStyle, RGB(255,255,255));

                x1 = LOWORD(lParam);
                y1 = HIWORD(lParam);
                figureStyle = -1;
            }
            if (figureStyle == 0) { 
                RestrictPaint(&x1, &x2, 0, g_nWidth, 0, g_nWidth-1);
                RestrictPaint(&y1, &y2, 0, g_nHeight - 200, 0, g_nHeight - 201);

                x2 = RestrictCursor(cursorX, 0, g_nWidth, 0, g_nWidth - 1);
                y2 = RestrictCursor(cursorY, 0, g_nHeight - 200, 0, g_nHeight - 201);
                __Line(hdc, x1, y1, x2, y2, penWidth, penStyle, RGB(redPen, greenPen, bluePen));

                x1 = LOWORD(lParam);
                y1 = HIWORD(lParam);  
            }
            else {
                SetCursor(LoadCursor(NULL, IDC_CROSS));
                DrawFigure(hWnd, x1, y1, x2, y2, FALSE);
                x2 = RestrictCursor(cursorX, 0, g_nWidth, 1, g_nWidth - 1);
                y2 = RestrictCursor(cursorY, 0, g_nHeight - 200, 1, g_nHeight - 201);
                DrawFigure(hWnd, x1, y1, x2, y2, FALSE);
            }
            ReleaseDC(hWnd, hdc);
        }
        break;

    case WM_LBUTTONUP:
        if (bDrawing)
        {
            DrawFigure(hWnd, x1, y1, x2, y2, FALSE);
            //// 마우스 캡처를 푼다
            ReleaseCapture();
            bDrawing = FALSE;

            SetRect(&rt, 0, g_nHeight - 200, g_nWidth, g_nHeight-180);
            InvalidateRect(hWnd, &rt, TRUE);

            SetRect(&rt, 400, g_nHeight - 200, 800, g_nHeight - 10);
            InvalidateRect(hWnd, &rt, TRUE);

            UpdateWindow(hWnd);
            DrawFigure(hWnd, x1, y1, x2, y2, TRUE);
        }
        break;

    case WM_CHAR:
        str[strLen++] = (char)wParam;
        InvalidateRect(hWnd, NULL, FALSE);
        break;

    case WM_HSCROLL:
        if ((HWND)lParam == hRedPen) tempPos = redPen;
        if ((HWND)lParam == hGreenPen) tempPos = greenPen;
        if ((HWND)lParam == hBluePen) tempPos = bluePen;
        if ((HWND)lParam == hPenWidth) tempPos = penWidth;
        if ((HWND)lParam == hRedBrush) tempPos = redBrush;
        if ((HWND)lParam == hGreenBrush) tempPos = greenBrush;
        if ((HWND)lParam == hBlueBrush) tempPos = blueBrush;

        switch (LOWORD(wParam)) {
        case SB_LINELEFT:
            tempPos = max(0, tempPos - 1);
            break;
        case SB_LINERIGHT:
            tempPos = min(255, tempPos + 1);
            if ((HWND)lParam == hPenWidth)
                tempPos = min(30, tempPos + 1);
            break;
        case SB_PAGELEFT:
            tempPos = max(0, tempPos - 10);
            break;
        case SB_PAGERIGHT:
            tempPos = min(255, tempPos + 10);
            if ((HWND)lParam == hPenWidth)
                tempPos = min(30, tempPos + 10);
            break;
        case SB_THUMBTRACK:
            tempPos = HIWORD(wParam);
            break;
        }
        if ((HWND)lParam == hRedPen) redPen = tempPos;
        if ((HWND)lParam == hGreenPen)greenPen = tempPos;
        if ((HWND)lParam == hBluePen) bluePen = tempPos;
        if ((HWND)lParam == hPenWidth) penWidth = tempPos;
        if ((HWND)lParam == hRedBrush) redBrush = tempPos;
        if ((HWND)lParam == hGreenBrush)greenBrush = tempPos;
        if ((HWND)lParam == hBlueBrush) blueBrush = tempPos;

        SetScrollPos((HWND)lParam, SB_CTL, tempPos, TRUE);

        SetRect(&rt, 400, g_nHeight - 195, 690, g_nHeight - 5);
        InvalidateRect(hWnd, &rt, TRUE);

        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}