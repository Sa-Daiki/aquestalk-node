# FROM amd64/ubuntu:latest

# RUN apt-get update && apt-get install -y gcc g++ libstdc++6

# # AquesTalk関連のファイルをコピー
# COPY aquestalk/lib64 /usr/local/lib/aquestalk/lib64
# COPY aquestalk/AquesTalk.h /usr/local/include/

# # AqKanji2Koe-A関連のファイルをコピー
# COPY aqkanji2koe/lib/*.so* /usr/local/lib/
# COPY aqkanji2koe/aq_dic /usr/local/lib/aqkanji2koe/aq_dic
# COPY aqkanji2koe/lib/AqKanji2Koe.h /usr/local/include/
# COPY aqkanji2koe/lib/AqUsrDic.h /usr/local/include/

# # シンボリックリンクを作成
# RUN ln -s /usr/local/lib/libAqKanji2Koe.so.4.1 /usr/local/lib/libAqKanji2Koe.so.4 && \
#     ln -s /usr/local/lib/libAqKanji2Koe.so.4 /usr/local/lib/libAqKanji2Koe.so && \
#     ln -s /usr/local/lib/libAqUsrDic.so.4.1 /usr/local/lib/libAqUsrDic.so.4 && \
#     ln -s /usr/local/lib/libAqUsrDic.so.4 /usr/local/lib/libAqUsrDic.so

# # ldconfig を実行して共有ライブラリのキャッシュを更新
# RUN ldconfig

# # メインプログラムをコピー
# COPY main.cpp /app/

# WORKDIR /app

# RUN ldconfig -p | grep -E 'libstdc\+\+\.so\.6|libc\.so\.6|libgcc_s\.so\.1|libm\.so\.6'
# # メインプログラムをビルド
# RUN g++ -o main main.cpp -I/usr/local/include -L/usr/local/lib -lAqKanji2Koe -lAqUsrDic -ldl

# CMD ["./main"]

# FROM amd64/ubuntu:latest

# ENV TZ=Asia/Tokyo
# ENV DEBIAN_FRONTEND=noninteractive

# RUN apt-get update && apt-get install -y ca-certificates && update-ca-certificates
# RUN apt-get update && apt install -y --no-install-recommends \
#     git \
#     build-essential \
#     cmake \
#     libasio-dev \
#     && apt-get clean \
#     && rm -rf /var/lib/apt/lists/*

# RUN git clone https://github.com/CrowCpp/Crow.git \
#     && mkdir Crow/build \
#     && cd Crow/build \
#     && cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF \
#     && make -j$(nproc) \
#     && make install \
#     && make clean \
#     && cd && rm -rf Crow

# WORKDIR /app
# COPY . /app

# RUN g++ -o main main.cpp -lpthread

# EXPOSE 8080

# CMD ["./main"]

FROM amd64/ubuntu:latest

ENV TZ=Asia/Tokyo
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y ca-certificates && update-ca-certificates
RUN apt-get update && apt install -y --no-install-recommends \
    git \
    build-essential \
    cmake \
    libasio-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/CrowCpp/Crow.git \
    && mkdir Crow/build \
    && cd Crow/build \
    && cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF \
    && make -j$(nproc) \
    && make install \
    && make clean \
    && cd && rm -rf Crow

RUN apt-get update && apt-get install -y gcc g++ libstdc++6

# AquesTalk関連のファイルをコピー
COPY aquestalk/lib64 /usr/local/lib/aquestalk/lib64
COPY aquestalk/AquesTalk.h /usr/local/include/

# AqKanji2Koe-A関連のファイルをコピー
COPY aqkanji2koe/lib/*.so* /usr/local/lib/
COPY aqkanji2koe/aq_dic /usr/local/lib/aqkanji2koe/aq_dic
COPY aqkanji2koe/lib/AqKanji2Koe.h /usr/local/include/
COPY aqkanji2koe/lib/AqUsrDic.h /usr/local/include/

# シンボリックリンクを作成
RUN ln -s /usr/local/lib/libAqKanji2Koe.so.4.1 /usr/local/lib/libAqKanji2Koe.so.4 && \
    ln -s /usr/local/lib/libAqKanji2Koe.so.4 /usr/local/lib/libAqKanji2Koe.so && \
    ln -s /usr/local/lib/libAqUsrDic.so.4.1 /usr/local/lib/libAqUsrDic.so.4 && \
    ln -s /usr/local/lib/libAqUsrDic.so.4 /usr/local/lib/libAqUsrDic.so

# ldconfig を実行して共有ライブラリのキャッシュを更新
RUN ldconfig

WORKDIR /app

# メインプログラムをコピー
COPY main.cpp /app/

RUN ldconfig -p | grep -E 'libstdc\+\+\.so\.6|libc\.so\.6|libgcc_s\.so\.1|libm\.so\.6'
# メインプログラムをビルド
RUN g++ -o main main.cpp -I/usr/local/include -L/usr/local/lib -lAqKanji2Koe -lAqUsrDic -ldl

CMD ["./main"]