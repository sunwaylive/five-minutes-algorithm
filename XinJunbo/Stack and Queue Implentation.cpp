//Author: Xin Junbo
//Date:  2014/09/03

#include<iostream>
#include<stack>
#include<queue>
using namespace std;
const int max_size = 100;

//***********************Implentation of Queue using array****************************
template<class T>
class CQueue{
public:
	   CQueue();
	   ~CQueue() {delete[] m_queue;}
	   bool pushQ(const T& data);
	   T frontQ() const;
	   void popQ();
	   bool isEmptyQ() const{return m_length==0; }
	   int Qsize() const{return m_length ;}
private:
	  int m_front, m_rear;
	  int m_length;
	  T* m_queue;
};

//CQueue  constructor
template<class T>
CQueue<T>::CQueue(){
	 m_queue = new T[max_size];
	 m_length = 0;
	 m_front = 0;
	 m_rear = -1;
}

//insert a node in the head of CQueue
template<class T>
bool CQueue<T>::pushQ(const T& data){
	if(Qsize() == max_size) return false;
	m_queue[++m_rear] = data;
	m_length++;
	return true;
}
//return the head element of the CQueue
template<class T>
T CQueue<T>::frontQ() const{
	if( isEmptyQ() )
		return INT_MIN;
	else
		return m_queue[m_front];
}
// pop out the first element of the CQueue
template<class T>
void CQueue<T>::popQ(){
	  if(!isEmptyQ()){
		m_front++;
		m_length--;
	  }
}

//**************Impletation of queue using Linklist*************************
template<class T> class CLinkQueue;
template<class T>
class Linklist{
	friend class CLinkQueue<T>;
private:
	Linklist<T>(const T &x): value(x), next(NULL){}
	T value;
	Linklist<T> *next;
};

template<class T>
class CLinkQueue{
public:
	CLinkQueue(): head(NULL), tail(NULL), m_len(0){}
	~CLinkQueue();
	bool pushLQ(const T& data);
	void popLQ();
	T frontLQ() const ;
	bool isEmptyLQ() const {return  m_len==0;}
	int sizeLQ() const {return m_len;}
private:
    Linklist<T> *head;
	Linklist<T> *tail;
	int m_len;
};

template<class T>
CLinkQueue<T>:: ~CLinkQueue(){
	  while(!isEmptyLQ())
		  popLQ();
}

template<class T>
bool CLinkQueue<T>:: pushLQ(const T& data){
	Linklist<T>* node = new Linklist<T>(data);
	if(m_len == max_size - 1) return false;
	if(isEmptyLQ())
		head = tail = node;
	else{
		tail -> next = node;
		tail = tail -> next;  //insert node at the end o the list
	}
	   m_len ++;
       return true;
}

template<class T>
void CLinkQueue<T>:: popLQ(){
	 if( isEmptyLQ() )  return;
		Linklist<T> *temp = head;
		 head = head -> next;
		 m_len -- ;
		 delete temp;
}

template<class T>
T CLinkQueue<T>::frontLQ() const{
	  if( isEmptyLQ()) 
		  return INT_MIN;
	  else
		  return head -> value;
}

//**********************Implentation of a CircularQueue using array********************
template<class T>
class CircularQueue{
public:
	  CircularQueue(int len);
	  ~CircularQueue(){delete[] cq_array;}
	  bool pushCQ(const T& data);
	  void popCQ();
	  T frontCQ() const;
	  bool isEmptyCQ() const{return cq_size == 0;}
	  int getLenCQ() const{return cq_size;}
private:
	int cq_front, cq_rear;
	int cq_totalLen;
	int cq_size;
	T* cq_array;
};

template<class T>
CircularQueue<T>::CircularQueue(int len){
	cq_totalLen = len;
	cq_array = new T[cq_totalLen];
	cq_front = 0;
	cq_rear = -1;
	cq_size = 0;
}

template<class T>
bool CircularQueue<T>::pushCQ(const T& data){
	if(getLenCQ() == cq_totalLen) return false;
	cq_rear = (cq_rear +1)%cq_totalLen;
	cq_array[cq_rear] = data;
	cq_size++;
	return true;
}

template<class T>
void CircularQueue<T>::popCQ(){
	if( isEmptyCQ() ) return;
	cq_front = (cq_front+1) % cq_totalLen;
	cq_size--;
}

template<class T>
T CircularQueue<T>::frontCQ() const{
	  if( isEmptyCQ())
		  return INT_MIN;
	  else
		  return cq_array[cq_front];  
}
	  
