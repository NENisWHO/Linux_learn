# 5_1 Linux 计划任务

[toc]

---

>用途：按照设置的时间间隔，为用户反复执行某一固定的系统任务
>软件包：cronie、crontabs
>系统服务：crond
>日志文件：/var/log/cron

---

## 1. crontab 命令
* 编辑：crontab -e [-u 用户名]
* 查看：crontab -l  [-u 用户名]
* 清除：crontab -r  [-u 用户名]

---

## 2. 计划任务书写格式

```shell
# 分 时 日 月 周    任务命令行（绝对路径）
# *    匹配范围内任意时间
# ,    分隔多个不连续的时间点
# -    指定连续的时间范围
# /n   指定时间频率，每n...

## 例如：
* * * * *         #每分钟执行一次
30 8 * * *        #每天早晨的8点30分，执行一次
30 23 * * 5       #每周的周五，23：30执行一次
30 23 * * 1-5     #每周的周一至周五，23：30执行一次
30 23 * * 1,3,6   #每周的周一周三周六，23：30执行一次
30 23 1 * 1       #每月的1号或每周一晚上，23:30执行一次
*/6 * * * *       #每6分钟执行一次
4 */2 * * *       #每2小时运行一次

### 案例：
[root@localhost ~]# crontab -e        #编写任务计划
[root@localhost ~]# crontab -l        #查看任务计划
* * * * * date >> /opt/time.txt
[root@localhost ~]# cat /opt/time.txt 
2024年 06月 10日 星期一 02:10:01 CST
2024年 06月 10日 星期一 02:11:01 CST
2024年 06月 10日 星期一 02:12:01 CST
[root@localhost ~]# ls /var/spool/cron    #任务文件存放路径
root
[root@localhost ~]# cat /var/spool/cron/root    #记录root用户计划任务
* * * * * date >> /opt/time.txt
[root@localhost ~]# crontab -r        #删除计划任务
[root@localhost ~]# crontab -l
no crontab for root
```
---