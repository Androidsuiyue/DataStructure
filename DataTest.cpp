#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<stdlib.h>
#include<windows.h>
using namespace std;
/** 定义user对象 **/
class User {
	public:
		User() {
			user_id=0;
			password="";
			count=0;
		}
		//用户id
		int user_id;
		//用户密码
		string password;
		//
		int count;
		//析构函数用于清理善后
		~User() {
		}
};
/** 定义user链表 **/
typedef struct UserNode {
	UserNode() {
		userNode_id=0;
		userNode_password="";
		userNode_count=0;
		nextNode=NULL;
	}
	int userNode_id;
	string userNode_password;
	int userNode_count;
	struct UserNode* nextNode;
} UserNode;
/** 定义user二叉树 **/
struct UserTree {
	UserTree() {
		lchild=NULL;
		rchild=NULL;
		user_id=0;
		password="";
	};
	struct UserTree*lchild,*rchild;
	int user_id;
	string password;
};
/** 定义user哈希表 **/
typedef struct {
	UserNode *firstUser;
} HashTable;


#define IdNum 1250000
HashTable hashTable[11131];//哈希表 
User user[IdNum];// 所有用户
//UserNode userNode[IdNum];
string psw[IdNum];// 用于存放重复的密码
int randomNumber[2020];
int pw = 0;// 用于确定放到 passw数组中的序号
int status = 0;// 用于确定是否重复
//20个存在5个不存在
string havePassword[25]= {"0123456789","123456","1234567","12345678","123456789",
                          "1234567890","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa",
                          "aaaaaaaaaa","aaaaaaaaaaa","aaaaaaaaaaaa","aaaaaaaaaaaaa","aaaaaaaaaaaaaa",
                          "1111111111","111111111","11111111","1111111","111111",
                          "qianzhenghao","malechao","zhoujiawei","aaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaa"
                         };
/**
 *@description 读取user.txt中用户
 *@return 用户数
 */
int ReadUserFormUserTxt() {
	ifstream ifs;
	ifs.open("user.txt" );
	int currentNumberOfLines=0;
	//对应user.txt中的两列
	int user_id;
	string password;
	while(!ifs.eof()) {
		ifs>>user_id>>password;
		//防止多读如回车符
		if (ifs.fail()) {
			break;
		}
		user[currentNumberOfLines].user_id=user_id;
		user[currentNumberOfLines].password=password;
		user[currentNumberOfLines].count=currentNumberOfLines;
		//cout<<currentNumberOfLines<<"---"<<password<<endl;
		currentNumberOfLines++;
	}
	user[currentNumberOfLines].count=-1;//将最后一个 id 设置为-1 用于判断是否到最后一个用户
	ifs.close();
	return currentNumberOfLines;
}
/**
 *@description 读取user_sorted.txt中用户
 *@return 用户数
 */
int ReadUserIdFormUserSortedTxt() {
	ifstream ifs;
	ifs.open("user_sorted.txt");
	//用户数
	int currentNumberOfLines=0;
	string a;
	int b;
	while(!ifs.eof()) {
		ifs>>b>>a;
		//防止多读如回车符
		if (ifs.fail()) {
			break;
		}
		user[currentNumberOfLines].user_id=b;
		user[currentNumberOfLines].password=a;
		user[currentNumberOfLines].count=currentNumberOfLines;
		//cout<<currentNumberOfLines<<"---"<<user[currentNumberOfLines].password<<endl;
		currentNumberOfLines++;
	}
	user[currentNumberOfLines].count=-1;// 将最后一个 id 设置为-1 用于判断是否到 最后一个用户
	ifs.close();
	return currentNumberOfLines;
}
/**
 *@description 读取password.txt中用户
 *@return 用户数
 */
int ReadUserFormPasswordTxt() {
	ifstream ifs;
	ifs.open("password.txt" );
	//用户数
	int currentNumberOfLines=0;
	char ch;
	string a;
	int b;
	while(!ifs.eof()) {
		ifs>>a>>b;
		//防止多读如回车符
		if (ifs.fail()) {
			break;
		}
		user[currentNumberOfLines].user_id=currentNumberOfLines;
		user[currentNumberOfLines].password=a;
		user[currentNumberOfLines].count=b;
		currentNumberOfLines++;
	}
	user[currentNumberOfLines].user_id=-1;// 将最后一个 id 设置为-1 用于判断是否到 最后一个用户
	ifs.close();
	return currentNumberOfLines;
}

/**
 * 读取文件中密码，统计密码出现次数，写入文件 password.txt
 */
void ReadPasswordOfUserTxtAndWrite() {
	int userCout=ReadUserFormUserTxt();
	int currentNumberOfLines=0;
	int count=0;//password重复次数
	ofstream ofs;
	ofs.open("password.txt",ios::ate);
	int currentNumberOfPasswrodLines =0;
	while(1) {
		//如果是最后一个user，结束循环
		if(user[currentNumberOfLines].count==-1) {
			break;
		}
		//如果当前用户行是password数组中的已有密码，则跳过
		for(int j=0; j<=currentNumberOfLines; j++) {
			if(psw[j]=="") {
				break;
			}
			if(psw[j]==user[currentNumberOfLines].password) {
				status=1;
				break;
			}
		}
		//跳过
		if(status==1) {
			currentNumberOfLines++;
			count=0;
			status=0;
			continue;
		}
		//没有重复则把密码放入数组
		psw[currentNumberOfPasswrodLines]=user[currentNumberOfLines].password;
		// 确定重复次数
		int i=0;
		while(1) {
			if(user[i].count==-1) {
				break;
			}
			if(user[i].password==user[currentNumberOfLines].password) {
				count++;
			}
			i++;
		}
		ofs<<user[currentNumberOfLines].password<<"\t"<<count<<endl;//写入文件
		currentNumberOfLines++;
		count=0;
		currentNumberOfPasswrodLines++;
		status=0;
	}
	ofs.close();
}