//*********************Implentation of a stack using array*********************
template<class T>
class CStack{
public:
	  CStack();
	  ~CStack(){delete[] s_array;}
	  bool pushS(const T& data);
	  void popS();
	  T topS() const;
	  bool isEmptyS() const{return s_size==0;};
	  size_t Qsize() const{return s_size;}
private:
	  int s_top,  s_size;
	  T* s_array;
};

template<class T>
CStack<T>::CStack(){
	s_array = new T[max_size];
	s_top = -1;
	s_size = 0;
}

template<class T>
bool CStack<T>::pushS(const T& data){
	if(s_size == max_size) return false;
	  s_array[++s_top] = data;
      s_size++;
	  return true;
}

template<class T>
void CStack<T>::popS(){
	if( isEmptyS()) return;
	s_top--;
	s_size--;
}

template<class T>
T CStack<T>::topS() const{
	if( isEmptyS())
		return INT_MIN;
	else
		return s_array[s_top];

}

//********************Implentation of stack using Linklist**********************
template<class T> class CLinkStack;
template<class T>
class ListNode{
	friend class CLinkStack<T>;
private:
	  T value;
	  ListNode* next;
	  ListNode(int data): value(data),  next(NULL){}
};

template<class T>
class CLinkStack{
public:
	CLinkStack():head(NULL), cs_size(0){};
	~CLinkStack();
   bool pushCS(const T& data);
	void popCS();
	T topCS() const;
	bool isEmptyCS() const{return cs_size == 0;}
	int CSsize() const{ return cs_size;}
private:
	ListNode<T>* head;
	size_t cs_size;
};

template<class T>
CLinkStack<T>::~CLinkStack(){
	while( !isEmptyCS())
		popCS();
}

template<class T>
bool CLinkStack<T>::pushCS(const T& data){
	if(cs_size == max_size) return false;
	ListNode<T> *tempNode = new ListNode<T>(data);
	if(isEmptyCS())
		head = tempNode;
     else{
		 tempNode -> next = head;
		 head = tempNode; 
	}
	 cs_size++;
	return true;
}

template<class T>
void CLinkStack<T>::popCS(){
	if( isEmptyCS()) return;
	ListNode<T>* p = head;
	head = head -> next;
	cs_size--;
	free(p);
}

template<class T>
T CLinkStack<T>::topCS() const{
	if( isEmptyCS())
		return INT_MIN;
	else
		return head ->value;
}
	
//************************Two stack to implentate a queue********************
template<class T>
class StackToQueue{
public:
    StackToQueue(): len(0){};
	bool pushSQ(const T& data);
	void popSQ();
	T frontSQ();
	bool isEmptySQ() const {return len==0;}
	int getLenSQ() const{return len;}

private:
   stack<T> s1;   // responsible for implentating   push
   stack<T> s2;  //responsible for implentating   pop
   int len;
};

template<class T>
bool StackToQueue<T>:: pushSQ(const T& data){
	if( getLenSQ() == max_size ) return false;
	s1.push(data);
	len++;
	return true;
}

template<class T>
void StackToQueue<T>::popSQ(){
	if( !isEmptySQ()) return;
	if(! s2.empty() ) 
		s2.pop();
    else{
	while( !s1.empty()){
		   T temp = s1.top();
		   s2.push(temp);
		   s1.pop();
	    }
	     s2.pop();
	}
		   len--;
}

template<class T>
T StackToQueue<T>::frontSQ(){
	if( isEmptySQ())
		return INT_MIN;
	if( s2.empty() )
	   while(!s1.empty()){
		     T temp = s1.top();
		     s2.push(temp);
		     s1.pop();
	      }
	 return s2.top();
}

//**************Two queue to implentate a stack*************************
template<class T>
class QueueToStack{
public:
	QueueToStack():qs_size(0){};
	bool pushQS(const T& data);
	void popQS();
	T topQS();
	bool isEmptyQS() const{return qs_size==0;}
	int getLenQS() const{return qs_size;}
private:
	queue<T> q1;
	queue<T> q2;
	int qs_size;
};

template<class T>
bool QueueToStack<T>::pushQS(const T& data){
	if(getLenQS() == max_size) return false;
	if( !q1.empty()) 
		q1.push(data);
	else 
		q2.push(data);
	   qs_size++;
	   return true;
}

