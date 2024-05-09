#include <stdio.h>
#include <stdint.h>

// PI4端子の設定
#define REG_PICR (*((volatile uint32_t*)0x40000300))
#define REG_PIDATA (*((volatile uint32_t*)0x400C0300))

// PI4端子を入力に設定
void setup_PI4_input() {
    REG_PICR &= ~(1 << 4); // PI4端子を入力に設定
}

// PI4端子の入力レベルを取得し、printfで表示
void print_PI4_input() {
    uint32_t input_level = (REG_PIDATA >> 4) & 0x01; // PI4端子の入力レベルを取得
    if (input_level)
        printf("Input voltage level: [H]\n");
    else
        printf("Input voltage level: [L]\n");
}

int main() {
    setup_PI4_input(); // PI4端子を入力に設定

    // テスト用の無限ループ
    while (1) {
        print_PI4_input(); // PI4端子の入力レベルを表示
    }

    return 0;
}
