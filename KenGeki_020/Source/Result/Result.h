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
		P_Grp	m_test;
//		std::unique_ptr < s3d::VideoTexture >		m_bg;

		P_GrpMovie		m_mov;

		P_Grp	m_chara;

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

