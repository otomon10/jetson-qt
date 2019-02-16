# example-app-01からの変更点

GUI部分以外をQtライブラリに依存しないように作成するため、
シグナル／スロット処理や、マルチスレッド制御をQtに依存しない形で実装した。
シグナル／スロット処理はboostのsignals2、マルチスレッド制御はC++標準ライブラリのthreadを使った。

# サードパーティのシグナルスロット制御

Qt APIを使ったソースファイルでsignalsやemitなどのキーワードを使用したくない場合は、
CONFIGにno_keywordsを定義する。boostのsignals2を使う場合などは指定する。

http://doc.qt.io/qt-5/signalsandslots.html#using-qt-with-3rd-party-signals-and-slots

# スレッドIDの再利用

スレッドIDは再利用されることがある。
LED発光のような短時間で終了する処理の場合、同じスレッドIDのスレッドが生成される場合があるので注意する。

https://ja.cppreference.com/w/cpp/thread/thread/id


