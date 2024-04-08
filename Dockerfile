FROM amd64/ubuntu:latest

RUN apt-get update && apt-get install -y gcc g++ libstdc++6

COPY lib64/f1/libAquesTalk.so /usr/local/lib/
COPY AquesTalk.h /usr/local/include/
COPY SampleTalk.c /app/

WORKDIR /app

RUN g++ -o SampleTalk SampleTalk.c -I/usr/local/include /usr/local/lib/libAquesTalk.so

CMD ["./SampleTalk"]