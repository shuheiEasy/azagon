# azagon

## ライブラリ一覧
|ライブラリ名|ライブラリの機能|
|:-:|:-:|
| dataObject | 型クラス |
| fileSystem | ファイル操作 |
| threadSystem | スレッド |
| logSystem  | ログ出力 |
| formatter  | 書式 |
| timeSystem | 時間 |

## ドキュメント
[ドキュメント](https://shuheieasy.github.io/azagon/)

## インストール方法
1. 関連パッケージのインストール
    ```bash
    sudo apt -y install cmake \
    gcc g++ \
    language-pack-ja
    ```
2. 本リポジトリをダウンロードした場所へ移動
3. ビルド用のフォルダを作成し移動する
    (例)
    ```bash
    mkdir build
    cd build
    ```
4. 下記コマンドを実行する
    ```bash
    cmake .. -DINSTALL_FLAG=ON
    ```
5. ビルドし、インストール
    ```bash
    sudo make install
    ```
6. パスを通す
    ```bash
    export LD_LIBRARY_PATH=/usr/local/lib/azagon:${LD_LIBRARY_PATH}
    ```
