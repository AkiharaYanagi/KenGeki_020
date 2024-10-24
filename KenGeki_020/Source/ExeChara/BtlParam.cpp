//=================================================================================================
//
//	バトルパラメータ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "BtlParam.h"
#include "../GameMain/G_Ftg.h"
#include "Main/ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//クラス内定数
	const int BtlParam::RecoveryWhiteDamage_Time = 1;
	const int BtlParam::RecoveryWhiteDamage = 4;


	BtlParam::BtlParam ()
	{
		LoadTimer ();
	}


	//コピーコンストラクタ
	BtlParam::BtlParam ( const BtlParam & rhs )
	{
		m_posChara = rhs.m_posChara;		//キャラ位置
		m_tempPt = rhs.m_tempPt;			//一時保存
		m_dirRight = rhs.m_dirRight;		//向き(右：正, 左：逆)
		m_inertial = rhs.m_inertial;		//慣性
		m_dashInertial = rhs.m_dashInertial;	//ダッシュ慣性
		m_vel = rhs.m_vel;			//速度
		m_acc = rhs.m_acc;			//加速度
		m_g = rhs.m_g;				//重力
		m_vg = rhs.m_vg;			//重力(計算用)

		m_life = rhs.m_life;		//ライフ
		m_balance = rhs.m_balance;	//バランス
		m_mana = rhs.m_mana;		//マナ
		m_accel = rhs.m_accel;		//アクセル

		m_balance_max = rhs.m_balance_max;	//バランス最大値
		m_white_damage = rhs.m_white_damage;	//白ダメージ

		m_power = rhs.m_power;			//実効攻撃値
		m_damaged = rhs.m_damaged;		//くらいフラグ
		m_hitEst = rhs.m_hitEst;		//攻撃成立フラグ
		m_FirstEf = rhs.m_FirstEf;		//初回Efフラグ
		m_FirstSE = rhs.m_FirstSE;		//初回SEフラグ
		m_ForcedChange = rhs.m_ForcedChange;	//強制変更
		m_clang = rhs.m_clang;			//打合発生フラグ
		m_transit = rhs.m_transit;		//スクリプト遷移したフレーム
		m_lurch;		//のけぞり(キャンセル不可)時間追加
		m_wait = rhs.m_wait;			//入力を一時停止
		m_stop = rhs.m_stop;			//入力、スクリプト処理を一時停止

		//タイマはコピーしない
		LoadTimer ();

		m_blackOut = rhs.m_blackOut;		//暗転
		m_scpStop = rhs.m_scpStop;			//スクリプトからの停止
		m_whiteOut = rhs.m_whiteOut;		//白転
		m_wall_break = rhs.m_wall_break;	//壁割り

		m_hitNum = rhs.m_hitNum;				//同一アクション内ヒット数
		m_chainHitNum = rhs.m_chainHitNum;		//連続ヒット数　(別アクション)
		mn_AirDash = rhs.mn_AirDash;			//空中ダッシュ回数

		m_acc_recoil = rhs.m_acc_recoil;		//反動(ノックバック)加速度
		m_vel_recoil = rhs.m_vel_recoil;		//反動(ノックバック)速度
		m_pos_x_recoil = rhs.m_pos_x_recoil;	//反動(ノックバック)位置

		m_nActTransit = rhs.m_nActTransit;		//アクション移行回数
	}

	BtlParam::~BtlParam ()
	{
	}


	void BtlParam::SetpChara ( P_Chara p )
	{
		m_pChara = p;
	}

	void BtlParam::SetwpExeChara ( WP_ExeChara pExeChara, WP_ExeChara pOther )
	{
		m_pExeChara = pExeChara;
		m_pOther = pOther;
	}

#if 0
	void BtlParam::SetPlayerID ( PLAYER_ID playerID )
	{
		m_playerID = playerID;
		PosInit ();
	}
