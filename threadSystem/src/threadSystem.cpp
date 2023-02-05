#include <threadSystem/threadSystem.hpp>

using namespace dataObject;
using namespace threadSystem;

Thread::Thread()
{
    _init();
}

Thread::~Thread()
{
    _kill();
}

bool Thread::isAlive() const
{
    if (thread_status == RUNNING)
    {
        return true;
    }
    return false;
}

void Thread::start()
{
    if (thread_status == INIT)
    {
        thread_status = ACTIVE;
    }
}

void Thread::join()
{
    if (thread != NULL)
    {
        switch (thread_status)
        {
        case INIT:
            _kill();
            break;
        case ACTIVE:
        case RUNNING:
            if (thread->joinable())
            {
                thread->join();
            }
            break;
        case DEACTIVE:
            break;
        }
    }
}

/////////////////////////////////////////
/// 継承した関数
/////////////////////////////////////////
int Thread::getSize() const
{
    if (this->isAlive())
    {
        return 1;
    }
    return 0;
}
const char *Thread::getLog() const
{
    String ret = "";
    switch (thread_status)
    {
    case NOTSET:
        ret = "NOTSET";
        break;
    case INIT:
        ret = "INIT";
        break;
    case ACTIVE:
        ret = "ACTIVE";
        break;
    case RUNNING:
        ret = "RUNNING";
        break;
    case DEACTIVE:
        ret = "DEACTIVE";
        break;
    }

    return ret.getChar();
}

/////////////////////////////////////////
/// private関数
/////////////////////////////////////////

void Thread::_init()
{
    thread_status = NOTSET;
    thread = NULL;
}

void Thread::_kill()
{
    if (thread != NULL)
    {
        thread_status = DEACTIVE;
        if (thread->joinable())
        {
            thread->join();
        }

        delete thread;
        thread = NULL;
    }
    thread_status = NOTSET;
}