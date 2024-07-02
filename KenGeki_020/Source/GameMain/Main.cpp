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


//-------------------------------------------------------------------------------------------------
//	実装
//-------------------------------------------------------------------------------------------------
using namespace GAME;


//メインループ中の最初の１回
void Init ()
{
#if 0
	//マウス位置にウィンドウを移動
	s3d::Point pt = s3d::Cursor::Pos () ;
	s3d::Window::SetPos ( pt );
#endif // 0

	//カーソル位置の取得
	POINT cursorPos;
	::GetCursorPos ( & cursorPos );
	cursorPos.x -= 700;
	cursorPos.y -= 15;
	s3d::Point pt { cursorPos.x, cursorPos.y };

	s3d::Window::SetPos ( pt );

}


//メインループ
void Main()
{
#if 0
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	// 画像ファイルからテクスチャを作成する | Create a texture from an image file
	const Texture texture{ U"example/windmill.png" };

	// 絵文字からテクスチャを作成する | Create a texture from an emoji
	const Texture emoji{ U"🦖"_emoji };

	// 太文字のフォントを作成する | Create a bold font with MSDF method
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// テキストに含まれる絵文字のためのフォントを作成し、font に追加する | Create a font for emojis in text and add it to font as a fallback
	const Font emojiFont{ 48, Typeface::ColorEmoji };
	font.addFallback(emojiFont);

	// ボタンを押した回数 | Number of button presses
	int32 count = 0;

	// チェックボックスの状態 | Checkbox state
	bool checked = false;

	// プレイヤーの移動スピード | Player's movement speed
	double speed = 200.0;

	// プレイヤーの X 座標 | Player's X position
	double playerPosX = 400;

	// プレイヤーが右を向いているか | Whether player is facing right
	bool isPlayerFacingRight = true;
#endif // 0

	//ウィンドウ設定
	s3d::Size size = s3d::Scene::Size ();
	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Virtual );
	s3d::Scene::Resize ( 1280, 960 );

	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Keep );
	s3d::Window::Resize ( 1600, 900 );
	s3d::Window::SetStyle ( s3d::WindowStyle::Sizable );
	s3d::Window::Centering ();

	//マウス位置にウィンドウを移動
	s3d::Point pt = s3d::Cursor::Pos () ;
	s3d::Window::SetPos ( pt );


	//	SivInput::Create();

	GameMain gameMain;

#if 0
	P_Grp grp = std::make_shared < GrpBs > ();
	grp->SetTextureName ( U"test.png" );
	gameMain.AddpTask ( grp );
#endif // 0

	gameMain.Load ();

	//	s3d::Texture tx ( ( U"test.png") );



	//test

	ColorF color { 1.0, 1.0, 1.0, 1.0 };
//	ColorF color { 1.0, 0.5, 0.5, 1.0 };
	s3d::Texture ef1 ( U"ef_001.png" );
	s3d::Texture ef4 ( U"ef_004.png" );

	const PixelShader ps = HLSL { U"example/shader/hlsl/rgb_shift.hlsl", U"PS" };
	const PixelShader ps_screen = HLSL { U"ScreenBlend.hlsl", U"PS" };

	//動画テスト
//	const VideoTexture vidTx ( U"BG.mp4", Loop::Yes );
	
	 
	//=========================================================================
	//メインループ
	bool init = F;
	while ( System::Update() )
	{
#if 0
		// テクスチャを描く | Draw the texture
		texture.draw(20, 20);

		// テキストを描く | Draw text
		font(U"Hello, Siv3D!🎮").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });

		// 指定した範囲内にテキストを描く | Draw text within a specified area
		font(U"Siv3D (シブスリーディー) は、ゲームやアプリを楽しく簡単な C++ コードで開発できるフレームワークです。")
			.draw(18, Rect{ 20, 430, 480, 200 }, Palette::Black);

		// 長方形を描く | Draw a rectangle
		Rect{ 540, 20, 80, 80 }.draw();

		// 角丸長方形を描く | Draw a rounded rectangle
		RoundRect{ 680, 20, 80, 200, 20 }.draw(ColorF{ 0.0, 0.4, 0.6 });

		// 円を描く | Draw a circle
		Circle{ 580, 180, 40 }.draw(Palette::Seagreen);

		// 矢印を描く | Draw an arrow
		Line{ 540, 330, 760, 260 }.drawArrow(8, SizeF{ 20, 20 }, ColorF{ 0.4 });

		// 半透明の円を描く | Draw a semi-transparent circle
		Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1.0, 0.0, 0.0, 0.5 });

		// ボタン | Button
		if (SimpleGUI::Button(U"count: {}"_fmt(count), Vec2{ 520, 370 }, 120, (checked == false)))
		{
			// カウントを増やす | Increase the count
			++count;
		}

		// チェックボックス | Checkbox
		SimpleGUI::CheckBox(checked, U"Lock \U000F033E", Vec2{ 660, 370 }, 120);

		// スライダー | Slider
		SimpleGUI::Slider(U"speed: {:.1f}"_fmt(speed), speed, 100, 400, Vec2{ 520, 420 }, 140, 120);

		// 左キーが押されていたら | If left key is pressed
		if (KeyLeft.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPosX = Max((playerPosX - speed * Scene::DeltaTime()), 60.0);
			isPlayerFacingRight = false;
		}

		// 右キーが押されていたら | If right key is pressed
		if (KeyRight.pressed())
		{
			// プレイヤーが右に移動する | Player moves right
			playerPosX = Min((playerPosX + speed * Scene::DeltaTime()), 740.0);
			isPlayerFacingRight = true;
		}

		// プレイヤーを描く | Draw the player
		emoji.scaled(0.75).mirrored(isPlayerFacingRight).drawAt(playerPosX, 540);
#endif // 0

#if 0
#endif // 0

		//初期化
		if ( ! init )
		{
			Init ();
			init = T;
		}


		//動画テスト
//		vidTx.advance ();
//		vidTx.draw ();


		//ゲームメイン
		gameMain.Move ();
		gameMain.Draw ();




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
#endif // 0

		{
			const ScopedCustomShader2D sader { ps };
			ef1.draw ( 30, 390 );
		}



		//		tx.draw ( 200, 200 );

		//		SivInput::Inst()->Is_Keyboard ( SIK_Z );
	}
}

