#include <iostream>
using namespace std;

//more effective c++, p158
//first，这个只是一个引用计数类智能指针的模板，T需要从引用计数类继承而来
template<typename T>
class RCPtr{
public:
    RCPtr(T *realPtr = NULL) : pointee(realPtr){ init(); }
    RCPtr(const RCPtr &rhs) : pointee(rhs.pointee){ init(); }
    RCPtr& operator=(const RCPtr &rhs){
        if(pointee != rhs.pointee){
            T  *old = pointee;
            pointee = rhs.pointee;
            init();
            if(old != NULL) old->removeReference();
        }
        return *this;
    }
    ~RCPtr(){ if(pointee != NULL) pointee->removeReference(); }

    T* operator->() const{ return pointee; }
    T& operator*() const { return *pointee; }

private:
    T *pointee;//raw pointer
    void init(){
        if(pointee != NULL){
            if(!pointee->isShareable()){ pointee = new T(*pointee); }
            else{ pointee->addReference(); }
        }
    }
};

//second
//引用计数对象，管理引用数目
class RCObject{
public:
    RCObject() : refCount(0), shareable(true){ }
    RCObject(const RCObject& rhs) : refCount(0), shareable(true){ }
    RCObject& operator=(const RCObject &rhs){ return *this; }
    virtual ~RCObject() = 0;//!!pure virtual, no instantiation

    //common operations
    void addReference(){ ++refCount; }
    void removeReference(){ if(--refCount) delete this; }//销毁指针
    void markUnshareable(){ shareable = false; }
    bool isShareable() const{ return shareable; }
    bool isShared() const{ return refCount > 1; }
private:
    size_t refCount;
    bool shareable;
};

//third
class String{
public:
    String(const char *initValue = "") : value(new StringValue(initValue)){  }
    const char& operator[](int index) const { return value->data[index]; }
    char& operator[](int index) {
        if(value->isShared()){
            value = new StringValue(value->data);
        }
        value->markUnshareable();
        return value->data[index];
    }

private:
    //保存引用计数和值的对应
    struct StringValue : public RCObject{
        char *data;//数据域
        StringValue(const char *initValue){ init(initValue); }
        StringValue(const StringValue &rhs){ init(rhs.data); }
        ~StringValue(){ delete[] data; }
        void init(const char *initValue){
            data = new char[strlen(initValue) + 1];
            strcpy(data, initValue);
        }
    };
    RCPtr<StringValue> value;
};

//首先引用计数不应该在类中，因为每个string的值对应一个引用计数，而不是每个string对象。
//本质上而言，两个大块，第一块就是 RCPtr这个智能指针的模板类，T类型要求是RCObject的子类， StringValue类本质上就是含有RCObject这个subobject的类型。
//只是将引用计数操作交给父类去做了，自己只用管理data相关的事务，

int main(){
    return 0;
}
