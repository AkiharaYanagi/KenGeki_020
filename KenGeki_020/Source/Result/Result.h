//=================================================================================================
//
//	リザルト
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

	class Result : public Scene, public std::enable_shared_from_this < Result >
	{
		P_GrpMovie		m_mov;		//背景ムービー
		P_Grp			m_chara;	//キャラ画像
		P_Grp			m_state;	//ステート(数値群)
		P_Grp			m_Msg;		//メッセージ

		P_FadeRect		m_fade_in;
		P_FadeRect		m_fade_out;
		uint32			m_plus_wait { 0 };

	public:
		Result ();
		Result ( const Result & rhs ) = delete;
		~Result ();

		void Load ();
		void ParamInit ();

		void Move ();
		void Draw ();

		P_GameScene Transit ();

	};

	using P_Result = std::shared_ptr < Result >;


}	//namespace GAME

