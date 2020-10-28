/*
    A smart pointer is a class template declared on the stack and initialized
    by using a raw pointer that points to a heap-allocated object. When the
    smart pointer is initialized, it owns the raw pointer.

    Since the smart pointer is declared on the stack, its destructor is called
    when it goes out of scope.

    std::unique_ptr
        A wrapper around a raw pointer which will automatically delete the heap
        object when it goes out of scope itself. Cannot be copied.
*/

#include <iostream>
#include <memory>

class someObject
{
public:
    void someMethod()
    {
        std::cout << "Method called using smart pointer." << "\n\n";
    }
};

void smartPointer()
{
    // Pass the object to the smart pointer.
    std::unique_ptr<someObject> sObj(new someObject());

    // Call the method through the smart pointer.
    sObj->someMethod();
}

// Using a smart poitner with a polymorphic class
class aPolyClass
{
public:
    virtual void printMessage()
    {
        std::cout << "printMessage() defined in aPolyClass." << "\n\n";
    }
};

class aDerivedClass : public aPolyClass
{
public:
    void printmessage()
    {
        std::cout << "printMessage defined in aDerivedClass." << "\n\n";
    }
};

// Move types specified as &&
void acceptParameter(std::unique_ptr<int>&& ptr)
{
    *ptr += 10;
    std::cout << "Smart pointer parameter + 10: " << *ptr << "\n\n";
}

void accPar(const std::shared_ptr<int>* ptr)
{

}

int main()
{
    // unique_ptr
    std::unique_ptr<int> p(new int{ 235 });
    std::cout << *p << "\n\n";

    // Better initialization
    std::unique_ptr<int> pp = std::make_unique<int>(711);
    std::cout << *pp << "\n\n";

    // Polymorphic class implementation
    std::unique_ptr<aPolyClass> ppp = std::make_unique<aDerivedClass>();
    ppp->printMessage();
    
    // Calling smart pointer directly
    smartPointer();

    // Shared pointers
    std::shared_ptr<int> p1 = std::make_shared<int>(1317);
    std::shared_ptr<int> p2 = p1;
    std::shared_ptr<int> p3 = p2;
    std::cout << *p3 << "\n\n";

    // Passing a unique smart pointer as a parameter
    // unique_ptr cannot be copied, so use move.
    auto ptrBar = std::make_unique<int>(1719);
    acceptParameter(std::move(ptrBar));
    std::cout << "ptrBar: " << *ptrBar << "\n\n";

}