/**
 *@description: 直接插入排序
 * 		每第i趟保证前i个元素有序，但不保证在最后一趟前这些元素归位
 */
void InserSortOrderById(int userCout) {
	int j;
	int tempUserId;
	string tempPassword;
	for(int i=1; i<userCout; i++) {
		if(user[i].user_id>user[i-1].user_id) {
			tempUserId=user[i].user_id;
			tempPassword = user[i].password;
			j=i-1;
			do {
				user[j+1].user_id=user[j].user_id;
				user[j+1].password=user[j].password;
				j--;
			} while(j>=0&&user[j].user_id<tempUserId);
			user[j+1].user_id=tempUserId;
			user[j+1].password=tempPassword;
		}
	}
}
/**
 *@description: 直接插入排序
 * 		每第i趟保证前i个元素有序，但不保证在最后一趟前这些元素归位
 */
void InserSort(int userCout) {
	int j;
	int tempCount;
	string tempPassword;
	for(int i=1; i<userCout; i++) {
		if(user[i].count>user[i-1].count) {
			tempPassword=user[i].password;
			tempCount = user[i].count;
			j=i-1;
			do {
				user[j+1].count=user[j].count;
				user[j+1].password=user[j].password;
				j--;
			} while(j>=0&&user[j].count<tempCount);
			user[j+1].count=tempCount;
			user[j+1].password=tempPassword;
		}
	}
}

/**
 *@description: 希尔排序
 * 		每i趟增量为d=n/2^i,保证数组中的一组位置相差d的元素有序
 */
void ShellSortOrderById(int n) {
	int i,j,d;
	d=n/2;
	int tempUserId;
	string tempPassword;
	while(d>0) {
		for(i=d; i<n; i++) {
			tempPassword = user[i].password;
			tempUserId = user[i].user_id;
			j=i-d;
			while(j>=0 && tempUserId>user[j].user_id) {
				user[j+d].password=user[j].password;
				user[j+d].user_id=user[j].user_id;
				j=j-d;
			}
			user[j+d].password = tempPassword;
			user[j+d].user_id = tempUserId;
		}
		d=d/2;
	}
}
/**
 *@description: 希尔排序
 * 		每i趟增量为d=n/2^i,保证数组中的一组位置相差d的元素有序
 */
void ShellSort(int n) {
	int i,j,d;
	d=n/2;
	int tempCount;
	string tempPassword;
	while(d>0) {
		for(i=d; i<n; i++) {
			tempPassword = user[i].password;
			tempCount = user[i].count;
			j=i-d;
			while(j>=0 && tempCount>user[j].count) {
				user[j+d].password=user[j].password;
				user[j+d].count=user[j].count;
				j=j-d;
			}
			user[j+d].password = tempPassword;
			user[j+d].count = tempCount;
		}
		d=d/2;
	}
}
/**
 *@description: 冒泡排序
 * 		每趟保证数组一个元素归位
 */
void BubbleSortOrderById(int n) {
	int i,j;
	int tempUserId;
	string tempPassword;
	bool exchange;
	for(i=0; i<n-1; i++) {
		exchange=false;
		for(j=n-1; j>i; j--)
			if(user[j].user_id>user[j-1].user_id) {
				tempUserId = user[j].user_id;
				tempPassword = user[j].password;
				user[j].user_id = user[j-1].user_id;
				user[j].password = user[j-1].password;
				user[j-1].user_id = tempUserId;
				user[j-1].password = tempPassword;
				exchange=true;
			}
		if(!exchange)
			return;
	}
}

/**
 *@description: 冒泡排序
 * 		每趟保证数组一个元素归位
 */
void BubbleSort(int n) {
	int i,j;
	int tempCount;
	string tempPassword;
	bool exchange;
	for(i=0; i<n-1; i++) {
		exchange=false;
		for(j=n-1; j>i; j--)
			if(user[j].count>user[j-1].count) {
				tempCount = user[j].count;
				tempPassword = user[j].password;
				user[j].count = user[j-1].count;
				user[j].password = user[j-1].password;
				user[j-1].count = tempCount;
				user[j-1].password = tempPassword;
				exchange=true;
			}
		if(!exchange)
			return;
	}
}

int partitionOrderById(int s,int t) {
	int i=s,j=t;
	string tempPassword=user[i].password;
	int tempUserId=user[i].user_id;
	while(i<j) {
		while(j>i && user[j].user_id <= tempUserId) {
			j--;
		}
		user[i].password = user[j].password;
		user[i].user_id = user[j].user_id;
		while(i<j && user[i].user_id >= tempUserId) {
			i++;
		}
		user[j].password = user[i].password;
		user[j].user_id = user[i].user_id;
	}
	user[i].user_id = tempUserId;
	user[i].password = tempPassword;
	return i;
}

/**
 *@description: 快速排序
 * 		每趟保证数组一个元素归位，但与冒泡不同的是只对当前数组的第一个元素归位
 */
void QuickSortOrderById(int s,int t) {
	int i;
	if(s<t) {
		i=partitionOrderById(s,t);
		QuickSortOrderById(s,i-1);
		QuickSortOrderById(i+1,t);
	}
}
int partition(int s,int t) {
	int i=s,j=t;
	string password=user[i].password;
	int count=user[i].count;
	while(i<j) {
		while(j>i && user[j].count <= count) {
			j--;
		}

		user[i].password = user[j].password;
		user[i].count = user[j].count;

		while(i<j && user[i].count >= count) {
			i++;
		}
		user[j].password = user[i].password;
		user[j].count = user[i].count;

	}
	user[i].count = count;
	user[i].password = password;
	return i;
}
/**
 *@description: 快速排序
 * 		每趟保证数组一个元素归位，但与冒泡不同的是只对当前数组的第一个元素归位
 */
void QuickSort(int s,int t) {
	int i;
	if(s<t) {
		i=partition(s,t);
		QuickSort(s,i-1);
		QuickSort(i+1,t);
	}
}

