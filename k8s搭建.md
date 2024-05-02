# k8s搭建

## 11. 搭建单机k8s
```
2G 2G 50G
1. 关闭防火墙
   systemctl disable firewalld
   systemctl stop firewalld
   查看状态
   systemctl status firewalld

2. 关闭selinux
1）安全增强型 Linux（Security-Enhanced Linux）简称 SELinux，它是一个 Linux 内核模块，也是 Linux 的一个安全子系统。
2）getenforce命令来自英文词组“get the current mode of SELinux”的拼写，其功能是用于显示SELinux服务模式。

3）临时关闭：setenforce 0
   永久关闭：vi /etc/selinux/config --> 将 SELINUX=enforcing 改成 SELINUX=disabled
   
3. 关闭swap
1）swapoff -a
2）永久关闭，vi /etc/fstab 注释掉swap那行

4. 设置主机名及配置hosts
   - hostnamectl set-hostname aminglinux01
   - vi /etc/hosts --> 添加ip地址和主机名

5. 将桥接的ipv4流量传递到iptables链
    1）modprobe br_netfilter ##生成bridge相关内核参数
    2）运行命令
cat > /etc/sysctl.d/k8s.conf << EOF
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
net.ipv4.ip_forward = 1
EOF
    3）sysctl --system # 生效

6. 时间同步
    yum install -y chrony
    systemctl start chronyd
    systemctl enable chronyd

7. 安装containerd
    1）先安装yum-utils工具
       yum install -y yum-utils
    2）配置Docker官方的yum仓库，
       yum-config-manager \
            --add-repo \
            https://download.docker.com/linux/centos/docker-ce.repo
            
        cat /etc/yum.repos.d/docker-ce.repo --> 可以查看仓库添加到了这个目录下
    3）安装containerd
       yum install containerd.io -y     
    4）启动服务
       systemctl enable containerd
       systemctl start containerd    
    5）生成默认配置
       containerd config default > /etc/containerd/config.toml
    6）修改默认配置
        - vi /etc/containerd/config.toml       
        - sandbox_image = "registry.cn-hangzhou.aliyuncs.com/google_containers/pause:3.8" # 修改为阿里云镜像地址
        - SystemdCgroup = true # 使用systemd cgroup
        - 重启containerd服务
          systemctl restart containerd  
     7）配置kubernetes仓库
        cat <<EOF > /etc/    yum.repos.d/kubernetes.repo
        [kubernetes]
        name=Kubernetes
        baseurl=https://mirrors.aliyun.com/kubernetes/yum/repos/kubernetes-el7-x86_64/
        enabled=1
        gpgcheck=1
        repo_gpgcheck=1
        gpgkey=https://mirrors.aliyun.com/kubernetes/yum/doc/yum-key.gpg https://mirrors.aliyun.com/kubernetes/yum/doc/rpm-package-key.gpg
        EOF
        说明：kubernetes用的是RHEL7的源，和8是通用的

！！！！！注意：教材的pdf文档在复制粘贴过程中，会出现错误导致配置出现问题！！！！！

     8）

```

```
kubeadm init --image-repository=registry.cn-hangzhou.aliyuncs.com/google_containers --apiserver-advertise-address=192.168.93.158 --kubernetes-version=v1.26.5  --service-cidr=10.15.0.0/16  --pod-network-cidr=10.18.0.0/16

Kubernetes 安装成功的信息

Your Kubernetes control-plane has initialized successfully!

To start using your cluster, you need to run the following as a regular user:

  mkdir -p $HOME/.kube
  sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
  sudo chown $(id -u):$(id -g) $HOME/.kube/config

Alternatively, if you are the root user, you can run:

  export KUBECONFIG=/etc/kubernetes/admin.conf

You should now deploy a pod network to the cluster.
Run "kubectl apply -f [podnetwork].yaml" with one of the options listed at:
  https://kubernetes.io/docs/concepts/cluster-administration/addons/

Then you can join any number of worker nodes by running the following on each as root:

kubeadm join 192.168.93.15*:6443 --token u7yyit.eqhbjhczme6vihtg \
	--discovery-token-ca-cert-hash sha256:a0da48829305b5aa45558d9d5f8cd506e3aca42756726dfb8cd93e0a0c1bec79 
```


## 2. 集群
```
1. 查看containerd版本
   rpm -qa |grep containerd 
   
```
```
1. master:
Your Kubernetes control-plane has initialized successfully!

To start using your cluster, you need to run the following as a regular user:

  mkdir -p $HOME/.kube
  sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
  sudo chown $(id -u):$(id -g) $HOME/.kube/config

Alternatively, if you are the root user, you can run:

  export KUBECONFIG=/etc/kubernetes/admin.conf

You should now deploy a pod network to the cluster.
Run "kubectl apply -f [podnetwork].yaml" with one of the options listed at:
  https://kubernetes.io/docs/concepts/cluster-administration/addons/

Then you can join any number of worker nodes by running the following on each as root:

kubeadm join 192.168.93.15*:6443 --token j2h9fv.c0362q9f8doj84il \
	--discovery-token-ca-cert-hash sha256:2f4e72fc895822414290d88dfab8c16739b0b15964e58ef0827812c19a6264d5 
```
## 3. 因为本身电脑配置的原因，要删除一个节点
1. 删除节点

```
**********************************************************************
* 如果需要在k8s集群中删除节点，首先需要在master节点上删除该节点的相关数据，*
* 再删除该节点，接着在该节点上进行reset操作，接着删除相关文件             *
**********************************************************************
1. 在Master节点操作
# 其中< node name >是在k8s集群中使用< kubectl get nodes >查询到的节点名称
kubectl drain <node name> --delete-local-data --force --ignore-daemonsets
kubectl delete node <node name>

2. 在需要删除的节点上
# 重置k8s
sudo kubeadm reset
# 删除残留的文件
sudo rm -rf /etc/kubernetes/
# 清除iptables或者ipvs的配置
sudo iptables -F && iptables -t nat -F && iptables -t mangle -F && iptables -X
sudo ipvsadm --clear

参考：[腾讯云](https://cloud.tencent.com/developer/article/2126222)    
```

## 4. 获取节点信息

```

获取节点信息：
kubectl get node 
kubectl get pod --all-namespaces

kubernetes
kubelet-1.26.2 kubeadm-1.26.2 kubectl-1.26.2
```
## 5. kubernetes、kubelet、kubeadm、kubectl

```
Kubernetes（简称k8s，因为第一个字母k和最后一个字母s中间有8个字母）是谷歌开源的一套容器化集群管理系统，当下已被众多大厂及中小企业采用，容器化技术是目前的大势所趋。

kubeadm：用来初始化集群的指令。

kubelet：在集群中的每个节点上用来启动 Pod 和容器等。

kubectl：用来与集群通信的命令行工具。
```
## 6. 节点也想执行kubectl get nodes 指令

```
在master节点执行
yum install rsync
rsync -av $HOME/.kube/ nodehostname:/root/.kube/
或者
scp -r /root/.kube/ nodehostname:/root/.kube

!!可能出现的错误：
ssh: Could not resolve hostname aminglinux02: Name or service not known
lost connection

解决：配置masert的/etc/hosts 文件，添加node节点的ip和主机名映射
```