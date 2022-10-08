# common_library

## ライブラリ一覧
|ライブラリ名|ライブラリの機能|
|:-:|:-:|
| dataObject | 型クラス |
| fileSystem | ファイル操作 |
| logSystem  | ログ出力 |
| formatter  | 書式 |
| timeSystem | 時間 |

## ドキュメント
[ドキュメント](https://shuheieasy.github.io/common_library/)

## インストール方法
1. 本リポジトリをダウンロードした場所へ移動
2. ビルド用のフォルダを作成し移動する
    (例)
    ```bash
    mkdir build
    cd build
    ```
3. 下記コマンドを実行する
    ```bash
    cmake .. -DINSTALL_FLAG=ON
    ```
4. ビルドし、インストール
    ```bash
    sudo make install
    ```
