#include <windows.h>
#include <WinUser.h>
#include <locale.h>

void Clipboard(char str[], int length)
{
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, length * sizeof(CHAR*));
    LPVOID gl = GlobalLock(h);
 
    memcpy(gl, str, length * sizeof(CHAR*));
 
    GlobalUnlock(gl);
 
    OpenClipboard(NULL); // hWnd is set to NULL
    EmptyClipboard(); // Sets clipboard ownership to someone don't know
    SetClipboardData(CF_TEXT, h);  // Successfully data to clipboard!
    CloseClipboard();
}

void ctrl_v_enter()
{
    INPUT enter;
    INPUT ctrl_v[2];

    // Pause for 5 seconds.

    // Set up a generic keyboard event.
    enter.type = INPUT_KEYBOARD;
    enter.ki.wScan = 0; // hardware scan code for key
    enter.ki.time = 0;
    enter.ki.dwExtraInfo = 0;
    enter.ki.wVk = VK_RETURN; 
    enter.ki.dwFlags = 0; // 0 for key press

    ctrl_v[0].type = INPUT_KEYBOARD;
    ctrl_v[0].ki.wScan = 0; // hardware scan code for key
    ctrl_v[0].ki.time = 0;
    ctrl_v[0].ki.dwExtraInfo = 0;
    ctrl_v[0].ki.wVk = VK_CONTROL; // virtual-key code for the "a" key
    ctrl_v[0].ki.dwFlags = 0; // 0 for key press

    ctrl_v[1].type = INPUT_KEYBOARD;
    ctrl_v[1].ki.wScan = 0; // hardware scan code for key
    ctrl_v[1].ki.time = 0;
    ctrl_v[1].ki.dwExtraInfo = 0;
    ctrl_v[1].ki.wVk = 0x56; 
    ctrl_v[1].ki.dwFlags = 0; // 0 for key press

    SendInput(2, ctrl_v, sizeof(INPUT));
    
    // Release the "A" key
    ctrl_v[0].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    ctrl_v[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, ctrl_v, sizeof(INPUT));

    SendInput(1, &enter, sizeof(INPUT));
    enter.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &enter, sizeof(INPUT));
    //enter.ki.dwFlags = 0;
    //SendInput(1, &enter, sizeof(INPUT));
    //enter.ki.dwFlags = KEYEVENTF_KEYUP;
    //SendInput(1, &enter, sizeof(INPUT));
}

void clibord(const char* text, int length)
{
    if(OpenClipboard(0))//открываем буфер обмена
        {
        HGLOBAL hgBuffer;
        char* chBuffer;
        EmptyClipboard(); //очищаем буфер
        hgBuffer= GlobalAlloc(GMEM_DDESHARE, length + 1);//выделяем память
        chBuffer= (char*)GlobalLock(hgBuffer); //блокируем память
        strcpy(chBuffer, LPCSTR(text));
        GlobalUnlock(hgBuffer);//разблокируем память
        SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
        CloseClipboard(); //закрываем буфер обмена
        }
}

int main()
{
    

    Sleep(5000);
    for(int i = 0; i < 20; ++i)
    {
        clibord("people are so weak", 19);
        ctrl_v_enter();

        Sleep(50);


        clibord("admin LOX", 10);
        ctrl_v_enter();

        Sleep(50);

        clibord("https://tenor.com/view/fuhrer-cat-gas-gif-25955244", 51);
        ctrl_v_enter();

        Sleep(50);

        clibord("https://tenor.com/view/kiss-gif-25984898", 41);
        ctrl_v_enter();

        Sleep(50);

        clibord("https://tenor.com/view/felix-argyle-cute-smile-gif-13483002", 60);
        ctrl_v_enter();

        Sleep(50);

        clibord("https://tenor.com/view/good-night-gif-23040113", 47);
        ctrl_v_enter();

        Sleep(50);
        
    }
        

    return 0;
}