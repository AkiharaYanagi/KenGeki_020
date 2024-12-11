//=================================================================================================
//
//	MutualChara ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../FtgConst.h"
#include "../../GameMain/Param.h"
#include "../../ExeChara/Main/ExeChara.h"
#include "Collision.h"
#include "Decision.h"
#include "../Fighting/FtgGrp.h"
#include "MutualChara_Utility.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class MutualChara : public TASK_VEC
	{
		//シーン共有パラメータ
		P_Param			m_pParam;

		//キャラ(参照)
		P_ExeChara		m_exeChara1;
		P_ExeChara		m_exeChara2;

		//判定クラス
		P_Collision		m_collision;
		P_Decision		m_decision;

		//-------------------------------------------------
		//勝者
		WINNER	m_winner { WINNER::WINNER_DRAW };

	public:
		MutualChara ();
		MutualChara ( const MutualChara & rhs ) = delete;
		~MutualChara ();

		//----------------------------------------------------
		void SetpChara ( P_ExeChara p1, P_ExeChara p2 );

		void ParamInit ( P_Param pParam );
		void Load ();
		void Init ();

		//スクリプトの毎フレーム処理
		void Conduct ();
		void Conduct_InDemo ();	//デモ中コンダクト
		void Conduct_InStop ();	//一時停止コンダクト


		//----------------------------------------------------
		//状態取得
		BtlParam	GetBtlPrm1p () const { return m_exeChara1->GetBtlPrm (); }
		BtlParam	GetBtlPrm2p () const { return m_exeChara2->GetBtlPrm (); }

		//----------------------------------------------------
		//状態変更
		void StartGreeting ();		//開始デモ
		void StartGetReady ();		//開始準備
		void StartFighting ();		//戦闘開始

		void WallBreak_Action ( PLAYER_ID id );	//壁割後のアクション指定
		void ShiftFightingMain ();		//戦闘通常状態に戻る
		void ShiftFightingMain_PreScriptMove ();		//戦闘通常状態に戻る
		void ShiftScpStop ();		//一時停止
		void RestoreScpStop ();		//一時停止からの復旧

		void EndBattle ();			//戦闘終了
		void ResetRect ();			//枠リセット
		void StartEndWait ();		//終了待機
		bool IsDown_Calm ();		//敗北ダウン安定状態
		void StartWinner ();		//勝者表示

		//----------------
		//演出

		//共通グラフィック
//		void SetpFtgGrp ( P_FtgGrp p ) { m_pFtgGrp = p; }

		bool IsWait ();	//両者待機状態


		//トレーニングモード設定
		void SetTraining ();

		//トレーニングモード初期化
		void TrainingInit ();


	private:
		//------------------------------------------------------
		//	内部関数
		//------------------------------------------------------

		//関数群
		MutualChara_Utility			m_utl;

		//サブルーチン
		void SystemChange ();		//システム変更
		void SaveParam();			//パラメータ記録

	};

	using P_MutualChara = std::shared_ptr < MutualChara >;


}	//namespace GAME