/**
 *@description: （直接）简单选择排序
 * 		每趟保证给定位置的一个元素归位，这个元素只能是最大或最小，且与冒泡不同的是每趟只交换一次位置
 */
void SelectSortOrderById(int n) {
	int i,j,k;
	int tempUserId;
	string tempPassword;
	for(i=0; i<n-1; i++) {
		k=i;
		for(j=i+1; j<n; j++) {
			if(user[j].user_id>user[k].user_id)
				k=j;
		}
		if(k!=i) {
			tempUserId = user[i].user_id;
			tempPassword = user[i].password;
			user[i].user_id = user[k].user_id;
			user[i].password = user[k].password;
			user[k].user_id = tempUserId;
			user[k].password = tempPassword;
		}
	}
}
/**
 *@description: （直接）简单选择排序
 * 		每趟保证给定位置的一个元素归位，这个元素只能是最大或最小，且与冒泡不同的是每趟只交换一次位置
 */
void SelectSort(int n) {
	int i,j,k;
	int tempCount;
	string tempPassword;
	for(i=0; i<n-1; i++) {
		k=i;
		for(j=i+1; j<n; j++) {
			if(user[j].count>user[k].count)
				k=j;
		}
		if(k!=i) {
			tempCount = user[i].count;
			tempPassword = user[i].password;
			user[i].count = user[k].count;
			user[i].password = user[k].password;
			user[k].count = tempCount;
			user[k].password = tempPassword;
		}
	}
}

/**
 *@description: 筛选
 */
void siftOrderById(int low,int high) {
	int i=low,j=2*i;
	int tempUserId = user[i].user_id;
	string tempPassword = user[i].password;
	while(j<=high) {
		if(j<high && user[j].user_id>user[j+1].user_id)
			j++;
		if(tempUserId>user[j].user_id) {
			user[i].password = user[j].password;
			user[i].user_id = user[j].user_id;
			i=j;
			j=2*i;
		} else break;
	}
	user[i].password = tempPassword;
	user[i].user_id = tempUserId;
}
/**
 *@description:  堆选择排序
 * 		原理：小根堆（父结点总是大于子节点） ①建堆：按照二叉树以第一个元素为根节点，按顺序从左到右填充成堆
 *		②把这个堆变为小根堆
 *		③把第一个元素和最后一个元素交换，此时的最后一个元素以归位，就把其剔除
 *		④循坏②③ 直到堆里只有一个元素，排序结束
 */
void HeapSortOrderById(int n) {
	int i;
	int tempUserId;
	string tempPassword;
	for(i=n/2; i>=0; i--) {
		siftOrderById(i,n);
	}
	for(i=n; i>=1; i--) {
		tempUserId = user[0].user_id;
		tempPassword = user[0].password;
		user[0].user_id = user[i].user_id;
		user[0].password = user[i].password;
		user[i].user_id = tempUserId;
		user[i].password = tempPassword;
		siftOrderById(0,i-1);
	}
}
/**
 *@description: 筛选
 */
void sift(int low,int high) {
	int i=low,j=2*i;
	int tempCount = user[i].count;
	string tempPassword = user[i].password;
	while(j<=high) {
		if(j<high && user[j].count>user[j+1].count)
			j++;
		if(tempCount>user[j].count) {
			user[i].password = user[j].password;
			user[i].count = user[j].count;
			i=j;
			j=2*i;
		} else break;
	}
	user[i].password = tempPassword;
	user[i].count = tempCount;
}
/**
 *@description:  堆选择排序
 * 		原理：小根堆（父结点总是大于子节点） ①建堆：按照二叉树以第一个元素为根节点，按顺序从左到右填充成堆
 *		②把这个堆变为小根堆
 *		③把第一个元素和最后一个元素交换，此时的最后一个元素以归位，就把其剔除
 *		④循坏②③ 直到堆里只有一个元素，排序结束
 */
void HeapSort(int n) {
	int i;
	int tempCount;
	string tempPassword;
	for(i=n/2; i>=0; i--) {
		sift(i,n);
	}
	for(i=n; i>=1; i--) {
		tempCount = user[0].count;
		tempPassword = user[0].password;
		user[0].count = user[i].count;
		user[0].password = user[i].password;
		user[i].count = tempCount;
		user[i].password = tempPassword;
		sift(0,i-1);
	}
}
void ShowUserList(int n) {
	cout<<"user---》"<<endl;
	for(int k=0; k<=n; k++) { // 输出出现次数最多的 20 个密码
		if(user[k].user_id==-1) {
			break;
		}
		cout<<user[k].password<<"\t"<<user[k].count<<endl;
	}
}

/**
 *@description:  归并排序
 */
void MergeOrderById(int low,int mid,int high) {
	User *tempUser =new User[high-low+1];// 临时用户数组
	int i=low,j=mid+1,k=0;
	while(i<=mid && j<=high) {
		if(user[i].user_id>=user[j].user_id) {
			tempUser[k].password=user[i].password;
			tempUser[k].user_id = user[i].user_id;
			i++;
			k++;
		} else {
			tempUser[k].password = user[j].password;
			tempUser[k].user_id = user[j].user_id;
			j++;
			k++;
		}
	}
	while(i<=mid) {
		tempUser[k].password = user[i].password;
		tempUser[k].user_id = user[i].user_id;
		i++;
		k++;
	}
	while(j<=high) {
		tempUser[k].password = user[j].password;
		tempUser[k].user_id = user[j].user_id;
		j++;
		k++;
	}
	for(k=0,i=low; i<=high; k++,i++) {
		user[i].password = tempUser[k].password;
		user[i].user_id = tempUser[k].user_id;
	}
	//ShowUserList(high);
}

