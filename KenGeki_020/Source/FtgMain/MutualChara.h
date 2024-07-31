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
#include "FtgConst.h"
#include "../GameMain/Param.h"
#include "../ExeChara/Main/ExeChara.h"
#include "Collision.h"
#include "Decision.h"
#include "FtgGrp.h"
#include "BattleTime.h"
#include "Round.h"
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
		//ファイティング：1p2p共通スクリプト処理
		UINT	m_scpStop {0};		//スクリプトからのストップ

		//特殊演出
#if 0
		UINT	m_blackOut {0};		//暗転
		bool	m_whiteOut { F };	//白転
		UINT	m_slow { 0 };		//スロー
#endif // 0

		//共通グラフィック
		P_FtgGrp	m_pFtgGrp;


		//test 動画
		std::unique_ptr < s3d::VideoTexture > mp_vtx;



		//-------------------------------------------------
		//勝者
		WINNER	m_winner { WINNER::WINNER_DRAW };

		//-------------------------------------------------
		//戦闘時間
		P_BattleTime	m_btlTime;
		//-------------------------------------------------
		//ラウンド
		P_Round		m_round;

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
		void Grp ();			//グラフィック共通
#if 0
		void Conduct_InStop ();	//停止コンダクト
#endif // 0


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
		void Shift_Fighting ();		//戦闘通常状態に戻る

		//----------------------------------------------------
		//戦闘時間
		void StartTime ();			//時間計測開始
		void TimeSet ();			//時間計測初期化
		void StartTimeUp ();		//タイムアップ
		void StartEndWait ();		//タイムアップ終了待機
		void StartEnd ();			//終了ステップ開始


		//----------------
		//終了判定
		bool FinishCheck_ZeroLife ();	//格闘終了判定
		bool FinishCheck_TimeUp ();		//時間終了

		//残ライフで勝者決定
		void DecideWinner_FromLife ();

		//試合(マッチ)終了判定
		bool IsEndMutch () { return m_round->IsEndMutch (); }

		//----------------
		//演出

		//共通グラフィック
		void SetpFtgGrp ( P_FtgGrp p ) { m_pFtgGrp = p; }

		bool IsWait ();	//両者待機状態

#if 0
		UINT GetBlackOut () const { return m_blackOut; };	//暗転
		void SetBlackOut ( UINT i )
		{
			m_blackOut = i;
			m_exeChara1->SetBlackOut ( i );
			m_exeChara2->SetBlackOut ( i );
		};

		UINT GetScpStop () const { return m_scpStop; };	//停止
		void SetScpStop ( UINT i ) { m_scpStop = i; };

		void RevertSlow ();	//スロウ解除
#endif // 0

#if 0
		bool CheckZeroLife ();	//格闘終了判定

		//特殊演出
		bool CheckWhiteOut () const { return m_whiteOut; }
		void SetWhiteOut ( bool b ) { m_whiteOut = b; }

		//初期操作 プレイヤ/CPU 設定
		void Set_1P_vs_2P ();
		void Set_1P_vs_CPU ();
		void Set_CPU_vs_CPU ();

		//勝者
		WINNER GetWinner () const { return m_winner; }
		CHARA_NAME GetWinnerName () const;

#endif // 0

		//トレーニングモード初期化
		void TrainingInit ();


	private:
		//------------------------------------------------------
		//	内部関数
		//------------------------------------------------------

		//関数群
		MutualChara_Utility			m_utl;

		void SaveParam();			//パラメータ記録

	};

	using P_MutualChara = std::shared_ptr < MutualChara >;


}	//namespace GAME


