#pragma once
#include "RestThread.h"
#include <dz1_task.h>
#include <atomic>
#include <condition_variable>
#include <deque>
#include <fstream>
#include <mutex>

namespace g4kafka {
// Keep bulky notifications off the host task's socket-completion queue.
// Only one host notification is pending at a time; the protocol worker never
// waits for presentation. Host handlers clone their arguments before returning.
class NotificationQueue {
    struct Entry {unsigned type,index;std::shared_ptr<void> value;};
    void *host_=nullptr;std::atomic<bool> *stop_=nullptr;
    std::mutex mutex_;std::condition_variable changed_;std::deque<Entry> pending_;
    rest::ManagedThread worker_;bool closing_=false,busy_=false;
    unsigned error_=0,delivered_=0,discarded_=0,lastIndex_=0,finishedIndex_=~0u;
    void record(){std::ofstream f("kafka-delivery.json",std::ios::binary);f<<"{\"delivered\":"<<delivered_<<",\"pending\":"<<pending_.size()<<",\"discarded\":"<<discarded_<<",\"error\":"<<error_<<",\"lastIndex\":"<<lastIndex_<<"}\n";}
    void pump(){
        for(;;){Entry entry;
            {std::unique_lock<std::mutex> lock(mutex_);changed_.wait(lock,[&]{return closing_||!pending_.empty();});if(closing_)return;entry=std::move(pending_.front());pending_.pop_front();busy_=true;}
            u64_t wait=5000000;auto status=Dz1Task_call(host_,DZ1_TASK_QUEUE_NONE,entry.type,entry.value.get(),nullptr,nullptr,&wait);
            {std::lock_guard<std::mutex> lock(mutex_);busy_=false;lastIndex_=entry.index;
                if(status.code){error_=status.code;discarded_+=static_cast<unsigned>(pending_.size())+1;pending_.clear();if(stop_)stop_->store(true);}else ++delivered_;
                if(pending_.empty()||error_)record();changed_.notify_all();if(error_)return;
            }
        }
    }
public:
    ~NotificationQueue(){close();}
    void start(void *host,std::atomic<bool> &stop){host_=host;stop_=&stop;worker_.start([this]{pump();});}
    bool post(unsigned type,unsigned index,void *value,Dz1DelFunc deleter,bool terminal=false){
        std::shared_ptr<void> owned(value,[deleter](void *p){if(p)deleter(p);});std::lock_guard<std::mutex> lock(mutex_);
        if(closing_||error_){++discarded_;record();return false;}
        if(type==0x00f00002&&finishedIndex_==index)return true; // Late stop notice; never append after FINISH.
        if(terminal)finishedIndex_=index;
        pending_.push_back({type,index,std::move(owned)});changed_.notify_one();return true;
    }
    void flush(const std::atomic<bool> &stop){
        std::unique_lock<std::mutex> lock(mutex_);
        // Host calls STOP synchronously. Do not make that call wait on itself:
        // the notification pump drains after the STOP handler returns.
        while(!closing_&&!error_&&(!pending_.empty()||busy_)&&!stop.load())changed_.wait_for(lock,std::chrono::milliseconds(20));
    }
    bool idle(){std::lock_guard<std::mutex> lock(mutex_);return pending_.empty()&&!busy_;}
    void close(){
        {std::lock_guard<std::mutex> lock(mutex_);closing_=true;discarded_+=static_cast<unsigned>(pending_.size());pending_.clear();changed_.notify_all();}
        if(worker_.joinable())worker_.join();
    }
};
}