void MergePassOrderById(int length,int n) {
	int i;
	for(i=0; i+2*length-1<n; i=i+2*length)
		MergeOrderById(i,i+length-1,i+2*length-1);
	if (i+length-1<n-1)
		MergeOrderById(i,i+length-1,n-1);
}
/**
 *@description:  归并排序
 * 		原理：将数组先拆分成不分割的数组，再按顺序两两合并成一个有序数组，直到长度为n的有序数组
 * 		①分割数组为两半
 *		②重复①直到数组不能再分割
 *		③把每个数组两两按顺序合并成一个有序数组
 *		④重复③直到数组长度到n
 */
void MergeSortOrderById(int n) {
	int length;
	for(length=1; length<n; length=2*length)
		MergePassOrderById(length,n);
}
/**
 *@description:  归并排序
 */
void Merge(int low,int mid,int high) {
	User *tempUser =new User[high-low+1];// 临时用户数组
	int i=low,j=mid+1,k=0;
	while(i<=mid && j<=high) {
		if(user[i].count>=user[j].count) {
			tempUser[k].password=user[i].password;
			tempUser[k].count = user[i].count;
			i++;
			k++;
		} else {
			tempUser[k].password = user[j].password;
			tempUser[k].count = user[j].count;
			j++;
			k++;
		}
	}
	while(i<=mid) {
		tempUser[k].password = user[i].password;
		tempUser[k].count = user[i].count;
		i++;
		k++;
	}
	while(j<=high) {
		tempUser[k].password = user[j].password;
		tempUser[k].count = user[j].count;
		j++;
		k++;
	}
	for(k=0,i=low; i<=high; k++,i++) {
		user[i].password = tempUser[k].password;
		user[i].count = tempUser[k].count;
	}
	//ShowUserList(high);
}

void MergePass(int length,int n) {
	int i;
	for(i=0; i+2*length-1<n; i=i+2*length)
		Merge(i,i+length-1,i+2*length-1);
	if (i+length-1<n-1)
		Merge(i,i+length-1,n-1);
}
/**
 *@description:  归并排序
 * 		原理：将数组先拆分成不分割的数组，再按顺序两两合并成一个有序数组，直到长度为n的有序数组
 * 		①分割数组为两半
 *		②重复①直到数组不能再分割
 *		③把每个数组两两按顺序合并成一个有序数组
 *		④重复③直到数组长度到n
 */
void MergeSort(int n) {
	int length;
	for(length=1; length<n; length=2*length)
		MergePass(length,n);
}

/**
 *@description:  得到数字中的位数的数字（如90，2）
 *@return  位数（返回9）
 */
int GetNumberOfDigitInNumber(int number,int digit) {
	int temp = 1;
	for (int i = 0; i < digit - 1; i++)
		temp *= 10;
	return (number / temp) % 10;
}

/**
 *@description:  得到数字中的位数的数字（如90，2）
 *		①分配：把一维数组按每位的基数存放到二维数组中
 *		②收集：把二维数组按基数存放回一维数组中
 *		③重复①②直到数的最大位数走完
 */
void RadixSortOrderById( int redix,int digitCout,int userCount) {
	User **radixArrays=(User **)malloc(sizeof(User*)*(redix));    //分别为0~9基数的存放空间
	for (int i=0; i<10; i++) {
		radixArrays[i] = new User[userCount+1];
		radixArrays[i][0].user_id = 0;    //index为0处记录这组数据的个数
	}
	for (int pos=1; pos<=digitCout; pos++) { //从个位开始入桶并出桶
		for (int i=0; i<userCount; i++) {  //分配过程  对数组循环位数
			//用二维数组来按位数存放一维数组，[当前位的数][重复的数目]=一维数组
			int num = GetNumberOfDigitInNumber(user[i].user_id,pos);
			//[][重复的数目++]并把重复的数目录在[][0]里
			int index = ++radixArrays[num][0].user_id;
			radixArrays[num][index].password = user[i].password;
			radixArrays[num][index].user_id = user[i].user_id;
		}
		for (int i=redix-1, j=0; i>=0; i--) { //收集
			//[当前位的数][重复的数目]对当前位的数进行收集，即二维数组变为一维数组
			for (int k = 1; k <= radixArrays[i][0].user_id; k++) {
				user[j] = radixArrays[i][k];
				user[j] = radixArrays[i][k];
				j++;
			}
			radixArrays[i][0].user_id = 0;    //出桶完毕，复位
		}
	}
}
/**
 *@description:  得到数字中的位数的数字（如90，2）
 *		①分配：把一维数组按每位的基数存放到二维数组中
 *		②收集：把二维数组按基数存放回一维数组中
 *		③重复①②直到数的最大位数走完
 */
void RadixSort( int redix,int digitCout,int userCount) {
	User **radixArrays=(User **)malloc(sizeof(User*)*(redix));    //分别为0~9基数的存放空间
	for (int i=0; i<10; i++) {
		radixArrays[i] = new User[userCount+1];
		radixArrays[i][0].count = 0;    //index为0处记录这组数据的个数
	}
	for (int pos=1; pos<=digitCout; pos++) { //从个位开始入桶并出桶
		for (int i=0; i<userCount; i++) {  //分配过程  对数组循环位数
			//用二维数组来按位数存放一维数组，[当前位的数][重复的数目]=一维数组
			int num = GetNumberOfDigitInNumber(user[i].count,pos);
			//[][重复的数目++]并把重复的数目录在[][0]里
			int index = ++radixArrays[num][0].count;
			radixArrays[num][index].password = user[i].password;
			radixArrays[num][index].count = user[i].count;
		}
		for (int i=redix-1, j=0; i>=0; i--) { //收集
			//[当前位的数][重复的数目]对当前位的数进行收集，即二维数组变为一维数组
			for (int k = 1; k <= radixArrays[i][0].count; k++) {
				user[j] = radixArrays[i][k];
				user[j] = radixArrays[i][k];
				j++;
			}
			radixArrays[i][0].count = 0;    //出桶完毕，复位
		}
	}
}

