# 2_2 Linux nginx

[toc]

---

>**环境：CentOS7.9最小化安装**

## 1. nginx基本应用

### 1.1 环境准备
1. 安装包依赖：**vim、bash-completion、net-tools、psmisc、gcc、make、pcre-devel、openssl-devel**

```
yum -y install vim   //安装vim编辑器
yum list | grep bash   //查询名字和bash有关的软件包
yum -y install bash-completion   //安装支持tab键的软件包，装好之
后，使用exit退出，重新登录才生效
yum -y install net-tools  //安装网络相关软件包
yum -y install  psmisc   //安装支持killall命令的软件

yum -y install  gcc  make  //安装编译工具
yum -y install  pcre-devel  //安装可以让nginx支持正则的软件包
yum -y install  openssl-devel  //安装可以让nginx支持安装加密网站的软件包
```

2. 安装nginx：

```
tar -xf nginx-1.17.6.tar.gz   //释放nginx

cd ~/nginx-1.17.6/    //进入nginx目录，自己的nginx-1.17.6目录
./configure  --prefix=/usr/local/nginx  --user=nginx  --with-http_ssl_module
//配置，--prefix是指定安装路径，--user是指定用户，--with-http_ssl_module是安全网站模块

make   //编译
make  install  //安装					
ls  /usr/local/nginx/     //检测看到4个目录则成功

****************************************
* conf 存放配置文件     sbin  存放主程序 *
* html 存放网站页面     logs  存放日志   *
****************************************
```

3. 启动nginx：

```
cd  /usr/local/nginx
useradd  nginx  -s  /sbin/nologin       //创建用户
/usr/local/nginx/sbin/nginx    //开启服务
sbin/nginx		//使用相对路径开启服务也可以
netstat  -ntulp | grep nginx    //检测服务是否正常开启

sbin/nginx  -V   //查看nginx版本以及安装时带了哪些参数和模块
systemctl  stop  firewalld   //关闭防火墙

使用真机的火狐浏览器打开192.168.99.5要看到nginx默认页面

sbin/nginx  -s  stop   //关闭服务
sbin/nginx  -s  reload  //重加载配置文件,服务必须是开启状态
```

### 1.2 测试网站页面（非默认网站index.html）：

```
[/usr/local/nginx/html/]下：

echo "abc-test~~~"  >  html/abc.html   //创建新页面
http://192.168.99.5/abc.html    //访问新页面
火狐访问192.168.99.5/abc.html    //如果无效,可以按ctrl+f5强制刷新
```

### 1.3 为nginx增加网站认证功能



