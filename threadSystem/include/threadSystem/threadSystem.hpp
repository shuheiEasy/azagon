#ifndef COMMON_THREADSYSTEM_H
#define COMMON_THREADSYSTEM_H

#include <dataObject/dataObject.hpp>
#include <thread>

/// @brief スレッドライブラリ
namespace threadSystem
{
    /// @brief スレッドクラス
    class Thread : public dataObject::DataObject
    {
    private:
        /// @brief スレッドの状態を示す列挙体
        enum ThreadStatus
        {
            NOTSET,
            INIT,
            ACTIVE,
            RUNNING,
            DEACTIVE
        };
        /// @brief 制御用スレッド
        std::thread *thread;
        /// @brief スレッドの状態
        ThreadStatus thread_status;
        /// @brief 初期化関数
        void _init();
        /// @brief スレッドの削除関数
        void _kill();
        /// @brief 実行関数
        /// @tparam F 関数ポインタの型
        /// @tparam ...Args 引数の型
        /// @param f 関数ポインタ
        /// @param ...args 可変引数
        template <class F, class... Args>
        void _run(F &&f, Args... args);

    public:
        /// @brief コンストラクタ
        Thread();
        /// @brief コンストラクタ
        /// @tparam F 関数ポインタの型
        /// @tparam ...Args 引数の型
        /// @param f 関数ポインタ
        /// @param ...args 可変引数
        template <class F, class... Args>
        Thread(F f, Args... args);
        /// @brief デストラクタ
        ~Thread();
        /// @brief スレッドが稼働中か判定
        /// @return 稼働しているならTrueを返す
        bool isAlive() const;
        /// @brief スレッドの終了まで待機
        void join();
        /// @brief 実行する関数の設定
        /// @tparam F 関数ポインタの型
        /// @tparam ...Args 引数の型
        /// @param f 関数ポインタ
        /// @param ...args 可変引数
        template <class F, class... Args>
        void setTarget(F f, Args... args);
        /// @brief スレッドの開始
        void start();

        /////////////////////////////////////////
        /// 継承した関数
        /////////////////////////////////////////
        const char *getType() const { return "Thread"; }
        int getSize() const;
        const char *getLog() const;
    };

    /////////////////////////////////////////////////
    /// テンプレートの実装部分
    /////////////////////////////////////////////////
    template <class F, class... Args>
    Thread::Thread(F f, Args... args)
    {
        _init();
        setTarget(f, args...);
    }

    template <class F, class... Args>
    void Thread::setTarget(F f, Args... args)
    {
        _kill();
        thread_status = INIT;
        thread = new std::thread(&Thread::_run<F, Args...>, this, f, args...);
    }

    template <class F, class... Args>
    void Thread::_run(F &&f, Args... args)
    {
        while (thread_status == INIT)
        {
        }
        if (thread_status == ACTIVE)
        {
            std::thread th(f, args...);
            thread_status = RUNNING;
            th.join();
            thread_status = DEACTIVE;
        }
    }

}
#endif