#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<stdlib.h>
#include<windows.h>
using namespace std;
/** ����user���� **/
class User {
	public:
		User() {
			user_id=0;
			password="";
			count=0;
		}
		//�û�id
		int user_id;
		//�û�����
		string password;
		//
		int count;
		//�����������������ƺ�
		~User() {
		}
};
/** ����user���� **/
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
/** ����user������ **/
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
/** ����user��ϣ�� **/
typedef struct {
	UserNode *firstUser;
} HashTable;


#define IdNum 1250000
HashTable hashTable[11131];//��ϣ�� 
User user[IdNum];// �����û�
//UserNode userNode[IdNum];
string psw[IdNum];// ���ڴ���ظ�������
int randomNumber[2020];
int pw = 0;// ����ȷ���ŵ� passw�����е����
int status = 0;// ����ȷ���Ƿ��ظ�
//20������5��������
string havePassword[25]= {"0123456789","123456","1234567","12345678","123456789",
                          "1234567890","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa",
                          "aaaaaaaaaa","aaaaaaaaaaa","aaaaaaaaaaaa","aaaaaaaaaaaaa","aaaaaaaaaaaaaa",
                          "1111111111","111111111","11111111","1111111","111111",
                          "qianzhenghao","malechao","zhoujiawei","aaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaa"
                         };
/**
 *@description ��ȡuser.txt���û�
 *@return �û���
 */
int ReadUserFormUserTxt() {
	ifstream ifs;
	ifs.open("user.txt" );
	int currentNumberOfLines=0;
	//��Ӧuser.txt�е�����
	int user_id;
	string password;
	while(!ifs.eof()) {
		ifs>>user_id>>password;
		//��ֹ�����س���
		if (ifs.fail()) {
			break;
		}
		user[currentNumberOfLines].user_id=user_id;
		user[currentNumberOfLines].password=password;
		user[currentNumberOfLines].count=currentNumberOfLines;
		//cout<<currentNumberOfLines<<"---"<<password<<endl;
		currentNumberOfLines++;
	}
	user[currentNumberOfLines].count=-1;//�����һ�� id ����Ϊ-1 �����ж��Ƿ����һ���û�
	ifs.close();
	return currentNumberOfLines;
}
/**
 *@description ��ȡuser_sorted.txt���û�
 *@return �û���
 */
int ReadUserIdFormUserSortedTxt() {
	ifstream ifs;
	ifs.open("user_sorted.txt");
	//�û���
	int currentNumberOfLines=0;
	string a;
	int b;
	while(!ifs.eof()) {
		ifs>>b>>a;
		//��ֹ�����س���
		if (ifs.fail()) {
			break;
		}
		user[currentNumberOfLines].user_id=b;
		user[currentNumberOfLines].password=a;
		user[currentNumberOfLines].count=currentNumberOfLines;
		//cout<<currentNumberOfLines<<"---"<<user[currentNumberOfLines].password<<endl;
		currentNumberOfLines++;
	}
	user[currentNumberOfLines].count=-1;// �����һ�� id ����Ϊ-1 �����ж��Ƿ� ���һ���û�
	ifs.close();
	return currentNumberOfLines;
}
/**
 *@description ��ȡpassword.txt���û�
 *@return �û���
 */
int ReadUserFormPasswordTxt() {
	ifstream ifs;
	ifs.open("password.txt" );
	//�û���
	int currentNumberOfLines=0;
	char ch;
	string a;
	int b;
	while(!ifs.eof()) {
		ifs>>a>>b;
		//��ֹ�����س���
		if (ifs.fail()) {
			break;
		}
		user[currentNumberOfLines].user_id=currentNumberOfLines;
		user[currentNumberOfLines].password=a;
		user[currentNumberOfLines].count=b;
		currentNumberOfLines++;
	}
	user[currentNumberOfLines].user_id=-1;// �����һ�� id ����Ϊ-1 �����ж��Ƿ� ���һ���û�
	ifs.close();
	return currentNumberOfLines;
}

/**
 * ��ȡ�ļ������룬ͳ��������ִ�����д���ļ� password.txt
 */
