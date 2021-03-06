#include <windows.h>
#include <tchar.h>

#include <cstdio>
#include <vector>

using std::vector;

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

class HoldDown { // 压键
public:
    HoldDown(void) : jump(false), backward(false), crouch(false), forward(false),
        a(false), b(false), c(false), d(false)
    {}

    bool jump, backward, crouch, forward;
    bool a,b,c,d;
};

void PrintOrigKeySeq(vector<int> q) {
    vector<int>::iterator it;
    for (it = q.begin(); it != q.end(); ++it) {
        fprintf(stderr, "%X",*it);
    }
    fprintf(stderr, "\n");
}

int _tmain(int argc, int argv)
{
    vector<int> orig_key_seq(16); // 原始按键序列
    vector<int>::size_type last_size;
    HoldDown hold_down;

    while (true) {
        last_size = orig_key_seq.size();

        Sleep(20); // wait for directive

        // direction
        if (!hold_down.jump && KEYDOWN(VK_JUMP)) {
            hold_down.jump = true;
            orig_key_seq.push_back(0x08);
        }
        if (hold_down.jump && KEYUP(VK_JUMP)) {
            hold_down.jump = false;
            orig_key_seq.push_back(0xF8);
        }

        if (!hold_down.backward && KEYDOWN(VK_BACKWARD)) {
            hold_down.backward = true;
            orig_key_seq.push_back(0x04);
        }
        if (hold_down.backward && KEYUP(VK_BACKWARD)) {
            hold_down.backward = false;
            orig_key_seq.push_back(0xF4);
        }

        if (!hold_down.crouch && KEYDOWN(VK_CROUCH)) {
            hold_down.crouch = true;
            orig_key_seq.push_back(0x02);
        }
        if (hold_down.crouch && KEYUP(VK_CROUCH)) {
            hold_down.crouch = false;
            orig_key_seq.push_back(0xF2);
        }

        if (!hold_down.forward && KEYDOWN(VK_FORWARD)) {
            hold_down.forward = true;
            orig_key_seq.push_back(0x06);
        }
        if (hold_down.forward && KEYUP(VK_FORWARD)) {
            hold_down.forward = false;
            orig_key_seq.push_back(0xF6);
        }

        // ABCD
        if (!hold_down.a && KEYDOWN(VK_A)) {
            hold_down.a = true;
            orig_key_seq.push_back(0x0A);
        }
        if (hold_down.a && KEYUP(VK_A)) {
            hold_down.a = false;
            orig_key_seq.push_back(0xFA);
        }

        if (!hold_down.b && KEYDOWN(VK_B)) {
            hold_down.b = true;
            orig_key_seq.push_back(0x0B);
        }
        if (hold_down.b && KEYUP(VK_B)) {
            hold_down.b = false;
            orig_key_seq.push_back(0xFB);
        }

        if (!hold_down.c && KEYDOWN(VK_C)) {
            hold_down.c = true;
            orig_key_seq.push_back(0x0C);
        }
        if (hold_down.c && KEYUP(VK_C)) {
            hold_down.c = false;
            orig_key_seq.push_back(0xFC);
        }

        if (!hold_down.d && KEYDOWN(VK_D)) {
            hold_down.d = true;
            orig_key_seq.push_back(0x0D);
        }
        if (hold_down.d && KEYUP(VK_D)) {
            hold_down.d = false;
            orig_key_seq.push_back(0xFD);
        }

        // 提取指令
        if (last_size < orig_key_seq.size()) {
            PrintOrigKeySeq(orig_key_seq);
        }

        do {
            // 清空指令
            static int blockcount = 0;

            if (blockcount < 20) {
                ++blockcount;
                break;
            }

            blockcount = 0;
            orig_key_seq.clear();
        } while (0);
    }
    return 0;
}