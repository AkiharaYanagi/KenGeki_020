﻿//=================================================================================================
//
//	Fighting ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/Scene.h"
#include "BG.h"
#include "../Mutual/MutualChara.h"
#include "FtgDemo_Actor.h"
#include "FtgGrp.h"
#include "BattleTime.h"
#include "Round.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Fighting : public TASK_LST, public std::enable_shared_from_this < Fighting >
	{
		//=====================================================
		//シーン共有パラメータ
		P_Param			m_pParam;

		//=====================================================
		//キャラ
		P_ExeChara		m_exeChara1;
		P_ExeChara		m_exeChara2;

		//キャラ相互処理
		P_MutualChara	m_mutualChara;

		//=====================================================
		//背景
		P_BG			m_bg;

		//=====================================================
		//デモ
		P_FtgDemoActor	m_demoActor;
		bool			m_demoSkip;	//スキップ

		//=====================================================
		//画面共通グラフィック処理
		P_FtgGrp		m_pFtgGrp ;

		//=====================================================
		//ステート名
		P_GrpStr		m_strState;
		bool			m_bDispStrState { F };
		bool			m_pre_bDispStrState { F };

		//-------------------------------------------------
		//戦闘時間
		P_BattleTime	m_btlTime;

		//-------------------------------------------------
		//ラウンド
		P_Round			m_round;

		//システム表示
		bool			m_bDispSys { F };
		bool			m_pre_bDispSys { F };

		//-------------------------------------------------
		//BGM名
		P_Grp			m_bgmName;

		//-------------------------------------------------
		//トレーニングモード
		bool			m_bTraining { F };

	public:
		Fighting ();
		Fighting ( const Fighting & rhs ) = delete;
		~Fighting ();

		void Init ();
		void Load ();
		void Move ();

		void ParamInit ( P_Param pParam );

		//デモ リスタート
		void DemoRestart ();

		//初期デモスキップ設定
		void SetDemoOn () { m_demoSkip = F; }
		void SetDemoSkip () { m_demoSkip = T; }

		//トレーニングモード
		void SetbTraining ( bool b ) { m_bTraining = b; }
		bool GetbTraining () const { return m_bTraining; }

		//トレーニング用リスタート
		void TrainingRestart ();

		//戦闘時間
		void StartTime ();			//時間計測開始
		void TimeSet ();			//時間計測初期化
		void StartTimeUp ();		//タイムアップ
		void StartEndWait ();		//タイムアップ終了待機

		void StopTimer ();			//タイマ停止

		//----------------
		//終了判定
		bool FinishCheck_ZeroLife ();	//格闘終了判定
		bool FinishCheck_TimeUp ();		//時間終了

		//時間終了時、残ライフで勝者決定(ラウンド反映)
		void DecideWinner_FromLife ();

#if 0
		//勝利デモ移行
		void WinnerDemo ();
#endif // 0

		//ラウンド取得
		void AddRound_1p () { m_round->AddRound_1p (); }
		void AddRound_2p () { m_round->AddRound_2p (); }

		//試合(マッチ)終了判定
		bool IsEndMutch () { return m_round->IsEndMutch (); }

		//終了
		bool IsEnd () const { return m_demoActor->IsEnd (); }
		bool IsDrawEnd () const { return m_demoActor->IsDrawEnd (); }

		//引分判定
		bool IsDraw () const;

#if 0
		//初期操作 プレイヤ/CPU 設定
		void Set_1P_vs_2P () { m_mutualChara->Set_1P_vs_2P (); }
		void Set_1P_vs_CPU () { m_mutualChara->Set_1P_vs_CPU (); }
		void Set_CPU_vs_CPU () { m_mutualChara->Set_CPU_vs_CPU (); }

		//壁割り演出
		void WallBreak_L () { m_bg->StartWallBreak_L (); }
		void WallBreak_R () { m_bg->StartWallBreak_R (); }

		//下位オブエジェクトにweak_ptrを渡す
//		void AssignWp ( WP_FTG wp ) const;

#endif // 0

		//システム表示 切替
		void SwitchDisp ();
		void OnDisp ();
		void OffDisp ();

		void SwitchDispStrState ();


		//タイマ切替
		void SetActiveTimer ( bool b ) { m_btlTime->SetActive ( b ); }

		//トレーニングモード設定
		void SetTraining ()
		{
			m_mutualChara->SetTraining ();
			m_btlTime->SetTraining ();
		}


	private:
		//共通グラフィック処理
		void Grp ();

		static const float BGM_X;
		static const float BGM_Y;
	};

	using P_FTG = std::shared_ptr < Fighting >;


}	//namespace GAME


