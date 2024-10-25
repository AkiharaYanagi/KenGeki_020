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
#include "../GameMain/SoundConst.h"
#include "PauseMenu_Const.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//===================================================
	//決定　タイトルに戻る
	void YNM_Item_Yes::Decide ()
	{
		//BGM
		SND_STOP_ALL_BGM ();
		mwp_Scene.lock()->Transit_Title ();
	}

	//キャンセル 自メニュを閉じる
	void YNM_Item_No::Decide ()
	{
		P_YesNo_Menu p = std::dynamic_pointer_cast <YesNo_Menu> ( mwp_Parent.lock () );
		p->Off ();
	}


	//===================================================

	YesNo_Menu::YesNo_Menu ()
	{
		//--------------------------------------------
		//基本背景
#if 0
		m_bg = std::make_shared < PrmRect > ();
		m_bg->SetSize ( 500, 200 );
		m_bg->SetColor ( 0x80000000 );
		float center = GAME_WINDOW_WIDTH * 0.5f;
		m_bg->SetPos ( (int32)(center - (m_bg->GetSize().x * 0.5f)), 400 );
		m_bg->SetZ ( Z_MENU_YN_BG );
		AddpTask ( m_bg );
//		GRPLST_INSERT ( m_bg );
#endif // 0
		Menu::SetBG_use ( T );
		Menu::SetBG_Size ( 500, 200 );
		float center = GAME_WINDOW_WIDTH * 0.5f;
		Menu::SetBG_Pos ( center - (500 * 0.5f), 400 );
		Menu::SetBG_Color ( _CLR ( 0xd0000000 ) );

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
		m_cursor->AddTexture_FromArchive ( U"title_cursor.png" );
		m_cursor->SetPos ( 380, 500 );
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
		const float center = GAME_WINDOW_WIDTH * 0.5f;
		const float by = 400;
		m_grpStr_yesno->SetPos ( center - 140, by );
		m_grpStr_yes->SetPos ( 510, by + 100 );
		m_grpStr_no->SetPos ( 720, by + 100 );

		Menu::Init ();
	}

	void YesNo_Menu::Move ()
	{
		//非アクティブ時は何もしない
		if ( ! GetActive () ) { Menu::Move (); return; }

		//選択
		if ( CFG_PUSH_KEY ( P1_RIGHT ) || CFG_PUSH_KEY ( P2_RIGHT ) )
		{
			Menu::Next ();
		}
		if ( CFG_PUSH_KEY ( P1_LEFT ) || CFG_PUSH_KEY ( P2_LEFT ) )
		{
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

		//カーソル位置
		m_cursor->SetPos ( 380.f + 210 * Menu::GetIdItem (), 500.f );

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
	}

	void YesNo_Menu::Off ()
	{
		m_grpStr_yesno->SetValid ( F );
		m_grpStr_yes->SetValid ( F );
		m_grpStr_no->SetValid ( F );
		m_cursor->SetValid ( F );
		SetActive ( F );
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

