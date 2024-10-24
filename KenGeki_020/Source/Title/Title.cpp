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
#include "../GameMain/VoiceConst.h"
#include "../GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

#pragma region CONST

	const float Title::BG_X = 0;
	const float Title::BG_Y = 0;
	const float Title::BG_VX = -64.f;
	const float Title::BG_P = (-7680 + 1920);

	const float Title::LOGO_X = ( WINDOW_WIDTH - 648 ) * 0.5f;
	const float Title::LOGO_Y = 0;

	const float Title::MENU_X = 580;
	const float Title::MENU_Y = 800 - 7;

	const float Title::CURSOR_X = 480;
	const float Title::CURSOR_Y = 800;
	const float Title::CURSOR_P = 70;

	const float Title::INST_X = 0;
	const float Title::INST_Y = 960 - 27;

	const uint32 Title::FADE_IN_T = 16;
	const uint32 Title::FADE_OUT_T = 16;

	const uint32 Title::TITLE_CALL_WAIT = 2;

#pragma endregion


	Title::Title ()
	{
		//---------------------------------------------------
		//グラフィック初期化
		//---------------------------------------------------
		m_bg = std::make_shared < GameGraphic > ();
		m_bg->AddTexture_FromArchive ( U"Title\\title_bg.png" );
		m_bg->SetPos ( BG_X, BG_Y );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

		m_logo = std::make_shared < GameGraphic > ();
		m_logo->AddTexture_FromArchive ( U"Title\\title_logo.png" );
		m_logo->SetPos ( LOGO_X, LOGO_Y );
		m_logo->SetZ ( Z_BG );
		AddpTask ( m_logo );
		GRPLST_INSERT ( m_logo );

		m_menu = std::make_shared < GameGraphic > ();
		m_menu->AddTexture_FromArchive ( U"Title\\title_menu.png" );
		m_menu->SetPos ( MENU_X, MENU_Y );
		m_menu->SetZ ( Z_CH );
		AddpTask ( m_menu );
		GRPLST_INSERT ( m_menu );

		m_cursor = std::make_shared < GameGraphic > ();
		m_cursor->AddTexture_FromArchive ( U"Title\\title_cursor.png" );
		m_cursor->SetPos ( CURSOR_X, CURSOR_Y );
		m_cursor->SetScalingCenter ( 0, 12.5f );
		m_cursor->SetZ ( Z_CH );
		AddpTask ( m_cursor );
		GRPLST_INSERT ( m_cursor );

		m_inst = std::make_shared < GameGraphic > ();
		m_inst->AddTexture_FromArchive ( U"Title\\Inst_Title.png" );
		m_inst->SetPos ( INST_X, INST_Y );
		m_inst->SetZ ( Z_CH );
		AddpTask ( m_inst );
		GRPLST_INSERT ( m_inst );

		//カーソル位置
		m_cursor->SetPos ( CURSOR_X, CURSOR_Y + CURSOR_P * (int32)m_to );


		//フェードイン
		m_fade_in = std::make_shared < FadeRect > ();
		AddpTask ( m_fade_in );
		GRPLST_INSERT ( m_fade_in );

		m_fade_in->StartWhiteIn ( FADE_IN_T );

		//フェードアウト
		m_fade_out = std::make_shared < FadeRect > ();
		m_fade_out->SetAfterClear ( F );
		AddpTask ( m_fade_out );
		GRPLST_INSERT ( m_fade_out );


		//タイマ
		m_tmr_title_bgm = std::make_shared < Timer > ( FADE_IN_T );
		m_tmr_title_bgm->Start ();
		m_tmr_title_call = std::make_shared < Timer > ( TITLE_CALL_WAIT );
		m_tmr_title_call->Start ();
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
		//常時演出
		
		//タイマ
		m_tmr_title_bgm->Move ();
		if ( m_tmr_title_bgm->IsLast () )
		{
			SND()->Test ();

			//BGM
			SND_STOP_ALL_BGM ();
			SND_PLAY_LOOP_BGM ( BGM_Title );
		}

		m_tmr_title_call->Move ();
		if ( m_tmr_title_call->IsLast () )
		{
			SND_PLAY_ONESHOT_VC ( VC_00_TITLE_CALL );
		}

		//背景スクロール
		m_bg_x += BG_VX;
		if ( m_bg_x < BG_P ) { m_bg_x = BG_X; }
		m_bg->SetPos ( m_bg_x, BG_Y );

		//カーソル回転
		m_cursor_scaling_y += m_cursor_scaling_vy;
		if ( m_cursor_scaling_y >=  1.f ) { m_cursor_scaling_vy = - 0.1f; }
		if ( m_cursor_scaling_y <= -1.f ) { m_cursor_scaling_vy =   0.1f; }
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
			if ( m_plus_wait > FADE_OUT_T - 1 )
			{
				//ゲーム共通パラメータ
				P_Param pParam = Scene::GetpParam ();

				switch ( m_to )
				{
				case TITLE_TO_BATTLE:
					SND_STOP_ALL_BGM ();
					pParam->SetGameMode ( GAME_MODE::MODE_MAIN );
					Scene::Transit_CharaSele ();
//					Scene::Transit_Fighting ();
					break;
				case TITLE_TO_TRAINING:
					SND_STOP_ALL_BGM ();
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
		//----------------------------
		//	キー上下でシーンを選択
		//----------------------------

		//キー上
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

			SND_PLAY_ONESHOT_SE ( SE_select_move );
		}

		//キー下
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

			SND_PLAY_ONESHOT_SE ( SE_select_move );
		}

		//カーソル位置更新
		m_cursor->SetPos ( CURSOR_X, CURSOR_Y + CURSOR_P * (int32)m_to );


		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( P1_BTN0 ) || CFG_PUSH_KEY ( P2_BTN0 ) )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_decide );

			//フェード開始
			m_fade_out->StartBlackOut ( FADE_OUT_T );
		}

	}


}	//namespace GAME

