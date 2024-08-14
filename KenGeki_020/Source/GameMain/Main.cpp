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

//ブレンド用 レンダーテクスチャ
std::unique_ptr < RenderTexture > p_rd_tx;


//メインループ
void Main()
{
	//読込
	Load ();

#if 0
	//-------------------------------------
	//test
	ColorF color { 1.0, 1.0, 1.0, 1.0 };
//	ColorF color { 1.0, 0.5, 0.5, 1.0 };
	s3d::Texture ef1 ( U"ef_001.png" );
	s3d::Texture ef4 ( U"ef_004.png" );

	const PixelShader ps = HLSL { U"example/shader/hlsl/rgb_shift.hlsl", U"PS" };
	const PixelShader ps_screen = HLSL { U"ScreenBlend.hlsl", U"PS" };

	//ブレンド用 レンダーテクスチャ
	p_rd_tx = std::make_unique < RenderTexture > ( 1280, 960, Palette::Lightgreen );
	//-------------------------------------
#endif // 0

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


	//中央
	s3d::Window::Centering ();


#else

	//マウス位置にウィンドウを移動
	s3d::Point pt = s3d::Cursor::Pos () ;
	s3d::Window::SetPos ( pt );

	//ウィンドウ位置のモニタIDを取得
	size_t monitorIndex = s3d::System::GetCurrentMonitorIndex ();
	s3d::Array < s3d::MonitorInfo > a_mInfo = s3d::System::EnumerateMonitors ();
	s3d::MonitorInfo mInfo = a_mInfo [ monitorIndex ];
	s3d::Vec2 mCenter = mInfo.displayRect.center();
	const int32 dev_y = - 32;
	s3d::Window::SetPos ( (int32)mCenter.x - wnd_w / 2, dev_y + (int32)mCenter.y - wnd_h / 2 );


	//カーソル位置にウィンドウを移動
//	WND_UTL::MoveWindow_toCursor ();


#endif // 0


}



void Move ()
{
	//---------------------------------------------------
	// 動作
	//---------------------------------------------------

	//毎回の更新
	const Array<Input> & keys = s3d::Keyboard::GetAllInputs();
	SivInput::Inst()->Update ( keys );

	//ゲームメイン
	gameSystem.Move ();
}



void Draw ()
{
	//---------------------------------------------------
	// 描画
	//---------------------------------------------------

	gameSystem.Draw ();

	//ブレンドテスト
#if 0
	{
		const ScopedColorMul2D colorMul { color };
		//			const ScopedRenderStates2D blend { BlendState::Multiplicative };
		ef4.draw ( 250, 400 );
		ef1.draw ( 30, 390 );

		//イメージ
		//ブレンド：スクリーン
		// 1 - ( 1 - A )( 1 - B );
}

	{
		//			const ScopedCustomShader2D shader { ps };
		const ScopedCustomShader2D shader { ps_screen };
		ef1.draw ( 30, 390 );
	}
#endif // 0


	//レンダーターゲット指定
#if 0
	{
		const s3d::ScopedRenderTarget2D target { * p_rd_tx };

		//ゲームメイン描画
		gameSystem.Draw ();

	}
	p_rd_tx->draw ();
#endif // 0


	//ピクセルシェーダ指定
#if 0
	//		s3d::Graphics2D::SetPSTexture ( 1, rd_tx );	//適用テクスチャを指定
	s3d::Graphics2D::SetPSTexture ( 1, ef1 );	//適用テクスチャを指定
	//		s3d::Graphics2D::SetPSTexture ( 1, ef4 );	//適用テクスチャを指定
	{
		//			const s3d::ScopedCustomShader2D shader { ps };
		const s3d::ScopedCustomShader2D shader { ps_screen };
		//			ef1.draw ( 30, 390 );
		//			ef4.draw ( 250, 400 );
		rd_tx.draw ();
	}
#endif // 0


}
