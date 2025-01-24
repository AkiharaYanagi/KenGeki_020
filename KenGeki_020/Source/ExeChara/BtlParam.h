//=================================================================================================
//
//	バトルパラメータ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Script.h"
#include "../GameMain/GameConst.h"
#include "../GameMain/Param.h"
#include "../FtgMain/FtgConst.h"
#include "Timer.h"
#include "TimerSlow.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//前方宣言
	class ExeChara;
	using P_ExeChara = std::shared_ptr < ExeChara >;
	using WP_ExeChara = std::weak_ptr < ExeChara >;
	class Chara;
	using P_Chara = std::shared_ptr < Chara >;
	class Action;
	using P_Action = std::shared_ptr < Action >;
	class Script;
	using P_Script = std::shared_ptr < Script >;


	//クラス宣言
	class BtlParam
	{
		//------------------------------------------------
		//データ
		P_Chara			m_pChara;		//キャラデータ
		WP_ExeChara		m_pExeChara;	//自エグゼキャラ(循環参照なのでweak_ptr)
		WP_ExeChara		m_pOther;		//相手エグゼキャラ(循環参照なのでweak_ptr)
		P_Action		m_pAction;		//現在アクション
		P_Script		m_pScript;		//現在スクリプト
		P_Param			m_pParam;		//全体パラメータ

		//------------------------------------------------
		//パラメータ
		PLAYER_ID	m_playerID;			//プレイヤID
		VEC2	m_posChara { 0, 0 };	//キャラ位置
		VEC2	m_tempPt;				//一時保存位置
		bool	m_dirRight { T };		//向き(右：正, 左：逆)
		VEC2	m_inertial { 0, 0 };	//慣性
		VEC2	m_dashInertial { 0, 0 };	//ダッシュ慣性
		VEC2	m_vel { 0, 0 };			//速度
		VEC2	m_acc { 0, 0 };			//加速度
		float	m_g { 0 };				//重力
		float	m_vg { 0 };				//重力(計算用)

		float	m_hitDrop { 0 };		//空中ヒット時落下補正

		int		m_life { 0 };			//ライフ
		int		m_balance { 0 };		//バランス(行動)
		int		m_mana { 0 };			//マナ(超必殺)
		int		m_accel { 0 };			//アクセル ( -500 ~ +1000 )

		int		m_balance_max { 0 };	//バランスゲージ変動上限
		int		m_white_damage { 0 };	//白ダメージ
		P_Timer		m_tmrWhiteDamage;	//白ダメージタイマ

		int		m_power { 0 };			//実効攻撃値
		bool	m_damaged { F };		//くらいフラグ
		bool	m_hitEst { F };			//攻撃成立フラグ
		bool	m_FirstEf { F };		//初回Efフラグ
		bool	m_FirstSE { F };		//初回SEフラグ
		bool	m_FirstVC { F };		//初回VCフラグ
		bool	m_ForcedChange { F };	//強制変更
		bool	m_clang { F };			//打合発生フラグ
		bool	m_transit { F };		//スクリプト遷移したフレーム
		UINT	m_lurch { 0 };			//のけぞり(キャンセル不可)時間追加
		bool	m_wait { F };			//入力を一時停止
		bool	m_stop { F };			//入力、スクリプト処理を一時停止


		VP_Timer	m_timers;			//タイマ監理
		P_Timer		m_tmrScpStop;		//全体ストップタイマ
		P_Timer		m_tmrHitstop;		//ヒットストップタイマ
		P_Timer		m_tmrDown;			//ダウンタイマ
		P_Timer		m_tmrEnd;			//終了状態タイマ
		P_Timer		m_tmrLurch;			//のけぞりタイマ
		P_Timer		m_tmrVib;			//個別振動タイマ
		P_Timer		m_tmrOfstCncl;		//相殺キャンセルタイマ
		P_Timer		m_tmrTaikou;		//剣撃対抗受付タイマ

		UINT	m_blackOut { 0 };		//暗転
		UINT	m_scpStop { 0 };		//スクリプトからの停止
		bool	m_whiteOut { F };		//白転
		bool	m_wall_break { F };		//壁割り

		//連続ヒット
		P_Timer	m_tmrHitPitch { 0 };	//ヒット間隔タイマ
		UINT	m_hitNum { 0 };			//同一アクション内ヒット数
		UINT	m_chainHitNum { 0 };	//連続ヒット数　(別アクション)
		int32	m_chainDamage { 0 };	//連続ヒットダメージ
		UINT	mn_AirDash { 0 };		//空中ダッシュ回数

		float	m_acc_recoil { 0 };		//反動(ノックバック)加速度
		float	m_vel_recoil { 0 };		//反動(ノックバック)速度
		float	m_pos_x_recoil { 0 };	//反動(ノックバック)位置

		float	m_vib { 0.f };			//振動量

		_CLR	m_color { 0xffffffff };	//色

		//Result用
		int		m_nActTransit { 0 };	//アクション移行回数

		bool	m_taikou { F };			//剣撃対抗

		float	m_reviseThrow { 1.f };		//投げ後の連続技中補正
		float	m_reviseOverDrive { 1.f };	//超必後の連続技中補正
		float	m_confirmed_revise { 1.f };	//最終確定補正値

	public:
		BtlParam ();
		BtlParam ( const BtlParam & rhs );	// ※ コピー可能
		~BtlParam ();

		//--------------------------------------------------------------------
		void ParamInit ( P_Param p );
		void SetpChara ( P_Chara p );
		void SetwpExeChara ( WP_ExeChara pExeChara, WP_ExeChara pOther );

		void Update ( P_Action pAct, P_Script pScp ) { m_pAction = pAct; m_pScript = pScp; }

		void LoadTimer ();
		void Init ();
		void TimerMove ();

		//--------------------------------------------------------------------
		//モード別初期化
		//トレーニング初期化
		void TrainingInit ();

		//--------------------------------------------------------------------
		//アクション終了時
		void EndAction ();

		//フレーム処理開始時
		void FrameInit ();

		//位置計算
		void CalcPos ( P_Script pScp );

		void PosInit ();

		//バトルパラメータにおける毎フレームの入力による動作
		void Move_Input ();


		//--------------------------------------------------------------------
		//各パラメータ
		GET_SET ( PLAYER_ID, GetPlayerID, SetPlayerID, m_playerID )	//プレイヤID
		GET_SET ( VEC2, GetPos, SetPos, m_posChara )			//キャラ位置
		GET_SET ( bool, GetDirRight, SetDirRight, m_dirRight )		//右正の向き
		GET_SET ( VEC2, GetInertial, SetInertial, m_inertial )		//慣性
		GET_SET ( VEC2, GetDashInertial, SetDashInertial, m_dashInertial )	//ダッシュ慣性
		GET_SET ( VEC2, GetVel, SetVel, m_vel )		//速度
		GET_SET ( VEC2, GetAcc, SetAcc, m_acc )		//加速度
		GET_SET ( float, GetG, SetG, m_g )			//重力
		GET_SET ( float, GetVg, SetVg, m_vg )		//重力(計算用)
		GET_SET ( float, GetHitDrop, SetHitDrop, m_hitDrop )	//空中ヒット時落下補正

		GET_SET ( int, GetLife, SetLife, m_life	)			//ライフ
		GET_SET ( int, GetBalance, SetBalance, m_balance )	//バランス
		GET_SET ( int, GetMana, SetMana, m_mana )			//マナ
		GET_SET ( int, GetAccel, SetAccel, m_accel )		//アクセル ( -500 ~ +1000 )
		GET_SET ( int, GetBalanceMax, SetBalanceMax, m_balance_max )	//バランス最大値
		GET_SET ( int, GetWhiteDamage, SetWhiteDamage, m_white_damage )	//白ダメージ
		GET_SET ( int, GetPower, SetPower, m_power )		//実効攻撃値
		
		//--------------------------------------------------------------------
		//単純フラグ { get; set; }
		GET_SET ( bool, GetDamaged, SetDamaged, m_damaged )		//くらい
		GET_SET ( bool, GetHitEst, SetHitEst, m_hitEst )			//ヒット成立
		GET_SET ( bool, GetForcedChange, SetForcedChange, m_ForcedChange )		//強制変更
		GET_SET ( bool, GetClang, SetClang, m_clang )				//打合
		GET_SET ( bool, GetTrangit, SetTrangit, m_transit )		//スクリプト遷移
		GET_SET ( bool, GetFirstEf, SetFirstEf, m_FirstEf )		//エフェクト発生初回
		GET_SET ( bool, GetFirstSE, SetFirstSE, m_FirstSE )		//SE発生初回
		GET_SET ( bool, GetFirstVC, SetFirstVC, m_FirstVC )		//VC発生初回
		GET_SET ( bool, GetWait, SetWait, m_wait )				//待機(入力を停止)
		GET_SET ( bool, GetStop, SetStop, m_stop )				//停止(入力、スクリプト処理を停止)

		//--------------------------------------------------------------------
		GET_SET ( UINT, GetBlackOut, SetBlackOut, m_blackOut )	//暗転
		GET_SET ( UINT, GetScpStop, SetScpStop, m_scpStop )	//スクリプトからの停止
		GET_SET ( UINT, GetHitNum, SetHitNum, m_hitNum )		//同一アクション内ヒット数
		GET_SET ( UINT, GetChainHitNum, SetChainHitNum, m_chainHitNum )		//同一アクション内ヒット数
		GET_SET ( int32, GetChainDamage, SetChainDamage, m_chainDamage )	//連続ヒットダメージ
		GET_SET ( bool, GetWhiteOut, SetWhiteOut, m_whiteOut )		//白転
		GET_SET ( bool, GetWallBreak, SetWallBreak, m_wall_break )	//壁割り

		//--------------------------------------------------------------------
		GET_SET ( int, GetNActTrs, SetNActTrs, m_nActTransit )	//アクション移行回数
		GET_SET ( UINT, GetNAirDash, SetNAirDash, mn_AirDash )	//空中ダッシュ移行回数

		GET_SET ( float, GetAccRecoil, SetAccRecoil, m_acc_recoil )
		GET_SET ( float, GetVelRecoil, SetVelRecoil, m_vel_recoil )
		GET_SET ( float, GetPosXRecoil, SetPosXRecoil, m_pos_x_recoil )

		GET_SET ( float, GetVib, SetVib, m_vib )

		GET_SET ( _CLR, GetColor, SetColor, m_color )

		GET_SET ( int, GetTaikou, SetTaikou, m_taikou )	//剣撃対抗
		GET_SET ( float, GetReviseThrow, SetReviseThrow, m_reviseThrow )
		GET_SET ( float, GetReviseOverDrive, SetReviseOverDrive, m_reviseOverDrive )
		GET_SET ( float, GetCnfmRvs, SetCnfmRvs, m_confirmed_revise )

		//--------------------------------------------------------------------
		//タイマ
		P_Timer GetTmr_ScpStop () { return m_tmrScpStop; }
		P_Timer GetTmr_HitStop () { return m_tmrHitstop; }
		P_Timer GetTmr_HitPitch () { return m_tmrHitPitch; }
		P_Timer GetTmr_Down () { return m_tmrDown; }
		P_Timer GetTmr_End () { return m_tmrEnd; }
		P_Timer GetTmr_Lurch () { return m_tmrLurch; }
		P_Timer GetTmr_OfstCncl () { return m_tmrOfstCncl; }
		P_Timer GetTmr_Taikou () { return m_tmrTaikou; }

		void AllTmr_Clear () { for ( P_Timer ptmr : m_timers ) { ptmr->Clear (); } }

		//--------------------------------------------------------------------
		bool IsHitStop () const 
		{ 
			//最後だけ外す
			if ( m_tmrHitstop->IsLast () ) { return F; }
			return m_tmrHitstop->IsActive ();
		}


		//====
		//増減用
		void AddLife ( int n );
		void AddBalance ( int n );
		void AddMana ( int n );
		void AddAccel ( int n );
		void DirZeroAccel ( int n );	//０方向に向かう
		void AddNActTrs ( int n ) { m_nActTransit += n; }
		void AddChainDamage ( int32 n ) { m_chainDamage += n; }
		void IncChainHitNum ();

		//----
		//処理まとめ
		void OnHit ();	//ヒット時
		void HitPitchWaitStart ( UINT time );	//ヒット間隔再スタート
		void CalcBalance ( P_Script pScp );
		void OnDamage ( int damage );	//ダメージ時

		void OnOffset_AA ();	//相殺時 (自分：攻撃、相手：攻撃)
		void OnOffset_AO ();	//相殺時 (自分：攻撃、相手：相殺)
		void OnOffset_OA ();	//相殺時 (自分：相殺、相手：攻撃)
		void OnOffset_Common ();	//共通

		void BackPt () { m_posChara = m_tempPt; }		//一つ前の位置に戻す
		void BackPtX () { m_posChara.x = m_tempPt.x; }		//一つ前の位置に戻す
		void Ground_Y ();	//Yリセット
		void Landing ();	//着地
		void BackMoveX ();	//重なり時後ろずらし（重なりが解消されるまで戻す）
		void LookOther ();	//相手の方向を向く
		bool IsLookOther ();

		void DecisionWhiteDamage ();	//白ダメージ確定
		void ChainReset ();	//連続ヒット関連リセット

		void SetLose ();	//敗北処理

		bool Is1P () const { return PLAYER_ID_1 == GetPlayerID(); }
		bool Is2P () const { return PLAYER_ID_2 == GetPlayerID(); }
	private:
		// 慣性の減少
		void DecreaseInertial ( float d, VEC2 & inertial );

		//白ダメージ
		static const int RecoveryWhiteDamage_Time;
		static const int RecoveryWhiteDamage;
	};


}	//namespace GAME

