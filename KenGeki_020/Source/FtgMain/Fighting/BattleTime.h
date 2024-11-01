//=================================================================================================
//
//	BattleTime ヘッダファイル
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
	class BattleTime : public TASK_VEC
	{
		bool		m_active { F };		//稼働状態

		P_Grp		m_time_bg;			//背景
		P_Grp		m_battle_time;		//共通テクスチャ
		P_Ob		m_battle_time_01;	//1の桁
		P_Ob		m_battle_time_02;	//10の桁
		int			m_time { START_TIME };	// 3600 ～ 0 [F] ( 60 ～ 0[Sec] )

		int			m_startTime { 0 };	//リセット時の開始時間

	public:
		BattleTime ();
		BattleTime ( const BattleTime & rhs ) = delete;
		~BattleTime ();

		void Init ();
		void Move ();

		void Set ();
		void Start ()
		{ m_active = T; }
		void Stop () { m_active = F; }

		void DispTime ();

		bool IsTimeUp ();

		void On ();
		void Off ();

		void SetActive ( bool b ) { m_active = b; }

		void SetTraining ();

	private:
		static const int START_TIME;

	};

	using P_BattleTime = std::shared_ptr < BattleTime >;


}	//namespace GAME