void ReadPasswordOfUserTxtAndWrite() {
	int userCout=ReadUserFormUserTxt();
	int currentNumberOfLines=0;
	int count=0;//password�ظ�����
	ofstream ofs;
	ofs.open("password.txt",ios::ate);
	int currentNumberOfPasswrodLines =0;
	while(1) {
		//��������һ��user������ѭ��
		if(user[currentNumberOfLines].count==-1) {
			break;
		}
		//�����ǰ�û�����password�����е��������룬������
		for(int j=0; j<=currentNumberOfLines; j++) {
			if(psw[j]=="") {
				break;
			}
			if(psw[j]==user[currentNumberOfLines].password) {
				status=1;
				break;
			}
		}
		//����
		if(status==1) {
			currentNumberOfLines++;
			count=0;
			status=0;
			continue;
		}
		//û���ظ���������������
		psw[currentNumberOfPasswrodLines]=user[currentNumberOfLines].password;
		// ȷ���ظ�����
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
		ofs<<user[currentNumberOfLines].password<<"\t"<<count<<endl;//д���ļ�
		currentNumberOfLines++;
		count=0;
		currentNumberOfPasswrodLines++;
		status=0;
	}
	ofs.close();
}

/**
 *@description: ֱ�Ӳ�������
 * 		ÿ��i�˱�֤ǰi��Ԫ�����򣬵�����֤�����һ��ǰ��ЩԪ�ع�λ
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
 *@description: ֱ�Ӳ�������
 * 		ÿ��i�˱�֤ǰi��Ԫ�����򣬵�����֤�����һ��ǰ��ЩԪ�ع�λ
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
 *@description: ϣ������
 * 		ÿi������Ϊd=n/2^i,��֤�����е�һ��λ�����d��Ԫ������
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
 *@description: ϣ������
 * 		ÿi������Ϊd=n/2^i,��֤�����е�һ��λ�����d��Ԫ������
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
 *@description: ð������
 * 		ÿ�˱�֤����һ��Ԫ�ع�λ
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
 *@description: ð������
 * 		ÿ�˱�֤����һ��Ԫ�ع�λ
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
 *@description: ��������
 * 		ÿ�˱�֤����һ��Ԫ�ع�λ������ð�ݲ�ͬ����ֻ�Ե�ǰ����ĵ�һ��Ԫ�ع�λ
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
 *@description: ��������
 * 		ÿ�˱�֤����һ��Ԫ�ع�λ������ð�ݲ�ͬ����ֻ�Ե�ǰ����ĵ�һ��Ԫ�ع�λ
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
 *@description: ��ֱ�ӣ���ѡ������
 * 		ÿ�˱�֤����λ�õ�һ��Ԫ�ع�λ�����Ԫ��ֻ����������С������ð�ݲ�ͬ����ÿ��ֻ����һ��λ��
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
 *@description: ��ֱ�ӣ���ѡ������
 * 		ÿ�˱�֤����λ�õ�һ��Ԫ�ع�λ�����Ԫ��ֻ����������С������ð�ݲ�ͬ����ÿ��ֻ����һ��λ��
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
 *@description: ɸѡ
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
 *@description:  ��ѡ������
 * 		ԭ��С���ѣ���������Ǵ����ӽڵ㣩 �ٽ��ѣ����ն������Ե�һ��Ԫ��Ϊ���ڵ㣬��˳����������ɶ�
 *		�ڰ�����ѱ�ΪС����
 *		�۰ѵ�һ��Ԫ�غ����һ��Ԫ�ؽ�������ʱ�����һ��Ԫ���Թ�λ���Ͱ����޳�
 *		��ѭ���ڢ� ֱ������ֻ��һ��Ԫ�أ��������
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
 *@description: ɸѡ
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
 *@description:  ��ѡ������
 * 		ԭ��С���ѣ���������Ǵ����ӽڵ㣩 �ٽ��ѣ����ն������Ե�һ��Ԫ��Ϊ���ڵ㣬��˳����������ɶ�
 *		�ڰ�����ѱ�ΪС����
 *		�۰ѵ�һ��Ԫ�غ����һ��Ԫ�ؽ�������ʱ�����һ��Ԫ���Թ�λ���Ͱ����޳�
 *		��ѭ���ڢ� ֱ������ֻ��һ��Ԫ�أ��������
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
	cout<<"user---��"<<endl;
	for(int k=0; k<=n; k++) { // ������ִ������� 20 ������
		if(user[k].user_id==-1) {
			break;
		}
		cout<<user[k].password<<"\t"<<user[k].count<<endl;
	}
}

/**
 *@description:  �鲢����
 */