template<class T>
void QueueToStack<T>::popQS(){
	if( isEmptyQS() ) return;
	if( !q1.empty() ) {
		 while( q1.size() != 1){
			 T temp = q1.front();
			 q2.push(temp);
		     q1.pop();
	     }
		 q1.pop();
	}else{
		   while( q2.size() != 1){
			   T temp = q2.front();
			   q1.push(temp);
			   q2.pop();
		   }
		    q2.pop();
	}
	qs_size --;
}

template<class T>
T QueueToStack<T>::topQS(){
      if(isEmptyQS())
		  return INT_MIN;
	   T temp;
		if( !q1.empty())
			 while( !q1.empty() ){
				  temp = q1.front();
				 q2.push(temp);
				 q1.pop();
			 } 
		else 
			 while( !q2.empty() ){
				 temp = q2.front();
				 q1.push(temp);
				 q2.pop();
			 }
		 return temp;
}


int main(void)
{
	int A[] = {3,2,54,22,12,5,8,9};
	//test of class CQueue
	cout<< "**************CQueue**************" << endl;
	CQueue<int> q;
    for(int i =0; i < sizeof(A)/sizeof(int); ++i)
		q.pushQ(A[i]);
	cout << q.Qsize() << endl;
	q.popQ();
	int temp = q.frontQ();
	cout << q.Qsize() << endl;
	cout << endl;

	cout<< "**************CLinkQueue************"<<endl;
	//test of class CLinkQueue
	CLinkQueue<int> lq;
	for(int i =0 ; i< sizeof(A)/sizeof(int); ++i)
		lq.pushLQ(A[i]);
	cout << lq.sizeLQ() << endl;
	lq.popLQ();
	int temp2 = lq.frontLQ();
	cout << temp2 << endl;
	cout << lq.sizeLQ() << endl;
	bool isempty = lq.isEmptyLQ();
	cout << isempty << endl;
	cout<< endl;

	cout << "**************CircurlarQueue************"<<endl;
	//test of class CircularQueue
	CircularQueue<int> cq(9);
	for(int i =0; i < sizeof(A)/sizeof(int); ++i)
		cq.pushCQ(A[i]);
	cout << cq.getLenCQ() << endl;
	cq.popCQ();
	cq.popCQ();
	cq.popCQ();
	int tmp = cq.frontCQ();
	cout << tmp << endl;
	cq.pushCQ(124);
	cq.pushCQ(65);
	cq.pushCQ(398);
	tmp = cq.frontCQ();
	cout << tmp << endl;
	cout << cq.getLenCQ() << endl;
	cout << endl;

	cout<<"**************CStack***********" << endl;
	// test of class CStack
	CStack<int> stk;
	for(int i = 0; i < sizeof(A)/sizeof(int); ++i)
		stk.pushS(A[i]);
	cout << stk.Qsize() << endl;
	stk.popS();
	stk.popS();
	int temp3 = stk.topS();
	cout << temp3 << endl;
	bool isEmptySS = stk.isEmptyS();
	cout << isEmptySS << endl;
	cout << stk.Qsize() << endl;
	cout << endl;

	cout<<"************CLinkStack***********"<<endl;
	//test of class CLinkStack
	CLinkStack<int> cstk;
	for(int i = 0; i < sizeof(A)/sizeof(int); ++i)
		cstk.pushCS(A[i]);
	cout << cstk.CSsize() << endl;
	cstk.popCS();
	cstk.popCS();
	cstk.popCS();
	int temp4 = cstk.topCS();
	cout << temp4 << endl;
	bool isEmptyCS = cstk.isEmptyCS();
	cout << isEmptyCS << endl;
	cout << cstk.CSsize() << endl;
	cout << endl;

	cout << "*************StackToQueue**************" << endl;
	//test of class StackToQueue
	StackToQueue<int> sToq;
	for(int i = 0; i < sizeof(A)/sizeof(int); ++i)
		sToq.pushSQ(A[i]);
	cout << sToq.getLenSQ() << endl;
	sToq.popSQ();
	sToq.popSQ();
	int topNum = sToq.frontSQ();
	cout << topNum << endl;
	cout << sToq.getLenSQ() << endl;
	cout << endl;

	cout<<"*****************QueueToStack*************"<<endl;
	//test o class QueueToStack
	QueueToStack<int> qTos;
	for(int i = 0; i < sizeof(A)/sizeof(int); ++i)
		qTos.pushQS(A[i]);
	cout << qTos.getLenQS() << endl;
	qTos.popQS();
	qTos.popQS();
	qTos.pushQS(111);
	int frontNum = qTos.topQS();
	cout << frontNum << endl;
	cout << qTos.getLenQS() << endl;

	getchar();
	return 0;
}

