FROM amd64/ubuntu:latest

RUN apt-get update && apt-get install -y gcc g++ libstdc++6

COPY aquestalk/lib64 /usr/local/lib/aquestalk/lib64
COPY aquestalk/AquesTalk.h /usr/local/include/
COPY aquestalk/Main.c /app/

WORKDIR /app

RUN g++ -o Main Main.c -I/usr/local/include -ldl

CMD ["./Main"]