/* 读取password.txt，对密码出现次数按照降序排序 */
void DescendingSortOfPasswordNumbers() {
	int choose=0;
	cout<<"请输入使用的排序方法 :"<<endl;
	cout<<"    1 直接插入排序 2 希尔排序 3 冒泡排序 4 快速排序 "<<endl;
	cout<<"   5 直接选择排序 6 堆排序  7 归并排序 8 基数排序 "<<endl;
	cin>>choose;
	while(1) {
		switch(choose) {
			case 1: {
				/************ 直接插入排序start  ************/
				int userCount= ReadUserFormPasswordTxt();
				time_t nowtime,nexttime;//用于统计时间
				nowtime=GetTickCount();// 获取当前时间
				//----------- 算法start ------------//
				InserSort(userCount);
				//----------- 算法end ------------//
				nexttime=GetTickCount();// 获取排好序后的时间
				ofstream ofs;
				ofs.open("password_InserSort.txt",ios::ate);
				int i=0;
				while(1) {
					if(user[i].user_id==-1) {
						break;
					}
					ofs<<user[i].password<<"\t"<<user[i].count<<endl;
					i++;
				}

				cout<<"直 接 插 入 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;
				cout<<"出现次数最多的 20 个密码是："<<endl;
				for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
					if(user[k].user_id==-1) {
						break;
					}
					cout<<user[k].password<<"\t"<<user[k].count<<endl;
				}
				cin>>choose;
				break;
				/************ 直接插入排序end  ************/
			}

			case 2:
				/************* 希尔排序start  *************/
			{
				int userCount= ReadUserFormPasswordTxt();
				time_t nowtime,nexttime;//用于统计时间
				nowtime=GetTickCount();// 获取当前时间
				//----------- 算法start ------------//
				ShellSort(userCount);
				//----------- 算法end ------------//
				nexttime=GetTickCount();// 获取排好序后的时间
				ofstream ocout;
				ocout.open("password_ShellSort.txt",ios::ate);
				{
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ocout<<user[i].password<<"\t"<<user[i].count<<endl;// 写入文件
						i++;
					}

				}
				cout<<"      希 尔 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//倍数是为了方便显 示时间
				cout<<"出现次数最多的 20 个密码是："<<endl;
				for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
					if(user[k].user_id==-1) {
						break;
					}
					cout<<user[k].password<<"\t"<<user[k].count<<endl;
				}
				cin>>choose;
				break;
				/************* 希尔排序end  *************/
			}
			case 3:
				/************* 冒泡排序start  *************/
			{
				int userCount=ReadUserFormPasswordTxt();
				time_t nowtime,nexttime;//用于统计时间
				nowtime=GetTickCount();// 获取当前时间
				//----------- 算法start ------------//
				BubbleSort(userCount);
				//----------- 算法start ------------//
				nexttime=GetTickCount();// 获取排好序后的时间
				ofstream ofs;
				ofs.open("password_BubbleSort.txt",ios::ate);
				int i=0;
				while(1) {
					if(user[i].user_id==-1) {
						break;
					}
					ofs<<user[i].password<<"\t"<<user[i].count<<endl;// 写入文件
					i++;
				}
				cout<<"      冒 泡 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显示时间
				cout<<"出现次数最多的 20 个密码是："<<endl;
				for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
					if(user[k].user_id==-1) {
						break;
					}
					cout<<user[k].password<<"\t"<<user[k].count<<endl;
				}
				cin>>choose;
				break;
				/************* 冒泡排序end  *************/
			}
			case 4: {
				/************* 快速排序start  *************/
				{
					int userCount=ReadUserFormPasswordTxt();
					time_t nowtime,nexttime;//用于统计时间
					nowtime=GetTickCount();// 获取当前时间
					//----------- 算法start ------------//
					QuickSort(0,userCount-1);
					//----------- 算法end ------------//
					nexttime=GetTickCount();// 获取排好序后的时间
					ofstream ofs;
					ofs.open("password_QuickSort.txt",ios::ate);
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ofs<<user[i].password<<"\t"<<user[i].count<<endl;// 写入文件
						i++;
					}
					cout<<"    快 速 排 序 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显 示时间
					cout<<"出现次数最多的 20 个密码是："<<endl;
					for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
						if(user[k].user_id==-1) {
							break;
						}
						cout<<user[k].password<<"\t"<<user[k].count<<endl;
					}
					cin>>choose;
					break;
				}
				/************* 快速排序end  *************/


				case 5:
					/************* 直接选择排序start  *************/
				{
					int userCount=ReadUserFormPasswordTxt();
					time_t nowtime,nexttime;//用于统计时间
					nowtime=GetTickCount();// 获取当前时间
					//----------- 算法start ------------//
					SelectSort(userCount);
					//----------- 算法end ------------//
					nexttime=GetTickCount();// 获取排好序后的时间
					ofstream ofs;
					ofs.open("password_SelectSort.txt",ios::ate);
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ofs<<user[i].password<<"\t"<<user[i].count<<endl;// 写入文件
						i++;
					}
					cout<<"    直接选择排 序 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显 示时间
					cout<<"出现次数最多的 20 个密码是："<<endl;
					for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
						if(user[k].user_id==-1) {
							break;
						}
						cout<<user[k].password<<"\t"<<user[k].count<<endl;
					}
					cin>>choose;
					break;
				}
				/************* 直接选择排序end *************/

				case 6:
					/************* 堆排序start  *************/
				{
					int userCount=ReadUserFormPasswordTxt();
					time_t nowtime,nexttime;//用于统计时间
					nowtime=GetTickCount();// 获取当前时间
					//----------- 算法start ------------//
					HeapSort(userCount-1);
					//----------- 算法end ------------//
					nexttime=GetTickCount();// 获取排好序后的时间
					ofstream ofs;
					ofs.open("password_HeapSort.txt",ios::ate);
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ofs<<user[i].password<<"\t"<<user[i].count<<endl;// 写入文件
						i++;
					}
					cout<<"    堆排 序 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;
					cout<<"出现次数最多的 20 个密码是："<<endl;
					for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
						if(user[k].user_id==-1) {
							break;
						}
						cout<<user[k].password<<"\t"<<user[k].count<<endl;
					}
					cin>>choose;
					break;
				}
				/************* 堆排序end *************/
				case 7:
					/************* 归并排序start  *************/
				{
					int userCount=ReadUserFormPasswordTxt();
					time_t nowtime,nexttime;//用于统计时间
					nowtime=GetTickCount();// 获取当前时间
					//----------- 算法start ------------//
					MergeSort(userCount);
					//----------- 算法end ------------//
					nexttime=GetTickCount();// 获取排好序后的时间
					ofstream ofs;
					ofs.open("password_MergeSort.txt",ios::ate);
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ofs<<user[i].password<<"\t"<<user[i].count<<endl;// 写入文件
						i++;
					}
					cout<<"    归并排 序 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显 示时间
					cout<<"出现次数最多的 20 个密码是："<<endl;
					for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
						if(user[k].user_id==-1) {
							break;
						}
						cout<<user[k].password<<"\t"<<user[k].count<<endl;
					}
					cin>>choose;
					break;
				}
				/************* 归并排序end  *************/

				case 8:
					/************* 基数排序start  *************/
				{
					int userCount=ReadUserFormPasswordTxt();
					time_t nowtime,nexttime;//用于统计时间
					nowtime=GetTickCount();// 获取当前时间
					cout<<nowtime<<endl;
					//----------- 算法start ------------//
					cout<<nowtime<<endl;
					RadixSort(10,7,userCount-1);
					//----------- 算法end ------------//
					nexttime= GetTickCount();// 获取排好序后的时间
					cout<<nexttime<<endl;
					ofstream ofs;
					ofs.open("password_RadixSort.txt",ios::ate);
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ofs<<user[i].password<<"\t"<<user[i].count<<endl;// 写入文件
						i++;
					}
					cout<<"    基数排 序 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显 示时间
					cout<<"出现次数最多的 20 个密码是："<<endl;
					for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
						if(user[k].user_id==-1) {
							break;
						}
						cout<<user[k].password<<"\t"<<user[k].count<<endl;
					}
					cin>>choose;
					break;
				}
				/************* 基数排序end *************/
				default: {
					return;
				}
			}
		}
	}
}

