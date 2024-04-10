#include <dlfcn.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AqKanji2Koe.h"
#include "AquesTalk.h"

#define MAX_INPUT_LENGTH 1024

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [input text] [voice type]\n", argv[0]);
        fprintf(stderr, "Using default values: input text = 'デフォルトのテキスト', voice type = 'f1'.\n");
        argv[1] = "デフォルトのテキスト";
        argv[2] = "f1";
    }

    const char *inputText = argv[1];  // 入力テキスト
    const char *voiceType = argv[2];  // 音声のタイプ

    // AqKanji2Koeの初期化
    const char *pathDic = "/usr/local/lib/aqkanji2koe/aq_dic";
    void *hAqKanji2Koe;
    char koe[MAX_INPUT_LENGTH]; // 変換後の音声記号列を格納
    int iret;
    
    hAqKanji2Koe = AqKanji2Koe_Create(pathDic, &iret);
    if (hAqKanji2Koe == NULL) {
        fprintf(stderr, "辞書の初期化に失敗しました: %d\n", iret);
        return 1;
    }

    // 入力テキストを音声記号列に変換
    iret = AqKanji2Koe_Convert(hAqKanji2Koe, inputText, koe, MAX_INPUT_LENGTH);
    if (iret != 0) {
        fprintf(stderr, "テキストの変換に失敗しました: %d\n", iret);
        AqKanji2Koe_Release(hAqKanji2Koe);
        return 1;
    }

    // AqKanji2Koeライブラリの解放
    AqKanji2Koe_Release(hAqKanji2Koe);

    // AquesTalkの処理
    void *handle;
    unsigned char* (*synthe_func)(const char*, int, int*);
    void (*free_wave_func)(unsigned char*);
    unsigned char *wav;
    int size;

    // AquesTalkライブラリのロード
    char lib_path[256];
    snprintf(lib_path, sizeof(lib_path), "/usr/local/lib/aquestalk/lib64/%s/libAquesTalk.so", voiceType);
    handle = dlopen(lib_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "ライブラリのロードに失敗: %s\n", dlerror());
        return 1;
    }

    // 音声合成関数を取得
    *(void **)(&synthe_func) = dlsym(handle, "AquesTalk_Synthe_Utf8");
    if (synthe_func == NULL) {
        fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // メモリ解放関数を取得
    *(void **)(&free_wave_func) = dlsym(handle, "AquesTalk_FreeWave");
    if (free_wave_func == NULL) {
        fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // 音声合成を実行
    printf("音声記号列: %s\n", koe);
    wav = synthe_func(koe, 100, &size);
    if (!wav) {
        fprintf(stderr, "音声合成に失敗: %d\n", size);
        dlclose(handle);
        return 1;
    }

    // // 音声データを標準出力に書き出し
    // fwrite(wav, size, 1, stdout);

    FILE *file = fopen("/app/output.wav", "wb");
    if (file == NULL) {
        fprintf(stderr, "ファイルを開けませんでした。\n");
        return 1;
    }

    // wav が指すバイナリデータをファイルに書き込みます。
    size_t written = fwrite(wav, 1, size, file);
    if (written < size) {
        fprintf(stderr, "ファイルへの書き込み中にエラーが発生しました。\n");
    }

    // ファイルを閉じます。
    fclose(file);

    // メモリの解放
    free_wave_func(wav);

    // ライブラリの解放
    dlclose(handle);

    std::cout << "音声合成が完了しました。終了するには Enter キーを押してください。" << std::endl;
    std::cin.get();

    return 0;
}
