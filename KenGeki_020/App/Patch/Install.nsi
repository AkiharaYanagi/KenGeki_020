# 日本語UI
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Japanese.nlf"

# アプリケーション名
Name "剣撃クロスゾーン 修正パッチ ver0.20"

#作成されるインストーラ
OutFile "Installer.exe"

#インストールされるディレクトリ
InstallDir "C:\Game\剣撃クロスゾーン"

#ページ
Page directory
Page instfiles



#デフォルトセクション
Section

	#出力先を指定します。
	SetOutPath "$INSTDIR"

	#インストールされるファイル
	File "F:\Projects\KenGeki_020\KenGeki_020\App\◆公開用　修正点・変更点.txt"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\Readme_剣撃クロスゾーン.txt"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\剣撃ゲーム指南書.pdf"


	#出力先を指定します。
	SetOutPath "$INSTDIR\KenGeki"

	#インストールされるファイル
	File "F:\Projects\KenGeki_020\KenGeki_020\App\KenGeki_CrossZone.exe"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\剣撃クロスゾーン.exe"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\chara_Sae_Bin.dat"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\chara_Retsudou_Bin.dat"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\chara_Ouka_Bin.dat"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\archive.dat"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\Se.dat"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\Vc.dat"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\剣撃クロスゾーン 入力設定.exe"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\ScriptEditor.exe"

SectionEnd
