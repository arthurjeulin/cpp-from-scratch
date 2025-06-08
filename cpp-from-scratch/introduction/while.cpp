#include <iostream>

int main()
{
  int work_items = 10;
  while(work_items > 0)
  {
    std::cout << "Work items:" << work_items << "\n";
    --work_items;
  }

  do
  {
    ++work_items;
    std::cout << "Work items:" << work_items << "\n";
  }
  while (work_items < 10);
  

  return 0;
}