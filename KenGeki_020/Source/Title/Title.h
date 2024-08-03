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
		P_PrmRect	m_rect;
		P_Grp		m_bg;
		P_Grp		m_Start;

		P_PrmRect	m_fade_in;
		UINT		m_wait_in;

		P_PrmRect	m_fade_out;
		UINT		m_wait_out;

	public:
		Title ();
		Title ( const Title & rhs ) = delete;
		~Title ();

		void ParamInit ();

		void Move ();
		void Load ();

		P_GameScene Transit ();

	};

	using P_Title = std::shared_ptr < Title >;


}	//namespace GAME

