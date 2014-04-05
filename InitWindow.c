#include "InitWindow.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <stdio.h>

//#define WIN32

void draw(GLfloat aspect, GLfloat mouse_coord_x, GLfloat mouse_coord_y, GLboolean *bQuit);
void init_OpenGL();

void fatal_error(const char *error)
{
    FILE *f=fopen("error.log", "wt");

    fprintf(f, error);

    fclose(f);
    exit(1);
}

void init_OpenGL()
{
    /*
    GLfloat ambient[]={0, 0, 0, 1};
    GLfloat specular[]={1, 1, 1, 1};*/

    /*
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);*/
    glEnable(GL_COLOR_MATERIAL);
    /*glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING)*/

    glEnable(GL_TEXTURE_2D);

    /*glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);*/
}

#ifdef WIN32

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

void init_and_run_window(Config *cfg)
{
    HINSTANCE hInstance=0;
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    GLboolean bQuit=GL_FALSE;

    GLfloat aspect=(GLfloat)cfg->width / (GLfloat)cfg->height;
    POINT coord;
    GLfloat mouse_coord_x, mouse_coord_y;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) return;

    DEVMODE  DevMode, restore;

    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &restore);
    ZeroMemory(&DevMode, sizeof(DevMode));
    DevMode.dmSize = sizeof(DevMode);
    DevMode.dmPelsHeight=cfg->height;
    DevMode.dmPelsWidth=cfg->width;
    DevMode.dmDisplayFrequency=cfg->fps;
    DevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    ChangeDisplaySettingsEx(NULL, &DevMode, NULL, CDS_UPDATEREGISTRY | CDS_RESET, NULL);

    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "Алгоритм Бухбергера",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          cfg->width,
                          cfg->height,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    EnableOpenGL(hwnd, &hDC, &hRC);
    init_OpenGL();
    BuildFont(&hDC);

    while (!bQuit)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) bQuit = GL_TRUE;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            GetCursorPos(&coord);
            mouse_coord_x=(float)coord.x/(float)cfg->width*2-1;
            mouse_coord_y=1-(float)coord.y/(float)cfg->height*2;

            glClearColor(1.0f, 1.0f, 1.0f, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            draw(aspect, mouse_coord_x*aspect, mouse_coord_y, &bQuit);
            Sleep(1000.0f/cfg->fps);
            SwapBuffers(hDC);
        }
    }

    ChangeDisplaySettingsEx(NULL,
                                 &restore,
                                 NULL,
                                 CDS_UPDATEREGISTRY | CDS_RESET,
                                 NULL);

    DisableOpenGL(hwnd, hDC, hRC);
    DestroyWindow(hwnd);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE: PostQuitMessage(0); break;
        case WM_DESTROY: return 0;
        case WM_KEYDOWN: if(wParam==VK_ESCAPE) PostQuitMessage(0); break;

        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;
    *hDC = GetDC(hwnd);
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, iFormat, &pfd);
    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

#endif // WIN32

#define __linux__

#ifdef __linux__

#include <unistd.h>
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/keysym.h>

static int snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};
static int dblBuf[]  = {GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None};

void init_and_run_window(Config *cfg)
{
    Display   *dpy;
    Window     win;
    XVisualInfo         *vi;
    Colormap             cmap;
    XSetWindowAttributes swa;
    GLXContext           cx;
    XEvent               event;
    GLboolean            bQuit = GL_FALSE;
    int                  dummy;
    static int i=0;

    GLfloat aspect=(GLfloat)cfg->width / (GLfloat)cfg->height;
    GLfloat mouse_coord_x, mouse_coord_y;

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) fatal_error("could not open display");
    if(!glXQueryExtension(dpy, &dummy, &dummy)) fatal_error("X server has no OpenGL GLX extension");

    vi = glXChooseVisual(dpy, DefaultScreen(dpy), dblBuf);
    if (vi == NULL)
    {
        vi = glXChooseVisual(dpy, DefaultScreen(dpy), snglBuf);
        if (vi == NULL) fatal_error("no RGB visual with depth buffer");
    }

    if(vi->class != TrueColor) fatal_error("TrueColor visual required for this program");

    cx = glXCreateContext(dpy, vi, None, GL_TRUE);
    if (cx == NULL) fatal_error("could not create rendering context");

    cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen), vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = KeyPressMask    | ExposureMask
                 | ButtonPressMask | StructureNotifyMask;
    win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0,
                        cfg->width, cfg->height, 0, vi->depth, InputOutput, vi->visual,
                        CWBorderPixel | CWColormap | CWEventMask, &swa);
    XSetStandardProperties(dpy, win, "main", "main", None,
                           0, 0, NULL);

    glXMakeCurrent(dpy, win, cx);

    XMapWindow(dpy, win);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, cfg->width, cfg->height);

    while (bQuit==GL_FALSE)
    {
        if(XPending(dpy)) XNextEvent(dpy, &event);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw(aspect, mouse_coord_x, mouse_coord_y, &bQuit);
        glXSwapBuffers(dpy, win);
        usleep(1000000.0f/cfg->fps);
    }
}
#endif // __linux__
