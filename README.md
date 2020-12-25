# 基础socket


纯socket，完成多用户对话，端口使用8843


可以使用telnet链接


```bash
telnet 127.0.0.1 8843
```


## docker安装


创建镜像


```bash
docker build -t socket:base .
```


创建容器
```bash
docker run -it --name socket-base -p 8843:8843 -d socket:base
```


## 编译安装


到src目录，make编译，然后执行生成的server软件
```bash
cd src
make
./server
```
