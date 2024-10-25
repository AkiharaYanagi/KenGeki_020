//=================================================================================================
//
//	PauseMenu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "PauseMenuItem.h"
#include "YesNo_Menu.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class PauseMenu : public Menu
	{
		//-----------------
		//稼働フラグ
		bool			m_bMenu { F };		//全体

		//見出文字
		P_MenuString	m_grpStr_pause;

		//メニュ内容
		P_PMI_To_Title		m_mi_title;
		P_PMI_ResumeGame	m_mi_resume;

		//カーソル
		P_Grp		m_cursor;
		float		m_cursor_scaling_vy { 0.05f };
		float		m_cursor_scaling_y { 1.f };


		//YNメニュ
		P_YesNo_Menu	m_yesnoMenu;

	public:
		PauseMenu ();
		PauseMenu ( const PauseMenu & rhs ) = delete;
		~PauseMenu ();

		void Load ();
		void Do ();
		void Move ();

		//メインMove()中でチェックしてtrueのとき他を処理しないでreturnする
		bool MenuCheck ();
		void Input ();

		//稼働
		void On ();
		void Off ();

		//表示
		void UnDisp ();

//		void SetwpParent ( WP_FtgMain p );
		void SetwpParentScene ( WP_Scene wp );

//		void OpenYNMenu () { m_yesnoMenu->On (); }

	private:
		static const float CURSOR_X;
		static const float CURSOR_Y;
		static const float CURSOR_SCL_VY;
	};


	using P_PauseMenu = std::shared_ptr < PauseMenu >;


}	//namespace GAME

