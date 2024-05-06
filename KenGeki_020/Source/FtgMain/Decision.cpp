//=================================================================================================
//
//	判定
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Decision.h"
//#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Decision::Decision ()
	{
#if 0
		//共通エフェクト
		m_efClang = make_shared < EfClang > ();
		AddpTask ( m_efClang );
		GRPLST_INSERT_MAIN ( m_efClang );

		m_efSpark = make_shared < EfSpark > ();
		AddpTask ( m_efSpark );
		GRPLST_INSERT_MAIN ( m_efSpark );

//		m_efParticle = make_shared < EfParticle > ();
//		GRPLST_INSERT_MAIN ( m_efParticle );

		m_efPart = make_shared < EfPart > ();
		AddpTask ( m_efPart );
		GRPLST_INSERT_MAIN ( m_efPart );

		m_efHit = make_shared < EfHit > ();
		AddpTask ( m_efHit );
		GRPLST_INSERT_MAIN ( m_efHit );
#endif // 0
	}

	Decision::~Decision ()
	{
	}

#if 0

	void Decision::SetpChara (P_ExeChara pExeChara1p, P_ExeChara pExeChara2p)
	{
		m_pExeChara1p = pExeChara1p;
		m_pExeChara2p = pExeChara2p;
	}

	void Decision::SetpHitStop (P_Timer pHitstop)
	{
		m_tmrHitstop = pHitstop;
	}


	//相互判定
	void Decision::Do ()
	{
		//------------------------------------------------------
		//ヒットストップは何もしない
		if ( m_tmrHitstop->IsActive () ) { return; }
#if 0
		//打合時は何もしない
		if (m_exeChara1.GetClang () || m_exeChara2.GetClang ()) { return; }
#endif // 0

		//------------------------------------------------------
		//粒子エフェクト取得
//		Decision_EfPart ();

		//------------------------------------------------------
		//判定用一時変数

		//判定送信用
//		CLANG_DECISION_LR sendDecision = CD_OFF; 

		//------------------------------------------------------
		//枠の取得

		//枠管理の取得
		P_CharaRect pCharaRect1p = m_pExeChara1p->GetpCharaRect ();
		P_CharaRect pCharaRect2p = m_pExeChara2p->GetpCharaRect ();

		//攻撃枠を取得
		PV_RECT pvARect1 = pCharaRect1p->GetpvARect ();
		PV_RECT pvARect2 = pCharaRect2p->GetpvARect ();

		//相殺枠を取得
		PV_RECT pvORect1 = pCharaRect1p->GetpvORect ();
		PV_RECT pvORect2 = pCharaRect2p->GetpvORect ();

		//当り枠を取得
		PV_RECT pvHRect1 = pCharaRect1p->GetpvHRect ();
		PV_RECT pvHRect2 = pCharaRect2p->GetpvHRect ();

		//エフェクトリストの取得
		PLP_ExEf plpExEf1 = m_pExeChara1p->GetplpExEf ();
		PLP_ExEf plpExEf2 = m_pExeChara2p->GetplpExEf ();

		//重なり中心位置
		VEC2 center = VEC2 (0, 0);

		//------------------------------------------------------
		//ダッシュぶつかり判定
		//[D]:ダッシュにおける攻撃判定[A]
		// >> 変更 [D]:ダッシュにおける相殺判定[O]


		//[D]-><-[D] : 特殊相殺
		if (DcsAtoA (pCharaRect1p, pCharaRect2p, center))
		{
			m_pExeChara1p->OnDashBranch ();
			m_pExeChara2p->OnDashBranch ();
		}


		//[D]->[A],[D]->[O] : 通常相殺
		//[D]->[H] : 通常ヒットから互いにスクリプトでアクション移行



		//------------------------------------------------------
		//打合：攻撃判定と攻撃判定、または攻撃判定と相殺判定 (相殺と相殺は何もしない)

		//ヒットより相殺を優先

		//------------------------------------------------------
		//エフェクト

		//エフェクトリストの相殺チェック
		//相殺時には各エフェクトに相殺状態をセット(反映はExeEffectがまとめて後に行う)
		DcsOffsetEf (plpExEf1, plpExEf2, pCharaRect2p);		//p1からp2へのチェック
		DcsOffsetEf (plpExEf2, plpExEf1, pCharaRect1p);		//p2からp1へのチェック

		//------------------------------------------------------
		//エフェクトのヒットチェック

		//p1からp2へのチェック
		int powerEf1p = 0;
		m_Efhit2P = DcsHitEf ( plpExEf1, pvHRect2, m_pExeChara2p, powerEf1p );
		
		//p2からp1へのチェック	
		int powerEf2p = 0;
		m_Efhit1P = DcsHitEf ( plpExEf2, pvHRect1, m_pExeChara1p, powerEf2p );



		//------------------------------------------------------
		//メインキャラ同士の本体相殺チェック

		//攻撃・攻撃
		bool offset_aa = OverlapAryRect_Center (pvARect1, pvARect2, center);

		//攻撃・相殺判定
		bool offset_ao = F;
		bool offset_oa = F;
		
		if ( ! m_pExeChara1p->IsNotOffset () )
		{
			offset_ao = OverlapAryRect_Center (pvARect1, pvORect2, center);
		}
		
		if ( ! m_pExeChara2p->IsNotOffset () )
		{
			offset_oa = OverlapAryRect_Center (pvORect1, pvARect2, center);
		}


//		m_bOffsetChara = DcsOffset ( pCharaRect1p, pCharaRect2p, center );
//		m_bOffsetChara = offset_aa || offset_ao || offset_oa;
		bool bOffset = offset_aa || offset_ao || offset_oa;


		//------------------------------------------------------
		//メインキャラのヒットチェック
		
		bool hit1P = false;
		bool hit2P = false;
		VEC2 hit_center_1p = { 0, 0 };
		VEC2 hit_center_2p = { 0, 0 };

		//両者の判定を行ってから反映する(片方ずつ反映するとヒット状態を参照してしまうため)
		if ( ! bOffset )	//相殺していないときのみ
		{
			//「投げ」と「投げられ」
			bool b_throw1 = m_pExeChara1p->IsThrowAction ();
			bool b_thrown2 = m_pExeChara2p->CanBeThrown ();
			bool no_check_1 = b_throw1 && ( ! b_thrown2 );

			if ( ! no_check_1 )
			{
				//ヒット判定と攻撃判定(1P->2P)
				hit2P = OverlapAryRect_Center ( pvARect1, pvHRect2, hit_center_2p );
			}

			//-------------------------------------------------
			bool b_throw2 = m_pExeChara2p->IsThrowAction ();
			bool b_thrown1 = m_pExeChara1p->CanBeThrown ();
			bool no_check_2 = b_throw2 && ( ! b_thrown1 );

			if ( ! no_check_2 )
			{
				//ヒット判定と攻撃判定(2P->1P)
				hit1P = OverlapAryRect_Center ( pvARect2, pvHRect1, hit_center_1p );
			}
		}


		//------------------------------------------------------
		//反映

		//相殺処理
		if ( bOffset )
		{
#if 0
			//攻撃種類の取得
			Action::ACTION_CATEGORY ac1p = m_exeChara1.GetActionCategory ();
			Action::ACTION_CATEGORY ac2p = m_exeChara2.GetActionCategory ();

			//攻撃種類の組合せ
			UINT x = 0;
			switch (ac1p)
			{
			case Action::ATTACK_L: x = 0; break;
			case Action::ATTACK_M: x = 1; break;
			case Action::ATTACK_H: x = 2; break;
			default: 0; break;	//その他は"弱"扱い
			}
			UINT y = 0;
			switch (ac2p)
			{
			case Action::ATTACK_L: y = 0; break;
			case Action::ATTACK_M: y = 1; break;
			case Action::ATTACK_H: y = 2; break;
			default: 0; break;	//その他は"弱"扱い
			}
			UINT lurch1p = LURCH[x][y];
			UINT lurch2p = LURCH[y][x];


			//[縦][横]
			const UINT c_indexDecision[3][3] =
			{
				//	{弱弱, 弱中, 弱強}, 
				//	{中弱, 中中, 中強}, 
				//	{強弱, 強中, 強強}
	#if	0
					{ CD_EQUAL, CD_RIGHT, CD_RIGHT },
					{ CD_LEFT, CD_EQUAL, CD_RIGHT },
					{ CD_LEFT, CD_LEFT, CD_EQUAL }
	#endif	//0
					//弱＞強
					{ CD_EQUAL, CD_RIGHT, CD_LEFT },
					{ CD_LEFT, CD_EQUAL, CD_RIGHT },
					{ CD_RIGHT, CD_LEFT, CD_EQUAL }
			};

			//判定勝ちの方は打合のけぞりにならず、ヒットストップの後アクション続行(キャンセル可能)

			//ExeCharaに通達
			const CLANG_DECISION_WL c_decision_wl[3] = { CD_DRAW, CD_WIN, CD_LOSE };

			m_exeChara1.OnClang (lurch1p, c_decision_wl[c_indexDecision[x][y]]);
			m_exeChara2.OnClang (lurch2p, c_decision_wl[c_indexDecision[y][x]]);


			//打合結果
			const CLANG_DECISION_LR c_decision[3] = { CD_EQUAL, CD_LEFT, CD_RIGHT };

			//打合結果表示 (打合結果勝負を左右に変換)
			if (m_exeChara1.GetDirRight ())	//1Pが右向(左側：LEFT)
			{
				sendDecision = c_decision[c_indexDecision[x][y]];
			}
			else
			{
				sendDecision = c_decision[c_indexDecision[y][x]];
			}
#endif // 0

			//打合時のエフェクト発生
			m_efClang->On ( center );
			m_efSpark->On ( center );
//			m_efParticle->On ( center );
			m_efPart->On ( center );

			//SE
			SOUND->Play_SE ( SE_Btl_Clang );

			//ヒットストップ開始
			m_tmrHitstop->Start ();

			if ( offset_ao )
			{
				m_pExeChara1p->OnClang_AO ();
				m_pExeChara2p->OnClang_OA ();
			}
			else if ( offset_oa )
			{
				m_pExeChara1p->OnClang_OA ();
				m_pExeChara2p->OnClang_AO ();
			}
			else
			{
				m_pExeChara1p->OnClang_AA ();
				m_pExeChara2p->OnClang_AA ();
			}
		}

		//------------------------------------------------------
		//Efヒット処理
		if (m_Efhit2P)
		{
			//SE
			SOUND->Play_SE ( SE_Btl_Hit );

			m_pExeChara1p->OnEfHit ();		//ヒット状態
//			m_pExeChara2p->OnDamaged (powerEf1p);		//くらい状態・ダメージ処理
			m_pExeChara2p->OnDamaged ();		//くらい状態・ダメージ処理
		}

		if (m_Efhit1P)
		{
			//SE
			SOUND->Play_SE ( SE_Btl_Hit );

			m_pExeChara2p->OnEfHit ();		//ヒット状態
//			m_pExeChara1p->OnDamaged (powerEf2p);		//くらい状態・ダメージ処理
			m_pExeChara1p->OnDamaged ();		//くらい状態・ダメージ処理
		}

		//================================================================
		//メインヒット処理
		if (hit2P)
		{
			m_pExeChara1p->OnHit ();		//ヒット状態
			m_efHit->On ( hit_center_2p );
			m_pExeChara2p->OnDamaged ();		//くらい状態・ダメージ処理
			m_pExeChara1p->OnDamaged_After ();	//相手ダメージ後
		}

		if (hit1P)
		{
			m_pExeChara2p->OnHit ();		//ヒット状態
			m_efHit->On ( hit_center_1p );
			m_pExeChara1p->OnDamaged ();		//くらい状態・ダメージ処理
			m_pExeChara2p->OnDamaged_After ();	//相手ダメージ後
		}
		//================================================================
	}



	//------------------------------------------------------
	//	内部関数
	//------------------------------------------------------
	bool Decision::DashDecision ( P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center )
	{
		tstring name = _T ( "FrontDash" );
		bool p1_dash = m_pExeChara1p->IsNameAction ( name );
		bool p2_dash = m_pExeChara1p->IsNameAction ( name );
		bool b = OverlapAryRect_Center ( pcr1->GetpvORect (), pcr2->GetpvORect (), center );
		return p1_dash & p2_dash & b;
	}

	//攻撃枠 同士判定　(中心付)
	bool Decision::DcsAtoA (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center)
	{
		//攻撃枠を取得
		PV_RECT pvARect1 = pcr1->GetpvARect ();
		PV_RECT pvARect2 = pcr2->GetpvARect ();

		//------------------------------------------------------
		//攻撃判定と攻撃判定が重なっていたらtrue
		if (OverlapAryRect_Center (pvARect1, pvARect2, center))
		{
			return true;
		}

		return false;
	}

	//相殺枠判定(中心付)
	bool Decision::DcsOffset (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center)
	{
		//攻撃枠を取得
		PV_RECT pvARect1 = pcr1->GetpvARect ();
		PV_RECT pvARect2 = pcr2->GetpvARect ();

		//相殺枠を取得
		PV_RECT pvORect1 = pcr1->GetpvORect ();
		PV_RECT pvORect2 = pcr2->GetpvORect ();

		//------------------------------------------------------
		//打合：攻撃判定と攻撃判定、または攻撃判定と相殺判定 (相殺と相殺は何もしない)
		if (OverlapAryRect_Center (pvARect1, pvARect2, center)
			|| OverlapAryRect_Center (pvORect1, pvARect2, center)
			|| OverlapAryRect_Center (pvARect1, pvORect2, center))
		{
			return true;
		}

		return false;
	}

	//エフェクトの相殺枠判定
	void Decision::DcsOffsetEf (PLP_ExEf plpExEf1, PLP_ExEf plpExEf2, P_CharaRect pCharaRect2p)
	{
		VEC2 centeref = VEC2 (0, 0);

		//エフェクトリストの相殺チェック
		for (P_ExEf pexef1 : (*plpExEf1))
		{
			P_CharaRect pcref1 = pexef1->GetpCharaRect ();

			//Chara
			if (DcsOffset (pcref1, pCharaRect2p, centeref))
			{
				//Efに相殺状態を設定
				pexef1->SetOffset (true);
			}
			//Ef
			for (P_ExEf pexef2 : (*plpExEf2))
			{
				P_CharaRect pcref2 = pexef2->GetpCharaRect ();

				if (DcsOffset (pcref1, pcref2, centeref))
				{
					//相殺時 各Efに記録
					pexef1->SetOffset (true);
				}
			}
		}

	}


	//エフェクトのヒット枠判定
	bool Decision::DcsHitEf (PLP_ExEf plpExEf1, PV_RECT pvHRect2, P_ExeChara pHitChara, int & refPower)
	{
		bool ret = false;
		VEC2 centeref = VEC2 (0, 0);

		//エフェクトリストのヒットチェック
		for (P_ExEf pexef1 : (*plpExEf1))
		{
			P_CharaRect pcref1 = pexef1->GetpCharaRect ();

			//Efが相殺時は飛ばす
			if (pexef1->GetOffset ()) { continue; }

			//枠管理の取得
			P_CharaRect pcr1pEf = pexef1->GetpCharaRect ();

			//攻撃枠を取得
			PV_RECT pvARect1 = pcr1pEf->GetpvARect ();

			//キャラの枠と判定する
			if (OverlapAryRect_Center (pvARect1, pvHRect2, centeref))
			{
				//攻撃値を設定
				refPower = pexef1->GetpScript ()->m_prmBattle.Power;

				//Efにヒット状態を設定
				pexef1->SetHit (true);

				//Charaにヒット状態を設定
				ret = true;
			}
		}

		return ret;
	}

	//判定後にキャラに反映する
	void Decision::Propagate ()
	{
	}


	//粒子エフェクト
	void Decision::Decision_EfPart ()
	{
		//両者の接触枠を取得
		PV_RECT pvRect1p = m_pExeChara1p->GetpCharaRect ()->GetpvCRect ();
		PV_RECT pvRect2p = m_pExeChara2p->GetpCharaRect ()->GetpvCRect ();

		UINT n1 = m_efPart->Collision ( pvRect1p );
		UINT n2 = m_efPart->Collision ( pvRect2p );

//		m_pExeChara1p->UpMana ( n1 );
//		m_pExeChara2p->UpMana ( n2 );
	}

#endif // 0

}	//namespace GAME

