//=================================================================================================
//
//	タイトル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title.h"
#include "../GameMain/SoundConst.h"


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
		m_bg->AddTexture_FromArchive ( U"Title\\title_bg.png" );
		m_bg->SetPos ( m_bg_x, 0 );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

		m_logo = std::make_shared < GameGraphic > ();
		m_logo->AddTexture_FromArchive ( U"Title\\title_logo.png" );
		m_logo->SetPos ( ( WINDOW_WIDTH - 648 ) * 0.5f, 0 );
		m_logo->SetZ ( Z_BG );
		AddpTask ( m_logo );
		GRPLST_INSERT ( m_logo );

		m_menu = std::make_shared < GameGraphic > ();
		m_menu->AddTexture_FromArchive ( U"Title\\title_menu.png" );
		m_menu->SetPos ( 580, 800 );
		m_menu->SetZ ( Z_CH );
		AddpTask ( m_menu );
		GRPLST_INSERT ( m_menu );

		m_cursor = std::make_shared < GameGraphic > ();
		m_cursor->AddTexture_FromArchive ( U"Title\\title_cursor.png" );
		m_cursor->SetPos ( 480, 840 );
		m_cursor->SetScalingCenter ( 0, 16 );
		m_cursor->SetZ ( Z_CH );
		AddpTask ( m_cursor );
		GRPLST_INSERT ( m_cursor );

		//カーソル位置
		m_cursor->SetPos ( 480.f, 800.f + 80 * (int32)m_to );


		//フェードイン
		m_fade_in = std::make_shared < FadeRect > ();
		AddpTask ( m_fade_in );
		GRPLST_INSERT ( m_fade_in );

		m_fade_in->StartWhiteIn ( 30 );

		//フェードアウト
		m_fade_out = std::make_shared < FadeRect > ();
		m_fade_out->SetAfterClear ( F );
		AddpTask ( m_fade_out );
		GRPLST_INSERT ( m_fade_out );
	}

	Title::~Title ()
	{
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

		//BGM
		SOUND->Stop_BGM ( BGM_Title );
		SOUND->Play_Loop_BGM ( BGM_Title );
	}


	void Title::ParamInit ()
	{
	}

	void Title::Move ()
	{
		//常時演出
		
		//背景スクロール
		m_bg_x -= 64.f;
		if (m_bg_x < (-7680 + 1920) ) { m_bg_x = 0; }
		m_bg->SetPos ( m_bg_x, 0 );

		//カーソル回転
		m_cursor_scaling_y += m_cursor_scaling_vy;
		if ( m_cursor_scaling_y >= 1.f ) { m_cursor_scaling_vy = - 0.1f; }
		if (m_cursor_scaling_y <= -1.f) { m_cursor_scaling_vy = 0.1f; }

		m_cursor->SetScaling ( 1.f, m_cursor_scaling_y );


		//フェード中は入力を受付しない
		if ( m_fade_in->IsActive () ) { Scene::Move (); return; }
		if ( m_fade_out->IsActive () ) { Scene::Move (); return; }


		//入力
		Input ();

		Scene::Move ();
	}

	P_GameScene Title::Transit ()
	{
		//フェード待機開始
		if ( m_fade_out->IsLast () )
		{
			++ m_plus_wait;
		}

		//フェード待機後、遷移
		if ( m_plus_wait > 0 )
		{
			if ( m_plus_wait > 15 )
			{
				//ゲーム共通パラメータ
				P_Param pParam = Scene::GetpParam ();

				switch ( m_to )
				{
				case TITLE_TO_BATTLE:
					SOUND->Stop_BGM ( BGM_Title );
					pParam->SetGameMode ( GAME_MODE::MODE_MAIN );
					Scene::Transit_CharaSele ();
//					Scene::Transit_Fighting ();
					break;
				case TITLE_TO_TRAINING:
					SOUND->Stop_BGM ( BGM_Title );
					pParam->SetGameMode ( GAME_MODE::MODE_TRAINING );
					Scene::Transit_CharaSele ();
//					Scene::Transit_Training ();
					break;
				}

				m_plus_wait = 0;
			}

			++ m_plus_wait;
		}


		return Scene::Transit ();
	}


	void Title::Input ()
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
			SOUND->Play_SE ( SE_Sys_Select );
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
			SOUND->Play_SE ( SE_Sys_Select );
		}

		//カーソル位置
		m_cursor->SetPos ( 480.f, 800.f + 80 * (int32)m_to );


		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( P1_BTN0 ) || CFG_PUSH_KEY ( P2_BTN0 ) )
		{
			SOUND->Play_SE ( SE_Sys_Enter );

			//フェード開始
			m_fade_out->StartBlackOut ( 16 );
		}

	}


}	//namespace GAME

