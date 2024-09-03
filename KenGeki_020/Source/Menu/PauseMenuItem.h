//=================================================================================================
//
//	PauseMenuItem
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=========================================================
	class PauseMenu;
	using WP_PauseMenu = std::weak_ptr < PauseMenu >;

	//=========================================================
	//共通
	class PauseMenuItem : public Menu
	{
	public:
		virtual void Do () {}
		virtual void Decide () {}
	};

	using P_PauseMenuItem = std::shared_ptr < PauseMenuItem >;

	//=========================================================

	//タイトルに戻る
	class PMI_To_Title : public PauseMenuItem
	{
		P_MenuString	m_grpStr_title;
	public :
		PMI_To_Title ();
		PMI_To_Title ( const PMI_To_Title & rhs ) = delete;
		~PMI_To_Title ();

		void Do ();
		void Decide ();
		void Off ();
		void On ();
	};
	using P_PMI_To_Title = std::shared_ptr < PMI_To_Title >;

	//--------------------------------------------------------------
	//ゲームに戻る
	class PMI_ResumeGame : public PauseMenuItem
	{
		P_MenuString	m_grpStr_resume;
	public:
		PMI_ResumeGame ();
		PMI_ResumeGame ( const PMI_ResumeGame & rhs ) = delete;
		~PMI_ResumeGame ();

		void Do ();
		void Decide ();
		void Off ();
		void On ();
	};
	using P_PMI_ResumeGame = std::shared_ptr < PMI_ResumeGame >;

	//=========================================================

}	//namespace GAME

