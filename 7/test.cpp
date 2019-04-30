#include <condition_variable>
#include <iostream>
#include <thread>

bool dataReady= false;                    

std::mutex mutex_;
std::condition_variable condVar1;
std::condition_variable condVar2;

const size_t COUNTLIMIT = 500000;

void ping(){                                          

 for (size_t i = 0; i < COUNTLIMIT; i++) {              
    std::unique_lock<std::mutex> lock(mutex_);
    condVar1.wait(lock, []{return dataReady == false;});
   // condVar1.wait (lck);
    dataReady= true;                          
    //std::cout << "ping" << std::endl;
    printf ("ping\n");
    condVar2.notify_one();                              

  }
}

void pong(){                                           

  for (size_t i = 0; i < COUNTLIMIT; i++) {                            
    std::unique_lock<std::mutex> lck(mutex_);
    condVar2.wait(lck, []{return dataReady == true;});
    //condVar2.wait (lck);
    dataReady= false;
    //std::cout << "pong" << std::endl;
    printf ("pong\n");
    condVar1.notify_one();
  }

}

int main(){

  //std::cout << std::boolalpha << std::endl;

  std::thread t1(ping);
  std::thread t2(pong);

  t1.join();
  t2.join();
  
  dataReady= false;
    
}
