#include <iostream>

using namespace std;

int iterateBit(int n, const string s) {
	int const_n = 5;
	
	if (n <= 0) {
		cout << s << endl;
		return 0;
	}
	else {
		string s2 = s + "0";
		iterateBit(n-1, s2);
		string s3 = s + "1";
		iterateBit(n-1, s3);
	}
	return 0;

}

int main() {

  // ��� �κ� ����;

  // array to map value for the sets

  // 8�� �� 2�� ��� ��
  	{
	  int n = 8;
	  int k = 2;
	  int sum1 = 1;
	  for (int i = 1; i <= k; i++) {
	    sum1 *= n--;
	  }
	  cout << "select with order: " << sum1 << endl;
  	}
  // 8 * 7 , 8 * 7 
  	{
	  int const_n = 8;
	  int const_k = 3;
	  int n = const_n;
	  int k = const_k;
	  int sum1 = 1;
	  int sum2 = 1;
	  for (int i = 1; i <= const_k; i++) {
	    sum1 *= n--;
	  }
	  for (int i = 1; i <= const_k; i++) {
	  	sum2 *= k--;
	  }
	  cout << "select with no order: " << sum1 / sum2 << endl;
  	}
  

  // 10 �� ȸ�� ��ȸ��
    	{
	  int const_n = 10;
	  int const_k = 2;
	  int n = const_n;
	  int k = const_k;

	  int sum1 = 1;
	  for (int i = 1; i <= const_k; i++) {
	    sum1 *= n--;
	  }
	  cout << "main, sub out of 10: " << sum1 << endl;
  	}

  // 10 �� A, B ������ ���
  {
	  int const_n = 10;
	  int const_k = 5;
	  int n = const_n;
	  int k = const_k;

	int sum1 = 1;
	int sum2 = 1;
	for (int i = 1; i <= const_k; i++) {
	  sum1 *= n--;
	}
	for (int i = 1; i <= const_k; i++) {
	  sum2 *= k--;
	}
	cout << "5 : 5 = " << sum1 << " " << sum2 << " "<< sum1 / sum2 << endl;
  }

  // 0 1 �� ����� ��� ����
  iterateBit(3, "");

  // with given n and k, from 0,1,..,n-1 select k (combination with repeatition)

  // with given n and k, from 0,1,..,n-1 select k (permutation with repeatition)

  // all pairs of ( ) 

  // �ڿ��� �Է� �޾Ƽ� n �޾Ƽ� {0,1,2...n-1} ������ ����� ��� ����϶�

  return 0;
}

