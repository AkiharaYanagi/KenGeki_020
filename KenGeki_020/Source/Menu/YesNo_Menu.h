//=================================================================================================
//
//	YesNo_Menu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Menu.h"
#include "PauseMenuItem.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//前方宣言
	class YesNo_Menu;	using WP_YesNo_Menu = std::weak_ptr < YesNo_Menu >;
	class Scene;	using WP_Scene = std::weak_ptr < Scene >;

	//===================================================
	//メニュ項目
	class YNM_Item_Yes : public Menu
	{
		WP_Scene	mwp_Scene;

	public:
		void Decide ();	//決定　タイトルに戻る
		void SetwpParentScene ( WP_Scene wp ) { mwp_Scene = wp; }

	};
	using P_YNM_Item_Yes = std::shared_ptr < YNM_Item_Yes >;


	class YNM_Item_No : public Menu
	{
	public: 
		void Decide ();	//キャンセル 自メニュを閉じる
	};
	using P_YNM_Item_No = std::shared_ptr < YNM_Item_No >;



	//===================================================
	// Y_N_メニュ
	class YesNo_Menu : public Menu
	{
		P_MenuString	m_grpStr_yesno;

		//カーソル
		P_Grp			m_cursor;
		float		m_cursor_scaling_vy{ 0.05f };
		float		m_cursor_scaling_y{ 1.f };

		P_MenuString	m_grpStr_yes;
		P_MenuString	m_grpStr_no;

		//メニュ項目
		P_YNM_Item_Yes	m_yes;
		P_YNM_Item_No	m_no;

		//開始後1[F]待つ
		bool			m_wait { F };

	public:
		YesNo_Menu ();
		YesNo_Menu ( const YesNo_Menu & rhs ) = delete;
		~YesNo_Menu ();

		void Load ();
		void Init ();
		void Move ();

		void On ();
		void Off ();

		void SetwpParentScene ( WP_Scene wp );

	private:
		static const float BG_X;
		static const float BG_Y;
		static const float BG_W;
		static const float BG_H;
		static const float CAPTION_X;
		static const float CAPTION_Y;
		static const float YES_X;
		static const float YES_Y;
		static const float NO_X;
		static const float NO_Y;
		static const float CURSOR_X;
		static const float CURSOR_Y;
		static const float CURSOR_P;
	};

	using P_YesNo_Menu = std::shared_ptr < YesNo_Menu >;



}	//namespace GAME

