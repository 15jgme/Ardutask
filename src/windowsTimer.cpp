// #include <MultiTime.h>
// #include <windows.h>


// void CALLBACK myTimerProc(
//   HWND unnamedParam1,
//   UINT unnamedParam2,
//   UINT unnamedParam3,
//   DWORD unnamedParam4
// )
// {reinterpret_cast<MultiTime*>(unnamedParam2)->timerCallback();}


// int MultiTime::setTimer(int freq, Task * t)
// {
//     // const HWND hWnd = GetConsoleWindow();
//     TIMERPROC Timerproc;
//     auto res = SetTimer(NULL,                // handle to main window 
//                         (UINT)this,                   // timer identifier 
//                         1000,                     // 5-second interval 
//                         (TIMERPROC) &myTimerProc); // timer callback
//     return 1;
//     // Note: need to fill in timerproc
//     // https://docs.microsoft.com/en-us/windows/win32/winmsg/using-timers#creating-a-timer
// }