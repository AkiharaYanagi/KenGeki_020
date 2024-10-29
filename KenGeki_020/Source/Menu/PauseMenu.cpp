//=================================================================================================
//
//	PauseMenu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "PauseMenu.h"
#include "PauseMenu_Const.h"
#include "../GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const float PauseMenu::CURSOR_X = 100;
	const float PauseMenu::CURSOR_Y = 330;


	PauseMenu::PauseMenu ()
	{
		//--------------------------------------------
		//基本背景
		Menu::SetBG_use ( T );
		Menu::SetBG_Size ( WINDOW_WIDTH, WINDOW_HEIGHT );
		Menu::SetBG_Pos ( 0.f, 0.f );
		Menu::SetBG_Color ( _CLR ( 0xd0000000 ) );

		//--------------------------------------------
		//見出文字
		m_grpStr_pause = std::make_shared < MenuString > ();
		m_grpStr_pause->SetStr ( U"- PAUSE -" );
		m_grpStr_pause->SetPos ( 500, 120 );
		m_grpStr_pause->SetZ ( Z_MENU_STR );
		AddpTask ( m_grpStr_pause );
		GRPLST_INSERT ( m_grpStr_pause );

		//--------------------------------------------
		//カーソル
		m_cursor = std::make_shared < GameGraphic > ();
		m_cursor->AddTexture_FromArchive ( U"Title\\title_cursor.png" );
		m_cursor->SetPos ( CURSOR_X, CURSOR_Y );
		m_cursor->SetZ ( Z_MENU_STR );
		m_cursor->SetScalingCenter ( 0, 12.5f );
		AddpTask ( m_cursor );
		GRPLST_INSERT ( m_cursor );

		//--------------------------------------------
		//メニュー項目

		//タイトル
		m_mi_title = std::make_shared < PMI_To_Title > ();
		AddpTask ( m_mi_title );
		//ゲームに戻る
		m_mi_resume = std::make_shared < PMI_ResumeGame > ();
		AddpTask ( m_mi_resume );


		//--------------------------------------------
		//Y/Nメニュ
		m_yesnoMenu = std::make_shared < YesNo_Menu > ();
		AddpTask ( m_yesnoMenu );


		//--------------------------------------------
		//初期状態はOff
		Off ();

		//test
//		On ();
	}

	PauseMenu::~PauseMenu ()
	{
	}

	void PauseMenu::Load ()
	{
		//--------------------------------------------
		//メニュー項目
		Menu::SetpMenuItem ( m_mi_title );
		Menu::SetpMenuItem ( m_mi_resume );

		Menu::Load ();
	}

	void PauseMenu::Do ()
	{
	}

	void PauseMenu::Move ()
	{
		//Y/Nメニュ稼働時は何もしない
		if ( m_yesnoMenu->GetActive () ) { Menu::Move (); return; }

		//非アクティブ時は何もしない
		if ( ! GetActive () )
		{
			Menu::Move (); return;
		}
		if ( ! m_bMenu )
		{
			Menu::Move (); return; 
		}

		//@info 解除を同一ボタンにすると同[F]で解除されてしまう
		//-> MenuCheck()内部で分岐する
		
		Input ();


		//Do()は選択されたメニュ項目について常に行う
		Menu::Do ();


		//カーソル回転
		m_cursor_scaling_y += m_cursor_scaling_vy;
		if ( m_cursor_scaling_y >=  1.f ) { m_cursor_scaling_vy = - 0.1f; }
		if ( m_cursor_scaling_y <= -1.f ) { m_cursor_scaling_vy =   0.1f; }
		m_cursor->SetScaling ( 1.f, m_cursor_scaling_y );

		//カーソル位置
		m_cursor->SetPos ( CURSOR_X, CURSOR_Y + 100.f * Menu::GetIdItem () );


		Menu::Move ();
	}


	bool PauseMenu::MenuCheck ()
	{
		//メニュポーズ中
		if ( m_bMenu )
		{
			//メニュポーズ解除
			bool bEsc = ( WND_UTL::AscKey ( VK_ESCAPE ) );
			bool bMenuBtn = ( CFG_PUSH_KEY ( P1_BTN6 ) || CFG_PUSH_KEY ( P2_BTN6 ) );
			if ( bEsc || bMenuBtn )
			{
				SND_PLAY_ONESHOT_SE(SE_select_Cancel);
				Off ();
				return F;
			}
			else
			{
				Move ();
				return T;
			}
		}

		//メニュポーズ開始
		bool bEsc = ( WND_UTL::AscKey ( VK_ESCAPE ) );
		bool bMenuBtn = ( CFG_PUSH_KEY ( P1_BTN6 ) || CFG_PUSH_KEY ( P2_BTN6 ) );
		if ( bEsc || bMenuBtn )
		{
			SND_PLAY_ONESHOT_SE (SE_select_move);
			On ();
		}

		return F;
	}

	void PauseMenu::Input ()
	{
		//=============================================================
		// 操作
		//=============================================================
		//選択
		if ( CFG_PUSH_KEY ( P1_DOWN ) || CFG_PUSH_KEY ( P2_DOWN ) )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_move );
			Menu::Next ();
		}
		if ( CFG_PUSH_KEY ( P1_UP ) || CFG_PUSH_KEY ( P2_UP ) )
		{
			SND_PLAY_ONESHOT_SE (SE_select_move);
			Menu::Prev ();
		}

		//決定
		if ( CFG_PUSH_KEY ( P1_BTN0 ) || CFG_PUSH_KEY ( P2_BTN0 ) )
		{
			Menu::Decide ();
		}
		//=============================================================
	}


	//稼働
	void PauseMenu::Off ()
	{
		m_grpStr_pause->SetValid ( F );
		m_cursor->SetValid ( F );

		m_mi_title->Off ();
		m_mi_resume->Off ();
		m_yesnoMenu->Off ();

		m_bMenu = F;
		SetActive ( F );

		Menu::Off ();
	}

	void PauseMenu::On ()
	{
		m_grpStr_pause->SetValid ( T );
		m_cursor->SetValid ( T );

		m_mi_title->On ();
		m_mi_resume->On ();

		//yes_noは別で起動する
//		m_yesnoMenu->On ();

		m_bMenu = T;
		SetActive ( T );

		Menu::On ();
	}


	//表示
	void PauseMenu::UnDisp ()
	{
		m_grpStr_pause->SetValid ( F );
		m_cursor->SetValid ( F );

		m_mi_title->Off ();
		m_mi_resume->Off ();
		m_yesnoMenu->Off ();

		//全体稼働フラグは残す
		//m_bMenu = F;

		SetActive ( F );
	}

#if 0
	void PauseMenu::SetwpParent ( WP_FtgMain p )
	{
		m_mi_title->SetwpParent ( shared_from_this () );
		m_mi_resume->SetwpParent ( shared_from_this () );

		m_yesnoMenu->SetwpParent ( p );
	}
#endif // 0

	void PauseMenu::SetwpParentScene ( WP_Scene wp )
	{
		m_mi_title->SetwpParent ( shared_from_this () );
		m_mi_resume->SetwpParent ( shared_from_this () );
		m_yesnoMenu->SetwpParentScene ( wp );
	}

}	//namespace GAME

