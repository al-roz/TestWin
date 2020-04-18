#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>


int x = 85;
int a;
HWND hEdt1;

HWND** m;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam);

int CheckNewPos(COORD* pos)
{
    if (pos->X == -1 || pos->X == a)
    {
        return 1;
    }
    if (pos->Y == -1 || pos->Y == a)
    {
        return 1;
    }
    return 0;
}


void changPos(COORD* Pos, int step)
{
    if (step == 1)
    {
        Pos->X += 0;
        Pos->Y -= 1;
    }
    if (step == 2)
    {
        Pos->X -= 1;
        Pos->Y += 0;
    }
    if (step == 3)
    {
        Pos->X += 0;
        Pos->Y += 1;
    }
    if (step == 4)
    {
        Pos->X += 1;
        Pos->Y += 0;
    }

    if (CheckNewPos(Pos))
    {
        if (step == 1)
        {
            Pos->X += 0;
            Pos->Y += 1;
        }
        if (step == 2)
        {
            Pos->X += 1;
            Pos->Y += 0;
        }
        if (step == 3)
        {
            Pos->X += 0;
            Pos->Y -= 1;
        }
        if (step == 4)
        {
            Pos->X -= 1;
            Pos->Y += 0;
        }
    }
}

    
int StrToInt(char* s,int len)
{
    int temp = 0; // число
    int i = 0;
    while ((s[i] >= 0x30 && s[i] <= 0x39 )||i <= len)
    {
        
        temp = temp + (s[i] & 0x0F);
        temp = temp * 10;        
        if (i % 2 == 0) temp /= 10;
        i++;
       
    }
   if (i == 2) temp = temp / 10;
    return temp;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    srand(time(NULL));
    HWND hwnd;
    MSG msg;
    WNDCLASS w;
    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = CreateSolidBrush(0x00FFFFFF);
    w.lpszClassName = "MyClass";
    RegisterClass(&w);

    hwnd = CreateWindow("MyClass", L"Test",
        WS_OVERLAPPEDWINDOW,
        500, 300, 500, 500,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);// отображение окна

    
    hEdt1 = CreateWindow(L"Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 110, 1, 60, 20, hwnd, NULL, hInstance, 0);
    ShowWindow(hEdt1, SW_SHOWNORMAL);
    UpdateWindow(hEdt1);// отображение окна
    UpdateWindow(hEdt1);// отображение окна

    HWND hBtn;
    HMENU hMenu = 1;
    hBtn = CreateWindow(L"Button", L"Нарисовать поле",
        WS_CHILD | WS_VISIBLE | WS_BORDER, 
        2, 25, 120, 30, hwnd,hMenu, hInstance, NULL);
    ShowWindow(hBtn, SW_SHOWNORMAL);
    UpdateWindow(hBtn);// отображение окна

   

    UpdateWindow(hwnd);// отображение окна
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
 
    
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{

    HDC hdc;
    HINSTANCE hInst;
    PAINTSTRUCT ps;
    static HWND hBtn; // дескриптор кнопки
    static HWND hStat; // дескриптор статического текста
    wchar_t StrA[20];

    int Len;
    
   switch (Message)
    {
     
    case WM_COMMAND:      
        
        switch (LOWORD(wparam))
        {
            case 1:
            {
                Len = GetWindowText(hEdt1, StrA, 20);
                a = StrToInt(StrA, Len);

                m = (HWND**)malloc(a * sizeof(HWND*));
                for (int i = 0; i < a; i++)
                    m[i] = (HWND*)malloc(a * sizeof(HWND));

                for (int i = 0; i < a; i++)
                {
                    for (int j = 0; j < a; j++)
                        m[i][j] = CreateWindow(L"Static", NULL, WS_EX_CLIENTEDGE | WS_CHILD | WS_VISIBLE,
                            x + 10 * i, 78 + 13 * j, 10, 13, hwnd, 0, hwnd, NULL);
                }



                COORD StartPos;

                int ans = a * a + 1;
                int kol = 0;
                for (int i = 0; i < a; i++)
                    for (int j = 0; j < a; j++)
                        SetWindowText(m[i][j], L"*");
                StartPos.X = rand() % a;
                StartPos.Y = rand() % a;
                SetWindowText(m[StartPos.X][StartPos.Y], L" ");
                while (kol < ans)
                {
                    int step = rand() % 4 + 1;
                    changPos(&StartPos, step);
                    SetWindowText(m[StartPos.X][StartPos.Y], L" ");

                    kol++;
                }



                for (int i = 0; i < a; i++)
                    free(m[i]);
                free(m);

                break;
            }
            
        }   
        break;
    
    case WM_PAINT: // перерисовка окна
    {
        hdc = BeginPaint(hwnd, &ps); // начало перерисовки
        TextOut(hdc, 1, 1, L"Введите числo", 13); // вывод текстовых сообщений
        TextOut(hdc, 3, 80, L"Результат:", 10);
        EndPaint(hwnd, &ps); // конец перерисовки
        break;
    }
       

    case WM_DESTROY: // закрытие окна
        PostQuitMessage(0);
        break;

    default: // обработка сообщения по умолчанию
        return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;

}

   