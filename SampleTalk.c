/**********************************************************************
	SampleTalk.c - AquesTalk1 for Linux 規則音声合成 サンプルプログラム

	標準入力から音声記号列を１行読み込み、
	標準出力に音声波形(.wavフォーマット）を出力

	COPYRIGHT (C) 2007 AQUEST CORP.

	使用方法は、readme.txt を参照ください。
	
	2007/01/08	N.Yamazaki	Creation
**********************************************************************/
#include <stdio.h>
#include "AquesTalk.h"


int main(int ac, char **av)
{
	int 	size;
	int 	iret;
	char	str[1024];

	// 音声記号列を入力
	if(fgets(str, 1024-1, stdin)==0) return 0;

	// 音声合成
	//	unsigned char *wav = AquesTalk_Synthe(str, 100, &size);	//SJIS
	//	unsigned char *wav = AquesTalk_Synthe_Euc(str, 100, &size);
		unsigned char *wav = AquesTalk_Synthe_Utf8(str, 100, &size);
	//	unsigned char *wav = AquesTalk_Synthe_Utf16(wstr, 100, &size);	// unsigned short *wstr
	//	unsigned char *wav = AquesTalk_Synthe_Roman(str, 100, &size);
	if(wav==0){
		fprintf(stderr, "ERR:%d\n",size);
		return -1;
	}

	// 音声データ(wavフォーマット)の出力
	fwrite(wav, 1, size, stdout);

	// 音声データバッファの開放
	AquesTalk_FreeWave(wav);
	
	return 0;
}
