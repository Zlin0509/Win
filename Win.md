# This is a summary for Win

## Part 1

**基础框架的构成**

### 两个主要函数
主函数，类似于之前的`main`函数  
`int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)`  
消息处理函数  
`LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM)`  

### 主函数

#### 函数主框架
```c
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    static char *szAppName = "HelloWin";
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW; // 设置窗口的样式 这里要求窗口长宽变化时都强制重绘 等价于在窗口大小变化是给WndProc函数一个WM_PAINT消息
    wndclass.lpfnWndProc = (WNDPROC) WndProc;  // 窗口过程函数 处理窗口打开时的窗口消息（如键盘，鼠标操作）
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance; // 当前程序的句柄
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 窗口图标
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // 窗口光标
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); // 窗口背景颜色
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName; // 窗口类的名字 内部标识 在外部无显示 用于区分窗口类别（在有多窗口的时候）

    if (!RegisterClass(&wndclass)) {
        MessageBox(NULL, "ERROR", szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName,
                        "The Windows Program",
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

    // 显示并更新窗口    iCmdShow 指定窗口的显示方式（最大化 最小化）
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); // 将窗口消息转换为编译器的 WM 消息
        DispatchMessage(&msg); // 将 msg 消息传给 WinProc 在这里调用 WinProc函数 (wndclass.lpfnWndProc 指定的函数)
    }
    return msg.wParam;
}
```

#### 代码讲解

##### `WNDCLASS`类
**窗口类** 一种模板或蓝图，指定窗口的类型和一些基础数据，告诉操作系统如何处理窗口实例  
`style`  
`lpfnWndProc`  
`dbClsExtra cbWndRxtra`  
`hInstance`  
`hIcon`  
`hCursor`  
`hbrBackground`  
`lpszMenuName`  
`lpszClassName`  





### 消息处理函数

#### 主框架
```c
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  
    // 写入项目需求的一些前置变量

    // 写入设计中考虑到的消息情况 并给出相应的处理
    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    // 如果在sitch中没有被捕获 则使用默认函数处理信息
    return DefWindowProc(hwnd, message, wParam, lParam);
}
```