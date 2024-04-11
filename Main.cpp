// #include <dlfcn.h>
// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "AqKanji2Koe.h"
// #include "AquesTalk.h"

// #define MAX_INPUT_LENGTH 1024

// int main(int argc, char **argv) {
//     if (argc < 3) {
//         fprintf(stderr, "Usage: %s [input text] [voice type]\n", argv[0]);
//         fprintf(stderr, "Using default values: input text = 'デフォルトのテキスト', voice type = 'f1'.\n");
//         argv[1] = "デフォルトのテキスト";
//         argv[2] = "f1";
//     }

//     const char *inputText = argv[1];  // 入力テキスト
//     const char *voiceType = argv[2];  // 音声のタイプ

//     // AqKanji2Koeの初期化
//     const char *pathDic = "/usr/local/lib/aqkanji2koe/aq_dic";
//     void *hAqKanji2Koe;
//     char koe[MAX_INPUT_LENGTH]; // 変換後の音声記号列を格納
//     int iret;
    
//     hAqKanji2Koe = AqKanji2Koe_Create(pathDic, &iret);
//     if (hAqKanji2Koe == NULL) {
//         fprintf(stderr, "辞書の初期化に失敗しました: %d\n", iret);
//         return 1;
//     }

//     // 入力テキストを音声記号列に変換
//     iret = AqKanji2Koe_Convert(hAqKanji2Koe, inputText, koe, MAX_INPUT_LENGTH);
//     if (iret != 0) {
//         fprintf(stderr, "テキストの変換に失敗しました: %d\n", iret);
//         AqKanji2Koe_Release(hAqKanji2Koe);
//         return 1;
//     }

//     // AqKanji2Koeライブラリの解放
//     AqKanji2Koe_Release(hAqKanji2Koe);

//     // AquesTalkの処理
//     void *handle;
//     unsigned char* (*synthe_func)(const char*, int, int*);
//     void (*free_wave_func)(unsigned char*);
//     unsigned char *wav;
//     int size;

//     // AquesTalkライブラリのロード
//     char lib_path[256];
//     snprintf(lib_path, sizeof(lib_path), "/usr/local/lib/aquestalk/lib64/%s/libAquesTalk.so", voiceType);
//     handle = dlopen(lib_path, RTLD_LAZY);
//     if (!handle) {
//         fprintf(stderr, "ライブラリのロードに失敗: %s\n", dlerror());
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

//     // 音声合成を実行
//     printf("音声記号列: %s\n", koe);
//     wav = synthe_func(koe, 100, &size);
//     if (!wav) {
//         fprintf(stderr, "音声合成に失敗: %d\n", size);
//         dlclose(handle);
//         return 1;
//     }

//     // // 音声データを標準出力に書き出し
//     // fwrite(wav, size, 1, stdout);

//     FILE *file = fopen("/app/output.wav", "wb");
//     if (file == NULL) {
//         fprintf(stderr, "ファイルを開けませんでした。\n");
//         return 1;
//     }

//     // wav が指すバイナリデータをファイルに書き込みます。
//     size_t written = fwrite(wav, 1, size, file);
//     if (written < size) {
//         fprintf(stderr, "ファイルへの書き込み中にエラーが発生しました。\n");
//     }

//     // ファイルを閉じます。
//     fclose(file);

//     // メモリの解放
//     free_wave_func(wav);

//     // ライブラリの解放
//     dlclose(handle);

//     std::cout << "音声合成が完了しました。終了するには Enter キーを押してください。" << std::endl;
//     std::cin.get();

//     return 0;
// }

// #include <crow.h>

// int main()
// {
//     crow::SimpleApp app;

//     CROW_ROUTE(app, "/")
//     .methods("POST"_method)
//     ([](const crow::request& req){
//         auto body = crow::json::load(req.body);
//         if (!body)
//             return crow::response(400);

//         std::string speaker = body["speaker"].s();
//         std::string text = body["text"].s();

//         // ここで取得したspeakerとtextを使って処理を行う

//         return crow::response(200);
//     });

//     app.port(8080).run();
//     return 0;
// }

#include <crow.h>
#include <string>
#include <fstream>
#include <dlfcn.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AqKanji2Koe.h"
#include "AquesTalk.h"

