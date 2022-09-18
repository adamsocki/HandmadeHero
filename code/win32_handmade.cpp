#include <windows.h>

LRESULT CALLBACK
MainWindowCallback( HWND window,
					UINT Message,
					WPARAM WParam,
					LPARAM LParam)
{
	LRESULT result = 0;

	switch (Message)
	{
		case WM_SIZE:
		{
			OutputDebugStringA("WM_SIZE\n");
		} break;
		case WM_DESTROY:
		{
			OutputDebugStringA("WM_DESTROY\n");
		} break;
		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WM_ACTIVATEAPP\n");
		} break;
		case WM_CLOSE:
		{
			OutputDebugStringA("WM_CLOSE\n");
		} break;
		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(window, &paint);
			int windowX = paint.rcPaint.left;
			int windowY = paint.rcPaint.top;
			int windowWidth = paint.rcPaint.right - paint.rcPaint.left;
			int windowHeight = paint.rcPaint.bottom - paint.rcPaint.top; 
			PatBlt(deviceContext, windowX, windowY, windowWidth, windowHeight, WHITENESS);
			EndPaint(window, &paint);
		} break;
		default:
		{
			//OutputDebugStringA("default\n");
			result = DefWindowProc(window, Message, WParam, LParam);
		} break;

	}
	return(result);
}


int CALLBACK
WinMain(HINSTANCE Instance,
	HINSTANCE PrevInstance,
	LPSTR CommandLine,
	int ShowCode)
{
		
	WNDCLASS WindowClass = {};

	WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWindowCallback;
	WindowClass.hInstance = Instance;
	WindowClass.lpszClassName = "HandmadeHeroWindowClass";
	//MessageBox(0, "This is my game.", "Adam's Game", MB_OK|MB_ICONINFORMATION);


	if (RegisterClass(&WindowClass))
	{
		HWND WindowHandle = CreateWindowEx(0, WindowClass.lpszClassName, "Handmade Hero", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, Instance, 0);
		if (WindowHandle) {
			MSG Message;
			for (;;) {
				BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
				if (MessageResult > 0) {
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else {
					break;
				}
			}

		}
		else {
				// TODO: LOGGING
		}

		
		
	}
	else {
		// TODO: Logging
	}

	return(0);

}
		