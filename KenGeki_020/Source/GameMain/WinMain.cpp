//=================================================================================================
//
// ウィンドウメイン ソースコード
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameMain.h"
//#include "../../resource1.h"

//-------------------------------------------------------------------------------------------------
//ネームスペースの利用
//-------------------------------------------------------------------------------------------------
using namespace GAME;

//------------------------------------------
// windows　エントリポイント
//------------------------------------------
int APIENTRY wWinMain ( HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow )
{
	//------------------------------------------------------------------------
	//デバッグ：ファイル出力
	TRACE_F ( _T ( "\n---------------------------------------\n" ) );
	TRACE_F ( _T ( "wWinMain : アプリケーション開始 hInst = %d\n" ), hInst );
	DebugOutFile::Create ();		//ファイルにデバッグメッセージを書出
	DBGOUT_FL_F ( _T ( "ファイル書出開始\n" ) );

	//------------------------------------------------------------------------
	//アプリケーション処理のオブジェクト
	LPCTSTR wndclss = _T ( "GameLibWnd" );				//ウィンドウクラス名, 
	LPCTSTR mutex = _T ( "2024 攻勢道場" );			//ミューテックス文字列, 
	LPCTSTR title = _T ( " 剣撃クロスゾーン - Ken Geki Cross Zone - " );	//タイトルバー, 
//	LPCTSTR icon = MAKEINTRESOURCE ( IDI_ICON1 );		//アイコン
	LPCTSTR icon = nullptr;
	ResourceName rcName = { wndclss, mutex, title, icon };

	std::shared_ptr < Application > app = make_shared < Application > ( rcName );
	app->SetFlag_MakeArchive ( T );	//アーカイブ作成フラグ
	app->AppLoad ( hInst );		//アプリケーションの初期化

	//------------------------------------------------------------------------
	//デバッグ表示切替
#define DEBUG_DISP 1
#if DEBUG_DISP
	app->FullDebugMode ();
	DBGOUT_WND_ON ();
#else
	app->NoDebugMode ();
	DBGOUT_WND_OFF ();
#endif // DEBUG_DISP

	//------------------------------------------------------------------------
	//ゲームメインテスト (何もしないテスト)
//	unique_ptr < GameMainTest > gameMain = make_unique < GameMainTest > ();
	//ゲームメインオブジェクト
	unique_ptr < GameMain >	gameMain = make_unique < GameMain > ();


	TRACE_F ( _T ( "ゲームメインの生成 sizeof(gameMain) = %d\n" ), sizeof ( *gameMain ) );

	app->SetGameMain ( ::move ( gameMain ) );	//ゲームメインの設置
	app->Load ();
	app->Init ();

	//------------------------------------------------------------------------
	//Windowsメッセージのメインループ
	MSG msg = { 0 };		//メッセージ
	TRACE_F ( _T ( "メッセージループの開始\n" ) );

	app->MainLoop ( & msg );

	TRACE_F ( _T ( "メッセージループの終了\n" ) );

	//------------------------------------------------------------------------
	TRACE_F ( _T ( "wWinMain : 終了\n" ) );
	TRACE_F ( _T ( "---------------------------------------\n\n" ) );

	return (int)msg.wParam;
}

  