void MergeOrderById(int low,int mid,int high) {
	User *tempUser =new User[high-low+1];// ��ʱ�û�����
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
 *@description:  �鲢����
 * 		ԭ���������Ȳ�ֳɲ��ָ�����飬�ٰ�˳�������ϲ���һ���������飬ֱ������Ϊn����������
 * 		�ٷָ�����Ϊ����
 *		���ظ���ֱ�����鲻���ٷָ�
 *		�۰�ÿ������������˳��ϲ���һ����������
 *		���ظ���ֱ�����鳤�ȵ�n
 */
void MergeSortOrderById(int n) {
	int length;
	for(length=1; length<n; length=2*length)
		MergePassOrderById(length,n);
}
/**
 *@description:  �鲢����
 */
void Merge(int low,int mid,int high) {
	User *tempUser =new User[high-low+1];// ��ʱ�û�����
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
 *@description:  �鲢����
 * 		ԭ���������Ȳ�ֳɲ��ָ�����飬�ٰ�˳�������ϲ���һ���������飬ֱ������Ϊn����������
 * 		�ٷָ�����Ϊ����
 *		���ظ���ֱ�����鲻���ٷָ�
 *		�۰�ÿ������������˳��ϲ���һ����������
 *		���ظ���ֱ�����鳤�ȵ�n
 */
void MergeSort(int n) {
	int length;
	for(length=1; length<n; length=2*length)
		MergePass(length,n);
}

/**
 *@description:  �õ������е�λ�������֣���90��2��
 *@return  λ��������9��
 */
int GetNumberOfDigitInNumber(int number,int digit) {
	int temp = 1;
	for (int i = 0; i < digit - 1; i++)
		temp *= 10;
	return (number / temp) % 10;
}

/**
 *@description:  �õ������е�λ�������֣���90��2��
 *		�ٷ��䣺��һά���鰴ÿλ�Ļ�����ŵ���ά������
 *		���ռ����Ѷ�ά���鰴������Ż�һά������
 *		���ظ��٢�ֱ���������λ������
 */
void RadixSortOrderById( int redix,int digitCout,int userCount) {
	User **radixArrays=(User **)malloc(sizeof(User*)*(redix));    //�ֱ�Ϊ0~9�����Ĵ�ſռ�
	for (int i=0; i<10; i++) {
		radixArrays[i] = new User[userCount+1];
		radixArrays[i][0].user_id = 0;    //indexΪ0����¼�������ݵĸ���
	}
	for (int pos=1; pos<=digitCout; pos++) { //�Ӹ�λ��ʼ��Ͱ����Ͱ
		for (int i=0; i<userCount; i++) {  //�������  ������ѭ��λ��
			//�ö�ά��������λ�����һά���飬[��ǰλ����][�ظ�����Ŀ]=һά����
			int num = GetNumberOfDigitInNumber(user[i].user_id,pos);
			//[][�ظ�����Ŀ++]�����ظ�����Ŀ¼��[][0]��
			int index = ++radixArrays[num][0].user_id;
			radixArrays[num][index].password = user[i].password;
			radixArrays[num][index].user_id = user[i].user_id;
		}
		for (int i=redix-1, j=0; i>=0; i--) { //�ռ�
			//[��ǰλ����][�ظ�����Ŀ]�Ե�ǰλ���������ռ�������ά�����Ϊһά����
			for (int k = 1; k <= radixArrays[i][0].user_id; k++) {
				user[j] = radixArrays[i][k];
				user[j] = radixArrays[i][k];
				j++;
			}
			radixArrays[i][0].user_id = 0;    //��Ͱ��ϣ���λ
		}
	}
}
/**
 *@description:  �õ������е�λ�������֣���90��2��
 *		�ٷ��䣺��һά���鰴ÿλ�Ļ�����ŵ���ά������
 *		���ռ����Ѷ�ά���鰴������Ż�һά������
 *		���ظ��٢�ֱ���������λ������
 */
void RadixSort( int redix,int digitCout,int userCount) {
	User **radixArrays=(User **)malloc(sizeof(User*)*(redix));    //�ֱ�Ϊ0~9�����Ĵ�ſռ�
	for (int i=0; i<10; i++) {
		radixArrays[i] = new User[userCount+1];
		radixArrays[i][0].count = 0;    //indexΪ0����¼�������ݵĸ���
	}
	for (int pos=1; pos<=digitCout; pos++) { //�Ӹ�λ��ʼ��Ͱ����Ͱ
		for (int i=0; i<userCount; i++) {  //�������  ������ѭ��λ��
			//�ö�ά��������λ�����һά���飬[��ǰλ����][�ظ�����Ŀ]=һά����
			int num = GetNumberOfDigitInNumber(user[i].count,pos);
			//[][�ظ�����Ŀ++]�����ظ�����Ŀ¼��[][0]��
			int index = ++radixArrays[num][0].count;
			radixArrays[num][index].password = user[i].password;
			radixArrays[num][index].count = user[i].count;
		}
		for (int i=redix-1, j=0; i>=0; i--) { //�ռ�
			//[��ǰλ����][�ظ�����Ŀ]�Ե�ǰλ���������ռ�������ά�����Ϊһά����
			for (int k = 1; k <= radixArrays[i][0].count; k++) {
				user[j] = radixArrays[i][k];
				user[j] = radixArrays[i][k];
				j++;
			}
			radixArrays[i][0].count = 0;    //��Ͱ��ϣ���λ
		}
	}
}

/* ��ȡpassword.txt����������ִ������ս������� */
void DescendingSortOfPasswordNumbers() {
	int choose=0;
	cout<<"������ʹ�õ����򷽷� :"<<endl;
	cout<<"    1 ֱ�Ӳ������� 2 ϣ������ 3 ð������ 4 �������� "<<endl;
	cout<<"   5 ֱ��ѡ������ 6 ������  7 �鲢���� 8 �������� "<<endl;
	cin>>choose;
	while(1) {
		switch(choose) {
			case 1: {
				/************ ֱ�Ӳ�������start  ************/
				int userCount= ReadUserFormPasswordTxt();
				time_t nowtime,nexttime;//����ͳ��ʱ��
				nowtime=GetTickCount();// ��ȡ��ǰʱ��
				//----------- �㷨start ------------//
				InserSort(userCount);
				//----------- �㷨end ------------//
				nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
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

				cout<<"ֱ �� �� �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;
				cout<<"���ִ������� 20 �������ǣ�"<<endl;
				for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
					if(user[k].user_id==-1) {
						break;
					}
					cout<<user[k].password<<"\t"<<user[k].count<<endl;
				}
				cin>>choose;
				break;
				/************ ֱ�Ӳ�������end  ************/
			}

			case 2:
				/************* ϣ������start  *************/
			{
				int userCount= ReadUserFormPasswordTxt();
				time_t nowtime,nexttime;//����ͳ��ʱ��
				nowtime=GetTickCount();// ��ȡ��ǰʱ��
				//----------- �㷨start ------------//
				ShellSort(userCount);
				//----------- �㷨end ------------//
				nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
				ofstream ocout;
				ocout.open("password_ShellSort.txt",ios::ate);
				{
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ocout<<user[i].password<<"\t"<<user[i].count<<endl;// д���ļ�
						i++;
					}

				}
				cout<<"      ϣ �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//������Ϊ�˷����� ʾʱ��
				cout<<"���ִ������� 20 �������ǣ�"<<endl;
				for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
					if(user[k].user_id==-1) {
						break;
					}
					cout<<user[k].password<<"\t"<<user[k].count<<endl;
				}
				cin>>choose;
				break;
				/************* ϣ������end  *************/
			}
			case 3:
				/************* ð������start  *************/
			{
				int userCount=ReadUserFormPasswordTxt();
				time_t nowtime,nexttime;//����ͳ��ʱ��
				nowtime=GetTickCount();// ��ȡ��ǰʱ��
				//----------- �㷨start ------------//
				BubbleSort(userCount);
				//----------- �㷨start ------------//
				nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
				ofstream ofs;
				ofs.open("password_BubbleSort.txt",ios::ate);
				int i=0;
				while(1) {
					if(user[i].user_id==-1) {
						break;
					}
					ofs<<user[i].password<<"\t"<<user[i].count<<endl;// д���ļ�
					i++;
				}
				cout<<"      ð �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷�����ʾʱ��
				cout<<"���ִ������� 20 �������ǣ�"<<endl;
				for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
					if(user[k].user_id==-1) {
						break;
					}
					cout<<user[k].password<<"\t"<<user[k].count<<endl;
				}
				cin>>choose;
				break;
				/************* ð������end  *************/
			}
			case 4: {
				/************* ��������start  *************/
				{
					int userCount=ReadUserFormPasswordTxt();
					time_t nowtime,nexttime;//����ͳ��ʱ��
					nowtime=GetTickCount();// ��ȡ��ǰʱ��
					//----------- �㷨start ------------//
					QuickSort(0,userCount-1);
					//----------- �㷨end ------------//
					nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
					ofstream ofs;
					ofs.open("password_QuickSort.txt",ios::ate);
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ofs<<user[i].password<<"\t"<<user[i].count<<endl;// д���ļ�
						i++;
					}
					cout<<"    �� �� �� �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷����� ʾʱ��
					cout<<"���ִ������� 20 �������ǣ�"<<endl;
					for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
						if(user[k].user_id==-1) {
							break;
						}
						cout<<user[k].password<<"\t"<<user[k].count<<endl;
					}
					cin>>choose;
					break;
				}
				/************* ��������end  *************/


				case 5:
					/************* ֱ��ѡ������start  *************/
				{
					int userCount=ReadUserFormPasswordTxt();
					time_t nowtime,nexttime;//����ͳ��ʱ��
					nowtime=GetTickCount();// ��ȡ��ǰʱ��
					//----------- �㷨start ------------//
					SelectSort(userCount);
					//----------- �㷨end ------------//
					nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
					ofstream ofs;
					ofs.open("password_SelectSort.txt",ios::ate);
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ofs<<user[i].password<<"\t"<<user[i].count<<endl;// д���ļ�
						i++;
					}
					cout<<"    ֱ��ѡ���� �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷����� ʾʱ��
					cout<<"���ִ������� 20 �������ǣ�"<<endl;
					for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
						if(user[k].user_id==-1) {
							break;
						}
						cout<<user[k].password<<"\t"<<user[k].count<<endl;
					}
					cin>>choose;
					break;
				}
				/************* ֱ��ѡ������end *************/

				case 6:
					/************* ������start  *************/
				{
					int userCount=ReadUserFormPasswordTxt();
					time_t nowtime,nexttime;//����ͳ��ʱ��
					nowtime=GetTickCount();// ��ȡ��ǰʱ��
					//----------- �㷨start ------------//
					HeapSort(userCount-1);
					//----------- �㷨end ------------//
					nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
					ofstream ofs;
					ofs.open("password_HeapSort.txt",ios::ate);
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ofs<<user[i].password<<"\t"<<user[i].count<<endl;// д���ļ�
						i++;
					}
					cout<<"    ���� �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;
					cout<<"���ִ������� 20 �������ǣ�"<<endl;
					for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
						if(user[k].user_id==-1) {
							break;
						}
						cout<<user[k].password<<"\t"<<user[k].count<<endl;
					}
					cin>>choose;
					break;
				}
				/************* ������end *************/
				case 7:
					/************* �鲢����start  *************/
				{
					int userCount=ReadUserFormPasswordTxt();
					time_t nowtime,nexttime;//����ͳ��ʱ��
					nowtime=GetTickCount();// ��ȡ��ǰʱ��
					//----------- �㷨start ------------//
					MergeSort(userCount);
					//----------- �㷨end ------------//
					nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
					ofstream ofs;
					ofs.open("password_MergeSort.txt",ios::ate);
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ofs<<user[i].password<<"\t"<<user[i].count<<endl;// д���ļ�
						i++;
					}
					cout<<"    �鲢�� �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷����� ʾʱ��
					cout<<"���ִ������� 20 �������ǣ�"<<endl;
					for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
						if(user[k].user_id==-1) {
							break;
						}
						cout<<user[k].password<<"\t"<<user[k].count<<endl;
					}
					cin>>choose;
					break;
				}
				/************* �鲢����end  *************/

				case 8:
					/************* ��������start  *************/
				{
					int userCount=ReadUserFormPasswordTxt();
					time_t nowtime,nexttime;//����ͳ��ʱ��
					nowtime=GetTickCount();// ��ȡ��ǰʱ��
					cout<<nowtime<<endl;
					//----------- �㷨start ------------//
					cout<<nowtime<<endl;
					RadixSort(10,7,userCount-1);
					//----------- �㷨end ------------//
					nexttime= GetTickCount();// ��ȡ�ź�����ʱ��
					cout<<nexttime<<endl;
					ofstream ofs;
					ofs.open("password_RadixSort.txt",ios::ate);
					int i=0;
					while(1) {
						if(user[i].user_id==-1) {
							break;
						}
						ofs<<user[i].password<<"\t"<<user[i].count<<endl;// д���ļ�
						i++;
					}
					cout<<"    ������ �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷����� ʾʱ��
					cout<<"���ִ������� 20 �������ǣ�"<<endl;
					for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
						if(user[k].user_id==-1) {
							break;
						}
						cout<<user[k].password<<"\t"<<user[k].count<<endl;
					}
					cin>>choose;
					break;
				}
				/************* ��������end *************/
				default: {
					return;
				}
			}
		}
	}
}

