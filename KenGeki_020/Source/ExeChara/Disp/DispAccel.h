﻿//=================================================================================================
//
// DispAccel ヘッダファイル
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

	class DispAccel : public TASK_VEC
	{
		PLAYER_ID	m_playerID {_PLAYER_NUM };		//プレイヤ表示側

		P_Grp	m_gaugeAccel;		//アクセルゲージ
		P_Grp	m_gaugeAccelHand;	//アクセルゲージ

	public:
		DispAccel ();
		DispAccel ( const DispAccel & rhs ) = delete;
		~DispAccel ();

		//プレイヤ別(1p,2p)のゲージ類の表示部のみ初期化
		void LoadPlayer ( PLAYER_ID playerID );

		//更新
		void Update ( int value );

		//表示切替
		void On ();
		void Off ();

	private:
		static const float BG_POS_X_1P;
		static const float BG_POS_X_2P;
		static const float BG_POS_Y;

		static const float HND_POS_X_1P;
		static const float HND_POS_X_2P;
		static const float HND_POS_Y;
		static const float HND_ROT_X;
		static const float HND_ROT_Y;

		static const float Z_GAUGE_ACCEL;
	};


	using P_DispAccel = std::shared_ptr < DispAccel >;


}	//namespace GAME

