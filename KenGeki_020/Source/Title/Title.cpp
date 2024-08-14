//=================================================================================================
//
//	タイトル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title.h"
//#include "../GameMain/SoundConst.h"

//遷移先
#include "../FtgMain/FtgMain.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Title::Title ()
	{
		//---------------------------------------------------
		//グラフィック初期化
		//---------------------------------------------------
		m_bg = std::make_shared < GameGraphic > ();
		m_bg->AddTexture_FromArchive ( U"title_logo.png" );
		m_bg->SetPos ( 0, 0 );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

		m_menu = std::make_shared < GameGraphic > ();
		m_menu->AddTexture_FromArchive ( U"title_menu.png" );
		m_menu->SetPos ( 580, 800 );
		m_menu->SetZ ( Z_CH );
		AddpTask ( m_menu );
		GRPLST_INSERT ( m_menu );

		m_cursor = std::make_shared < GameGraphic > ();
		m_cursor->AddTexture_FromArchive ( U"title_cursor.png" );
		m_cursor->SetPos ( 480, 840 );
		m_cursor->SetZ ( Z_CH );
		AddpTask ( m_cursor );
		GRPLST_INSERT ( m_cursor );

#if 0
		m_rect = std::make_shared < PrmRect > ();
		m_rect->SetPos ( 0, 0 );
		m_rect->SetZ ( Z_BG );
		m_rect->SetSize ( 1280, 960 );
		m_rect->SetColor ( 0xffffffff );
		AddpTask ( m_rect );
		GRPLST_INSERT_MAIN ( m_rect );

		m_Start = make_shared < GrpAcv > ();
		m_Start->AddTexture ( _T ( "Start.png" ) );
		m_Start->SetZ ( Z_BG );
		m_Start->SetPos ( 640 - 128, 800 );
		AddpTask ( m_Start );
		GRPLST_INSERT_MAIN ( m_Start );


		//フェードイン
		m_fade_in = make_shared < PrmRect > ();
		m_fade_in->SetSize ( VEC2 ( 1280, 960 ) );
		m_fade_in->SetPos ( VEC2 ( 0, 0 ) );
		m_fade_in->SetAllColor ( 0xffffffff );
		m_fade_in->SetZ ( Z_FADE - 0.1f);
		m_fade_in->SetValid ( T );
		AddpTask ( m_fade_in );
		GRPLST_INSERT_MAIN ( m_fade_in );
		m_fade_in->SetFade ( 8, _CLR ( 0xffffffffUL ), _CLR ( 0x00ffffffUL ) );	//開始値、目標値を手動設定
		m_wait_in = 1;

		//フェードアウト
		m_fade_out = make_shared < PrmRect > ();
		m_fade_out->SetSize ( VEC2 ( 1280, 960 ) );
		m_fade_out->SetPos ( VEC2 ( 0, 0 ) );
		m_fade_out->SetAllColor ( 0x00000000 );
		m_fade_out->SetZ ( Z_FADE - 0.1f);
		m_fade_out->SetValid ( F );
		AddpTask ( m_fade_out );
		GRPLST_INSERT_MAIN ( m_fade_out );
		m_wait_out = 0;
#endif // 0
	}

	Title::~Title ()
	{
	}

	void Title::ParamInit ()
	{
	}

	void Title::Move ()
	{
		//キー上下でシーンを選択
		if ( CFG_PUSH_KEY ( P1_UP ) || CFG_PUSH_KEY ( P2_UP ) )
		{
			switch ( m_to )
			{
			case TITLE_TO_BATTLE:
				m_to = TITLE_TO_TRAINING;
				break;
			case TITLE_TO_TRAINING:
				m_to = TITLE_TO_BATTLE;
				break;
			}
		}
		if ( CFG_PUSH_KEY ( P1_DOWN ) || CFG_PUSH_KEY ( P2_DOWN ) )
		{
			switch ( m_to )
			{
			case TITLE_TO_BATTLE:
				m_to = TITLE_TO_TRAINING;
				break;
			case TITLE_TO_TRAINING:
				m_to = TITLE_TO_BATTLE;
				break;
			}
		}

		//カーソル位置
		m_cursor->SetPos ( 480.f, 800.f + 80 * (int32)m_to );


#if 0
		//フェードイン中
		if ( m_wait_in != 0 )
		{
			++ m_wait_in;

			if ( m_wait_in > 15 )
			{
				m_wait_in = 0;
			}
		}


		//フェードアウト中
		if ( m_wait_out != 0 )
		{
			++ m_wait_out;

			if ( m_wait_out > 15 )
			{
				Scene::Transit_CharaSele ();
				m_wait_out = 0;
			}
		}

#endif // 0
		Scene::Move ();
	}

	void Title::Load ()
	{
		//==================================================
		//	Scene共通
		//==================================================
		//遷移先を自身に設定
		//	(コンストラクタでは shared_from_this() が使えないため、Load() で呼び出す)
		Scene::SetwpThis ( shared_from_this () );
		//==================================================

		Scene::Load ();
	}

	P_GameScene Title::Transit ()
	{
		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( P1_BTN0 ) || CFG_PUSH_KEY ( P2_BTN0 ) )
		{
#if 0
			SOUND->Play_SE ( SE_Sys_EnterFighting );

			//フェード開始
			m_fade_out->SetFade ( 8, _CLR ( 0x00000000UL ), _CLR ( 0xff000000UL ) );	//開始値、目標値を手動設定
			m_wait_out = 1;
#endif // 0

			switch ( m_to )
			{
			case TITLE_TO_BATTLE:
				Scene::Transit_Fighting ();
				break;
			case TITLE_TO_TRAINING:
				Scene::Transit_Training ();
				break;
			}

		}

		return Scene::Transit ();
	}


}	//namespace GAME

