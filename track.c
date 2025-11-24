using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

class Program
{
    delegate void WinEventDelegate(IntPtr hWinEventHook, uint eventType,
        IntPtr hwnd, int idObject, int idChild, uint dwEventThread, uint dwmsEventTime);

    static WinEventDelegate procDelegate = new WinEventDelegate(WinEventProc);

    [DllImport("user32.dll")]
    static extern IntPtr SetWinEventHook(uint eventMin, uint eventMax,
        IntPtr hmodWinEventProc, WinEventDelegate lpfnWinEventProc,
        uint idProcess, uint idThread, uint dwFlags);

    const uint EVENT_OBJECT_LOCATIONCHANGE = 0x800B;
    const uint WINEVENT_OUTOFCONTEXT = 0;

    static void Main()
    {
        SetWinEventHook(EVENT_OBJECT_LOCATIONCHANGE, EVENT_OBJECT_LOCATIONCHANGE,
            IntPtr.Zero, procDelegate, 0, 0, WINEVENT_OUTOFCONTEXT);

        Console.WriteLine("Tracking window size changes...");
        Console.ReadLine();
    }

    static void WinEventProc(IntPtr hWinEventHook, uint eventType,
        IntPtr hwnd, int idObject, int idChild, uint dwEventThread, uint dwmsEventTime)
    {
        // idObject == 0 означает само окно
        if (idObject == 0)
        {
            Console.WriteLine($"Window {hwnd} changed size/position");
        }
    }
}
