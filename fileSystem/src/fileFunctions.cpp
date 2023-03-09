#include <fileSystem/fileSystem.hpp>

using namespace dataObject;
using namespace fileSystem;

String fileSystem::getAbsolutePath(String &path)
{
    // 絶対パスか判定
    if (path[0] == "/")
    {
        // 絶対パスなので返り値に直接設定
        return path;
    }

    // 相対パスから変換
    char *current_dir_path = NULL;
    String current_path;
    current_dir_path = getcwd(NULL, 360);

    if (current_dir_path == NULL)
    {
        printf("カレントディレクトリの取得に失敗しました!\n");
        String ret = "";
        return ret;
    }
    else
    {
        current_path = current_dir_path;
    }

    // カレントパスのリスト
    List<String> ret_path_list;
    // 絶対パスを生成するためのリスト
    List<String> input_path_list;

    // リスト化
    if (OSTYPE == "LINUX")
    {
        ret_path_list = current_path.split("/");
        ret_path_list.del(0);
        input_path_list = path.split("/");
    }
    else if (OSTYPE == "WINDOWS")
    {
        ret_path_list = current_path.split("\\");
        input_path_list = path.split("\\");
    }
    else
    {
        printf("未対応OSです!\n");
        exit(1);
    }

    // パスのリスト生成
    for (int i = 0; i < input_path_list.getSize(); i++)
    {
        if (input_path_list[i] == ".")
        {
            continue;
        }
        else if (input_path_list[i] == "..")
        {
            ret_path_list.del(-1);
        }
        else
        {
            ret_path_list.append(input_path_list[i]);
        }
    }

    // パス生成
    String ret = "";
    String path_separator;
    if (OSTYPE == "LINUX")
    {
        path_separator = "/";
    }
    else
    {
        path_separator = "\\";
    }

    for (int i = 0; i < ret_path_list.getSize(); i++)
    {
        if (OSTYPE == "LINUX")
        {
            ret += path_separator + ret_path_list[i];
        }
        else
        {
            ret += path_separator + ret_path_list[i];
        }
    }

    return ret;
}

dataObject::String fileSystem::getCurrentDir(const int size)
{
    char buf[size];
    getcwd(buf, size);
    return String(buf);
}

dataObject::List<File> fileSystem::getDirList(const char *path) { return getDirList(File(path)); }

dataObject::List<File> fileSystem::getDirList(const dataObject::String &path) { return getDirList(File(path)); }

dataObject::List<File> fileSystem::getDirList(const File &dir)
{
    // 戻り値
    List<File> ret;

    // ファイルリスト取得
    auto file_list = getFileList(dir);

    // ディレクトリのみ取得
    for (int i = 0; i < file_list.getSize(); i++)
    {
        if (file_list[i].isdir())
        {
            ret.append(file_list[i]);
        }
    }

    return ret;
}

dataObject::List<File> fileSystem::getFileList(const char *path) { return getFileList(File(path)); }
dataObject::List<File> fileSystem::getFileList(const char *path, const char *extension) { return getFileList(File(path), String(extension)); }
dataObject::List<File> fileSystem::getFileList(const char *path, const dataObject::String &extension) { return getFileList(File(path), extension); }

dataObject::List<File> fileSystem::getFileList(const dataObject::String &path) { return getFileList(File(path)); }
dataObject::List<File> fileSystem::getFileList(const dataObject::String &path, const char *extension) { return getFileList(File(path), String(extension)); }
dataObject::List<File> fileSystem::getFileList(const dataObject::String &path, const dataObject::String &extension) { return getFileList(File(path), extension); }

dataObject::List<File> fileSystem::getFileList(const File &dir)
{
    List<File> ret;

    // 存在判定
    if (!dir.exists())
    {
        printf("[ERROR] ファイルがありません!\n");
        return ret;
    }

    // ディレクトリ判定
    if (!dir.isdir())
    {
        printf("[ERROR] ディレクトリではありません!\n");
        return ret;
    }

    DIR *dir_ptr;
    dirent *dp;

    if ((dir_ptr = opendir(dir.getPath().getChar())) != NULL)
    {
        while ((dp = readdir(dir_ptr)) != NULL)
        {
            String file_path = dp->d_name;
            if (!((file_path == ".") || (file_path == "..")))
            {
                file_path = dir.getPath() + file_path;
                ret.append(File(file_path));
            }
        }

        closedir(dir_ptr);
    }

    return ret;
}

dataObject::List<File> fileSystem::getFileList(const File &dir, const char *extension)
{
    return getFileList(dir, String(extension));
}

dataObject::List<File> fileSystem::getFileList(const File &dir, const dataObject::String &extension)
{
    // 戻り値
    List<File> ret;

    // ファイルリスト取得
    auto file_list = getFileList(dir);

    // ディレクトリのみ取得
    for (int i = 0; i < file_list.getSize(); i++)
    {
        if (file_list[i].getExtension() == extension)
        {
            ret.append(file_list[i]);
        }
    }

    return ret;
}

List<String> fileSystem::getPathList(String &path)
{
    List<String> ret;
    String path_separator;

    // パス区切り文字
    if (OSTYPE == "LINUX")
    {
        path_separator = "/";
    }
    else if (OSTYPE == "WINDOWS")
    {
        path_separator = "\\";
    }
    else
    {
        path_separator = "/";
    }

    // パス分割
    ret = path.split(path_separator);

    return ret;
}

dataObject::Int fileSystem::moveCurrentDir(const dataObject::String &path)
{
    Int ret = -2;

    // ディレクトリ判定
    File dir(path);
    if (!dir.isdir())
    {
        ret = -1;
    }
    else
    {
        // カレントディレクトリ移動
        if (chdir(dir.getPath().c_str()) == 0)
        {
            ret = 0;
        }
        else
        {
            ret = -2;
        }
    }

    return ret;
}