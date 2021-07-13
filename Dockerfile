FROM ubuntu:21.04

USER root
RUN sed -i "s/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g" /etc/apt/sources.list && sed -i "s/security.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g" /etc/apt/sources.list && apt update && apt install --no-install-recommends --yes --fix-missing build-essential git

