# ニンテンドークラシックミニ スーパーファミコンのコントローラーをパソコンで使えるようにするハードウェア

[ニンテンドークラシックミニ スーパーファミコンのコントローラーをパソコンで使えるようにするハードウェア](https://kkawahara.net/software/ncmsfc-controller-converter)

## ハードウェアの配線図

![](./docs/sketch.webp)

## 書き込み方法

`ツール`-`ライブラリの管理...`から XInput をインストールする。

[GitHub - dmadison/ArduinoXInput_AVR: AVR boards package for the ArduinoXInput project](https://github.com/dmadison/ArduinoXInput_AVR)

[GitHub - dmadison/ArduinoXInput_Sparkfun: SparkFun boards package for the ArduinoXInput project](https://github.com/dmadison/ArduinoXInput_SparkFun)

上記サイトにアクセスし、Arduino のインストール場所(例: `C:\Program Files (x86)\Arduino`)に以下のように`xinput`と`xinput_sparkfun`をコピーする。

```
└───Arduino Installation
        ├───drivers
        ├───examples
        ├───hardware
        │   ├───arduino
        │   ├───tools
        │   ├───xinput
        │   └───xinput_sparkfun
        │       └───avr
        │           ├───bootloaders
        │           ├───cores
        │           ├───libraries
        │           └───variants
        ├───java
        ├───lib
        ├───libraries
        ├───reference
        ├───tools
        └───tools-builder
```

Arduino IDE を再起動する。

`ツール`-`ボード`から`SparkFun Pro Micro w/ XInput`を選択する。

書き込みにはコツが必要で、まずポートを正しく選択しておく必要がある。 マイコンのリセットボタンをダブルクリックすると、8 秒間 COM ポートが出現する。
マイコンのリセットボタンをダブルクリックし、素早く Arduino IDE のツール-シリアルポートから COM ポートを設定する。

書き込む際は Arduino IDE のマイコンボードに書き込むを押した後、マイコンボードに書き込んでいます...のメッセージが出た直後にマイコンのリセットボタンをダブルクリックする。
うまくいけばボードへの書き込みが完了しました。のメッセージが表示される。
