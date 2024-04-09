/*-------------------------------------------------------------
	Kanji2KoeCmd - かな漢字混じりテキストを音声記号列に変換

	$ Kanji2KoeCmd (dic_dir) < in.txt > out.koe

	■ビルド（GCC 5.1以上の環境が必要）
	  $ ln -sf ../lib64/libAqKanji2Koe.so.4.0 ./libAqKanji2Koe.so.4
	  $ ln -sf ../lib64/libAqKanji2Koe.so.4.0 ./libAqKanji2Koe.so
	  $ g++  -I./lib64 -o Kanji2KoeCmd Kanji2KoeCmd.cpp -L. -lAqKanji2Koe

	■実行
	  $ echo 音声合成テスト | LD_LIBRARY_PATH=. ./Kanji2KoeCmd ../aq_dic

	■ライブラリの配置
	  libAqKanji2Koe.so.X.Xを他のアプリからも呼び出す場合は、
	  ldconfigコマンドで共有ライブラリに登録する。
	  詳しくは、本ライブラリのマニュアルの「ライブラリ配置」を参照
	
	■辞書の配置(デフォルト）

		|- Kanji2KoeCmd
		|- aq_dic/		辞書フォルダ(aq_dic)を同じディレクトリに配置
			|- aqdic.bin 
			|- aq_user.dic (ユーザ辞書:任意)
			|- CREDITS

  
	2011/01/14	N.Yamazaki	Creation
	2019/03/05	N.Yamazaki	Ver.4用に一部修正

-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>		// setlocale()
#include <AqKanji2Koe.h>

#define	NSTR	4096

char * GetPathDic(const char *pathModule);

int main(int ac, char **av)
{
	int iret;
	char kanji[NSTR];
	char koe[NSTR];
	void *hAqKanji2Koe;
	
	// 開発ライセンスキー(ライセンス証に記載）の設定
//	iret = AqKanji2Koe_SetDevKey("XXX-XXX-XXX");

	if(ac==1){
		char *pPathDic  = GetPathDic(av[0]);
		hAqKanji2Koe = AqKanji2Koe_Create(pPathDic, &iret);
		free(pPathDic);
	}
	else {
		hAqKanji2Koe = AqKanji2Koe_Create(av[1], &iret);
	}
		
	if(hAqKanji2Koe==0){
		fprintf(stderr, "ERR: can not initialize Dictionary(%d)\n", iret);
		fprintf(stderr, "USAGE: $ Kanji2KoeCmd (dic_dir) < in.txt > out.koe\n");
		return iret;
	}

	int i;
	for(i=0; ; i++){
		if(fgets(kanji, NSTR, stdin)==0) break;
		iret = AqKanji2Koe_Convert(hAqKanji2Koe, kanji, koe, NSTR);
		if(iret!=0) {
			fprintf(stderr, "ERR: AqKanji2Koe_Convert()=%d\n", iret);
			break;
		}
		fprintf(stdout, "%s\n", koe);
	}

	AqKanji2Koe_Release(hAqKanji2Koe);
	return 0;
}

char * GetPathDic(const char *pathModule)
{
	char *p = strrchr((char*)pathModule, '/');
	if(p==NULL){
		return strdup("./aq_dic");
	}
	char *path = (char*)malloc(strlen(pathModule)+strlen("/aq_dic")+1);
	strncpy(path, pathModule, p-pathModule);
	strcpy(path+(p-pathModule), "/aq_dic");
	return path;
}

