#include <node.h>
#include <node_buffer.h>
#include <windows.h>
using namespace v8;

enum ClickType
{
    LEFT,
    RIGHT
};

void click(const FunctionCallbackInfo<Value> &args, ClickType type)
{
    HWND hwnd = (HWND)((int)args[0]->NumberValue());
    int x = args[1]->NumberValue();
    int y = args[2]->NumberValue();

    v8::Isolate *isolate = args.GetIsolate();
    v8::HandleScope scope(isolate);

    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);

    POINT clientPos;
    clientPos.x = 0;
    clientPos.y = 0;
    ClientToScreen(hwnd, &clientPos);
    int clientOffset = (clientPos.y - windowRect.top);
    y += clientOffset;

    if (type == ClickType::LEFT)
    {
        PostMessage(hwnd, WM_LBUTTONDOWN, 0, MAKELPARAM(x, y));
        PostMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(x, y));
    }

    if (type == ClickType::RIGHT)
    {
        PostMessage(hwnd, WM_RBUTTONDOWN, 0, MAKELPARAM(x, y));
        PostMessage(hwnd, WM_RBUTTONUP, 0, MAKELPARAM(x, y));
    }
}

void leftClick(const FunctionCallbackInfo<Value> &args)
{
    click(args, ClickType::LEFT);
}

void rightClick(const FunctionCallbackInfo<Value> &args)
{
    click(args, ClickType::RIGHT);
}



HWND g_HWND=NULL;
int pid = 0;
BOOL CALLBACK EnumWindowsProcMy(HWND hwnd,LPARAM lParam)
{
      DWORD lpdwProcessId;
    GetWindowThreadProcessId(hwnd,&lpdwProcessId);
    if(lpdwProcessId==lParam)
    {
        g_HWND=hwnd;
        return FALSE;
    }
    return TRUE;
}


void getHwndFromPid(const FunctionCallbackInfo<Value> &args)
{
    int pidarg = ((int)args[0]->NumberValue());
    v8::Isolate *isolate = args.GetIsolate();
    v8::HandleScope scope(isolate);
    pid = pidarg;
    EnumWindows(EnumWindowsProcMy,pid);

    args.GetReturnValue().Set(Number::New(isolate, (int)g_HWND));
}

void getMousePosition(const FunctionCallbackInfo<Value> &args)
{
    HWND hwnd = (HWND)((int)args[0]->NumberValue());
    v8::Isolate *isolate = args.GetIsolate();
    v8::HandleScope scope(isolate);

    POINT p;

    GetCursorPos(&p);

    if (hwnd != 0)
        ScreenToClient(hwnd, &p);

    Local<Number> x = Number::New(isolate, p.x);
    Local<Number> y = Number::New(isolate, p.y);
    Local<Object> retval = Object::New(isolate);

    retval->Set(String::NewFromUtf8(isolate, "x"), x);
    retval->Set(String::NewFromUtf8(isolate, "y"), y);

    args.GetReturnValue().Set(retval);
}

void Init(Handle<Object> exports)
{
    NODE_SET_METHOD(exports, "leftClick", leftClick);
    NODE_SET_METHOD(exports, "rightClick", rightClick);
 NODE_SET_METHOD(exports, "getHwndFromPid", getHwndFromPid);
    NODE_SET_METHOD(exports, "getMousePosition", getMousePosition);
}

NODE_MODULE(addon, Init)