#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>


int x = 85;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam);
    
int StrToInt(char* s)
{
    int temp = 0; // число
    int i = 0;
    int sign = 0; // знак числа 0- положительное, 1 - отрицательное
    if (s[i] == '-')
    {
        sign = 1;
        i++;
    }
    while (s[i] >= 0x30 && s[i] <= 0x39)
    {
        temp = temp + (s[i] & 0x0F);
        temp = temp * 10;
        i++;
    }
    temp = temp / 10;
    if (sign == 1)
        temp = -temp;
    return(temp);
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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

    HWND hEdt1;
    hEdt1 = CreateWindow(L"Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 110, 1, 60, 20, hwnd, NULL, hInstance, 0);
    ShowWindow(hEdt1, SW_SHOWNORMAL);
    UpdateWindow(hEdt1);// отображение окна
    UpdateWindow(hEdt1);// отображение окна

    HWND hBtn;
    hBtn = CreateWindow(L"Button", L"Ќарисовать поле",
        WS_CHILD | WS_VISIBLE | WS_BORDER, 
        2, 25, 120, 30, hwnd, 0, hInstance, NULL);
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
    static HWND hEdt1;
    static HWND hBtn; // дескриптор кнопки
    // дескрипторы полей редактировани€
    static HWND hStat; // дескриптор статического текста
    wchar_t StrA[20];

    int a, b, sum, Len;
    switch (Message)
    {
     
    case WM_COMMAND:      
            
            Len = GetWindowText(hEdt1, StrA, 20);
            a = StrToInt(StrA);
            printf("%d", Len);
            //x += 10;
            hStat = CreateWindow(L"Static", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
                x, 78, 120, 20, hwnd, 0, hwnd, NULL);            
            ShowWindow(hStat, SW_SHOWNORMAL);
            SetWindowText(hStat, L"Hello");
            
        break;
    
    case WM_PAINT: // перерисовка окна
        hdc = BeginPaint(hwnd, &ps); // начало перерисовки
        TextOut(hdc, 1, 1, L"¬ведите числo", 13); // вывод текстовых сообщений
        TextOut(hdc, 3, 80, L"–езультат:", 10);
        EndPaint(hwnd, &ps); // конец перерисовки
        break;
    case WM_DESTROY: // закрытие окна
        PostQuitMessage(0);
        break;
    default: // обработка сообщени€ по умолчанию
        return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;

}

   