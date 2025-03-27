//=================================================================================================
//
// エグゼキャラ　ヘッダファイル
//		キャラのデータを受けてゲーム上で実行（フレーム毎動作、描画）する
//		操作時の位置などを保存する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

#include "../../GameMain/GameConst.h"
#include "../../GameMain/Param.h"
#include "../../FtgMain/FtgConst.h"
#include "../../FtgMain/Fighting/FtgGrp.h"

#include "CharaData.h"
#include "../Disp/DispChara.h"
#include "../BtlParam.h"
#include "../Rect/CharaRect.h"
#include "ExCh_Actor.h"

#include "../Input/PlayerInput.h"
#include "../Input/CPUInput.h"
#include "../Input/NewCPUInput.h"

#include "../Effect/OperateEffect.h"
#include "../../FtgMain/Ef/EfSouha.h"
//#include "../FtgMain/Ef/EfPart.h"

#if 0
#include "TimerSlow.h"
#endif // 0


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	//前方宣言
	class ExeChara;
	using P_ExeChara = std::shared_ptr < ExeChara >;
	using WP_ExeChara = std::weak_ptr < ExeChara >;

	class Fighting;
	using WP_FTG = std::weak_ptr < Fighting >;
	//------------------------------------------------

	//定数
	constexpr UINT32 CLR_LOOP_NUM { 8 };




	//キャラ実行 クラス
	class ExeChara : public TASK_VEC, public std::enable_shared_from_this < ExeChara >
	{
		//------------------------------------------------
		//基本データ
		P_Chara			m_pChara;		//キャラデータ
		WP_ExeChara		m_pOther;		//相手キャラ(循環参照なのでweak_ptr)

		PLAYER_MODE		m_playerMode { MODE_PLAYER };	//プレイヤーモード(人,CPU,ネットワーク)
		CHARA_NAME		m_name { CHARA_TEST };			//キャラ名

		//------------------------------------------------
		//パラメータ
		BtlParam		m_btlPrm;		//バトルパラメータ	

		//シーン共有パラメータ
		P_Param			m_pParam;

		//------------------------------------------------
		//表示
		P_DispChara		m_dispChara;	//キャラ全般表示
		P_FtgGrp		m_pFtgGrp;		//全体画像処理

		//------------------------------------------------
		//ゲーム進行状態(アクタ, ステートを保持する)
		//ExeChara_Actor	m_actor;
		P_ExeChara_Actor	m_pActor;	//shared_from_this()のためにポインタでオブジェクトを保持	

		//------------------------------------------------
		//スクリプト実行
		UINT			m_actionID { 0 };	//実効現在アクションID
		P_Action		m_pAction;			//実効アクションポインタ
		UINT			m_frame { 0 };		//実効内部フレーム(スクリプトID)
		P_Script		m_pScript;			//実効スクリプトポインタ


		//------------------------------------------------
		//枠
		P_CharaRect		m_charaRect;	//枠セット

		//------------------------------------------------
		//入力
		P_CharaInput	m_pCharaInput;	//入力
		P_PlayerInput	m_pPlayerInput;	//プレイヤ
		P_CPUInput		m_pCPUInput;	//CPU
		P_NewCPUInput	m_pNewCPUInput;	//New_CPU

		//------------------------------------------------
		//エフェクト監理
		P_OprEf			m_oprtEf;

		//------------------------------------------------
		//自身変更指定の一時保存
		//ヒット時など相手を変更するときに判定後、1P2P同時に適用する
		s3d::String		m_nameChangeMine;	//変更する自身のアクション名 

		//相手変更指定の一時保存
		//ヒット時など相手を変更するときに判定後、1P2P同時に適用する
		s3d::String		m_nameChangeOther;	//変更する相手のアクション名 

		//------------------------------------------------
		//剣撃走破
		P_EfSouha		m_efSouha;

	public:
		ExeChara () = delete;
		ExeChara ( PLAYER_ID m_playerID );	//プレイヤID指定コンストラクタのみ
		ExeChara ( const ExeChara & rhs ) = delete;
		~ExeChara ();

		//===========================================================
		//基本タスク関数　＆　初期化関連
	public:
		void ParamInit ( P_Param pParam );
		void Load ();
		void Init ();

	private:
		//初期化
		void LoadCharaData ();
		void LoadCharaData_test ();
		void LoadInput ();
		//===========================================================

	public:
		//===========================================================
		//***********************************************************
		//	毎フレームMutualCharaから呼ばれる主なスクリプト処理関数の一連
		//***********************************************************
		//	↓ 処理順番
		void PreScriptMove ();			//	スクリプト前処理
		//MutualChara::Collision ();	//	相互判定 (接触枠)
		void RectMove ();				//	ぶつかり後、判定枠を設定
		//MutualChara::Decision ();		//	相互判定 (攻撃枠、ヒット枠)
		void PostScriptMove ();			//	スクリプト後処理
		//===========================================================


		//===========================================================
		//***********************************************************
		//Stateから呼ばれる状態別処理
		//***********************************************************
		//PreScriptMove
		void Input ();				//入力処理
		void TransitAction ();		//アクション移項
		void CalcPos ();			// 位置計算		//ぶつかり後、位置の修正
		void Generate_Effect ();	//スクリプト処理 前 エフェクト生成
		void Generate_Effect_once ();	//スクリプト処理 前 エフェクト生成 １回のみ
		void PreMove_Effect ();		//スクリプト処理 前 エフェクト動作

		//PostScriptMove
		void BtlPrm_Move_Input ();	//バトルパラメータ入力処理
		void PostMove_Effect ();	//スクリプト処理 後 エフェクト動作
		void MoveTimer ();			//タイマ稼働
		void CheckLife ();			//ライフ判定
		void UpdateGraphic ();		//グラフィック更新
		void SoundPlay ();			//音の再生(SE, VC)
		//===========================================================

		void SE_Play ();			//SE再生
		void VC_Play ();			//VC再生

		//------------------------------------------------------------
		//相手を設定
		void SetpOther ( WP_ExeChara p ) { m_pOther = p; }

		//全体画像処理を設定
		void SetpFtgGrp ( P_FtgGrp p ) { m_pFtgGrp = p; }

		//---------------------------------------------

#if 0
		//------------------------------------------------
		//エフェクト

		//エフェクトリスト取得
		PLP_ExEf GetplpExEf () { return m_oprtEf->GetplpExEf (); }

		//粒子エフェクト
		void SetpParticle ( P_EfPart p ) { m_efPart = p; }
#endif // 0

		//===========================================================
		//枠
	public:
		P_CharaRect GetpCharaRect () const { return m_charaRect; }		//枠取得


		void SetCollisionRect ();	//[PreMove] 位置から接触枠設定
		void SetRect ();			//[PostMove] 相殺・攻撃・当り 枠設定
		void ResetRect ();			//リセット
	private:
		void SetOffsetRect ();	//相殺枠設定
		void SetAttackRect ();	//攻撃枠設定
		void SetHitRect ();		//当り枠設定
		//===========================================================


//==========================================================================
// ExeChara_Event.cpp
//==========================================================================

	public:
		//----------------------
		// 外部からの状態確認
		//----------------------

		//各値取得
		PLAYER_ID GetPlayerID () const { return m_btlPrm.GetPlayerID (); }
		bool IsPlayerID ( PLAYER_ID id ) { return m_btlPrm.GetPlayerID () == id; }
		bool Is1P () const { return m_btlPrm.Is1P(); }
		bool Is2P () const { return m_btlPrm.Is2P(); }
		CHARA_NAME GetCharaName () const { return m_name; }

		P_Action GetpAction () const { return m_pAction; }
		P_Script GetpScript () const { return m_pScript; }
		ACTION_POSTURE GetPosture () const { return m_pAction->GetPosture (); }

		//パラメータ
		//@todo スクリプトの持つ　ScriptParam_Battle と ExeCharaの持つ実効値 BtlPrm の整理
		BtlParam GetBtlPrm () const { return m_btlPrm; }

		void SetPos ( VEC2 v ) { m_btlPrm.SetPos ( v ); }
		VEC2 GetPos () const { return m_btlPrm.GetPos (); }		//位置を取得
		bool GetDirRight () const { return m_btlPrm.GetDirRight (); }	//向きを取得
		void SetDirRight ( bool b ) { m_btlPrm.SetDirRight ( b ); }		//立ち状態で向きを設定

		void BackPtX () { m_btlPrm.BackPtX (); }		//一つ前の位置に戻す
		void BackMoveX () { m_btlPrm.BackMoveX (); }	//重なりが解消されるまで位置に戻す
		void LookOther () { m_btlPrm.LookOther (); }	//相手の方向を向く

		int GetLife () const { return m_btlPrm.GetLife (); }		//ライフ取得
		//ライフ０チェック
		bool IsZeroLife () const { return ( 0 >= m_btlPrm.GetLife () ); }

		//SEの初回チェック
		void SetFirstSE ( bool b ) { m_btlPrm.SetFirstSE ( b ); }
		//SEの再生指定
		void PlaySE ( const s3d::String & se_name );

		//ボイスの初回チェック
		void SetFirstVC ( bool b ) { m_btlPrm.SetFirstVC ( b ); }
		//ボイスの再生指定
		void PlayVoice ( const s3d::String & vc_name );


		//------------------------------------------------------------
		bool CanBeThrown () const;		//投げられ判定
		bool IsThrowAction () const;	//投げ判定
		bool IsNotOffset () const;		//相殺しない判定
		bool CanGuard () const;			//ガードできる状態かどうか

		//特殊アクション（名前指定）
		bool IsNameAction ( s3d::String name ) const { return m_pAction->IsName ( name ); }

		//アクションが存在するかどうか
		bool ExistActionName ( s3d::String name ) const { return m_pChara->ExistAction ( name ); }

		//ヒットストップ
		bool IsHitStop () { return m_btlPrm.IsHitStop (); }


		//----------------------
		//	外部からの状態変更
		//----------------------

		//デモ用ステート指定
		void StartGreeting () { m_pActor->StartGreeting (); }
		void StartGetReady () { m_pActor->StartGetReady (); }
		void StartFighting () { m_pActor->StartFighting (); }
		void StartTimeUp   () { m_pActor->StartTimeUp (); }
		void StartEndWait  () { m_pActor->StartEndWait (); }
		void StartDown		() { m_pActor->StartDown (); }
		bool IsDown_Calm () { return IsNameAction ( U"敗北ダウン" ); }
		void StartWinner	() { m_pActor->StartWinner (); }

		void ShiftFightingMain () { m_pActor->ShiftFightingMain (); }
		void ShiftFightingMain_PreScriptMove () { m_pActor->ShiftFightingMain_PreScriptMove (); }
		void ShiftScpStop () { m_pActor->ShiftScpStop (); }
		void RestoreScpStop () { m_pActor->ShiftScpStop (); }

		bool SkipDecision () const { return m_pActor->SkipDecision (); }
		void ClearInput () { m_pCharaInput->ClearInput (); }
		void SetLose () { m_btlPrm.SetLose (); }

		void EndBattle ();	//戦闘終了

#if 0
		//一時停止
		void SetWait ( bool b ) { m_btlPrm.SetWait ( b ); }	//入力を停止
		void SetStop ( bool b ) { m_btlPrm.SetStop ( b ); }	//描画更新を停止
		void SetStopTimer ( UINT i ) { m_btlPrm.GetTmr_Stop ()->Start ( i ); }
#endif // 0

		//----------------------
		//	イベント
		//----------------------

		//ダッシュ相殺
		void OnDashOffset ();

		//相殺発生
		void OnOffset_AA ();	//自分：Attack, 相手：Attack
		void OnOffset_OA ();	//自分：Offset, 相手：Attack
		void OnOffset_AO ();	//自分：Attack, 相手：Offset
		void OnOffset_Common ();	//共通

		//自分・攻撃 -> 相手・くらい
		//ヒット発生
		bool IsHit () const { return m_btlPrm.GetHitEst (); }
		void SetHit ( bool b ) { m_btlPrm.SetHitEst ( b ); }
		void OnHit ();
		void OnEfHit ();

		//相手・攻撃 → 自分・くらい
		//くらい発生
		bool IsDamaged_prm () const { return m_btlPrm.GetDamaged (); }
		void SetDamaged ( bool b ) { m_btlPrm.SetDamaged ( b ); }
//		void OnDamaged ( int damage );
		void OnDamaged ();
		void OnDamaged_After ();	//相手ダメージ処理の後

		bool CheckGuard ();		//ガード成立判定
		void OnGuard ();		//ガード成立後の処理
		void OnKnockBack ();

		//-------------------------
		//判定後、自身の強制変更
		void ChangeMine ();

		//判定後、相手の強制変更
		void ChangeOhter ();
		//-------------------------

#if 0
		//相殺
		bool GetClang () const { return m_btlPrm.GetClang (); }
		void SetClang ( bool b ) { m_btlPrm.SetClang ( b ); }
#endif // 0




		//-------------------------------------------------
		//スクリプトからの変更
		//@info FtgGrpに移行
#if 0
		//暗転
		UINT GetBlackOut () const { return m_btlPrm.GetBlackOut (); }
		void SetBlackOut ( UINT i ) { m_btlPrm.SetBlackOut ( i ); }

		//停止
		UINT GetScpStop () const { return m_btlPrm.GetScpStop (); }
		void SetScpStop ( UINT i ) { m_btlPrm.SetScpStop ( i ); }

		//白転
		bool GetWhiteOut () const { return m_btlPrm.GetWhiteOut (); }
		void SetWhiteOut ( bool b ) { m_btlPrm.SetWhiteOut ( b ); }

		//壁割
		bool GetWallBreak () const { return m_btlPrm.GetWallBreak (); }
		void SetWallBreak ( bool b ) { m_btlPrm.SetWallBreak ( b ); }

#endif // 0

#if 0
#if 0
		//のけぞり時間
		void SetLurch ( UINT n ) { if ( 0 != n ) { m_lurch = n;  } }
		bool LurchTimer ();
#endif // 0

		//------------------------------------------------
		void OverEfPart ();	//EfPart重なり
#endif // 0
//==========================================================================

		//-------------------------------------------------
		//システム

		//トレーニングモード初期化
		void TrainingInit ();

		//入力表示切替
		void OnDispInput ();
		void OffDispInput ();

		//枠表示切替
		void OnDispRect ();
		void OffDispRect ();

		//最前面表示切替
		void OnFrontEnd ();
		void OffFrontEnd ();

		//プレイヤインプット面表示切替
		void On_DispPlayerInput ();
		void Off_DispPlayerInput ();

		//CPU操作切替
		void ControlCPU ();
		void ControlPlayer ();

	//================================================
	//	内部関数
	//================================================
	private:
		V_UINT	m_vOfstCncl;		//相殺キャンセルリスト(地上)
		V_UINT	m_vOfstCncl_Air;	//相殺キャンセルリスト(空中)
		void MakeOfstCnclList ();	//相殺キャンセルリスト生成

	public:
		//アクション指定(Stateから指定)
		void SetAction ( UINT action_id );
		void SetAction ( s3d::String action_name );
		//アクション移行(条件チェック)
		UINT Check_TransitAction_Condition ( BRANCH_CONDITION CONDITION ) const;
		//アクション移行(条件チェック) 名前を返す
//		tstring Check_TransitAction_Condition_str ( BRANCH_CONDITION CONDITION ) const;	
		s3d::String Check_TransitAction_Condition_str ( BRANCH_CONDITION CONDITION ) const;	

//		bool TranditAction_Command_Special ();	//アクション移項（コマンドに関する処理）限定
		void TranditAction_Special ();	//特殊条件移行

	private:
		//アクションの移項
		void TransitAction_Condition_I ( BRANCH_CONDITION CONDITION, bool forced );	//条件をチェックして移行
		void TransitAction_Condition_E ( BRANCH_CONDITION CONDITION, bool forced );	//条件をチェックして移行
		bool TranditAction_Command ();	//アクション移項（コマンドに関する処理）
		bool TranditAction_Exclusion ( P_Action pNextAct );	//特定アクションの除外
		void EndAction ();	//アクション移項時、前アクションの最後の処理

		//スクリプト処理
		void ExeScript ();	//スクリプト通常処理
		void SetParamFromScript ();	//スクリプトからパラメータを反映する
		void SpecialAction ();		//特殊アクション指定

		//------------------------------------------------
		//アクション体勢
		bool Is_AP_Stand () const { return m_pAction->GetPosture () == AP_STAND; }
		bool Is_AP_Jump () const { return m_pAction->GetPosture () == AP_JUMP; }
		bool Is_AP_Crouch () const { return m_pAction->GetPosture () == AP_CROUCH; }


		//------------------------------------------------
		//アクションカテゴリ

		//現在アクションカテゴリ取得
		ACTION_CATEGORY ActCtg () const { return m_pAction->GetCategory (); }
		bool IsActCtg ( ACTION_CATEGORY ac ) const { return ac == ActCtg (); }
		//各アクションかどうか
		bool IsAttacking () const
		{
			return
				m_pAction->GetCategory ()  == AC_ATTACK_L 
			||	m_pAction->GetCategory ()  == AC_ATTACK_M
			||	m_pAction->GetCategory ()  == AC_ATTACK_H; 
		}
		bool IsAttack_L ()	 const { return m_pAction->GetCategory () == AC_ATTACK_L; }
		bool IsStand ()		 const { return m_pAction->GetCategory () == AC_NEUTRAL; }
		bool IsMove ()		 const { return m_pAction->GetCategory () == AC_MOVE; }
		bool IsDash ()		 const { return m_pAction->GetCategory () == AC_DASH; }
		bool IsSpecial ()	 const { return m_pAction->GetCategory () == AC_SPECIAL; }
		bool IsOverdrive ()	 const { return m_pAction->GetCategory () == AC_OVERDRIVE; }
		bool IsPoised ()	 const { return m_pAction->GetCategory () == AC_POISED; }
		bool IsClang ()		 const { return m_pAction->GetCategory () == AC_CLANG; }
		bool IsAvoid ()		 const { return m_pAction->GetCategory () == AC_AVOID; }
		bool IsDotty ()		 const { return m_pAction->GetCategory () == AC_DOTTY; }
		bool IsDamaged ()	 const { return m_pAction->GetCategory () == AC_DAMAGED; }
		bool IsGuard ()		 const { return m_pAction->GetCategory () == AC_GUARD; }

		bool IsAir ()		 const { return m_pAction->GetPosture () == AP_JUMP; }
		bool IsThrow () const;
		bool Have_TransitAction_Condition ( BRANCH_CONDITION BRC_CND ) const;
#if 0
	public:
		//FightingオブジェクトのWPを設置
//		void SetwpFighting ( WP_FTG wp );


		//色変化
		//enum CLR_LOOP_NUM { CLR_LOOP_NUM = 8 };
		static const UINT32 CLR_LOOP [ CLR_LOOP_NUM ];

	private:
		//スロウタイマ
		TimerSlow		m_tmrSlow;

	public:
		void RevertSlow ();
#endif // 0

	public:

	public:
		//終了のための待機状態かどうか
		bool IsWait () { return IsStand (); }

		
		//メインイメージを同一Z値で先頭にする
		void TopByZ () { m_dispChara->TopByZ (); }


	};


}	//namespace GAME