/* ��ȡuser.txt����id���ս������� */
void DescendingSortOfUserIdNumbers() {
	int choose=0;
	cout<<"������ʹ�õ����򷽷� :"<<endl;
	cout<<"    1 ֱ�Ӳ������� 2 ϣ������ 3 ð������ 4 �������� "<<endl;
	cout<<"   5 ֱ��ѡ������ 6 ������  7 �鲢���� 8 �������� "<<endl;
	cin>>choose;
	while(1) {
		switch(choose) {
			case 1: {
				/************ ֱ�Ӳ�������start  ************/
				int userCount= ReadUserFormUserTxt();
				time_t nowtime,nexttime;//����ͳ��ʱ��
				nowtime=GetTickCount();// ��ȡ��ǰʱ��
				//----------- �㷨start ------------//
				InserSortOrderById(userCount);
				//----------- �㷨end ------------//
				nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
				cout<<"ֱ �� �� �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;
				cout<<"���ִ������� 20 �������ǣ�"<<endl;
				for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
					if(user[k].count==-1) {
						break;
					}
					cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
				}
				cin>>choose;
				break;
				/************ ֱ�Ӳ�������end  ************/
			}

			case 2:
				/************* ϣ������start  *************/
			{
				int userCount= ReadUserFormUserTxt();
				time_t nowtime,nexttime;//����ͳ��ʱ��
				nowtime=GetTickCount();// ��ȡ��ǰʱ��
				//----------- �㷨start ------------//
				ShellSortOrderById(userCount);
				//----------- �㷨end ------------//
				nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
				ofstream ocout;
				ocout.open("user_sorted.txt",ios::ate);
				{
					int i=0;
					while(1) {
						if(user[i].count==-1) {
							break;
						}
						ocout<<user[i].user_id<<"\t"<<user[i].password<<endl;// д���ļ�
						i++;
					}

				}
				cout<<"      ϣ �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//������Ϊ�˷����� ʾʱ��
				cout<<"���ִ������� 20 �������ǣ�"<<endl;
				for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
					if(user[k].count==-1) {
						break;
					}
					cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
				}
				cin>>choose;
				break;
				/************* ϣ������end  *************/
			}
			case 3:
				/************* ð������start  *************/
			{
				int userCount=ReadUserFormUserTxt();
				time_t nowtime,nexttime;//����ͳ��ʱ��
				nowtime=GetTickCount();// ��ȡ��ǰʱ��
				//----------- �㷨start ------------//
				BubbleSortOrderById(userCount);
				//----------- �㷨start ------------//
				nexttime=GetTickCount();// ��ȡ�ź�����ʱ��

				cout<<"      ð �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷�����ʾʱ��
				cout<<"���ִ������� 20 �������ǣ�"<<endl;
				for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
					if(user[k].count==-1) {
						break;
					}
					cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
				}
				cin>>choose;
				break;
				/************* ð������end  *************/
			}
			case 4: {
				/************* ��������start  *************/
				{
					int userCount=ReadUserFormUserTxt();
					time_t nowtime,nexttime;//����ͳ��ʱ��
					nowtime=GetTickCount();// ��ȡ��ǰʱ��
					//----------- �㷨start ------------//
					QuickSortOrderById(0,userCount-1);
					//----------- �㷨end ------------//
					nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
					cout<<"    �� �� �� �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷����� ʾʱ��
					cout<<"���ִ������� 20 �������ǣ�"<<endl;
					for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
						if(user[k].count==-1) {
							break;
						}
						cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
					}
					cin>>choose;
					break;
				}
				/************* ��������end  *************/


				case 5:
					/************* ֱ��ѡ������start  *************/
				{
					int userCount=ReadUserFormUserTxt();
					time_t nowtime,nexttime;//����ͳ��ʱ��
					nowtime=GetTickCount();// ��ȡ��ǰʱ��
					//----------- �㷨start ------------//
					SelectSortOrderById(userCount);
					//----------- �㷨end ------------//
					nexttime=GetTickCount();// ��ȡ�ź�����ʱ��

					cout<<"    ֱ��ѡ���� �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷����� ʾʱ��
					cout<<"���ִ������� 20 �������ǣ�"<<endl;
					for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
						if(user[k].count==-1) {
							break;
						}
						cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
					}
					cin>>choose;
					break;
				}
				/************* ֱ��ѡ������end *************/

				case 6:
					/************* ������start  *************/
				{
					int userCount=ReadUserFormUserTxt();
					time_t nowtime,nexttime;//����ͳ��ʱ��
					nowtime=GetTickCount();// ��ȡ��ǰʱ��
					//----------- �㷨start ------------//
					HeapSortOrderById(userCount-1);
					//----------- �㷨end ------------//
					nexttime=GetTickCount();// ��ȡ�ź�����ʱ��

					cout<<"    ���� �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷����� ʾʱ��
					cout<<"���ִ������� 20 �������ǣ�"<<endl;
					for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
						if(user[k].count==-1) {
							break;
						}
						cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
					}
					cin>>choose;
					break;
				}
				/************* ������end *************/
				case 7:
					/************* �鲢����start  *************/
				{
					int userCount=ReadUserFormUserTxt();
					time_t nowtime,nexttime;//����ͳ��ʱ��
					nowtime=GetTickCount();// ��ȡ��ǰʱ��
					//----------- �㷨start ------------//
					MergeSortOrderById(userCount);
					//----------- �㷨end ------------//
					nexttime=GetTickCount();// ��ȡ�ź�����ʱ��
					cout<<"    �鲢�� �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷����� ʾʱ��
					cout<<"���ִ������� 20 �������ǣ�"<<endl;
					for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
						if(user[k].count==-1) {
							break;
						}
						cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
					}
					cin>>choose;
					break;
				}
				/************* �鲢����end  *************/

				case 8:
					/************* ��������start  *************/
				{
					int userCount=ReadUserFormUserTxt();
					time_t nowtime,nexttime;//����ͳ��ʱ��
					nowtime=GetTickCount();// ��ȡ��ǰʱ��
					//----------- �㷨start ------------//
					RadixSortOrderById(10,7,userCount);
					//----------- �㷨end ------------//
					nexttime= GetTickCount();// ��ȡ�ź�����ʱ��
					cout<<"    ������ �� �� �� �� ʱ �� Ϊ ��---"<<(nexttime-nowtime)<<"ms"<<endl;//* ������Ϊ�˷����� ʾʱ��
					cout<<"���ִ������� 20 �������ǣ�"<<endl;
					for(int k=0; k<=19; k++) { // ������ִ������� 20 ������
						if(user[k].count==-1) {
							break;
						}
						cout<<user[k].user_id<<"\t"<<user[k].password<<endl;
					}
					cin>>choose;
					break;
				}
				/************* ��������end *************/
				default: {
					return;
				}
			}
		}
	}
}

