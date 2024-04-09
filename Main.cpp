// #include <stdio.h>
// #include <string.h>
// #include <dlfcn.h>
// #include "AqKanji2Koe.h"
// #include "AquesTalk.h"

// #define MAX_INPUT_LENGTH 1024

// using namespace std;

// int main(int argc, char **argv)
// {
//     int iret;
//     int size;
//     char str[MAX_INPUT_LENGTH];
//     const char *voice_type;
//     void *handle;
//     unsigned char* (*synthe_func)(const char*, int, int*);
//     void (*free_wave_func)(unsigned char*);

//     // 音声記号列を入力
//     if (fgets(str, MAX_INPUT_LENGTH, stdin) == NULL) {
//         fprintf(stderr, "Failed to read input.\n");
//         return 1;
//     }

//     // 入力の長さをチェック
//     if (strlen(str) >= MAX_INPUT_LENGTH - 1) {
//         fprintf(stderr, "Input is too long. Maximum length is %d.\n", MAX_INPUT_LENGTH - 1);
//         return 1;
//     }

//     // 音声タイプを取得
//     if (argc > 1) {
//         voice_type = argv[1];
//     } else {
//         voice_type = "f1";
//     }

//     // 音声タイプに基づいてライブラリをロード
//     char lib_path[256];
//     snprintf(lib_path, sizeof(lib_path), "/usr/local/lib/aquestalk/lib64/%s/libAquesTalk.so", voice_type);
//     handle = dlopen(lib_path, RTLD_LAZY);
//     if (handle == NULL) {
//         fprintf(stderr, "Failed to load library: %s\n", dlerror());
//         return 1;
//     }

//     // 音声合成関数を取得
//     *(void **)(&synthe_func) = dlsym(handle, "AquesTalk_Synthe_Utf8");
//     if (synthe_func == NULL) {
//         fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
//         dlclose(handle);
//         return 1;
//     }

//     // メモリ解放関数を取得
//     *(void **)(&free_wave_func) = dlsym(handle, "AquesTalk_FreeWave");
//     if (free_wave_func == NULL) {
//         fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
//         dlclose(handle);
//         return 1;
//     }

//     // 音声合成
//     unsigned char *wav = synthe_func(str, 100, &size);
//     if (wav == NULL) {
//         fprintf(stderr, "ERR:%d\n", size);
//         dlclose(handle);
//         return 1;
//     }

//     // 音声データの出力
//     fwrite(wav, 1, size, stdout);

//     // メモリとライブラリのハンドルを解放
//     free_wave_func(wav);
//     dlclose(handle);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AqKanji2Koe.h"

#define NSTR 4096

int main(int argc, char **argv) {
    char kanji[NSTR]; // 入力される漢字かな混じり文
    char koe[NSTR];   // 変換後の音声記号列を格納するバッファ
    void *hAqKanji2Koe;
    int iret;
    const char *pathDic = "/usr/local/lib/aqkanji2koe/aq_dic";

    // AqKanji2Koeライブラリの初期化
    hAqKanji2Koe = AqKanji2Koe_Create(pathDic, &iret);
    if (hAqKanji2Koe == NULL) {
        fprintf(stderr, "辞書の初期化に失敗しました: %d\n", iret);
        return 1;
    }

    // 標準入力からテキストを読み込み
    printf("漢字かな混じり文を入力してください: ");
    if (fgets(kanji, NSTR, stdin) == NULL) {
        fprintf(stderr, "入力の読み込みに失敗しました\n");
        AqKanji2Koe_Release(hAqKanji2Koe);
        return 1;
    }

    // テキストを音声記号列に変換
    iret = AqKanji2Koe_Convert(hAqKanji2Koe, kanji, koe, NSTR);
    if (iret != 0) {
        fprintf(stderr, "テキストの変換に失敗しました: %d\n", iret);
    } else {
        printf("音声記号列: %s\n", koe);
    }

    // リソースの解放
    AqKanji2Koe_Release(hAqKanji2Koe);

    return 0;
}

