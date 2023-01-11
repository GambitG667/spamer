#include <windows.h> //использует системные библиотеки такчто хрен его знает чем их заменить на линукс
#include <WinUser.h>
#include <locale.h>
#include <time.h>


void ctrl_v_enter() // сама симуляция нажатий. 
{
    INPUT enter;
    INPUT ctrl_v[2];


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
    ctrl_v[0].ki.wVk = VK_CONTROL; // virtual-key code for the smth key
    ctrl_v[0].ki.dwFlags = 0; // 0 for key press

    ctrl_v[1].type = INPUT_KEYBOARD;
    ctrl_v[1].ki.wScan = 0; // hardware scan code for key
    ctrl_v[1].ki.time = 0;
    ctrl_v[1].ki.dwExtraInfo = 0;
    ctrl_v[1].ki.wVk = 0x56; 
    ctrl_v[1].ki.dwFlags = 0; // 0 for key press

    SendInput(2, ctrl_v, sizeof(INPUT));
    
    // Release the  key
    ctrl_v[0].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    ctrl_v[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, ctrl_v, sizeof(INPUT));
    
    Sleep(50); //Задержка нужна чтоб комп успевал переваривать нажатия, без неё он начинает лагать

    SendInput(1, &enter, sizeof(INPUT));
    enter.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &enter, sizeof(INPUT));

}

void clibord(const char* text, int length) //функция загрузки в буфер обмена со стековерфлоу
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
    srand(time(NULL));
    int delay = 500;  // минимальная задержка между сообщениями. Очень сильно зависит от инета, задается вручную. У меня инет говно, так что я ставил на 1000.
    int randomaiser = 100; //максимальная рандомная прибавка к задержке 100 - оптимально
    int number_retry = 10; // количество повторов, до 20 все работает неплохо. потом дикорд тормозит и набивается очередь сообщений.

    std::cout<<"input delay, randomaiser and retry: ";
    std::cin>> delay >> randomaiser >> number_retry;

    std::cout<<"OK. Wait 5 sec\n";
    Sleep(5000);
    std::cout<<"Let's go";
    for(int i = 0; i < number_retry; ++i)
    {

        clibord(" https://tenor.com/view/fuhrer-cat-gas-gif-25955244\n", 53);
        ctrl_v_enter();

        Sleep(delay + rand()%randomaiser); // рандомизация задержки

        clibord(" https://tenor.com/view/kiss-gif-25984898\n", 43);
        ctrl_v_enter();

        Sleep(delay + rand()%randomaiser);

        clibord(" https://tenor.com/view/felix-argyle-cute-smile-gif-13483002\n", 62);
        ctrl_v_enter();

        Sleep(delay + rand()%randomaiser);

        clibord(" https://tenor.com/view/good-night-gif-23040113\n", 49);
        ctrl_v_enter();

        Sleep(delay + rand()%randomaiser);

        clibord("https://tenor.com/view/gachi-fist-gachimuchi-team-gif-21227013\n", 64);
        ctrl_v_enter();

        Sleep(delay + rand()%randomaiser);

        clibord("https://tenor.com/view/%D0%BA%D1%83%D0%B7%D0%BD%D0%B5-%D1%81%D0%BF%D0%B8%D0%BB%D0%BB%D0%B5%D1%80-%D0%BA%D1%83%D0%B7%D0%BD%D0%B5%D1%83-%D0%BA%D1%83%D0%B7%D0%BD%D0%B5%D1%86-%D0%B3%D0%B5%D0%BD%D0%B0-gif-23203142\n", 210);
        ctrl_v_enter();

        Sleep(delay + rand()%randomaiser);
        
    }
        

    return 0;
}
