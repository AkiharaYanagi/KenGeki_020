//=================================================================================================
//
//	ExeChara アクタ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "ExCh_State.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class ExeChara_Actor
	{
		//ステート
		P_CHST_Start		m_Start;
		P_CHST_Greeting		m_Greeting;
		P_CHST_GetReady		m_GetReady;

		P_CHST_Main			m_Main;

		P_CHST_ScpStop		m_ScpStop;
		P_CHST_WallBreak	m_WallBreak;
		P_CHST_Slow_Skip	m_Slow_Skip;

		P_CHST_EndWait		m_EndWait;
		P_CHST_Down			m_Down;
		P_CHST_DownWait		m_DownWait;
		P_CHST_WinWait		m_WinWait;
		P_CHST_Win			m_Win;
		P_CHST_WinEnd		m_WinEnd;
		P_CHST_TimeUp		m_TimeUp;

		//ステート監理
		VP_ExeChara_State	mvp_state;

		//現在ステート
		P_ExeChara_State	mp_state;

		//共通パラメータ
		P_ExeChara_Param	mp_param;

	public:
		ExeChara_Actor ();
		ExeChara_Actor ( const ExeChara_Actor & rhs ) = delete;
		~ExeChara_Actor () {}

		void Init ();

		void SetwpExeChara ( WP_ExeChara p ) { mp_param->SetwpExeChara ( p ); }

		P_ExeChara_State GetpState () { return mp_state; }
		s3d::String GetStateName () { return mp_state->GetName(); }

		//状態変更	(Start()を実行する)
		void StartGreeting ();
		void StartGetReady ();
		void StartFighting ();
		void StartTimeUp ();
		void StartEndWait ();
		void StartDown ();

		void StartWinner ();

		//メイン中一時遷移		(Start()を実行しない)
		void ShiftFighting ();
		void ShiftScpStop ();
		void ShiftSlowSkip ();
		void ShiftWallBreak ();


		//==========================================================
		//MutualCharaから呼ばれる主な関数
		//==========================================================
		//	↓ 処理順番
		//	void ExeChara::PreScriptMove ();	//	スクリプト前処理
		//	void MutualChara::Collision ();		//	相互判定 (接触枠)
		//	void ExeChara::RectMove ();	//	ぶつかり後、判定枠を設定
		//	void MutualChara::Decision ();		//	相互判定 (攻撃枠、ヒット枠)
		//	void ExeChara::PostScriptMove ();	//	スクリプト後処理
		void PreScriptMove ();
		void RectMove ();
		void PostScriptMove ();

		//Decision()の最初に呼ばれ、処理をスキップするかどうか
		bool SkipDecision () const { return mp_state->SkipDecision (); }
	};


}	//namespace GAME

