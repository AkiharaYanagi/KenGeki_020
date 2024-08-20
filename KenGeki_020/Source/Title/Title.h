//=================================================================================================
//
//	タイトル イントロダクション対応
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Title : public Scene, public std::enable_shared_from_this < Title >
	{
		P_Grp		m_bg;
		P_Grp		m_menu;
		P_Grp		m_cursor;

		P_FadeRect	m_fade_in;
		P_FadeRect	m_fade_out;
		uint32		m_plus_wait { 0 };

#if 0
		P_PrmRect	m_fade_out;
		UINT		m_wait_out;

		P_PrmRect	m_fade_in;
		UINT		m_wait_in;

		P_PrmRect	m_rect;
		P_Grp		m_Start;
#endif // 0

		//シーン選択
		enum TITLE_TO
		{
			TITLE_TO_BATTLE,
			TITLE_TO_TRAINING,
		};

		TITLE_TO	m_to { TITLE_TO_BATTLE };

	public:
		Title ();
		Title ( const Title & rhs ) = delete;
		~Title ();

		void ParamInit ();

		void Move ();
		void Load ();

		P_GameScene Transit ();

	private:
		void Select ();
	};

	using P_Title = std::shared_ptr < Title >;


}	//namespace GAME

