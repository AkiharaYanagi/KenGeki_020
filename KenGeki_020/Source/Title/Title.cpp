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

		m_fade_in->StartWhiteIn ( 8 );

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
	}


	void Title::ParamInit ()
	{
	}

	void Title::Move ()
	{
		//フェード中は何もしない
		if ( m_fade_in->IsActive () ) { Scene::Move (); return; }
		if ( m_fade_out->IsActive () ) { Scene::Move (); return; }

		//選択
		Select ();

		//カーソル回転
		m_cursor_scaling_y += m_cursor_scaling_vy;
		if ( m_cursor_scaling_y >= 1.f ) { m_cursor_scaling_vy = - 0.1f; }
		if (m_cursor_scaling_y <= -1.f) { m_cursor_scaling_vy = 0.1f; }

		m_cursor->SetScaling ( 1.f, m_cursor_scaling_y );

		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( P1_BTN0 ) || CFG_PUSH_KEY ( P2_BTN0 ) )
		{
			SOUND->Play_SE ( SE_Sys_Enter );

			//フェード開始
			m_fade_out->StartBlackOut ( 16 );
		}

		Scene::Move ();
	}

	P_GameScene Title::Transit ()
	{
		//フェード待機後、遷移開始
		if ( m_fade_out->IsLast () )
		{
			++ m_plus_wait;
		}

		if ( m_plus_wait > 0 )
		{
			if ( m_plus_wait > 15 )
			{
				switch ( m_to )
				{
				case TITLE_TO_BATTLE:
					Scene::Transit_CharaSele ();
//					Scene::Transit_Fighting ();
					break;
				case TITLE_TO_TRAINING:
					Scene::Transit_Training ();
					break;
				}

				m_plus_wait = 0;
			}

			++ m_plus_wait;
		}


		return Scene::Transit ();
	}


	void Title::Select ()
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
	}


}	//namespace GAME