#define MAX_INPUT_LENGTH 1024

int main()
{
   crow::SimpleApp app;

   CROW_ROUTE(app, "/")
   .methods("POST"_method)
   ([](const crow::request& req){
       auto body = crow::json::load(req.body);
       if (!body)
           return crow::response(400);

       std::string speaker = body["speaker"].s();
       std::string text = body["text"].s();

       // ここで取得したspeakerとtextを使って音声合成処理を行い、wavファイルを生成する
       const char *inputText = text.c_str();  // 入力テキスト
       const char *voiceType = speaker.c_str();  // 音声のタイプ

       // AqKanji2Koeの初期化
       const char *pathDic = "/usr/local/lib/aqkanji2koe/aq_dic";
       void *hAqKanji2Koe;
       char koe[MAX_INPUT_LENGTH]; // 変換後の音声記号列を格納
       int iret;
       
       hAqKanji2Koe = AqKanji2Koe_Create(pathDic, &iret);
       if (hAqKanji2Koe == NULL) {
           fprintf(stderr, "辞書の初期化に失敗しました: %d\n", iret);
           return crow::response(500);
       }

       // 入力テキストを音声記号列に変換
       iret = AqKanji2Koe_Convert(hAqKanji2Koe, inputText, koe, MAX_INPUT_LENGTH);
       if (iret != 0) {
           fprintf(stderr, "テキストの変換に失敗しました: %d\n", iret);
           AqKanji2Koe_Release(hAqKanji2Koe);
           return crow::response(500);
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
           return crow::response(500);
       }

       // 音声合成関数を取得
       *(void **)(&synthe_func) = dlsym(handle, "AquesTalk_Synthe_Utf8");
       if (synthe_func == NULL) {
           fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
           dlclose(handle);
           return crow::response(500);
       }

       // メモリ解放関数を取得
       *(void **)(&free_wave_func) = dlsym(handle, "AquesTalk_FreeWave");
       if (free_wave_func == NULL) {
           fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
           dlclose(handle);
           return crow::response(500);
       }

       // 音声合成を実行
       printf("音声記号列: %s\n", koe);
       wav = synthe_func(koe, 100, &size);
       if (!wav) {
           fprintf(stderr, "音声合成に失敗: %d\n", size);
           dlclose(handle);
           return crow::response(500);
       }

       std::string wav_file_path = "/app/output.wav";
       FILE *file = fopen(wav_file_path.c_str(), "wb");
       if (file == NULL) {
           fprintf(stderr, "ファイルを開けませんでした。\n");
           free_wave_func(wav);
           dlclose(handle);
           return crow::response(500);
       }

       // wav が指すバイナリデータをファイルに書き込みます。
       size_t written = fwrite(wav, 1, size, file);
       if (written < size) {
           fprintf(stderr, "ファイルへの書き込み中にエラーが発生しました。\n");
           free_wave_func(wav);
           dlclose(handle);
           fclose(file);
           return crow::response(500);
       }

       // ファイルを閉じます。
       fclose(file);

       // メモリの解放
       free_wave_func(wav);

       // ライブラリの解放
       dlclose(handle);

       // wavファイルをバイナリモードで読み込む
       std::ifstream wav_file(wav_file_path, std::ios::binary);

       // wavファイルのサイズを取得する
       wav_file.seekg(0, std::ios::end);
       size_t wav_file_size = wav_file.tellg();
       wav_file.seekg(0, std::ios::beg);

       // wavファイルのデータを格納するバッファを用意する
       std::vector<char> wav_data(wav_file_size);

       // バッファにwavファイルのデータを読み込む
       wav_file.read(wav_data.data(), wav_file_size);

       // wavファイルを閉じる
       wav_file.close();

       // レスポンスヘッダーを設定する
       crow::response res;
       res.set_header("Content-Type", "audio/wav");
       res.set_header("Content-Disposition", "attachment; filename=\"output.wav\"");
       res.set_header("Content-Length", std::to_string(wav_file_size));

       // レスポンスボディにwavファイルのデータを設定する
       res.body = std::string(wav_data.begin(), wav_data.end());

       return res;
   });

   app.port(8080).run();
   return 0;
}