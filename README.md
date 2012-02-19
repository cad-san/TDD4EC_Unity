#Test-Driven Development for Embedded Cの写経用リポジトリ

##概要

このリポジトリはTDD for Enbedded Cを写経するために作成したものです。[TDD for ECのオフィシャルサイト](http://pragprog.com/book/jgade/test-driven-development-for-embedded-c)で配布されているコードから、unity用のコードを切り出し、使いやすくしたものです。

あくまで個人の写経用なので、私の写経に伴って更新されています。単純に、unityのワークスペースとして利用したい場合は、initタグをチェックアウトしてください。

姉妹リポジトリ：[cad-san/TDD4EC_CppUTest](https://github.com/cad-san/TDD4EC_CppUTest)

## ディレクトリ構成

	include  … プロダクトコードのヘッダファイルを格納
	src      … プロダクトコードのソースファイルを格納
	mocks    … テスト用のmockをここに格納
	tests    … テストコードをここに格納（init時点ではtestになってます）
	unity    … unityのフレームワーク（基本さわらない）

## 使い方

詳細はTDD for ECの書籍を参照していただけるとありがたいです。
ここでは基本的な使い方を述べます。

1. テストスイートをtests以下に追加する (ex. tests/hoge/hogeTest.c)
2. テストランナーをtests以下に追加する (ex. tests/hoge/hogeTestRunner.c)
3. tests/AllTest.cにテストを追加して実行させるようにする
4. プロダクトコードのヘッダをinclude以下に追加 (ex. include/hoge/hoge.h)
5. プロダクトコードをsrc以下に追加(ex. src/hoge/hoge.c)
6. Makefileに、それぞれビルド対象に追加する
7. リポジトリ直下でmake実行