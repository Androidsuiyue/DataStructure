# DataStructure
数据结构大数据处理
user.txt(大小限制这里只放了1万条)中存放了120万余条用户编号(user_id)、密码(password)的记录。
每行包含一条记录，每条记录包含：user_id和password中间为TAB分隔（即C语言中的\t）。
user_id的范围为：1～1,230,000
password的范围：只包含字母和数字，并且长度处于[6,19]之间。


请作如下处理：

	（1）读取文件中的密码(password)字段，统计密码出现的次数count，写入文件password.txt。不需要排序。格式：每行一条记录，password和count中间用TAB分隔（即C语言中的\t）。

	（2）读取password.txt，对密码出现次数按照降序排序。
分别采用：直接插入排序、希尔排序、冒泡排序、快速排序、直接选择排序、堆排序、归并排序、基数排序；求出每种排序方法所需要的绝对时间。屏幕上输出各种各种排序的绝对时间。
最后屏幕上输出出现次数最多的20个密码及次数。

	（3）读取user.txt，使用链表存放，使用顺序查找，随机生成2000个user_id（1～1,230,000之内的），再随机生成20个user_id（大于1,230,000的），输出查找所花总时间。

	（4）读取user.txt，按照用户id使用二叉排序树存放，随机生成2000个user_id（1～1,230,000之内的），再随机生成20个user_id（大于1,230,000的），输出查找所花总时间。

	（5）读取user.txt，先按照user_id排序，结果写入user_sorted.txt。用不同的排序方法分别输出排序所需时间。（如果所花时间过长，请缩小数据范围，并估算最终所需的大概时间）

	（6）读取user_sorted.txt，使用二分查找，随机生成2000个user_id（1～1,230,000之内的），再随机生成20个user_id（大于1,230,000的），输出查找所花总时间。（只计算查找的时间）

		（7）设计一个哈希存储的方案，用来存放password.txt中的数据（关键字为密码）；设计20个存在的密码和不存在的密码，输出该密码和出现的次数，以及查找所花总时间。
