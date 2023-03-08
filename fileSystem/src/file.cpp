#include <fileSystem/fileSystem.hpp>

using namespace dataObject;
using namespace fileSystem;

File::File()
{
    String buf = "";
    _init(buf);
}
File::File(const char *path)
{
    _init(String(path));
}
File::File(const String &path)
{
    _init(path);
}

File::File(const File &file)
{
    _filetype = file.getFileType();
    _filemode = CLOSEMODE;
    _path = file.getPath();
    _name = file.getName();
    _extension = file.getExtension();
    _file_ptr = NULL;
}

File::~File() { close(); }

int File::getSize() const
{
    int ret = -2;

    switch (_filetype)
    {
    case FT_Unknown:
        ret = -1;
        break;
    case FT_NoExist:
        ret = 0;
        break;
    case FT_File:
    case FT_Dir:
        ret = 1;
        break;
    default:
        break;
    }

    return ret;
}

/////////////////////////////////////////////////
//
// public 独自メンバ関数
//
/////////////////////////////////////////////////

// ファイル閉じる
void File::close()
{
    if (_file_ptr != NULL)
    {
        fclose(_file_ptr);
    }
    _file_ptr = NULL;
    _filemode = CLOSEMODE;
}

// ファイルの存在確認
Bool File::exists() const
{
    Bool ret = false;
    switch (_filetype)
    {
    case FT_File:
    case FT_Dir:
        ret = true;
        break;
    }
    return ret;
}

// 拡張子取得
String File::getExtension() const
{
    return _extension;
}

// ファイルポインター
FILE *File::getFilePtr()
{
    return _file_ptr;
}

// ファイル形式取得
FileType File::getFileType() const
{
    return _filetype;
}

// 名前取得
String File::getName() const
{
    return _name;
}

// 名前取得
String File::getPath() const
{
    return _path;
}

// ディレクトリ判定
Bool File::isdir() const
{
    Bool ret = false;
    if (_filetype == FT_Dir)
    {
        ret = true;
    }
    return ret;
}

// ファイル判定
Bool File::isfile() const
{
    Bool ret = false;
    if (_filetype == FT_File)
    {
        ret = true;
    }
    return ret;
}

// ディレクトリ作成
Bool File::mkdir()
{

    // パス設定
    _setDirPath();

    // ディレクトリ作成
    if ((_filetype == FT_NoExist) || (_filetype == FT_File))
    {
        if (::mkdir(_path.getChar(), 0777) == 0)
        {
            _filetype = FT_Dir;
        }
        else
        {
            printf("ディレクトリの作成に失敗しました\n");
            _filetype = FT_Unknown;
        }
    }
    else
    {
        if (_filetype == FT_Dir)
        {
            printf("ディレクトリが存在していたので作成しません\n");
        }
        else
        {
            printf("ディレクトリの作成はできません\n");
        }
    }

    // 戻り値
    Bool ret = false;
    if (_filetype == FT_Dir)
    {
        ret = true;
    }
    return ret;
}

Bool File::mkfile()
{
    // 拡張子設定
    _setExtension();

    // ファイル作成
    FILE *fp = NULL;

    switch (_filetype)
    {
    case FT_NoExist:
    case FT_Dir:
        if (((fp = fopen(_path.getChar(), "w")) != NULL))
        {
            fclose(fp);
            _filetype = FT_File;
        }
        else
        {
            printf("ファイルの作成に失敗しました\n");
            _filetype = FT_Unknown;
        }
        break;
    case FT_File:
        printf("ファイルが存在していたので作成しません\n");
        break;
    default:
        printf("ファイルが作成できません\n");
        break;
    }

    // 戻り値
    Bool ret = false;
    if (_filetype == FT_File)
    {
        ret = true;
    }
    return ret;
}

Bool File::open(FileMode mode)
{
    Bool ret;
    switch (mode)
    {
    case READMODE:
        ret = open("r");
        _filemode = READMODE;
        break;
    case WRITEMODE:
        ret = open("w");
        _filemode = WRITEMODE;
        break;
    case APPENDMODE:
        ret = open("a");
        _filemode = APPENDMODE;
        break;
    }
    return ret;
}

Bool File::open(const char *mode)
{
    close();
    _file_ptr = fopen(_path.getChar(), mode);

    Bool ret = false;
    if (_file_ptr != NULL)
    {
        ret = true;
        _filemode = UNKNOWNMODE;
    }
    return ret;
}

Bool File::remove(const bool force_mode)
{
    Bool ret = false;
    if (_filetype == FT_File)
    {
        if (unlink(_path.getChar()) == 0)
        {
            ret = true;
        }
    }
    else if (_filetype == FT_Dir)
    {
        Bool remove_flag = false;
        if (force_mode)
        {
            auto file_list = getFileList(_path);
            for (int i = 0; i < file_list.getSize(); i++)
            {
                remove_flag = file_list[i].remove(force_mode);
                if (!remove_flag)
                {
                    break;
                }
            }
        }
        else
        {
            remove_flag = true;
        }

        if (remove_flag)
        {
            if (rmdir(_path.getChar()) == 0)
            {
                ret = true;
            }
        }
    }

    return ret;
}

Bool File::touch()
{
    return mkfile();
}

/////////////////////////////////////////////////
//
// private
//
/////////////////////////////////////////////////

void File::_init(String path)
{
    // 絶対パス取得
    _path = getAbsolutePath(path);

    // 名前取得
    _setName();

    // 拡張子設定
    _extension = "";

    // ファイルポインター
    _file_ptr = NULL;

    // ファイルモード取得
    _filemode = CLOSEMODE;

    // フォルダ・ファイルの存在判定
    struct stat stat_buffer;
    if (stat(_path.getChar(), &stat_buffer) == 0)
    {
        // フォルダ・ファイル判定
        if (S_ISREG(stat_buffer.st_mode))
        {
            _filetype = FT_File;
        }
        else if (S_ISDIR(stat_buffer.st_mode))
        {
            _filetype = FT_Dir;
        }
        else
        {
            _filetype = FT_Unknown;
        }

        // フォルダ
        if (_filetype == FT_Dir)
        {
            _setDirPath();
        }
        // ファイル
        else if (_filetype == FT_File)
        {
            _setExtension();
        }
    }
    else
    {
        _filetype = FT_NoExist;
    }
}

void File::_setDirPath()
{
    if (OSTYPE == "LINUX")
    {
        if (_path[-1] != "/")
        {
            _path += "/";
        }
    }
    else
    {
        if (_path[-1] != "\\")
        {
            _path += "\\";
        }
    }
}

void File::_setExtension()
{
    List<String> name_list = _name.split(".");
    if (len(name_list) > 1)
    {
        _extension = name_list[-1];
    }
}

void File::_setName()
{
    List<String> path_list = getPathList(_path);

    if (path_list[-1] == "")
    {
        if (path_list.getSize() > 1)
        {
            _name = path_list[-2];
        }
        else
        {
            _name = path_list[-1];
        }
    }
    else
    {
        _name = path_list[-1];
    }
}