/**
 *@describtion�� �������2000�������1,230,000֮��,�������20������1,230,000��
 *		��time����ֵ������ǰʱ�䣩��Ϊ������
 */
void setRandomNumber() {
	srand((unsigned)time(NULL));
	for(int i=0; i<=1999; i++) {
		randomNumber[i]=(rand()%1230000);      //����1~1229999������
	}
	for(int j=2000; j<=2019; j++) {
		randomNumber[j]=(rand()%1230000)+1230000;
	}
}


/**��ȡuser.txt��ʹ�������ţ�ʹ��˳�����***/
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
		//��ֹ�����س���
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
	ifs.close();//�ж��Ƿ����ĩβ
	//���������
	setRandomNumber();
	//˳�����
	int currRandomNumber;
	UserNode *p=NULL;
	time_t starttime,endtime;
	cout<<"˳����ҿ�ʼ"<<endl;
	starttime=GetTickCount();
	for(int i=0; i<2020; i++) {
		p = userHead;
		currRandomNumber =randomNumber[i];
		while(p!=NULL) {
			if(p->userNode_id==currRandomNumber) {
				cout<<"�ҵ�"<<i<<":-id-"<<p->userNode_id<<"-����-"<<p->userNode_password<<endl;
				break;
			}
			p=p->nextNode;
		}
	}
	endtime = GetTickCount();
	cout<<"˳����ҽ���"<<endl;
	cout<<"��������ʱ��Ϊ��----"<<(endtime-starttime)<<"ms"<<endl;
	free(userHead);
}

