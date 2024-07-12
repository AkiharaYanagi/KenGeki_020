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
//#include "Fighting.h"
//#include "G_Ftg.h"
//#include "FtgGrp.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
//	using WP_FTG = std::weak_ptr < Fighting >;


	class MutualChara : public TASK_VEC
	{
		//シーン共有パラメータ
		P_Param			m_pParam;

		//キャラ
		P_ExeChara		m_exeChara1;
		P_ExeChara		m_exeChara2;

		//判定クラス
		P_Collision		m_collision;
		P_Decision		m_decision;

#if 0
		//-------------------------------------------------
		//ファイティング：1p2p共通スクリプト処理
		UINT	m_scpStop {0};		//スクリプトからのストップ
		P_Timer	m_tmrHitstop;		//ヒットストップ

		//特殊演出
		UINT	m_blackOut {0};		//暗転
		bool	m_whiteOut { F };	//白転
		UINT	m_slow { 0 };		//スロー

		P_FtgGrp	m_pFtgGrp;

		//-------------------------------------------------
		//勝者
		WINNER	m_winner { WINNER::WINNER_DRAW };

#endif // 0

	public:
		MutualChara ();
		MutualChara ( const MutualChara & rhs ) = delete;
		~MutualChara ();

		void ParamInit ( P_Param pParam );
		void Load ();
		void Init ();

		//スクリプトの毎フレーム処理
		void Conduct ();
		void Grp ();			//グラフィック共通
#if 0
		void Conduct_InStop ();	//停止コンダクト
#endif // 0

#if 0

		//状態取得
		BtlParam	GetBtlPrm1p () const { return m_exeChara1->GetBtlPrm (); }
		BtlParam	GetBtlPrm2p () const { return m_exeChara2->GetBtlPrm (); }

		//状態変更
		void StartGreeting ();		//開始デモ
		void StartGetReady ();		//開始準備
		void StartFighting ();		//戦闘開始

		bool CheckZeroLife ();	//格闘終了判定

		UINT GetBlackOut () const { return m_blackOut; };	//暗転
		void SetBlackOut ( UINT i )
		{
			m_blackOut = i;
			m_exeChara1->SetBlackOut ( i );
			m_exeChara2->SetBlackOut ( i );
		};

		UINT GetScpStop () const { return m_scpStop; };	//停止
		void SetScpStop ( UINT i ) { m_scpStop = i; };

		void RevertSlow ();	//状態を元に戻す


		//特殊演出
		bool CheckWhiteOut () const { return m_whiteOut; }
		void SetWhiteOut ( bool b ) { m_whiteOut = b; }

		void SetpFtgGrp ( P_FtgGrp p ) { m_pFtgGrp = p; }

		//トレーニングモード初期化
		void TrainingInit ();

		
		//初期操作 プレイヤ/CPU 設定
		void Set_1P_vs_2P ();
		void Set_1P_vs_CPU ();
		void Set_CPU_vs_CPU ();


		//勝者
		WINNER GetWinner () const { return m_winner; }
		CHARA_NAME GetWinnerName () const;

		//下位オブエジェクトにweak_ptrを渡す
//		void AssignWp ( WP_FTG wp ) const;


#endif // 0
	private:
		//------------------------------------------------------
		//	内部関数
		//------------------------------------------------------


		void _Collision ();		//重なり判定
		void _Decision ();		//攻撃判定

		//---------------------------------------
		// Conduct
		
		void SwitchRect ();			//枠表示切替
		void SwitchDispInput ();	//入力表示切替
		void SwitchFrontEnd ();		//ゲージ類表示切替
		void SwithcCPU ();			//2PをCPU操作切替
		void ResetMatch ();			//試合初期化

	};

	using P_MutualChara = std::shared_ptr < MutualChara >;


}	//namespace GAME


