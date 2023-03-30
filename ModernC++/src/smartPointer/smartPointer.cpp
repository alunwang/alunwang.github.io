// Author: Huahua
// Demostrate smart pointer:
// 1. Ownership
// 2. Life cycle
// 3. Preferred way to define a smart pointer
// 4. Preferred way to pass a smart pointer in function

#include <iostream>
#include <memory>
 
class Entity {
public:
  Entity() { puts("Entity created!"); }
  ~Entity() { puts("Entity destroyed!"); }
};

/*
 * 1. Preferred way to define a unique_ptr smart pointer
 *    auto e1 = std::make_unique<Entity>();
 * 2. e1 is living in its scope, outside its scope, it is released.
 */
void ex1()
{
  puts("--------");
  puts("Entering ex1");
  { // Define a scope and limit e1's life to this scope
    puts("Entering ex1::scope1");
    auto e1 = std::make_unique<Entity>();    
    puts("Leaving ex1::scope1");
  }
  puts("Leaving ex1");
}
 
void foo(std::unique_ptr<Entity>)
{
  puts("Entering foo");
  puts("Leaving foo");
}

/*
 * 1. Use move() to pass unique_ptr because it is single ownership
 */
void ex2()
{
  puts("--------");
  puts("Entering ex2");
  auto e1 = std::make_unique<Entity>();  
  foo(std::move(e1)); // Use move() to transfer the ownership because it is single ownership
  // e1 was destoried.
  puts("Leaving ex2");
}

/*
 * 1. Preferred way to define a shared_ptr smart pointer
 *    auto e1 = std::make_shared<Entity>();
 * 2. Use e1.use_count() to check its reference count
 * 3. Can be assigned, its reference count increases.
 * 4. Its ownership can be transferred with move(), its reference count remains the same.
 */
void ex3()
{
  puts("--------");
  puts("Entering ex3");
  auto e1 = std::make_shared<Entity>();
  std::cout << e1.use_count() << std::endl;
  {
    puts("Entering ex3::scope1");
    auto e2 = e1; // use_count ++
    std::cout << e1.use_count() << std::endl;
    auto e3 = std::move(e2); // use_count remains
    std::cout << e1.use_count() << std::endl;
    puts("Leaving ex3::scope1");
  }
  std::cout << e1.use_count() << std::endl;
  puts("Leaving ex3");
}


void observe(std::weak_ptr<Entity> ew)
{
  if (std::shared_ptr<Entity> spt = ew.lock()) {
    std::cout << spt.use_count() << std::endl;
    std::cout << "entity still alive!" << std::endl;
  } else {
    std::cout << "entity was expired :(" << std::endl;
  }
}
 
void ex4()
{
  puts("--------");
  puts("Entering ex4");
  std::weak_ptr<Entity> ew;  
  {
    puts("Entering ex4::scope1");
    auto e1 = std::make_shared<Entity>();
    std::cout << e1.use_count() << std::endl;
    ew = e1; // use_count remains
    std::cout << e1.use_count() << std::endl;
    observe(ew);
    puts("Leaving ex4::scope1");
  }
  observe(ew);
  puts("Leaving ex4");
}

int main(int argc, char** argv)
{
  ex1();
  ex2();
  ex3();
  ex4();
  return 0;
}