#include <windows.h>

#include <cstdio>

#define VK_LETTER_A 0x41
#define VK_LETTER_S 0x53
#define VK_LETTER_D 0x44
#define VK_LETTER_F 0x46

// 1P
#define VK_A VK_LETTER_A
#define VK_B VK_LETTER_S
#define VK_C VK_LETTER_D
#define VK_D VK_LETTER_F
#define VK_FORWARD VK_RIGHT
#define VK_BACKWARD VK_LEFT
#define VK_JUMP VK_UP
#define VK_CROUCH VK_DOWN

#define KEYDOWN(vk_code) ((::GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) ((::GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

int _tmain(int argc, int argv)
{
    while (true) {
        Sleep(20); // wait for directive

        if (KEYDOWN(0x41)) {
            fprintf(stderr, "d");
        }
    }
    return 0;
}