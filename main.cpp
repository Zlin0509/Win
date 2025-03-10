#include <windows.h>

//窗口处理函数WndProc()的声明
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//主函数，程序的入口，相当于之前的main()函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    static char szAppName[] = "HelloWin";
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;//WNDCLASSEX也行，会多几个分量，配合RegisterClassEX使用

    //设置WNDCLASS结构体，为下一步调用RegisterClass()函数做准备
    wndclass.style = CS_HREDRAW | CS_VREDRAW;//支持重绘，不能为0
    wndclass.lpfnWndProc = (WNDPROC) WndProc;//主函数与窗口处理函数绑定
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    //注册
    if (!RegisterClass(&wndclass)) {
        MessageBox(NULL, "This program requires Windows NT!",
                   szAppName, MB_ICONERROR);
        return 0;
    }

    //调用CreateWindow()函数创建窗体
    hwnd = CreateWindow (szAppName,                  // window class name
                         "The Windows Program",        // window caption
                         WS_OVERLAPPEDWINDOW,        // window style
                         CW_USEDEFAULT,              // initial x position
                         CW_USEDEFAULT,              // initial y position
                         CW_USEDEFAULT,              // initial x size
                         CW_USEDEFAULT,              // initial y size
                         NULL,                       // parent window handle
                         NULL,                       // window menu handle
                         hInstance,                  // program instance handle
                         NULL);                     // creation parameters

    //显示和更新窗口
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    //消息循环，不停接收消息直至收到WM_QUIT消息后，跳出循环，程序结束
    while (GetMessage(&msg, NULL, 0, 0))//如果函数取得WM_QUIT之外的其他消息，返回非零值。如果函数取得WM_QUIT消息，返回值是零
    {
        TranslateMessage(&msg);//翻译消息，将按键消息转换为字符消息
        DispatchMessage(&msg);//以此消息为参数转发给相应的窗口消息处理程序
    }
    return msg.wParam;
}

//窗口处理函数，函数格式固定，函数名无所谓
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //Code here!

    HDC hdc;
    PAINTSTRUCT ps;
    char a[] = "Hello, Windows!";

    //分支结构，处理各种消息
    switch (message) {
        //绘图，很多情况下会被调用
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            TextOut(hdc, 200, 200, a, strlen(a));
            EndPaint(hwnd, &ps);
            return 0;

            //用户点击关闭窗体按钮时触发
        case WM_DESTROY:
            PostQuitMessage(0);//发出WM_QUIT消息，终止消息循环
            return 0;
    }

    //缺省采用系统消息默认处理函数
    return DefWindowProc(hwnd, message, wParam, lParam);
}

