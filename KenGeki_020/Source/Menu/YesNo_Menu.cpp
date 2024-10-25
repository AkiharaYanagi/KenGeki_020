//=================================================================================================
//
//	YesNo_Menu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "YesNo_Menu.h"
#include "../GameMain/Scene.h"
#include "PauseMenu_Const.h"
#include "../GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const float YesNo_Menu::BG_X = (GAME_WINDOW_WIDTH * 0.5f) - (BG_W * 0.5f);
	const float YesNo_Menu::BG_Y = 400;
	const float YesNo_Menu::BG_W = 500;
	const float YesNo_Menu::BG_H = 200;

	const float YesNo_Menu::CAPTION_X = GAME_WINDOW_WIDTH * 0.5f - 190;
	const float YesNo_Menu::CAPTION_Y = BG_Y;

	const float YesNo_Menu::YES_X = BG_X + 100;
	const float YesNo_Menu::YES_Y = 400;
	const float YesNo_Menu::NO_X = YES_X + CURSOR_P;
	const float YesNo_Menu::NO_Y = 200;

	const float YesNo_Menu::CURSOR_X = BG_X + 20;
	const float YesNo_Menu::CURSOR_Y = 530;
	const float YesNo_Menu::CURSOR_P = 210;

	//===================================================
	//決定　タイトルに戻る
	void YNM_Item_Yes::Decide ()
	{
		//BGM
		SND_PLAY_ONESHOT_SE(SE_select_decide);
		SND_STOP_ALL_BGM ();
		mwp_Scene.lock()->Transit_Title ();
	}

	//キャンセル 自メニュを閉じる
	void YNM_Item_No::Decide ()
	{
		SND_PLAY_ONESHOT_SE(SE_select_Cancel);
		P_YesNo_Menu p = std::dynamic_pointer_cast <YesNo_Menu> ( mwp_Parent.lock () );
		p->Off ();
	}


	//===================================================

	YesNo_Menu::YesNo_Menu ()
	{
		//--------------------------------------------
		//基本背景
		Menu::SetBG_use ( T );
		Menu::SetBG_Size ( BG_W, BG_H );
		Menu::SetBG_Pos ( BG_X, BG_Y );
		Menu::SetBG_Color ( _CLR ( 0xd0000000 ) );
		Menu::SetBG_Z ( Z_MENU_YN_BG );

		//見出
		m_grpStr_yesno = std::make_shared < MenuString > ();
		m_grpStr_yesno->SetbMenu ( T );
		m_grpStr_yesno->SetStr ( U"- 終了します -" );
		m_grpStr_yesno->SetZ ( Z_MENU_YN_STR );
		AddpTask ( m_grpStr_yesno );
		GRPLST_INSERT ( m_grpStr_yesno );

		m_grpStr_yes = std::make_shared < MenuString > ();
		m_grpStr_yes->SetbMenu ( T );
		m_grpStr_yes->SetStr ( U"はい" );
		m_grpStr_yes->SetZ ( Z_MENU_YN_STR );
		AddpTask ( m_grpStr_yes );
		GRPLST_INSERT ( m_grpStr_yes );

		m_grpStr_no = std::make_shared < MenuString > ();
		m_grpStr_no->SetbMenu ( T );
		m_grpStr_no->SetStr ( U"いいえ" );
		m_grpStr_no->SetZ ( Z_MENU_YN_STR );
		AddpTask ( m_grpStr_no );
		GRPLST_INSERT ( m_grpStr_no );

		//--------------------------------------------
		m_cursor = std::make_shared < GameGraphic > ();
		m_cursor->AddTexture_FromArchive(U"Title\\title_cursor.png");
		m_cursor->SetPos ( CURSOR_X, CURSOR_Y );
		m_cursor->SetZ ( Z_MENU_YN_STR );
		m_cursor->SetScalingCenter ( 0, 12.5f );
		AddpTask ( m_cursor );
		GRPLST_INSERT ( m_cursor );

		//--------------------------------------------
		//メニュー項目
		m_yes = std::make_shared < YNM_Item_Yes > ();
		m_no = std::make_shared < YNM_Item_No > ();

		//--------------------------------------------
		Off ();
		//On ();
	}

	YesNo_Menu::~YesNo_Menu ()
	{
	}

	void YesNo_Menu::Load ()
	{
		Menu::SetpMenuItem ( m_yes );
		Menu::SetpMenuItem ( m_no );
		Menu::Load ();
	}

	void YesNo_Menu::Init ()
	{
		m_grpStr_yesno->SetPos (CAPTION_X, CAPTION_Y);
		m_grpStr_yes->SetPos ( YES_X, BG_Y + 100 );
		m_grpStr_no->SetPos ( NO_X, BG_Y + 100 );

		Menu::Init ();
	}

	void YesNo_Menu::Move ()
	{
		//非アクティブ時は何もしない
		if ( ! GetActive () ) { Menu::Move (); return; }

		//選択
		if ( CFG_PUSH_KEY ( P1_RIGHT ) || CFG_PUSH_KEY ( P2_RIGHT ) )
		{
			SND_PLAY_ONESHOT_SE(SE_select_move);
			Menu::Next ();
		}
		if ( CFG_PUSH_KEY ( P1_LEFT ) || CFG_PUSH_KEY ( P2_LEFT ) )
		{
			SND_PLAY_ONESHOT_SE(SE_select_move);
			Menu::Prev ();
		}

		//ON後１[F]待つ
		if ( m_wait )
		{
			//決定
			if ( CFG_PUSH_KEY ( P1_BTN0 ) || CFG_PUSH_KEY ( P2_BTN0 ) )
			{
				Menu::Decide ();
			}
		}
		m_wait = T;

		//カーソル回転
		m_cursor_scaling_y += m_cursor_scaling_vy;
		if (m_cursor_scaling_y >= 1.f) { m_cursor_scaling_vy = -0.1f; }
		if (m_cursor_scaling_y <= -1.f) { m_cursor_scaling_vy = 0.1f; }
		m_cursor->SetScaling(1.f, m_cursor_scaling_y);

		//カーソル位置
		m_cursor->SetPos ( CURSOR_X + CURSOR_P * Menu::GetIdItem (), CURSOR_Y );


		Menu::Move ();
	}

	void YesNo_Menu::On ()
	{
		m_grpStr_yesno->SetValid ( T );
		m_grpStr_yes->SetValid ( T );
		m_grpStr_no->SetValid ( T );
		m_cursor->SetValid ( T );
		SetActive ( T );

		m_wait = F;
		Menu::On();
	}

	void YesNo_Menu::Off ()
	{
		m_grpStr_yesno->SetValid ( F );
		m_grpStr_yes->SetValid ( F );
		m_grpStr_no->SetValid ( F );
		m_cursor->SetValid ( F );
		SetActive ( F );
		m_wait = F;
		Menu::Off ();
	}

#if 0
	void YesNo_Menu::SetwpParent ( WP_FtgMain p )
	{
		m_yes->SetpFtgMain ( p );
		m_no->SetwpParent ( shared_from_this () );
	}
#endif // 0
	void YesNo_Menu::SetwpParentScene ( WP_Scene wp )
	{
		m_yes->SetwpParentScene ( wp );
		m_no->SetwpParent ( shared_from_this () );
	}


}	//namespace GAME

