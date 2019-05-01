#include <condition_variable>
#include <iostream>
#include <thread>

bool dataReady = false;                    

const size_t COUNTLIMIT = 500000;

std::condition_variable condVar1;
std::condition_variable condVar2;



void ping(std::mutex& m){                                          

 for (size_t i = 0; i < COUNTLIMIT; i++) {              
    std::unique_lock<std::mutex> lock(m);
    condVar1.wait(lock, []{return dataReady == false;});
    printf ("ping\n");
    dataReady = true;                          
    condVar2.notify_one();                              

  }
}

void pong(std::mutex& m){                                           

  for (size_t i = 0; i < COUNTLIMIT; i++) {                            
    std::unique_lock<std::mutex> lck(m);
    condVar2.wait(lck, []{return dataReady == true;});
    printf ("pong\n");
    dataReady = false;
    condVar1.notify_one();
  }

}

int main(){

  std::mutex mtx;

  std::thread t1(ping,std::ref(mtx));
  std::thread t2(pong,std::ref(mtx));

  t1.join();
  t2.join();
      
}