/* 读取user.txt，对id按照降序排序 */
void DescendingSortOfUserIdNumbers() {
	int choose=0;
	cout<<"请输入使用的排序方法 :"<<endl;
	cout<<"    1 直接插入排序 2 希尔排序 3 冒泡排序 4 快速排序 "<<endl;
	cout<<"   5 直接选择排序 6 堆排序  7 归并排序 8 基数排序 "<<endl;
	cin>>choose;
	while(1) {
		switch(choose) {
			case 1: {
				/************ 直接插入排序start  ************/
				int userCount= ReadUserFormUserTxt();
				time_t nowtime,nexttime;//用于统计时间
				nowtime=GetTickCount();// 获取当前时间
				//----------- 算法start ------------//
				InserSortOrderById(userCount);
				//----------- 算法end ------------//
				nexttime=GetTickCount();// 获取排好序后的时间
				cout<<"直 接 插 入 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;
				cout<<"出现次数最多的 20 个密码是："<<endl;
				for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
					if(user[k].count==-1) {
						break;
					}
					cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
				}
				cin>>choose;
				break;
				/************ 直接插入排序end  ************/
			}

			case 2:
				/************* 希尔排序start  *************/
			{
				int userCount= ReadUserFormUserTxt();
				time_t nowtime,nexttime;//用于统计时间
				nowtime=GetTickCount();// 获取当前时间
				//----------- 算法start ------------//
				ShellSortOrderById(userCount);
				//----------- 算法end ------------//
				nexttime=GetTickCount();// 获取排好序后的时间
				ofstream ocout;
				ocout.open("user_sorted.txt",ios::ate);
				{
					int i=0;
					while(1) {
						if(user[i].count==-1) {
							break;
						}
						ocout<<user[i].user_id<<"\t"<<user[i].password<<endl;// 写入文件
						i++;
					}

				}
				cout<<"      希 尔 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//倍数是为了方便显 示时间
				cout<<"出现次数最多的 20 个密码是："<<endl;
				for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
					if(user[k].count==-1) {
						break;
					}
					cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
				}
				cin>>choose;
				break;
				/************* 希尔排序end  *************/
			}
			case 3:
				/************* 冒泡排序start  *************/
			{
				int userCount=ReadUserFormUserTxt();
				time_t nowtime,nexttime;//用于统计时间
				nowtime=GetTickCount();// 获取当前时间
				//----------- 算法start ------------//
				BubbleSortOrderById(userCount);
				//----------- 算法start ------------//
				nexttime=GetTickCount();// 获取排好序后的时间

				cout<<"      冒 泡 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显示时间
				cout<<"出现次数最多的 20 个密码是："<<endl;
				for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
					if(user[k].count==-1) {
						break;
					}
					cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
				}
				cin>>choose;
				break;
				/************* 冒泡排序end  *************/
			}
			case 4: {
				/************* 快速排序start  *************/
				{
					int userCount=ReadUserFormUserTxt();
					time_t nowtime,nexttime;//用于统计时间
					nowtime=GetTickCount();// 获取当前时间
					//----------- 算法start ------------//
					QuickSortOrderById(0,userCount-1);
					//----------- 算法end ------------//
					nexttime=GetTickCount();// 获取排好序后的时间
					cout<<"    快 速 排 序 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显 示时间
					cout<<"出现次数最多的 20 个密码是："<<endl;
					for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
						if(user[k].count==-1) {
							break;
						}
						cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
					}
					cin>>choose;
					break;
				}
				/************* 快速排序end  *************/


				case 5:
					/************* 直接选择排序start  *************/
				{
					int userCount=ReadUserFormUserTxt();
					time_t nowtime,nexttime;//用于统计时间
					nowtime=GetTickCount();// 获取当前时间
					//----------- 算法start ------------//
					SelectSortOrderById(userCount);
					//----------- 算法end ------------//
					nexttime=GetTickCount();// 获取排好序后的时间

					cout<<"    直接选择排 序 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显 示时间
					cout<<"出现次数最多的 20 个密码是："<<endl;
					for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
						if(user[k].count==-1) {
							break;
						}
						cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
					}
					cin>>choose;
					break;
				}
				/************* 直接选择排序end *************/

				case 6:
					/************* 堆排序start  *************/
				{
					int userCount=ReadUserFormUserTxt();
					time_t nowtime,nexttime;//用于统计时间
					nowtime=GetTickCount();// 获取当前时间
					//----------- 算法start ------------//
					HeapSortOrderById(userCount-1);
					//----------- 算法end ------------//
					nexttime=GetTickCount();// 获取排好序后的时间

					cout<<"    堆排 序 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显 示时间
					cout<<"出现次数最多的 20 个密码是："<<endl;
					for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
						if(user[k].count==-1) {
							break;
						}
						cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
					}
					cin>>choose;
					break;
				}
				/************* 堆排序end *************/
				case 7:
					/************* 归并排序start  *************/
				{
					int userCount=ReadUserFormUserTxt();
					time_t nowtime,nexttime;//用于统计时间
					nowtime=GetTickCount();// 获取当前时间
					//----------- 算法start ------------//
					MergeSortOrderById(userCount);
					//----------- 算法end ------------//
					nexttime=GetTickCount();// 获取排好序后的时间
					cout<<"    归并排 序 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显 示时间
					cout<<"出现次数最多的 20 个密码是："<<endl;
					for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
						if(user[k].count==-1) {
							break;
						}
						cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
					}
					cin>>choose;
					break;
				}
				/************* 归并排序end  *************/

				case 8:
					/************* 基数排序start  *************/
				{
					int userCount=ReadUserFormUserTxt();
					time_t nowtime,nexttime;//用于统计时间
					nowtime=GetTickCount();// 获取当前时间
					//----------- 算法start ------------//
					RadixSortOrderById(10,7,userCount);
					//----------- 算法end ------------//
					nexttime= GetTickCount();// 获取排好序后的时间
					cout<<"    基数排 序 法 所 用 时 间 为 ：---"<<(nexttime-nowtime)<<"ms"<<endl;//* 倍数是为了方便显 示时间
					cout<<"出现次数最多的 20 个密码是："<<endl;
					for(int k=0; k<=19; k++) { // 输出出现次数最多的 20 个密码
						if(user[k].count==-1) {
							break;
						}
						cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
					}
					cin>>choose;
					break;
				}
				/************* 基数排序end *************/
				default: {
					return;
				}
			}
		}
	}
}

