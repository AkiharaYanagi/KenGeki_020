//=================================================================================================
//
// メイン ソースコード
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameMain.h"
#include "G_Ftg.h"


//-------------------------------------------------------------------------------------------------
//	実装
//-------------------------------------------------------------------------------------------------
using namespace GAME;


//前方宣言
void Load ();
void Init ();
void Move ();
void Draw ();

//ゲームシステム
GameSystem gameSystem;


//メインループ
void Main()
{
	//タイトル
	Window::SetTitle ( U"剣撃クロスゾーン" );

	//読込
	Load ();

	//========================================
	//メインループ
	bool init = F;
	while ( System::Update() )
	{
		//初期化
		if ( ! init ) { Init (); init = T; }

		//動作
		Move ();

		//描画
		Draw ();
	}
	//========================================
}


//起動後１回のみの初期化
void Load ()
{
	//-------------------------------------
	//シーン共通
	//格闘部分共通パラメータシングルトン生成
	G_Ftg::Create ();

	//-------------------------------------
	//システム初期化
	gameSystem.SystemLoad ();

	//ゲームメイン
	UP_GameMain gameMain = std::make_unique < GameMain > ();
	gameMain->Load ();
	gameMain->Init ();

	//ゲームシステムにメインを追加
	gameSystem.SetpGameMain ( std::move ( gameMain ) );
}

//メインループ中の最初の１回のみの初期化
void Init ()
{
	//ウィンドウ設定

	//ゲーム表示サイズ
	s3d::Size size = s3d::Scene::Size ();
	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Virtual );
	s3d::Scene::Resize ( 1280, 960 );
//	s3d::Scene::Resize ( 1200, 900 );

	//ウィンドウサイズ
	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Keep );
//	s3d::Window::Resize ( 1600, 900 );
	int32 wnd_w = 1728;
	int32 wnd_h = 972;
	s3d::Window::Resize ( wnd_w, wnd_h );	//16:9 で(1280,960)が入るサイズ
	s3d::Window::SetStyle ( s3d::WindowStyle::Sizable );

	//位置
#define CURSOR_POS_START 0
#if CURSOR_POS_START
	s3d::Window::Centering ();	//モニタ中央
#else
	//カーソル位置のモニタの中心
	WND_UTL::MoveWindow_toCenter_onCursor ();
#endif // 0

}



//---------------------------------------------------
// 動作
//---------------------------------------------------
void Move ()
{
	//ゲームメイン
	gameSystem.Move ();
}


//---------------------------------------------------
// 描画
//---------------------------------------------------
void Draw ()
{
	//ゲームメイン
	gameSystem.Draw ();
}
