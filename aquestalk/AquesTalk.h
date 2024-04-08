//////////////////////////////////////////////////////////////////////
/*!	@class	CAquesTalk

	@brief	規則音声合成エンジン AquesTalk1

  音声記号列から音声波形データをメモリ上に生成する
  出力音声波形は、8HKzサンプリング, 16bit,モノラル,WAVフォーマット


	@author	AQUEST Corp.

	@date	2006/05/08	Creation
	@date	2006/10/03	Ver.2.0
	@date	2006/10/12	Ver.2.1 .defファイルの使用と__stdcallの定義
	@date	2007/09/27	Ver.2.2 各種文字コードの記号列に対応
	@date	2020/12/01	Ver.1.7 多声種、バグフィックス
*/
//	このソースコードの利用条件については、
//	同梱の AqLicense.txt をご覧ください
//  COPYRIGHT (C) 2006 AQUEST CORP.
//////////////////////////////////////////////////////////////////////
#if !defined(_AQUESTALK_H_)
#define _AQUESTALK_H_
#ifdef __cplusplus
extern "C"{
#endif


/////////////////////////////////////////////
//!	音声記号列から音声波形を生成
//!	音声波形データは内部で領域確保される。
//!	音声波形データの解放は本関数の呼び出し側でAquesTalk_FreeWave()にて行う
//! @param	koe[in]		音声記号列（SJIS NULL終端）
//! @param	iSpeed[in]	発話速度 [%] 50-300 の間で指定
//!	@param	pSize[out]	生成した音声データのサイズ[byte]（エラーの場合はエラーコードが返る）
//!	@return	WAVフォーマットの音声データの先頭アドレス。エラー時はNULLが返る
unsigned char * AquesTalk_Synthe(const char *koe, int iSpeed, int *pSize);

//! @param	koe[in]		音声記号列（EUC NULL終端）
unsigned char * AquesTalk_Synthe_Euc(const char *koe, int iSpeed, int *pSize);

//! @param	koe[in]		音声記号列（UTF8 NULL終端 BOMはつけられない）
unsigned char * AquesTalk_Synthe_Utf8(const char *koe, int iSpeed, int *pSize);

//! @param	koe[in]		音声記号列（UTF16 NULL終端 BOMの有無は問わない　エンディアンは実行環境に従う）
unsigned char * AquesTalk_Synthe_Utf16(const unsigned short *koe, int iSpeed, int *pSize);

//! @param	koe[in]		音声記号列（ローマ字表記 NULL終端）
unsigned char * AquesTalk_Synthe_Roman(const char *koe, int iSpeed, int *pSize);


/////////////////////////////////////////////
//!	音声データの領域を開放
//!	@param  wav[in]		AquesTalk_Synthe()で返されたアドレスを指定
void AquesTalk_FreeWave(unsigned char *wav);



#ifdef __cplusplus
}
#endif
#endif // !defined(_AQUESTALK_H_)