/**
 *@describtion： 随机生成2000随机数在1,230,000之间,随机生成20个大于1,230,000的
 *		以time函数值（即当前时间）作为种子数
 */
void setRandomNumber() {
	srand((unsigned)time(NULL));
	for(int i=0; i<=1999; i++) {
		randomNumber[i]=(rand()%1230000);      //生成1~1229999的整数
	}
	for(int j=2000; j<=2019; j++) {
		randomNumber[j]=(rand()%1230000)+1230000;
	}
}


/**读取user.txt，使用链表存放，使用顺序查找***/
void SequentialSearchOfUserLinkNode() {
	int id;
	string password;
	UserNode *userHead = new UserNode;
	UserNode *userTail=NULL;
	userTail=userHead;
	ifstream ifs;
	ifs.open("user.txt");
	int i=0;
	while(!ifs.eof()) {
		ifs>>id>>password;
		//防止多读如回车符
		if (ifs.fail()) {
			break;
		}
		UserNode *tempUser = new UserNode;
		tempUser->nextNode=NULL;
		tempUser->userNode_id=id;
		tempUser->userNode_password = password;
		userTail->nextNode=tempUser;
		userTail=tempUser;
		i++;
	}
	ifs.close();//判断是否读到末尾
	//设置随机数
	setRandomNumber();
	//顺序查找
	int currRandomNumber;
	UserNode *p=NULL;
	time_t starttime,endtime;
	cout<<"顺序查找开始"<<endl;
	starttime=GetTickCount();
	for(int i=0; i<2020; i++) {
		p = userHead;
		currRandomNumber =randomNumber[i];
		while(p!=NULL) {
			if(p->userNode_id==currRandomNumber) {
				cout<<"找到"<<i<<":-id-"<<p->userNode_id<<"-密码-"<<p->userNode_password<<endl;
				break;
			}
			p=p->nextNode;
		}
	}
	endtime = GetTickCount();
	cout<<"顺序查找结束"<<endl;
	cout<<"查找所用时间为：----"<<(endtime-starttime)<<"ms"<<endl;
	free(userHead);
}

/**
 *@describtion 二分查找
 */
int BinSearch(int k,int userCount) {
	int low=0,high=userCount-1,mid;
	while(low<=high) {
		mid=(low+high)/2;
		if(k==user[mid].user_id)
			return mid+1;
		if(k>user[mid].user_id)
			high=mid-1;
		else
			low = mid+1;
	}
	return 0;
}

//读取user_sorted.txt，使用二分查找
void SearchUserIdFromUserSortTxtByBinSearch() {
	int userCount=ReadUserIdFormUserSortedTxt();
	//设置随机数
	setRandomNumber();
	//根据二叉树进行查找
	int currRandomNumber=0;
	time_t startTime,endTime;
	cout<<"二分查找开始"<<endl;
	startTime=GetTickCount();
	for(int k=0; k<2020; k++) {
		currRandomNumber=randomNumber[k];
		//调用二分查找
		int s = BinSearch(currRandomNumber,userCount);
		if(s!=0) {
			cout<<"找到"<<k<<":-id-"<<user[s].user_id<<"-密码-"<<user[s].password<<endl;
		}
	}
	endTime = GetTickCount();
	cout<<"二分查找结束"<<endl;
	cout<<"查找所用时间为："<<(endTime-startTime)<<"ms"<<endl;
}