/**
 *@describtion ���ֲ���
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

//��ȡuser_sorted.txt��ʹ�ö��ֲ���
void SearchUserIdFromUserSortTxtByBinSearch() {
	int userCount=ReadUserIdFormUserSortedTxt();
	//���������
	setRandomNumber();
	//���ݶ��������в���
	int currRandomNumber=0;
	time_t startTime,endTime;
	cout<<"���ֲ��ҿ�ʼ"<<endl;
	startTime=GetTickCount();
	for(int k=0; k<2020; k++) {
		currRandomNumber=randomNumber[k];
		//���ö��ֲ���
		int s = BinSearch(currRandomNumber,userCount);
		if(s!=0) {
			cout<<"�ҵ�"<<k<<":-id-"<<user[s].user_id<<"-����-"<<user[s].password<<endl;
		}
	}
	endTime = GetTickCount();
	cout<<"���ֲ��ҽ���"<<endl;
	cout<<"��������ʱ��Ϊ��"<<(endTime-startTime)<<"ms"<<endl;
}


//��ȡuser.txt�������û�idʹ�ö������������.
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
		//���뵽��Ӧ��λ��,������ұߣ�С�������
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
	//���������
	setRandomNumber();
	//���ݶ��������в���
	int currRandomNumber ;
	UserTree *p=NULL;
	time_t startTime,endTime;
	cout<<"���������ҿ�ʼ"<<endl;
	startTime=GetTickCount();;
	for(int k=0; k<2020; k++) {
		p=Root;
		currRandomNumber=randomNumber[k];
		while(p!=NULL) {
			if(p->user_id==currRandomNumber) {
				cout<<"�ҵ�"<<k<<":-id-"<<p->user_id<<"-����-"<<p->password<<endl;
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
	cout<<"���������ҽ���"<<endl;
	cout<<"��������ʱ��Ϊ��"<<(endTime-startTime)<<"ms"<<endl;
	free(Root);
}

int toHash(string key) {
	int arraySize = 11131; // �����Сһ��ȡ����
	int hashCode = 0;
	for (int i = 0; i <key.length(); i++) { // ���ַ�������߿�ʼ����
		int letterValue = key[i] - 0;// ����ȡ�����ַ���ת�������֣�����a����ֵ��97����97-96=1
		// �ʹ���a��ֵ��ͬ��b=2��
		hashCode = ((hashCode << 5) + letterValue) % 11131;// ��ֹ�����������ÿ�����������ȡģ����
	}
	return hashCode;
}

void HashTableStoragePasswordTxt() {
	//�ó�ֵ
	for(int i=0; i<11131; i++) {
		hashTable[i].firstUser=NULL;
	}
	ifstream ifs;
	ifs.open("password.txt" );
	//�û���
	int currentNumberOfLines=0;
	char ch;
	string a;
	int b;
	int adr=0;
	while(!ifs.eof()) {
		ifs>>a>>b;
		//��ֹ�����س���
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
		time_t nowTime,nextTime;//����ͳ��ʱ��
		nowTime=GetTickCount();// ��ȡ��ǰʱ��
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
		nextTime=GetTickCount();// ��ȡ��ǰʱ��
		if(q1!=NULL) {
			cout<<"�ɹ� ���� "<<q1->userNode_password<<" ���� "<<q1->userNode_password<<" �Ƚϣ�"<<temp<<" ʱ��:"<<(nextTime-nowTime)<<endl;
		} else {
			cout<<"ʧ�� ����"<<havePassword[j]<<" �Ƚϣ�"<<temp<<" ʱ��:"<<(nextTime-nowTime)<<endl;
		}
	}
}

int main() {
	int  flag=0;
	do {
		cout<<"���������� :"<<endl;
		cout<<"1 ��ȡuser.txtд��password�� 2 ��ȡpassword.txt ��7���㷨���� 3 ��ȡuser.txt������˳�����2020��id��"<<endl;
		cout<<"4 ��ȡuser.txt������������Ų���2020��id�� 5 ��ȡuser.txt ����7���㷨����ʱ�䣻 6 ���ֲ���id��"<<endl;
		cout<<"7 ��˳���+�����ϣ�洢password.txt"<<endl;
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
		cout<<"0 �˳� 1 ����"<<endl;
		cin>>flag;
	} while(flag==1);
	return 0; 
}



