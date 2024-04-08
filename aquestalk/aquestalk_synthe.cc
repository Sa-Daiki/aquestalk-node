#include <napi.h>
#include "AquesTalk.h"

Napi::Value Synthesize(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // 引数の検証
  if (info.Length() < 1 || !info[0].IsString()) {
    Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    return env.Null();
  }

  // 引数から文字列を取得
  std::string text = info[0].As<Napi::String>().Utf8Value();
  int size;

  // 音声合成
  unsigned char *wav = AquesTalk_Synthe_Utf8(const_cast<char*>(text.c_str()), 100, &size);
  if (wav == nullptr) {
    Napi::Error::New(env, "Failed to synthesize voice").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Node.jsのBufferとして音声データを返す
  Napi::Buffer<unsigned char> buffer = Napi::Buffer<unsigned char>::Copy(env, wav, size);

  AquesTalk_FreeWave(wav);

  return buffer;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "synthesize"), Napi::Function::New(env, Synthesize));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