//读取user.txt，按照用户id使用二叉排序树存放.
void SearchUserIdByUserBinaryTree() {
	ifstream ifs;
	ifs.open("user.txt");
	UserTree *Root = new UserTree;
	UserTree *temp=NULL;
	UserTree *child=NULL;
	int id;
	string password;
	ifs>>id>>password;
	Root->user_id=id;
	Root->password=password;
	Root->lchild=NULL;
	Root->rchild=NULL;
	while(!ifs.eof()) {
		ifs>>id>>password;
		child=new UserTree;
		child->user_id=id;
		child->password=password;
		temp=Root;
		//插入到对应的位置,大的在右边，小的在左边
		while(true) {
			if(child->user_id<=temp->user_id && temp->lchild==NULL) {
				temp->lchild=child;
				break;
			} else if(child->user_id>=temp->user_id && temp->rchild==NULL) {
				temp->rchild=child;
				break;
			} else {
				if(child->user_id<=temp->user_id)
					temp=temp->lchild;
				else if(child->user_id>=temp->user_id)
					temp=temp->rchild;
			}
		}
	}
	ifs.close();
	//设置随机数
	setRandomNumber();
	//根据二叉树进行查找
	int currRandomNumber ;
	UserTree *p=NULL;
	time_t startTime,endTime;
	cout<<"二叉树查找开始"<<endl;
	startTime=GetTickCount();;
	for(int k=0; k<2020; k++) {
		p=Root;
		currRandomNumber=randomNumber[k];
		while(p!=NULL) {
			if(p->user_id==currRandomNumber) {
				cout<<"找到"<<k<<":-id-"<<p->user_id<<"-密码-"<<p->password<<endl;
				break;
			}
			if(currRandomNumber>p->user_id) {
				p=p->rchild;
			} else if(currRandomNumber<p->user_id) {
				p=p->lchild;
			}
		}
	}
	endTime = GetTickCount();
	cout<<"二叉树查找结束"<<endl;
	cout<<"查找所用时间为："<<(endTime-startTime)<<"ms"<<endl;
	free(Root);
}

int toHash(string key) {
	int arraySize = 11131; // 数组大小一般取质数
	int hashCode = 0;
	for (int i = 0; i <key.length(); i++) { // 从字符串的左边开始计算
		int letterValue = key[i] - 0;// 将获取到的字符串转换成数字，比如a的码值是97，则97-96=1
		// 就代表a的值，同理b=2；
		hashCode = ((hashCode << 5) + letterValue) % 11131;// 防止编码溢出，对每步结果都进行取模运算
	}
	return hashCode;
}

void HashTableStoragePasswordTxt() {
	//置初值
	for(int i=0; i<11131; i++) {
		hashTable[i].firstUser=NULL;
	}
	ifstream ifs;
	ifs.open("password.txt" );
	//用户数
	int currentNumberOfLines=0;
	char ch;
	string a;
	int b;
	int adr=0;
	while(!ifs.eof()) {
		ifs>>a>>b;
		//防止多读如回车符
		if (ifs.fail()) {
			break;
		}
		UserNode *q=new UserNode();
		q->userNode_count=b;
		q->userNode_password=a;
		q->userNode_id=currentNumberOfLines;
		q->nextNode = NULL;
		adr=toHash(a);
		if(hashTable[adr].firstUser==NULL) {
			q->nextNode = NULL;
			hashTable[adr].firstUser=q;
		} else {
			q->nextNode=hashTable[adr].firstUser;
			hashTable[adr].firstUser=q;
		}
		currentNumberOfLines++;
	}
	ifs.close();
	UserNode *q1=new UserNode();
	for(int j=0; j<25; j++) {
		time_t nowTime,nextTime;//用于统计时间
		nowTime=GetTickCount();// 获取当前时间
		adr=0;
		adr=toHash(havePassword[j]);
		q1=hashTable[adr].firstUser;
		int temp=0;
		while(q1!=NULL) {
			temp++;
			if(q1->userNode_password==havePassword[j]) {
				break;
			}
			q1=q1->nextNode;
		}
		nextTime=GetTickCount();// 获取当前时间
		if(q1!=NULL) {
			cout<<"成功 密码 "<<q1->userNode_password<<" 次数 "<<q1->userNode_password<<" 比较："<<temp<<" 时间:"<<(nextTime-nowTime)<<endl;
		} else {
			cout<<"失败 密码"<<havePassword[j]<<" 比较："<<temp<<" 时间:"<<(nextTime-nowTime)<<endl;
		}
	}
}

int main() {
	int  flag=0;
	do {
		cout<<"请输入题数 :"<<endl;
		cout<<"1 读取user.txt写入password； 2 读取password.txt 用7个算法排序； 3 读取user.txt链表存放顺序查找2020个id；"<<endl;
		cout<<"4 读取user.txt二叉排序树存放查找2020个id； 5 读取user.txt 估计7个算法排序时间； 6 二分查找id；"<<endl;
		cout<<"7 用顺序表+链表哈希存储password.txt"<<endl;
		int test=0;
		cin>>test;
		switch(test) {
			case 0:
				break;
			case 1:
				ReadPasswordOfUserTxtAndWrite();
				break;
			case 2:
				DescendingSortOfPasswordNumbers();
				break;
			case 3:
				SequentialSearchOfUserLinkNode();
				break;
			case 4:
				SearchUserIdByUserBinaryTree();
				break;
			case 5:
				DescendingSortOfUserIdNumbers();
				break;
			case 6:
				SearchUserIdFromUserSortTxtByBinSearch();
				break;
			case 7:
				HashTableStoragePasswordTxt();
				break;
		}
		cout<<"0 退出 1 继续"<<endl;
		cin>>flag;
	} while(flag==1);
	return 0; 
}



