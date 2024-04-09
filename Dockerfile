FROM amd64/ubuntu:latest

RUN apt-get update && apt-get install -y gcc g++ libstdc++6

# AquesTalk関連のファイルをコピー
COPY aquestalk/lib64 /usr/local/lib/aquestalk/lib64
COPY aquestalk/AquesTalk.h /usr/local/include/

# AqKanji2Koe-A関連のファイルをコピー
COPY aqkanji2koe/lib /usr/local/lib/
COPY aqkanji2koe/aq_dic /usr/local/lib/aq_dic
COPY aqkanji2koe/lib/AqKanji2Koe.h /usr/local/include/
COPY aqkanji2koe/lib/AqUsrDic.h /usr/local/include/

# シンボリックリンクを作成
RUN ln -s /usr/local/lib/libAqKanji2Koe.so.4.1 /usr/local/lib/libAqKanji2Koe.so.4
RUN ln -s /usr/local/lib/libAqKanji2Koe.so.4 /usr/local/lib/libAqKanji2Koe.so
RUN ln -s /usr/local/lib/libAqUsrDic.so.4.1 /usr/local/lib/libAqUsrDic.so.4
RUN ln -s /usr/local/lib/libAqUsrDic.so.4 /usr/local/lib/libAqUsrDic.so

# メインプログラムをコピー
COPY Main.cpp /app/

WORKDIR /app

# メインプログラムをビルド
RUN g++ -o Main Main.cpp -I/usr/local/include -L/usr/local/lib -lAqKanji2Koe -lAqUsrDic -ldl

CMD ["./Main"]