#include <fileSystem/fileSystem.hpp>

using namespace dataObject;
using namespace fileSystem;

/// @brief コンストラクタ
FileExplorer::FileExplorer()
{
    _init();
}

FileExplorer::FileExplorer(const String &path)
{
    _init();
    _dir = new File(path.getChar());
    _searchDir();
}
/// @brief コンストラクタ
/// @param path パス
FileExplorer::FileExplorer(const char *path)
{
    _init();
    _dir = new File(path);
    _searchDir();
}

FileExplorer::~FileExplorer()
{
    if (_dir != NULL)
    {
        delete _dir;
    }
    if (_file_list != NULL)
    {
        delete _file_list;
    }
}

List<File> FileExplorer::getDirList()
{
    List<File> ret;

    // ポインタに実体があるとき
    if (_file_list != NULL)
    {
        for (int i = 0; i < _file_list->getSize(); i++)
        {
            if (_file_list->get(i).isdir())
            {
                ret.append(_file_list->get(i));
            }
        }
    }

    return ret;
}

/// @brief ファイルリストの取得
/// @return List<File> ファイルリスト
List<File> FileExplorer::getFileList()
{
    List<File> ret;

    // ポインタに実体があるとき
    if (_file_list != NULL)
    {
        ret = *_file_list;
    }

    return ret;
}

/// @brief 指定した拡張子のファイルリストの取得
/// @param extension 拡張子
/// @return List<File> ファイルリスト
List<File> FileExplorer::getFileList(const char *extension)
{
    return getFileList(String(extension));
}

List<File> FileExplorer::getFileList(const dataObject::String extension)
{
    List<File> ret;

    // ポインタに実体がないとき
    if (_file_list != NULL)
    {
        for (int i = 0; i < _file_list->getSize(); i++)
        {
            if (_file_list->get(i).getExtension() == extension)
            {
                ret.append(_file_list->get(i));
            }
        }
    }
    return ret;
}

const char *FileExplorer::getLog() const
{
    if (_file_list != NULL)
    {
        return _file_list->getLog();
    }
    else
    {
        return "None";
    }
}

int FileExplorer::getSize() const
{
    if (_file_list != NULL)
    {
        return _file_list->getSize();
    }
    else
    {
        return 0;
    }
}

FileExplorer &FileExplorer::operator=(const String &path)
{
    setPath(path);
    return *this;
}
/// @brief 代入演算子
/// @param path パス
FileExplorer &FileExplorer::operator=(const char *path)
{
    setPath(path);
    return *this;
}
void FileExplorer::setPath(const String &path)
{
    // ディレクトリの取得
    if (_dir == NULL)
    {
        _dir = new File(path.getChar());
    }
    else
    {
        *_dir = File(path.getChar());
    }

    _searchDir();
}
/// @brief ディレクトリへのパス
/// @param path パス
void FileExplorer::setPath(const char *path)
{
    // ディレクトリの取得
    if (_dir == NULL)
    {
        _dir = new File(path);
    }
    else
    {
        *_dir = File(path);
    }

    _searchDir();
}

/////////////////////////////////////////////////
//
// private
//
/////////////////////////////////////////////////

void FileExplorer::_init()
{
    _dir = NULL;
    _file_list = NULL;

    printf("廃止予定のクラスです\n");
}

int FileExplorer::_searchDir()
{
    // ディレクトリ判定
    if (!_dir->isdir())
    {
        printf("[ERROR] ディレクトリではありません!\n");
        return -1;
    }

    // ファイルのリストを初期化
    if (_file_list == NULL)
    {
        _file_list = new List<File>();
    }
    else
    {
        _file_list->clear();
    }

    DIR *dir;
    dirent *dp;

    if ((dir = opendir(_dir->getPath().getChar())) != NULL)
    {
        while ((dp = readdir(dir)) != NULL)
        {
            String file_path = dp->d_name;
            if (!((file_path == ".") || (file_path == "..")))
            {
                file_path = _dir->getPath() + file_path;
                _file_list->append(File(file_path));
            }
        }

        closedir(dir);
    }

    return 0;
}