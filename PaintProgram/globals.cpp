#include "function.h"

HINSTANCE g_hInst = nullptr;
HWND      hRedPen = NULL, hGreenPen = NULL, hBluePen = NULL, hPenWidth = NULL;
HWND      hRedBrush = NULL, hGreenBrush = NULL, hBlueBrush = NULL;
int       redPen = 0, greenPen = 0, bluePen = 0;
int       redBrush = 0, greenBrush = 0, blueBrush = 0;
int       penWidth = 1;
int       g_nWidth = 0, g_nHeight = 0;
int       figureStyle = -1;
int       defaultEllipse = 1, defaultRect = 1, defaultRoundRect = 1;
int       penStyle = 0;
int       hatchStyle = HS_FILL;
int       textStyle = 0;
int       eraserStyle = 0;
int       sizeChange = 0;