#endif // 0

	void BtlParam::LoadTimer ()
	{
		//タイマの初期化
		m_tmrHitstop	= std::make_shared < Timer > ( HITSTOP_TIME );	//ヒットストップ
		m_tmrDown		= std::make_shared < Timer > ( DOWN_TIME );		//ダウンタイマ
		m_tmrEnd		= std::make_shared < Timer > ( END_TIME );		//終了状態タイマ
		m_tmrScpStop		= std::make_shared < Timer > ();		//ストップタイマ
		m_tmrHitPitch	= std::make_shared < Timer > ();		//ヒット間隔タイマ
		m_tmrLurch		= std::make_shared < Timer > ();		//のけぞりタイマ
		m_tmrVib		 = std::make_shared < Timer > ();	//個別振動
		m_tmrWhiteDamage = std::make_shared < Timer > ();	//白ダメージ

		m_timers.push_back ( m_tmrHitstop );
		m_timers.push_back ( m_tmrDown );
		m_timers.push_back ( m_tmrEnd );
		m_timers.push_back ( m_tmrScpStop );
		m_timers.push_back ( m_tmrHitPitch );
		m_timers.push_back ( m_tmrLurch );
		m_timers.push_back ( m_tmrVib );
		m_timers.push_back ( m_tmrWhiteDamage );
	}

	void BtlParam::PosInit ()
	{
		//初期位置
		if ( PLAYER_ID_1 == m_playerID )
		{
			m_posChara = VEC2 ( PLAYER_1_BASE_X, PLAYER_1_BASE_Y );
			m_dirRight = true;
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			m_posChara = VEC2 ( PLAYER_2_BASE_X, PLAYER_2_BASE_Y );
			m_dirRight = false;
		}
	}

	void BtlParam::Init ()
	{
		//ゲームパラメータ
		m_life = LIFE_START;
		m_balance = BALANCE_START;
		m_balance_max = BALANCE_START;
		m_mana = MANA_START;
		m_accel = ACCEL_START;
		m_white_damage = 0;

		m_power = 0;

		m_hitEst = false;
		m_FirstEf = false;
		m_FirstSE = false;

		m_inertial = VEC2 ( 0, 0 );
		m_dashInertial = VEC2 ( 0, 0 );
		m_vel = VEC2 ( 0, 0 );
		m_acc = VEC2 ( 0, 0 );

		m_hitDrop = 0;

		EndAction ();

		PosInit ();

		m_wait = false;
		m_stop = false;

		AllTmr_Clear ();

		m_hitNum = 0;
		m_chainHitNum = 0;

		//反動(ノックバック)
		m_acc_recoil = 0;
		m_vel_recoil = 0;
		m_pos_x_recoil = 0;
	}

	void BtlParam::TimerMove ()
	{
		for ( P_Timer ptmr : m_timers )
		{
			ptmr->Move ();
		}
	}

	//------------------------------------------------
	void BtlParam::TrainingInit ()
	{
		Init ();
		m_mana = MANA_MAX;
	}



	//------------------------------------------------
	//アクション終了時
	void BtlParam::EndAction ()
	{
		m_clang = false;
		m_hitEst = false;
		m_FirstEf = false;
		m_ForcedChange = false;
		m_lurch = 0;
		AllTmr_Clear ();
		m_hitNum = 0;
		m_hitDrop = 0;
	}

	//------------------------------------------------
	//位置計算
	// ■ 毎フレーム１回
	void BtlParam::CalcPos ( P_Script pScp )
	{
		//------------------------
		//スクリプト値
		VEC2 vel = pScp->m_prmBattle.Vel;
		VEC2 acc = pScp->m_prmBattle.Acc;

		//------------------------
		// 位置 (xのみ向きを乗算)
		m_tempPt = GetPos ();		//一時保存
		float dir = GetDirRight () ? 1.f : -1.f;		//向き

		//------------------------
		// 慣性
#if 0
		//攻撃(スクリプト遷移)時、現在の慣性を反映する
		//加速度(慣性)
		if ( m_transit )
		{
			m_inertial = m_pScript->GetAcc ();
			float dir = m_dirRight ? 1.f : -1.f;
			m_ptChara += dir * m_inertial;
		}

		// 慣性の減少
		if ( m_inertial.x > 0 )
		{
			m_inertial.x -= 0.3f;
			if ( m_inertial.x < 0 ) { m_inertial.x = 0; }
		}
		else
		{
			m_inertial.x += 0.3f;
			if ( m_inertial.x > 0 ) { m_inertial.x = 0; }
		}

		if ( m_inertial.y > 0 )
		{
			m_inertial.y -= 0.3f;
			if ( m_inertial.y < 0 ) { m_inertial.y = 0; }
		}
		else
		{
			m_inertial.y += 0.3f;
			if ( m_inertial.y > 0 ) { m_inertial.y = 0; }
		}
#endif // 0

		//ダッシュ慣性
		DecreaseInertial ( 0.5f, m_dashInertial );
		m_posChara += m_dashInertial * dir;

		//------------------------
		// 空中ヒット時落下補正
		acc.y += m_hitDrop;			//加速度に加える
		m_posChara.y += m_hitDrop;	//直接位置を補正する



		//------------------------
		//計算種類で分岐
		CLC_ST clcSt = pScp->m_prmBattle.CalcState;
		switch ( clcSt )
		{
		case CLC_MAINTAIN: 	//持続
			m_acc = acc;

			m_vel.x += m_acc.x;		//加速度
			m_posChara.x += dir * m_vel.x;		//速度
			m_posChara.x += dir * m_inertial.x;		//慣性

			m_vel.y += m_acc.y;		//加速度
			m_posChara.y += m_vel.y;		//速度
			m_posChara.y += m_inertial.y;		//慣性

			break;

		case CLC_SUBSTITUDE:	//代入

			m_vel.x = vel.x;
			m_acc.x = acc.x;
			m_posChara.x += dir * m_vel.x;		//速度
			m_posChara.x += dir * m_inertial.x;		//慣性

			m_vg += m_g;
			m_vel.y = vel.y + m_vg;
			m_acc.y = acc.y;
			m_posChara.y += m_vel.y;		//速度
			m_posChara.y += m_inertial.y;		//慣性

			break;

		case CLC_ADD:	//加算

			m_vel.x += vel.x;
			m_acc.x += acc.x;
			m_posChara.x += dir * m_vel.x;		//速度
			m_posChara.x += dir * m_inertial.x;		//慣性

			m_vel.y += vel.y;
			m_acc.y += acc.y;
			m_posChara.y += m_vel.y;		//速度
			m_posChara.y += m_inertial.y;		//慣性

			break;

		default: break;
		}

		//---------------
		//画面端 (キャラ移動補正)
		float wall_L = (float)FIELD_EDGE + G_FTG()->GetWallLeft ();
		float wall_R = G_FTG()->GetWallRight () - (float)FIELD_EDGE;




		//壁より先には移動しない
		if ( m_posChara.x < wall_L ) { m_posChara.x = wall_L; }
		if ( m_posChara.x > wall_R ) { m_posChara.x = wall_R; }
#if 0
#endif // 0




		//---------------
		//反動(ノックバック)
		m_vel_recoil += dir * m_acc_recoil;
		m_posChara.x += m_vel_recoil;
		m_vel_recoil *= 0.8f;	//Velは減衰
		if ( std::abs ( m_vel_recoil ) < 0.01f ) { m_vel_recoil = 0; } 

#if 0
		//デバッグ表示あり
		if ( m_playerID == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( 4, _T ( "m_acc_recoil = %f" ), m_acc_recoil );
			DBGOUT_WND_F ( 5, _T ( "m_vel_recoil = %f" ), m_vel_recoil );
		}
#endif // 0
		m_acc_recoil = 0;		//accは初速のみ


		//------------------------------------------------
		//演出・個別振動
		if ( ! m_tmrVib->IsActive () )
		{
			//スクリプトからの指定があるとき
			int32 vib = m_pScript->m_prmStaging.Vibration_S;
			if ( vib > 0 )
			{
				//開始
				m_tmrVib->Start ( vib );
				m_vib = 10.f;
			}
			else
			{
				//通常時
				m_vib = 0;
			}
		}
		else
		{
			//反転する
			m_vib *= -1;

			//終了時
			if ( m_tmrVib->IsLast () )
			{
				m_vib = 0;
			}
		}

		//-------------------------------------------------
		//ライフ関連
		// 
		//白ダメージ回復
		
		if ( 0 < m_white_damage ) 
		{
			//タイマ
			if ( ! m_tmrWhiteDamage->IsActive () )
			{
				m_tmrWhiteDamage->Start ( RecoveryWhiteDamage_Time );
			}

			if ( m_tmrWhiteDamage->IsLast () )
			{
				m_white_damage -= RecoveryWhiteDamage;
				m_life += RecoveryWhiteDamage;
			}

			if ( m_white_damage < 0 ) { m_white_damage = 0; }
		}

#if 0
		if ( m_playerID == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( 6, _T ( "m_white_damage = %d" ), m_white_damage );
		}
#endif // 0

//		//アクセルディジーズ
		//アクセル値が低いとき、ライフの減少をもたらす
		//ネガティブポイズン
		if ( m_accel < 0 )
		{
			//ライフ残１０％補正
			if ( (float)LIFE_MAX * 0.1f < m_life )
			{
				m_life += m_accel / 100;
			}
		}
	}


	// 慣性の減少
	void BtlParam::DecreaseInertial ( float d, VEC2& inertial )
	{
		if ( inertial.x > 0 )
		{
			inertial.x -= d;
			if ( inertial.x < 0 ) { inertial.x = 0; }
		}
		else
		{
			inertial.x += d;
			if ( inertial.x > 0 ) { inertial.x = 0; }
		}

		if ( inertial.y > 0 )
		{
			inertial.y -= d;
			if ( inertial.y < 0 ) { inertial.y = 0; }
		}
		else
		{
			inertial.y += d;
			if ( inertial.y > 0 ) { inertial.y = 0; }
		}
	}

	//着地
	void BtlParam::Landing ()
	{
		VEC2 pos = GetPos ();

		//位置が基準より下だったら
		if ( (float)PLAYER_BASE_Y < pos.y )
		{
			//着地条件のブランチを取得
			UINT indexAction = m_pExeChara.lock()->Check_TransitAction_Condition ( BRANCH_CONDITION::BRC_GRD );
			if ( NO_COMPLETE != indexAction )
			{
				Ground_Y ();

				//自身を変更
				m_pExeChara.lock()->SetAction ( indexAction );	//遷移
			}

			//位置が基準より下で立ち状態だったら
			if ( m_pAction->IsName ( U"立ち" ) )
			{
				Ground_Y ();
			}
		}

		//位置が基準より上で立ち状態だったら
		if ( (float)PLAYER_BASE_Y > pos.y )
		{
			if ( m_pAction->IsName  ( U"立ち" ) )
			{
				UINT indexAction = m_pChara->GetActionID ( U"落下" );
				m_pExeChara.lock()->SetAction ( indexAction );			//落下
			}
		}
	}


	//y位置リセット
	void BtlParam::Ground_Y ()
	{
		float x = m_posChara.x;
		float y = PLAYER_BASE_Y;
		SetPos ( VEC2 ( x, y ) );
		SetVel ( VEC2 ( 0, 0 ) );
		SetAcc ( VEC2 ( 0, 0 ) );
		SetVg ( 0 );
		SetG ( 0 );

		//空中ダッシュ回数リセット
		mn_AirDash = 0;
	}

	void BtlParam::BackMoveX ()
	{
		//向きによらず、相手から離れる方向
		VEC2 iPos = GetPos ();
		VEC2 ePos = m_pOther.lock ()->GetPos ();
		bool dirBack = true;

		//同値の場合は1P2Pで選別
		if ( iPos.x == ePos.x )
		{
			dirBack = ( m_playerID == PLAYER_ID_1 );
		}
		else
		{
			//互いの位置で補正方向を決定
			dirBack = ( iPos.x < ePos.x );
		}

		float x = iPos.x + 10 * ( dirBack ? -1.f : 1.f );
		float y = iPos.y;
		SetPos ( VEC2 ( x, y ) );
	}

	//相手の方向を向く
	void BtlParam::LookOther ()
	{
		//振り向きチェック
		if ( ! IsLookOther () )
		{
			return; 
		}

		//相手と位置xが同じ場合は向き持続
		VEC2 iPos = GetPos ();
		VEC2 ePos = m_pOther.lock ()->GetPos ();
		if ( iPos.x == ePos.x )
		{
			return;
		}

		//互いの位置で方向を決定
		SetDirRight ( iPos.x < ePos.x );
	}

	bool BtlParam::IsLookOther ()
	{
		//「振り向き」チェックする動作
		if ( m_pAction->IsName ( U"立ち")		) { return T; }
		if ( m_pAction->IsName ( U"前歩き")		) { return T; }
		if ( m_pAction->IsName ( U"後歩き")		) { return T; }
		if ( m_pAction->IsName ( U"着地")		) {	return T; }
		if ( m_pAction->IsName ( U"空中やられ")	) {	return T; }

		return F;
	}

	//------------------------------------------------------------------------
	//ゲージ類
	void BtlParam::AddLife ( int n )
	{
		m_life += n;
		if ( m_life < 0 ) { m_life = 0; }
		if ( LIFE_MAX < m_life ) { m_life = LIFE_MAX; }
	}

	//加算後、最大最小値でチェック
	void BtlParam::AddBalance ( int n )
	{
		m_balance += n;
		if ( m_balance < 0 ) { m_balance = 0; }
		if ( m_balance_max < m_balance ) { m_balance = m_balance_max; }
	}

	void BtlParam::AddMana ( int n )
	{
		m_mana += n;
		if ( m_mana < 0 ) { m_mana = 0; }
		if ( MANA_MAX < m_mana ) { m_mana = MANA_MAX; }
	}

	void BtlParam::AddAccel ( int n )
	{
		m_accel += n;
		if ( m_accel < ACCEL_MIN ) { m_accel = ACCEL_MIN; }
		if ( ACCEL_MAX < m_accel ) { m_accel = ACCEL_MAX; }
	}

	void BtlParam::DirZeroAccel ( int n )
	{
		//方向
		if ( m_accel < 0 )
		{
			m_accel += n; 
			if ( 0 < m_accel ) { m_accel = 0; }
		}
		else
		{
			m_accel -= n; 
			if ( m_accel < 0 ) { m_accel = 0; }
		}
	}


	//-------------------------------------------------------------------
	// イベント

	void BtlParam::OnDamage ( int damage )
	{
		//通常ダメージ：マイナスの値
		//回復		：プラスの値
		
#if 0
		//--------------------------------------------
		//ダメージをライフによって補正(根性値)
		int lf = m_btlPrm.GetLife ();
		if ( lf < LIFE_MAX * 0.5f )
		{
			damage = (int)( damage * ( 0.001f * ( 0.5f * LIFE_MAX + lf ) ) );
		}
#endif // 0

		//--------------------------------------------
		//一旦白ダメージに蓄積
		
		//最大値より大きい時補正
		if ( m_life + damage < 0 )
		{
			m_white_damage += m_life;
			m_life = 0;
		}
		else
		{
			m_white_damage += - damage; 
			m_life += damage;
		}

		//回復のとき上限チェック
		if ( m_life + damage > LIFE_MAX ) { m_life = LIFE_MAX; }

#if 0
		m_life += damage;
		m_white_damage = 0;
#endif // 0
	}


	//============================================================
	//相殺時 (自分：攻撃、相手：攻撃)
	void BtlParam::OnOffset_AA ()
	{
		OnOffset_Common ();

		//@info 自分の攻撃が相殺したときは、内部ヒット数が増加する
		++ m_hitNum;
	}

	//相殺時 (自分：攻撃、相手：相殺)
	void BtlParam::OnOffset_AO ()
	{
		OnOffset_Common ();

		//@info 自分の攻撃が相殺したときは、内部ヒット数が増加する
		++ m_hitNum;
	}

	//相殺時 (自分：相殺、相手：攻撃)
	void BtlParam::OnOffset_OA ()
	{
		OnOffset_Common ();

		//@info 自身が相殺判定で相手の攻撃を取ったとき、内部ヒット数は増加しない
		//		++ m_hitNum;
	}

	//相殺時共通
	void BtlParam::OnOffset_Common ()
	{
		m_clang = T;		//打合発生フラグ
		m_tmrHitstop->Start ( OFFSET_TIME );		//ヒットストップの設定
		HitPitchWaitStart ( OFFSET_TIME );

		//-------------------------------------------------
		//ノックバック処理		// 値は (float) = (int)1/10
		float recoil_i = 0.1f * m_pScript->m_prmBattle.Recoil_I;
		SetAccRecoil ( recoil_i );

	}
	//============================================================


	//ヒット時
	void BtlParam::OnHit ()
	{
		m_hitEst = T;		//攻撃成立フラグ
		m_tmrHitstop->Start ( HITSTOP_TIME );		//ヒットストップの設定

//		m_tmrHitPitch->WaitStart ( HITSTOP_TIME );	//ヒット間隔のカウント
		//※ヒットストップ分を待機してからスタート
		HitPitchWaitStart ( HITSTOP_TIME );

		++ m_hitNum;

		++ m_chainHitNum;
	}

	void BtlParam::HitPitchWaitStart ( UINT time )
	{
		m_tmrHitPitch->Clear ();
		m_tmrHitPitch->WaitStart ( time );	//ヒット間隔のカウント
	}


	void BtlParam::CalcBalance ( P_Script pScp )
	{
		//バランス処理
		int sb = pScp->m_prmBattle.Balance_I;
#if 0
		int b = GetBalance ();
		b -= sb;
		SetBalance ( b );
#endif // 0
		AddBalance ( -sb );
	}


	//白ダメージ確定
	void BtlParam::DecisionWhiteDamage ()
	{
		m_white_damage = 0;
	}


	//敗北処理
	void BtlParam::SetLose ()
	{
		m_white_damage = 0;
		m_life = 0;
	}
}

//namespace GAME

