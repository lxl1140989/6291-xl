使用简介

此份sdk 基于 openwrt，使用前需要先安装openwrt所需的相关工具，可访问
https://wiki.openwrt.org/doc/howto/buildroot.exigence

1.下载sdk

git clone https://github.com/lxl1140989/6291-xl.git

从 http://pan.baidu.com/s/1bpyqSyz 下载 sdk 的package 压缩包 dl.tar.gz
下载后，放到dmsdk文件夹中，然后解压
cd 6291-xl
tar -zxvf dl.tar.gz

2.编译

cd 6291-xl

make  或者 make V=s (输出编译的详细信息)

生成的firmware位于 bin/xburst/

烧录文件为6291-nor-16MB.bin，升级文件为6291-nor-update-fw.bin
